/* libs */
#include "STD_TYPES.h"
#include "BIT_MAN.h"
/* own */
#include "SysTick_interface.h"
#include "SysTick_registers.h"

SysTickCallBack_t SysTickCB;

void SysTick_init(void)
{
   /* disable the counter */
   SysTick_setEnableState(0);
   
   /* disable the interrupt */
   SysTick_setINTstate(0);
   
   /* reset counter value and the zero flag */
   SysTick_resetValAndZeroFlag();
   
   /* reset load value */
   SysTick_setLoadVal(0);
   
   /* set clock source to AHB (processor clock) */
   SysTick_setClockSource(SYSTICK_CLOCK_SOURCE_AHB);
}

u8 SysTick_isReachedZero(void)
{
   return BIT_GET(STK_CTRL, 16);
}

void SysTick_resetZeroFlag(void)
{
   volatile u32 x = SysTick_isReachedZero();
   x++;
}

u8 SysTick_setClockSource(u8 clkSrc)
{
   switch (clkSrc)
   {
   case SYSTICK_CLOCK_SOURCE_AHB_DIV8:
      STK_CTRL = BIT_CLEAR(STK_CTRL, 2);
      
      return 1;
   break;

   case SYSTICK_CLOCK_SOURCE_AHB:
      STK_CTRL = BIT_SET(STK_CTRL, 2);
      
      return 1;
   break;
   }
   
   /* invalid clock source */
   return 0;
}

u8 SysTick_getClockSource(void)
{
   return BIT_GET(STK_CTRL, 2);
}

void SysTick_setINTstate(u8 state)
{
   if (state == 1)
   {
      STK_CTRL = BIT_SET(STK_CTRL, 1);
   }
   else
   {
      STK_CTRL = BIT_CLEAR(STK_CTRL, 1);
   }
}

u8 SysTick_getINTstate(void)
{
   return BIT_GET(STK_CTRL, 1);
}

void SysTick_setEnableState(u8 state)
{
   if (state == 1)
   {
      STK_CTRL = BIT_SET(STK_CTRL, 0);
   }
   else
   {
      STK_CTRL = BIT_CLEAR(STK_CTRL, 0);
   }
}

u8 SysTick_getEnableState(void)
{
   return BIT_GET(STK_CTRL, 0);
}

u8 SysTick_setLoadVal(u32 val)
{
   /* if value needs more than 24 bits */
   if (val > (u32)16777215)
   {
      return 0;
   }
   
   STK_LOAD = val;

   return 1;
}

u32 SysTick_getLoadVal(void)
{
   return STK_LOAD;
}

void SysTick_resetValAndZeroFlag(void)
{
   STK_VAL = 0;
}

u32 SysTick_getCurrentVal(void)
{
   return STK_VAL;
}

void SysTick_registerCallBack(SysTickCallBack_t cb)
{
	SysTickCB = cb;
}

void SysTick_deregisterCallBack(void)
{
	SysTickCB = 0;
}

void SysTick_Handler(void)
{
	/* cache the counter value early at entrance for a better accuracy */
	register u32 val = STK_VAL;

	/* call the callback function if it's not empty */
	if (SysTickCB)
	{
		SysTickCB(val);
	}
}
