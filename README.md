## Parking System
## Overview
ภาพรวม (Overview)
โครงการนี้คือ ระบบที่จอดรถ (Parking System) สร้างขึ้นด้วย ESP32, จอ OLED, และเซ็นเซอร์สำหรับตรวจจับสถานะการจอดรถ
ผู้ใช้ กดปุ่ม เพื่อปิดเสียงเตือน Buzzer
เซ็นเซอร์อัลตราโซนิก ใช้ตรวจจับว่ามีรถจอดอยู่ในช่องหรือไม่
จอ OLED แสดงสถานะการจอด (ว่าง/ไม่ว่าง) 
## Hardware Used
- ESP32 
- OLED Display
- Ultrasonic Sensor (HC-SR04)
- Button Switch
- 2 LEDs (Red,  Green) + resistors
- HCSR04 Library
- Buzzer
- DHT11

  
## Pin Connections

| Component       | ESP32 Pin |
|-----------------|-----------|
| **Button**      | GPIO   5  |
| **Ultrasonic TRIG** | GPIO 32 |
| **Ultrasonic ECHO** | GPIO 33 |
| **Green LED**   | GPIO 19   |
| **Red LED**     | GPIO 18   |
| **OLED (I2C)**  | SDA: 21, SCL: 22 |
| **Buzzer**     | GPIO 4   |
| **DHT 11**     | GPIO 15  |
---
## OLED Display
หน้าจอ OLED แสดง:  
- มีรถ (แสดงไฟสีเขียว พร้อมข้อความ Available).  
- ไม่มีรถ (แสดงไฟสีแดง พร้อมข้อความ Not Available).  
- Temperature.

## หลักการทำงาน
- เมื่อไม่มีรถ แสดงไฟสีเขียว พร้อมข้อความ Available
- เมื่อมีรถ แสดงไฟสีแดง เตือนด้วยเสียง Buzzer พร้อมข้อความ Not Available
- เมื่อกดปุ่มสวิตช์สีแดง เสียงเตือน Buzzer จะหยุดลง
- เมื่อรถออกจากช่อง ไฟจะกลับมาแสดงเป็นสีเขียว พร้อมข้อความ Available

## Configuration
Code:
```cpp
// Temperature
float temperature = 0;
// Ultrasonic Sensor
const int trigPin = 32;
const int echoPin = 33;
// Buzzer && Button
const int buzzerPin = 4;
const int buttonPin = 5; 
// LEDs
const int greenLED = 19;
const int redLED = 18;
const int thresholdDistance = 50; // ระยะที่ถือว่ามีรถจอด
// สถานะเสียงถูกเปิดหรือยัง
bool alarmTriggered = false; // อ่านระยะทางจาก Ultrasonic
int count = 1;
```

---
