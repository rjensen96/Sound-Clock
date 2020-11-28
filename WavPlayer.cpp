#include "WavPlayer.h"

i2s_config_t WavPlayer::i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
    .sample_rate = 44100,                            // Note, this will be changed later
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
    .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,       // high interrupt priority
    .dma_buf_count = 8,                             // 8 buffers
    .dma_buf_len = 1024,                            // 1K per buffer, so 8K of buffer space
    .use_apll=0,
    .tx_desc_auto_clear= true, 
    .fixed_mclk=-1    
};

i2s_pin_config_t WavPlayer::pin_config = {
    .bck_io_num = BCK_IO_PIN,                                 // The bit clock connectiom, goes to pin 27 of ESP32
    .ws_io_num = WS_IO_PIN,                                  // Word select, also known as word select or left right clock
    .data_out_num = DATA_OUT_PIN,                               // Data out from the ESP32, connect to DIN on 38357A
    .data_in_num = I2S_PIN_NO_CHANGE                  // we are not interested in I2S data into the ESP32
};



bool WavPlayer::StartPlaying(const unsigned char *data) {
    memcpy(&header,data,44);                     // Copy the header part of the wav data into our structure
    DumpWavHeader(&header);                          // Dump the header data to serial, optional!
    if(ValidWavData(&header))
    {
        i2s_driver_install(i2s_num, &i2s_config, 0, NULL);        // ESP32 will allocated resources to run I2S
        i2s_set_pin(i2s_num, &pin_config);                        // Tell it the pins you will be using
        i2s_set_sample_rates(i2s_num, header.SampleRate);      //set sample rate 
        TheData=data + sizeof(header);                                       // set to start of data  
        DataIdx = 0;
        isValid = true;
        Serial.println("StartPlaying: Valid header");
    }
    else
        isValid = false;                     
}

bool WavPlayer::Update() {
    if(isValid) {
        uint8_t Mono[4];                             // This holds the data we actually send to the I2S if mono sound
        const unsigned char *Data;                   // Points to the data we are going to send                                              
        size_t BytesWritten;                         // Returned by the I2S write routine, we are not interested in it

        // The WAV Data could be mono or stereo but always 16 bit, that's a data size of 2 byte or 4 bytes  
        // Unfortunately I2S only allows stereo, so to send mono we have to send the mono sample on both left and right
        // channels. It's a bit of a faf really!
        if(header.NumChannels==1)     // mono
        {
            Mono[0]=*(TheData+DataIdx);                 // copy the sample to both left and right samples, this is left
            Mono[1]=*(TheData+DataIdx+1);      
            Mono[2]=*(TheData+DataIdx);                 // Same data to the right channel
            Mono[3]=*(TheData+DataIdx+1);     
            Data=Mono;    
        }
        else                            // stereo
            Data=TheData+DataIdx;

        i2s_write(i2s_num,Data,4,&BytesWritten, portMAX_DELAY); 
        DataIdx+=header.BlockAlign;                            // increase the data index to next next sample
        if(DataIdx>=header.DataSize){               // If we gone past end of data reset back to beginning
            isValid = false;                   
        }
        return true;
    }

  return false;
}

void WavPlayer::DumpWavHeader(WavHeader* Wav)
{
  if(memcmp(Wav->RIFFSectionID,"RIFF",4)!=0)
  {
    Serial.print("Not a RIFF format file - ");    
    PrintData(Wav->RIFFSectionID,4);
    return;
  } 
  if(memcmp(Wav->RiffFormat,"WAVE",4)!=0)
  {
    Serial.print("Not a WAVE file - ");  
    PrintData(Wav->RiffFormat,4);  
    return;
  }  
  if(memcmp(Wav->FormatSectionID,"fmt",3)!=0)
  {
    Serial.print("fmt ID not present - ");
    PrintData(Wav->FormatSectionID,3);      
    return;
  } 
  if(memcmp(Wav->DataSectionID,"data",4)!=0)
  {
    Serial.print("data ID not present - "); 
    PrintData(Wav->DataSectionID,4);
    return;
  }  
  // All looks good, dump the data
  Serial.print("Total size :");Serial.println(Wav->Size);
  Serial.print("Format section size :");Serial.println(Wav->FormatSize);
  Serial.print("Wave format :");Serial.println(Wav->FormatID);
  Serial.print("Channels :");Serial.println(Wav->NumChannels);
  Serial.print("Sample Rate :");Serial.println(Wav->SampleRate);
  Serial.print("Byte Rate :");Serial.println(Wav->ByteRate);
  Serial.print("Block Align :");Serial.println(Wav->BlockAlign);
  Serial.print("Bits Per Sample :");Serial.println(Wav->BitsPerSample);
  Serial.print("Data Size :");Serial.println(Wav->DataSize);
}

bool WavPlayer::ValidWavData(WavHeader* Wav)
{
  
  if(memcmp(Wav->RIFFSectionID,"RIFF",4)!=0) 
  {    
    Serial.print("Invlaid data - Not RIFF format");
    return false;        
  }
  if(memcmp(Wav->RiffFormat,"WAVE",4)!=0)
  {
    Serial.print("Invlaid data - Not Wave file");
    return false;           
  }
  if(memcmp(Wav->FormatSectionID,"fmt",3)!=0) 
  {
    Serial.print("Invlaid data - No format section found");
    return false;       
  }
  if(memcmp(Wav->DataSectionID,"data",4)!=0) 
  {
    Serial.print("Invlaid data - data section not found");
    return false;      
  }
  if(Wav->FormatID!=1) 
  {
    Serial.print("Invlaid data - format Id must be 1");
    return false;                          
  }
  if(Wav->FormatSize!=16) 
  {
    Serial.print("Invlaid data - format section size must be 16.");
    return false;                          
  }
  if((Wav->NumChannels!=1)&(Wav->NumChannels!=2))
  {
    Serial.print("Invlaid data - only mono or stereo permitted.");
    return false;   
  }
  if(Wav->SampleRate>48000) 
  {
    Serial.print("Invlaid data - Sample rate cannot be greater than 48000");
    return false;                       
  }
  if(Wav->BitsPerSample!=16) 
  {
    Serial.print("Invlaid data - Only 16 bits per sample permitted.");
    return false;                        
  }
  return true;
}

void WavPlayer::PrintData(const char* Data,uint8_t NumBytes)
{
    for(uint8_t i=0;i<NumBytes;i++)
      Serial.print(Data[i]); 
      Serial.println();  
}
