#include "Motor.h"
#include <Arduino.h>



Motor::Motor(int in1, int in2, int ppr)
{
  this->in1 = in1;
  this->in2 = in2;
  this->ppr = ppr;
  this->angle = 0;
  this->RPM = 0;
  pinMode(this->in1,OUTPUT);
  pinMode(this->in2,OUTPUT);
  digitalWrite(this->in1,LOW);
  digitalWrite(this->in2,LOW);
  return;
}

Motor::~Motor()
{
    digitalWrite(this->in1,LOW);
    digitalWrite(this->in2,LOW);
}


int Motor::setMotor(int power){
  if(power < 0){
    analogWrite(this->in1, abs(power));
    digitalWrite(this->in2,LOW);
    return 1;
  }
  digitalWrite(this->in1,LOW);
  analogWrite(this->in2, power);
  return 1;  
}

int Motor::stopMotor(){
    digitalWrite(this->in1,LOW);
    digitalWrite(this->in2,LOW);
    return 1;
}


float Motor::updateRPM(int increment)
{
  long currT = micros();
  float deltaT = ((float) (currT - prevT))/1.0e6; 
  this->prevT = currT;
  this->RPM = (increment/deltaT)/this->ppr*60.0;
  return this->RPM;
}


float Motor::updateAngle(int increment)
{
  this->angle += increment;
  return this->angle;
}

float Motor::getAngle()
{
  return this->angle;
}

float Motor::getRPM()
{
  return this->RPM;
}