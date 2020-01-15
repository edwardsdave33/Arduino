#define LED 11
#define ENCODER 3

int encoderState = 0;

int encoderChanged() {
    int currentState = digitalRead(ENCODER);
    if (currentState != encoderState) {
        encoderState = currentState;
        return true;
    }

    return false;
}

void rapidBlink() {
    digitalWrite(LED, HIGH);
    delay(100);
    digitalWrite(LED, LOW);
    delay(100);
    digitalWrite(LED, HIGH);
    delay(100);
    digitalWrite(LED, LOW);
    delay(100);
}

void setup() {
    encoderState = digitalRead(ENCODER);
    pinMode(LED, OUTPUT);
    Serial.begin(9600);
}

void loop() {
  if (encoderChanged()) {
      Serial.println("encoderChanged");
      rapidBlink();
  }
}