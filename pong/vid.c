//module to set the video mode, that is all that it does right now
#include <dpmi.h>
#include "pong.h"
  
void set_vid_mode(unsigned char mode)
{
     __dpmi_regs r;
     
     r.h.ah = 0x00; //interrupt subroutine
     r.h.al = mode;
     
     __dpmi_int(0x10, &r);
}

