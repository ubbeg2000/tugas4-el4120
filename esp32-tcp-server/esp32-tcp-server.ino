#include <WiFi.h>

const char *ssid = "ESP32-ELKHAN";

WiFiServer server(27015);

const int pot_pin = 35;
const int but_pin = 25;

unsigned long current_time = millis();
unsigned long previous_time = 0;
const long timeout_time = 2000;

void setup()
{
  Serial.begin(115200);
  delay(10);

  // Set mode pin-pin input
  pinMode(pot_pin, INPUT);
  pinMode(but_pin, INPUT);

  // Inisialisasi WiFi Access Point
  WiFi.softAP(ssid);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Inisialisai server TCP
  server.begin();
}

void loop()
{
  // Menunggu client
  WiFiClient client = server.available();

  if (client)
  {
    current_time = millis();
    previous_time = current_time;

    while (client.connected() && current_time - previous_time <= timeout_time)
    {
      current_time = millis();
      if (client.available())
      {
        // Menerima masukkan dari client
        for (int i = 0; i < 50; i++) 
        {
          char c = client.read();
        }

        // Membaca keadaan tombol dan potensiometer
        int pot_state = analogRead(pot_pin);
        int but_state = digitalRead(but_pin);
        char buffer_kirim[12];

        // Mengirim data ke client
        sprintf(buffer_kirim, "%d %d\n", pot_state, but_state);
        client.print(buffer_kirim);
      }
    }

    // Menutup koneksi
    client.stop();
  }
}
