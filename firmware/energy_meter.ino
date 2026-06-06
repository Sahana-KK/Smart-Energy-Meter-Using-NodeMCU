```cpp
/*
  Embedded Energy Management System Using NodeMCU (ESP8266)
  -----------------------------------------------------------
  Features:
  - ACS712 current sensor RMS measurement
  - Real-time power calculation
  - Energy consumption estimation (kWh)
  - OLED display output (SSD1306)
  - Serial monitoring for debugging

  Hardware:
  - NodeMCU ESP8266
  - ACS712 Current Sensor
  - SSD1306 OLED Display (I2C)

  Author: Sahana
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ---------------- OLED CONFIG ----------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ---------------- SENSOR CONFIG ----------------
const int sensorPin = A0;

// Calibration offset (zero-current ADC value)
int offsetADC = 512;

// ---------------- VARIABLES ----------------
float current = 0.0;
float power = 0.0;
float energy = 0.0;

// Mains voltage assumption (India standard)
const float voltage = 230.0;

// Timing
unsigned long prevTime = 0;

// ---------------- SETUP ----------------
void setup() {
  Serial.begin(115200);

  // I2C for OLED (SDA=D2 GPIO4, SCL=D1 GPIO5)
  Wire.begin(4, 5);

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED init failed");
    while (true);
  }

  display.clearDisplay();
  display.setTextColor(WHITE);

  display.setTextSize(2);
  display.setCursor(10, 20);
  display.println("SMART");
  display.display();
  delay(2000);

  // ---------------- CALIBRATION ----------------
  // Find zero-current ADC offset
  long sum = 0;

  for (int i = 0; i < 500; i++) {
    sum += analogRead(sensorPin);
    delay(2);
  }

  offsetADC = sum / 500;

  Serial.print("Calibrated Offset: ");
  Serial.println(offsetADC);

  prevTime = millis();
}

// ---------------- LOOP ----------------
void loop() {

  // -------- RMS CURRENT CALCULATION --------
  long sumSq = 0;

  for (int i = 0; i < 200; i++) {
    int adc = analogRead(sensorPin);
    int diff = adc - offsetADC;
    sumSq += diff * diff;
    delay(1);
  }

  float rms = sqrt(sumSq / 200.0);

  // Calibration factor (tune based on ACS712 model)
  current = rms * 0.02;

  // Noise filtering
  if (current < 0.05) current = 0;

  // -------- POWER CALCULATION --------
  power = voltage * current;

  // -------- ENERGY CALCULATION --------
  unsigned long now = millis();
  float hours = (now - prevTime) / 3600000.0;
  prevTime = now;

  energy += (power * hours) / 1000.0; // Wh → kWh

  // ---------------- SERIAL OUTPUT ----------------
  Serial.print("Current: ");
  Serial.print(current, 2);
  Serial.println(" A");

  Serial.print("Power: ");
  Serial.print(power, 0);
  Serial.println(" W");

  Serial.print("Energy: ");
  Serial.print(energy, 3);
  Serial.println(" kWh");

  // ---------------- OLED DISPLAY ----------------
  display.clearDisplay();
  display.setTextSize(1);

  display.setCursor(0, 0);
  display.print("Current: ");
  display.print(current, 2);
  display.println(" A");

  display.setCursor(0, 20);
  display.print("Power: ");
  display.print(power, 0);
  display.println(" W");

  display.setCursor(0, 40);
  display.print("Energy: ");
  display.print(energy, 3);
  display.println(" kWh");

  display.display();

  delay(500);
}
```
