/*
 * This code uses timer1 16bit of microcontroller to blink the led at a desired 
 * time interval of 4 sec.
 * it uses 1024 prescaler value
 */

void setup() {
  DDRB |= (1<<DDB5);
  SREG |= (1<<7); //enable GIE bit
  TIMSK1 |= (1<<TOIE1); //enabling timer overflow interrupt enable bit
  TCCR1B = (TCCR1B | (1<<CS12) | (1<<CS10)) & (~(1<<CS11)) & (~(1<<WGM13)) & (~(1<<WGM12)); //setting 1024 prescale & Setting WGM13:12 to 0 for normal mode
  TCCR1A &= (~(1<<WGM11)) & (~(1<<WGM10)); //setting to normal mode continues.
  TCNT1 = 3035;
  
  Serial.begin(9600);
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
 
}

ISR(TIMER1_OVF_vect)
{
 PORTB ^= (1<<PB5);
 Serial.print("isr time:  ");
 Serial.println(millis());
 TCNT1 = 3035; 
}
