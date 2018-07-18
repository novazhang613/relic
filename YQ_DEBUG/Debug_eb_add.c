 eb_t a = {{ {0x4d434a0eff05220, 0xe373cd9a4b74c2aa, 0x8b41871094a27bde, 0xdf467ffcca25147d, 0xc0d568}, {0xe27e290ff88ff78c, 0xce1d239ec07f1449, 0x1363e78bb1af26fe, 0xaede486a6b63ac7b, 0x27886a}, {0x1, 0x0, 0x0, 0x0, 0x0},  0x1}};

 eb_t b = {{{0x8aa7e5987efaba64, 0xa55a46917fe67aed, 0xbde6a467b4127ff4, 0x9703a1fe2597ed3a, 0x43cb4fe}, {0x2d6d35cd34702bda, 0xc02735ce335b656c, 0x9e4644ee15533aa5, 0x618028cf49413f0c, 0x3fbe65a}, {0x1, 0x0, 0x0, 0x0, 0x0}, 0x1}};

eb_add(d, a, b);
|_ eb_add_projc_imp(eb_t r, const eb_t p, const eb_t q)
	 |_ eb_add_projc_mix(r, p, q);
	 		|_ fb_add(t0, p->y, q->y); (line 169)
 					t0 = {0xcf131cc2ccffdc56, 0xe3a1650f3247125, 0x8d25a365a4fc1c5b, 0xcf5e60a522229377, 0x3dc6e30}
	 		|_ fb_add(t1, p->x, q->x); (line 170)
 					t1 = {0x8e73d138910ae844, 0x46298b0b3492b847, 0x36a7237720b0042a, 0x4845de02efb2f947, 0x4fc6196}
	 		|_ fb_copy(t2,t1);
	 		|_ fb_sqr(r->z, t1); (line 196) 
					r-> z = {0xae8caeb45b4dfd0d, 0xdd1d19c86ef28bba, 0x3f98bd3044a44e1c, 0x30117066924f097, 0x4bac754}
	 		|_ fb_add(t1, t0, r->z); (line 198)
 	*				t1 = {0x619fb27697b2215b, 0xd3270f989dd6fa9f, 0xb2bd1e55e0585247, 0xcc5f77a34b0663e0, 0x766a964}
			|_ fb_mul(t3, r->z, q->x);
					t3 = {0xe87429d8c0681a01, 0x6431018305ce463c, 0x4dbee33cd2c2aebf, 0xa2f08e741e5af733, 0x7df3635}
			|_  fb_add(t4, q->x, q->y);
					t4 = {0xa7cad0554a8a91be, 0x657d735f4cbd1f81, 0x23a0e089a1414551, 0xf68389316cd6d236, 0x7c752a4}
			|_  fb_sqr(r->x, t0);
					r->x = {0xbdc10e0c3defbfc8, 0x1fd8220b57030b76, 0x587eda68cdd95387, 0x909001a02c4e0292, 0x30a52fb}
	*				t1 = {0x619fb27697b2215b, 0xd3270f989dd6fa9f, 0xb2bd1e55e0585247, 0xcc5f77a34b0663e0, 0x766a964}
			|_  fb_add(t1, t1, t2); (line:215 OPT_ONE)
*					t1 = {0xefec634e06b8c91f, 0x950e8493a94442d8, 0x841a3d22c0e8566d, 0x841aa9a1a4b49aa7, 0x39ac8f2}

			....

			|_  fb_add(r->y, r->y, t0);
					r->y = {0x4dca4de5fb7e9812, 0x89cae6122be24d8, 0x6a6d93df644b549c, 0x301b6d172c0a9d68, 0x325336}

x:
c:0296a88b dcc5cd50
c:86496f5b 65263580
c:b79d983e 1870d15f
c:aedcbde6 39681d33
c:758a42b

y:
c:4dca4de5fb7e9812
c:89cae6122be24d8
c:6a6d93df644b549c
c:301b6d172c0a9d68
c:325336

z:
c:ae8caeb45b4dfd0d
c:dd1d19c86ef28bba
c:3f98bd3044a44e1c
c:30117066924f097
c:4bac754


