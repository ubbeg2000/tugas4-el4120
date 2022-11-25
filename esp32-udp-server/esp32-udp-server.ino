// Library
#include <WiFi.h>
#include <WiFiUdp.h>

// SSID dan Password WiFi:
const char *ssid = "ESP32-ELKHAN";

// Port UDP Server
const int udp_port = 8888;

int pot_pin = 35;
int but_pin = 25;

WiFiUDP udp;

void setup()
{
  // Inisialiasi komunikasi serial
  Serial.begin(115200);

  // Set mode pin-pin input
  pinMode(pot_pin, INPUT);
  pinMode(but_pin, INPUT);

  // Inisialisasi WiFi Access Point
  WiFi.softAP(ssid);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Inisialisasi server UDP
  udp.begin(WiFi.softAPIP(), udp_port);
}

void loop()
{
  char buffer_terima[100];

  // Parsing data yang diterima
  udp.parsePacket();
  if (udp.read(buffer_terima, 100) > 0)
  {
    // Membaca keadaan tombol dan potensimeter
    int but_state = digitalRead(but_pin);
    int pot_state = analogRead(pot_pin);

    // Mengirim data ke client
    char buffer_kirim[12];
    sprintf(buffer_kirim, "%d %d\n", pot_state, but_state);
    udp.beginPacket();
    udp.write((uint8_t *)buffer_kirim, 11);
    udp.endPacket();

    // Mencetak pesan yang dikirim
    Serial.println(buffer_kirim);
  }
}
