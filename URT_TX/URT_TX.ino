

void setup() {
  starting();// put your setup code here, to run once:

}


void loop() {
  data('S');
  data('a');
  data('s');
  data('\n');
  delay(1000);
    
  
}
void data(uint8_t dbyte){
  while((UCSR0A & (1<<UDRE0)) == 0){};
  UDR0 = dbyte;
}

void starting(){
  UCSR0A |= (1<<U2X0);
  UBRR0 = 207;
  UCSR0C = (0<<UMSEL00)|(0<<UPM00)|(0<<USBS0);
  UCSR0C = (3<<UCSZ00);
  UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
  
}
