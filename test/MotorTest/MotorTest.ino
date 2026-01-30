void setup() {
  Serial.begin(115200); // Make sure your Serial Monitor matches this!
  
  // On Nano, we don't strictly need "while(!Serial)" because 
  // the board auto-resets when you open the monitor.
  
  pinMode(LED_BUILTIN, OUTPUT); 

  // --- FLASH LED TWICE ---
  for(int i=0; i<2; i++) {
    digitalWrite(LED_BUILTIN, HIGH); // On
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);  // Off
    delay(200);
  }

  Serial.println("--- STARTING NANO BENCHMARK ---");
  
  unsigned long startTime = millis();

  // The Heavy Math (Calculating Pi)
  // Note: This will be VERY slow on Nano compared to STM32
  float pi = 0;
  float sign = 1.0;
  
  for (long i = 0; i < 500000; i++) {
    pi += sign / (2.0 * i + 1.0);
    sign *= -1.0;
  }
  pi *= 4.0;

  unsigned long endTime = millis();
  
  Serial.print("Calculated Pi: ");
  Serial.println(pi, 6);
  Serial.print("Time Taken: ");
  Serial.print(endTime - startTime);
  Serial.println(" ms");
  
  Serial.println("-----------------------------------");
}

void loop() {
  // Blink slowly to show it's done
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}