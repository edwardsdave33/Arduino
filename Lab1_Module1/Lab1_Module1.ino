
#define LEDPIN 11
#define BUTTON 10
#define POT A0
void setup() {
  pinMode(BUTTON,INPUT);
  pinMode(POT,INPUT);
  pinMode(LEDPIN,OUTPUT):
  Serial.begin(9600); //9600 bits per secondes 
}

void loop() {
  pot_val= analogRead(POT);
  Serial.println(pot_val);
  pushed =  digitalRead(BUTTON);
  if(!(pushed)){
    while(!(pushed)){
      pushed = digitalRead(BUTTON);
    }
  digitalWrite(LEDPIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(pot_val);               // wait for a second
  digitalWrite(LEDPIN, LOW);    // turn the LED off by making the voltage LOW
  delay(pot_val);   
  }
}
