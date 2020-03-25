volatile int period = 1;

void setup()
{
  pinMode(2, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(2), onButtonRelease, FALLING);
}



void onButtonRelease() {
  period = period >= 3 ? 1 : period + 1;
}

void loop()
{
  PORTB ^= (1 << 5);
  delay(1000 * period);
}