#include <Audio.h>
#include "Arduino.h"
#include "WiFi.h"

#define I2S_DOUT  42
#define I2S_BCLK  1
#define I2S_LRC   2

Audio audio;

void setup() {
  Serial.begin(115200);

  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin("vivoY21", "tushar111");

  while (WiFi.status() != WL_CONNECTED)
    delay(1500);

  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(100);
  audio.connecttospeech("amol khadake Pune exemplifies an indigenous Marathi culture and ethos in which education arts and crafts and theatres are given due prominence", "en"); // Google TTS
}

void loop() {
  audio.loop();
}

void audio_info(const char *info) {
  Serial.print("audio_info: ");
  Serial.println(info);
}
