/******************************** 

  Vapour Meat (2018)
  'A helmet to inhale meat clouds.'
  Artwork created by Devon Ward and Oron Catts.
  First exhibited at Science Gallery Dublin (2018).
  Arduino sketch by Devon Ward

  Code to controll ultrasonic sensor and ultrasonic vapouriser.
  When sensor detects the presence of someone in front of the 
  installation, this Arduino will turn on a peristaltic pump and 
  a ultrasonic vapouriser for 10 seconds.
  Code by Devon Ward. This sketch includes previous sketches
  for ultrasonic sensor. 

  
  Code used: 
  Arduino's Project Hub: Ultrasonic sensors:
  https://create.arduino.cc/projecthub/MisterBotBreak/how-to-use-an-ultrasonic-sensor-181cee

 */


#define TRIGGER_PIN   12
#define ECHO_PIN      11

int smokePin = 6;         // pin to control vapouriser
int pumpPin = 5;          // pin to control peristaltic pump
int ledPin = 13;          // pin to control led
long duration;            // variable to store time to receive ultrasound
int distance;             // variable to store distance of object
int triggerDistance = 80; // distance threshold to turn system on
int delayTime = 10000;    // 


unsigned long previousMillis = 0;
const long interval = 100;

void setup() {
  pinMode(smokePin, OUTPUT);
   pinMode(pumpPin, OUTPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();
  // Clears the TRIGGER_PIN
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);

  //Sets the TRIGGER_PIN on HIGH state for 10 micro seconds
  digitalWrite( TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite( TRIGGER_PIN, LOW);

  // Reads the ECHO_PIN, returns the sound wave travel time in microseconds
  duration = pulseIn(ECHO_PIN, HIGH);

  // Calculates cm based on duration of ultrasound from trigger to receiver
  distance = duration*0.034/2;
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    Serial.print("distance: ");
    Serial.print(distance);
    Serial.print("cm......");
    
    if (distance <= triggerDistance) {
      Serial.println(" ");
      Serial.print("Vapourise!!!");
      Serial.println(" "); 
      analogWrite(smokePin, 255); 
      analogWrite(pumpPin, 255); 
      digitalWrite(ledPin, HIGH);
      delay(delayTime); 
    } else {
      Serial.println("NO MEAT...");
      analogWrite(smokePin, 0);
      analogWrite(pumpPin, 255); 
      digitalWrite(ledPin, LOW); 
    }
    
  }
  // prints the distance in the Serial Monitor  
  

}
