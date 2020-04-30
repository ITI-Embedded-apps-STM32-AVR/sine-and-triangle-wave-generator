// libs
#include "STD_TYPES.h"
#include "BIT_MAN.h"
#include "Delay_interface.h"
// MCAL
#include "RCC_interface.h"
#include "SysTick_interface.h"
// HAL
#include "DAC_interface.h"

#include "diag/Trace.h"

u8 port_pin[] = {
		'A', 0,
		'A', 1,
		'A', 2,
		'A', 3,
		'A', 4,
		'A', 5,
		'A', 6,
		'A', 7,
		'A', 8,
		'A', 9,
		'A', 10,
		'A', 11,
		'A', 12,
		'B', 5,
		'B', 6,
		'B', 7,
};


const u16 sinwave[] = {
   32767.5,
   34824.98834867678,
   36874.35673081834,
   38907.517225687734,
   40916.44587767438,
   42893.21436318109,
   44830.021280095185,
   46719.22293635852,
   48553.36351612795,
   50325.20450447427,
   52027.75325449361,
   53654.29058409019,
   55198.397293518305,
   56653.979499031106,
   58015.29268265567,
   59276.96436318109,
   60434.01529888728,
   61481.8791383373,
   62416.4204416803,
   63233.951001343274,
   63931.24439770145,
   64505.54873228242,
   64954.5974882523,
   65276.61847532215,
   65470.34082377339,
   65535.0,
   65470.34082377339,
   65276.61847532216,
   64954.59748825231,
   64505.54873228242,
   63931.24439770145,
   63233.951001343274,
   62416.4204416803,
   61481.879138337295,
   60434.01529888727,
   59276.96436318109,
   58015.29268265567,
   56653.9794990311,
   55198.397293518305,
   53654.29058409019,
   52027.75325449362,
   50325.204504474284,
   48553.36351612795,
   46719.22293635853,
   44830.02128009519,
   42893.21436318109,
   40916.44587767439,
   38907.517225687734,
   36874.35673081835,
   34824.98834867678,
   32767.500000000007,
   30710.011651323224,
   28660.64326918166,
   26627.482774312262,
   24618.554122325626,
   22641.785636818917,
   20704.978719904815,
   18815.777063641497,
   16981.63648387204,
   15209.795495525734,
   13507.246745506402,
   11880.709415909812,
   10336.602706481703,
   8881.020500968896,
   7519.707317344322,
   6258.035636818913,
   5100.984701112714,
   4053.1208616627,
   3118.5795583196964,
   2301.0489986567204,
   1603.7556022985566,
   1029.4512677175776,
   580.4025117476923,
   258.3815246778498,
   64.65917622661169,
   0.0,
   64.65917622661169,
   258.3815246778462,
   580.4025117476923,
   1029.4512677175812,
   1603.755602298553,
   2301.048998656717,
   3118.5795583196928,
   4053.1208616627073,
   5100.984701112725,
   6258.035636818906,
   7519.707317344315,
   8881.020500968878,
   10336.602706481684,
   11880.709415909812,
   13507.24674550638,
   15209.795495525712,
   16981.63648387202,
   18815.77706364147,
   20704.978719904815,
   22641.785636818902,
   24618.554122325604,
   26627.482774312266,
   28660.643269181644,
   30710.011651323228,
};

 void dac_triangleWave_cb(u32 val);
 void dac_sinWave_cb(u32 val);

 void main(void)
 {
	 /* init clocks */
	 RCC_init();

	 RCC_setClockPrescaler(RCC_PCLK1, RCC_APB_PRESCALER_AHB_DIV2);
	 RCC_setClockPrescaler(RCC_PCLK2, RCC_APB_PRESCALER_AHB_DIV2);

	 RCC_setClockState(RCC_CLOCK_HSE, 1);
	 RCC_setPLLHSEdiv2(0);
	 RCC_setPLLmul(RCC_PLL_MUL5); /* 40MHz */
	 RCC_setPLLsource(RCC_PLL_SOURCE_HSE);
	 RCC_setClockState(RCC_CLOCK_PLL, 1);
	 RCC_changeSysClock(RCC_CLOCK_PLL);

	 /* enable clocks for ports A & B */
	 RCC_setPeripheralClock(RCC_BUS_APB2, RCC_PERI_GPIOA, 1);
	 RCC_setPeripheralClock(RCC_BUS_APB2, RCC_PERI_GPIOB, 1);

	 DAC_Init(0, port_pin, 8);

	 SysTick_init();

	 /* freq = 5MHz, tick = 0.2us */
    SysTick_setClockSource(SYSTICK_CLOCK_SOURCE_AHB_DIV8);

	 /* 1ms ==> ~10Hz triangle wave */
    SysTick_registerCallBack(dac_triangleWave_cb);
	 SysTick_setLoadVal(5000 - 1);

	 /* 1ms ==> ~10Hz sin wave */
    //SysTick_registerCallBack(dac_sinWave_cb);
	 //SysTick_setLoadVal(5000 - 1);

	 SysTick_setINTstate(1);
	 SysTick_setEnableState(1);

	 //DAC_WriteValue(0, 2*19859); // 2v

	 while (1)
	 {

	 }
 }

 void dac_triangleWave_cb(u32 val) /* 10 Hz signal, 1000Hz sampling */
{
   (void)val; /* prevent compiler warning (acknowledge it's an unsed variale) */

   static u8 dir = 0;
   static u16 i = 0;

   DAC_WriteValue(0, i);

   if (dir == 0)
   {
      i += 1310;
   }
   else
   {
      i -= 1310;
   }

   if (i == 65500)
   {
   	dir = 1;
   }
   else if (i == 0)
   {
      dir = 0;
   }
}

void dac_sinWave_cb(u32 val) /* 10 Hz signal, 1000Hz sampling */
{
   (void)val; /* prevent compiler warning (acknowledge it's an unsed variale) */

   static u8 i = 0;

   DAC_WriteValue(0, sinwave[i]);

   i++;

   if (i == 100)
   {
      i = 0;
   }
}
