
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                               clock.c
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


/*======================================================================*
                           clock_handler
 *======================================================================*/
PUBLIC void clock_handler(int irq)
{
                checkArr();
		if (ticks == nextSchedual)
		{
			schedual(); disp_str("!");
		}
if(currentProcess!=-1)
{
                p_proc_ready=&proc_table[currentProcess];
}
/*switch(currentProcess)
{
case 0:{disp_str("0");break;}
case 1:{disp_str("1");break;}
case 2:{disp_str("2");break;}
case 3:{disp_str("3");break;}
case 4:{disp_str("4");break;}
case -1:{disp_str("+");break;}
default:{disp_str("*");break;}
}*/
		ticks++;
        
}

/*======================================================================*
                              milli_delay
 *======================================================================*/
PUBLIC void milli_delay(int milli_sec)
{
        int t = get_ticks();

        while(((get_ticks() - t) * 1000 / HZ) < milli_sec) {}
}

