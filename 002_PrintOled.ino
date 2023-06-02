#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
int i = 0;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  display.clearDisplay();
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  display.setCursor(0, i);
  display.println("Aan Aryo Ganteng");
  display.display();
  digitalWrite(LED_BUILTIN, LOW);
  if (i > 48)
    i = 0;
  i += 8;
  delay(500);
}
