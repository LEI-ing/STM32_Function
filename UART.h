#ifndef _UART_H
#define _UART_H

typedef struct
{
    GPIO_TypeDef *GPIOx;
    uint16_t GPIO_Pin_TX;
    uint16_t GPIO_Pin_RX;
} USART_gpioInitTypeDef;

void MyUSART_Init(USART_TypeDef *USARTx, USART_gpioInitTypeDef *USART_gpioStructure, uint32_t BaudRate, FunctionalState USART_ITstate);

#endif
