//ADAPTIVE LINE FOLLOWER BY vilas 
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

  Serial.begin(9600);
}

int s0 = analogRead(centerIR);
int s1 = analogRead(leftIR);
int s2 = analogRead(rightIR);

int speed = 170;
int turnspeed = 170;
int turndelta = 50;

int prev =0;

int current(){
  if (!s0 && !s1 && !s2) return 1;
  else return 0;
}
void loop() {
  s1 = digitalRead(leftIR);
  s2 = digitalRead(rightIR);
  s0 = digitalRead(centerIR);
    if (s1 && s0){
    forward(speed, speed);
    delay(80);
    if (prev == 0) forward(turnspeed, -turnspeed);
    else forward(turnspeed, 0);
    delay(150);
    prev = -1;
  } else if(s2 && s0){
    forward(speed, speed);
    delay(80);
    if (prev == 0) forward(-turnspeed, turnspeed);
    else forward(0, turnspeed);
    delay(150);
    prev = 1;
  } else if(s1){
    forward(speed + turndelta, 0);
    prev = -2;
  } else if(s2){
    forward(0, speed + turndelta);
    prev = 2;
  } else if(s0){
    forward(speed, speed);
    prev = 0;
  } else{
    if (prev == -2 || prev == -1){
        forward(turnspeed, -turnspeed);
      } else if (prev == 2 || prev ==1){
        forward(-turnspeed, turnspeed);
      }
  }
  Serial.println();
}