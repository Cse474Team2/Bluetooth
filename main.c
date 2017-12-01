#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"

void uartInit();
void uartSendByte(uint8_t value);

void main() {
  uartInit();
  
  uartSendByte('$');
  uartSendByte('$');
  uartSendByte('$');
  
  while (true) {
    // do nothing
     uartSendByte('$');
  }
}

void uartInit() {
  SYSCTL_RCGCUART_R |= 1;
  SYSCTL_RCGCGPIO_R |= 0x05;
  
  GPIO_PORTC_AFSEL_R |= (1 << 4) | (1 << 5);
  GPIO_PORTA_AFSEL_R |= (1 << 1) | (1 << 0);
  // TODO: check this!
  GPIO_PORTC_PCTL_R |= 0x220000;
  GPIO_PORTA_PCTL_R |= 0x11;
  
  GPIO_PORTC_DEN_R |= (1 << 4) | (1 << 5);
  GPIO_PORTC_DEN_R |= (1 << 0) | (1 << 1);
   
  // Disable UART
  UART1_CTL_R &= ~0x01;
  UART0_CTL_R &= ~0x01;
  
  // BAUD RATE CALC
  uint32_t megaHertz = 16;
  float divider = (megaHertz * 1000000) / (float)(16 * 9600);
  uint32_t whole = (uint32_t)divider;
  uint32_t fraction = (uint32_t)((divider - whole) * 64 + 0.5);
  
  UART1_IBRD_R = whole;
  UART1_FBRD_R = fraction;
  
  UART1_LCRH_R = (0x3 << 5);
  
  UART0_IBRD_R = 104;
  UART0_FBRD_R = 11;
  
  UART0_LCRH_R = (0x3 << 5);
  
  UART1_CTL_R |= 0x01;
  UART0_CTL_R |= 0x01;
}

void uartSendByte(uint8_t value) {
  while (UART0_FR_R & 0x02) {}
  
  UART0_DR_R = value;
}
  