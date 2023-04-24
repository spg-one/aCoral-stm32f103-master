#include"acoral.h"
#include"shell.h"
#include "gtim.h"

void dummy(void *args){
	int i=0;
	while(1){
		i++;
		// LedControl(i);
		acoral_print("dummy....");
		acoral_delay_self(1000);
	}
}

/*温度计算公式*/
float temp_count(uint16_t num)
{
	float temp = num * 0.0625 - 50.0625;
	if (temp < 30)
	{
		temp = temp + (temp-30)*0.05;
	}else if(temp >= 30 && temp <= 100)
	{
		temp = temp;
	}else{
		temp = temp + (100-temp)*0.012;
	}
	return temp;
}


void route()
{
	/*复位*/
 	GPIO_InitTypeDef gpio_init_struct;
    __HAL_RCC_GPIOA_CLK_ENABLE();
    gpio_init_struct.Pin = GPIO_PIN_0;
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP; /*输出*/
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &gpio_init_struct);


	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
	//__HAL_TIM_SET_COUNTER(&g_tim2_cnt_ch1_handle, 0);
	acoral_delay_self(10);
	// HAL_Delay(10);

	/*数据转换期 + 数据通信期*/
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
	acoral_delay_self(27);
	gtim_timx_cnt_chy_init(0);
	acoral_delay_self(30);
	// HAL_Delay(70);

	int num = __HAL_TIM_GET_COUNTER(&g_tim2_cnt_ch1_handle);
	float temp = temp_count(num);
	acoral_print("当前温度为：%f\n",temp);
}

void test()
{
	acoral_print("测试\n");
}

void user_main(void)
{
	gtim_timx_cnt_chy_init(0); /*初始化通用定时器*/

	acoral_period_policy_data_t* data;
	data = acoral_malloc(sizeof(acoral_period_policy_data_t));
	data->prio = 20;
	data->prio_type = ACORAL_ABSOLUTE_PRIO;
	data->time = 1000; /*一秒钟采集一次*/
	acoral_create_thread(route,512,NULL,"tmp_thread",NULL,ACORAL_SCHED_POLICY_PERIOD,data);
}
