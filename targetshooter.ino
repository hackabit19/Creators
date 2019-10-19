#include<math.h>
#include<Servo.h>
#define pi 3.14
#define servo_pin 9
#define baud_rate 9600
const int steppin=10;
const int dirpin=9;

Servo s;
int len,height,depth;
int pos_step,no_step,pos_servo;


void setup() {
  // put your setup code here, to run once:
  //attaching servo pins to arduino
  s.attach(servo_pin);
  //attaching stepper pins with arduino
  pinMode(steppin,OUTPUT);
  pinMode(dirpin,OUTPUT);
  Serial.begin(baud_rate); 
  s.write(90); 
  pos_step=90;
  no_step=90/1.8;
   
  
   /* Serial.println("Enter x:");
  l=Serial.read();//inputing x coordinate
  Serial.println("Enter y:");
  h=Serial.read();//inputing y coordinate
  Serial.println("Enter z:");
  d=Serial.read();//inputing z coordinate*/
}

void loop() {
  // put your main code here, to run repeatedly:
len=Serial.read();                               //reading the lenght from serial port directed from pyserial
height=Serial.read();                            //reading the lenght from serial port directed from pyserial
depth=Serial.read();                             //reading the lenght from serial port directed from pyserial
  coordinate_angle(len-50,height,depth);
  coordinate_angle(len,height+66,depth);
  coordinate_angle(len,height,depth+120);
}
void coordinate_angle(int x,int y,int z)        //function to convert 3d coordinate to spherical coordinates
{
  float r;
  int i,phi,theta;
  r=sqrt(x*x+y*y+z*z);
  theta=(atan(y/x)*180)/pi;//angle with the Z axis
  phi=(atan(sqrt(x*x+y*y)/z)*180)/pi; //angle on the x y plane(servo)
  pos_servo=s.read();
  Serial.println("Servo Initial Position");
  Serial.println(pos_servo);
  if(pos_servo<phi)
  {
    for(i=pos_servo;i<=phi;i++)
    {
      s.write(i);
      delay(20);
    }
  }
  else
  {
    for(i=pos_servo;i>=phi;i--)
    {
      s.write(i);
      delay(20);
    }
  }
  Serial.println("Servo Final position");
  Serial.println(pos_servo);
  Serial.println("Stepper Initial Position");
  Serial.println(pos_step);
  if(pos_step<theta)
  {
    digitalWrite(dirpin,HIGH);
    for(i=no_step;i<=(theta/1.8);i++)
    {
      digitalWrite(steppin,HIGH);
      delayMicroseconds(500);
      digitalWrite(steppin,LOW);
      delayMicroseconds(500);
    }
    pos_step=theta;
    no_step=theta/1.8;
  }
  else
  {
      digitalWrite(dirpin,LOW);

    for(i=no_step;i>=(theta/1.8);i--)
    {
      digitalWrite(steppin,HIGH);
      delayMicroseconds(500);
      digitalWrite(steppin,LOW);
      delayMicroseconds(500);
    }
    pos_step=theta;
    no_step=theta/1.8;
  }
    Serial.println("Stepper Final positon");
    Serial.println(pos_step);
}
