#include <Arduino.h>
#include "driver/i2s.h"                       // Library of I2S routines, comes with ESP32 standard install
#include "WavHeader.h"

// I2S physical wiring connection pins
const int BCK_IO_PIN = 27;
const int WS_IO_PIN = 26; // 33 also works
const int DATA_OUT_PIN = 25;

static const i2s_port_t i2s_num = I2S_NUM_0;  // i2s port number


class WavPlayer {
public:
    WavPlayer();
    bool StartPlaying(const unsigned char *data);
    bool Update();
    bool DonePlaying();

protected:
    WavHeader header;
    unsigned const char* TheData;
    uint32_t DataIdx=0;
    bool isValid;
    uint32_t play_start_time;
    uint32_t play_end_time;

    void DumpWavHeader(WavHeader* Wav);
    bool ValidWavData(WavHeader* Wav);
    void PrintData(const char* Data,uint8_t NumBytes);
};
