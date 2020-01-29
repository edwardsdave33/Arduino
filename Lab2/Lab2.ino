#include <Servo.h>

const int BUTTON = 11;
const int SPEED_RIGHT = 6;
const int DIR_RIGHT = 7;
const int SPEED_LEFT = 5;
const int DIR_LEFT = 4;

Servo xyServo;
Servo zyServo;
Servo clawServo;

volatile int leftEncoderCount = 0;
volatile int rightEncoderCount = 0;

int lastLeftEncoderCount = 0;
int lastRightEncoderCount = 0;
int lastMillis = 0;

void incLeftEncoderCount() { leftEncoderCount++; }
void incRightEncoderCount() { rightEncoderCount++; }

int buttonIsPushed(int pin) {
  return !digitalRead(pin);
}

void setup() {
  Serial.begin(9600); //9600 bits per secondes

  while (!buttonIsPushed(BUTTON))
  {
    Serial.println("waiting on button");
  }

  delay(100);
  xyServo.attach(8);
  zyServo.attach(9);
  clawServo.attach(10);

  pinMode(SPEED_RIGHT, OUTPUT);
  pinMode(DIR_RIGHT, OUTPUT);
  pinMode(SPEED_LEFT, OUTPUT);
  pinMode(DIR_LEFT, OUTPUT);

  attachInterrupt(0, incLeftEncoderCount, CHANGE);
  attachInterrupt(1, incRightEncoderCount, CHANGE);
  interrupts();

  digitalWrite(DIR_RIGHT, HIGH);
  digitalWrite(DIR_LEFT, HIGH);
}

float rps(int currentCount, int lastCount, int currentTime, int lastTime) {
  return (currentCount - lastCount) / (currentTime - lastTime) / 1000;
}

float proportionalSpeed(float k, float target_rps, float current_rps) {
  return k * (target_rps - current_rps);
}

void loop() {
  float right_rps = rps(
      rightEncoderCount,
      lastRightEncoderCount,
      millis(),
      lastMillis
      );

  float left_rps = rps(
      leftEncoderCount,
      lastLeftEncoderCount,
      millis(),
      lastMillis
      );

  lastMillis = millis();

  analogWrite(SPEED_RIGHT, proportionalSpeed(100, 1, right_rps));
  analogWrite(SPEED_LEFT, proportionalSpeed(95, 1, left_rps));

  delay(500);
}
