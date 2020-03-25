volatile int period = 1;

int calculateOCR(double frequency, long prescaler) {
  const long CLOCK_FREQ = 16000000;
  return (CLOCK_FREQ / (frequency * prescaler)) - 1.0;
}


void setup_timer1() {
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  
  OCR1A = calculateOCR(1, 1024);
  
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10); // 1024
  TIMSK1 |= (1 << OCIE1A);
}

void setup()
{ 
  pinMode(2, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  
  noInterrupts();
  setup_timer1();
  interrupts();
  
  attachInterrupt(digitalPinToInterrupt(2), onButtonRelease, RISING);
}


void onButtonRelease() {
  digitalWrite(13, HIGH);
  period = period >= 3 ? 1 : period + 1;
  OCR1A = calculateOCR(1.0/(double)(period), 1024);
}

ISR(TIMER1_COMPA_vect)
{
  PORTB ^= (1 << 5);
}

void loop()
{
  delay(1000);
}