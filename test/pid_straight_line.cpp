#include <Arduino.h>

// motor pins
#define in1 A1
#define in2 A2
#define in3 A3
#define in4 A4

#define ena 6
#define enb 5

// encoder pins
#define rightc1 3   //swapping right pins to get positive for forward direction on connection
#define rightc2 11
#define leftc1 2
#define leftc2 10

// ir pins
#define centerIR 4
#define leftIR 8
#define rightIR 7

//variables
volatile long countLeft = 0;
volatile long countRight = 0;

void forward(int rightSpeed, int leftSpeed){
  rightSpeed = constrain(rightSpeed, -255, 255);
  leftSpeed = constrain(leftSpeed, -255, 255);
  if (leftSpeed >= 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    leftSpeed = -leftSpeed;
  }
  if (rightSpeed >= 0) {
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  } else {
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    rightSpeed = -rightSpeed;
  }
  analogWrite(ena, leftSpeed);
  analogWrite(enb, rightSpeed);
}

void counterLeft(){
  if(digitalRead(leftc2)>0)  countLeft++;
  else countLeft--;
}

void counterRight(){
  if(digitalRead(rightc2)>0)  countRight--;
  else countRight++;
}

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  
  pinMode(rightc1, INPUT_PULLUP);
  pinMode(rightc2, INPUT_PULLUP);  
  pinMode(leftc1, INPUT_PULLUP);
  pinMode(leftc2, INPUT_PULLUP);
  
  pinMode(centerIR, INPUT);
  pinMode(leftIR, INPUT);
  pinMode(rightIR, INPUT);
  
  attachInterrupt(digitalPinToInterrupt(leftc1), counterLeft, RISING);
  attachInterrupt(digitalPinToInterrupt(rightc1), counterRight, RISING);

  Serial.begin(9600);
}

long Lcount, Rcount, prevLcount, prevRcount,finalL, finalR = 0;
double deltaL, deltaR = 0;

double kp = 1.5;
double ki = 0;
double kd = 0;

double error, previous_error = 0.0;
double integral = 0.0;
double derivative = 0.0;
double correction = 0.0;

double target = 200.0; // target counts per loop

volatile unsigned long timer = millis();
unsigned long previous_timer = timer;
double dt = 0;

void loop() {
  timer = millis();
  dt = (timer - previous_timer)*0.001; // in seconds
  previous_timer = timer;

  forward(target, target);
  prevLcount = Lcount;
  prevRcount = Rcount; // to get delta 
  noInterrupts(); // avoiding curroption of interrrupt variables
  Lcount = countLeft;
  Rcount = countRight;
  countLeft = 0;
  countRight = 0;
  interrupts();

  deltaL = Lcount - prevLcount;
  deltaR = Rcount - prevRcount; //calc error

  error = Lcount - Rcount;
  // if(error <=2){
  //   error = 0;
  // }
  integral += error * dt; 
  derivative = (error - previous_error) / dt; 
  previous_error = error;

  correction = kp * error + ki * integral + kd * derivative;

  finalL = target - correction;
  finalR = target + correction;

  forward(finalR, finalL);

  Serial.print("Correction: ");
  Serial.print(correction);
  Serial.print("  Left Count: ");
  Serial.print(Lcount);
  Serial.print("  Right Count: ");
  Serial.print(Rcount);
  Serial.print(" finalR: ");
  Serial.print(finalR);
  Serial.print(" finalL: ");
  Serial.print(finalL);
  Serial.print(" error: ");
  Serial.print(error);
  // Serial.print(" deltaR: ");
  // Serial.print(deltaR);
  // Serial.print(" deltaL: ");
  // Serial.print(deltaL);
  Serial.print(" integral: ");
  Serial.print(integral);
  Serial.print(" derivative: ");
  Serial.print(derivative);
  // Serial.print(" dt: ");
  // Serial.print(dt);
  // Serial.print(" target: ");
  // Serial.print(target);
  // Serial.print("");
  Serial.println();
  delay(70);
}
