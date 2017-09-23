#include <allegro.h>
#include "pong.h"

//this is the timer...
volatile int counter;

void tick_tock(void)
{
	counter++;
}

void reset_counter(void)
{
	counter=0;
} 