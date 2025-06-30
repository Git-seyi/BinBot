// Replace these with your Blynk template info
#define BLYNK_TEMPLATE_ID "TemplateID"
#define BLYNK_TEMPLATE_NAME "Smart Bin"
#define BLYNK_AUTH_TOKEN "AuthToken"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "smartbin";       // Your Wi-Fi name (2.4GHz only)
char pass[] = "toniella1";   // Your Wi-Fi password

void setup() {
  Serial.begin(9600);  // Read from Arduino
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();

  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');

    // Expected format: "FILL:67;MOTION:DETECTED"
    int fillIndex = input.indexOf("FILL:");
    int motionIndex = input.indexOf("MOTION:");

    if (fillIndex != -1 && motionIndex != -1) {
      int fillLevel = input.substring(fillIndex + 5, input.indexOf(';')).toInt();
      String motion = input.substring(motionIndex + 7);

      // Send to Blynk
      Blynk.virtualWrite(V0, fillLevel);   // Fill Level (%)
      Blynk.virtualWrite(V1, motion);      // Motion: DETECTED or NOT DETECTED
      Blynk.virtualWrite(V2, 1);           // Online flag
    }
  }
}
