
/* test finite-field-multiplication
	dig_t a[FB_DIGS];
	dig_t b[FB_DIGS]; 
	dig_t c[2*FB_DIGS]; 
	dig_t rdc_res[FB_DIGS]; 
 	
	a[0] = 0x3b99b6e229dcdf51; 
	a[1] = 0x2b02bc515c19b015; 
	a[2] = 0x1f5f4dbdf477315b; 
	a[3] = 0x7191ca77bb93d20; 
	a[4] = 0x664f828; 

	b[0] = 0xadc44c51c145855b; 
	b[1] = 0x7293f518ea2e378b; 
	b[2] = 0x2e79f7ef2d36901e; 
	b[3] = 0xde5c38ea7de139ad; 
	b[4] = 0x4de5614; 

	// run the 283 bits multiplication function 
	fb_muln_low(&c[0], &a[0], &b[0]);

	// print out the results in hex
	int i;
	for (i=0;i<2*FB_DIGS;i++) {
		printf("c:%llx\n", *(c+i));
	}

	// reduction
  fb_rdcn_low(&rdc_res[0], &c[0]);
	// print out the results in hex
	printf("\n");
	for (i=0;i<FB_DIGS;i++) {
		printf("rdc_res_quick:%llx\n", *(rdc_res+i));
	}
	printf("\n");

*/
