/*
 * RELIC is an Efficient LIbrary for Cryptography
 * Copyright (C) 2007-2015 RELIC Authors
 *
 * This file is part of RELIC. RELIC is legal property of its developers,
 * whose names are not listed here. Please refer to the COPYRIGHT file
 * for contact information.
 *
 * RELIC is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * RELIC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with RELIC. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file
 *
 * Benchmarks for binary field arithmetic.
 *
 * @ingroup bench
 */

#include <stdio.h>
#include <stdbool.h>

#include "relic.h"
#include "relic_bench.h"

static void memory(void) {
	fb_t a[BENCH];

	BENCH_SMALL("fb_null", fb_null(a[i]));

	BENCH_SMALL("fb_new", fb_new(a[i]));
	for (int i = 0; i < BENCH; i++) {
		fb_free(a[i]);
	}

	for (int i = 0; i < BENCH; i++) {
		fb_new(a[i]);
	}
	BENCH_SMALL("fb_free", fb_free(a[i]));

	(void)a;
}

static void util(void) {
	char str[2 * FB_BYTES + 1];
	uint8_t bin[FB_BYTES];
	fb_t a, b;

	fb_null(a);
	fb_null(b);

	fb_new(a);
	fb_new(b);

	BENCH_BEGIN("fb_copy") {
		fb_rand(a);
		
		//////////////////
		// YQ Debug
		int kk;
		for (kk=0;kk<FB_DIGS;kk++) {
			printf("a[%d] = 0x%llx\n",kk,a[kk]);
		}
		printf("\n");
		//////////////////

		BENCH_ADD(fb_copy(b, a));
	}
	BENCH_END;

	BENCH_BEGIN("fb_neg") {
		fb_rand(a);
		BENCH_ADD(fb_neg(b, a));
	}
	BENCH_END;

	BENCH_BEGIN("fb_zero") {
		fb_rand(a);
		BENCH_ADD(fb_zero(a));
	}
	BENCH_END;

	BENCH_BEGIN("fb_is_zero") {
		fb_rand(a);
		BENCH_ADD(fb_is_zero(a));
	}
	BENCH_END;

	BENCH_BEGIN("fb_get_bit") {
		fb_rand(a);
		BENCH_ADD(fb_get_bit(a, FB_DIGIT / 2));
	}
	BENCH_END;

	BENCH_BEGIN("fb_set_bit") {
		fb_rand(a);
		BENCH_ADD(fb_set_bit(a, FB_DIGIT / 2, 1));
	}
	BENCH_END;

	BENCH_BEGIN("fb_set_dig") {
		fb_rand(a);
		fb_rand(b);
		BENCH_ADD(fb_set_dig(a, b[0]));
	}
	BENCH_END;

	BENCH_BEGIN("fb_bits") {
		fb_rand(a);
		BENCH_ADD(fb_bits(a));
	}
	BENCH_END;

	BENCH_BEGIN("fb_rand") {
		BENCH_ADD(fb_rand(a));
	}
	BENCH_END;

	BENCH_BEGIN("fb_size_str (16)") {
		fb_rand(a);
		BENCH_ADD(fb_size_str(a, 16));
	}
	BENCH_END;

	BENCH_BEGIN("fb_write_str (16)") {
		fb_rand(a);
		BENCH_ADD(fb_write_str(str, sizeof(str), a, 16));
	}
	BENCH_END;

	BENCH_BEGIN("fb_read_str (16)") {
		fb_rand(a);
		fb_write_str(str, sizeof(str), a, 16);
		BENCH_ADD(fb_read_str(a, str, sizeof(str), 16));
	}
	BENCH_END;

	BENCH_BEGIN("fb_write_bin") {
		fb_rand(a);
		BENCH_ADD(fb_write_bin(bin, sizeof(bin), a));
	}
	BENCH_END;

	BENCH_BEGIN("fb_read_bin") {
		fb_rand(a);
		fb_write_bin(bin, sizeof(bin), a);
		BENCH_ADD(fb_read_bin(a, bin, sizeof(bin)));
	}
	BENCH_END;

	BENCH_BEGIN("fb_cmp_dig") {
		fb_rand(a);
		BENCH_ADD(fb_cmp_dig(a, (dig_t)0));
	}
	BENCH_END;

	BENCH_BEGIN("fb_cmp") {
		fb_rand(a);
		fb_rand(b);
		BENCH_ADD(fb_cmp(b, a));
	}
	BENCH_END;

	fb_free(a);
	fb_free(b);
}

