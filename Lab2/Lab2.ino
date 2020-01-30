#include <Arduino_LSM6DS3.h>
#include <Servo.h>

typedef struct {
  float k_p;
  float k_i;
  float k_d;
} pid_t;

typedef struct {
  int powerPin;
  int directionPin;
  pid_t pid;

  float targetVelocity;

  volatile int encoderCount;
  float pos;
  float velocity;
  float accel;

  int lastVelUpdate;
  int lastAccelUpdate;
} motor_t;

typedef struct {
  float imuAccel = 0;
} imu_axis;

const pid_t pid = {.k_p = 1, .k_i = 1, .k_d = 1};

motor_t leftMotor = {.powerPin = 6, .directionPin = 7, .pid = pid};
motor_t rightMotor = {.powerPin = 8, .directionPin = 9, .pid = pid};

/* Misc */

float derivative(float f_a, float f_b, float t_a, float t_b) {
  return (f_b - f_a) / (t_b - t_a);
};

float trapRule(float f_a, float f_b, float t_a, float t_b) {
  return (f_a + f_b) / 2 * (t_b - t_a);
};

int buttonIsPushed(int pin) { return !digitalRead(pin); };

/* Encoder ISR */

void encoderISR(motor_t &m) { m.encoderCount += (m.velocity > 0 ? 1 : -1); };

void rightEncoderISR() { encoderISR(rightMotor); };

void leftEncoderISR() { encoderISR(leftMotor); };

/* Motor opprations */

void initMotor(motor_t &m) {
  pinMode(m.powerPin, OUTPUT);
  pinMode(m.directionPin, OUTPUT);
};

float calcMotorVelocity(motor_t &m, int pos) {
  int t = millis();
  float vel = derivative(pos, m.pos, t, m.lastVelUpdate);

  m.lastVelUpdate = t;
  return vel;
};

float calcMotorAccel(motor_t &m, int velocity) {
  int t = millis();
  float accel = derivative(velocity, m.velocity, t, m.lastAccelUpdate);

  m.lastAccelUpdate = t;
  return accel;
};

int calcMotorPower(motor_t &m) {
  return (m.pid.k_p * (m.targetVelocity - m.velocity));
};

void updateMotor(motor_t &m) {
  // pos = encoderCount * wheelCircumferance / 16
  float pos = m.encoderCount * 0.33  / 16;
  float velocity = calcMotorVelocity(m, pos);
  float accel = calcMotorAccel(m, velocity);

  m.pos = pos;
  m.velocity = velocity;
  m.accel = accel;

  int power = calcMotorPower(m);

  if (m.targetVelocity > 0) {
    digitalWrite(m.directionPin, HIGH);
    analogWrite(m.powerPin, power);
  } else {
    digitalWrite(m.directionPin, LOW);
    analogWrite(m.powerPin, -power);
  }
};

void setup() {
  Serial.begin(9600); // 9600 bits per secondes

  while (!buttonIsPushed(11)) {
    Serial.println("waiting on button");
  }

  attachInterrupt(0, rightEncoderISR, CHANGE);
  attachInterrupt(1, leftEncoderISR, CHANGE);
  interrupts();
}

void loop() {
  rightMotor.targetVelocity = 0.5;
  leftMotor.targetVelocity = 0.5;

  updateMotor(rightMotor);
  updateMotor(leftMotor);

  delay(100);
}
