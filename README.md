# 🌱 Smart Plant Monitor
An Arduino-based plant monitoring system that tracks soil moisture, temperature, and light levels, with an automatic water pump for dry soil.  

## 🚀 Features
✅ Measure soil moisture and display as DRY, MED, or WET  
🌡️ Monitor temperature in Celsius and Fahrenheit  
💡 Track ambient light levels as LOW, MED, or HIGH  
💧 Automatic water pump activates when soil is dry  
🖥️ Display readings on a 16x2 I2C LCD  

## 🛠️ Tech Stack
- Arduino UNO (ATmega328P)  
- Arduino IDE  
- C++ (Arduino language)  
- LiquidCrystal_I2C library (I2C LCD control)  
- Sensors: Soil moisture, Light sensor, NTC Thermistor  
- DC water pump  

## 🧰 How to Run
1. Connect the sensors and pump to the Arduino as specified in the code.  
2. Upload `SmartPlantMonitor.ino` to your Arduino using the Arduino IDE.  
3. Power the Arduino via USB or external 9V supply.  
4. Observe sensor readings on the LCD and watch the pump activate automatically when the soil is dry. 
