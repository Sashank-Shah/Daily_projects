void data_lcd(unsigned char data) {
  PORTD = data;
  PORTB |= (1<<PB0);
  PORTB &= (~(1<<PB1));
  PORTB |= (1<<PB2);
  delay(10);
  PORTB &= (~(1<<PB2));
}
void cmd_lcd(unsigned char cmd) {
  PORTD = cmd;
  PORTB &= (~(1<<PB0));
  PORTB &= (~(1<<PB1));
  PORTB |= (1<<PB2);
  delay(10);
  PORTB &= (~(1<<PB2));
}

void letter_lcd(const unsigned char *str,unsigned char len) {
  char i = 0;
  for(i=0;i<=len;i++){
    data_lcd(str[i]); 
  }
}
void lcd_initialize() {
  cmd_lcd(0x38);
  cmd_lcd(0x06);
  cmd_lcd(0x0C);
  cmd_lcd(0x01);
  
}
void setup() {
  DDRD = 0xFF;// put your setup code here, to run once:
  DDRB |= (1<<DDB0)|(1<<DDB1)|(1<<DDB2);
  lcd_initialize();
}

void loop() {
  cmd_lcd(0x80); // put your main code here, to run repeatedly:
  letter_lcd("Bit manipulation",16);
  cmd_lcd(0xC0);
  letter_lcd("By Sashank",10);
 
}
