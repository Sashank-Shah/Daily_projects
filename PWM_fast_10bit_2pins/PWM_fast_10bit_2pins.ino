/* This code is for amking the use of pwm generator principle
 * The PWM is set in PWM fast mode with 10bit
 * We are using channel A of output compare set of pins.
 * Here timer1 16bit is used.
 */

void setup() {
  // set the mode of the timer to pwm fast mode 10bit AND OC1B is set inverting type and OC1A is set non-inverting type 
  TCCR1A = (TCCR1A |((1<<COM1A1)|(1<<WGM11)|(1<<WGM10)|(1<<COM1B1)|(1<<COM1B0))) & (~(1<<COM1A0));
  TCCR1B = (TCCR1B|(1<<WGM12))&(~(1<<WGM13));
  //SETTING CLK/64 = 250KHz frequency
  TCCR1B = (TCCR1B|((1<<CS10)|(1<<CS11)))&(~(1<<CS12));
  //SETTING THE OC1B and oc1A pins as output
  DDRB |= (1<<DDB2)|(1<<DDB1);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(unsigned int i=0; i<1023; i++)
  {
    OCR1B = i;
    OCR1A = i;
    delay(20);
  }
  delay(1000);

}
