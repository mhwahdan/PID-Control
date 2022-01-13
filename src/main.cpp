#include <Arduino.h>
#include <util/atomic.h>
#include "Motor.h"
#include "PIDController.h"

// Pins
#define ENCA 2 //Encoder pin A
#define ENCB 3 //Encoder pin B
#define PWM 6 //PWN pin for voltage magnitude control
#define IN1 5 //Direction control pin 1
#define IN2 6 //Direction control pin 2
#define MODE 1 //0 -> speed control | 1 -> direction control
#define PPR 388
/*
Approximate motor + Gear box Pulses per rotation = 388 pulses making the
Motor have max. RPM = 260 RPM but after attaching the blades to it 
Motor has 96% efficiency which changed max. RPM -> 250 RPM

Constraints :-
- The motor is provided with DC voltage power supply 12volts
- The motor is connected to a motor driver 1298n H-bridge
- The controller used is an Arduino Uno
*/

void Calculate_paramters();
double vcc;
float v;
float kp;
float ki;
float kd;
double Setpoint;
//displacment control
double angle = 180;
PIDController PID;
Motor* motor; //motor to be controlled by PID algorithm

void setup() {
    kp = 10;
    ki = 5;
    kd = 2;
    Setpoint = 100;//angle / 360 * PPR;
    pinMode(ENCA,INPUT);
    pinMode(ENCB,INPUT);
    PID.begin();
    PID.tune(20, 5, 1);
    PID.limit(-255, 255);
    PID.setpoint(Setpoint);
    attachInterrupt(digitalPinToInterrupt(ENCA), Calculate_paramters,RISING);
    // put your setup code here, to run once:
    Serial.begin(115200);
    motor = new Motor( IN1, IN2, PPR);
}

void loop() {
  float RPM;
  float angle;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
    angle = motor->getAngle();
    RPM = motor->getRPM();
  }
  Serial.print(RPM);
  Serial.println();
}

void Calculate_paramters(){
  // Read encoder B when ENCA rises
  int b = digitalRead(ENCB);
  int increment = 0;
  if(b>0){
    // If B is high, increment forward
    increment = 1;
  }
  else{
    // Otherwise, increment backward
    increment = -1;
  }
  motor->updateAngle(increment);
  motor->updateRPM(increment);
  // Compute velocity with method 2
  vcc =PID.compute(motor->getRPM());
  char d = 'A';
  if(vcc < 0)
    d = 'C';
  motor->setMotor(vcc, d);
}