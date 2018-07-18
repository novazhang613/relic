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
 * Benchmarks for arithmetic on binary elliptic curves.
 *
 * @ingroup bench
 */

#include <stdio.h>
#include <stdbool.h>

#include "relic.h"
#include "relic_bench.h"

static void memory(void) {
	eb_t a[BENCH];

	BENCH_SMALL("eb_null", eb_null(a[i]));

	BENCH_SMALL("eb_new", eb_new(a[i]));
	for (int i = 0; i < BENCH; i++) {
		eb_free(a[i]);
	}

	for (int i = 0; i < BENCH; i++) {
		eb_new(a[i]);
	}
	BENCH_SMALL("eb_free", eb_free(a[i]));

	(void)a;
}

static void util(void) {
	eb_t p, q, t[4];
	uint8_t bin[2 * FB_BYTES + 1];
	int l;

	eb_null(p);
	eb_null(q);
	for (int j= 0; j < 4; j++) {
		eb_null(t[j]);
	}

	eb_new(p);
	eb_new(q);
	for (int j= 0; j < 4; j++) {
		eb_new(t[j]);
	}

	BENCH_BEGIN("eb_is_infty") {
		eb_rand(p);
		BENCH_ADD(eb_is_infty(p));
	} BENCH_END;

	BENCH_BEGIN("eb_set_infty") {
		eb_rand(p);
		BENCH_ADD(eb_set_infty(p));
	} BENCH_END;

	BENCH_BEGIN("eb_copy") {
		eb_rand(p);
		eb_rand(q);
		BENCH_ADD(eb_copy(p, q));
	} BENCH_END;

	BENCH_BEGIN("eb_cmp") {
		eb_rand(p);
		eb_dbl(p, p);
		eb_rand(q);
		eb_dbl(q, q);
		BENCH_ADD(eb_cmp(p, q));
	} BENCH_END;

	BENCH_BEGIN("eb_cmp (1 norm)") {
		eb_rand(p);
		eb_dbl(p, p);
		eb_rand(q);
		BENCH_ADD(eb_cmp(p, q));
	} BENCH_END;

	BENCH_BEGIN("eb_cmp (2 norm)") {
		eb_rand(p);
		eb_rand(q);
		BENCH_ADD(eb_cmp(p, q));
	} BENCH_END;

	BENCH_BEGIN("eb_rand") {
		BENCH_ADD(eb_rand(p));
	} BENCH_END;

	BENCH_BEGIN("eb_rhs") {
		eb_rand(p);
		BENCH_ADD(eb_rhs(q->x, p));
	} BENCH_END;

	BENCH_BEGIN("eb_tab (4)") {
		eb_rand(p);
		BENCH_ADD(eb_tab(t, p, 4));
	} BENCH_END;

	BENCH_BEGIN("eb_is_valid") {
		eb_rand(p);
		BENCH_ADD(eb_is_valid(p));
	} BENCH_END;

	BENCH_BEGIN("eb_size_bin (0)") {
		eb_rand(p);
		BENCH_ADD(eb_size_bin(p, 0));
	} BENCH_END;

	BENCH_BEGIN("eb_size_bin (1)") {
		eb_rand(p);
		BENCH_ADD(eb_size_bin(p, 1));
	} BENCH_END;

	BENCH_BEGIN("eb_write_bin (0)") {
		eb_rand(p);
		l = eb_size_bin(p, 0);
		BENCH_ADD(eb_write_bin(bin, l, p, 0));
	} BENCH_END;

	BENCH_BEGIN("eb_write_bin (1)") {
		eb_rand(p);
		l = eb_size_bin(p, 1);
		BENCH_ADD(eb_write_bin(bin, l, p, 1));
	} BENCH_END;

	BENCH_BEGIN("eb_read_bin (0)") {
		eb_rand(p);
		l = eb_size_bin(p, 0);
		eb_write_bin(bin, l, p, 0);
		BENCH_ADD(eb_read_bin(p, bin, l));
	} BENCH_END;

	BENCH_BEGIN("eb_read_bin (1)") {
		eb_rand(p);
		l = eb_size_bin(p, 1);
		eb_write_bin(bin, l, p, 1);
		BENCH_ADD(eb_read_bin(p, bin, l));
	} BENCH_END;

	eb_free(p);
	eb_free(q);
	for (int j = 0; j < 4; j++) {
		eb_free(t[j]);
	}
}

