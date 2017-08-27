
#include <gba_console.h>
#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_input.h>
#include <stdio.h>
#include <stdlib.h>

#include "rtcDriver.h"

//---------------------------------------------------------------------------------
// Program entry point
//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------


	// the vblank interrupt must be enabled for VBlankIntrWait() to work
	// since the default dispatcher handles the bios flags no vblank handler
	// is required
	irqInit();
	irqEnable(IRQ_VBLANK);

	consoleDemoInit();

	rtcInit();
	u8 time[7];

	// ansi escape sequence to set print co-ordinates
	// /x1b[line;columnH
	//iprintf("\x1b[10;10HHello World!\n");

	//

	while (1) {
		rtcGetTimeAndDate(time);
		iprintf(CON_CLS());
		iprintf(CON_POS(3, 4));
		iprintf("Today is %04d/%02d/%02d\n", time[0] + 2000, time[1], time[2]);
		iprintf(CON_POS(3, 5));
		iprintf("It's %02d:%02d:%02d", time[4], time[5], time[6]);
		VBlankIntrWait();
	}
}


