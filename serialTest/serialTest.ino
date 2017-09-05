// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
}
bool flash = false;
// the loop routine runs over and over again forever:
void loop() {

  if (flash == true)
  {
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);               // wait for a second
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);               // wait for a second
  }

  if (Serial.available() > 0)
  {
    flash = true;
  }
}
