#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  dht.begin();

  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(10, 20);
  display.println("Starting...");
  display.display();
  delay(2000);
}

void loop() {
  float temp = dht.readTemperature();      // Celsius
  float humidity = dht.readHumidity();

  // Check if reading failed
  if (isnan(temp) || isnan(humidity)) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(10, 25);
    display.println("Sensor Error!");
    display.display();
    delay(2000);
    return;
  }

  display.clearDisplay();

  // Title
  display.setTextSize(1);
  display.setCursor(30, 0);
  display.println("DHT11 Sensor");
  display.drawLine(0, 10, 127, 10, SSD1306_WHITE);

  // Temperature
  display.setTextSize(1);
  display.setCursor(0, 16);
  display.println("Temp:");
  display.setTextSize(2);
  display.setCursor(0, 26);
  display.print(temp, 1);
  display.println(" C");

  // Humidity
  display.setTextSize(1);
  display.setCursor(0, 46);
  display.println("Humidity:");
  display.setTextSize(2);  
  display.setCursor(60, 46);  // adjust this if needed
  display.print(humidity, 0);
  display.println("%");

  display.display();

  Serial.print("Temp: "); Serial.print(temp);
  Serial.print(" C  Humidity: "); Serial.println(humidity);

  delay(2000); // DHT11 needs ~2 sec between readings
}