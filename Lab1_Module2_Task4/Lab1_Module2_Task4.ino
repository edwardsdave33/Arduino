#define SPEED_M1 6
#define DIR_M1 7
#define SPEED_M2 5
#define DIR_M2 4
#define LED 3
#define BUTTON 10

volatile int leftEncoderCount = 0;
volatile int rightEncoderCount = 0;

void incLeftEncoderCount() { leftEncoderCount++; }
void incRightEncoderCount() { rightEncoderCount++; }

int buttonIsPushed(int pin) {
  return !digitalRead(pin);
}

float rotationCount(int n) {
  return (float) n / 16;
}

void setup() {
  pinMode(SPEED_M1, OUTPUT);
  pinMode(DIR_M1, OUTPUT);
  pinMode(SPEED_M2, OUTPUT);
  pinMode(DIR_M2, OUTPUT);
  pinMode(LED, OUTPUT);

  Serial.begin(9600); //9600 bits per secondes

  while (!buttonIsPushed(BUTTON))
  {
    Serial.println("waiting on button");
  }
  delay(100);

  while (buttonIsPushed(BUTTON))
  {
    Serial.println("waiting for release");
  }

  attachInterrupt(0, incLeftEncoderCount, CHANGE);
  attachInterrupt(1, incRightEncoderCount, CHANGE);
  interrupts();

  // forward
  while (true)
  {
    digitalWrite(DIR_M1, HIGH);
    digitalWrite(DIR_M2, HIGH);
    
    analogWrite(SPEED_M1, 100);
    analogWrite(SPEED_M2, 100);

    if (rotationCount(leftEncoderCount) > 3) break;
  }

  leftEncoderCount = 0;
  rightEncoderCount = 0;

  // reverse
  while (true) {
    digitalWrite(DIR_M1, LOW);
    digitalWrite(DIR_M2, LOW);

    analogWrite(SPEED_M1, 100);
    analogWrite(SPEED_M2, 100);

    if (rotationCount(leftEncoderCount) > 2) break;
  }
  
  leftEncoderCount = 0;
  rightEncoderCount = 0;

  // spin
  while (true) {
    digitalWrite(DIR_M1, HIGH);
    digitalWrite(DIR_M2, LOW);

    analogWrite(SPEED_M1, 100);
    analogWrite(SPEED_M2, 100);

    if (leftEncoderCount > 8) break;
  }

  analogWrite(SPEED_M1, 0);
  analogWrite(SPEED_M2, 0);
}

void loop() {
}