static void arith(void) {
	eb_t p, q, r, t[EB_TABLE_MAX];
	bn_t k, l, n;

	eb_null(p);
	eb_null(q);
	eb_null(r);
	for (int i = 0; i < EB_TABLE_MAX; i++) {
		eb_null(t[i]);
	} bn_null(k);
	bn_null(l);
	bn_null(n);

	eb_new(p);
	eb_new(q);
	eb_new(r);
	bn_new(k);
	bn_new(n);
	bn_new(l);

	eb_curve_get_ord(n);

	BENCH_BEGIN("eb_add") {
		eb_rand(p);
		eb_rand(q);
		eb_add(p, p, q);
		eb_rand(q);
		eb_rand(p);
		eb_add(q, q, p);
		BENCH_ADD(eb_add(r, p, q));
	} BENCH_END;

#if EB_ADD == BASIC || !defined(STRIP)
	BENCH_BEGIN("eb_add_basic") {
		eb_rand(p);
		eb_rand(q);
		BENCH_ADD(eb_add_basic(r, p, q));
	} BENCH_END;
#endif

#if EB_ADD == PROJC || !defined(STRIP)
	BENCH_BEGIN("eb_add_projc") {
		eb_rand(p);
		eb_rand(q);
		eb_add_projc(p, p, q);
		eb_rand(q);
		eb_rand(p);
		eb_add_projc(q, q, p);
		BENCH_ADD(eb_add_projc(r, p, q));
	} BENCH_END;

	BENCH_BEGIN("eb_add_projc (z2 = 1)") {
		eb_rand(p);
		eb_rand(q);
		eb_add_projc(p, p, q);
		eb_rand(q);
		eb_norm(q, q);
		BENCH_ADD(eb_add_projc(r, p, q));
	} BENCH_END;

	BENCH_BEGIN("eb_add_projc (z1,z2 = 1)") {
		eb_rand(p);
		eb_norm(p, p);
		eb_rand(q);
		eb_norm(q, q);
		BENCH_ADD(eb_add_projc(r, p, q));
	} BENCH_END;
#endif

	BENCH_BEGIN("eb_sub") {
		eb_rand(p);
		eb_rand(q);
		eb_add(p, p, q);
		eb_rand(q);
		eb_rand(p);
		eb_add(q, q, p);
		BENCH_ADD(eb_sub(r, p, q));
	} BENCH_END;

#if EB_ADD == BASIC || !defined(STRIP)
	BENCH_BEGIN("eb_sub_basic") {
		eb_rand(p);
		eb_rand(q);
		BENCH_ADD(eb_sub_basic(r, p, q));
	} BENCH_END;
#endif

#if EB_ADD == PROJC || !defined(STRIP)
	BENCH_BEGIN("eb_sub_projc") {
		eb_rand(p);
		eb_rand(q);
		eb_add_projc(p, p, q);
		eb_rand(q);
		eb_rand(p);
		eb_add_projc(q, q, p);
		BENCH_ADD(eb_sub_projc(r, p, q));
	} BENCH_END;

	BENCH_BEGIN("eb_sub_projc (z2 = 1)") {
		eb_rand(p);
		eb_rand(q);
		eb_add_projc(p, p, q);
		eb_rand(q);
		eb_norm(q, q);
		BENCH_ADD(eb_sub_projc(r, p, q));
	} BENCH_END;

	BENCH_BEGIN("eb_sub_projc (z1,z2 = 1)") {
		eb_rand(p);
		eb_norm(p, p);
		eb_rand(q);
		eb_norm(q, q);
		BENCH_ADD(eb_sub_projc(r, p, q));
	} BENCH_END;
#endif

	BENCH_BEGIN("eb_dbl") {
		eb_rand(p);
		eb_rand(q);
		eb_add(p, p, q);
		BENCH_ADD(eb_dbl(r, p));
	} BENCH_END;

#if EB_ADD == BASIC || !defined(STRIP)
	BENCH_BEGIN("eb_dbl_basic") {
		eb_rand(p);
		BENCH_ADD(eb_dbl_basic(r, p));
	} BENCH_END;
#endif

#if EB_ADD == PROJC || !defined(STRIP)
	BENCH_BEGIN("eb_dbl_projc") {
		eb_rand(p);
		eb_rand(q);
		eb_add_projc(p, p, q);
		BENCH_ADD(eb_dbl_projc(r, p));
	} BENCH_END;

	BENCH_BEGIN("eb_dbl_projc (z1 = 1)") {
		eb_rand(p);
		eb_norm(p, p);
		BENCH_ADD(eb_dbl_projc(r, p));
	} BENCH_END;
#endif

	BENCH_BEGIN("eb_hlv") {
		eb_rand(p);
		BENCH_ADD(eb_hlv(r, p));
	}
	BENCH_END;
#if defined(EB_KBLTZ)
	if (eb_curve_is_kbltz()) {
		BENCH_BEGIN("eb_frb") {
			eb_rand(p);
			eb_rand(q);
			eb_frb(p, q);
			BENCH_ADD(eb_frb(r, p));
		}
		BENCH_END;
	}

#if EB_ADD == BASIC || !defined(STRIP)
	if (eb_curve_is_kbltz()) {
		BENCH_BEGIN("eb_frb_basic") {
			eb_rand(p);
			BENCH_ADD(eb_frb_basic(r, p));
		}
		BENCH_END;
	}
#endif

#if EB_ADD == PROJC || !defined(STRIP)
	if (eb_curve_is_kbltz()) {
		BENCH_BEGIN("eb_frb_projc") {
			eb_rand(p);
			eb_rand(q);
			eb_add_projc(p, p, q);
			BENCH_ADD(eb_frb_projc(r, p));
		}
		BENCH_END;
	}
#endif

#endif /* EB_KBLTZ */

	BENCH_BEGIN("eb_neg") {
		eb_rand(p);
		eb_rand(q);
		eb_add(p, p, q);
		BENCH_ADD(eb_neg(r, p));
	}
	BENCH_END;

#if EB_ADD == BASIC || !defined(STRIP)
	BENCH_BEGIN("eb_neg_basic") {
		eb_rand(p);
		BENCH_ADD(eb_neg_basic(r, p));
	}
	BENCH_END;
#endif

#if EB_ADD == PROJC || !defined(STRIP)
	BENCH_BEGIN("eb_neg_projc") {
		eb_rand(p);
		eb_rand(q);
		eb_add_projc(p, p, q);
		BENCH_ADD(eb_neg_projc(r, p));
	}
	BENCH_END;
#endif

	BENCH_BEGIN("eb_mul") {
		bn_rand_mod(k, n);
		eb_rand(p);
		eb_rand(q);
		BENCH_ADD(eb_mul(q, p, k));
	}
	BENCH_END;

#if EB_MUL == BASIC || !defined(STRIP)
	BENCH_BEGIN("eb_mul_basic") {
		bn_rand_mod(k, n);
		eb_rand(p);
		BENCH_ADD(eb_mul_basic(q, p, k));
	}
	BENCH_END;
#endif

#if EB_MUL == LODAH || !defined(STRIP)
	BENCH_BEGIN("eb_mul_lodah") {
		bn_rand_mod(k, n);
		eb_rand(p);
		BENCH_ADD(eb_mul_lodah(q, p, k));
	}
	BENCH_END;
#endif

#if EB_MUL == LWNAF || !defined(STRIP)
	BENCH_BEGIN("eb_mul_lwnaf") {
		bn_rand_mod(k, n);
		eb_rand(p);
		BENCH_ADD(eb_mul_lwnaf(q, p, k));
	}
	BENCH_END;
#endif

#if EB_MUL == RWNAF || !defined(STRIP)
	BENCH_BEGIN("eb_mul_rwnaf") {
		bn_rand_mod(k, n);
		eb_rand(p);
		BENCH_ADD(eb_mul_rwnaf(q, p, k));
	}
	BENCH_END;
#endif

#if EB_MUL == HALVE || !defined(STRIP)
		BENCH_BEGIN("eb_mul_halve") {
			bn_rand_mod(k, n);
			eb_rand(p);
			BENCH_ADD(eb_mul_halve(q, p, k));
		}
		BENCH_END;
#endif

	BENCH_BEGIN("eb_mul_gen") {
		bn_rand_mod(k, n);
		BENCH_ADD(eb_mul_gen(q, k));
	}
	BENCH_END;

	BENCH_BEGIN("eb_mul_dig") {
		bn_rand(k, BN_POS, BN_DIGIT);
		bn_rand_mod(k, n);
		BENCH_ADD(eb_mul_dig(p, q, k->dp[0]));
	}
	BENCH_END;

	for (int i = 0; i < EB_TABLE; i++) {
		eb_new(t[i]);
	}

	BENCH_BEGIN("eb_mul_pre") {
		eb_rand(p);
		BENCH_ADD(eb_mul_pre(t, p));
	} BENCH_END;

	BENCH_BEGIN("eb_mul_fix") {
		bn_rand_mod(k, n);
		eb_rand(p);
		eb_mul_pre(t, p);
		BENCH_ADD(eb_mul_fix(q, (const eb_t *)t, k));
	} BENCH_END;

	for (int i = 0; i < EB_TABLE; i++) {
		eb_free(t[i]);
	}

#if EB_FIX == BASIC || !defined(STRIP)
	for (int i = 0; i < EB_TABLE_BASIC; i++) {
		eb_new(t[i]);
	}
	BENCH_BEGIN("eb_mul_pre_basic") {
		eb_rand(p);
		BENCH_ADD(eb_mul_pre_basic(t, p));
	} BENCH_END;

	BENCH_BEGIN("eb_mul_fix_basic") {
		bn_rand_mod(k, n);
		eb_rand(p);
		eb_mul_pre_basic(t, p);
		BENCH_ADD(eb_mul_fix_basic(q, (const eb_t *)t, k));
	} BENCH_END;
	for (int i = 0; i < EB_TABLE_BASIC; i++) {
		eb_free(t[i]);
	}
#endif

#if EB_FIX == YAOWI || !defined(STRIP)
	for (int i = 0; i < EB_TABLE_YAOWI; i++) {
		eb_new(t[i]);
	}
	BENCH_BEGIN("eb_mul_pre_yaowi") {
		eb_rand(p);
		BENCH_ADD(eb_mul_pre_yaowi(t, p));
	} BENCH_END;

	BENCH_BEGIN("eb_mul_fix_yaowi") {
		bn_rand_mod(k, n);
		eb_rand(p);
		eb_mul_pre_yaowi(t, p);
		BENCH_ADD(eb_mul_fix_yaowi(q, (const eb_t *)t, k));
	} BENCH_END;
	for (int i = 0; i < EB_TABLE_YAOWI; i++) {
		eb_free(t[i]);
	}
#endif

#if EB_FIX == NAFWI || !defined(STRIP)
	for (int i = 0; i < EB_TABLE_NAFWI; i++) {
		eb_new(t[i]);
	}
	BENCH_BEGIN("eb_mul_pre_nafwi") {
		eb_rand(p);
		BENCH_ADD(eb_mul_pre_nafwi(t, p));
	} BENCH_END;

	BENCH_BEGIN("eb_mul_fix_nafwi") {
		bn_rand_mod(k, n);
		eb_rand(p);
		eb_mul_pre_nafwi(t, p);
		BENCH_ADD(eb_mul_fix_nafwi(q, (const eb_t *)t, k));
	} BENCH_END;
	for (int i = 0; i < EB_TABLE_NAFWI; i++) {
		eb_free(t[i]);
	}
#endif

#if EB_FIX == COMBS || !defined(STRIP)
	for (int i = 0; i < EB_TABLE_COMBS; i++) {
		eb_new(t[i]);
	}
	BENCH_BEGIN("eb_mul_pre_combs") {
		eb_rand(p);
		BENCH_ADD(eb_mul_pre_combs(t, p));
	} BENCH_END;

	BENCH_BEGIN("eb_mul_fix_combs") {
		bn_rand_mod(k, n);
		eb_rand(p);
		eb_mul_pre_combs(t, p);
		BENCH_ADD(eb_mul_fix_combs(q, (const eb_t *)t, k));
	} BENCH_END;
	for (int i = 0; i < EB_TABLE_COMBS; i++) {
		eb_free(t[i]);
	}
#endif

#if EB_FIX == COMBD || !defined(STRIP)
	for (int i = 0; i < EB_TABLE_COMBD; i++) {
		eb_new(t[i]);
	}
	BENCH_BEGIN("eb_mul_pre_combd") {
		eb_rand(p);
		BENCH_ADD(eb_mul_pre_combd(t, p));
	} BENCH_END;

	BENCH_BEGIN("eb_mul_fix_combd") {
		bn_rand_mod(k, n);
		eb_rand(p);
		eb_mul_pre_combd(t, p);
		BENCH_ADD(eb_mul_fix_combd(q, (const eb_t *)t, k));
	} BENCH_END;
	for (int i = 0; i < EB_TABLE_COMBD; i++) {
		eb_free(t[i]);
	}
#endif

#if EB_FIX == LWNAF || !defined(STRIP)
	for (int i = 0; i < EB_TABLE_LWNAF; i++) {
		eb_new(t[i]);
	}
	BENCH_BEGIN("eb_mul_pre_lwnaf") {
		eb_rand(p);
		BENCH_ADD(eb_mul_pre_lwnaf(t, p));
	} BENCH_END;

	BENCH_BEGIN("eb_mul_fix_lwnaf") {
		bn_rand_mod(k, n);
		eb_rand(p);
		eb_mul_pre_lwnaf(t, p);
		BENCH_ADD(eb_mul_fix_lwnaf(q, (const eb_t *)t, k));
	} BENCH_END;
	for (int i = 0; i < EB_TABLE_LWNAF; i++) {
		eb_free(t[i]);
	}
#endif

	BENCH_BEGIN("eb_mul_sim") {
		bn_rand_mod(k, n);
		bn_rand_mod(l, n);
		eb_rand(p);
		eb_rand(q);
		BENCH_ADD(eb_mul_sim(r, p, k, q, l));
	} BENCH_END;

#if EB_SIM == BASIC || !defined(STRIP)
	BENCH_BEGIN("eb_mul_sim_basic") {
		bn_rand_mod(k, n);
		bn_rand_mod(l, n);
		eb_rand(p);
		eb_rand(q);
		BENCH_ADD(eb_mul_sim_basic(r, p, k, q, l));
	} BENCH_END;
#endif

#if EB_SIM == TRICK || !defined(STRIP)
	BENCH_BEGIN("eb_mul_sim_trick") {
		bn_rand_mod(k, n);
		bn_rand_mod(l, n);
		eb_rand(p);
		eb_rand(q);
		BENCH_ADD(eb_mul_sim_trick(r, p, k, q, l));
	} BENCH_END;
#endif

#if EB_SIM == INTER || !defined(STRIP)
	BENCH_BEGIN("eb_mul_sim_inter") {
		bn_rand_mod(k, n);
		bn_rand_mod(l, n);
		eb_rand(p);
		eb_rand(q);
		BENCH_ADD(eb_mul_sim_inter(r, p, k, q, l));
	} BENCH_END;
#endif

#if EB_SIM == JOINT || !defined(STRIP)
	BENCH_BEGIN("eb_mul_sim_joint") {
		bn_rand_mod(k, n);
		bn_rand_mod(l, n);
		eb_rand(p);
		eb_rand(q);
		BENCH_ADD(eb_mul_sim_joint(r, p, k, q, l));
	} BENCH_END;
#endif

	BENCH_BEGIN("eb_mul_sim_gen") {
		bn_rand_mod(k, n);
		bn_rand_mod(l, n);
		eb_rand(q);
		BENCH_ADD(eb_mul_sim_gen(r, k, q, l));
	} BENCH_END;

	BENCH_BEGIN("eb_map") {
		uint8_t msg[5];
		rand_bytes(msg, 5);
		BENCH_ADD(eb_map(p, msg, 5));
	} BENCH_END;

	BENCH_BEGIN("eb_pck") {
		eb_rand(p);
		BENCH_ADD(eb_pck(q, p));
	} BENCH_END;

	BENCH_BEGIN("eb_upk") {
		eb_rand(p);
		BENCH_ADD(eb_upk(q, p));
	} BENCH_END;

	eb_free(p);
	eb_free(q);
	bn_free(k);
	bn_free(l);
	bn_free(n);
}

