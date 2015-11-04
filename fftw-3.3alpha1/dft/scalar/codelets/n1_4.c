/*
 * Copyright (c) 2003, 2007-8 Matteo Frigo
 * Copyright (c) 2003, 2007-8 Massachusetts Institute of Technology
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

/* This file was automatically generated --- DO NOT EDIT */
/* Generated on Sat Nov 15 20:36:51 EST 2008 */

#include "codelet-dft.h"

#ifdef HAVE_FMA

/* Generated by: ../../../genfft/gen_notw -fma -reorder-insns -schedule-for-pipeline -compact -variables 4 -pipeline-latency 4 -n 4 -name n1_4 -include n.h */

/*
 * This function contains 16 FP additions, 0 FP multiplications,
 * (or, 16 additions, 0 multiplications, 0 fused multiply/add),
 * 13 stack variables, 0 constants, and 16 memory accesses
 */
#include "n.h"

static void n1_4(const R *ri, const R *ii, R *ro, R *io, stride is, stride os, INT v, INT ivs, INT ovs)
{
     INT i;
     for (i = v; i > 0; i = i - 1, ri = ri + ivs, ii = ii + ivs, ro = ro + ovs, io = io + ovs, MAKE_VOLATILE_STRIDE(is), MAKE_VOLATILE_STRIDE(os)) {
	  E T4, Tb, T3, Tf, T9, T5, Tc, Td;
	  {
	       E T1, T2, T7, T8;
	       T1 = ri[0];
	       T2 = ri[WS(is, 2)];
	       T7 = ii[0];
	       T8 = ii[WS(is, 2)];
	       T4 = ri[WS(is, 1)];
	       Tb = T1 - T2;
	       T3 = T1 + T2;
	       Tf = T7 + T8;
	       T9 = T7 - T8;
	       T5 = ri[WS(is, 3)];
	       Tc = ii[WS(is, 1)];
	       Td = ii[WS(is, 3)];
	  }
	  {
	       E T6, Ta, Te, Tg;
	       T6 = T4 + T5;
	       Ta = T4 - T5;
	       Te = Tc - Td;
	       Tg = Tc + Td;
	       io[WS(os, 3)] = Ta + T9;
	       io[WS(os, 1)] = T9 - Ta;
	       ro[0] = T3 + T6;
	       ro[WS(os, 2)] = T3 - T6;
	       io[0] = Tf + Tg;
	       io[WS(os, 2)] = Tf - Tg;
	       ro[WS(os, 3)] = Tb - Te;
	       ro[WS(os, 1)] = Tb + Te;
	  }
     }
}

static const kdft_desc desc = { 4, "n1_4", {16, 0, 0, 0}, &GENUS, 0, 0, 0, 0 };
void X(codelet_n1_4) (planner *p) {
     X(kdft_register) (p, n1_4, &desc);
}

#else				/* HAVE_FMA */

/* Generated by: ../../../genfft/gen_notw -compact -variables 4 -pipeline-latency 4 -n 4 -name n1_4 -include n.h */

/*
 * This function contains 16 FP additions, 0 FP multiplications,
 * (or, 16 additions, 0 multiplications, 0 fused multiply/add),
 * 13 stack variables, 0 constants, and 16 memory accesses
 */
#include "n.h"

static void n1_4(const R *ri, const R *ii, R *ro, R *io, stride is, stride os, INT v, INT ivs, INT ovs)
{
     INT i;
     for (i = v; i > 0; i = i - 1, ri = ri + ivs, ii = ii + ivs, ro = ro + ovs, io = io + ovs, MAKE_VOLATILE_STRIDE(is), MAKE_VOLATILE_STRIDE(os)) {
	  E T3, Tb, T9, Tf, T6, Ta, Te, Tg;
	  {
	       E T1, T2, T7, T8;
	       T1 = ri[0];
	       T2 = ri[WS(is, 2)];
	       T3 = T1 + T2;
	       Tb = T1 - T2;
	       T7 = ii[0];
	       T8 = ii[WS(is, 2)];
	       T9 = T7 - T8;
	       Tf = T7 + T8;
	  }
	  {
	       E T4, T5, Tc, Td;
	       T4 = ri[WS(is, 1)];
	       T5 = ri[WS(is, 3)];
	       T6 = T4 + T5;
	       Ta = T4 - T5;
	       Tc = ii[WS(is, 1)];
	       Td = ii[WS(is, 3)];
	       Te = Tc - Td;
	       Tg = Tc + Td;
	  }
	  ro[WS(os, 2)] = T3 - T6;
	  io[WS(os, 2)] = Tf - Tg;
	  ro[0] = T3 + T6;
	  io[0] = Tf + Tg;
	  io[WS(os, 1)] = T9 - Ta;
	  ro[WS(os, 1)] = Tb + Te;
	  io[WS(os, 3)] = Ta + T9;
	  ro[WS(os, 3)] = Tb - Te;
     }
}

static const kdft_desc desc = { 4, "n1_4", {16, 0, 0, 0}, &GENUS, 0, 0, 0, 0 };
void X(codelet_n1_4) (planner *p) {
     X(kdft_register) (p, n1_4, &desc);
}

#endif				/* HAVE_FMA */
