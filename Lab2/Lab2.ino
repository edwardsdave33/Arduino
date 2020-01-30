#include <Arduino_LSM6DS3.h>
#include <Servo.h>

class Motor {

  public:

    int targetVelocity = 0;

    int displacement = 0;
    int velocity = 0;
    int acceleration = 0;

    Motor(int speedPinIn, int directionPinIn) {
      speedPin = speedPinIn;
      directionPin = directionPinIn;

      pinMode(speedPin, OUTPUT);
      pinMode(directionPin, OUTPUT);

    }

    void encoderISR() {
      float travelPerTick = 0.33 / 16;
      velocity ? displacement += travelPerTick : displacement -= travelPerTick;
    }

    void update() {
      updateVelocity();
      updateAcceleration();
      updatePower();
    }

  private:

    int speedPin;
    int directionPin;
    int powerValue;

    int lastDisplacment = 0;
    int lastVelocity = 0;
    int lastVelocityUpdateTime = 0;
    int lastAccelerationUpdateTime = 0;

    void updateVelocity() {
      int t = millis();
      velocity = (displacement - lastDisplacement) / (t - lastVelocityUpdateTime);
      lastDisplacment = displacement;
      lastVelocityUpdateTime = t;
    }

    void updateAcceleration() {
      int t = millis();
      acceleration = (velocity - lastVelocity) / (t - lastAccelerationUpdateTime);
      lastVelocity = velocity;
      lastAccelerationUpdateTime = t;
    }

    void updatePower() {
      velocity < targetVelocity ? powerValue++ : powerValue--;

      analogWrite(speedPin, powerValue >= 0 ? powerValue : -powerValue);

      if (powerValue) {
        digitalWrite(directionPin, HIGH);
      } else {
        digitalWrite(directionPin, LOW);
      }
    }

};

Motor rightMotor (6, 7);
Motor leftMotor (5, 4);

void rightEncoderISR() {
  rightMotor.encoderISR();
}

void leftEncoderISR() {
  rightMotor.encoderISR();
}

int buttonIsPushed(int pin) {
    return !digitalRead(pin);
}

void setup() {
  Serial.begin(9600); //9600 bits per secondes

  while (!buttonIsPushed(11)) {
    Serial.println("waiting on button");
  }

  attachInterrupt(0, rightEncoderISR, CHANGE);
  attachInterrupt(1, leftEncoderISR, CHANGE);

  interrupts();
}

void loop() {
  rightMotor.update();
  leftMotor.update();

  delay(100);
}
