int trigPin = 9;    // Trigger
int echoPin = 8;    // Echo
int LED = 13;  //LED pin to use (13 usually is onboard).
long duration, cm, inches;
long lastLEDStart = 0;
bool lastLEDState = false;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}


void checkLED(int micro) {
  long start = millis();
  while(millis() - start < micro) {
    long m = millis();
    if(m - lastLEDStart >= cm*5){
      if(lastLEDState && cm < 100) {
        digitalWrite(LED, HIGH);
      } else if(!lastLEDState || cm >=100) {
        digitalWrite(LED, LOW);
      }
      lastLEDState = !lastLEDState;
      lastLEDStart = m;
    }
    delayMicroseconds(1);
  }
}

void loop() {
  digitalWrite(trigPin, LOW);
  checkLED(5);
  digitalWrite(trigPin, HIGH);
  checkLED(10);
  digitalWrite(trigPin, LOW);

  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  inches = (duration/2) / 74;   // Divide by 74 or multiply by 0.0135
  
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  checkLED(250);
}
