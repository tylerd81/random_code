//this is the library of ISR functions
#include <dpmi.h>
#include "keys.h"
#include "timer.h"

//the _go32_dpmi_seginfo structs used to install the ISRs
static _go32_dpmi_seginfo 	seginfo_key_isr,	
				   			seginfo_old_keyboard_isr,
				   			seginfo_old_timer_isr,
				   			seginfo_timer_isr;
							
volatile int keys[8] = {0,0,0,0,0,0,0,0}; //the keys array
volatile unsigned int counter;	//the counter used by the timer isr



//this function just reprograms the clock to tick at a different speed
//it just loads up the counter register with a different number
//to countdown from.  Each time the clock ticks the counter register
//is decremented by 1 (every 1.1913Mhz or whatever).  So how many
//ticks are in each million some odd?
void change_time(unsigned short ticks)
{
	//send the control word to the control register
	outportw(TIMER_CONTROL_REG, CONTROL_WORD);
	
	//then write the low byte to the counter register
	outportb(COUNTER_0, LOW_BYTE(ticks));
	
	//then the high byte
	outportb(COUNTER_0, HI_BYTE(ticks));
}


//this is the keyboard ISR
void _isr_key_press(void)
{
	unsigned char key_pressed;
	unsigned char i;

		
	//get the keycode that was pressed from IO port 0x60
	key_pressed = inportb(KBD_PORT);	
		
	//the following just resets the keyboard controller i guess...
	//read the byte from the keyboard control register
	i = inportb(0x61);
	
	i |= 0x82;	//set some bits on the byte
	outportb(0x61, i);	//write the byte back...
	i &= 0x7F; //set some more bits
	outportb(0x61, i); //write it again..  signal another key is ready to be read	
	
	
	//now set the flags in the keys array
	switch(key_pressed)
	{
		//key presses
		case KEY_UP:
			keys[UP] = 1;
			break;
		
		case KEY_DOWN:
			keys[DOWN] = 1;
			break;
		
		case KEY_LEFT:
			keys[LEFT] = 1;
			break;
		
		case KEY_RIGHT:
			keys[RIGHT] = 1;
			break;
			
		case KEY_A:
			keys[PRESS_A] = 1;
			break;
		
		case KEY_W:
			keys[PRESS_W] = 1;
			break;
		
		case KEY_S:
			keys[PRESS_S] = 1;
			break;
		
		//key releases
		case BREAK_A:
			keys[PRESS_A] = 0;
			break;
			
		case BREAK_UP:
			keys[UP] = 0;
			break;
			
		case BREAK_DOWN:
			keys[DOWN] = 0;
			break;
			
		case BREAK_RIGHT:
			keys[RIGHT] = 0;
			break;
			
		case BREAK_LEFT:
			keys[LEFT] = 0;
			break;

		case KEY_ESC:
			keys[QUIT] = 1;
			break;
		
		case BREAK_W:
			keys[PRESS_W] = 0;
			break;
	
		case BREAK_S:
			keys[PRESS_S] = 0;
			break;
					
		default:
			;
			//there is no default now
	}
	
	outportb(0x20, 0x20);
}

void end_isr_key_press(void){} //just a dummy function

void install_keyboard_isr(void)
{
	//first we have to lock all the data and code that the ISR will use
	_go32_dpmi_lock_data(keys, sizeof(keys));
	
	//lock the code
	_go32_dpmi_lock_code(_isr_key_press, end_isr_key_press - _isr_key_press);
	
	//save the old ISR
	_go32_dpmi_get_protected_mode_interrupt_vector(KEYBOARD_IR, &seginfo_old_keyboard_isr);
	
	//setup the struct for the new isr...
	seginfo_key_isr.pm_offset = _isr_key_press; //offset of the isr function
	seginfo_key_isr.pm_selector = _go32_my_cs(); //selector of the ISR
	
	//install the ISR wrapper...
	_go32_dpmi_allocate_iret_wrapper(&seginfo_key_isr);
	
	//install the new isr...
	if(_go32_dpmi_set_protected_mode_interrupt_vector(KEYBOARD_IR, &seginfo_key_isr)) //nonzero on failure
	{
		printf("failed to set _isr_key_press()...\n");
		return;
	}
	
	//the isr should now be installed
}
	
void kill_keyboard_isr(void)
{
	//just reinstall the old isr
	_go32_dpmi_set_protected_mode_interrupt_vector(KEYBOARD_IR, &seginfo_old_keyboard_isr);
}

//this is the timer isr, all it does is increment a counter every time the value
//in the counter register of the clock is decremented to 0 (or when the clock interrupts
//the cpu)
void _isr_timer(void)
{
	counter++;
}
void end_isr_timer(){} //dummy function

void install_timer_isr(void)
{
	//lock the counter variable
	_go32_dpmi_lock_data(&counter, sizeof(counter));
	
	//lock the code
	_go32_dpmi_lock_code(_isr_timer,end_isr_timer - _isr_timer);
	
	//save the old timer isr
	_go32_dpmi_get_protected_mode_interrupt_vector(TIMER_INT, &seginfo_old_timer_isr);
	
	//setup new timer isr
	seginfo_timer_isr.pm_offset = _isr_timer;
	seginfo_timer_isr.pm_selector = _go32_my_cs();
	
	//install the wrapper
	_go32_dpmi_allocate_iret_wrapper(&seginfo_timer_isr);
	
	//install the new timer isr
	if(_go32_dpmi_set_protected_mode_interrupt_vector(TIMER_INT, &seginfo_timer_isr))
	{
		printf("Failed to set _isr_timer()\n");
		return;
	}
}

void kill_timer_isr(void)
{
	_go32_dpmi_set_protected_mode_interrupt_vector(TIMER_INT, &seginfo_old_timer_isr);
}