/*
 * main.h
 *
 *  Created on: 13 de abr de 2021
 *      Author: igor
 */

#ifndef MAIN_H_
#define MAIN_H_

#define SIZE_TASK_STACK (1024U)
#define SIZE_SCHED_STACK (1024U)
#define SRAM_START (0x20000000U)
#define SIZE_SRAM (128 * 1024)
#define SRAM_END (SRAM_START + SIZE_SRAM)

#define T0_STACK_START SRAM_END
#define T1_STACK_START (SRAM_END - 1 * SIZE_TASK_STACK)
#define T2_STACK_START (SRAM_END - 2 * SIZE_TASK_STACK)
#define T3_STACK_START (SRAM_END - 3 * SIZE_TASK_STACK)
#define IDLE_STACK_START (SRAM_END - 4 * SIZE_TASK_STACK)
#define SCHED_STACK_START (SRAM_END - 5 * SIZE_TASK_STACK)

#define TICK_HZ 1000U
#define HSI_CLOCK 16000000U
#define SYSTICK_TIM_CLK HSI_CLOCK
#define MAX_TASKS 5

#define TASK_RUNNING_STATE 0x00
#define TASK_BLOCKED_STATE 0xFF

#define INTERRUPT_DISABLE() {__asm volatile ("MOV R0,#0x1"); __asm volatile ("MSR PRIMASK,R0");}
#define INTERRUPT_ENABLE() {__asm volatile ("MOV R0,#0x0"); __asm volatile ("MSR PRIMASK,R0");}

void task0(void);
void task1(void);
void task2(void);
void task3(void);
void idle_task(void);
void init_systick_timer(uint32_t tick_hz);
__attribute__((naked)) void init_scheduler_stack(uint32_t sched_top_of_stack);
void init_tasks_stack(void);
void UsageFault_Handler_c(uint32_t *pBaseStackFrame);
void enable_processor_faults(void);
__attribute__((naked)) void switch_sp_to_psp(void);
uint32_t get_psp_value(void);
void save_psp_value(uint32_t current_psp_value);
void update_next_task(void);
void task_delay(uint32_t tick_count);

typedef struct{
	uint32_t psp_value;
	uint32_t block_count;
	uint32_t current_state;
	void (*task)(void);
}TCB_t;

#endif /* MAIN_H_ */












