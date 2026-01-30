#include <Arduino.h>
#include <PID_v1.h>

#define in1 A1
#define in2 A2
#define in3 A3
#define in4 A4

#define ena 6
#define enb 5

// encoder pins
#define rightc1 3  //swapping right pins to get positive for forward direction on connection
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

unsigned long loop_timer = millis();

double kp = 1.5;
double ki = 0.001;
double kd = 0.001;  //.00002

double Setpoint = 0, Input, Output;

long Lcount = 0;
long Rcount = 0;

uint8_t speedBias = 200;
PID myPID(&Input, &Output, &Setpoint, kp, ki, kd, DIRECT);

void forward(int rightSpeed, int leftSpeed) {
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

void counterLeft() {
  if (digitalRead(leftc2) > 0) countLeft++;
  else countLeft--;
}

void counterRight() {
  if (digitalRead(rightc2) > 0) countRight--;
  else countRight++;
}

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);

  pinMode(rightc1, INPUT);
  pinMode(rightc2, INPUT);
  pinMode(leftc1, INPUT);
  pinMode(leftc2, INPUT);

  pinMode(centerIR, INPUT);
  pinMode(leftIR, INPUT);
  pinMode(rightIR, INPUT);

  attachInterrupt(digitalPinToInterrupt(leftc1), counterLeft, RISING);
  attachInterrupt(digitalPinToInterrupt(rightc1), counterRight, RISING);

  Serial.begin(9600);

  loop_timer = millis();

  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(-50, 50);

  forward(0, 0);
}

void loop() {
  if (millis() - loop_timer >= 100) {
    noInterrupts();  // avoiding curroption of interrrupt variables
    Lcount = countLeft;
    Rcount = countRight;
    countLeft = 0;
    countRight = 0;
    interrupts();

    Input = Rcount - Lcount;

    myPID.Compute();

    forward(speedBias - Output, speedBias + Output);

    // Serial.print("  Left Count: ");
    Serial.print((float)Lcount);
    Serial.print(" ");
    // Serial.print("  Right Count: ");
    Serial.print((float)Rcount);
    // Serial.print("  Correction: ");
    // Serial.print(correction);
    // Serial.print(" finalR: ");
    // Serial.print(finalR);
    // Serial.print(" finalL: ");
    // Serial.print(finalL);
    // Serial.print(" error: ");
    // Serial.print(error);
    // Serial.print(" deltaR: ");
    // Serial.print(deltaR);
    // Serial.print(" deltaL: ");
    // Serial.print(deltaL);
    // Serial.print(" integral: ");
    // Serial.print(integral);
    // Serial.print(" derivative: ");
    // Serial.print(derivative);
    // Serial.print(" dt: ");
    // Serial.print(dt);
    // Serial.print(" target: ");
    // Serial.print(target);
    // Serial.print("");
    Serial.println();
  }
}