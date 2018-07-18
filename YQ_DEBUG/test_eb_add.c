
	int r0 = STS_ERR, r1 = STS_ERR;

	if (core_init() != STS_OK) {
		core_clean();
		return 1;
	}


	util_banner("Tests for the YIQUN module:", 0);

//YQ added for test	
	fb_param_set_any();
	dig_t* poly = fb_poly_get();
	for(int i=0;i<5;i++) {
		printf("poly:%llx\n", poly[i]);
	}

int j;
	r0 = eb_param_set_any_plain();

/*
	if (r0 == STS_OK) {
		if (addition() != STS_OK) {
			core_clean();
			return 1;
		}
	}
*/


	eb_t  d;
  eb_t SHA = {{{0,1,2,3,0},{4,5,6,7,0},{8,9,10,11,0},0}};
//	a->x[0] = 1;

// a->x = {0x4d434a0eff05220, 0xe373cd9a4b74c2aa, 0x8b41871094a27bde, 0xdf467ffcca25147d, 0xc0d568};

 eb_t a = {{ {0x4d434a0eff05220, 0xe373cd9a4b74c2aa, 0x8b41871094a27bde, 0xdf467ffcca25147d, 0xc0d568}, {0xe27e290ff88ff78c, 0xce1d239ec07f1449, 0x1363e78bb1af26fe, 0xaede486a6b63ac7b, 0x27886a}, {0x1, 0x0, 0x0, 0x0, 0x0},  0x1}};

 eb_t b = {{{0x8aa7e5987efaba64, 0xa55a46917fe67aed, 0xbde6a467b4127ff4, 0x9703a1fe2597ed3a, 0x43cb4fe}, {0x2d6d35cd34702bda, 0xc02735ce335b656c, 0x9e4644ee15533aa5, 0x618028cf49413f0c, 0x3fbe65a}, {0x1, 0x0, 0x0, 0x0, 0x0}, 0x1}};


eb_add(d, a, b);

// result should be:
// d = {x = {0x296a88bdcc5cd50, 0x86496f5b65263580, 0xb79d983e1870d15f, 0xaedcbde639681d33, 0x758a42b}, y = {0x4dca4de5fb7e9812, 0x89cae6122be24d8, 0x6a6d93df644b549c, 0x301b6d172c0a9d68, 0x325336}, z = {0xae8caeb45b4dfd0d, 0xdd1d19c86ef28bba, 0x3f98bd3044a44e1c, 0x30117066924f097, 0x4bac754}, norm = 0x0};

	// print out the results in hex
	int i;
	for (i=0;i<FB_DIGS;i++) {
		printf("c:%llx\n", *(d->x +i));
	}
	printf("\n");
	for (i=0;i<FB_DIGS;i++) {
		printf("c:%llx\n", *(d->y +i));
	}
	printf("\n");
	for (i=0;i<FB_DIGS;i++) {
		printf("c:%llx\n", *(d->z +i));
	}

