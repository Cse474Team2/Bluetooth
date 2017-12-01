#include <stdbool.h>
#include <stdint.h>
#include "tm4c123gh6pm.h"

void initGpio();
void initUart();

void setUARTClock(uint8_t megaHertz, uint32_t baudRate);
void sendByte(uint8_t byte);

int main() {
  initGpio();
  initUart();

  // Enter config mode
  sendByte('$');
  sendByte('$');
  sendByte('$');
  
  char str[] = "SN,test123";
  
  // Print string
  //for (int i = 0; i < sizeof(str); i++) {
    //sendByte(str[i]);
  //}
  
  // Exit config
  sendByte('-');
  sendByte('-');
  sendByte('-');
  
  while (true) {
    // Loop forever
  }
}

// Activates port c and a
void initGpio() {
  SYSCTL_RCGC2_R |= 0x04;
  // Uart 0 for debug 
  SYSCTL_RCGC2_R |= 0x01;
}

// Initialise the UART
void initUart() {  
  // Turn on Uart 1
  SYSCTL_RCGCUART_R |= 0x02;
  // Uart 0 for debug
  SYSCTL_RCGCUART_R |= 0x01;

  // Uart 0 for debug
  // Setup port A
  // Select alternate function for PA1 and PA0
  //GPIO_PORTA_AFSEL_R |= 0x3;
  //GPIO_PORTA_PCTL_R = 0x11;
  // Set PA1 and PA0 as digital
  //GPIO_PORTA_DEN_R |= 0x03;

  // Setup port C
  // Select alternate function for PC4 and PC5
  GPIO_PORTC_AFSEL_R |= 0x30;
  // DO NOT TOUCH THIS. YOU MAY KILL THE BOARD
  GPIO_PORTC_PCTL_R &= ~0xFF0000;
  GPIO_PORTC_PCTL_R |= 0x220000;
  // Set PC4 and PC5 as digital
  GPIO_PORTC_DEN_R |= 0x30;

  setUARTClock(16, 115200);
  // Uart 0 for debug
  //setUARTClock(16, 9600);
}

// Set the divider for UART to be at the given baud rate
void setUARTClock(uint8_t megaHertz, uint32_t baudRate) {
  // Disable UART while configuring
  UART1_CTL_R &= ~0x01;

  // Calculate the divisor needed for the baud rate
  float divider = (megaHertz * 1000000) / (float)(16 * baudRate);
  uint32_t whole = (uint32_t)divider;
  uint32_t fraction = (uint32_t)((divider - whole) * 64 + 0.5);

  // Set the integer and fractional part of the divisor
  UART1_IBRD_R = whole;
  UART1_FBRD_R = fraction;

  // Set the packets to be 8 data bits, no parity, and 1 stop bit
  UART1_LCRH_R = (0x3 << 5);

  // Enable UART after config
  UART1_CTL_R |= 0x01;
}

// Send a byte via UART
void sendByte(uint8_t byte) {
  // Wait for UART1 TX FIFO to be ready
  while (UART1_FR_R & 0x20) {}
  // Send byte
  UART1_DR_R = byte;
}
