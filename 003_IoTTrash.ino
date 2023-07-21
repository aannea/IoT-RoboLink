#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Alamat I2C LCD, sesuaikan dengan alamat LCD Anda
const int I2C_ADDR = 0x27;
// Jumlah kolom dan baris pada LCD
const int LCD_COLUMNS = 16;
const int LCD_ROWS = 2;
const int sensorPin = A0;
const int soundSensorPin = 7;
const int trigPin = 3;     // Pin trigger sensor ultrasonik
const int echoPin = 4;     // Pin echo sensor ultrasonik
const int trigPin2 = 6;
const int echoPin2 = 5;
const int servoPin = 2;    // Pin servo
bool buka = false;
String isFull = "Belum Penuh";

Servo servo;                // Objek servo
LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_ROWS);

void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(soundSensorPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  servo.attach(servoPin);
  servo.write(0);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  int soundValue = digitalRead(soundSensorPin);
  long duration1, duration2;
  int distance1, distance2;
  Serial.println(soundValue);
  bool hasWater = sensorValue > 270;
  String status = hasWater ? "Ada Air" : "Tidak Ada Air";

  // Mengirimkan pulsa ultrasonik
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Menerima waktu pantulan ultrasonik
  duration1 = pulseIn(echoPin, HIGH);

  // Menghitung jarak berdasarkan waktu pantulan
  distance1 = duration1 * 0.034 / 2;
  Serial.println(distance1);

  // Mengirimkan pulsa ultrasonik ke sensor 2
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  // Menerima waktu pantulan ultrasonik dari sensor 2
  duration2 = pulseIn(echoPin2, HIGH);

  // Menghitung jarak berdasarkan waktu pantulan dari sensor 2
  distance2 = duration2 * 0.034 / 2;

  if (distance2 < 10) {
    isFull = "Penuh";
  }else {
    isFull = "Belum Penuh";
  }
  Serial.println(isFull);
  
  // Jika objek terdeteksi dalam jarak tertentu, gerakkan servo
  if (distance1 < 10 || soundValue == HIGH) {
    buka = true;
  } else {
    buka = false;
  }

  if (buka) {
    servo.write(90);
    delay(2000);
  } else {
    servo.write(0);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(status);
  lcd.setCursor(0, 1);
  lcd.print(isFull);
  delay(1000);  // Delay antar pembacaan sensor
}
