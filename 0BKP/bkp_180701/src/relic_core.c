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
 * Implementation of the library basic functions.
 *
 * @ingroup relic
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "relic_core.h"
#include "relic_rand.h"
#include "relic_types.h"
#include "relic_err.h"
#include "relic_arch.h"
#include "relic_fp.h"
#include "relic_fb.h"
#include "relic_ep.h"
#include "relic_eb.h"
#include "relic_cp.h"
#include "relic_pp.h"

/*============================================================================*/
/* Public definitions                                                         */
/*============================================================================*/

/**
 * If multi-threading is enabled, assigns each thread a local copy of the data.
 */
#if MULTI == PTHREAD
#define thread 	__thread
#else
#define thread /* */
#endif

/**
 * Default library context.
 */
thread ctx_t first_ctx;

/**
 * Active library context.
 */
thread ctx_t *core_ctx = NULL;

#if MULTI == OPENMP
#pragma omp threadprivate(first_ctx, core_ctx)
#endif

int core_init() {
	if (core_ctx == NULL) {
		core_ctx = &(first_ctx);
	}
	// add some output to addr_c here after each step.

#if defined(CHECK) && defined(TRACE)
	core_ctx->trace = 0;
#endif

#ifdef CHECK
	core_ctx->reason[ERR_NO_MEMORY] = MSG_NO_MEMORY;
	core_ctx->reason[ERR_NO_PRECI] = MSG_NO_PRECI;
	core_ctx->reason[ERR_NO_FILE] = MSG_NO_FILE;
	core_ctx->reason[ERR_NO_READ] = MSG_NO_READ;
	core_ctx->reason[ERR_NO_VALID] = MSG_NO_VALID;
	core_ctx->reason[ERR_NO_BUFFER] = MSG_NO_BUFFER;
	core_ctx->reason[ERR_NO_FIELD] = MSG_NO_FIELD;
	core_ctx->reason[ERR_NO_CURVE] = MSG_NO_CURVE;
	core_ctx->reason[ERR_NO_CONFIG] = MSG_NO_CONFIG;
	core_ctx->last = NULL;
#endif /* CHECK */

#if ALLOC == STATIC
	core_ctx->next = 0;
#endif

#ifdef OVERH
	core_ctx->over = 0;
#endif

	core_ctx->code = STS_OK;

	TRY {
		arch_init();
		rand_init();
#ifdef WITH_FP
		fp_prime_init();
#endif
#ifdef WITH_FB
		fb_poly_init();
#endif
#ifdef WITH_FT
		ft_poly_init();
#endif
#ifdef WITH_EP
		ep_curve_init();
#endif
#ifdef WITH_EB
		eb_curve_init();
#endif
#ifdef WITH_ED
		ed_curve_init();
#endif
#ifdef WITH_PP
		pp_map_init();
#endif
	}
	CATCH_ANY {
		return STS_ERR;
	}

	return STS_OK;
}

int core_init_test(volatile int* addr_c) {
	*(addr_c) = 0x111;
	*(addr_c) = (volatile int) core_ctx;
	if (core_ctx == NULL) {
		// print the value of core_ctx to addr_rc.
	*(addr_c) = (volatile int) core_ctx;
		core_ctx = &(first_ctx);
		// print the value of core_ctx to addr_rc.
	*(addr_c) = (volatile int) core_ctx;
	}
	// add some output to addr_c here after each step.
	// and one here.

#if defined(CHECK) && defined(TRACE)
	core_ctx->trace = 0;
#endif

#ifdef CHECK
	core_ctx->reason[ERR_NO_MEMORY] = MSG_NO_MEMORY;
	core_ctx->reason[ERR_NO_PRECI] = MSG_NO_PRECI;
	core_ctx->reason[ERR_NO_FILE] = MSG_NO_FILE;
	core_ctx->reason[ERR_NO_READ] = MSG_NO_READ;
	core_ctx->reason[ERR_NO_VALID] = MSG_NO_VALID;
	core_ctx->reason[ERR_NO_BUFFER] = MSG_NO_BUFFER;
	core_ctx->reason[ERR_NO_FIELD] = MSG_NO_FIELD;
	core_ctx->reason[ERR_NO_CURVE] = MSG_NO_CURVE;
	core_ctx->reason[ERR_NO_CONFIG] = MSG_NO_CONFIG;
	core_ctx->last = NULL;
#endif /* CHECK */
	*(addr_c) = 0x222;

#if ALLOC == STATIC
	core_ctx->next = 0;
#endif

#ifdef OVERH
	core_ctx->over = 0;
#endif

	*(addr_c) = 0x333; //stuck here
//YQ this is hard to exec
// core_ctx->code = STS_OK;

	*(addr_c) = 0x301;
	TRY {
	*(addr_c) = 0x444;
		arch_init();
	*(addr_c) = 0x555; //stuck here

//YQ this is hard to exec
// rand_init();
	core_get()->seeded = 0;

	*(addr_c) = 0x666;
#ifdef WITH_FP
		fp_prime_init();
#endif
#ifdef WITH_FB
	*(addr_c) = 0x777;
		fb_poly_init();
	*(addr_c) = 0x888;
#endif
#ifdef WITH_FT
		ft_poly_init();
#endif
#ifdef WITH_EP
		ep_curve_init();
#endif
#ifdef WITH_EB
		eb_curve_init();
#endif
#ifdef WITH_ED
		ed_curve_init();
#endif
#ifdef WITH_PP
		pp_map_init();
#endif
	}
	CATCH_ANY {
	*(addr_c) = 0x302;
		return STS_ERR;
	}

	return STS_OK;
}
int core_clean(void) {
	rand_clean();
#ifdef WITH_FP
	fp_prime_clean();
#endif
#ifdef WITH_FB
	fb_poly_clean();
#endif
#ifdef WITH_FT
	ft_poly_clean();
#endif
#ifdef WITH_EP
	ep_curve_clean();
#endif
#ifdef WITH_EB
	eb_curve_clean();
#endif
#ifdef WITH_ED
	ed_curve_clean();
#endif
#ifdef WITH_PP
	pp_map_clean();
#endif
	arch_clean();
	core_ctx = NULL;
	return STS_OK;
}

ctx_t *core_get() {
	return core_ctx;
}

void core_set(ctx_t *ctx) {
	core_ctx = ctx;
}
