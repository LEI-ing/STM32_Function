#ifndef TIM_H
#define TIM_H

#define TimerFrequency 1000000

void TIM_General_Init(TIM_TypeDef *TIM, uint8_t time_ms, FunctionalState IT_State, uint8_t PreemptionPriority, uint8_t SubPriority);

#endif
