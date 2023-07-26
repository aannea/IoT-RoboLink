#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <CTBot.h>
#include <ESP8266WiFi.h>

const char* ssid = "Redmi"; 
const char* password = "00000000"; 
String telegramToken = "6503558712:AAHD6yn6ceBQzqtZ0p_49vS8WiZa6Pilci4";
int i = 0;
const int I2C_ADDR = 0x27;
const int LCD_COLUMNS = 16;
const int LCD_ROWS = 2;
const int sensorPin = A0;
const int soundSensorPin = D7;
const int trigPin = D3;
const int echoPin = D4;
const int trigPin2 = D6;
const int echoPin2 = D5;
const int servoPin = D0;
bool buka = false;
String isFull = "Belum Penuh";

CTBot myBot;
Servo servo;
LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_ROWS);

void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(sensorPin, INPUT);
  pinMode(soundSensorPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  lcd.setCursor(4, 0);
  lcd.print("Connecting");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    lcd.setCursor(i, 1);
    lcd.print(".");
    i++;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connected");
  servo.attach(servoPin);
  servo.write(0);
  Serial.begin(9600);
  myBot.setTelegramToken(telegramToken); 
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  int soundValue = digitalRead(soundSensorPin);
  long duration1, duration2;
  int distance1, distance2;
  Serial.println(soundValue);
  bool hasWater = sensorValue > 270;
  String status = hasWater ? "Ada Air" : "Tidak Ada Air";
  if (hasWater) {
    myBot.sendMessage(878347012, "Terdeteksi Air");
  }


  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration1 = pulseIn(echoPin, HIGH);
  distance1 = duration1 * 0.034 / 2;
  Serial.println(distance1);

  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = duration2 * 0.034 / 2;

  if (distance2 < 10) {
    isFull = "Penuh";
    myBot.sendMessage(878347012,"Bak Sampah Full, Tolong kosongkan");
  } else {
    isFull = "Belum Penuh";
  }
  Serial.println(isFull);
  
  if (distance1 < 10 || soundValue == HIGH) {
    buka = true;
  } else {
    buka = false;
  }

  if (buka) {
    servo.write(180);
    delay(2000);
  } else {
    servo.write(0);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(status);
  lcd.setCursor(0, 1);
  lcd.print(isFull);
  delay(1000);
}
