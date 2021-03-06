/* Mulator - An extensible {ARM} {e,si}mulator
 * Copyright 2011-2016  Pat Pannuto <pat.pannuto@gmail.com>
 *
 * This file is part of Mulator.
 *
 * Mulator is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Mulator is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Mulator.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "core/isa/opcodes.h"
#include "core/isa/decode_helpers.h"

#include "core/operations/ldm.h"

// arm-thumb
static void ldm_t1(uint16_t inst) {
	uint8_t registers = inst & 0xff;
	uint8_t rn = (inst >> 8) & 0x7;
	
	// If rn is not in Reglist, writeback suffix
	bool wback = ~(registers & (1 << rn));

	if (hamming(registers) < 1)
		CORE_ERR_unpredictable("ldm_t1 load no regs?\n");

	OP_DECOMPILE("LDM<c> <Rn>!,<registers>",rn, registers);

	return ldm(rn, registers, wback);
}

__attribute__ ((constructor))
static void register_opcodes_arm_thumb_ldm(void) {
	// ldm_t1: 1100 1<x's>
	register_opcode_mask_16(0xc800, 0x3000, ldm_t1);
}