static void arith(void) {
	fb_t a, b, c, d[2], t[FB_TABLE_MAX];
	dv_t e;
	bn_t f;
	int bits;

	fb_null(a);
	fb_null(b);
	fb_null(c);
	fb_null(d[0]);
	fb_null(d[1]);
	for (int i = 0; i < FB_TABLE_MAX; i++) {
		fb_null(t[i]);
	}
	dv_null(e);
	bn_null(f);

	fb_new(a);
	fb_new(b);
	fb_new(c);
	fb_new(d[0]);
	fb_new(d[1]);
	dv_new(e);
	dv_zero(e, 2 * FB_DIGS);
	bn_new(f);

	BENCH_BEGIN("fb_add") {
		fb_rand(a);
		fb_rand(b);
		BENCH_ADD(fb_add(c, a, b));
	}
	BENCH_END;

	BENCH_BEGIN("fb_add_dig") {
		fb_rand(a);
		fb_rand(b);
		BENCH_ADD(fb_add_dig(c, a, b[0]));
	}
	BENCH_END;

	BENCH_BEGIN("fb_sub") {
		fb_rand(a);
		fb_rand(b);
		BENCH_ADD(fb_sub(c, a, b));
	}
	BENCH_END;

	BENCH_BEGIN("fb_sub_dig") {
		fb_rand(a);
		fb_rand(b);
		BENCH_ADD(fb_sub_dig(c, a, b[0]));
	}
	BENCH_END;

	BENCH_BEGIN("fb_poly_add") {
		fb_rand(a);
		BENCH_ADD(fb_poly_add(c, a));
	}
	BENCH_END;

	BENCH_BEGIN("fb_poly_sub") {
		fb_rand(a);
		BENCH_ADD(fb_poly_sub(c, a));
	}
	BENCH_END;

	BENCH_BEGIN("fb_mul") {
		fb_rand(a);
		fb_rand(b);
		BENCH_ADD(fb_mul(c, a, b));
	}
	BENCH_END;

	BENCH_BEGIN("fb_mul_dig") {
		fb_rand(a);
		fb_rand(b);
		BENCH_ADD(fb_mul_dig(c, a, b[0]));
	}
	BENCH_END;

#if FB_MUL == BASIC || !defined(STRIP)
	BENCH_BEGIN("fb_mul_basic") {
		fb_rand(a);
		fb_rand(b);
		BENCH_ADD(fb_mul_basic(c, a, b));
	}
	BENCH_END;
#endif

#if FB_MUL == INTEG || !defined(STRIP)
	BENCH_BEGIN("fb_mul_integ") {
		fb_rand(a);
		fb_rand(b);
		BENCH_ADD(fb_mul_integ(c, a, b));
	}
	BENCH_END;
#endif

#if FB_MUL == LCOMB || !defined(STRIP)
	BENCH_BEGIN("fb_mul_lcomb") {
		fb_rand(a);
		fb_rand(b);
		BENCH_ADD(fb_mul_lcomb(c, a, b));
	}
	BENCH_END;
#endif

#if FB_MUL == RCOMB || !defined(STRIP)
	BENCH_BEGIN("fb_mul_rcomb") {
		fb_rand(a);
		fb_rand(b);
		BENCH_ADD(fb_mul_rcomb(c, a, b));
	}
	BENCH_END;
#endif

#if FB_MUL == LODAH || !defined(STRIP)
	BENCH_BEGIN("fb_mul_lodah") {
		fb_rand(a);
		fb_rand(b);
		BENCH_ADD(fb_mul_lodah(c, a, b));
	}
	BENCH_END;
#endif

#if FB_KARAT > 0 || !defined(STRIP)
	BENCH_BEGIN("fb_mul_karat") {
		fb_rand(a);
		fb_rand(b);
		BENCH_ADD(fb_mul_karat(c, a, b));
	}
	BENCH_END;
#endif

	BENCH_BEGIN("fb_sqr") {
		fb_rand(a);
		BENCH_ADD(fb_sqr(c, a));
	}
	BENCH_END;

#if FB_SQR == BASIC || !defined(STRIP)
	BENCH_BEGIN("fb_sqr_basic") {
		fb_rand(a);
		BENCH_ADD(fb_sqr_basic(c, a));
	}
	BENCH_END;
#endif

#if FB_SQR == INTEG || !defined(STRIP)
	BENCH_BEGIN("fb_sqr_integ") {
		fb_rand(a);
		BENCH_ADD(fb_sqr_integ(c, a));
	}
	BENCH_END;
#endif

#if FB_SQR == TABLE || !defined(STRIP)
	BENCH_BEGIN("fb_sqr_table") {
		fb_rand(a);
		BENCH_ADD(fb_sqr_table(c, a));
	}
	BENCH_END;
#endif

	BENCH_BEGIN("fb_lsh") {
		fb_rand(a);
		a[FB_DIGS - 1] = 0;
		bits = a[0] & MASK(FB_DIG_LOG);
		BENCH_ADD(fb_lsh(c, a, bits));
	}
	BENCH_END;

	BENCH_BEGIN("fb_rsh") {
		fb_rand(a);
		a[FB_DIGS - 1] = 0;
		bits = a[0] & MASK(FB_DIG_LOG);
		BENCH_ADD(fb_rsh(c, a, bits));

	}
	BENCH_END;

	BENCH_BEGIN("fb_rdc") {
		fb_rand(a);
		fb_lsh(e, a, FB_BITS);
		fb_rand(e);
		BENCH_ADD(fb_rdc(c, e));
	}
	BENCH_END;

#if FB_RDC == BASIC || !defined(STRIP)
	BENCH_BEGIN("fb_rdc_basic") {
		fb_rand(a);
		fb_lsh(e, a, FB_BITS);
		fb_rand(e);
		BENCH_ADD(fb_rdc_basic(c, e));
	}
	BENCH_END;
#endif

#if FB_RDC == QUICK || !defined(STRIP)
	BENCH_BEGIN("fb_rdc_quick") {
		fb_rand(a);
		fb_lsh(e, a, FB_BITS);
		fb_rand(e);
		BENCH_ADD(fb_rdc_quick(c, e));
	}
	BENCH_END;
#endif

	BENCH_BEGIN("fb_srt") {
		fb_rand(a);
		fb_sqr(e, a);
		BENCH_ADD(fb_srt(c, e));
	}
	BENCH_END;

#if FB_SRT == BASIC || !defined(STRIP)
	BENCH_BEGIN("fb_srt_basic") {
		fb_rand(a);
		fb_sqr(e, a);
		BENCH_ADD(fb_srt_basic(c, e));
	}
	BENCH_END;
#endif

#if FB_SRT == QUICK || !defined(STRIP)
	BENCH_BEGIN("fb_srt_quick") {
		fb_rand(a);
		fb_sqr(e, a);
		BENCH_ADD(fb_srt_quick(c, e));
	}
	BENCH_END;
#endif

	BENCH_BEGIN("fb_trc") {
		fb_rand(a);
		BENCH_ADD(fb_trc(a));
	}
	BENCH_END;

#if FB_TRC == BASIC || !defined(STRIP)
	BENCH_BEGIN("fb_trc_basic") {
		fb_rand(a);
		BENCH_ADD(fb_trc_basic(a));
	}
	BENCH_END;
#endif

#if FB_TRC == QUICK || !defined(STRIP)
	BENCH_BEGIN("fb_trc_quick") {
		fb_rand(a);
		BENCH_ADD(fb_trc_quick(a));
	}
	BENCH_END;
#endif

	if (FB_BITS % 2 != 0) {
		BENCH_BEGIN("fb_slv") {
			fb_rand(a);
			BENCH_ADD(fb_slv(c, a));
		}
		BENCH_END;

#if FB_SLV == BASIC || !defined(STRIP)
		BENCH_BEGIN("fb_slv_basic") {
			fb_rand(a);
			BENCH_ADD(fb_slv_basic(c, a));
		}
		BENCH_END;
#endif

#if FB_SLV == QUICK || !defined(STRIP)
		BENCH_BEGIN("fb_slv_quick") {
			fb_rand(a);
			BENCH_ADD(fb_slv_quick(c, a));
		}
		BENCH_END;
#endif
	}

	BENCH_BEGIN("fb_inv") {
		fb_rand(a);
		BENCH_ADD(fb_inv(c, a));
	}
	BENCH_END;

#if FB_INV == BASIC || !defined(STRIP)
	BENCH_BEGIN("fb_inv_basic") {
		fb_rand(a);
		BENCH_ADD(fb_inv_basic(c, a));
	}
	BENCH_END;
#endif

#if FB_INV == BINAR || !defined(STRIP)
	BENCH_BEGIN("fb_inv_binar") {
		fb_rand(a);
		BENCH_ADD(fb_inv_binar(c, a));
	}
	BENCH_END;
#endif

#if FB_INV == ALMOS || !defined(STRIP)
	BENCH_BEGIN("fb_inv_almos") {
		fb_rand(a);
		BENCH_ADD(fb_inv_almos(c, a));
	}
	BENCH_END;
#endif

#if FB_INV == EXGCD || !defined(STRIP)
	BENCH_BEGIN("fb_inv_exgcd") {
		fb_rand(a);
		BENCH_ADD(fb_inv_exgcd(c, a));
	}
	BENCH_END;
#endif

#if FB_INV == BRUCH || !defined(STRIP)
	BENCH_BEGIN("fb_inv_bruch") {
		fb_rand(a);
		BENCH_ADD(fb_inv_bruch(c, a));
	}
	BENCH_END;
#endif

#if FB_INV == ITOHT || !defined(STRIP)
	BENCH_BEGIN("fb_inv_itoht") {
		fb_rand(a);
		BENCH_ADD(fb_inv_itoht(c, a));
	}
	BENCH_END;
#endif

#if FB_INV == LOWER || !defined(STRIP)
	BENCH_BEGIN("fb_inv_lower") {
		fb_rand(a);
		BENCH_ADD(fb_inv_lower(c, a));
	}
	BENCH_END;
#endif

	BENCH_BEGIN("fb_inv_sim (2)") {
		fb_rand(d[0]);
		fb_rand(d[1]);
		BENCH_ADD(fb_inv_sim(d, (const fb_t *)d, 2));
	}
	BENCH_END;

	BENCH_BEGIN("fb_exp") {
		fb_rand(a);
		bn_rand(f, BN_POS, FB_BITS);
		BENCH_ADD(fb_exp(c, a, f));
	}
	BENCH_END;

#if FB_EXP == BASIC || !defined(STRIP)
	BENCH_BEGIN("fb_exp_basic") {
		fb_rand(a);
		bn_rand(f, BN_POS, FB_BITS);
		BENCH_ADD(fb_exp_basic(c, a, f));
	}
	BENCH_END;
#endif

#if FB_EXP == SLIDE || !defined(STRIP)
	BENCH_BEGIN("fb_exp_slide") {
		fb_rand(a);
		bn_rand(f, BN_POS, FB_BITS);
		BENCH_ADD(fb_exp_slide(c, a, f));
	}
	BENCH_END;
#endif

#if FB_EXP == MONTY || !defined(STRIP)
	BENCH_BEGIN("fb_exp_monty") {
		fb_rand(a);
		bn_rand(f, BN_POS, FB_BITS);
		BENCH_ADD(fb_exp_monty(c, a, f));
	}
	BENCH_END;
#endif

	for (int i = 0; i < FB_TABLE; i++) {
		fb_new(t[i]);
	}

	BENCH_BEGIN("fb_itr") {
		fb_rand(a);
		bn_rand(f, BN_POS, 8);
		fb_itr_pre(t, f->dp[0]);
		BENCH_ADD(fb_itr(c, a, f->dp[0], (const fb_t *)t));
	}
	BENCH_END;

	for (int i = 0; i < FB_TABLE; i++) {
		fb_free(t[i]);
	}

#if FB_ITR == BASIC || !defined(STRIP)
	BENCH_BEGIN("fb_itr_basic") {
		fb_rand(a);
		bn_rand(f, BN_POS, 8);
		BENCH_ADD(fb_itr_basic(c, a, f->dp[0]));
	}
	BENCH_END;
#endif

#if FB_ITR == QUICK || !defined(STRIP)
	for (int i = 0; i < FB_TABLE_QUICK; i++) {
		fb_new(t[i]);
	}
	BENCH_BEGIN("fb_itr_quick") {
		fb_rand(a);
		bn_rand(f, BN_POS, 8);
		fb_itr_pre_quick(t, f->dp[0]);
		BENCH_ADD(fb_itr_quick(c, a, (const fb_t *)t));
	}
	BENCH_END;
	for (int i = 0; i < FB_TABLE_QUICK; i++) {
		fb_new(t[i]);
	}
#endif

	fb_free(a);
	fb_free(b);
	fb_free(c);
	fb_free(d[0]);
	fb_free(d[1]);
	dv_free(e);
	bn_free(f);
}

