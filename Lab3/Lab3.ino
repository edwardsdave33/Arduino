#define BUTTON 10
#define SPEED_MLEFT 6
#define DIR_MLEFT 7
#define SPEED_MRIGHT 5
#define DIR_MRIGHT 4

void Init(){
    pinMode(BUTTON, INPUT);
    pinMode(SPEED_MLEFT, OUTPUT);
    pinMode(DIR_MLEFT, OUTPUT);
    pinMode(SPEED_MRIGHT, OUTPUT);
    pinMode(DIR_MRIGHT, OUTPUT);
}

int buttonIsPushed(int pin) {
    return !digitalRead(pin);
}

void WaitButton(){
    while (!buttonIsPushed(BUTTON)) {
        Serial.println("waiting on button");
    }
    delay(100);

    while (buttonIsPushed(BUTTON)) {
        Serial.println("waiting for release");
   }
}

void Forward(){

}

void setup(){
    Init();
    WaitButton();
}

void loop(){
    Forward():
    ReactBumpers();

}