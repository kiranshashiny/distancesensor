// ---------------------------------------------------------------- //
// Arduino Ultrasoninc Sensor HC-SR04
// Re-writed by Arbi Abdul Jabbaar
// Using Arduino IDE 1.8.7
// Using HC-SR04 Module
// Tested on 17 September 2019
// ---------------------------------------------------------------- //

#define EntryEchoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define EntryTrigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04
#define EntryOutPin 11 // this sends the signal to turn LED On/OFF

#define echoPin 8 // Echo 
#define trigPin 9 // Trig of HC-SR04
#define ExitOutPin 12 // Power On and Off.
#define FiveVolts  13

int train_in_station=0;

// defines variables
long EntryDuration; // variable for the EntryDuration of sound wave travel
int EntryDistance; // variable for the EntryDistance measurement

long duration; // variable for the EntryDuration of sound wave travel
int  distance; // variable for the EntryDistance measurement

void setup() {
  pinMode(EntryTrigPin, OUTPUT); // Sets the EntryTrigPin as an OUTPUT
  pinMode(EntryEchoPin, INPUT); // Sets the EntryEchoPin as an INPUT

  pinMode(trigPin, OUTPUT); // Sets the EntryTrigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the EntryEchoPin as an INPUT

  pinMode(11, OUTPUT);           // Sets the EntryEchoPin as an INPUT
  pinMode(12, OUTPUT);
  
  pinMode(13, OUTPUT );
  digitalWrite(13, HIGH );
  
  Serial.begin(9600); // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
}
void loop() {
  // Entry code.
  
  // Clears the EntryTrigPin condition
  digitalWrite(EntryTrigPin, LOW);
  delayMicroseconds(2);
  // Sets the EntryTrigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(EntryTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(EntryTrigPin, LOW);
  // Reads the EntryEchoPin, returns the sound wave travel time in microseconds
  EntryDuration = pulseIn(EntryEchoPin, HIGH);
  // Calculating the EntryDistance
  EntryDistance = EntryDuration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the EntryDistance on the Serial Monitor
  Serial.print("EntryDistance: ");
  Serial.print(EntryDistance);
  //Serial.println(" cm");




  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print(" . Exit Distance: ");
  Serial.print(distance);
  //Serial.println(" cm");


  // Start checking for train arrival.
  if ( EntryDistance < 100) {

    Serial.println (" Train In Station, Turn lights on");
    digitalWrite ( EntryOutPin, LOW );
    train_in_station=1;
  } else {
    // Wait until train leaves station !
    // check if the exit echo Pin is ON or not
    // wait until exit Echo Pin is turned on
    // Waiting for exit distance signal
    
    if ( train_in_station) {
       Serial.print (" .   Waiting");
       if ( distance < 100) {
         // this means the train left station, then turn off light 
         digitalWrite ( EntryOutPin, HIGH);
         Serial.print ("  Train left, Turn Lights OFF");
         
         train_in_station=0;
       } 
    }
  }
  
  //. 1 Jul
  Serial.println();
}
