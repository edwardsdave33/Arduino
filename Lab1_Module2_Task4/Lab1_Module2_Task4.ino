#define SPEED_M1 6
#define DIR_M1 7
#define SPEED_M2 5
#define DIR_M2 4
#define LED 3
#define BUTTON 10

struct motor {
  int encoderPin;
  int encoderState = 0;
  int encoderCount = 0;
  int rotationCount = 0;
};

motor m_left = {
  .encoderPin = 3
};

motor m_right = {
  .encoderPin = 2
};

void setup() {
  pinMode(BUTTON, INPUT);
  pinMode(POT, INPUT);
  pinMode(LEDPIN, OUTPUT);
  Serial.begin(9600); //9600 bits per secondes
}

int buttonIsPushed(int pin) {
  return !digitalRead(pin);
}

int encoderChanged(int encoder) {
    int currentState = digitalRead(encoder);
    if (currentState != encoderState) {
        encoderState = currentState;
        return true;
    }

    return false;
}

void loop() {
  if (encoderChanged()) {
    encoderCount++;
  }


}
