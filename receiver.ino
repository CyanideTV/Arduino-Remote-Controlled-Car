//Receiver code 

#include<SoftwareSerial.h>
SoftwareSerial mybt(2,3);
char direction = 0;

// SPEED CONTROL
const int ENA = 5; // left wheels
const int ENB = 6; // right wheels

// Left wheels
const int IN1 = 10;
const int IN2 = 11;

// Right wheels
const int IN3 = 12;
const int IN4 = 13;

void setup() 
{
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
    
  Serial.begin(38400);
  mybt.begin(38400);
}

void loop() 
{
  if(mybt.available()>0)
  {
    direction = mybt.read();
    // Serial.println(direction);
    if      (direction =='A')  { Serial.print("top");           car_control( 1, 0, 0, 1, 150, 150); } 
    else if (direction =='B')  { Serial.print("bottom");        car_control( 0, 1, 1, 0, 150, 150); } 
    else if (direction =='C')  { Serial.print("left");          car_control( 0, 1, 0, 1, 150, 150); }
    else if (direction =='D')  { Serial.print("right");         car_control( 1, 0, 1, 0, 150, 150); }
    else if (direction =='E')  { Serial.print("top-left");      car_control( 1, 0, 0, 1, 70, 150); }
    else if (direction =='F')  { Serial.print("top-right");     car_control( 1, 0, 0, 1, 150, 70); }
    else if (direction =='G')  { Serial.print("bottom-left");   car_control( 0, 1, 1, 0, 70, 150); }
    else if (direction =='H')  { Serial.print("bottom-right");  car_control( 0, 1, 1, 0, 150, 70); }
    else if (direction =='S')  { Serial.print("stop");          car_control( 0, 0, 0, 0, 0, 0); }
  }
}

void car_control(uint8_t sIN1, uint8_t sIN2,uint8_t sIN3,uint8_t sIN4,int sENA,int sENB)
{
    analogWrite(ENA, sENA);
    analogWrite(ENB, sENB);
    digitalWrite(IN1, sIN1);
    digitalWrite(IN2, sIN2);
    digitalWrite(IN3, sIN3);
    digitalWrite(IN4, sIN4);
    Serial.print("; Speed left = ");
    Serial.print(sENA);
    Serial.print("; Speed right = ");
    Serial.println(sENB);
}