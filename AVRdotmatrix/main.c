#include "main.h"

SPI_CONFIG_t SPI_t={
		.SPI_MSTR_SLAVE_set=SPI_MSTR_MODE,
		.SPI_Shift_dir_set=MSB_FIRST_SHIFT,
		.SPI_CLOCK_phase_set=CLOCK_PHASE_SAMPLE_TRAILING,
		.SPI_CLOCK_polarity_set=CLOCK_POLARITY_RSEDG_FEDG,
		.CLK_set=SPI_FOSC_4,
};

I2C_CONFIG_t I2C_t={
		.SCL_FREQ=I2C_STANDARD_MODE,
		.Prescaler_Freq=TWPS_PRESCALER_1,
};

int main()
{
	uint8 Str_disp[9];
	SPI_INIT(&SPI_t);
	I2C_INIT(&I2C_t);
	MAX7219_INIT_ARR(NO_SEGS);
	RTCDS1307_SET_TIME(MODE_24H,12,36,5);
	while(1)
	{
		RTCDS1307_TIME_STR(Str_disp);
		Max7219_disp_string(Str_disp);
	}
	return 0;
}



