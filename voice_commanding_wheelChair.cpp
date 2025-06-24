#include <SoftwareSerial.h>
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
const int m11 = 7;
const int m12 = 6;
const int m21 = 4;
const int m22 = 2;
const int ena1 = 3;
const int ena2 = 5;
const int bz = A5;
#define trigPin1 A0
#define echoPin1 A1
long duration, distance, ULSensor;
SoftwareSerial bluetooth(A2,A3);
String Readcmd;
int  s = 0,c=0;
void setup()
{
  Serial.begin(9600);
  bluetooth.begin(9600);
  inputString.reserve(200);
  Serial.println("WELCOME TO VOICE CONTROL ROBO"); 
  bluetooth.println("WELCOME TO VOICE CONTROL ROBO");
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(bz,OUTPUT);
  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
  pinMode(m21, OUTPUT);
  pinMode(m22, OUTPUT);
  pinMode(ena1, OUTPUT);
  pinMode(ena2, OUTPUT);
  digitalWrite(bz,LOW);
  digitalWrite(m11, LOW);
  digitalWrite(m12, LOW);
  digitalWrite(m21, LOW);
  digitalWrite(m22, LOW);
  analogWrite(ena1,200);
  analogWrite(ena2,200);
  delay(2000);
  }
void loop()
{
  UltrasonicSensor(trigPin1, echoPin1);
  ULSensor = distance;
 // Serial.print("ultrasonic sensor distance = ");
   // bluetooth.println(ULSensor);
  if(ULSensor < 20 && s > 0)
  {
    Serial.println("DISTANCE IS LESSTHAN THRESHOLD VLUE ROBO STOP");
    bluetooth.println("DISTANCE IS LESSTHAN THRESHOLD VLUE ROBO STOP");
    digitalWrite(m11,LOW);
    digitalWrite(m12,LOW);
    digitalWrite(m21,LOW);
    digitalWrite(m22,LOW); 
    digitalWrite(bz,HIGH);
    if(c < 1)
    {
    digitalWrite(m11,HIGH);
    digitalWrite(m12,LOW);
    digitalWrite(m21,LOW);
    digitalWrite(m22,HIGH);
    delay(2000);
    c=2;
    }
    else
    {
      c = 0;
    digitalWrite(m11,LOW);
    digitalWrite(m12,HIGH);
    digitalWrite(m21,HIGH);
    digitalWrite(m22,LOW);
    delay(2000);
    }
    delay(500);
  }
  else
  {
   digitalWrite(bz,LOW); 
  }
  delay(800);
  Serial.print("DISTANCE = ");
  Serial.println(ULSensor);
  bluetooth.print("DISTANCE = ");
  bluetooth.println(ULSensor);
  if (stringComplete) {
    Serial.println(inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;
    delay(300);
  }
 serial_check(); 
}
void serial_check()
{
  while (bluetooth.available()){ 
  Readcmd = bluetooth.readString(); 
  if (Readcmd.length() > 0) {
  bluetooth.println(Readcmd);
  if(Readcmd == "FRONT")
  {
    Serial.println("MOVING FORWARD");
    bluetooth.println("MOVING FORWARD");
    digitalWrite(m11,LOW);
    digitalWrite(m12,HIGH);
    digitalWrite(m21,LOW);
    digitalWrite(m22,HIGH);
    s = 1;
    }
  else if(Readcmd == "BACK")
  {
    Serial.println("MOVING BACKWARD");
    bluetooth.println("MOVING BACKWARD");
    digitalWrite(m11,HIGH);
    digitalWrite(m12,LOW);
    digitalWrite(m21,HIGH);
    digitalWrite(m22,LOW);
  }
 else if(Readcmd == "LEFT")
  {
    Serial.println("MOVING LEFT");
    bluetooth.println("MOVING LEFT");
    digitalWrite(m11,LOW);
    digitalWrite(m12,HIGH);
    digitalWrite(m21,HIGH);
    digitalWrite(m22,LOW);
    }
 else if(Readcmd == "RIGHT")
 {
    Serial.println("MOVING RIGHT");
    bluetooth.println("MOVING RIGHT");
    digitalWrite(m11,HIGH);
    digitalWrite(m12,LOW);
    digitalWrite(m21,LOW);
    digitalWrite(m22,HIGH);
    }
  else if(Readcmd == "STOP")
 {
    Serial.println("STOP");
    bluetooth.println("STOP");
    digitalWrite(m11,LOW);
    digitalWrite(m12,LOW);
    digitalWrite(m21,LOW);
    digitalWrite(m22,LOW);
  }
 else
 {
   
 }
 Readcmd="";
  }
  }
  }
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
void UltrasonicSensor(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
}