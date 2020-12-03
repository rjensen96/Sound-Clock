#include "WavPlayer.h"
#include "sound/WavData.h"

WavPlayer player;

const int STATUS_LED = 10;
const int BUTTON_PIN = 37;
const int SPEAK_TIMEOUT = 5000;

enum SpeechState {
  WAITING,
  SPEAK_HOUR,
  SPEAK_MINUTE
};

SpeechState speechstate;

const int NUM_TEST_WAVS = sizeof(testWav) / sizeof(testWav[0]);


void setup() {
  digitalWrite(STATUS_LED, 1);    // Inverted for the built-in light
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(STATUS_LED, OUTPUT);

  while (! Serial) {
    delay(1);
  }

  Serial.begin(115200);
  Serial.println("..... STARTING .....");

  speechstate = WAITING;
  Serial.println("Done with setup()");
}

void loop() {
  static int file_num = -1;
  static uint32_t start_time = 0;

  if(!player.Update()) {
    file_num++;
    if(start_time > 0 && file_num < NUM_TEST_WAVS + 1)
      Serial.println("Used time: " + (String)(millis() - start_time));
    
    if(file_num < NUM_TEST_WAVS) {
      start_time = millis();
      player.StartPlaying(testWav[file_num]);
    }
  }
}
