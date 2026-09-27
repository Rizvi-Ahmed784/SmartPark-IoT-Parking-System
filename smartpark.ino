#include <ESP32Servo.h>

// ---- Servo ----
Servo gateServo;
#define SERVO_PIN 14  // Servo connected to GPIO14

// ---- IR Sensors ----
#define IR_ENTER 16   // IR at entry
#define IR_BACK  13   // IR at exit

// ---- Ultrasonic Sensors (6 slots) ----
#define TRIG1 4
#define ECHO1 34
#define TRIG2 5
#define ECHO2 35
#define TRIG3 18
#define ECHO3 32
#define TRIG4 19
#define ECHO4 33
#define TRIG5 23
#define ECHO5 25
#define TRIG6 26
#define ECHO6 27

// ---- Parking Variables ----
int S1=0, S2=0, S3=0, S4=0, S5=0, S6=0;
int flag1=0, flag2=0;
int totalSlots = 6;
int slot = 6;  // available slots

// ---- Distance function ----
float getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);
  if (duration == 0) return 9999;
  return duration * 0.034 / 2;
}

// ---- Update slot status ----
void updateSlots() {
  S1 = (getDistance(TRIG1, ECHO1) < 5);
  S2 = (getDistance(TRIG2, ECHO2) < 5);
  S3 = (getDistance(TRIG3, ECHO3) < 5);
  S4 = (getDistance(TRIG4, ECHO4) < 5);
  S5 = (getDistance(TRIG5, ECHO5) < 5);
  S6 = (getDistance(TRIG6, ECHO6) < 5);

  int totalFull = S1+S2+S3+S4+S5+S6;
  slot = totalSlots - totalFull;
}

void setup() {
  Serial.begin(115200);

  pinMode(IR_ENTER, INPUT);
  pinMode(IR_BACK, INPUT);

  pinMode(TRIG1, OUTPUT); pinMode(ECHO1, INPUT);
  pinMode(TRIG2, OUTPUT); pinMode(ECHO2, INPUT);
  pinMode(TRIG3, OUTPUT); pinMode(ECHO3, INPUT);
  pinMode(TRIG4, OUTPUT); pinMode(ECHO4, INPUT);
  pinMode(TRIG5, OUTPUT); pinMode(ECHO5, INPUT);
  pinMode(TRIG6, OUTPUT); pinMode(ECHO6, INPUT);

  gateServo.attach(SERVO_PIN);
  gateServo.write(90); // closed

  Serial.println("ESP32 Parking System Ready...");
}

void loop() {
  updateSlots();

  // ---- Print Slot Status ----
  Serial.print("Available slots: ");
  Serial.println(slot);

  Serial.print("S1: "); Serial.print(S1 ? "Full" : "Empty");
  Serial.print(" | S2: "); Serial.print(S2 ? "Full" : "Empty");
  Serial.print(" | S3: "); Serial.println(S3 ? "Full" : "Empty");

  Serial.print("S4: "); Serial.print(S4 ? "Full" : "Empty");
  Serial.print(" | S5: "); Serial.print(S5 ? "Full" : "Empty");
  Serial.print(" | S6: "); Serial.println(S6 ? "Full" : "Empty");

  // ---- IR Entry Logic (your flag style) ----
  if (digitalRead(IR_ENTER) == LOW && flag1 == 0) {
    if (slot > 0) {
      flag1 = 1;
      if (flag2 == 0) {
        gateServo.write(0);   // open
        slot = slot - 1;
        Serial.println("Car Entered → Gate Opened");
      }
    } else {
      Serial.println("Sorry, Parking FULL → Gate Closed");
      delay(1500);
    }
  }

  // ---- IR Exit Logic ----
  if (digitalRead(IR_BACK) == LOW && flag2 == 0) {
    flag2 = 1;
    if (flag1 == 0) {
      gateServo.write(0);   // open
      slot = slot + 1;
      Serial.println("Car Exited → Gate Opened");
    }
  }

  // ---- Reset after cycle ----
  if (flag1 == 1 && flag2 == 1) {
    delay(1000);
    gateServo.write(90);  // close
    flag1 = 0;
    flag2 = 0;
    Serial.println("Gate Closed, Ready for Next Car");
  }

  Serial.println("---------------------------");
  delay(500);
}
