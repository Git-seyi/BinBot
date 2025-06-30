#include <Servo.h>

// --- Pin Definitions ---
const int pirPin = 7;
const int servoPin = 3;
const int trigPin = 10;
const int echoPin = 11;
const int redLED = 8;
const int yellowLED = 9;
const int blueLED = 6;

Servo lidServo;

// --- Variables ---
long duration;
int distance;
const int binHeight = 38; // cm
int fillLevel = 0;
bool motionDetected = false;
bool lidOpen = false;
unsigned long motionEndTime = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(pirPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(blueLED, OUTPUT);

  lidServo.attach(servoPin);
  lidServo.write(0); // Start with lid closed
}

void loop() {
  // --- Measure Fill Level (Ultrasonic) ---
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000); // 30ms timeout
  if (duration == 0) {
    Serial.println("⚠️ No echo detected – bin likely empty or issue.");
  } else {
    distance = duration * 0.034 / 2;
    fillLevel = map(distance, 2, binHeight, 100, 0);
    fillLevel = constrain(fillLevel, 0, 100);

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.print(" cm | Fill Level: ");
    Serial.print(fillLevel);
    Serial.println(" %");
  }

  // --- PIR Motion Detection ---
  int motion = digitalRead(pirPin);

  if (motion == HIGH) {
    // BLUE LED = Person detected
    digitalWrite(blueLED, HIGH);
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, LOW);

    if (!lidOpen) {
      lidServo.write(90); // Open lid
      Serial.println("LID OPEN");
      lidOpen = true;
    }

    motionDetected = true;
    motionEndTime = millis(); // Reset hold timer
  } else {
    if (motionDetected && (millis() - motionEndTime < 3000)) {
      // YELLOW LED = Recently detected
      digitalWrite(yellowLED, HIGH);
      digitalWrite(blueLED, LOW);
      digitalWrite(redLED, LOW);
      Serial.println("RECENT MOTION – HOLDING YELLOW LED");
    } else {
      // RED LED = No motion
      digitalWrite(redLED, HIGH);
      digitalWrite(blueLED, LOW);
      digitalWrite(yellowLED, LOW);

      if (lidOpen) {
        lidServo.write(0); // Close lid
        Serial.println("LID CLOSED");
        lidOpen = false;
      }

      motionDetected = false;
    }
  }

  delay(500);
}
