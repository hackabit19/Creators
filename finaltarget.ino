#include <AFMotor.h>
#include <Servo.h>
# define stepAngle 1.8
# define pi 3.14
Servo servo;
int x, y , z;
float theta,phi,currentAngle,n;
String serialData;

int parseDataX(String data);
int parseDataY(String data);

AF_DCMotor motor(3);//using M1and M2 

void setup( ) {
Serial.begin(9600);
//Serial.setTimeout(10);
Serial.println("Motor test!");
motor.setSpeed(255);
servo.attach(10);
servo.write(90);
motor.run(FORWARD);
delay(50*100/36);
motor.run(RELEASE);
              
}

void loop (){
  if(Serial.available()){
    
  //x = Serial.parseInt();
  //y = Serial.parseInt();
  //z = Serial.parseInt();
  serialData=Serial.readString();
  if(serialData)
  {
  theta = parseDataX(serialData);
  phi=parseDataY(serialData);
  }
  if(theta>0){
  motor_motion(theta);
  }
  if(phi>0)
  {
    servo_motion(phi,servo.read());
  }
  }
}


int parseDataX(String data)
{
  data.remove(data.indexOf("Y"));
  data.remove(data.indexOf("X"),1);
  unsigned int xdata=data.toInt();
  //xdata=(xdata*180)/600;
  Serial.print("Dc motor angle: ");
  Serial.println(xdata);
  return xdata;
}
int parseDataY(String data)
{
  data.remove(0,data.indexOf("Y")+1);
  unsigned int ydata=data.toInt();
  
  //ydata=(ydata*180)/480;
  Serial.print("Servo motor angle: ");
  Serial.println(ydata);
  return ydata;
}



void motor_motion(int theta){
//float r, phi;
int i, j ,k , l, pos_servo = 0,current_pos = 0,no_step;

//theta = (atan (x/z)*180)/ pi;
//r = z /cos((theta*pi/180));
//phi = (atan(y/r)*180)/pi;
    /*Serial.readBytes(input,sizeof(angle));
    angle=atoi(input);
    memset(input,0,sizeof(input));*/
  if(theta>0)
  {
  if( currentAngle != theta ){

        if( currentAngle < theta){
             n = theta - currentAngle;
              motor.run(FORWARD);
              delay(n*100/36);
              motor.run(RELEASE);
            Serial.print("DC MOTOR: Forward angle =");
            //Serial.println(theta);
            Serial.println(n);
            Serial.println(" ");
        }
        else if( currentAngle > theta){
            n = currentAngle - theta;
            if(theta == 0){
               n =currentAngle;
            }
            motor.run(BACKWARD);
            delay(n*100/36);
            motor.run(RELEASE);
            Serial.print("DC MOTOR: Backward angle =");
            //Serial.println(theta);
            Serial.println(n);
            Serial.println(" ");
        }
        currentAngle=theta;
  }
  }
}

void servo_motion(int phi, int pos_servo){
  
  phi=180-phi;
  if(phi<=pos_servo){

  n=pos_servo-phi;
  
  for(int i= pos_servo;i>phi;i--){
  servo.write(i);
  delay(10);
  }
  Serial.print("SERVO: Backward angle =");
  //Serial.println(phi);
  Serial.println(n);
  Serial.println(" ");
  }
  else 
  {
    n=phi-pos_servo;
  for(int i=pos_servo; i<=phi; i++){
  servo.write(i);
  delay(10);
  }
  Serial.print("SERVO: Forward angle =");
  //Serial.println(phi);
  Serial.println(n);
  Serial.println(" ");
  }
}
