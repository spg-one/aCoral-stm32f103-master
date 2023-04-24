/**
 * @file int.c
 * @author 王彬浩 (SPGGOGOGO@outlook.com)
 * @brief kernel层，中断相关函数
 * @version 1.0
 * @date 2022-07-24
 * @copyright Copyright (c) 2022
 * @revisionHistory 
 *  <table> 
 *   <tr><th> 版本 <th>作者 <th>日期 <th>修改内容 
 *   <tr><td> 0.1 <td>jivin <td>2010-03-08 <td>Created 
 *   <tr><td> 1.0 <td>王彬浩 <td> 2022-07-24 <td>Standardized 
 *  </table>
 */
#include <type.h>
#include <hal.h>
#include <lsched.h>
#include <print.h>
#include <int.h>

/**
 * @brief 中断初始化函数
 * 
 */
void acoral_intr_sys_init()
{
	
}

/**
 * @brief 将服务函数isr绑定到中断向量Vector
 * 
 * @param vector 中断向量号
 * @param isr 中断服务程序指针
 * @return acoral_32 返回0表示成功
 */
acoral_32 acoral_intr_attach(acoral_vector vector, void (*isr)(acoral_vector))
{
	
}

/**
 * @brief 将中断的服务函数设为默认的
 * 
 * @param vector 中断向量号
 * @return acoral_32 返回0表示成功
 */
acoral_32 acoral_intr_detach(acoral_vector vector)
{
	
}

/**
 * @brief 使能中断
 * 
 * @param vector 中断向量号
 */
void acoral_intr_unmask(acoral_vector vector)
{

}

/**
 * @brief 除能中断
 * 
 * @param vector 中断向量号
 */
void acoral_intr_mask(acoral_vector vector)
{

}

/**
 * @brief aCoral默认中断处理程序
 * 
 * @param vector 中断向量号 
 */
void acoral_default_isr(acoral_vector vector)
{
	acoral_print("in Default interrupt route\n");
}

/**
 * @brief 中断退出函数
 * 
 */
void acoral_intr_exit()
{
	if (!acoral_need_sched)
		return;

	if (acoral_intr_nesting)
		return;

	if (acoral_sched_is_lock)
		return;

	if (!acoral_start_sched)
		return;

	/*如果需要调度，则调用此函数*/
	HAL_INTR_EXIT_BRIDGE();
}


/**
 * @brief 设置中断类型，ACORAL_COMM_INTR、ACORAL_EXPERT_INTR或ACORAL_RT_INTR
 * 
 * @param vector 
 * @param type 
 */
void acoral_intr_set_type(acoral_vector vector, acoral_u8 type)
{

}

/**
 * @brief 异常错误输出，aCoral除了中断异常以外的异常发生后，都会通过EXP_HANDLER进入这个函数打印异常信息
 * 
 * @param lr 链接寄存器，保存异常发生时的pc
 * @param stack 栈指针，保存发生异常时线程的栈
 */
void acoral_fault_entry(acoral_u32 lr, acoral_u32 *stack)
{
	acoral_intr_disable();
	if (!acoral_start_sched)
		while (1)
			;
	acoral_print("Exception occur\n");
	acoral_print("******************\n");
	acoral_print("Thread name:%s\n", acoral_cur_thread->name);
	acoral_print("Thread prio:%d\n", acoral_cur_thread->prio);
	acoral_print("Thread stack_size:%d\n", acoral_cur_thread->stack_size);
	acoral_print("Thread stack_buttom:0x%x\n", acoral_cur_thread->stack_buttom);
	acoral_print("Thread stack:0x%x\n", acoral_cur_thread->stack);
	acoral_print("Pc:0x%x\n", lr);
	acoral_print("Stack:0x%x\n", stack);
	acoral_print("******************\n");
	while (1)
		;
}
