#ifndef ECC_MUL_H
#define ECC_MUL_H

#include "relic_fb.h"

// Hardcoded constants for Yiqun's chip.

#define ADDR_OFFSET 0x00002000  //dra = 0d592

#define ADDR_A 0x00005500  //dra = 0d592
#define ADDR_B 0x00005600  //drb = 0d608
#define ADDR_C 0x00005700  //drc = 0d624
#define ADDR_T 0x00005800  //drt = 0d640
#define ADDR_IR 0x00006800  //drir = 0d896 
#define ADDR_IR_T 0x00006900  //drirt = 0d912

#define ADDR_REC_FIN 0x0010000

/*
#define ADDR_A 0x00002500  //dra = 0d592
#define ADDR_B 0x00002600  //drb = 0d608
#define ADDR_C 0x00002700  //drc = 0d624
#define ADDR_T 0x00002800  //drt = 0d640
#define ADDR_IR 0x00003800  //drir = 0d896 
#define ADDR_IR_T 0x00003900  //drirt = 0d912
*/

#define IDRA   ((((unsigned int)ADDR_A) >> 8 ) & 0xFF)
#define IDRB   ((((unsigned int)ADDR_B) >> 8 ) & 0xFF)
#define IDRC   ((((unsigned int)ADDR_C) >> 8 ) & 0xFF)
#define IDRT   ((((unsigned int)ADDR_T) >> 8 ) & 0xFF)
#define IDRIR  ((((unsigned int)ADDR_IR) >> 8 ) & 0xFF)
#define IDRIRT ((((unsigned int)ADDR_IR_T) >> 8 ) & 0xFF)


#define DECODER 0xA0000140
#define NUM_FOR   ((int)(FB_DIGS * FB_DIGIT/4 * 10-1))  // - ((int)((256*2-FB_POLYN)/4))*10))
#define NUM_PLN_Minus1  ((int)(FB_POLYN/512))

#define FB_MOD 		((int)(FB_BITS % FB_DIGIT))


// Shift bits 
#define SHIFT_BIT ((int)(FB_POLYN % 32))

//void LIM_mulrdc(volatile int *addr_a, volatile int *addr_c);
void LIM_mulrdc();

void LIM_mulrdc_single(volatile int *addr_a, volatile int *addr_b, volatile int *addr_c, uint8_t Idrb, uint8_t Idrc, uint8_t Idrt, uint8_t Idrir, uint8_t Idrirt); 

void LIM_addr_ir_set();

#endif
