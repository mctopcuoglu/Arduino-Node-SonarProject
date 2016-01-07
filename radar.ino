#include <Servo.h>
#include <NewPing.h>

#define TRIGGER_PIN  10   // Arduino'ya bağlanacak TRIGGER pini
#define ECHO_PIN     11   // // Arduino'ya bağlanacak ECHO pini
#define MAX_DISTANCE 200 // Santimetre cinsinden Sensörümüzün bize göstermesini istediğimiz maksimum uzaklık

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

Servo myservo;
int angle;
int angleStep;

int angleStepDelayInMs=50;

void setup() {
  angle=0;
  angleStep=1;
  Serial.begin(9600);
  myservo.attach(12);
}

void loop() {
    alterServoMoveDirection();

    Serial.print(angle);
    Serial.print("|");
    Serial.print(sonar.ping_cm());
    Serial.println();

    angle+=angleStep;
    myservo.write(angle);
    delay(angleStepDelayInMs);
}

void alterServoMoveDirection()
{
  if(angle==180)
  {
    angleStep=-1;  
  }
  else if (angle==0)
  {
    angleStep=1;  
  } 
}

