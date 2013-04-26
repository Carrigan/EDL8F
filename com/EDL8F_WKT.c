#include "LPC8xx.h"

void wkt_setup()
{
	// Set bit 9 in the SYSAHBCLKCTRL register to enable the clock
	LPC_SYSCON -> SYSAHBCLKCTRL |= (1ul << 9);
	
	// Clear the WKT reset in PRESETCTRL
	LPC_SYSCON->PRESETCTRL &= ~(1ul << 9);
	LPC_SYSCON->PRESETCTRL |= (1ul << 9);
	
	// Enable low power oscillator in the PMU
	LPC_PMU -> DPDCTRL |= 1ul << 2;
	
	// Set up the WKT Timer, but do not start it.
	CTRL = 0x00000005;
}

void wkt_begin(unsigned int pPeriodInTicks)
{
	WKT->COUNT = pPeriodInTicks;
}

void wkt_stop()
{
	WKT->CTRL |= 0x00000004;
}