static void bench(void) {
	eb_param_print();
	util_banner("Utilities:", 1);
	memory();
	util();
	util_banner("Arithmetic:", 1);
	arith();
}

int main(void) {
	int r0 = STS_ERR, r1 = STS_ERR;

	if (core_init() != STS_OK) {
		core_clean();
		return 1;
	}

	conf_print();
	util_banner("Benchmarks for the EB module:", 0);

	r0 = eb_param_set_any_plain();

	if (r0 == STS_OK) {

	//eb_t p, q, p_ref;//, r, t[EB_TABLE_MAX];
	bn_t k, l, n;
	int kk;

	//eb_null(p);
	//eb_null(q);
	//eb_null(p_ref);
	bn_null(n);

	//eb_new(p);
	//eb_new(q);
	//eb_new(p_ref);
	bn_new(n);

	eb_curve_get_ord(n);

// EB_ADD
	util_print("\n-- fb_inv:			");
	eb_t p = {{{0x4d434a0eff05220, 0xe373cd9a4b74c2aa, 0x8b41871094a27bde, 0xdf467ffcca25147d, 0xc0d568}, {0xe27e290ff88ff78c, 0xce1d239ec07f1449, 0x1363e78bb1af26fe, 0xaede486a6b63ac7b, 0x27886a},{0x1, 0x0, 0x0, 0x0, 0x0}}}; 
	eb_t q = {{{0x8aa7e5987efaba64, 0xa55a46917fe67aed, 0xbde6a467b4127ff4, 0x9703a1fe2597ed3a, 0x43cb4fe}, {0x2d6d35cd34702bda, 0xc02735ce335b656c, 0x9e4644ee15533aa5, 0x618028cf49413f0c, 0x3fbe65a}, {0x1, 0x0, 0x0, 0x0, 0x0}}}; 
	
	/* arm
	eb_t p = {{{0xeff05220, 0x4d434a0, 0x4b74c2aa, 0xe373cd9a, 0x94a27bde, 0x8b418710, 0xca25147d, 0xdf467ffc, 0xc0d568}, {0xf88ff78c, 0xe27e290f, 0xc07f1449, 0xce1d239e, 0xb1af26fe, 0x1363e78b, 0x6b63ac7b, 0xaede486a, 0x27886a}, {0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}}}; 
	
	eb_t q = {{{0x7efaba64, 0x8aa7e598, 0x7fe67aed, 0xa55a4691, 0xb4127ff4, 0xbde6a467, 0x2597ed3a, 0x9703a1fe, 0x43cb4fe}, {0x34702bda, 0x2d6d35cd, 0x335b656c, 0xc02735ce, 0x15533aa5, 0x9e4644ee, 0x49413f0c, 0x618028cf, 0x3fbe65a}, {0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}}}; 
*/
	
	eb_t p_ref= {{{0x296a88bdcc5cd50, 0x86496f5b65263580, 0xb79d983e1870d15f, 0xaedcbde639681d33, 0x758a42b}, {0x4dca4de5fb7e9812, 0x89cae6122be24d8, 0x6a6d93df644b549c, 0x301b6d172c0a9d68, 0x325336}, {0xae8caeb45b4dfd0d, 0xdd1d19c86ef28bba, 0x3f98bd3044a44e1c, 0x30117066924f097, 0x4bac754}}}; 

	/*arm
	eb_t p_ref = {{{0xdcc5cd50, 0x296a88b, 0x65263580, 0x86496f5b, 0x1870d15f, 0xb79d983e, 0x39681d33, 0xaedcbde6, 0x758a42b}, {0xfb7e9812, 0x4dca4de5, 0x22be24d8, 0x89cae61, 0x644b549c, 0x6a6d93df, 0x2c0a9d68, 0x301b6d17, 0x325336}, {0x5b4dfd0d, 0xae8caeb4, 0x6ef28bba, 0xdd1d19c8, 0x44a44e1c, 0x3f98bd30, 0x6924f097, 0x3011706, 0x4bac754}}}; 
	*/

	eb_add(p, p, q);

	bool	correctness = true;
	for (kk=0;kk<FB_DIGS;kk++) {
		printf("p->x[%d] = 0x%llx;\n",kk,p->x[kk]);
		if(p->x[kk]!=p_ref->x[kk]) {
			printf("p/p_ref->x [%d] not match! p[%d] = 0x%llx; p_ref[%d] = 0x%llx\n",kk, kk,p->x[kk],kk,p_ref->x[kk]);
			correctness = false;
		}
	}
	for (kk=0;kk<FB_DIGS;kk++) {
		printf("p->y[%d] = 0x%llx;\n",kk,p->y[kk]);
		if(p->y[kk]!=p_ref->y[kk]) {
			printf("p/p_ref->y [%d] not match! p[%d] = 0x%llx; p_ref[%d] = 0x%llx\n",kk, kk,p->y[kk],kk,p_ref->y[kk]);
			correctness = false;
		}
	}
	for (kk=0;kk<FB_DIGS;kk++) {
		printf("p->z[%d] = 0x%llx;\n",kk,p->z[kk]);
		if(p->z[kk]!=p_ref->z[kk]) {
			printf("p/p_ref->z [%d] not match! p[%d] = 0x%llx; p_ref[%d] = 0x%llx\n",kk, kk,p->z[kk],kk,p_ref->z[kk]);
			correctness = false;
		}
	}

	if (correctness) printf("	Pass!\n");
	else						 printf("	Fail!\n");
	

	}

	core_clean();
	return 0;
}
