
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                               proc.c
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                                    Forrest Yu, 2005
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "type.h"
#include "const.h"
#include "protect.h"
#include "proto.h"
#include "string.h"
#include "proc.h"
#include "global.h"
void priorNormalize();
void schedual();
void checkArr();
/*======================================================================*
                              schedule
 *======================================================================*/
void schedual()
{
int i;
	if (head[0] != -1)
	{
		currentProcess = head[0];
		indice[0][head[0]] = -2;
		indice[1][head[0]] = -1;
		priorNormalize();

		if (queues[0][currentProcess].remaining >= 5)
		{
			for (i = 0; i < 3; i++)
			{
				queues[i][currentProcess].remaining -= 5;
			}
			nextSchedual = ticks + 5;
		}
		else
		{
			nextSchedual = ticks + queues[0][currentProcess].remaining;
			for (i = 0; i < 3; i++)
			{
				queues[i][currentProcess].remaining = 0;
			}
		}
		return;
	}
	if (head[1] != -1)
	{
		currentProcess = head[1];
		indice[1][head[1]] = -2;
		indice[2][head[1]] = -1;
		priorNormalize();
		
		if (queues[0][currentProcess].remaining >= 10)
		{
			for (i = 0; i < 3; i++)
			{
				queues[i][currentProcess].remaining -= 10;
			}
			nextSchedual = ticks + 10;
		}
		else
		{
			nextSchedual = ticks + queues[0][currentProcess].remaining;
			for (i = 0; i < 3; i++)
			{
				queues[i][currentProcess].remaining = 0;
			}
		}
		return;
	}
	if (head[2] != -1)
	{
		currentProcess = head[2];
		priorNormalize();
		
	    nextSchedual = ticks + queues[0][currentProcess].remaining;
		for (i = 0; i < 3; i++)
		{
			queues[i][currentProcess].remaining = 0;
		}
		indice[2][currentProcess] = -2;
		priorNormalize();
		return;
	}
	currentProcess = -1; return;
}

void checkArr()
{
int i;
	for (i = 0; i < NR_TASKS; i++)
	{
		if (queues[0][i].arr == ticks)
		{
			indice[0][i] = -1;
			priorNormalize();
		}
                if (queues[0][i].remaining <=0)
		{
			int j;
                        for(j=0;j<3;j++)
                        {
                              indice[j][i]=-2;
                        }
		}
	}
}

void priorNormalize()
{
int j;
int i;
	for (j = 0; j < 3; j++)
	{
		int checked[NR_TASKS];
		for (i = 0; i < NR_TASKS; i++)
		{
			checked[i] = 0;
		}

		int nonvalidNum = 0;
		for (i = 0; i < NR_TASKS; i++)
		{
			if (indice[j][i] == -2)
				nonvalidNum++;
		}
		if (nonvalidNum == 5)
		{
			head[j] = -1;
			continue;
		}

		int checkedNum = 0;
		int selected = -1;
		int maxPrior = 4;
		int lastSelected = -1;
		while (checkedNum < 5)
		{
			selected = -1;
			maxPrior = 4;
			for (i = 0; i < NR_TASKS; i++)
			{
				if (checked[i] == 0)
				{
					if (indice[j][i] == -2)
					{
						checked[i] = 1; checkedNum++; continue;
					}
					else
					{
						if (queues[j][i].priority < maxPrior)
						{
							maxPrior = queues[j][i].priority;
							selected = i;
						}
					}
				}
			}
			if (selected != -1)
			{
				if (lastSelected == -1)
				{
					head[j] = selected;
				}
				else
				{
					indice[j][lastSelected] = selected;
				}
				checked[selected] = 1;
				checkedNum++;
				lastSelected = selected;
			}
		}
		if (lastSelected != -1)
		{
			indice[j][lastSelected] = -1;
		}
	}
}

/*======================================================================*
                           sys_get_ticks
 *======================================================================*/
PUBLIC int sys_get_ticks()
{
	return ticks;
}

