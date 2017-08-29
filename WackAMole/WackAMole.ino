#define PIN_SPEAKER 2

  const int melody[] = {
    262, 196, 196, 220, 196, 0, 247, 262
  };

  const int durations[] = {
    4, 8, 8, 4, 4, 4, 4, 4
  };

void setup() {
  // put your setup code here, to run once:

  //Setup pins:
  pinMode(PIN_SPEAKER, OUTPUT);
  PlayVictorySound();

}

void loop() {
  // put your main code here, to run repeatedly:

}

void PlayVictorySound(){

for (int thisNote = 0; thisNote < 8; thisNote++){
  int noteDuration = 1000/durations[thisNote];
  tone(PIN_SPEAKER, melody[thisNote], noteDuration);
  delay(noteDuration * 1.30);
  noTone(PIN_SPEAKER);
}
}

