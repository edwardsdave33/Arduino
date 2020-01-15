
#define SPEED_M1 6
#define DIR_M1 7
#define SPEED_M2 5
#define DIR_M2 4
#define LED 3
#define ENCODER 11
#define BUTTON 10
void setup() {
  pinMode(BUTTON,INPUT);
  pinMode(SPEED_M1,OUTPUT);
  pinMode(DIR_M1,OUTPUT);
  pinMode(SPEED_M2,OUTPUT);
  pinMode(DIR_M2,OUTPUT);
  pinMode(LED,OUTPUT);
  pinMODE(ENCODER,INPUT);
  
  while (!buttonIsPushed(BUTTON)) {
    Serial.println("waiting on button");
  }
  delay(100);

  while (buttonIsPushed(BUTTON)) {
    Serial.println("waiting for release");
  }
  //Serial.begin(9600); //9600 bits per secondes 
}

void loop()   {
  trans=0;
  pressed=digitalRead(BUTTON);
  digitalWrite(DIR_M1, HIGH);  
  analogWrite(SPEED_M1,100);
  digitalWrite(DIR_M2, LOW);   
  analogWrite(SPEED_M2,100);
 
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
