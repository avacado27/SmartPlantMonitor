#include <Wire.h>               // Includes I2C communication library
#include <LiquidCrystal_I2C.h>  // Includes library for controlling the I2C LCD

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Initializes LCD at address 0x27 for a 16x2 display

const int lightSensorPin = A0;  // Light sensor
const int moisturePin = A1;     // Soil moisture sensor
const int tempSensorPin = A2;   // NTC thermistor
const int pumpPin = 12;         // Pump

// Constants for temperature calculation
const float beta = 3950.0;               // NTC thermistor's Beta value
const float seriesResistor = 10000;      // Series resistor value (ohms)
const float roomTempResistance = 10000;  // NTC resistance at 25°C
const float roomTemp = 25 + 273.15;      // Room temperature in Kelvin

// Timing variables
unsigned long previousLCDTime = 0;
const unsigned long lcdInterval = 2000;

unsigned long previousPumpTime = 0;
const unsigned long pumpDuration = 3000;
bool showTemp = true;
bool pumpRunning = false;
unsigned long pumpStartTime = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(pumpPin, OUTPUT); // Sets the pump pin as output
  lcd.init(); // Initializes LCD display
  lcd.backlight();  // Turns on LCD backlight for visibility

}

void loop() {
  // put your main code here, to run repeatedly:
  // Read sensors
  int tempValue = analogRead(tempSensorPin);
  int lightValue = analogRead(lightSensorPin);
  int moistureValue = analogRead(moisturePin);

  // Calculate soil moisture percentage
  float moisturePercent = map(moistureValue, 0, 1023, 100, 0);

  // Calculate temperature in Celsius
  float resistance = (1023.0 / tempValue - 1) * seriesResistor;
  float tempK = 1 / (log(resistance / roomTempResistance) / beta + 1 / roomTemp);
  float tempC = tempK - 273.15;
  float tempF = tempC * 9.0 / 5.0 + 32.0;

  
  if (millis() - previousLCDTime >= lcdInterval) {
    previousLCDTime = millis();
    // Display Temperature
    if (showTemp) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Temp C: ");
      lcd.print(tempC);
      lcd.setCursor(0, 1);
      lcd.print("Temp F: ");
      lcd.print(tempF);

    } else {
      // Display light and soil moisture
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Light: ");
      if (lightValue < 300) {
        lcd.print("LOW");
      } else if (lightValue < 700) {
        lcd.print("MED");
      } else {
        lcd.print("HIGH");
      }

      lcd.setCursor(0, 1);
      lcd.print("Soil: ");
      if (moisturePercent < 35) {
        lcd.print("DRY");
      } else if (moisturePercent < 65) {
        lcd.print("MED");
      } else {
        lcd.print("WET");
      }
      if (pumpRunning) {
        lcd.print(" PUMP ON");
      }
    }

    showTemp = !showTemp;
  }
  

  // Control pump if soil moisture is below 35%
  if (moisturePercent < 35 && !pumpRunning) {
    digitalWrite(pumpPin, HIGH);  // Turn on pump
    pumpStartTime = millis();
    pumpRunning = true;
  }

  if (pumpRunning && millis() - pumpStartTime >= pumpDuration) {
    digitalWrite(pumpPin, LOW);  // Turn off pump
    pumpRunning = false;
  }
}
