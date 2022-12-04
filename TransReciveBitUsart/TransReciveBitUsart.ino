
unsigned char USART_Laxman(){
  unsigned char Data;
  while(!(UCSR0A&(1<<RXC0))) {
    
  }
  Data = UDR0;
  return Data;
}


void setup() {
  UCSR0A |= (1<<U2X0);    //HIGH SPEED MODE
  UBRR0 = 207;            //BAUD RATE CALCULATED FROM HIGH SPEED MODE
  UCSR0B |= (1<<RXEN0)|(1<<TXEN0);  //RX AND TX ENABLE
  UCSR0C &= (~(1<<UMSEL01))&(~(1<<UMSEL00))&(~(1<<UPM01))&(~(1<<UPM00)); //ASYNCHRONOUS MODE
  UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
  UCSR0B &= (~(1<<UCSZ02));
  UCSR0C &= (~(1<<USBS0)); //1 STOP BIT
  DDRB |= (1<<DDB5);
  
  
}

char message;
void loop() {
  message = USART_Laxman();
  
  
}
