#include "stm32f10x.h"
#include "GPIO.h"

typedef struct
{
    GPIO_TypeDef *GPIOx;
    uint16_t GPIO_Pin_TX;
    uint16_t GPIO_Pin_RX;
} USART_gpioInitTypeDef;

/**
 * @brief 自定义串口初始化函数
 *
 * @param USARTx values: USART1, USART2, USART3,
 * @param USART_gpioStructure 串口对应的GPIO初始化结构体
 * @param BaudRate 波特率
 * @param USART_ITstate 中断状态， values: ENABLE or DISABLE
 * @param PreemptionPriority 抢占优先级
 * @param SubPriority 从占优先级
 */
void MyUSART_Init(USART_TypeDef *USARTx, USART_gpioInitTypeDef *USART_gpioStructure, uint32_t BaudRate, FunctionalState USART_ITstate, uint8_t PreemptionPriority, uint8_t SubPriority)
{
    MyGPIO_Init(USART_gpioStructure->GPIOx, USART_gpioStructure->GPIO_Pin_TX, GPIO_Mode_AF_PP);
    MyGPIO_Init(USART_gpioStructure->GPIOx, USART_gpioStructure->GPIO_Pin_RX, GPIO_Mode_IPU);

    const USART_TypeDef *USARTs[] = {
        USART1,
        USART2,
        USART3};
    const uint32_t RCC_CLK_USART[] = {RCC_APB2Periph_USART1, RCC_APB1Periph_USART2, RCC_APB1Periph_USART3};
    const uint8_t NVIC_Channels[]  = {USART1_IRQn, USART2_IRQn, USART3_IRQn};

    uint8_t i;
    for (i = 0; i < sizeof(USARTs) / sizeof(USARTs[0]); i++) {
        if (USARTx == USARTs[i]) {
            if (i == 0) {
                RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
            } else
                RCC_APB1PeriphClockCmd(RCC_CLK_USART[i], ENABLE);

            break;
        }
    }

    USART_InitTypeDef USART_Initstruct;
    USART_Initstruct.USART_BaudRate            = BaudRate;
    USART_Initstruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Initstruct.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
    USART_Initstruct.USART_Parity              = USART_Parity_No;
    USART_Initstruct.USART_StopBits            = USART_StopBits_1;
    USART_Initstruct.USART_WordLength          = USART_WordLength_8b;
    USART_Init(USARTx, &USART_Initstruct);

    USART_Cmd(USARTx, ENABLE);

    if (USART_ITstate == SET) {
        USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);

        NVIC_InitTypeDef NVIC_InitTypeDefStruct;
        NVIC_InitTypeDefStruct.NVIC_IRQChannel                   = NVIC_Channels[i];
        NVIC_InitTypeDefStruct.NVIC_IRQChannelCmd                = ENABLE;
        NVIC_InitTypeDefStruct.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;
        NVIC_InitTypeDefStruct.NVIC_IRQChannelSubPriority        = SubPriority;
        NVIC_Init(&NVIC_InitTypeDefStruct);
    }
}
