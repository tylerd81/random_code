#include <pc.h>
#define VGA_STATUS_PORT 0x03DA
/* 
 * write to the status port, the byte is returned, if bit 4 is set then a retrace
 * is in progress, meaning the electron gun is moving back to the top left corner
 * or the screen.  If it's not set then the electron gun is busy updating the
 * screen.
 */
 
void vsync(void)
{
	int mask = 0x08;
	
	while(inportb(VGA_STATUS_PORT) & mask)
	{
		;//do nothing and wait for retrace to end, so we don't start in the
		 //middle of a retrace 
	}
	
	//the bit is not set meaning a retrace is not happening
	while(!(inportb(VGA_STATUS_PORT) & mask))
	{
		;
	}
	//once the bit is set we know we are at the begining of a retrace period and it is
	//safe to update the vram
}
	