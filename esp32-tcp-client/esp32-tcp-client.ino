#include <WiFi.h>

WiFiClient client;

const char *ssid = "ESP32-ELKHAN";

// Address dan port tujuan
const char *host = "192.168.4.2";
const uint16_t port = 27015;

int pot_pin = 35;
int but_pin = 25;

// Jumlah pengiriman data yang akan dilakukan
int attemp = 10;

void setup()
{
  // Inisialisasi komunikasi serial
  Serial.begin(115200);

  // Set mode pin-pin input
  pinMode(pot_pin, INPUT);
  pinMode(but_pin, INPUT);

  // Inisialisasi WiFi Access Point
  WiFi.softAP(ssid);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
}

void loop()
{
  // Mencoba untuk memulai koneksi ke server
  Serial.print("Menghubungkan ke ");
  Serial.println(host);

  if (!client.connect(host, port))
  {
    Serial.println("Koneksi gagal, menunggu 5 detik sebelum mencoba kembali...");
    delay(5000);
    return;
  }

  int i = 0;
  while (i < attemp)
  {
    i++;
    
    // Membaca keadaan tombol dan potensiometer
    int but_state = digitalRead(but_pin);
    int pot_state = analogRead(pot_pin);

    // Mengirimkan data ke server
    char buffer_kirim[12];
    sprintf(buffer_kirim, "%d %d\n", pot_state, but_state);
    Serial.print(buffer_kirim);
    client.print(buffer_kirim);

    // Jeda 10 detik
    delay(1000);
  }

  // Menutup koneksi
  client.stop();
  delay(5000);
}