int main(void) {
	if (core_init() != STS_OK) {
		core_clean();
		return 1;
	}

	conf_print();
	util_banner("Benchmarks for the FB module:", 0);

	fb_param_set_any();
	fb_param_print();
/*
	util_banner("Utilities:\n", 0);
	memory();
	util();
	util_banner("Arithmetic:\n", 0);
	arith();
*/

	fb_t a, b, c;
	int kk;
	int result;
	bool correctness;

	// FB_COPY
		util_print("\n-- fb_copy:			");
  	a[1] = 0x44e96edeb7e69206;
  	a[2] = 0x545073551aa4fcef;
  	a[3] = 0xdf41c952986a48c5;
  	a[4] = 0x4c6dfc1;

		fb_copy(b, a);

		correctness = true;
		for (kk=0;kk<FB_DIGS;kk++) {
			if(a[kk]!=b[kk]) {
				printf("a/b [%d] not match! a[%d] = 0x%llx; b[%d] = 0x%llx\n",kk, kk,a[kk],kk,b[kk]);
				correctness = false;
			}
		}

		if (correctness) printf("Pass!");
		else						 printf("Fail!");

	// FB_NEG
		util_print("\n-- fb_neg:			");
		a[0] = 0x54d98527a61946a9;
		a[1] = 0x4550b3557a250d65;
		a[2] = 0x2464d1aad631c046;
		a[3] = 0x1c89aaeb8b15a787;
		a[4] = 0x40c73b8;

		fb_copy(b, a);

		correctness = true;
		for (kk=0;kk<FB_DIGS;kk++) {
			if(a[kk]!=b[kk]) {
				printf("a/b [%d] not match! a[%d] = 0x%llx; b[%d] = 0x%llx\n",kk, kk,a[kk],kk,b[kk]);
				correctness = false;
			}
		}

		if (correctness) printf("Pass!");
		else						 printf("Fail!");


	// FB_GET_BIT
		util_print("\n-- fb_get_bit:			");
		//test0
		a[0] = 0x54d98527a61946a9;
		a[1] = 0xad14a0429c446e43;
		a[2] = 0x1b63a1f8cf6a031a;
		a[3] = 0x1f6cc5322c201d87;
		a[4] = 0x3a95699;
		result= 0; 

		if(fb_get_bit(a, FB_BITS / 2) != result)
				printf(" test 0: fail!");
		else						 printf("Pass!");

		//test1
		a[0] = 0xc161753b049c3a11;
		a[1] = 0x878541edc40e6ce1;
		a[2] = 0xd5d33eac20e7ca6;
		a[3] = 0x4351f66ea52a243d;
		a[4] = 0x2d402ed;
		result= 1; 

		if(fb_get_bit(a, FB_BITS / 2) != result)
				printf(" test 1: fail!");
		else						 printf("Pass!");
	
	// FB_ADD
		util_print("\n-- fb_add:			");
		fb_t c_ref;
		a[0] = 0xb1e1bee3b7b0fe8c;
		a[1] = 0x73076118feeae79;
		a[2] = 0x576cf716897e086a;
		a[3] = 0x9bffd0b4fbd4c338;
		a[4] = 0x50f4ed5;
		
		b[0] = 0x324b78c6afcb6eff;
		b[1] = 0xb27475c8598433aa;
		b[2] = 0xbce0b52813c16e4a;
		b[3] = 0xaa181e9eb106663a;
		b[4] = 0x100d148;
		
		c_ref[0] = 0x83aac625187b9073;
		c_ref[1] = 0xb54403d9d66a9dd3;
		c_ref[2] = 0xeb8c423e9abf6620;
		c_ref[3] = 0x31e7ce2a4ad2a502;
		c_ref[4] = 0x40f9f9d;
		
		/*
		a[0] = 0xb7b0fe8c;
		a[1] = 0xb1e1bee3;
		a[2] = 0x8feeae79;
		a[3] = 0x7307611;
		a[4] = 0x897e086a;
		a[5] = 0x576cf716;
		a[6] = 0xfbd4c338;
		a[7] = 0x9bffd0b4;
		a[8] = 0x50f4ed5;
		
		b[0] = 0xafcb6eff;
		b[1] = 0x324b78c6;
		b[2] = 0x598433aa;
		b[3] = 0xb27475c8;
		b[4] = 0x13c16e4a;
		b[5] = 0xbce0b528;
		b[6] = 0xb106663a;
		b[7] = 0xaa181e9e;
		b[8] = 0x100d148;
		
		c_ref[0] = 0x187b9073;
		c_ref[1] = 0x83aac625;
		c_ref[2] = 0xd66a9dd3;
		c_ref[3] = 0xb54403d9;
		c_ref[4] = 0x9abf6620;
		c_ref[5] = 0xeb8c423e;
		c_ref[6] = 0x4ad2a502;
		c_ref[7] = 0x31e7ce2a;
		c_ref[8] = 0x40f9f9d;
		*/
		
		fb_add(c,a,b);

		correctness = true;
		for (kk=0;kk<FB_DIGS;kk++) {
			if(c[kk]!=c_ref[kk]) {
				printf("c/c_ref [%d] not match! c[%d] = 0x%llx; c_ref[%d] = 0x%llx\n",kk, kk,c[kk],kk,c_ref[kk]);
				correctness = false;
			}
		}

		if (correctness) printf("Pass!");
		else						 printf("Fail!");
	
	// FB_POLY_ADD
		util_print("\n-- fb_poly_get:			");
		
		a[0] = 0xc31f411494bb3559;
		a[1] = 0x2f866ee5cdeef86e;
		a[2] = 0x46549365f8c86a55;
		a[3] = 0x79d00c95d0eba4d5;
		a[4] = 0xb07de;
		
		c_ref[0] = 0xc31f411494bb25f8;
		c_ref[1] = 0x2f866ee5cdeef86e;
		c_ref[2] = 0x46549365f8c86a55;
		c_ref[3] = 0x79d00c95d0eba4d5;
		c_ref[4] = 0x80b07de;
		
		/*
		a[0] = 0x94bb3559;
		a[1] = 0xc31f4114;
		a[2] = 0xcdeef86e;
		a[3] = 0x2f866ee5;
		a[4] = 0xf8c86a55;
		a[5] = 0x46549365;
		a[6] = 0xd0eba4d5;
		a[7] = 0x79d00c95;
		a[8] = 0xb07de;
		
		c_ref[0] = 0x94bb25f8;
		c_ref[1] = 0xc31f4114;
		c_ref[2] = 0xcdeef86e;
		c_ref[3] = 0x2f866ee5;
		c_ref[4] = 0xf8c86a55;
		c_ref[5] = 0x46549365;
		c_ref[6] = 0xd0eba4d5;
		c_ref[7] = 0x79d00c95;
		c_ref[8] = 0x80b07de;
		*/

		fb_poly_add(c,a);

		correctness = true;
		for (kk=0;kk<FB_DIGS;kk++) {
			if(c[kk]!=c_ref[kk]) {
				printf("c/c_ref [%d] not match! c[%d] = 0x%llx; c_ref[%d] = 0x%llx\n",kk, kk,c[kk],kk,c_ref[kk]);
				correctness = false;
			}
		}

		if (correctness) printf("Pass!");
		else						 printf("Fail!");
		

	// FB_MUL
		util_print("\n-- fb_mul:			");

		a[0] = 0x7033a4f9c7fc7431;
		a[1] = 0xd420666d5e5900e3;
		a[2] = 0xf0723071d69c5fc6;
		a[3] = 0x3558e403d20466e2;
		a[4] = 0x5810233;
		
		b[0] = 0xcbd645b438967c78;
		b[1] = 0x8672fdc3007dc6c4;
		b[2] = 0xbae0f64df1014246;
		b[3] = 0x596c0a453a84e316;
		b[4] = 0x58e8692;
		
		c_ref[0] = 0x56fd23fc0fe60cde;
		c_ref[1] = 0x70ee3a6cb0ed6d2f;
		c_ref[2] = 0x393825db285f5682;
		c_ref[3] = 0xe0d4c27387967077;
		c_ref[4] = 0x6811803;
		
		/*
		a[0] = 0xc7fc7431;
		a[1] = 0x7033a4f9;
		a[2] = 0x5e5900e3;
		a[3] = 0xd420666d;
		a[4] = 0xd69c5fc6;
		a[5] = 0xf0723071;
		a[6] = 0xd20466e2;
		a[7] = 0x3558e403;
		a[8] = 0x5810233;
		
		b[0] = 0x38967c78;
		b[1] = 0xcbd645b4;
		b[2] = 0x7dc6c4;
		b[3] = 0x8672fdc3;
		b[4] = 0xf1014246;
		b[5] = 0xbae0f64d;
		b[6] = 0x3a84e316;
		b[7] = 0x596c0a45;
		b[8] = 0x58e8692;
		
		c_ref[0] = 0xfe60cde;
		c_ref[1] = 0x56fd23fc;
		c_ref[2] = 0xb0ed6d2f;
		c_ref[3] = 0x70ee3a6c;
		c_ref[4] = 0x285f5682;
		c_ref[5] = 0x393825db;
		c_ref[6] = 0x87967077;
		c_ref[7] = 0xe0d4c273;
		c_ref[8] = 0x6811803;
		*/

		fb_mul(c,a,b);

		correctness = true;
		for (kk=0;kk<FB_DIGS;kk++) {
			if(c[kk]!=c_ref[kk]) {
				printf("c/c_ref [%d] not match! c[%d] = 0x%llx; c_ref[%d] = 0x%llx\n",kk, kk,c[kk],kk,c_ref[kk]);
				correctness = false;
			}
		}

		if (correctness) printf("Pass!");
		else						 printf("Fail!");

	// FB_SQR
		util_print("\n-- fb_sqr:			");
		a[0] = 0xfec95269ddf4953;
		a[1] = 0x366030d06a8874df;
		a[2] = 0x9fb6c0b8bd426a03;
		a[3] = 0x620156e6d3250caf;
		a[4] = 0x4fbd3c3;
		
		c_ref[0] = 0xce9876bfcf6a2dda;
		c_ref[1] = 0xc7a35d42e0d412de;
		c_ref[2] = 0x8af7749479c387d1;
		c_ref[3] = 0xc5f479bad582665f;
		c_ref[4] = 0xc54af1;
		
		/*
		a[0] = 0x9ddf4953;
		a[1] = 0xfec9526;
		a[2] = 0x6a8874df;
		a[3] = 0x366030d0;
		a[4] = 0xbd426a03;
		a[5] = 0x9fb6c0b8;
		a[6] = 0xd3250caf;
		a[7] = 0x620156e6;
		a[8] = 0x4fbd3c3;
		
		c_ref[0] = 0xcf6a2dda;
		c_ref[1] = 0xce9876bf;
		c_ref[2] = 0xe0d412de;
		c_ref[3] = 0xc7a35d42;
		c_ref[4] = 0x79c387d1;
		c_ref[5] = 0x8af77494;
		c_ref[6] = 0xd582665f;
		c_ref[7] = 0xc5f479ba;
		c_ref[8] = 0xc54af1;
		*/
	
		fb_sqr(c,a);

		correctness = true;
		for (kk=0;kk<FB_DIGS;kk++) {
			if(c[kk]!=c_ref[kk]) {
				printf("c/c_ref [%d] not match! c[%d] = 0x%llx; c_ref[%d] = 0x%llx\n",kk, kk,c[kk],kk,c_ref[kk]);
				correctness = false;
			}
		}

		if (correctness) printf("Pass!");
		else						 printf("Fail!");

	// FB_INV
		util_print("\n-- fb_inv:			");
	
		a[0] = 0x99ad95ce72c07eb5;
		a[1] = 0xb423f9c18d02f5eb;
		a[2] = 0xe1920a6999801648;
		a[3] = 0xb94f51f83561ab7a;
		a[4] = 0xc761a;
		
		c_ref[0] = 0xc2ad4f1667355ab5;
		c_ref[1] = 0x4f33997cd07c1b06;
		c_ref[2] = 0xd4f2acfa4e67e7d9;
		c_ref[3] = 0x4738a6355bcd46d2;
		c_ref[4] = 0x1ce2f34;
		
		/*
		a[0] = 0x72c07eb5;
		a[1] = 0x99ad95ce;
		a[2] = 0x8d02f5eb;
		a[3] = 0xb423f9c1;
		a[4] = 0x99801648;
		a[5] = 0xe1920a69;
		a[6] = 0x3561ab7a;
		a[7] = 0xb94f51f8;
		a[8] = 0xc761a;
		
		c_ref[0] = 0x67355ab5;
		c_ref[1] = 0xc2ad4f16;
		c_ref[2] = 0xd07c1b06;
		c_ref[3] = 0x4f33997c;
		c_ref[4] = 0x4e67e7d9;
		c_ref[5] = 0xd4f2acfa;
		c_ref[6] = 0x5bcd46d2;
		c_ref[7] = 0x4738a635;
		c_ref[8] = 0x1ce2f34;
		*/

		fb_inv(c,a);

		correctness = true;
		for (kk=0;kk<FB_DIGS;kk++) {
			if(c[kk]!=c_ref[kk]) {
				printf("c/c_ref [%d] not match! c[%d] = 0x%llx; c_ref[%d] = 0x%llx\n",kk, kk,c[kk],kk,c_ref[kk]);
				correctness = false;
			}
		}

		if (correctness) printf("Pass!");
		else						 printf("Fail!");


	core_clean();
	return 0;
}
