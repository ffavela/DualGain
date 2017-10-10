#define Pin13LED         13
int x = 0;    // variable
byte state = HIGH;

String myString="";
void mySerialFunct(void);

void setup() {
  Serial.begin(9600);      // open the serial port at 9600 bps:
  pinMode(Pin13LED, OUTPUT);
}

void loop() {
  if (Serial.available() > 0)
    {
        myString = Serial.readStringUntil('$');
        /* int corner = Serial.readStringUntil('\n').toInt(); */

        // Do something awesome!
        myString+=" yeah! ";
        myString+='$';
        Serial.print(myString);
    }
}
