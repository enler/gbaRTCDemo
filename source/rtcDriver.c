#include <gba_types.h>

#define REG_GPIO_DATA *(vu16*)0x80000C4
#define REG_GPIO_DIRECTION *(vu16*)0x80000C6
#define REG_GPIO_CONTROL *(vu16*)0x80000C8

void BCDToInteger(u8 * data, u32 length) {
//---------------------------------------------------------------------------------
	u32 i;
	for (i = 0; i < length; i++) {
		data[i] = (data[i] & 0xF) + ((data[i] & 0xF0)>>4)*10;
	}
}

void rtcSendCommond(u8 cmd) {
	for (int i = 0; i < 8; i++) {
		u8 bit = (cmd >> (7 - i)) & 1;
		REG_GPIO_DATA = (bit << 1) | 4;
		REG_GPIO_DATA = (bit << 1) | 4;
		REG_GPIO_DATA = (bit << 1) | 4;
		REG_GPIO_DATA = (bit << 1) | 5;
	}
}

u8 rtcReadByte()
{
  u8 result = 0;
  for (int i = 0; i < 8; i++ )
  {
    REG_GPIO_DATA = 4;
    REG_GPIO_DATA = 4;
    REG_GPIO_DATA = 4;
    REG_GPIO_DATA = 4;
    REG_GPIO_DATA = 4;
    REG_GPIO_DATA = 5;
    result = (result >> 1) | ((REG_GPIO_DATA & 2) >> 1 << 7);
  }
  return result;
}

void rtcGetTimeAndDate(u8 * time) {
	REG_GPIO_DATA = 1;
	REG_GPIO_DATA = 5;
	REG_GPIO_DIRECTION = 7;
	rtcSendCommond(0x65);
	REG_GPIO_DIRECTION = 5;
	for (int i = 0; i < 7; i++ )
      time[i] = rtcReadByte();
	time[4] &= 0x7F;
	REG_GPIO_DATA = 1;
	REG_GPIO_DATA = 1;
	BCDToInteger(time, 7);
}

void rtcInit() {
	REG_GPIO_CONTROL = 1;
}