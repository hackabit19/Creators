#include<math.h>
#include<Servo.h>
#define pi 3.14
#define servo_pin 9
#define baud_rate 9600

Servo s;
int len,height,depth;


void setup() {
  // put your setup code here, to run once:
  s.attach(servo_pin);
  Serial.begin(baud_rate); 
  s.write(90); 
   /* Serial.println("Enter x:");
  l=Serial.read();//inputing x coordinate
  Serial.println("Enter y:");
  h=Serial.read();//inputing y coordinate
  Serial.println("Enter z:");
  d=Serial.read();//inputing z coordinate*/
}

void loop() {
  // put your main code here, to run repeatedly:
len=serial.read();                               //reading the lenght from serial port directed from pyserial
height=serial.read();                            //reading the lenght from serial port directed from pyserial
depth=serial.read();                             //reading the lenght from serial port directed from pyserial
  coordinate_angle(len-50,height,depth);
  coordinate_angle(len,height+66,depth);
  coordinate_angle(len,height,depth+120);
}
void coordinate_angle(int x,int y,int z)        //function to convert 3d coordinate to spherical coordinates
{
  float r;
  int i,pos,phi,theta;
  r=sqrt(x*x+y*y+z*z);
  theta=(atan(y/x)*180)/pi;
  phi=(atan(sqrt(x*x+y*y)/z)*180)/pi;
  pos=s.read();
  Serial.println(pos);
  if(pos<phi)
  {
  for(i=pos;i<=phi;i++)
  {
    s.write(i);
    delay(20);
    }
  }
  else
  {
    for(i=pos;i>=phi;i--)
    {
      s.write(i);
      delay(20);
      }
    }
    Serial.println(pos);
}
