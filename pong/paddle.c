//the functions that create the paddle(s) and move them (by updating the structs) but does
//not do the actual drawing, draw.c does that
#include "pong.h"
#define PADDLE_GAP 2 //this is the gap between the edge of the screen and the paddles


#define PADDLE_MOVE	2 //move 2 pixels

//the paddles will be an array of type struct paddle_tag, of course since
//there are 2 paddles there will be 2 elements in the array
paddle_tag paddles[NUM_PADDLES];

//these define the width of the paddles and also the starting and ending x positions
//x never changes
void create_paddles(void)
{
    paddles[LEFT_PADDLE].x = 2;
    paddles[LEFT_PADDLE].y = 85;	//start near middle of screen
    paddles[LEFT_PADDLE].height = PADDLE_HEIGHT; //ten pixels high
    //make the end_x one pixel in front of the actual paddle so that it
    //will not look like the ball is going into the paddle
    paddles[LEFT_PADDLE].end_x = paddles[LEFT_PADDLE].x + PADDLE_WIDTH;
    paddles[LEFT_PADDLE].end_y = paddles[LEFT_PADDLE].y + PADDLE_HEIGHT;
    //paddles[LEFT_PADDLE].old_x = 2;
    paddles[LEFT_PADDLE].old_y = 85;
    
    paddles[RIGHT_PADDLE].x = 316;
    paddles[RIGHT_PADDLE].y = 85;
    paddles[RIGHT_PADDLE].height = PADDLE_HEIGHT;
    paddles[RIGHT_PADDLE].end_x = paddles[RIGHT_PADDLE].x - PADDLE_WIDTH;
    paddles[RIGHT_PADDLE].end_y = paddles[RIGHT_PADDLE].y + PADDLE_HEIGHT;    
    //paddles[RIGHT_PADDLE].old_x = 316;
    paddles[RIGHT_PADDLE].old_y = 85;
}

//this obviously moves the paddle up, paddle is either LEFT_PADDLE or RIGHT_PADDLE
//all we do here is first save the old x and y and then decrement y to move it up
//the screen.  We don't draw it here though of course
//this function will check to make sure the move is valid, ie that we don't go off
//of the screen, if it can't move the paddle then it will do nothing at all
int move_paddle_up(int paddle)
{
	//there is no reason to save the x because it will never change...
	paddles[paddle].old_y = paddles[paddle].y;
	
	if(paddles[paddle].y > PADDLE_MOVE)
	{
		paddles[paddle].y-=PADDLE_MOVE;
		paddles[paddle].end_y = paddles[paddle].y + PADDLE_HEIGHT;
	}
	else
		return 0; //can't move
	return 1;
}

int move_paddle_down(int paddle)
{
	paddles[paddle].old_y = paddles[paddle].y;
	
	if(paddles[paddle].y < (SCREEN_BOTTOM - (PADDLE_MOVE + PADDLE_HEIGHT)))
	{
		paddles[paddle].y+=PADDLE_MOVE;
		paddles[paddle].end_y = paddles[paddle].y + PADDLE_HEIGHT;
	}
	else
		return 0; //can't move
	return 1;
}
	
	

	
	