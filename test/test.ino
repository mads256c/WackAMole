#include <LiquidCrystal.h>

#define TIME 30 // How much time the user gets.

volatile int current;
volatile int score = 0;
volatile int timer = 0;
volatile bool gameStarted = false;
volatile bool doFlash = false;

const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;

volatile LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void resetLEDs()
{
  for (int i = 2; i < 8; i++)
  {
    digitalWrite(i, false);
  }
}

void initPins()
{
  // Set pinMode and do ledcheck
  for (int i = 2; i < 8; i++)
  {
    pinMode(i, OUTPUT);
    digitalWrite(i, true);
    delay(100);
    digitalWrite(i, false);
  }
}

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.print("Starting program");
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  OCR1A = 62500;            // compare match register 16MHz/256/1Hz
  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (1 << CS12);    // 256 prescaler
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt

  randomSeed(analogRead(0));
  current = random(6);

  interrupts();
  initPins();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Press any button");
  lcd.setCursor(0, 1);
  lcd.print("to start...");
}
void loop() {
  // put your main code here, to run repeatedly:
  if (doFlash == true)
  {
    for (int x = 0; x < 5; x++)
    {
      for (int i = 0; i < 7; i++)
      {
        digitalWrite(i + 2, HIGH);
      }
      delay(1000);
      for (int i = 0; i < 7; i++)
      {
        digitalWrite(i + 2, LOW);
      }
      delay(1000);
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Press any button");
    lcd.setCursor(0, 1);
    lcd.print("to start...");
    doFlash = false;
  }
  else {
    if (analogRead(current) > 256 && gameStarted == true)
    {
      digitalWrite(current + 2, false);
      current = random(6);
      digitalWrite(current + 2, true);
      score++;
      lcd.setCursor(0, 0);
      lcd.print("Score: ");
      lcd.print(score);
      delay(250);
    }
    else if (gameStarted == false)
    {
      resetLEDs();
      for (int i = 0; i < 7; i++)
      {
        if (analogRead(i) > 512)
        {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Score: ");
          lcd.print(score);
          gameStarted = true;
          digitalWrite(current + 2, true);
          delay(250);
          break;
        }
      }
    }
  }
}

ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{
  Interrupt();
}

void Interrupt()
{
  if (gameStarted == true)
  {
    timer++;
    lcd.setCursor(0, 1);
    lcd.print("Time:    ");
    lcd.setCursor(6, 1);
    lcd.print(TIME - timer);
    if (timer > TIME)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("GAME OVER!");
      lcd.setCursor(0, 1);
      lcd.print("Score: ");
      lcd.print(score);
      score = 0;
      timer = 0;
      current = 0;
      resetLEDs();
      gameStarted = false;
      doFlash = true;
    }
  }
}

