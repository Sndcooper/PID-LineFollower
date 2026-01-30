#define ENCA 2 // YELLOW
#define ENCB 10 // WHITE

volatile int posi = 0; // specify posi as volatile: https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/volatile/

void setup() {
  Serial.begin(9600);
  pinMode(ENCA,INPUT);
  pinMode(ENCB,INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA),readEncoder,RISING);
}

void loop() {
  // Read the position in an atomic block to avoid a potential
  // misread if the interrupt coincides with this code running
  // see: https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/volatile/
  int pos = 0; 
  noInterrupts();
    pos = posi;
  interrupts();

  Serial.println(pos);
}

void readEncoder(){
  int b = digitalRead(ENCB);
  if(b > 0){
    posi++;
  }
  else{
    posi--;
  }
}




// #define la 2
// #define lb 3
// #define ra 10
// #define rb 11

// long lcount, rcount = 0;

// void lcounter(){
//   if (digitalRead(lb)) lcount++;
//   else lcount--;
// }
// void rcounter(){
//   if(digitalRead(rb)) rcount++;
//   else lcount--;
// }

// void setup() {
//   // put your setup code here, to run once:
//   pinMode(la, INPUT);
//   pinMode(lb, INPUT);
//   pinMode(ra, INPUT);
//   pinMode(rb, INPUT);

//   attachInterrupt(digitalPinToInterrupt(la), lcounter, RISING);
//   attachInterrupt(digitalPinToInterrupt(ra), rcounter, RISING);
//   Serial.begin(9600);

// }

// void loop() {
//   // put your main code here, to run repeatedly:
//   noInterrupts();
//   int LCount = lcount;
//   int RCount = rcount;
//   interrupts();
//   Serial.print(LCount);
//   Serial.print(" ");
//   Serial.println(RCount);
// }
