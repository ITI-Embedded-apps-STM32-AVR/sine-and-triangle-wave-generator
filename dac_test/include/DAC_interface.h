#ifndef DAC_INTERFACE_H_
#define DAC_INTERFACE_H_

void DAC_Init(u8 idx, void* port_pin_in, u8 bitCount);
void DAC_WriteValue(u8 idx, u64 val);


#endif /* DAC_INTERFACE_H_ */
