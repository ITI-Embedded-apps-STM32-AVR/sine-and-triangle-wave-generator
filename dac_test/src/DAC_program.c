#include "STD_TYPES.h"
#include "BIT_MAN.h"
#include "DAC_Config.h"
#include "DAC_interface.h"
#include "DIO_interface.h"

/* how many members in the port/pin array are considered 1 unit,
 * in this case 2 because a pin and a port are considered 1 unit */
#define PORT_PIN_ARRAY_STEP 2

typedef struct
{
	u8* port_pin_in; /* LSB first */
	u8 bitCount;
} DAC_t;

DAC_t dacs[DAC_DEVICES_COUNT];

void DAC_Init(u8 idx, void* port_pin_in, u8 bitCount)
{
	dacs[idx].port_pin_in = port_pin_in;
	dacs[idx].bitCount    = bitCount;

	/* cache the array address for faster access */
	register u8* const port_pin_in_cahced = dacs[idx].port_pin_in;

	for (u8 i = 0; i < bitCount; i++) /* foreach bit */
	{
		/* each bit has a corresponding port and pin (2 consequent members in the port/pin array)
		 * set the mode of the pin to output push-pull with the lowest pin-frequency (save power) */
		DIO_setPinMode(port_pin_in_cahced[PORT_PIN_ARRAY_STEP * i + 0], port_pin_in_cahced[PORT_PIN_ARRAY_STEP * i + 1], DIO_PIN_MODE_OUT_PUSH_PULL_2MHZ);
		/* initially each pin is set to low */
		DIO_setPinVal(port_pin_in_cahced[PORT_PIN_ARRAY_STEP * i + 0], port_pin_in_cahced[PORT_PIN_ARRAY_STEP * i + 1], 0);
	}
}

void DAC_WriteValue(u8 idx, u64 val)
{
	/* cache the array address for faster access */
	register u8* const port_pin_in_cahced = dacs[idx].port_pin_in;

	for (u8 i = 0; i < dacs[idx].bitCount; i++) /* foreach bit */
	{
		DIO_setPinVal(port_pin_in_cahced[PORT_PIN_ARRAY_STEP * i + 0],
                      port_pin_in_cahced[PORT_PIN_ARRAY_STEP * i + 1],
                      BIT_GET(val, i));
	}
}

