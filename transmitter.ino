//transmitter code 
#include<SoftwareSerial.h>

SoftwareSerial mybt(2,3);

int x_direction, x_position;
int y_direction, y_position;

const int PIN_ANALOG_X = 0;
const int PIN_ANALOG_Y = 1;

const int X_THRESHOLD_LOW = 490;
const int X_THRESHOLD_HIGH = 540;

const int Y_THRESHOLD_LOW = 480;
const int Y_THRESHOLD_HIGH = 530;

void setup() 
{
pinMode(A0, INPUT);
pinMode(A1, INPUT);
mybt.begin(38400);
Serial.begin(38400);
}

void loop() 
{

  x_direction = 0;
  y_direction = 0;

  //read current position
  x_position = analogRead(PIN_ANALOG_X);
  y_position = analogRead(PIN_ANALOG_Y);

  Serial.print("x = ");
  Serial.print(x_position);
  Serial.print(", y = ");
  Serial.print(y_position);
  Serial.print("; Direction: ");

  if        (x_position > X_THRESHOLD_HIGH) { x_direction = 1;  }
  else if   (x_position < X_THRESHOLD_LOW)  { x_direction = -1; }

  if        (y_position > Y_THRESHOLD_HIGH) { y_direction = 1;  }
  else if   (y_position < Y_THRESHOLD_LOW)  { y_direction = -1; }

  if (x_direction == -1) // car needs to go left side
    {
      if      (y_direction == -1) { mybt.write("E"); Serial.println("top-left"); }     // (-1,-1) top right corner
      else if (y_direction == 0)  { mybt.write("C"); Serial.println("left"); }           // (-1,0) forward
      else                        { mybt.write("G"); Serial.println("bottom-left"); }      // (-1,+1) tof left corner
    }
    
  else if (x_direction == 0) // car need to go straight 
    {
      if      (y_direction == -1) { mybt.write("A"); Serial.println("top"); }         // (0,-1) right
      else if (y_direction == 0)  { mybt.write("S"); Serial.println("stop"); }          // (0,0) stop
      else                        { mybt.write("B"); Serial.println("bottom"); }          // (0,+1) left
    }

  else if (x_direction == 1) // car needs to go right side
    {
      if      (y_direction == -1) { mybt.write("F"); Serial.println("top-right"); }  // (+1,-1) bottom right corner
      else if (y_direction == 0)  { mybt.write("D"); Serial.println("right"); }        // (0,0) reverse
      else                        { mybt.write("H"); Serial.println("bottom-right"); }   // (+1,+1) bottom left corner
    }

  delay(200);

}
