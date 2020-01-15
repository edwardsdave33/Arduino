#define SPEED_M1 6
#define DIR_M1 7
#define SPEED_M2 5
#define DIR_M2 4
#define LED 3
#define ENCODER 11
#define BUTTON 10

int trans = 0;

int buttonIsPushed(int pin) {
  return !digitalRead(pin);
}

void setup()
{
  pinMode(BUTTON, INPUT);
  pinMode(SPEED_M1, OUTPUT);
  pinMode(DIR_M1, OUTPUT);
  pinMode(SPEED_M2, OUTPUT);
  pinMode(DIR_M2, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(ENCODER, INPUT);

  Serial.begin(9600);

  while (!buttonIsPushed(BUTTON))
  {
    Serial.println("waiting on button");
  }
  delay(100);

  while (buttonIsPushed(BUTTON)) {
    Serial.println("waiting for release");
  }
  
  digitalWrite(DIR_M1, HIGH);
  analogWrite(SPEED_M1, 100);
  digitalWrite(DIR_M2, LOW);
  analogWrite(SPEED_M2, 100);
}

void loop() {
  if (digitalRead(ENCODER)) {
    digitalWrite(LED, HIGH);
    delay(1000);
    digitalWrite(LED, LOW);
    delay(1000);
    digitalWrite(LED, HIGH);
    delay(1000);
    digitalWrite(LED, LOW);
    trans += 1;
  } else {
    digitalWrite(LED, LOW);
  }
}