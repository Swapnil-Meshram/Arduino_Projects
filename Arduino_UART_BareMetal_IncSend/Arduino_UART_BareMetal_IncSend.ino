#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>

#define F_CPU 16000000

void printString(const char *string);
void printDecimel(uint32_t val);
void UART_Sent(uint16_t data);

int main (void)
{
  int i = 0;
  UBRR1 = 103;
  UCSR1B = (1<<TXEN1)|(1<<RXEN1)|(1<<RXCIE1); //00001000, 00010000

  
    while(1)
    {
      printDecimel(i);
      printString("\n\r");
      i++;
      _delay_ms(1000);
      //printString(recvdata);

    }
}

void printString(const char *string)
{
  while (*string)
  {
    UART_Sent(*string++);
  }
}

void UART_Sent(uint16_t data)
{
  while((UCSR1A & (1<<UDRE1))==0); //00100000
  UDR1 = data;
  
}

void printDecimel(uint32_t val)
{
  unsigned char val_buf[5];
  int8_t val_index;
  for(val_index=0;val_index<5;++val_index) {
    val_buf[val_index] = (val % 10) + '0';
    val /= 10;
  }
  for(val_index=4;val_index>0;--val_index) {
    if (val_buf[val_index] != '0') break;
  }
  for(;val_index>=0;--val_index) {
    UART_Sent(val_buf[val_index]);
  }
}
