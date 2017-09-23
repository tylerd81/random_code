//include file for all the timer defines from isrs.c

#define TIMER_INT			0x1C

#define TIMER_CONTROL_REG	0x43 	//the timer control register's port

//these defines are used by change_time()
#define CONTROL_WORD		0x3C 	//word to write to the control register
#define TIMER_60HZ			0x4DAE	//60 ticks a second
#define TIMER_30HZ			0x965C	//30
#define TIMER_20HZ			0xE90B	//20
#define TIMER_18HZ			0xFFFF	//18.2 - this is what it's usually set to
#define COUNTER_0			0x40	//this is the port of the counter to change

//prototypes
void change_time(unsigned short ticks);
void _isr_timer(void);				//the actual timer ISR
void end_isr_timer(void);			//dummy function
void install_timer_isr(void);
void kill_timer_isr(void);

extern volatile unsigned int counter;	//counter for the timer isr