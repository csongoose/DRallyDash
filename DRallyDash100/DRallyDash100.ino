// The license applies for this code as well. See license.md for details.

#define lDisable1 NaN     //unused
#define rev1 14           //pin for RPM led 1
#define rev2 15           //pin for RPM led 2
#define rev3 16           //pin for RPM led 3
#define rev4 17           //pin for RPM led 4

#define a1 13             //Digit 1
#define b1 12
#define c1 11
#define d1 10

#define a2 9              //Digit 2
#define b2 8
#define c2 7
#define d2 6

#define a3 5              //Digit 3
#define b3 4
#define c3 3
#define d3 2
#define Srpin1 1          //unused - reserved
#define Srpin0 0          //unused - reserved
int dig1;
int dig2;
int dig3;

String msg;
String def;

void ledWrite(int ledValue, int led1, int led2, int led3, int led4) {

  if (ledValue == 0){
    //digitalWrite(lDisable1, HIGH);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
  } else if (ledValue == 1) {
    //digitalWrite(lDisable1, HIGH);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
  } else if (ledValue == 2) {
    //digitalWrite(lDisable1, HIGH);
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
  } else if (ledValue == 3) {
    //digitalWrite(lDisable1, HIGH);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
  } else if (ledValue == 4) {
    //digitalWrite(lDisable1, HIGH);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
  } else if (ledValue == 5) {
    //digitalWrite(lDisable1, HIGH);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
  } else if (ledValue == 6) {
    //digitalWrite(lDisable1, HIGH);
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
  } else if (ledValue == 7) {
    //digitalWrite(lDisable1, HIGH);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
  } else if (ledValue == 8) {
    //digitalWrite(lDisable1, HIGH);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, HIGH);
  } else if (ledValue == 9) {
    //digitalWrite(lDisable1, HIGH);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, HIGH);
  }

}

void setup() {
  dig1 = 0;
  dig2 = 0;
  dig3 = 0;
  //pinMode(lDisable1, OUTPUT);
  pinMode(a1, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(c1, OUTPUT);
  pinMode(d1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(c2, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(a3, OUTPUT);
  pinMode(b3, OUTPUT);
  pinMode(c3, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(rev1, OUTPUT);
  pinMode(rev2, OUTPUT);
  pinMode(rev3, OUTPUT);
  pinMode(rev4, OUTPUT);
  // Start of boot sequence. Test of LEDs and allowing time for the serial connection to estabilish.
  Serial.begin(9600);
  // Following lines are for testing purposes (can be deactivated if needed)
  digitalWrite(rev1, HIGH);
  ledWrite(1, a1, b1, c1, d1);
  ledWrite(1, a2, b2, c2, d2);
  ledWrite(1, a3, b3, c3, d3);
  delay(100);
  digitalWrite(rev2, HIGH);
  ledWrite(2, a1, b1, c1, d1);
  ledWrite(2, a2, b2, c2, d2);
  ledWrite(2, a3, b3, c3, d3);
  delay(100);
  digitalWrite(rev3, HIGH);
  ledWrite(4, a1, b1, c1, d1);
  ledWrite(4, a2, b2, c2, d2);
  ledWrite(4, a3, b3, c3, d3);
  delay(100);
  digitalWrite(rev4, HIGH);
  ledWrite(8, a1, b1, c1, d1);
  ledWrite(8, a2, b2, c2, d2);
  ledWrite(8, a3, b3, c3, d3);
  delay(100);
  // Set the initial position of the dashboard
  digitalWrite(rev1, LOW);
  digitalWrite(rev2, LOW);
  digitalWrite(rev3, LOW);
  digitalWrite(rev4, LOW);
  ledWrite(0, a1, b1, c1, d1);
  ledWrite(0, a2, b2, c2, d2);
  ledWrite(0, a3, b3, c3, d3);
  }

void loop() {
  if (Serial.available() > 0) {
    msg = Serial.readStringUntil('\n');

    def = msg.charAt(0);
    if (def == "s") {                               // speed display
      dig1 = msg.substring(1, 2).toInt();
      dig2 = msg.substring(2, 3).toInt();
      dig3 = msg.substring(3, 4).toInt();
      ledWrite(dig1, a1, b1, c1, d1);
      ledWrite(dig2, a2, b2, c2, d2);
      ledWrite(dig3, a3, b3, c3, d3);
    } else if (def == "r") {                           // rpm LEDs
      if (msg.substring(1, 2).toInt() == 0) {
        digitalWrite(rev1, LOW);
        digitalWrite(rev2, LOW);
        digitalWrite(rev3, LOW);
        digitalWrite(rev4, LOW);
      } else if (msg.substring(1, 2).toInt() == 1) {
        digitalWrite(rev1, HIGH);
        digitalWrite(rev2, LOW);
        digitalWrite(rev3, LOW);
        digitalWrite(rev4, LOW);
      } else if (msg.substring(1, 2).toInt() == 2) {
        digitalWrite(rev1, HIGH);
        digitalWrite(rev2, HIGH);
        digitalWrite(rev3, LOW);
        digitalWrite(rev4, LOW);
      } else if (msg.substring(1, 2).toInt() == 3) {
        digitalWrite(rev1, HIGH);
        digitalWrite(rev2, HIGH);
        digitalWrite(rev3, HIGH);
        digitalWrite(rev4, LOW);
      } else if (msg.substring(1, 2).toInt() == 4) {
        digitalWrite(rev1, HIGH);
        digitalWrite(rev2, HIGH);
        digitalWrite(rev3, HIGH);
        digitalWrite(rev4, HIGH);
      }
    }
  }


}
