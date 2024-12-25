#include <Wire.h>
#include <Adafruit_ADS1X15.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_BMP280.h>
//#include <PubSubClient.h>
#include <ESP8266WiFi.h>

// ADS1115, BMP280, OLED Display
Adafruit_ADS1115 ads;
Adafruit_BMP280 bmp;
Adafruit_SSD1306 display(128, 64, &Wire);

// MQTT
//const char* mqtt_server = "13.232.2.142";
//const char* mqtt_user = "admin";
//const char* mqtt_password = "admin";
//WiFiClient espClient;
//PubSubClient client(espClient);

// WiFi
//const char* ssid = "NG";
//const char* password = "1q2w3e4r";

// MQTT topics
//const char* topic_mq135 = "sensor/mq135";
//const char* topic_ldr = "sensor/ldr";
//const char* topic_temp = "temperature";
//const char* topic_pressure = "sensor/pressure";

void setup() {
  Serial.begin(9600);

  // Initialize OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC,0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.display();

  // Initialize ADS1115
  ads.begin(0x48);
  
  // Initialize BMP280
  if (!bmp.begin(0x76)) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }
  
  // Initialize WiFi
//  setup_wifi();
  
  // Set up MQTT server
//  client.setServer(mqtt_server, 1883);
}

//void setup_wifi() {
//  delay(10);
//  Serial.println();
//  Serial.print("Connecting to ");
//  Serial.println(ssid);
//  
//  WiFi.begin(ssid, password);
//  
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.print(".");
//  }
//  
//  Serial.println("");
//  Serial.println("WiFi connected");
//  Serial.println("IP address: ");
//  Serial.println(WiFi.localIP());
//}
//
//void reconnect() {
//  // Loop until reconnected
//  while (!client.connected()) {
//    Serial.print("Attempting MQTT connection...");
//    // Attempt to connect using username and password
//    if (client.connect("NodeMCUClient", mqtt_user, mqtt_password)) {
//      Serial.println("connected");
//    } else {
//      Serial.print("failed, rc=");
//      Serial.print(client.state());
//      Serial.println(" try again in 5 seconds");
//      delay(5000);
//    }
//  }
//}

void loop() {
//  if (!client.connected()) {
//    reconnect();
//  }
//  client.loop();

  // Read from ADS1115
  int16_t adc0 = ads.readADC_SingleEnded(0);  // MQ135
  int16_t adc1 = ads.readADC_SingleEnded(1);  // LDR

  // Read BMP280
  float temperature = bmp.readTemperature();
  float pressure = bmp.readPressure() / 100.0F; // Convert to hPa

  // Display data on OLED
  display.clearDisplay();
  display.setTextSize(1.6);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("MQ135: "); display.println(adc0);
  display.print("LDR: "); display.println(adc1);
  display.print("Temp: "); display.print(temperature); display.println(" C");
  display.print("Pressure: "); display.print(pressure); display.println(" hPa");
  display.display();
//  
//  // Publish to MQTT
//  client.publish(topic_mq135, String(adc0).c_str());
//  client.publish(topic_ldr, String(adc1).c_str());
//  client.publish(topic_temp, String(temperature).c_str());
//  client.publish(topic_pressure, String(pressure).c_str());

  delay(2000); // Wait for 2 seconds before repeating
}
