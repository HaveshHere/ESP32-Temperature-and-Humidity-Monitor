# 🌡️ ESP32-Temperature-and-Humidity-Monitor

Real-time temperature and humidity monitoring using DHT11 sensor displayed on an OLED screen with ESP32.

## 📸 Hardware Setup

![Image](https://github.com/user-attachments/assets/8d2defa1-6ab3-4048-ab16-c50044244ff9)

## 🎥 Demo

<!-- Add your demo video or GIF here -->

---

## 🛠️ Hardware Requirements

- ESP32 Development Board
- DHT11 Temperature & Humidity Sensor Module
- SSD1306 OLED Display (128x64, I2C)
- Breadboard
- Jumper Wires

---

## 🔌 Wiring Table

### OLED Display (SSD1306)

| OLED Pin | ESP32 Pin |
|----------|-----------|
| VCC      | 3.3V      |
| GND      | GND       |
| SDA      | GPIO 21   |
| SCL      | GPIO 22   |

### DHT11 Sensor

| DHT11 Pin | ESP32 Pin |
|-----------|-----------|
| VCC (+)   | 3.3V      |
| GND (-)   | GND       |
| S (Signal)| GPIO 4 (D4) |

> **Tip:** Use the breadboard's power rails (red = 3.3V, blue = GND) to share power between both the OLED and DHT11.

---

## 📦 Libraries Required

Install these via Arduino IDE → Library Manager:

- `Adafruit SSD1306`
- `Adafruit GFX Library`
- `DHT sensor library` by Adafruit

---

## 💻 Code

```cpp
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
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();

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

  display.setTextSize(1);
  display.setCursor(30, 0);
  display.println("DHT11 Sensor");
  display.drawLine(0, 10, 127, 10, SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(0, 16);
  display.println("Temp:");
  display.setTextSize(2);
  display.setCursor(0, 26);
  display.print(temp, 1);
  display.println(" C");

  display.setTextSize(1);
  display.setCursor(0, 46);
  display.println("Humidity:");
  display.setTextSize(2);
  display.setCursor(60, 46);
  display.print(humidity, 0);
  display.println("%");

  display.display();

  Serial.print("Temp: "); Serial.print(temp);
  Serial.print(" C  Humidity: "); Serial.println(humidity);

  delay(2000);
}
```

---

## 🚦 Getting Started

1. Clone this repository.
2. Open the `.ino` file in Arduino IDE.
3. Install the required libraries via Library Manager.
4. Select your ESP32 board under **Tools → Board → ESP32 Dev Module**.
5. Connect your hardware following the wiring table above.
6. Upload the code and open Serial Monitor at **115200 baud** to verify readings.
