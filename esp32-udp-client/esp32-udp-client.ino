#include <WiFi.h>

// SSID WiFi:
const char *ssid = "ESP32-ELKHAN";

// Address dan port tujuan
const char *udp_address = "255.255.255.255";
const int udp_port = 8888;

// Definisi pin
int pot_pin = 35;
int but_pin = 25;

WiFiUDP udp;

void setup()
{
  // Inisialisasi komunikasi serial
  Serial.begin(115200);
  
  // Set mode pin input
  pinMode(pot_pin, INPUT);
  pinMode(but_pin, INPUT);

  // Inisialisasi WiFi Access Point
  WiFi.softAP(ssid);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Inisialisasi UDP client
  udp.begin(udp_port);
}

void loop()
{
  // Membaca keadaan tombol dan potensiometer
  int but_state = digitalRead(but_pin);
  int pot_state = analogRead(pot_pin);

  // Mengirim data ke server
  char buffer_kirim[12];
  sprintf(buffer_kirim, "%d %d\n", pot_state, but_state);
  udp.beginPacket(udp_address, udp_port);
  udp.write((uint8_t *)buffer_kirim, 11);
  udp.endPacket();
  Serial.println(buffer_kirim);

  // Jeda 10 detik
  delay(10000);
}
