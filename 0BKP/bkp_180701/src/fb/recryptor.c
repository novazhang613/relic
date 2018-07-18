#include "relic_conf.h"
#include "recryptor.h"

// NEED UPDATE FOR DIFFERENT BANKS!!!

void LIM_mulrdc(volatile int *addr_a, volatile int *addr_b, volatile int *addr_c, uint8_t Idrb, uint8_t Idrc, uint8_t Idrt, uint8_t Idrir, uint8_t Idrirt) { 
//void LIM_mulrdc(volatile int *addr_a, int *addr_b, volatile int *addr_c, uint8_t Idrb, uint8_t Idrc, uint8_t Idrt, uint8_t Idrir, uint8_t Idrirt) { 

/*
	// DEBUG
	volatile int* addr_debug = (int*) 0x4a20;
	*(addr_debug) = Idrt; 
*/
	volatile int* decoder = (int*)DECODER;

	//int* addr_ir =(int*)((unsigned int)(Idrir) << 8); 	

		int i,j;
		uint8_t u;

		// the length of c !!! needs to set here !!! if not set, will get x for the overflow bits
		// write c to 0 : addr 0d616 ~ 0d623
		for (i=0;i<FB_DIGS;i++) {
			addr_c[i] = 0x0; 
		}

	// # banks
	#if FB_POLYN == 163
	uint8_t banks = 1; // 6??
	#endif 
	#if FB_POLYN == 233
	uint8_t banks = 1;
	#endif 
	#if FB_POLYN == 283
	uint8_t banks = 3;
	#endif 
	#if FB_POLYN == 409
	uint8_t banks = 7;
	#endif 

	//**************************/
	// precompute table t[0] = 0
	//**************************/
		
		// precompute table t[0] = 0
		// copy from t[0] = c = 0
		*(decoder) = Idrc + (Idrt<<16) + (1<<23) + (4<<24) + (banks<<28); 

		// ADVANCED precomput for ir_t[0]=0
		// copy from ir_t[0] = c = 0
		*(decoder) = Idrc + (Idrirt<<16) + (1<<23) + (4<<24) + (banks<<28); 

		// precompute table t[1] = b
		*(decoder) = Idrb + ((Idrt+1)<<16) + (1<<23) + (4<<24) + (banks<<28); 
		// precompute table t[2] = t[1] << 1
		*(decoder) = Idrb + ((Idrt+2)<<16) + (1<<23) + (6<<24) + (banks<<28); 

		// t[2] = t[2] ^ ir_t[u]
		//u = ( *(addr_b + 28) >> 8) & 0x1; //grab the first bit // Another option is to use addr_t
		u = (addr_b[FB_DIGS-1] >> (FB_MOD-1)) & 0x1;  
		if (u==1) {
				*(decoder) =(Idrt+2) + (Idrir<<8) + ((Idrt+2)<<16) + (1<<23) + (3<<24) + (banks<<28); 
		}
		// else if u ==0, no need for xor 


		// precompute table t[3] = t[1] ^ t[2]
		*(decoder) = (Idrt+2) + ((Idrt+1)<<8) + ((Idrt+3)<<16) + (1<<23) + (3<<24) + (banks<<28); 

		// precompute table t[4] = t[2] << 1
		*(decoder) = (Idrt+2) + ((Idrt+4)<<16) + (1<<23) + (6<<24) + (banks<<28); 

		// t[4] = t[4] ^ ir_t[u]
		u = (addr_b[FB_DIGS-1] >> (FB_MOD-2)) & 0x1; // grab the 2nd bit  
		if (u==1) {
				*(decoder) = (Idrt+4) + ((Idrir)<<8) + ((Idrt+4)<<16) + (1<<23) + (3<<24) + (banks<<28); 
		}
		// else if u ==0, no need for xor 

		// precompute table t[5] = t[1] ^ t[4]
		*(decoder) = (Idrt+4) + ((Idrt+1)<<8) + ((Idrt+5)<<16) + (1<<23) + (3<<24) + (banks<<28); 

		// use this xor instead of shift, to avoid increased 1 bit !!!
		// precompute table t[6] = t[2] ^ t[4] 
		*(decoder) = (Idrt+4) + ((Idrt+2)<<8) + ((Idrt+6)<<16) + (1<<23) + (3<<24) + (banks<<28); 

		// precompute table t[7] = t[1] ^ t[6]
		*(decoder) = (Idrt+6) + ((Idrt+1)<<8) + ((Idrt+7)<<16) + (1<<23) + (3<<24) + (banks<<28); 

		// precompute table t[8] = t[4] << 1
		*(decoder) = (Idrt+4) + ((Idrt+8)<<16) + (1<<23) + (6<<24) + (banks<<28); 

		// t[8] = t[8] ^ ir_t[u]
		u = (addr_b[FB_DIGS-1] >> (FB_MOD-3)) & 0x1; // grab the 3rd bit  
		if (u==1) {
				*(decoder) = (Idrt+8) + ((Idrir)<<8) + ((Idrt+8)<<16) + (1<<23) + (3<<24) + (banks<<28);
		}
				// else if u ==0, no need for xor 

		// precompute table t[9] = t[1] ^ t[8]
		*(decoder) = (Idrt+8) + ((Idrt+1)<<8) + ((Idrt+9)<<16) + (1<<23) + (3<<24) + (banks<<28); 

		// precompute table t[10] = t[2] ^ t[8]
		*(decoder) = (Idrt+8) + ((Idrt+2)<<8) + ((Idrt+10)<<16) + (1<<23) + (3<<24) + (banks<<28);  

		// precompute table t[11] = t[1] ^ t[10]
		*(decoder) = (Idrt+10) + ((Idrt+1)<<8) + ((Idrt+11)<<16) + (1<<23) + (3<<24) + (banks<<28);  

		// precompute table t[12] = t[4] ^ t[8]
		*(decoder) = (Idrt+8) + ((Idrt+4)<<8) + ((Idrt+12)<<16) + (1<<23) + (3<<24) + (banks<<28); 

		// precompute table t[13] = t[1] ^ t[12]
		*(decoder) = (Idrt+12) + ((Idrt+1)<<8) + ((Idrt+13)<<16) + (1<<23) + (3<<24) + (banks<<28); 

		// use this xor instead of shift, to avoid increased 1 bit !!!
		// why this is wrong !!! precompute table t[14] = t[1] ^ t[13] 
		// precompute table t[14] = t[2] ^ t[12] 
		*(decoder) = (Idrt+12) + ((Idrt+2)<<8) + ((Idrt+14)<<16) + (1<<23) + (3<<24) + (banks<<28);

		// precompute table t[15] = t[1] ^ t[14]
		*(decoder) = (Idrt+14) + ((Idrt+1)<<8) + ((Idrt+15)<<16) + (1<<23) + (3<<24) + (banks<<28); 

	//**************************/
	// precompute table ir_t[0] = 0
	//**************************/
		// precompute table t[1] = b
		*(decoder) = Idrir + ((Idrirt+1)<<16) + (1<<23) + (4<<24) + (banks<<28); 

		// precompute table t[2] = t[1] << 1
		*(decoder) = Idrir + ((Idrirt+2)<<16) + (1<<23) + (6<<24) + (banks<<28); 

		/*
		// t[2] = t[2] ^ ir_t[u]
		//u = ( *(addr_b + 28) >> 8) & 0x1; //grab the first bit // Another option is to use addr_t
		u = (addr_ir[FB_DIGS-1] >> (FB_MOD-1)) & 0x1;  
		if (u==1) {
				*(decoder) =(Idrirt+2) + (Idrir<<8) + ((Idrirt+2)<<16) + (1<<23) + (3<<24) + (banks<<28); 
		}
		// else if u ==0, no need for xor 
		*/

		// precompute table t[3] = t[1] ^ t[2]
		*(decoder) = (Idrirt+2) + ((Idrirt+1)<<8) + ((Idrirt+3)<<16) + (1<<23) + (3<<24) + (banks<<28); 

		// precompute table t[4] = t[2] << 1
		*(decoder) = (Idrirt+2) + ((Idrirt+4)<<16) + (1<<23) + (6<<24) + (banks<<28); 

		/*
		// t[4] = t[4] ^ ir_t[u]
		u = (addr_ir[FB_DIGS-1] >> (FB_MOD-2)) & 0x1; // grab the 2nd bit  
		if (u==1) {
				*(decoder) = (Idrirt+4) + ((Idrir)<<8) + ((Idrirt+4)<<16) + (1<<23) + (3<<24) + (banks<<28); 
		}
		// else if u ==0, no need for xor 
		*/

		// precompute table t[5] = t[1] ^ t[4]
		*(decoder) = (Idrirt+4) + ((Idrirt+1)<<8) + ((Idrirt+5)<<16) + (1<<23) + (3<<24) + (banks<<28); 

		// use this xor instead of shift, to avoid increased 1 bit !!!
		// precompute table t[6] = t[2] ^ t[4] 
		*(decoder) = (Idrirt+4) + ((Idrirt+2)<<8) + ((Idrirt+6)<<16) + (1<<23) + (3<<24) + (banks<<28); 

		// precompute table t[7] = t[1] ^ t[6]
		*(decoder) = (Idrirt+6) + ((Idrirt+1)<<8) + ((Idrirt+7)<<16) + (1<<23) + (3<<24) + (banks<<28); 

		// precompute table t[8] = t[4] << 1
		*(decoder) = (Idrirt+4) + ((Idrirt+8)<<16) + (1<<23) + (6<<24) + (banks<<28); 

		/*
		// t[8] = t[8] ^ ir_t[u]
		u = (addr_ir[FB_DIGS-1] >> (FB_MOD-3)) & 0x1; // grab the 3rd bit  
		if (u==1) {
				*(decoder) = (Idrirt+8) + ((Idrir)<<8) + ((Idrirt+8)<<16) + (1<<23) + (3<<24) + (banks<<28);
		}
				// else if u ==0, no need for xor 
		*/

		// precompute table t[9] = t[1] ^ t[8]
		*(decoder) = (Idrirt+8) + ((Idrirt+1)<<8) + ((Idrirt+9)<<16) + (1<<23) + (3<<24) + (banks<<28); 

		// precompute table t[10] = t[2] ^ t[8]
		*(decoder) = (Idrirt+8) + ((Idrirt+2)<<8) + ((Idrirt+10)<<16) + (1<<23) + (3<<24) + (banks<<28);  

		// precompute table t[11] = t[1] ^ t[10]
		*(decoder) = (Idrirt+10) + ((Idrirt+1)<<8) + ((Idrirt+11)<<16) + (1<<23) + (3<<24) + (banks<<28);  

		// precompute table t[12] = t[4] ^ t[8]
		*(decoder) = (Idrirt+8) + ((Idrirt+4)<<8) + ((Idrirt+12)<<16) + (1<<23) + (3<<24) + (banks<<28); 

		// precompute table t[13] = t[1] ^ t[12]
		*(decoder) = (Idrirt+12) + ((Idrirt+1)<<8) + ((Idrirt+13)<<16) + (1<<23) + (3<<24) + (banks<<28); 

		// use this xor instead of shift, to avoid increased 1 bit !!!
		// why this is wrong !!! precompute table t[14] = t[1] ^ t[13] 
		// precompute table t[14] = t[2] ^ t[12] 
		*(decoder) = (Idrirt+12) + ((Idrirt+2)<<8) + ((Idrirt+14)<<16) + (1<<23) + (3<<24) + (banks<<28);

		// precompute table t[15] = t[1] ^ t[14]
		*(decoder) = (Idrirt+14) + ((Idrirt+1)<<8) + ((Idrirt+15)<<16) + (1<<23) + (3<<24) + (banks<<28); 

	// For debug
	int t =0;
 	int* addr_base_res  	= (int*)0x00004B00; //drirt = 0d1200


// To optimize: first few bits (256-233) are known to be zero, can remove those 
	for (i= FB_DIGS ; i > 0; i -= 1) {
	//i= FB_DIGS ;

		for (j= FB_DIGIT -4; j >= 0 ; j-=4) {
		//j= FB_DIGIT -8;
		

		 		//u = (*(addr_a + (i-1)*4) >> j ) & 0x0F;
		 		u = ( addr_a[i-1] >> j ) & 0x0F;
				addr_base_res[t] = u;
				t++;
		 		// XOR
		 		*(decoder) = (Idrt + u) + (Idrc<<8) + (Idrc<<16) + (1<<23) + (3<<24) + (banks<<28) ; // 0x9<<24 + drc/8<<16 + drc/8<<8 + (drt +8*u)/8 + = 0d616 0d(624+8*u)to be XORed 

				if(!(i==1 && j==0)) {
		 			// OVERFLOW !!!
		 			// shift c by 4 bits 
		 			*(decoder) = (Idrc) + (Idrc<<16) + (1<<23) + (7<<24) + (banks<<28); //0x21<<24 + drc/8<<8 + drc/8 = 0d616 #to be shifted 

					//// 2nd shift to deal with overflow

		 			u = ( addr_c[FB_DIGS-1] >> SHIFT_BIT ) & 0x0F;
		 			// XOR
		 			*(decoder) = (Idrirt + u) + (Idrc<<8) + (Idrc<<16) + (1<<23) + (3<<24) + (banks<<28); // 0x9<<24 + drc/8<<16 + + drc/8<<8 + (drirt + 8*u)/8= 0d616 0d(624+8*u)to be XORed 

				}
			}
		}
/*
*/
} 



