
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            global.c
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                                    Forrest Yu, 2005
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#define GLOBAL_VARIABLES_HERE

#include "type.h"
#include "const.h"
#include "protect.h"
#include "proto.h"
#include "proc.h"
#include "global.h"


PUBLIC	PROCESS			proc_table[NR_TASKS];

PUBLIC PROCESS queue0[NR_TASKS];
PUBLIC PROCESS queue1[NR_TASKS];
PUBLIC PROCESS queue2[NR_TASKS];
PUBLIC PROCESS* queues[3];

PUBLIC int index0[NR_TASKS];
PUBLIC int index1[NR_TASKS];
PUBLIC int index2[NR_TASKS];
PUBLIC int* indice[3];
PUBLIC int head[3];

PUBLIC int currentProcess = -1;
PUBLIC int nextSchedual = 0;

PUBLIC	char			task_stack[STACK_SIZE_TOTAL];

PUBLIC	TASK	task_table[NR_TASKS] = {{TestA, STACK_SIZE_TESTA, "TestA"},
					{TestB, STACK_SIZE_TESTB, "TestB"},
					{TestC, STACK_SIZE_TESTC, "TestC"},
                                        {TestD, STACK_SIZE_TESTD, "TestD"},
                                        {TestE, STACK_SIZE_TESTE, "TestE"}};

PUBLIC	irq_handler		irq_table[NR_IRQ];

PUBLIC	system_call		sys_call_table[NR_SYS_CALL] = {sys_get_ticks};

