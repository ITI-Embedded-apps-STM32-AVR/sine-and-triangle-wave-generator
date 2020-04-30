#ifndef SysTick_INTERFACE_H_
#define SysTick_INTERFACE_H_

#define SYSTICK_CLOCK_SOURCE_AHB_DIV8 0
#define SYSTICK_CLOCK_SOURCE_AHB      1

typedef void (*SysTickCallBack_t)(u32);

void SysTick_init(void);

u8 SysTick_isReachedZero(void);
void SysTick_resetZeroFlag(void);

u8 SysTick_setClockSource(u8 clkSrc);
u8 SysTick_getClockSource(void);

void SysTick_setINTstate(u8 state);
u8 SysTick_getINTstate(void);

void SysTick_setEnableState(u8 state);
u8 SysTick_getEnableState(void);

u8 SysTick_setLoadVal(u32 val);
u32 SysTick_getLoadVal(void);

void SysTick_resetValAndZeroFlag(void);
u32 SysTick_getCurrentVal(void);

void SysTick_registerCallBack(SysTickCallBack_t cb);
void SysTick_deregisterCallBack(void);

#endif /* SysTick_INTERFACE_H_ */
