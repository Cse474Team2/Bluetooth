#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <stdbool.h>

// Initialises bluetooth communications
void bluetoothInit();

// Sends a string via bluetooth
void bluetoothSendString(char* str, uint32_t size);

// Returns true if there is data available
bool bluetoothCharAvailable();

// Get next character from bluetooth connection
char bluetoothGetChar();

#endif // BLUETOOTH_H
