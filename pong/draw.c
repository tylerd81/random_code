//module to do the actual drawing to the screen, also sets up the vram selector.
#include <dpmi.h>
#include <sys/farptr.h> //for _farpokeb() (that may change, might use _farpokew()
#include "pong.h"
#include "keys.h"
#include "timer.h"

//#define BALLCOLOR     (eflag ? 0 : 15) //if eflag is set then erase otherwise use the color

_selector vram;     //this is our global selector to vram

//pong_init() must be called first, it sets up the vram selector.
//if this fails it will return 0
int pong_init(void)
{
     int temp_selector;
     /* 
      * note that vram is NOT a pointer, it is a selector that is used to 
      * select a descriptor.  vram is actually just an unsigned short, or
      * a 16 bit (2 byte) variable.
      */
      
     /*
      * __dpmi_segment_to_descriptor() returns -1 on error, but all the
      * functions that use the descriptor expect it to be an unsigned
      * short (the descriptor really is only 16 bits), so here after
      * we check for error, we cast the int to an unsigned short, 
      * which should not matter because the high 16 bits should
      * not have been set if this is a valid descriptor or they
      * were set to 0.
      */
     temp_selector = __dpmi_segment_to_descriptor(0xA000);
     if(temp_selector < 0)
          return 0;
      
     vram = (unsigned short)temp_selector;
     
	 install_keyboard_isr();
	 install_timer_isr();
	      
     //all went well so now lets set the video mode
     set_vid_mode(MODE13H);
     return 1;
}

void pong_exit(void)
{
     kill_timer_isr();
     kill_keyboard_isr();
     set_vid_mode(TEXTMODE);
}

/* 
 * this function will be too slow for drawing the paddles, they will use
 * there own special routines, but this function is for testing and just
 * messing around.
 */
void __putpixel(int x, int y, char color)
{
     int offset = x + (y * 320);     
     _farpokeb(vram, offset, color);
}


/*
 * new draw_ball() using the ball struct.  The actual ball will be created by create_ball() 
 * which will fill in the struct, the ball is going to be a set size just so that this 
 * function can be as fast as possible
 */
inline void draw_ball(ball_tag *ball)
{
     unsigned int poke_this;
     //unsigned int mask = 0x0F000000; //highest bit set
     int offset;
     
     //the ball is 4 wide by 5 high
     unsigned int ball_img[] = { 0x00090900,
                                 0x09090909,
                                 0x09090909,
                                 0x09090909,
                                 0x00090900,
                                };                    
      
     int row;
     bool clipping = 0;     //no clipping yet (don't redraw the background)
     
     //first we have to erase the old ball
     offset = ball->old_x + (ball->old_y * 320);
     for(row = 0; row < 5; row++)
     {
        _farpokel(vram, offset, 0x00000000); //shut all the bytes off
        offset+=320; //next line
     }
     
     //now draw the new ball
     
     
    /* calculate the offset of where the ball is */
    offset = ball->x + (ball->y * 320);
    
    for(row=0;row<5;row++)
    {
       	_farpokel(vram, offset, ball_img[row]); //poke the long (or int, same thing here, both 32 bits)
       	offset+=320; //add another y
    }
    
     return;     
}

//this function erases the ball at it's current position, not the old x and old y
void erase_ball(ball_tag *ball)
{
	int offset, row;
	offset = ball->x + (ball->y*320);
	
	for(row = 0; row < 5; row++)
	{
		_farpokel(vram, offset, 0x00000000);
		offset+=320;	//move to the next y
	}
}

//the parameters are void because paddles[] is a global
void draw_paddles(void)
{
	int offset, i;
   	int paddle_num;
   	
   	//this loop erases the paddle
   	for(paddle_num = 0; paddle_num < NUM_PADDLES; paddle_num++)
   	{
   		//calculate the starting offset of the paddle
   		offset = paddles[paddle_num].x + (paddles[paddle_num].old_y * 320);
   		for(i = 0; i < paddles[paddle_num].height; i++)
   		{
   		    //must change this depending on PADDLE_WIDTH
   			_farpokew(vram, offset, 0x0000);
   			offset+=320; //add a y and keep x offset the same
   		}
   	}
   	
   	//and then this loop draws the paddle
   	for(paddle_num = 0; paddle_num < NUM_PADDLES; paddle_num++)
   	{
   		//calculate the starting offset of the paddle
   		offset = paddles[paddle_num].x + (paddles[paddle_num].y * 320);
   		for(i = 0; i < paddles[paddle_num].height; i++)
   		{
   		    //must change this depending on PADDLE_WIDTH
   			_farpokew(vram, offset, 0xF0F0);
   			offset+=320; //add a y and keep x offset the same
   		}
   	}
}
   		
   			
   		
   			
   	 
   
	

