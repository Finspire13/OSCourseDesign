
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                               clock.c
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                                    Forrest Yu, 2005
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "type.h"
#include "const.h"
#include "protect.h"
#include "string.h"
#include "proc.h"
#include "tty.h"
#include "console.h"
#include "global.h"
#include "proto.h"
/*======================================================================*
                           clock_handler
 *======================================================================*/
PUBLIC void clock_handler(int irq)
{

if(ticks==1)
{
disp_str("                                                                                                                  ");
disp_str("                                                                                                                       ");
disp_str("       *****************************************************************************               ");
disp_str("                                                                                                                  ");
disp_str("                                                                  Rawinix  1.0                                   ");
disp_str("                                                                          ");
disp_str("       *****************************************************************************               ");
disp_str("              You Can Press:TAB F1 F2 F11 F12                       ");
disp_str("1.TAB:Hit The Susliks                       ");
disp_str("                                    2. F1:Shut Down                       ");
disp_str("                                          3. F2:Show Current Location                       ");
disp_str("                              4. F11:Show Current Directory                       ");
disp_str("                            5.  F12:Show Current Date                       ");
disp_str("                                6. Ctrl:Show Process Management                       ");
disp_str("                                                                                                                  ");
disp_str("                                                                        ");
}

	ticks++;
	p_proc_ready->ticks--;

	if (k_reenter != 0) {
		return;
	}

	if (p_proc_ready->ticks > 0) {
		return;
	}

	schedule();

      if(shot_num>=0&&is_shot==1)
      {
                switch(shot_num)
                {
                  case 0:{ disp_str("D @ G                                                                           ");game_target=0x21; is_shot=0;shot_num++;break;}
                  case 1:{ disp_str("J @ L                                                                             ");game_target=0x25;is_shot=0;shot_num++;break;}
                  case 2:{ disp_str("B @ M                                                                           ");game_target=0x31;is_shot=0;shot_num++;break;}
                  case 3:{ disp_str("Z @ C                                                                           ");game_target=0x2D;is_shot=0;shot_num++;break;}
                  case 4:{ disp_str("Q @ E                                                                          ");game_target=0x11;is_shot=0;shot_num++;break;}
                  case 5:{ disp_str("G @ J                                                                          ");game_target=0x23;is_shot=0;shot_num++;break;}
                  case 6:{ disp_str("A @ D                                                                          ");game_target=0x1F;is_shot=0;shot_num++;break;}
                  case 7:{ disp_str("Z @ C                                                                           ");game_target=0x2D;is_shot=0;shot_num++;break;}
                  case 8:{ disp_str("Y @ I                                                                          ");game_target=0x16;is_shot=0;shot_num++;break;}
                  case 9:{ disp_str("X @ V                                                                            ");game_target=0x2E;is_shot=0;shot_num++;break;}
                  case 10:{
                   disp_str("Your Score:\n");
                   int num=(ticks-game_start_tick)/100;
disp_int(num);
                   game_target=0x01;
                   shot_num=-1;
                   break;
                 }
                  default:break;
                }
      }

}




/*======================================================================*
                              milli_delay
 *======================================================================*/
PUBLIC void milli_delay(int milli_sec)
{
        int t = get_ticks();

        while(((get_ticks() - t) * 1000 / HZ) < milli_sec) {}
}

/*======================================================================*
                           init_clock
 *======================================================================*/
PUBLIC void init_clock()
{
        /* 初始化 8253 PIT */
        out_byte(TIMER_MODE, RATE_GENERATOR);
        out_byte(TIMER0, (u8) (TIMER_FREQ/HZ) );
        out_byte(TIMER0, (u8) ((TIMER_FREQ/HZ) >> 8));

        put_irq_handler(CLOCK_IRQ, clock_handler);    /* 设定时钟中断处理程序 */
        enable_irq(CLOCK_IRQ);                        /* 让8259A可以接收时钟中断 */
}


