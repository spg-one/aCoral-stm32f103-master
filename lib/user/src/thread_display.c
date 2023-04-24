#include<thread.h>
#include<policy.h>
#include<hal.h>
#include"shell.h"

void display_thread(acoral_32 argc,acoral_char **argv){
	acoral_sr cpu_sr;	
	acoral_list_t *head,*tmp;
	acoral_thread_t * thread;
	head=&acoral_threads_queue.head;
	acoral_print("\t\tSystem Thread Information\r\n");
	acoral_print("------------------------------------------------------\r\n");
	acoral_print("Name\t\tType\t\tConsole\t\tState\r\n");
	HAL_ENTER_CRITICAL();

	for(tmp=head->next;tmp!=head;tmp=tmp->next){
		thread=list_entry(tmp,acoral_thread_t,global_list);
		acoral_print("%s\t\t",thread->name);
		switch(thread->policy){
			case ACORAL_SCHED_POLICY_COMM:
				acoral_print("Common\t\t");
				break;
			case ACORAL_SCHED_POLICY_PERIOD:
				acoral_print("Period\t\t");
				break;
			default:
				break;
		}
		acoral_print("%d\t\t",thread->console_id);
		if(thread->state&ACORAL_THREAD_STATE_RUNNING)
				acoral_print("Running\t\t");
		else if(thread->state&ACORAL_THREAD_STATE_READY)
				acoral_print("Ready\t\t");
		else if(thread->state&ACORAL_THREAD_STATE_DELAY)
				acoral_print("Delay\t\t");
		else if(thread->state&ACORAL_THREAD_STATE_SUSPEND)
				acoral_print("Sleep\t\t");
		else if(thread->state==ACORAL_THREAD_STATE_EXIT)
				acoral_print("Freeze\t\t");
		else
				acoral_print("Error\t\t");
		acoral_print("\r\n");
	}
	acoral_print("------------------------------------------------------\r\n");

	HAL_EXIT_CRITICAL();
}

acoral_shell_cmd_t dt_cmd={
	"dt",
	(void*)display_thread,
	"View all thread info",
	NULL
};
