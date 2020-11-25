#include "wifi_config.h"
#include <WiFi.h>
#include <ezTime.h>
  
WiFiClient wifiClient;
String uniqueId;
Timezone LocalTime;
#define LOCAL_TIMEZONE "America/Denver"

const int STATUS_LED = 10;
const int BUTTON_PIN = 37;

// RYAN'S NOTES STARTING OUT:
// This code is a fork of the esp32GrowLight from dajensen's GitHub.
// need to change this to be the code for the SoundClock.

// TODO: 
// update IDE... need spiffs
// look at the DAC audio guy's article
// SPIFFS: ESP32 ... easy to upload all the .wav files this way.

// A useful resource for playing sound off an SD card in an Arduino Zero (not sure if we're going to use an SD card though)
// https://www.arduino.cc/en/Reference/AudioZeroBegin

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

void setup() {
  digitalWrite(STATUS_LED, 1);    // Inverted for the built-in light
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(STATUS_LED, OUTPUT);
    
  Serial.begin(115200);
  //delay(5000); // This is necessary for the ESP32 to get serial messages
  Serial.println("..... STARTING .....");
  WiFi.begin(cfg.ssid, cfg.password);
  while (WiFi.status() != WL_CONNECTED) {
		delay(100);
	}
  Serial.println("Wifi Connected");
 
  waitForSync();  // from ezTime, means wait for NTP to get date and time.
  Serial.println("synced");
  
  LocalTime.setLocation(LOCAL_TIMEZONE);
  Serial.println("Local time: " + LocalTime.dateTime());
  Serial.println("Hour: " + String(LocalTime.hour()) + " Minute: " + String(LocalTime.minute()));      
}

void loop() {
  Serial.println("Loop");
  int hour = LocalTime.hour() % 12;
  int minute = LocalTime.minute();
  
  delay(5000);
  Serial.println("Hour: " + (String)hour + " Minute: " + (String)minute);
} 

// SETUP and LOOP are the two required functions in Arduino