/*
void LIM_mulrdc(volatile int *addr_a, volatile int *addr_c) {

    int i;
		volatile int* decoder = (int*) (int*)DECODER;

    // the length of c !!! needs to set here !!! if not set, will get x for the overflow bits
    //for (i=0;i< (32*(NUM_PLN_Minus1+1)) ;i=i+4) {
    for (i=0;i< 36;i=i+4) {
      *(addr_c + i) = 0x0; 
      // different !!!!!!!!!
    }   

    // precompute table t[0] = 0
    // copy from t[0] = c = 0
    //[OCT14] asm("nop");
      *(decoder) = IDRC + ((IDRT + 0)<<16) + 75497472 + (1<<28); // 1<<23+4<<24

    // ADVANCED precomput for ir_t[0]=0
    // copy from ir_t[0] = c = 0
      //[OCT14] asm("nop");
      *(decoder) = IDRC + ((IDRIRT + 0)<<16) + 75497472 + (1<<28);

    // *************************************
    // precompute table ir_t[1] ~ ir_t[15]
    // *************************************
      //[OCT14] asm("nop");
      *(decoder+1) = IDRIR + ((IDRIRT)<<8) + (FB_POLYN<<16) + (NUM_PLN_Minus1<<27) + (1<<28); 

    // *******************************
    // precompute table t[1] ~ t[15] 
    // *******************************
      //[OCT14] asm("nop");
      *(decoder+2) = IDRB + ((IDRT)<<8) + (IDRIR << 16) + (NUM_PLN_Minus1<<27) + (1<<28);


     //int Idra;
     //Idra =   (((unsigned int)addr_a) >> 8 ) & 0xFF;

    // *************************************
    // FOR LOOP 
    // *************************************
      //[OCT14] asm("nop");
      //[OCt14]*(decoder+3) = Idra + (Idrc<<8) + (NUM_FOR <<16) + (NUM_PLN_Minus1<<27) + (1<<28);
      *(decoder+3) = IDRA + (IDRC<<8) + ((NUM_FOR+1) <<16) + (NUM_PLN_Minus1<<27) + (1<<28);

}
*/
