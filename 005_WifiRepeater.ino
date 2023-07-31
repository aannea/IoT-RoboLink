#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

// Konfigurasi jaringan WiFi yang akan dihubungi sebagai klien (repeater)
const char* ssid_client = "MYUSUF";
const char* password_client = "Wismeneng";

// Konfigurasi jaringan WiFi baru sebagai Access Point
const char* ssid_ap = "AanNea";
const char* password_ap = "bodoamat";

ESP8266WiFiMulti wifiMulti;

void setup() {
  Serial.begin(115200);

  // Tambahkan jaringan WiFi klien yang akan dihubungi
  wifiMulti.addAP(ssid_client, password_client);

  // Tunggu hingga terhubung ke jaringan WiFi klien
  Serial.print("Connecting to WiFi client...");
  while (wifiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println();
  Serial.print("Connected to WiFi client, IP address: ");
  Serial.println(WiFi.localIP());

  // Aktifkan mode WiFi SoftAP sebagai Access Point
  WiFi.softAP(ssid_ap, password_ap);

  Serial.print("Access Point SSID: ");
  Serial.println(ssid_ap);
  Serial.print("Access Point Password: ");
  Serial.println(password_ap);
  Serial.print("Access Point IP address: ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  // Kode lain yang ingin Anda tambahkan pada loop (jika ada)
}
