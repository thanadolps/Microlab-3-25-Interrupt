volatile int count = 0;

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
}

ISR(TIMER1_COMPA_vect)
{
  PORTB ^= (1 << 5);
  count = (count + 1) % 10;
  PORTB = (PORTB & 0b11110000) | count;
}

void loop()
{
  delay(1000);
}