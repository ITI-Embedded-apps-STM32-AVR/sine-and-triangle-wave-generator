#ifndef SysTick_REGISTERS_H_
#define SysTick_REGISTERS_H_

#define SYSTICK_BASE  0xE000E010

#define STK_CTRL  (*((volatile u32*)(SYSTICK_BASE + 0x00)))
#define STK_LOAD  (*((volatile u32*)(SYSTICK_BASE + 0x04)))
#define STK_VAL   (*((volatile u32*)(SYSTICK_BASE + 0x08)))
#define STK_CALIB (*((volatile const u32*)(SYSTICK_BASE + 0x0C)))

#endif /* SysTick_REGISTERS_H_ */
