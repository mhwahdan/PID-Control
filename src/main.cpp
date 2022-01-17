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

PIDController PID;
Motor* motor; //motor to be controlled by PID algorithm
int mode = 0;
void setup() {
    motor = new Motor( IN1, IN2, PPR);
    Serial.begin(115200);
    while (Serial.available() == 0);
    mode = Serial.readString().toInt();
    Serial.println("Enter Setpoint");
    while (Serial.available() == 0);
    Setpoint = Serial.readString().toDouble();
    if(mode == 2)
      Setpoint = Setpoint / 360 * motor->ppr;
    Serial.println("Enter KP");
    while (Serial.available() == 0);
    kp = Serial.readString().toDouble();
    Serial.println("Enter KI");
    while (Serial.available() == 0);
    ki = Serial.readString().toDouble();
    Serial.println("Enter KD");
    while (Serial.available() == 0);
    kd = Serial.readString().toDouble();
    //Setpoint = 100;//angle / 360 * PPR;
    pinMode(ENCA,INPUT);
    pinMode(ENCB,INPUT);
    PID.begin();
    PID.tune(kp, ki, kd);
    PID.limit(-255, 255);
    PID.setpoint(Setpoint);
    attachInterrupt(digitalPinToInterrupt(ENCA), Calculate_paramters,RISING);
    // put your setup code here, to run once:
    motor->setMotor(50);
}

void loop() {
  float RPM;
  float angle;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
    angle = motor->getAngle();
    RPM = motor->getRPM();
  }
  Serial.print(mode == 2? angle : RPM);
  Serial.println();
}

void Calculate_paramters(){
  // Read encoder B when ENCA rises
  int b = digitalRead(ENCB);
  int increment = (b > 0? 1:-1);
  motor->updateAngle(increment);
  motor->updateRPM(increment);
  // Compute velocity with method 2
  vcc =PID.compute(mode == 2? motor->getAngle() : motor->getRPM());
  motor->setMotor(vcc);
}