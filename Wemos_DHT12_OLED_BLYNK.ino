
// Use Adafruit_SSD1306-esp8266-64x48 library to display properly on 64x48 Wemos shield OLED
// or put modified "Adafruit_SSD1306.h" and "Adafruit_SSD1306.cpp" files into project folder 
// and change from <Adafruit_SSD1306.h> to "Adafruit_SSD1306.h" in code below.

#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WEMOS_DHT12.h>


#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space

#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 display(OLED_RESET);

char auth[] = ""; //Enter the Auth code which was send by Blink

char ssid[] = "";  //Enter your WIFI Name
char pass[] = "";  //Enter your WIFI Password

DHT12 dht12;


SimpleTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.

void sendSensor()
{

  float h = (dht12.humidity);
   // float h = dht12.readhumidity();
   float t = (dht12.cTemp); // or dht12.fTemp for Fahrenheit 
 //float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit 

 
    if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
 
  Blynk.virtualWrite(V5, h);  //V5 is for Humidity
  Blynk.virtualWrite(V6, t);  //V6 is for Temperature
}


void setup() {

  Serial.begin(115200);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  Blynk.begin(auth, ssid, pass);

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);

}

void loop() {
  
  // Clear the buffer.
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.setTextColor(WHITE);


  Blynk.run(); // Initiates Blynk
  timer.run(); // Initiates SimpleTimer
  if(dht12.get()==0);


  if(dht12.get()==0){
    display.println("Temp.");
    display.print(dht12.cTemp);
    display.println(" c");
    display.println("Humidity");
    display.print(dht12.humidity);
    display.println(" %");
  }
  else
  {
    display.println("Error!");
  }
  display.display();
  //delay(1000);

}
