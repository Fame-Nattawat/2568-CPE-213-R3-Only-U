#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// Temperature
#define DHTPIN 15
#define DHTTYPE DHT11
float temperature = 0;
DHT dht(DHTPIN, DHTTYPE);
// OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Ultrasonic Sensor
const int trigPin = 32;
const int echoPin = 33;

// Buzzer && Button
const int buzzerPin = 4;
const int buttonPin = 5; 
// LEDs
const int greenLED = 19;
const int redLED = 18;

// ระยะที่ถือว่ามีรถจอด
const int thresholdDistance = 50; // ค่อยแก้หาระยะ

// สถานะเสียงถูกเปิดหรือยัง
bool alarmTriggered = false;
// อ่านระยะทางจาก Ultrasonic
int count = 1;
float readDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;
  return distance;
}

void setup() {
  dht.begin();
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  // เริ่ม OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED Not Work!!"));
    while (true); // ค้างไว้
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 20);
  display.println("READY....");
  display.display();
  delay(2000);
}

void loop() {
  float distance = readDistance();
  float tSum = 0;
    for (int i = 0; i < 3; i++)
    {
      float t = dht.readTemperature();
      tSum += t;
      delay(200);
    }
  temperature = tSum / 3;
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 10);

  if (distance <= thresholdDistance && !alarmTriggered && count ==1) {
    tone(buzzerPin, 1000); // เริ่มเสียงค้าง
    alarmTriggered = true; // ตั้งสถานะว่าเปิดไปแล้ว
  } else if (!alarmTriggered) {
    noTone(buzzerPin); // ไม่มีเสียง
  }
	

  if (distance <= thresholdDistance) {
    // ตรวจพบรถ และยังไม่ได้เปิดเสียง
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
    display.println("Not Available");
    display.print("Temperature = ");
    display.print(temperature);
  } else{
    // ยังไม่มีรถ และยังไม่เคยเปิดเสียง
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
    display.println("Available");
    display.print("Temperature = ");
    display.print(temperature);
    
  }
    if (digitalRead(buttonPin) == LOW) {
    count = 0;
    noTone(buzzerPin);     // หยุดเสียง
    alarmTriggered = false; // รีเซ็ตสถานะ
    }
    if (distance > thresholdDistance){
	count = 1;
}

  display.display();
  delay(300);
}