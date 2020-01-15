
#define MOTOR1 11
#define MOTOR2 10
#define LED 3
#define ENCODER 4
void setup() {
  pinMode(BUTTON,INPUT);
  pinMode(MOTOR1,INPUT);
  pinMode(MOTOR2,OUTPUT);
  pinMode(LED,OUTPUT);
  pinMODE(ENCODER,INPUT);
  
  //Serial.begin(9600); //9600 bits per secondes 
}

void loop()   {
  trans=0;
  pressed=digitalRead(BUTTON);
  digitalWrite(MOTOR1, HIGH);   // turn the LED on (HIGH is the voltage level)
  analogWrite(MOTOR1,100);
 
 if(digitalRead(ENCODER){
  digitalWrite(LED,HIGH);
  delay(1000);
  digitalWrite(LED,LOW);
  delay(1000);
  digitalWrite(LED,HIGH);
  delay(1000);
  digitalWrite(LED,LOW);
  trans+=1;
  }else{
  digitalWrite(LED,LOW):
    
  }
}
