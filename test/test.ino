void setup() {
  // put your setup code here, to run once:
randomSeed(analogRead(0));


for (int i = 2; i < 8; i++)
{
  pinMode(i, OUTPUT);
  digitalWrite(i, true);
  delay(100);
  digitalWrite(i, false);
}

  for (int i = 8; i < 14; i++)
  {
  pinMode(i, INPUT);
  }
}
void loop() {
  // put your main code here, to run repeatedly:
for (int i = 0; i < 7; i++)
{
  digitalWrite(i + 2, digitalRead(i + 8));
}


}
