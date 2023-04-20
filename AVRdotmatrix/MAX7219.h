/*
 * MAX7219.h
 *
 *  Created on: Mar 21, 2023
 *      Author: Seif pc
 */

#ifndef MAX7219_H_
#define MAX7219_H_

/************Includes Section**************/
#include "mcalStdtypes.h"
#include "spi.h"
/************Define Section******************/
#define DIGIT_0  0x01
#define DIGIT_1  0x02
#define DIGIT_2  0x03
#define DIGIT_3  0x04
#define DIGIT_4  0x05
#define DIGIT_5  0x06
#define DIGIT_6  0x07
#define DIGIT_7  0x08
#define DECODE_MODE  0x09
#define INTENSITY_REG  0x0A
#define SCAN_LIM_REG  0x0B
#define SHUTDOWN_REG  0x0C
#define DISPLAY_TEST_REG  0x0F
#define NO_DIGITS 8
#define NO_DIGITS_DOT_MATRIX 8
#define POWER_ON 0x01
#define NORMAL_OP 0x00
#define EXTERNAL_DECODER 0x00
#define INTENSITY_LEVEL7 0x07
#define LCD_MODE_ON

/*********Software Interfaces*******************/
Bool MAX7219_INIT();
Bool MAX7219_SEND_Data(uint8 Address,uint8 Data);
void MAX7219Disp_Number(int32_t data);
void MAX7219Disp_float(float Val,Bool Temp_flag);
#ifndef LCD_MODE_ON
Bool Max7219_Send_DArr_Ddata(uint8 Address,uint8 Data[],uint8 size,Bool *temp_flag,Bool *temp_flag_2);
#else
Bool Max7219_Send_DArr_Ddata(uint8 Address,uint8 Data[],uint8 size);
Bool Max7219_disp_string(char *str);
#endif
void MAX7219Disp_float_num(float Val,Bool Temp_flag,uint32 Num);
Bool MAX7219_INIT_ARR(uint8 no_segs);


#endif /* MAX7219_H_ */
