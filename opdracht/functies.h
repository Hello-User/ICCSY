#include <avr/io.h>

void initUsart()
{
  UCSR0A = 0;
  UCSR0B = (1 << TXEN0) |(1<<RXEN0)| (1<<RXCIE0);;
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  //8bits
  UBRR0H=00;  UBRR0L=103;  //9600
}

void writeChar(char c)
{
  while(!(UCSR0A & (1<<UDRE0)));
  UDR0=c;
}


void writeString(char* s)
{
  while(*s)
  writeChar(*s++);
}

void writeInt(int16_t nr)
{
  char buffer[8];
  itoa(nr,buffer,10);
  writeString(buffer);
}

char readChar() {
  while(~UCSR0A & 1 << RXC0);
  return UDR0;
}

void writeHexReg(uint8_t nr)
{
  char buffer[8];
  utoa(nr,buffer,16);
  writeString(buffer);
}
