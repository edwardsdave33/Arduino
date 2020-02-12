#define BUTTON 10
#define SPEED_MLEFT 6
#define DIR_MLEFT 7
#define SPEED_MRIGHT 5
#define DIR_MRIGHT 4
#define LEFT_BUMP
#define RIGHT_BUMP
enum
{
    LEFT,
    RIGHT
};
volatile int leftEncoderCount = 0;
volatile int rightEncoderCount = 0;

void incLeftEncoderCount() { leftEncoderCount++; }
void incRightEncoderCount() { rightEncoderCount++; }

void Init()
{
    pinMode(BUTTON, INPUT);
    pinMode(SPEED_MLEFT, OUTPUT);
    pinMode(DIR_MLEFT, OUTPUT);
    pinMode(SPEED_MRIGHT, OUTPUT);
    pinMode(DIR_MRIGHT, OUTPUT);
}

int buttonIsPushed(int pin)
{
    return !digitalRead(pin);
}

void WaitButton()
{
    while (!buttonIsPushed(BUTTON))
    {
        Serial.println("waiting on button");
    }
    delay(100);

    while (buttonIsPushed(BUTTON))
    {
        Serial.println("waiting for release");
    }
}
void Pivot(int dir, int angle)
{

    analogWrite(SPEED_MLEFT, 100);
    analogWrite(SPEED_MRIGHT, 100);
    if (dir == RIGHT)
    {
        digitalWrite(DIR_MLEFT, HIGH);
        digitalWrite(DIR_MRIGHT, LOW);
    }
    else
    {
        digitalWrite(DIR_MLEFT, LOW;
        digitalWrite(DIR_MRIGHT, HIGH);
    }

    int encoderdelta = map(0, 360, 0, 24);
    int currentright = rightEncoderCount;
    while ((rightEncoderCount - currentright) < encoderdelta)
    {
    }
    analogWrite(SPEED_MLEFT, 0);
    analogWrite(SPEED_MRIGHT, 0);
}

void ReactBumpers()
{

    if (digitalRead(LEFT_BUMP) && digitalRead(RIGHT_BUMP))
    {
        Pivot(RIGHT, 180);
    }
    else if (digitalRead(LEFT_BUMP))
    {
        Pivot(RIGHT, 55);
    }

    else if (digitalRead(RIGHT_BUMP))
    {
        Pivot(LEFT, 55);
    }
}

void Forward()
{
    digitalWrite(DIR_MLEFT, HIGH);
    digitalWrite(DIR_MRIGHT, HIGH);
    analogWrite(SPEED_MLEFT, 100);
    analogWrite(SPEED_MRIGHT, 100);
}

void setup()
{
    Init();
    WaitButton();
    attachInterrupt(0, incLeftEncoderCount, CHANGE);
    attachInterrupt(1, incRightEncoderCount, CHANGE);
    interrupts();
}

void loop()
{
    Forward();
    ReactBumpers();
}