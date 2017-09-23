//header file for the keyboard ISR and it's data (from isrs.c)

//macros to get the high and low bytes out of a 16 bit value
#define HI_BYTE(x) 			((x >> 8) & 0x0F)
#define LOW_BYTE(x) 		(x & 0x0F) //just turn off the high byte

//all the variables and defines for the keyboard ISR
#define KEYBOARD_IR			0x09
#define ATTRIB				0x07
#define KBD_PORT			0x60

#define KEY_ESC				0x01	//for quitting

//these are the actual scan codes recieved from port 0x60
#define KEY_A				0x1E
#define KEY_UP      		0x48
#define KEY_DOWN			0x50
#define KEY_LEFT			0x4B
#define KEY_RIGHT			0x4D
#define KEY_W				0x11
#define KEY_S				0x1F

//these are when the key is released, just add 128 to the KEY_*
#define BREAK_A				KEY_A + 128
#define BREAK_UP 			KEY_UP + 128
#define BREAK_DOWN  		KEY_DOWN + 128
#define BREAK_LEFT			KEY_LEFT + 128
#define BREAK_RIGHT			KEY_RIGHT + 128
#define BREAK_W				KEY_W + 128
#define BREAK_S				KEY_S + 128

//and these are used to access the elements of the keys array
#define UP					0
#define DOWN				1
#define LEFT				2
#define RIGHT				3
#define PRESS_A				4
#define QUIT                5
#define PRESS_W				6
#define PRESS_S				7
//the keys[] array
extern volatile int keys[];

//keyboard ISR functions
void _isr_key_press(void); 			//the actual keyboard ISR. WE DO NOT CALL THIS FUNCTION OURSELVES!!!
void end_isr_key_press(void); 		//dummy function
void install_keyboard_isr(void);
void kill_keyboard_isr(void);
