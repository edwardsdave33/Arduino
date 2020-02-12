#define BUTTON 10


void Init(){
    pinMode(BUTTON, INPUT);


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

void setup(){
    Init();
    WaitButton();
}

void loop(){

    
}