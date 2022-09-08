#include <Servo.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(3,4); //Bluetooth

Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5;
Servo myservo6;

int motorSpeed =10;
int ledpin=13;
char s;
String str;
String valuestr;
int value;
void setup()
{
  myservo1.attach(10); //Gripper attached to pin 10 in arduino
  myservo2.attach(9); //Wrist pitch attached to pin 9 in arduino
  myservo3.attach(8); //Wrist roll attached to pin 8 in arduino
  myservo4.attach(7); //Elbow attached to pin 7 in arduino
  myservo5.attach(6); //Shoulder attached to pin 6 in arduino
  myservo6.attach(5); //Waist attached to pin 5 in arduino
  mySerial.begin(9600);
  Serial.begin(9600);
  pinMode(ledpin,OUTPUT);
}

void rotate(int x)
{
  myservo5.write(x);
Serial.println(x);
}


void loop()
{
  
  if (mySerial.available())
  {
  str =mySerial.readString();
  Serial.println(str);
  Serial.println("DATA RECEIVED:");
  int str_len = str.length() + 1;
  char char_array[str_len];
  str.toCharArray(char_array, str_len);
  value  = str.substring(1).toInt();
  if(char_array[0] == 'a')
  {
    Serial.println("Gripper");
    Serial.println(value);  
    if(value >= 0 && value <= 180)
    {
      myservo1.write(value);
    }
  }
  else if(char_array[0] == 'b')
  {
    Serial.println("wrist pitch");
    Serial.println(value);
    if(value >= 45 && value <= 180)
    {
      myservo2.write(value);
    }
  }
  else if(char_array[0] == 'c')
  {
    Serial.println("wrist roll");
    Serial.println(value);
    if(value >= 0 && value <= 180)
    {
      myservo3.write(value);
    }
  }
  else if(char_array[0] == 'd')
  {
    Serial.println("elbow");
    Serial.println(value);
    if(value >= 45 && value <= 130)
    {
      myservo4.write(value);
    }
  }
  else if(char_array[0] == 'e')
  {
    Serial.println("shoulder");
    Serial.println(value);  
    if(value >= 0 && value <= 170)
    {
      int current = myservo5.read();
      if(current < value)
      {
        while(current <= value)
      {
        current = current+1;
        rotate(current);
        delay(50);
      }
      }
      else
      {
      while(current > value)
      {
        current = current-1;
        rotate(current);
        delay(50);
      }        
      }
//      myservo5.write(value);
    }
  }
  else if(char_array[0] == 'f')
  {
    Serial.println("waist");
    Serial.println(value);
    if(value >= 0 && value <= 90)
    {
      myservo6.write(value);
    }
  }
}
}
