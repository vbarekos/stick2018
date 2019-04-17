// Orion Stick 30-3-2019

 // Pins για τον αισθητήρα υπερήχων 1
 const int trigPin1 = 12;
 const int echoPin1 = 11;

  // Pins για τον αισθητήρα υπερήχων 2
 const int trigPin2 = 9;
 const int echoPin2 = 8;
 
 // μεταβλητές για απόσταση
 long duration, distance, FrontSensor,DownSensor;
 
 // Τα pins του Buzzer και LED
 const int buzPin1 = 3; // Δεξί ακουστικό για τον Αισθ Υπερήχων 1
 const int buzPin2 = 7; // Αριστερό ακουστικό για τον Αισθ Υπερήχων 2
 
 const int ledPin1 = 13; // Οπτική ένδειξη για τον Αισθ Υπερήχων 1
 const int ledPin2 = 2;  // Οπτική ένδειξη για τον Αισθ Υπερήχων 2

void setup() {
  // Στο setup μέρος τοποθετώ κώδικα Αρχικοποίησης, δλδ που εκτελείται μόνο μία φορά στην αρχή:
  Serial.begin(9600); // Βγάλε Σχόλιο αν χρησιμοποιείς serial communication. Αρχικοποίηση σειριακής @ 9600 baud

  // Αισθητήρας Υπερήχων
  pinMode(trigPin1, OUTPUT); // Ορισμός του trigPin ως ΕΞΟΔΟΣ
  pinMode(echoPin1, INPUT); // Ορισμός του echoPin ως ΕΙΣΟΔΟΣ

  pinMode(trigPin2, OUTPUT); // Ορισμός του trigPin ως ΕΞΟΔΟΣ
  pinMode(echoPin2, INPUT); // Ορισμός του echoPin ως ΕΙΣΟΔΟΣ
  }

void loop() {

  // εδώ μπαίνει ο κυρίως κώδικας ο οποίος εκτελείται συνεχώς επαναλαμβανόμενα:
 SonarSensor(trigPin1, echoPin1);
 FrontSensor = distance;
 SonarSensor(trigPin2, echoPin2);
 DownSensor = distance;
 
 // Εκτύπωση της απόστασης σε Σειριακή Επικοινωνία (Serial Monitor)
 Serial.print("FrontSensor: ");
 Serial.println(FrontSensor); 
 Serial.print("DownSensor: ");
 Serial.println(DownSensor); 
 Serial.println("---");
 delay(100);
 
 dist_control();

} // τέλος βρόγχου επανάληψης

void SonarSensor(int trigPin,int echoPin)
{
  // Δημιουργία του παλμού για αισθητήρα Υπερήχων
  // Καθάρισμα του trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Θέσε το trigPin σε HIGH για 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Διάβασμα του παλμού ανάκλασης, echoPin. Επιστρέφει το χρόνο πτήσης κύματος σε microseconds
  duration = pulseIn(echoPin, HIGH);
  // Υπολογισμός απόστασης μέχρι το εμπόδιο
  distance = (duration/2) / 29.1;
  }


void dist_control() {
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  noTone(buzPin1);
  noTone(buzPin2);

  if((FrontSensor < 50)&&(FrontSensor > 0)) {
    tone(buzPin1, 10, 1000); // παίξε ήχο στο buzzer
    digitalWrite(ledPin1, HIGH);
    delay(100); 
  }
  
  else if(DownSensor > 30) {
    tone(buzPin2, 10, 1000); // παίξε ήχο στο buzzer
    digitalWrite(ledPin2, HIGH);
    delay(100); 
  }

}


