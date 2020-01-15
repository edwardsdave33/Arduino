#define LEDPIN 11
#define BUTTON 10
#define POT A0

void setup() {
  pinMode(BUTTON, INPUT);
  pinMode(POT, INPUT);
  pinMode(LEDPIN, OUTPUT);
  Serial.begin(9600); //9600 bits per secondes
}

int buttonIsPushed(int pin) {
  return !digitalRead(pin);
}

void loop() {
  int pot_val;

  while (!buttonIsPushed(BUTTON)) {
    Serial.println("waiting on button");
  }
  delay(100);

  while (buttonIsPushed(BUTTON)) {
    Serial.println("waiting for release");
  }

  while (true) {
    pot_val = analogRead(POT);
    Serial.println("blink");
    digitalWrite(LEDPIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(pot_val);               // wait for a second
    digitalWrite(LEDPIN, LOW);    // turn the LED off by making the voltage LOW
    delay(pot_val);
  }
}
