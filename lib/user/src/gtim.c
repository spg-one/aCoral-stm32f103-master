#include "gtim.h"

/*定时器句柄*/
TIM_HandleTypeDef g_tim2_cnt_ch1_handle;

/*初始化函数*/
void gtim_timx_cnt_chy_init(uint16_t psc)
{
    TIM_SlaveConfigTypeDef tim_slave_config = {0};

    g_tim2_cnt_ch1_handle.Instance = TIM2;
    g_tim2_cnt_ch1_handle.Init.Prescaler = psc;
    g_tim2_cnt_ch1_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    g_tim2_cnt_ch1_handle.Init.Period = 65535;
    HAL_TIM_IC_Init(&g_tim2_cnt_ch1_handle);

    tim_slave_config.SlaveMode = TIM_SLAVEMODE_EXTERNAL1;
    tim_slave_config.InputTrigger = TIM_TS_TI1FP1; 
    tim_slave_config.TriggerPolarity = TIM_TRIGGERPOLARITY_FALLING; /*下降沿*/
    tim_slave_config.TriggerFilter = 0;

    HAL_TIM_SlaveConfigSynchro(&g_tim2_cnt_ch1_handle, &tim_slave_config);

    HAL_TIM_IC_Start(&g_tim2_cnt_ch1_handle, TIM_CHANNEL_1);
}

/*定时器输入捕获*/
void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM2)
    {
        GPIO_InitTypeDef gpio_init_struct;
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_TIM2_CLK_ENABLE();

        gpio_init_struct.Pin = GPIO_PIN_0;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP; /*推挽式复用输入*/
        gpio_init_struct.Pull = GPIO_PULLUP; /*上拉，检测低电平*/
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &gpio_init_struct);
    }
}