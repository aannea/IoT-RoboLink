#include <Servo.h>                    // Library untuk mengontrol servo
#include <Wire.h>                     // Library I2C untuk komunikasi dengan LCD
#include <LiquidCrystal_I2C.h>        // Library untuk mengontrol LCD I2C

const int I2C_ADDR = 0x27;            // Alamat I2C LCD, sesuaikan dengan alamat LCD Anda
const int LCD_COLUMNS = 16;          // Jumlah kolom pada LCD
const int LCD_ROWS = 2;              // Jumlah baris pada LCD
const int sensorPin = A0;            // Pin analog untuk membaca sensor air
const int soundSensorPin = 7;        // Pin digital untuk membaca sound sensor dan membuka tutup
const int trigPin = 3;               // Pin trigger sensor ultrasonik untuk membuka tutup
const int echoPin = 4;               // Pin echo sensor ultrasonik untuk membuka tutup
const int trigPin2 = 6;              // Pin trigger sensor ultrasonik untuk mendeteksi sampah full
const int echoPin2 = 5;              // Pin echo sensor ultrasonik untuk mendeteksi sampah full
const int servoPin = 2;              // Pin servo untuk menggerakkan tutup
bool buka = false;                   // Variable untuk mengontrol pembukaan dan penutupan tutup
String isFull = "Belum Penuh";       // Variable untuk menyimpan status penuh/tidak penuh

Servo servo;                         // Objek servo untuk mengontrol motor servo
LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_ROWS); // Objek lcd untuk mengontrol LCD I2C

void setup() {
  lcd.init();                       // Inisialisasi LCD
  lcd.backlight();                  // Hidupkan backlight LCD
  pinMode(soundSensorPin, INPUT);   // Set pin sound sensor sebagai input
  pinMode(trigPin, OUTPUT);         // Set pin trigPin sebagai output untuk sensor ultrasonik
  pinMode(echoPin, INPUT);          // Set pin echoPin sebagai input untuk sensor ultrasonik
  pinMode(trigPin2, OUTPUT);        // Set pin trigPin2 sebagai output untuk sensor ultrasonik
  pinMode(echoPin2, INPUT);         // Set pin echoPin2 sebagai input untuk sensor ultrasonik
  servo.attach(servoPin);           // Menghubungkan servo ke pin servoPin
  servo.write(0);                   // Mengatur posisi awal servo ke 0 derajat
  Serial.begin(9600);               // Inisialisasi komunikasi serial dengan baud rate 9600
}

void loop() {
  int sensorValue = analogRead(sensorPin);   // Membaca nilai analog dari sensor air
  int soundValue = digitalRead(soundSensorPin); // Membaca nilai digital dari sound sensor
  long duration1, duration2;                 // Variabel untuk menyimpan waktu pantulan ultrasonik
  int distance1, distance2;                  // Variabel untuk menyimpan jarak dari ultrasonik
  Serial.println(soundValue);                // Mencetak nilai digital dari sound sensor ke Serial Monitor
  bool hasWater = sensorValue > 270;         // Memeriksa apakah ada air dengan membaca nilai analog dari sensor air
  String status = hasWater ? "Ada Air" : "Tidak Ada Air"; // Menyimpan status air dalam bentuk string

  // Mengirimkan pulsa ultrasonik ke sensor 1
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Menerima waktu pantulan ultrasonik dari sensor 1
  duration1 = pulseIn(echoPin, HIGH);

  // Menghitung jarak berdasarkan waktu pantulan dari sensor 1
  distance1 = duration1 * 0.034 / 2;
  Serial.println(distance1);               // Mencetak jarak dari ultrasonik ke Serial Monitor

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

  // Menentukan status penuh/tidak penuh berdasarkan jarak dari sensor 2
  if (distance2 < 10) {
    isFull = "Penuh";
  } else {
    isFull = "Belum Penuh";
  }
  Serial.println(isFull);                 // Mencetak status penuh/tidak penuh ke Serial Monitor

  // Jika objek terdeteksi dalam jarak tertentu atau ada suara, gerakkan servo
  if (distance1 < 10 || soundValue == HIGH) {
    buka = true;
  } else {
    buka = false;
  }

  if (buka) {
    servo.write(90);                     // Menggerakkan servo ke posisi 90 derajat (buka)
    delay(2000);                         // Delay untuk membuka tutup selama 2 detik
  } else {
    servo.write(0);                      // Menggerakkan servo ke posisi 0 derajat (tutup)
  }

  lcd.clear();                           // Membersihkan layar LCD
  lcd.setCursor(0, 0);                   // Mengatur posisi kursor pada baris 1, kolom 1
  lcd.print(status);                     // Menampilkan status air pada LCD
  lcd.setCursor(0, 1);                   // Mengatur posisi kursor pada baris 2, kolom 1
  lcd.print(isFull);                     // Menampilkan status penuh/tidak penuh pada LCD
}
