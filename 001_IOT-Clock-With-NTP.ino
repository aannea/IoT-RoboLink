#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <TimeLib.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);//scl d1 sda d2

char* ssid = "YOUR_WIFI";
char* pw = "YOUR_WIFI_PASSWORD";
const long utcOffsetInSeconds = 25200;
WiFiUDP ntpUDP;

NTPClient timeClient(ntpUDP, "id.pool.ntp.org", utcOffsetInSeconds);

char Time[ ] = "Jam: 00:00:00";
char Date[ ] = "Tgl: 00/00/2000";
byte last_second, second_, minute_, hour_, day_, month_;
int year_;
int i=0;
int led = D4;

void setup() {
  pinMode(led,OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Aan Aryoo");
  lcd.setCursor(6,1);
  lcd.print("NEA");
  delay(2000);
  

  WiFi.begin(ssid, pw);
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Connecting");

  while(WiFi.status() != WL_CONNECTED){
    if(i==11){
      i=0;
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("Connecting");
    }
    delay(200);
    lcd.setCursor(3+i,1);
    lcd.print(".");
    i++;
  }
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Connected!");
  lcd.setCursor(6,1);
  lcd.print("NICE");
  
  delay(2000);
  timeClient.begin();
}

void loop() {
  
  timeClient.update();
  unsigned long unix_epoch = timeClient.getEpochTime();

  second_ = second(unix_epoch);
  if(last_second != second_) {
    minute_ = minute(unix_epoch);
    hour_ = hour(unix_epoch);
    day_ = day(unix_epoch);
    month_ = month(unix_epoch);
    year_ = year(unix_epoch);

    Time[12] = second_ % 10 + 48;
    Time[11] = second_ / 10 + 48;
    Time[9] = minute_ % 10 + 48;
    Time[8] = minute_ / 10 + 48;
    Time[6] = hour_ % 10 + 48;
    Time[5] = hour_ / 10 + 48;

    Date[5] = day_ / 10 + 48;
    Date[6] = day_ % 10 + 48;
    Date[8] = month_ / 10 + 48;
    Date[9] = month_ % 10 + 48;
    Date[13] = (year_ / 10) % 10 + 48;
    Date[14] = year_ % 10 %10 + 48;

    lcd.setCursor(0,0);
    lcd.print(Time);
    lcd.setCursor(0,1);
    lcd.print(Date);
    last_second = second_;
  }
  digitalWrite(led,HIGH);
  delay(1000);
  digitalWrite(led,LOW);
}
