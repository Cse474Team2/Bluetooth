#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "tiva.h"
#include "bluetooth.h"

static void gpioInit();
static void uart1Init();

static void uart1SetClock(uint8_t megaHertz, uint32_t baudRate);
static void uart1SendByte(uint8_t byte);

// Initialises bluetooth communications
void bluetoothInit() {
  gpioInit();
  uart1Init();
}

// Sends a string via bluetooth
void bluetoothSendString(char* str, uint32_t size) {
  // Size is used to avoid any mistakes with forgetting to end the string.
  for (int i = 0; i < size; i++) {
    uart1SendByte(str[i]);
  }
}

// Returns true if there is data available
bool bluetoothCharAvailable() {
  return !(UART1_FR & 0x10);
}

// Get next character from bluetooth connection
char bluetoothGetChar() {
  while (UART1_FR & 0x10) {}
  return UART1_DR;
}

// Activates port c and a
static void gpioInit() {
  SYSCTL_RCGC2 |= 0x04;
}

// Initialise the UART
static void uart1Init() {
  // Turn on Uart 1
  SYSCTL_RCGCUART |= 0x02;

  // Setup port C
  // Select alternate function for PC4 and PC5
  // DO NOT TOUCH THIS. YOU MAY KILL THE BOARD
  GPIO_PORTC_AFSEL |= 0x30;
  // DO NOT TOUCH THIS. YOU MAY KILL THE BOARD
  GPIO_PORTC_PCTL &= ~0xFF0000;
  GPIO_PORTC_PCTL |= 0x220000;
  // Set PC4 and PC5 as digital
  // DO NOT TOUCH THIS. YOU MAY KILL THE BOARD
  GPIO_PORTC_DEN |= 0x30;

  // Set Uart clock
  uart1SetClock(16, 115200);
}

// Set the divider for UART to be at the given baud rate
static void uart1SetClock(uint8_t megaHertz, uint32_t baudRate) {
  // Disable UART while configuring
  UART1_CTL &= ~0x01;

  // Calculate the divisor needed for the baud rate
  float divider = (megaHertz * 1000000) / (float)(16 * baudRate);
  uint32_t whole = (uint32_t)divider;
  uint32_t fraction = (uint32_t)((divider - whole) * 64 + 0.5);

  // Set the integer and fractional part of the divisor
  UART1_IBRD = whole;
  UART1_FBRD = fraction;

  // Set the packets to be 8 data bits, no parity, and 1 stop bit
  UART1_LCRH = (0x3 << 5);

  // Enable UART after config
  UART1_CTL |= 0x01;
}

// Send a byte via UART
static void uart1SendByte(uint8_t byte) {
  // Wait for UART1 TX FIFO to be ready
  while (UART1_FR & 0x20) {}
  // Send byte
  UART1_DR = byte;
}
