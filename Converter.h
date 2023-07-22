


#ifndef CONVERTER_H_
#define CONVERTER_H_


	
typedef enum{
	HELLO=0,
	BIN_NUM,
	DEC_NUM,
	HEX_NUM,
	CHOICE
}CONVERTER_t;

void CONVERTER_Init(void);

u8 CONVERTER_GetInputBinary(void);
u8 CONVERTER_GetInputHex(void);
u8 CONVERTER_GetInputDec(void);
CONVERTER_t CONVERTER_GetInputChoice(void);
u8 CONVERTER_GetInput(CONVERTER_t input_t);

void CONVERTER_UI(CONVERTER_t output_t,u8 num,u8 output_num);

void CONVERTER_APP(void);

#endif /* CONVERTER_H_ */