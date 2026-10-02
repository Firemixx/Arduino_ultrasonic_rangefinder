#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <NewPing.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

#define TRIG_PIN 9
#define ECHO_PIN 10
#define MAX_DIST 400

#define MEASUREMENTS 10

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DIST);

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

void setup() {

  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
}

void loop() {

  unsigned long sum = 0;
  int validMeasurements = 0;
  for (int i = 0; i < MEASUREMENTS; i++) {
    unsigned int time = sonar.ping();
    if (time > 0) {
      sum += time;
      validMeasurements++;
    }
    delay(30);
  }
  if (validMeasurements > 0)
   {
    float averageTime = (float)sum / validMeasurements;
    float distance = averageTime / 58.0;
    float millimeters = distance * 10.0;
    Serial.print("Distance: ");
    Serial.print(distance, 1);
    Serial.print(" cm / ");
    Serial.print(millimeters, 0);
    Serial.println(" mm");
    display.clearDisplay();
    display.setCursor(0, 1);
    display.setTextSize(2);
    display.print(distance, 1);
    display.print(" cm");
    display.setCursor(0, 30);
    display.print(millimeters, 0);
    display.print(" mm");
    display.display();
  }

  delay(100);
}