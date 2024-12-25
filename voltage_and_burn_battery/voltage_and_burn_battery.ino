#include <Wire.h>
#include <Adafruit_ADS1X15.h>
#include <ESP8266WiFi.h>
#include <Adafruit_SSD1306.h>
Adafruit_ADS1115 ads;
const char* ssid = "dlink-4C33";       // Replace with your Wi-Fi SSID
const char* password = "roHITMAN45"; // Replace with your Wi-Fi password
WiFiServer server(80);


Adafruit_SSD1306 display(128, 64, &Wire);
void setup() {
  // put your setup code here, to run once:

  // Initialize OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC,0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.display();

  // Initialize ADS1115
  ads.begin(0x48);
   ads.setGain(GAIN_TWOTHIRDS);
     Serial.begin(115200);

  // Start Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Start server
  server.begin();

  // Set GPIO pins as output


  Serial.println("Setup complete.");

  
}

void loop() {
  // put your main code here, to run repeatedly:
  int16_t adc0 = ads.readADC_SingleEnded(1);
   float voltage = (adc0 * 0.1875) / 1000.0;  
    display.clearDisplay();
  display.setTextSize(1.6);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Voltage: "); display.println(voltage);
    display.print("step: "); display.println(adc0);
  display.display();


  // Perform CPU-intensive computation
  volatile int x = 0;
  for (int i = 0; i < 100000; i++) {
    x += i * i;
  }

  // Send dummy data over Wi-Fi
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Client connected!");
    client.println("NodeMCU Test");
    client.stop();
  }

  // Keep Wi-Fi active with periodic transmissions
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient wifiClient;
    if (wifiClient.connect("example.com", 80)) {
      wifiClient.print("GET / HTTP/1.1\r\nHost: example.com\r\n\r\n");
      wifiClient.stop();
    }
  }

  delay(50); // Wait for 1 seconds before repeating
}
