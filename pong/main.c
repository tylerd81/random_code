//main module for pong2k3 version 0.00001 12/19/02
#include <stdio.h>
#include <stdlib.h>
#include <pc.h>
#include "pong.h"
#include "keys.h"
#include "timer.h"

int main(void)
{
     ball_tag ball;
     bool done = 0;
     char ch;
     int i = 0;
     if(!pong_init()) {
          printf("pong_init() failed... exiting\n");
          exit(EXIT_FAILURE);
     }
      
     create_ball(&ball);
     create_paddles();
     draw_paddles(); //draw paddle for the first time
     draw_ball(&ball); //draw the ball for the first time
     
     change_time(TIMER_60HZ);
     
   	 while(!done)
   	 {
		while(counter)
		{
   	    	if(keys[UP]) //move paddle up
   	    		move_paddle_up(LEFT_PADDLE);
   	    	if(keys[DOWN])
   	    		move_paddle_down(LEFT_PADDLE);
   	    	if(keys[PRESS_S])
   	    		move_paddle_down(RIGHT_PADDLE);
   	    	if(keys[PRESS_W])
   	    		move_paddle_up(RIGHT_PADDLE);
			if(keys[QUIT])
				done = 1;  	    		
				
   	    	check_ball(&ball);
   	    	//animate_ball(&ball);
   	    	vsync();
   	    	draw_ball(&ball);
   	    	draw_paddles();
   	    	
   	    	counter = 0; //reset the counter
   	    }
     }
    
     pong_exit();
     return 0;
}
 
