const int forwardLeft  = 2;//*
const int backwardLeft = 3;//*
const int backwardRight= 4;//*
const int forwardRight = 5;//* + and - of both motors
const int rightMotorSpeed = 9;//*
const int leftMotorSpeed  = 6;//*Control power of rightside and leftside motor
const int stopLights = 10;//Back light
const int rightLight = 7;//*
const int leftLight  = 8;//*Left and right headlights
const int mnS = 0;  //min speed of motors
const int mdS = 100;//medium speed of motors
const int high = 1;//*
const int  low = 0;//*LOW, HIGH for digitalWrite
unsigned long lastStopLight = 0; //*
unsigned long lastBlink = 0;     //*
unsigned long flashesTime = 0;   //*timers used for lights

int onOff = 1;//used for signals
int fl = 0;//I can either flash or have automatic signals
int flashOrBlinkSignal = 0;//bool variables for signals and flashes
char cmd = 'S';//command that will be read
char lastCmd = 'S';//last command read
int speedRead = 245;//Max speed of motors

void setup() 
{
  pinMode(backwardLeft , OUTPUT);
  pinMode(backwardRight, OUTPUT);
  pinMode(forwardLeft , OUTPUT);
  pinMode(forwardRight, OUTPUT);
  pinMode(stopLights, OUTPUT);
  pinMode(leftLight,  OUTPUT);
  pinMode(rightLight, OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  if (Serial.available() > 0)
  {
    //Memorize the command sent trough bluetooth
    cmd = Serial.read();
    //turn on the lights after 400ms
    if (millis() - flashesTime > 400 && flashOrBlinkSignal == 1)
    {
      fl = 0;
      digitalWrite(leftLight,  HIGH);
      digitalWrite(rightLight, HIGH);
    }
    if (cmd == 'L' || cmd == 'R' || cmd == 'I' || cmd == 'G')
    {
      //blink every 200ms
      if (millis() - lastBlink > 200)
      {
        lastBlink = millis();
        //switch onOff from 0 to 1 everytime
        onOff = (onOff == 0) ? 1 : 0;
        //on left or forward-left blink with left light
        //else blink with rightlight
        if (cmd == 'L' || cmd == 'G')
          digitalWrite(leftLight, onOff);
        else
          digitalWrite(rightLight, onOff);
      }
    }
    if (cmd != lastCmd)
    {
      /*If command differs from last command:
        -you may need to turn on the lights;
        -change last command to the new one;
        -deal with the command. */
      if (onOff == 0 && flashOrBlinkSignal == 0)
      {
        digitalWrite(leftLight,  HIGH);
        digitalWrite(rightLight, HIGH);
      }
      lastCmd = cmd;
      dealWithIt();  
    }
  }
}
void dealWithIt()
{
  //Nu am facut switch, fiindca unele if-uri au sausi
  if (cmd != 'B' && cmd != 'H' && cmd != 'J' && cmd != 'L' && cmd != 'R')
    digitalWrite(stopLights,  LOW); 
  else
  {
    digitalWrite(stopLights, HIGH);
    lastStopLight = millis();
  }
  if (cmd >= '0' && cmd <= '9')
  {
    //change the speed of the motors.
    speedRead = 100 + (cmd - '0') * 15;
  }
  else if (cmd == 'X')
  {
    //Switches to flash
    flashOrBlinkSignal = 1;
  }
  else if (cmd == 'x')
  {
    //Switches to blinkers
    flashOrBlinkSignal = 0;
  }
  else if (cmd == 'W' || cmd == 'w')
  { 
    //Flasing
    digitalWrite(rightLight, LOW);
    digitalWrite(leftLight , LOW);
    flashesTime = millis();
    fl = 1;
  }
  else if (cmd == 'S')
    stopMoving();
  else if (cmd == 'F')
    moveDirection(high, high);
  else if (cmd == 'B')
    moveDirection(low, low);
  else if (cmd == 'L')
    moveDirection(high, low);
  else if (cmd == 'R')
    moveDirection(low, high);
  else if (cmd == 'I')
  {
    //Turn right while moving forward
    moveDirection(high, high);
    analogWrite(leftMotorSpeed, mnS);
  }
  else if (cmd == 'G')
  {
    //Turn left while moving forward
    moveDirection(high, high);
    analogWrite(rightMotorSpeed, mnS);
  }
  else if (cmd == 'J')
  {
    //Turn right while moving backwards
    moveDirection(low, low);
    analogWrite(leftMotorSpeed, mdS);
  }
  else if (cmd == 'H')
  {
    //Turn left while moving backwards
    moveDirection(low, low);
    analogWrite(rightMotorSpeed, mdS);
  }
}
void stopMoving()
{
  //Stop all motors
  digitalWrite(forwardLeft,   LOW);
  digitalWrite(forwardRight,  LOW);
  digitalWrite(backwardLeft,  LOW);
  digitalWrite(backwardRight, LOW);
  digitalWrite(stopLights,   HIGH);
  lastStopLight = millis();
}
void moveDirection(int directionLeft1, int directionRight1)
{
  /*directionLeft1 directionRight1
    1--------------1 = forward
    0--------------0 = backward
    1--------------0 = left
    0--------------1 = right
    directionLeft1,  2 - directions for left motor
    directionRight1, 2 - directions ofr right motor*/
  int directoinLeft2 = (directionLeft1 == 0)? 1 : 0;
  int directionRight2 = (directionRight1 == 0)? 1 : 0;
  digitalWrite(forwardLeft, directionLeft1);
  digitalWrite(forwardRight, directionRight1);
  digitalWrite(backwardLeft, directionLeft2);
  digitalWrite(backwardRight, directionRight2);
  analogWrite(leftMotorSpeed, speedRead);
  analogWrite(rightMotorSpeed,speedRead);
}
