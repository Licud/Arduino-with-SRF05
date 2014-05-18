int echoPin = 2;                                   // SRF05 echo pin (digital 2)
int initPin = 3;                                   // SRF05 trigger pin (digital 3)
int speakerPin = 13;                               // Speaker pin
unsigned long pulseTime = 0;                       
unsigned int pulseT;

void setup() {
  Serial.begin(9600);                              //Start serial monitor (debug)
  pinMode(initPin, OUTPUT);               
  pinMode(echoPin, INPUT);
  pinMode(speakerPin, OUTPUT);  
}

void playTone(int pitchTime){
  long t1 = millis() + 500;
  while(millis() < t1){
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(pitchTime);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(pitchTime);
  } 
  delay(pitchTime / 2);                                 // Delay time that playTone beeps
}
  
void loop() { 
  digitalWrite(initPin, HIGH);                        // Send 10 microsecond pulse 
  delayMicroseconds(10);                              // Wait 10 microseconds before turning off 
  digitalWrite(initPin, LOW);                         // Stop sending the pulse 
  delayMicroseconds(10);
  
  pulseTime = pulseIn(echoPin, HIGH);                 // Length of time echoPin is high 
  pulseT = pulseTime / 58;                            // Get centimetre equivalent of pulsetime

  if(pulseT <= 30){
    playTone(pulseTime /2);                           // Call playTone function, give pulseTime * 30
    Serial.println(pulseTime);
  }
  else{
    digitalWrite(speakerPin, LOW);
    Serial.println("Nothing in range");
  }
}
