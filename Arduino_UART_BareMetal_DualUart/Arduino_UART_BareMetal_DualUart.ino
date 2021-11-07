#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>

#define F_CPU 16000000

void printStringU0(const char *string);
void printStringU1(const char *string);
void UART_SentU0(uint16_t data);
void UART_SentU1(uint16_t data);
void printDecimel(uint32_t val);
char UART_charRecieved();
void UART_strRecieved(char *string);

int main(void)
{

    char recvdata[100];
    UBRR0 = 103;
    UCSR0B = (1<<TXEN0)|(1<<RXEN0)|(1<<RXCIE0); //00001000, 00010000

    UBRR1 = 103;
    UCSR1B = (1<<TXEN1)|(1<<RXEN1)|(1<<RXCIE1); //00001000, 00010000

    //while((UCSR0A & (1<<UDRE0))==0); //00100000

    printStringU0("Hello World \nFirst Uart Driver Code\n");
    //printDecimel(97);
    //UART_Sent(10);

    _delay_ms(1000);

//    UART_strRecieved(recvdata);
//    printString("Received data string : ");
//    printString(recvdata);
    while(1)
    {
      UART_strRecieved(recvdata);
      printStringU0("\nReceived data string : ");
      printStringU0(recvdata);
    }
}

void printStringU0(const char *string)
{
  while (*string)
  {
    UART_SentU0(*string++);
  }
}

void UART_SentU0(uint16_t data)
{
  while((UCSR0A & (1<<UDRE0))==0); //00100000
  UDR0 = data;
  
}

void printStringU1(const char *string)
{
  while (*string)
  {
    UART_SentU1(*string++);
  }
}

void UART_SentU1(uint16_t data)
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
    UART_SentU0(val_buf[val_index]);
  }
}


char UART_charRecieved()
{
  while(!(UCSR1A & (1<<RXC1)));  // 1000000
  return UDR1;
}

void UART_strRecieved(char *string)
{
  int i=0;
  char val;
  do
  {

    val = UART_charRecieved();
    if(val!='\n')
    {
      string[i]=val;
      i++;
    }    else
    {
      string[i]='\0';
      break;
    }

  }
  while( !(UCSR1A & (1<<RXC1)));
}
