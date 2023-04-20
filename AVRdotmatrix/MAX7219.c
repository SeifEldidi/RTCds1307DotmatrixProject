/*
 * MAX7219.c
 *
 *  Created on: Mar 21, 2023
 *      Author: Seif pc
 */
#include "MAX7219.h"

uint8 Data_arr[6]={0};
uint8 Data_arr_2[6]={0};
static uint8 MAX721DIG[]={0x7E,0x30,0x6D,0x79,0x33,0x5B,0x5F,0x70,0x7f,0x7b,0x77,0x01,0x4E};

#ifdef LCD_MODE_ON
static uint8 Pattern[][8]={
	{	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 32 Space
	{	0x80,0x80,0x80,0x80,0x80,0x00,0x80,0x00}, // 33 !
	{	0xa0,0xa0,0xa0,0x00,0x00,0x00,0x00,0x00}, // 34 "
	{	0x00,0x50,0xf8,0x50,0x50,0xf8,0x50,0x00}, // 35 #
	{	0x20,0x78,0xa0,0x70,0x28,0xf0,0x20,0x00}, // 36 $
	{	0xc8,0xc8,0x10,0x20,0x40,0x98,0x98,0x00}, // 37 %
	{	0x20,0x50,0x20,0x40,0xa8,0x90,0x68,0x00}, // 38 &
	{	0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00}, // 39 '
	{	0x20,0x40,0x80,0x80,0x80,0x40,0x20,0x00}, // 40 (
	{	0x80,0x40,0x20,0x20,0x20,0x40,0x80,0x00}, // 41 )
	{	0x00,0xa8,0x70,0xf8,0x70,0xa8,0x00,0x00}, // 42 *
	{	0x00,0x20,0x20,0xf8,0x20,0x20,0x00,0x00}, // 43 +
	{	0x00,0x00,0x00,0x00,0x00,0x60,0x60,0xc0}, // 44 ,
	{	0x00,0x00,0x00,0xf8,0x00,0x00,0x00,0x00}, // 45 -
	{	0x00,0x00,0x00,0x00,0x00,0xc0,0xc0,0x00}, // 46 .
	{	0x08,0x08,0x10,0x20,0x40,0x80,0x80,0x00}, // 47 /
	{	0x20,0x50,0x88,0x88,0x88,0x50,0x20,0x00}, // 48 0
	{	0x30,0x50,0x90,0x10,0x10,0x10,0x38,0x00}, // 49 1
	{	0x70,0x88,0x88,0x10,0x20,0x40,0xf8,0x00}, // 50 2
	{	0x70,0x88,0x08,0x30,0x08,0x88,0x70,0x00}, // 51 3
	{	0x10,0x30,0x50,0x90,0xf8,0x10,0x10,0x00}, // 52 4
	{	0xf8,0x80,0xf0,0x08,0x08,0x88,0x70,0x00}, // 53 5
	{	0x38,0x40,0x80,0xf0,0x88,0x88,0x70,0x00}, // 54 6
	{	0xf8,0x88,0x10,0x20,0x20,0x20,0x20,0x00}, // 55 7
	{	0x70,0x88,0x88,0x70,0x88,0x88,0x70,0x00}, // 56 8
	{	0x70,0x88,0x88,0x78,0x08,0x10,0xe0,0x00}, // 57 9
	{	0x00,0xc0,0xc0,0x00,0x00,0xc0,0xc0,0x00}, // 58 :
	{	0x00,0x60,0x60,0x00,0x00,0x60,0x60,0xc0}, // 59 ;
	{	0x10,0x20,0x40,0x80,0x40,0x20,0x10,0x00}, // 60 <
	{	0x00,0x00,0xf0,0x00,0xf0,0x00,0x00,0x00}, // 61 =
	{	0x80,0x40,0x20,0x10,0x20,0x40,0x80,0x00}, // 62 >
	{	0x70,0x88,0x10,0x20,0x20,0x00,0x20,0x00}, // 63 ?
	{	0x70,0x88,0xb8,0xa8,0xa8,0x90,0x40,0x00}, // 64 @
	{	0x20,0x50,0x88,0x88,0xf8,0x88,0x88,0x00}, // 65 A
	{	0xf0,0x88,0x88,0xf0,0x88,0x88,0xf0,0x00}, // 66 B
	{	0x38,0x40,0x80,0x80,0x80,0x40,0x38,0x00}, // 67 C
	{	0xe0,0x90,0x88,0x88,0x88,0x90,0xe0,0x00}, // 68 D
	{	0xf8,0x80,0x80,0xf0,0x80,0x80,0xf8,0x00}, // 69 E
	{	0xf8,0x80,0x80,0xf0,0x80,0x80,0x80,0x00}, // 70 F
	{	0x70,0x88,0x80,0xb8,0x88,0x88,0x70,0x00}, // 71 G
	{	0x88,0x88,0x88,0xf8,0x88,0x88,0x88,0x00}, // 72 H
	{	0xe0,0x40,0x40,0x40,0x40,0x40,0xe0,0x00}, // 73 I
	{	0xf8,0x08,0x08,0x08,0x08,0x88,0x70,0x00}, // 74 J
	{	0x88,0x90,0xa0,0xc0,0xa0,0x90,0x88,0x00}, // 75 K
	{	0x80,0x80,0x80,0x80,0x80,0x80,0xf8,0x00}, // 76 L
	{	0x82,0xc6,0xaa,0x92,0x92,0x92,0x92,0x00}, // 77 M
	{	0x88,0xc8,0xc8,0xa8,0x98,0x98,0x88,0x00}, // 78 N
	{	0x70,0x88,0x88,0x88,0x88,0x88,0x70,0x00}, // 79 O
	{	0xf0,0x88,0x88,0xf0,0x80,0x80,0x80,0x00}, // 80 P
	{	0x70,0x88,0x88,0x88,0xa8,0x90,0x68,0x00}, // 81 Q
	{	0xf0,0x88,0x88,0xf0,0x90,0x88,0x88,0x00}, // 82 R
	{	0x78,0x80,0x80,0x70,0x08,0x08,0xf0,0x00}, // 83 S
	{	0xf8,0x20,0x20,0x20,0x20,0x20,0x20,0x00}, // 84 T
	{	0x88,0x88,0x88,0x88,0x88,0x88,0x70,0x00}, // 85 U
	{	0x88,0x88,0x88,0x88,0x50,0x50,0x20,0x00}, // 86 V
	{	0x82,0x82,0x82,0x92,0x54,0x54,0x28,0x00}, // 87 W
	{	0x88,0x88,0x50,0x20,0x50,0x88,0x88,0x00}, // 88 X
	{	0x88,0x88,0x50,0x50,0x20,0x20,0x20,0x00}, // 89 Y
	{	0xf8,0x08,0x10,0x20,0x40,0x80,0xf8,0x00}, // 90 Z
	{	0xe0,0x80,0x80,0x80,0x80,0x80,0xe0,0x00}, // 91 [
	{	0x80,0x80,0x40,0x20,0x10,0x08,0x08,0x00}, // 92
	{	0xe0,0x20,0x20,0x20,0x20,0x20,0xe0,0x00}, // 93 ]
	{	0x20,0x50,0x88,0x00,0x00,0x00,0x00,0x00}, // 94 ^
	{	0x00,0x00,0x00,0x00,0x00,0x00,0xf8,0x00}, // 95 _
	{	0x80,0x40,0x20,0x00,0x00,0x00,0x00,0x00}, // 96
	{	0x00,0x00,0xf0,0x08,0x78,0x98,0x68,0x00}, // 97 a
	{	0x80,0x80,0xf0,0x88,0x88,0xc8,0xb0,0x00}, // 98 b
	{	0x00,0x00,0x70,0x80,0x80,0x80,0x70,0x00}, // 99 c
	{	0x08,0x08,0x78,0x88,0x88,0x98,0x68,0x00}, // 100 d
	{	0x00,0x00,0x70,0x88,0xf8,0x80,0x70,0x00}, // 101 e
	{	0x30,0x40,0xf0,0x40,0x40,0x40,0x40,0x00}, // 102 f
	{	0x00,0x00,0x78,0x88,0x88,0x78,0x08,0xf0}, // 103 g
	{	0x80,0x80,0xe0,0x90,0x90,0x90,0x90,0x00}, // 104 h
	{	0x40,0x00,0xc0,0x40,0x40,0x40,0xe0,0x00}, // 105 i
	{	0x20,0x00,0x60,0x20,0x20,0x20,0x20,0xc0}, // 106 j
	{	0x80,0x80,0x90,0xa0,0xc0,0xa0,0x90,0x00}, // 107 k
	{	0xc0,0x40,0x40,0x40,0x40,0x40,0xe0,0x00}, // 108 l
	{	0x00,0x00,0xe8,0x54,0x54,0x54,0x54,0x00}, // 109 m
	{	0x00,0x00,0xd0,0x68,0x48,0x48,0x48,0x00}, // 110 n
	{	0x00,0x00,0x70,0x88,0x88,0x88,0x70,0x00}, // 111 o
	{	0x00,0x00,0xf0,0x48,0x48,0x70,0x40,0xe0}, // 112 p
	{	0x00,0x00,0x78,0x90,0x90,0x70,0x10,0x38}, // 113 q
	{	0x00,0x00,0xd0,0x68,0x40,0x40,0xe0,0x00}, // 114 r
	{	0x00,0x00,0x70,0x80,0x60,0x10,0xe0,0x00}, // 115 s
	{	0x40,0xe0,0x40,0x40,0x40,0x40,0x20,0x00}, // 116 t
	{	0x00,0x00,0x90,0x90,0x90,0x90,0x78,0x00}, // 117 u
	{	0x00,0x00,0x88,0x88,0x50,0x50,0x20,0x00}, // 118 v
	{	0x00,0x00,0x88,0x88,0xa8,0x50,0x50,0x00}, // 119 w
	{	0x00,0x00,0x90,0x90,0x60,0x90,0x90,0x00}, // 120 x
	{	0x00,0x00,0x90,0x90,0x90,0x70,0x10,0xe0}, // 121 y
	{	0x00,0x00,0xf8,0x10,0x20,0x40,0xf8,0x00}, // 122 z
	{	0x20,0x40,0x40,0x80,0x40,0x40,0x20,0x00}, // 123 {
	{	0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00}, // 124 |
	{	0x80,0x40,0x40,0x20,0x40,0x40,0x80,0x00}, // 125 }
	{	0x00,0x00,0x00,0x40,0xa8,0x10,0x00,0x00}, // 126 ~
	{	0x60,0x90,0x90,0xa0,0x90,0x90,0xa0,0x00}, // 127 �
	{	0x88,0x20,0x50,0x88,0xf8,0x88,0x88,0x00}, // 128 �
	{	0x88,0x70,0x88,0x88,0x88,0x88,0x70,0x00}, // 129 �
	{	0x88,0x00,0x88,0x88,0x88,0x88,0x70,0x00}, // 130 �
	{	0x50,0x00,0xf0,0x08,0x78,0x98,0x68,0x00}, // 131 �
	{	0x50,0x00,0x70,0x88,0x88,0x88,0x70,0x00}, // 132 �
	{	0x50,0x00,0x90,0x90,0x90,0x90,0x78,0x00}, // 133 �
	{	0x60,0x90,0x90,0x60,0x00,0x00,0x00,0x00}, // 134 �
};
#endif

static void CLEAR_DISPLAY_Arr();
static uint8_t no_digits(int32_t data);
static Bool Max7219_Send_DArr(uint8 Address,uint8 Data,uint8 size);

Bool MAX7219_INIT()
{
	Bool ret=E_OK;
	MAX7219_SEND_Data(DECODE_MODE,EXTERNAL_DECODER);
	MAX7219_SEND_Data(INTENSITY_REG,INTENSITY_LEVEL7);
	MAX7219_SEND_Data(SCAN_LIM_REG,NO_DIGITS-1);
	MAX7219_SEND_Data(SHUTDOWN_REG,POWER_ON);
	MAX7219_SEND_Data(DISPLAY_TEST_REG,NORMAL_OP);
	return ret;
}

Bool MAX7219_INIT_ARR(uint8 no_segs)
{
	Bool ret = E_OK;
	Max7219_Send_DArr(DECODE_MODE, EXTERNAL_DECODER,no_segs);
	Max7219_Send_DArr(INTENSITY_REG, INTENSITY_LEVEL7,no_segs);
	Max7219_Send_DArr(SCAN_LIM_REG, NO_DIGITS_DOT_MATRIX - 1,no_segs);
	Max7219_Send_DArr(SHUTDOWN_REG, POWER_ON,no_segs);
	Max7219_Send_DArr(DISPLAY_TEST_REG, NORMAL_OP,no_segs);
	return ret;
}

static Bool Max7219_Send_DArr(uint8 Address,uint8 Data,uint8 size)
{
	Bool ret=E_OK;
	uint8 Seg_no=0;
	SPI_CLEAR_SS();
	for(Seg_no=0;Seg_no<=size-1;Seg_no++)
	{
		ret=SPI_SEND_blocking(Address);
		ret=SPI_SEND_blocking(Data);
	}
	SPI_SET_SS();
	return ret;
}

#ifndef LCD_MODE_ON
Bool Max7219_Send_DArr_Ddata(uint8 Address,uint8 Data[],uint8 size,Bool *temp_flag,Bool *temp_flag_2)
{
	Bool ret = E_OK;
	uint8 Seg_no = 0;
	SPI_CLEAR_SS();
	for (Seg_no = 0; Seg_no <= size - 1; Seg_no++) {
		ret = SPI_SEND_blocking(Address);
		if(*temp_flag==1&&Seg_no==size-1)
		{
			*temp_flag=0;
			ret = SPI_SEND_blocking(MAX721DIG[Data[Seg_no]]|0x80);
		}
		else if(*temp_flag_2==1&&Seg_no==1)
		{
			*temp_flag_2 = 0;
			ret = SPI_SEND_blocking(MAX721DIG[12]);
		}
		else
			ret = SPI_SEND_blocking(MAX721DIG[Data[Seg_no]]);
	}
	SPI_SET_SS();
	return ret;
}
#else
Bool Max7219_Send_DArr_Ddata(uint8 Address,uint8 Data[],uint8 size)
{
	Bool ret = E_OK;
	uint8 Seg_no = 0;
	SPI_CLEAR_SS();
	for (Seg_no = 0; Seg_no <= size - 1; Seg_no++) {
		ret = SPI_SEND_blocking(Address);
		ret = SPI_SEND_blocking(MAX721DIG[Data[Seg_no]]);
	}
	SPI_SET_SS();
	return ret;
}
uint8 diff;

Bool Max7219_disp_string(char *str)
{
	Bool E_state=E_OK;
	uint8 len=0;
	uint8 Address_Cnt=1;
	uint8 Digit_Cnt=0;
	uint8 Str_Cnt=0;
	uint8 Max=0;
	while(*(str+len)!='\0')//calculate length of string
		len++;
	if(len<NO_DIGITS)
		Max=len-1;
	else
		Max=NO_DIGITS-1;
	for(Address_Cnt=1;Address_Cnt<=8;Address_Cnt++)
	{
		SPI_CLEAR_SS();
		for(Digit_Cnt=0;Digit_Cnt<=Max;Digit_Cnt++)
		{
			E_state = SPI_SEND_blocking(Address_Cnt); //turn on first row
			diff = Pattern[str[len - Str_Cnt - 1] - 32][Address_Cnt - 1];
			E_state = SPI_SEND_blocking(
					Pattern[str[len - Str_Cnt - 1] - 32][Address_Cnt - 1]);
			Str_Cnt++;
		}
		Str_Cnt=0;
		SPI_SET_SS();
	}
	return E_state;
}
#endif

static void Convert_digs(int32 Num,uint8 Arr[])
{
	int8 size=0;
	while(Num!=0)
	{
		Arr[size++]=Num%10;
		Num/=10;
	}
}

void MAX7219Disp_float_num(float Val,Bool Temp_flag,uint32 Num)
{
	Bool flag=0,flag_2=0;
	int8 Counter=DIGIT_5;
	uint8 Arr[2];
	int32 int_val=Val*1000;

	Convert_digs(Num,Data_arr);
	Convert_digs(int_val,Data_arr_2);
	CLEAR_DISPLAY_Arr();
	for(Counter=DIGIT_5;Counter>=1;Counter--)
	{
		Arr[0] = Data_arr[DIGIT_5-Counter];
		Arr[1] = Data_arr_2[DIGIT_5-Counter];
		if(Counter==DIGIT_2)
			flag=1;
		if(Counter==DIGIT_5)
			flag_2=1;
#ifndef LCD_MODE_ON
		Max7219_Send_DArr_Ddata(Counter, Arr, 2,&flag,&flag_2);
#endif
	}
}

Bool MAX7219_SEND_Data(uint8 Address,uint8 Data)
{
	Bool ret;
	SPI_CLEAR_SS();
	ret=SPI_SEND_blocking(Address);
	ret=SPI_SEND_blocking(Data);
	SPI_SET_SS();
	return ret;
}

static void CLEAR_DISPLAY()
{
	MAX7219_SEND_Data(DIGIT_7, MAX721DIG[0]);
	MAX7219_SEND_Data(DIGIT_6, MAX721DIG[0]);
	MAX7219_SEND_Data(DIGIT_5, MAX721DIG[0]);
	MAX7219_SEND_Data(DIGIT_4, MAX721DIG[0]);
	MAX7219_SEND_Data(DIGIT_3, MAX721DIG[0]);
	MAX7219_SEND_Data(DIGIT_2, MAX721DIG[0]);
	MAX7219_SEND_Data(DIGIT_1, MAX721DIG[0]);
	MAX7219_SEND_Data(DIGIT_0, MAX721DIG[0]);
}

static void CLEAR_DISPLAY_Arr()
{
	Max7219_Send_DArr(DIGIT_7, MAX721DIG[0],2);
	Max7219_Send_DArr(DIGIT_6, MAX721DIG[0],2);
	Max7219_Send_DArr(DIGIT_5, MAX721DIG[0],2);
	Max7219_Send_DArr(DIGIT_4, MAX721DIG[0],2);
	Max7219_Send_DArr(DIGIT_3, MAX721DIG[0],2);
	Max7219_Send_DArr(DIGIT_2, MAX721DIG[0],2);
	Max7219_Send_DArr(DIGIT_1, MAX721DIG[0],2);
	Max7219_Send_DArr(DIGIT_0, MAX721DIG[0],2);
}

static uint8_t no_digits(int32_t data)
{
	int len=0;
	while(data!=0)
	{
		data/=10;
		len++;
	}
	return len;
}


void MAX7219Disp_Number(int32_t data)
{
		Bool neg_flag=0;
		if(data==0)
			CLEAR_DISPLAY();
		else if(data<0)
		{
			neg_flag=1;
			data*=-1;
		}
		if(data!=0)
		{
			CLEAR_DISPLAY();
			uint8_t dig = no_digits(data);
			uint8_t Cnt = 0;
			if (neg_flag == 1) {
				MAX7219_SEND_Data(dig + 1, MAX721DIG[11]);
			}
			for (Cnt = 0; Cnt <= dig - 1; Cnt++) {
				MAX7219_SEND_Data(Cnt + 1, MAX721DIG[data % 10]);
				data /= 10;
			}
		}
}

void MAX7219Disp_float(float Val,Bool Temp_flag)
{
	int32 int_val=Val*1000;
	CLEAR_DISPLAY();
	uint8_t dig = no_digits(int_val);
	uint8_t Cnt = 0;
	for (Cnt = 0; Cnt <= dig - 1; Cnt++) {
		if(Cnt==0&&Temp_flag)
			MAX7219_SEND_Data(Cnt + 1, MAX721DIG[12]);
		else if(Cnt==3)
			MAX7219_SEND_Data(Cnt + 1, (MAX721DIG[(int_val % 10)]|0x80));
		else
			MAX7219_SEND_Data(Cnt + 1, MAX721DIG[int_val % 10]);
		int_val /= 10;
	}
}

