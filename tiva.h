#ifndef TIVA_H
#define TIVA_H

// GPIO registers
#define GPIO_PORTA_DATA       (*((volatile uint32_t *)0x400043FC))
#define GPIO_PORTA_DIR        (*((volatile uint32_t *)0x40004400))
#define GPIO_PORTA_DEN        (*((volatile uint32_t *)0x4000451C))

// GPIO registers
#define GPIO_PORTC_AFSEL      (*((volatile uint32_t *)0x40006420))
#define GPIO_PORTC_DEN        (*((volatile uint32_t *)0x4000651C))
#define GPIO_PORTC_PCTL       (*((volatile uint32_t *)0x4000652C))

// UART registers
#define UART1_DR              (*((volatile uint32_t *)0x4000D000))
#define UART1_FR              (*((volatile uint32_t *)0x4000D018))
#define UART1_IBRD            (*((volatile uint32_t *)0x4000D024))
#define UART1_FBRD            (*((volatile uint32_t *)0x4000D028))
#define UART1_LCRH            (*((volatile uint32_t *)0x4000D02C))
#define UART1_CTL             (*((volatile uint32_t *)0x4000D030))

// GPIO registers
#define GPIO_PORTF_DIR        (*((volatile uint32_t *)0x40025400))
#define GPIO_PORTF_DEN        (*((volatile uint32_t *)0x4002551C))

// Timer registers
#define TIMER1_CFG            (*((volatile uint32_t *)0x40031000))
#define TIMER1_TAMR           (*((volatile uint32_t *)0x40031004))
#define TIMER1_CTL            (*((volatile uint32_t *)0x4003100C))
#define TIMER1_RIS            (*((volatile uint32_t *)0x4003101C))
#define TIMER1_ICR            (*((volatile uint32_t *)0x40031024))
#define TIMER1_TAILR          (*((volatile uint32_t *)0x40031028))

// System Control registers
#define SYSCTL_RCGC2          (*((volatile uint32_t *)0x400FE108))
#define SYSCTL_RCGCTIMER      (*((volatile uint32_t *)0x400FE604))
#define SYSCTL_RCGCGPIO       (*((volatile uint32_t *)0x400FE608))
#define SYSCTL_RCGCUART       (*((volatile uint32_t *)0x400FE618))

#endif // TIVA_H
