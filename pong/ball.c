//v 0.0001
//this is the module that controls the ball, it doesnt draw it though
//The ball doesn't really respond to user input, it is always moving and changes direction
//when it hits something (the paddle).
#include <string.h>
#include "pong.h"
#include "keys.h"

//these are the boundaries that the ball cannot go past, or when it does
//someone scores
#define X_BOUNDS_LEFT   0
#define X_BOUNDS_RIGHT  319

#define LEEWAY	4	//number of pixels to allow for the paddle to be able to hit just a tip of the ball

/* 
 * so the order in which these are called should be:
 * first at the very begining create the ball
 * next draw the ball for the first time with draw_ball()
 * then start the loop...
 * check_ball() to see if it hit anything...
 * animate_ball() - move the ball
 * then draw it in the new position
 * then check_ball() again and so on...
 */
//call this in the initialization to setup the ball struct
int create_ball(ball_tag *ball)
{
    memset(ball, 0, sizeof(ball_tag));
    
    //set the ball in the middle of the screen
    ball->x = 160;
    ball->y = 100; 
    
    //now we have to set the initial direction, this should be random but
    //for now it isn't going to be
    ball->direction = MOVE_RIGHT;
    ball->steps=3;
    ball->y_steps=0; //move straight across
    return 1;
}

//this checks whether the ball is in bounds and if it has hit one of its
//boundaries it changes the direction of the ball
//this is also where it will check whether or not a paddle has hit the ball
void check_ball(ball_tag *ball)
{
    //check for collision with LEFT_PADDLE
    if(ball->x == paddles[LEFT_PADDLE].x + PADDLE_WIDTH) //maybe a collision
    {
    	if(ball->y >= (paddles[LEFT_PADDLE].y - LEEWAY) && ball->y <= (paddles[LEFT_PADDLE].end_y +LEEWAY))
    	{
    		int paddle_center, ball_center;
    		
    		ball->direction = MOVE_RIGHT; //the left paddle got hit so send the ball on its way
    		ball->old_x = ball->x;
    		ball->old_y = ball->y;
    		ball->x += ball->steps;
    		
    		paddle_center = paddles[LEFT_PADDLE].y + (PADDLE_HEIGHT/2);
    		ball_center = ball->y + (BALL_HEIGHT/2);
    		
    		//change the y value of the ball depending on where on the paddle the ball bounced
    		if(ball_center < (paddle_center - 1)) //hit upper part
    		{
    			ball->y_steps--;// = -1;
    			if(ball->y_steps == 0)
    				ball->y_steps--; //no zero
    		}
    		else if(ball_center > (paddle_center - 1))
    		{
    			ball->y_steps++;// = 1;
    			if(ball->y_steps == 0)
    				ball->y_steps++;
    		}
    		/*
    		else
    		{
    			ball->y_steps = 0;
    		}*/
    		return;
    	}
    	//if it didn't hit the paddle then it hit the edge of the screen... so that means someone
    	//scored, so reset the ball 
    	reset_ball(ball);
    	return;
    } 
  
  	//check for collisions with the RIGHT_PADDLE
    else if(ball->x >= paddles[RIGHT_PADDLE].x - BALL_WIDTH) //hit the right side of the screen
    {
    	if(ball->y >= (paddles[RIGHT_PADDLE].y - LEEWAY) && ball->y <= (paddles[RIGHT_PADDLE].end_y + LEEWAY))
    	{
    	    int paddle_center, ball_center;
    		ball->direction = MOVE_LEFT; //ball has hit the right paddle
    		ball->old_x = ball->x;
    		ball->old_y = ball->y;
    		ball->x -= ball->steps;
    		
    		//find the centers of each of the objects
    		paddle_center = paddles[RIGHT_PADDLE].y + (PADDLE_HEIGHT/2);
    		ball_center = ball->y  + (BALL_HEIGHT/2);
    		
    		
    		//now figure out the y_steps
    		if(ball_center < (paddle_center - 1)) //hit in higher part of paddle
    		{
    			ball->y_steps--;// = -1; //send ball upwards
    			if(ball->y_steps == 0)
    				ball->y_steps--;
    		}
    		else if(ball_center > (paddle_center -1)) //hit in lower part
    		{
    			ball->y_steps++;// = 1; //move ball downwards
    			if(ball->y_steps == 0)
    				ball->y_steps++;
    		}
    		
    		else
    		{
    			ball->y_steps = 0; //keep ball going straight
    		}
    		
    		return;
    	}
    	//if we didn't hit the paddle then we hit the edge of the screen
    	reset_ball(ball);
    	return;
    }   
    else //ball is in motion between paddles, we just move the ball depending on the direction it is moving
    {
    	int temp_y;

		//save the old x and y    	
    	ball->old_x = ball->x;
    	ball->old_y = ball->y;

    	//move the x position
    	if(ball->direction == MOVE_RIGHT)
    		ball->x += ball->steps;
    	else //we are moving MOVE_LEFT
    		ball->x -= ball->steps;
    	
    	//move the ball's y position
    	if((ball->y + ball->y_steps > 0) && (ball->y + ball->y_steps < SCREEN_BOTTOM))
    		ball->y += ball->y_steps; //move it up or down
    	else //we cant move either up or down (one or the other), so change directions
    	{
    		//just negate the steps so we move the opposite direction
    		ball->y_steps = -(ball->y_steps);
    		ball->y += ball->y_steps;
    	}
    	
    	return;
    }
}

//this does the moving of the ball, but doesn't draw it all it needs is the ball struct
//to know which way the ball is moving and where on the screen it is located
//each time it is called the ball is moved ball.steps amount of pixels, or x
//is incremented or decremented by ball.steps

//this is not used anymore - 12/27/02
void animate_ball(ball_tag *ball)
{
    //save the old x and y first
    ball->old_x = ball->x;
    ball->old_y = ball->y;
    
    if(ball->direction == MOVE_RIGHT) //increment x
        ball->x += ball->steps;
    else if(ball->direction == MOVE_LEFT) //decrment x
        ball->x -= ball->steps;
}    

void reset_ball(ball_tag *ball)
{
    //first erase the old ball
    erase_ball(ball);
        
	//just set the ball to the middle of the screen (or near the middle at least)
	ball->x = 160;
	ball->y = 100;
	ball->direction = MOVE_LEFT;
	ball->y_steps = 0;
	while(!keys[PRESS_A]) //don't return untill A is hit
		;	//do nothing
}
	