
#include "StdTypes.h"
#include "Utils.h"
#define  F_CPU   8000000
#include <util/delay.h>

#include "KeyPad_Interface.h"
#include "LCD_Interface.h"

#include "Converter.h"

void CONVERTER_Init(void)
{
	
}

u8 CONVERTER_GetInputBinary(void)
{
	u8 num=0,bit_num=0,input=0,flag=0;
	num=KEYPAD_GetKey();
	while ((num!='X') && (num!='='))
	{
		if (num!=NO_KEY && (bit_num<8))
		{
			
			if (num=='1')
			{
				if (flag==0)
				{
					LCD_WriteString((c8*)"        ");
					LCD_GoTo(line1,3);
				}
				flag=1;
				SET_BIT(input,(7-bit_num));
				LCD_WriteChar(num);
				bit_num++;
			}
			else if (num=='0')
			{
				if (flag==0)
				{
					LCD_WriteString((c8*)"        ");
					LCD_GoTo(line1,3);
				}
				flag=1;
				LCD_WriteChar(num);
				bit_num++;
			}
		}
		num=KEYPAD_GetKey();
	}
	if (num=='X')
	{
		return num;
	}
	else
	{
		return input;
	}
	
}
u8 CONVERTER_GetInputHex(void)
{
	u8 num=0,input=0,flag=0;
	s8 nipple_num=1;
	num=KEYPAD_GetKey();
	while ((num!='X') && (num!='='))
	{
		if (num!=NO_KEY && (nipple_num>=0))
		{
			if (flag==0)
			{
				LCD_WriteString((c8*)"        ");
				LCD_GoTo(line1,3);
			}
			flag=1;
			if (num>='0' && num<='9')
			{
				LCD_WriteChar(num);
				num=num-'0';
				input=input|(num<<(nipple_num*4));
				nipple_num--;
			}
			else if (num>='A' && num<='F')
			{
				LCD_WriteChar(num);
				num=(num-'A') + 10;
				input=input|(num<<(nipple_num*4));
				nipple_num--;
			}
		}
		num=KEYPAD_GetKey();
	}
	if (num=='X')
	{
		return num;
	}
	else
	{
		return input;
	}
}

u8 CONVERTER_GetInputDec(void)
{
	u8 num=0,input=0,flag=0;
	num=KEYPAD_GetKey();
	while ((num!='X') && (num!='='))
	{
		if (num!=NO_KEY)
		{
			if (num>='0' && num<='9')
			{
				if (flag==0)
				{
					LCD_WriteString((c8*)"        ");
					LCD_GoTo(line1,3);
				}
				flag=1;
				LCD_WriteChar(num);
				input=input*10+(num-'0');
			}
			
		}
		num=KEYPAD_GetKey();
	}
	if (num=='X')
	{
		return num;
	}
	else
	{
		return input;
	}
}
CONVERTER_t CONVERTER_GetInputChoice(void)
{
	u8 input=0,choice_flag=0;
	CONVERTER_t choice;
	input=KEYPAD_GetKey();
	while (choice_flag==0)
	{
		if (input!=NO_KEY)
		{
			switch (input)
			{
				case '1':
				choice = BIN_NUM;
				choice_flag++;
				break;
				case '2':
				choice = DEC_NUM;
				choice_flag++;
				break;
				case '3':
				choice = HEX_NUM;
				choice_flag++;
				break;
			}
		}
		input=KEYPAD_GetKey();
	}
	return choice;
}
u8 CONVERTER_GetInput(CONVERTER_t input_t)
{
	u8 num=0;
	switch (input_t)
	{
		case BIN_NUM:
		num = CONVERTER_GetInputBinary();
		break;
		case DEC_NUM:
		num = CONVERTER_GetInputDec();
		break;
		case HEX_NUM:
		num = CONVERTER_GetInputHex();
		break;
		case CHOICE:
		num = CONVERTER_GetInputChoice();
		break;
	}

	return num;
}

void CONVERTER_UI(CONVERTER_t output_t,u8 num,u8 output_num)
{
	switch(output_t)
	{
		case HELLO:
		LCD_Clear();
		LCD_WriteStringGoto(line1,0,(c8*)"HELLO,CONVERTER");
		LCD_WriteStringGoto(line2,0,(c8*)"BY:AHMED MOSTAFA");
		_delay_ms(1000);
		LCD_Clear();
		break;
		case CHOICE:
		if (num==0)
		{
			LCD_Clear();
			LCD_WriteStringGoto(line1,0,(c8*)"Convert From....");
			LCD_WriteStringGoto(line2,0,(c8*)"1-BIN2-DEC3-HEX");
		}
		else if (num==1)
		{
			LCD_Clear();
			LCD_WriteStringGoto(line1,0,(c8*)"Convert TO....");
			LCD_WriteStringGoto(line2,0,(c8*)"1-BIN2-DEC3-HEX");
		}
		break;
		case BIN_NUM:
		LCD_ClearPosition(num,0,15);
		LCD_WriteStringGoto(num,0,(c8*)"B: ");
		break;
		case DEC_NUM:
		LCD_ClearPosition(num,0,15);
		LCD_WriteStringGoto(num,0,(c8*)"D: ");
		break; 
		case HEX_NUM:
		LCD_ClearPosition(num,0,15);
		LCD_WriteStringGoto(num,0,(c8*)"H: ");
		break;
	}
	if ((num==1))
	{
		switch(output_t)
		{
			case BIN_NUM:
			LCD_WriteBinary(output_num);
			break;
			case DEC_NUM:
			LCD_WriteNumber(output_num);
			break;
			case HEX_NUM:
			LCD_WriteHex(output_num);
			break;
		}
	}
	LCD_GoTo(line1,3);
}

void CONVERTER_APP(void)
{
	CONVERTER_t choice1,choice2;
	u8 num=0;
	static u8 flag=0;
	if (flag==0)
	{
		CONVERTER_UI(HELLO,0,0);
		flag++;
	}
	CONVERTER_UI(CHOICE,0,0);
	choice1 = CONVERTER_GetInput(CHOICE);
	CONVERTER_UI(CHOICE,1,0);
	choice2 = CONVERTER_GetInput(CHOICE);
	CONVERTER_UI(choice1,0,0);
	CONVERTER_UI(choice2,1,0);
	while (num!='X')
	{
		num = CONVERTER_GetInput(choice1);
		CONVERTER_UI(choice2,1,num);

	}
	
}