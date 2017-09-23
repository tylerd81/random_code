#define TEXTMODE 0x03     //normal DOS textmode
#define MODE13H 0x13     //mode 13h of course

#define SCREEN_BOTTOM	170
//these are for determining which way the ball is moving
#define MOVE_LEFT    0
#define MOVE_RIGHT   1

//for choosing which paddle to use
#define LEFT_PADDLE		0
#define RIGHT_PADDLE	1
#define NUM_PADDLES		2 //in case for some reason we ever add more

#define PADDLE_HEIGHT 20
#define PADDLE_WIDTH 2
#define BALL_WIDTH  4
#define BALL_HEIGHT 6 //ball is actually 5 pixels high

typedef unsigned short _selector; //not the actual selector, just a typedef
typedef char bool;



//The ball struct.. added 12/20
typedef struct 
{
     int x;               //x position of the ball
     int y;               //y position
     int old_x;
     int old_y;
     bool erase_flag;     //1 if ball is to be erased
     char *bg;          //pointer to mem where to save what is underneath the ball
     bool direction;    //whether the ball is traveling left or right
     int steps;         //number of x pixels to move the ball each time animate_ball() is called
     int y_steps;		//number of pixels to move up and down, negative numbers mean of course
     					//to move down that many pixels
}ball_tag;
     
//all we need to know about the paddles are the starting x and y and the height
//the width is determined whether we are using _farpokeb(), _farpokew(), or _farpokel()
//we are using _farpokew() right now, 16bits or 2 bytes or 2 pixels wide
typedef struct
{
	int x;
	int y;
	int end_x;
	int end_y;
	int old_x; //for erasing the paddle, we don't need to save end_x and end_y
	int old_y; //because we don't check for collisions here
	int height;
}paddle_tag;
	
//the extern form paddle.c, this is the actual array that holds the paddle data
extern paddle_tag paddles[];

//prototypes

//draw.c
int pong_init(void);
void __putpixel(int x, int y, char color);
void pong_exit(void);
inline void draw_ball(ball_tag *ball);
void erase_ball(ball_tag *ball);

//vid.c
void set_vid_mode(unsigned char mode);

//ball.c
int create_ball(ball_tag *ball);
void animate_ball(ball_tag *ball);
void check_ball(ball_tag *ball);
void reset_ball(ball_tag *ball);

//time.c
void tick_tock(void);
void reset_counter(void);

//vsync.c
void vsync(void);

//paddle.c
void create_paddles(void);
int move_paddle_up(int paddle);
int move_paddle_down(int paddle);
