#include <Wire.h>
#include <Adafruit_ADS1X15.h>
#include <Adafruit_SSD1306.h>
Adafruit_ADS1115 ads
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
     Serial.begin(9600);

  
  
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
  Serial.print("Voltage: "); Serial.println(voltage);


  delay(50); // Wait for 1 seconds before repeating
}
