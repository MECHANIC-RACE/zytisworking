#ifndef UART_RECEIVE
#define UART_RECEIVE

#include "stm32f1xx.h"
#include "usart.h"


extern uint8_t ReceivebufferG[7];
extern uint8_t ReceivebufferR[19];
void U_Transmit(uint8_t num);

#endif // !UART_RECEIVE