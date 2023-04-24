#ifndef GTIM_H
#define GTIM_H

#include "stm32f1xx_hal.h" 

extern TIM_HandleTypeDef g_tim2_cnt_ch1_handle;

void gtim_timx_cnt_chy_init(uint16_t psc);

void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim);

#endif