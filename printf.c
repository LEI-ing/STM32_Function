#include "stm32f10x.h"
#include "stdio.h"
#include "UART.h"

#define USART_printf USART1

/**
 * @brief printf重定向，需要使用的串口在printf.c的宏定义中，需要自行完成串口初始化
 * 
 * @param ch 
 * @param f 
 * @return int 
 */
int fputc(int ch, FILE *f)
{
    while ((USART_printf->SR & 0x40) == 0);
    USART_printf->DR = (uint8_t)ch;

    return ch;
}
