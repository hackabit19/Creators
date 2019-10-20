#include<math.h>
#include<Servo.h>
#define pi 3.14
#define servo_pin 9
#define baud_rate 9600
const int steppin=10;
const int dirpin=11;

Servo s;
Servo st;
int len,height,depth;
int pos_step,no_step,pos_servo;
void coordinate_angle(int x,int y,int z);
void trigger();
void motor();

void setup() {
  // put your setup code here, to run once:
  //attaching servo pins to arduino
  s.attach(servo_pin);
  //attaching stepper pins with arduino
  pinMode(steppin,OUTPUT);
  pinMode(dirpin,OUTPUT);
  pinMode(12,OUTPUT);
  Serial.begin(baud_rate); 
  s.write(90); 
  st.attach(8);
  pos_step=0;
  no_step=0;
   
  
   /* Serial.println("Enter x:");
  l=Serial.read();//inputing x coordinate
  Serial.println("Enter y:");
  h=Serial.read();//inputing y coordinate
  Serial.println("Enter z:");
  d=Serial.read();//inputing z coordinate*/
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available()>0)
  {
len=Serial.read();                               //reading the length from serial port directed from pyserial
height=Serial.read();                            //reading the length from serial port directed from pyserial
depth=Serial.read();       
//reading the length from serial port directed from pyserial
  
  coordinate_angle(len,height,depth);
  }
  
}
void coordinate_angle(int x,int y,int z)        //function to convert 3d coordinate to spherical coordinates
{
  float r;
  int i,phi,theta;
  r=sqrt(x*x+y*y+z*z);
  phi=(atan(y/x)*180)/pi;//angle on the x y plane(servo)
  theta=(atan(sqrt(x*x+y*y)/z)*180)/pi; //angle with the z plane(stepper)
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
  /*if(pos_step<theta)
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
  }*/
  motor(theta);
    Serial.println("Stepper Final positon");
    Serial.println(pos_step);
    trigger();  //for triggering the gun
}
void trigger()
{
  int i;
  for(i= 120;i>=1;i-=1)     // command to move from 180 degrees to 0 degrees
  {                                
    st.write(i);              //command to rotate the servo to the specified angle
    delay(10);                      
  }
}
void motor(int angle)
{
  int t=(angle*1000)/360;
  if(pos_step<angle)
  {
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
  analogWrite(12,255);
  delay(t);
  }
  else
  {
   digitalWrite(11,HIGH);
  digitalWrite(10,LOW);
  analogWrite(12,255);
  delay(t); 
  }
  pos_step=angle;
}
