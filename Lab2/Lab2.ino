#include <Arduino_LSM6DS3.h>
#include <Servo.h>

const int BUTTON = 11;
const int SPEED_RIGHT = 6;
const int DIR_RIGHT = 7;
const int SPEED_LEFT = 5;
const int DIR_LEFT = 4;

Servo xyServo;
Servo zyServo;
Servo clawServo;

class RealTimeVar
{
public:
  void set(float x)
  {
    lastValue = value;
    value = x;

    lastT = t;
    t = millis() / 1000;
  };

  float get()
  {
    return value;
  };

  float derivative()
  {
    return (value - lastValue) / (t - lastT);
  };

  float integral()
  {
    runningIntegral += (value + lastValue) / 2 * (t - lastT);
    return runningIntegral;
  };

  float value;
  float lastValue;
  float t;
  float lastT;
  float runningIntegral;
};

volatile int leftEncoderCount = 0;
volatile int rightEncoderCount = 0;

RealTimeVar leftEncoderPos;
RealTimeVar leftEncoderVel;
RealTimeVar leftEncoderAccel;

RealTimeVar imuPos;
RealTimeVar imuVel;
RealTimeVar imuAccel;

void incLeftEncoderCount() { leftEncoderCount++; }
void incRightEncoderCount() { rightEncoderCount++; }

int buttonIsPushed(int pin)
{
  return !digitalRead(pin);
}

void setup()
{
  Serial.begin(9600);

  if (!IMU.begin())
  {
    Serial.println("Failed to initialize IMU!");

    while (1)
      ;
  }

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
  analogWrite(SPEED_LEFT, 80);
  analogWrite(SPEED_RIGHT, 80);
}

float proportionalSpeed(float k, float target_rps, float current_rps)
{
  return k * (target_rps - current_rps);
}

void loop()
{
  leftEncoderPos.set(leftEncoderCount * 0.33 / 16);
  leftEncoderVel.set(leftEncoderPos.derivative());
  leftEncoderAccel.set(leftEncoderVel.derivative());

  Serial.print("Motor Data:\t\t");
  Serial.print(leftEncoderPos.get());
  Serial.print("\t");
  Serial.print(leftEncoderVel.get());
  Serial.print("\t");
  Serial.println(leftEncoderAccel.get());

  if (IMU.accelerationAvailable())
  {
    float x, y, z;

    IMU.readAcceleration(x, y, z);

    imuAccel.set(x * 9.81);
    imuVel.set(imuAccel.integral());
    imuPos.set(imuVel.integral());

    Serial.print("IMU Data:\t\t");
    Serial.print(imuPos.get());
    Serial.print('\t');
    Serial.print(imuVel.get());
    Serial.print('\t');
    Serial.println(imuAccel.get());
  }

  delay(2000);
}
