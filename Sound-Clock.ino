#include "wifi_config.h"
#include <WiFi.h>
#include <ezTime.h>
#include "WavPlayer.h"
#include "sound/WavData.h"

WavPlayer player;
WiFiClient wifiClient;
String uniqueId;
Timezone LocalTime;
#define LOCAL_TIMEZONE "America/Denver"

int time_hour;
int time_minute;

const int STATUS_LED = 10;
const int BUTTON_PIN = 37;
const int SPEAK_TIMEOUT = 10000;

// TODO: 
// update IDE... need spiffs
// look at the DAC audio guy's article
// SPIFFS: ESP32 ... easy to upload all the .wav files this way.

enum SpeechState {
  WAITING,
  SPEAK_HOUR,
  SPEAK_MINUTE
};

SpeechState speechstate;

void PrintMacAddr(const unsigned char *mac) {
  Serial.print("MAC: ");
  Serial.print(mac[5],HEX);
  Serial.print(":");
  Serial.print(mac[4],HEX);
  Serial.print(":");
  Serial.print(mac[3],HEX);
  Serial.print(":");
  Serial.print(mac[2],HEX);
  Serial.print(":");
  Serial.print(mac[1],HEX);
  Serial.print(":");
  Serial.println(mac[0],HEX);
}

// SETUP and LOOP are the two required functions in Arduino

void setup() {
  digitalWrite(STATUS_LED, 1);    // Inverted for the built-in light
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(STATUS_LED, OUTPUT);
    
  Serial.begin(115200);
  delay(5000); // This is necessary for the ESP32 to get serial messages
  Serial.println("..... STARTING .....");
  WiFi.begin(cfg.ssid, cfg.password);
  while (WiFi.status() != WL_CONNECTED) {
		delay(100);
	}
  Serial.println("Wifi Connected");
 
  waitForSync();  // from ezTime, means wait for NTP to get date and time.
  Serial.println("synced");
  
  LocalTime.setLocation(LOCAL_TIMEZONE);

  speechstate = WAITING;
  Serial.println("Done with setup()");
}

void loop() {

  switch (speechstate)
  {
  case SPEAK_HOUR:
    speechstate = SpeakHour();
    break;
  case SPEAK_MINUTE:
    speechstate = SpeakMinute();
    break;
  case WAITING:
  default:
    speechstate = DoWaiting();
    break;
  }
} 

SpeechState SpeakHour() {
  SpeechState rv = SPEAK_HOUR;

  if (!player.Update()) { 
    // this handles the change from hour to minute. No longer playing the hour.
    Serial.println("minute " + (String)time_minute);
    player.StartPlaying(minuteWav[time_minute]);
    Serial.println("HOUR->MINUTE");
    rv = SPEAK_MINUTE;
  }
  return rv;
}

SpeechState SpeakMinute() {
  SpeechState rv = SPEAK_MINUTE;

    if (!player.Update()) {
      rv = WAITING;
      Serial.println("MINUTE->WAITING");
    }
    return rv;
}

SpeechState DoWaiting() {
  SpeechState rv = WAITING;
  static uint32_t prevTime = 0;
  uint32_t currTime = millis();

  if(currTime - prevTime >= SPEAK_TIMEOUT) {

    // this handles the change from hour to minute. We are done playing the hour.  Now changing states to the SPEAK_MINUTE state.
    time_hour = LocalTime.hour() % 12;
    time_minute = LocalTime.minute() / 5 * 5;
    Serial.println("Got time: hour " + (String)time_hour + " and minute " + (String)time_minute);
    
    Serial.println("hour " + (String)time_hour);
    player.StartPlaying(hourWav[time_hour]);
    Serial.println("WAITING->HOUR");
    rv = SPEAK_HOUR;
    prevTime = currTime;
  }
  events();
  return rv;
}
