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
/* Generated on Sat Nov 15 20:44:54 EST 2008 */

#include "codelet-dft.h"

#ifdef HAVE_FMA

/* Generated by: ../../../genfft/gen_notw_c -fma -reorder-insns -schedule-for-pipeline -simd -compact -variables 4 -pipeline-latency 8 -n 6 -name n2fv_6 -with-ostride 2 -include n2f.h -store-multiple 2 */

/*
 * This function contains 18 FP additions, 8 FP multiplications,
 * (or, 12 additions, 2 multiplications, 6 fused multiply/add),
 * 29 stack variables, 2 constants, and 15 memory accesses
 */
#include "n2f.h"

static void n2fv_6(const R *ri, const R *ii, R *ro, R *io, stride is, stride os, INT v, INT ivs, INT ovs)
{
     DVK(KP500000000, +0.500000000000000000000000000000000000000000000);
     DVK(KP866025403, +0.866025403784438646763723170752936183471402627);
     INT i;
     const R *xi;
     R *xo;
     xi = ri;
     xo = ro;
     for (i = v; i > 0; i = i - VL, xi = xi + (VL * ivs), xo = xo + (VL * ovs), MAKE_VOLATILE_STRIDE(is), MAKE_VOLATILE_STRIDE(os)) {
	  V T1, T2, T4, T5, T7, T8;
	  T1 = LD(&(xi[0]), ivs, &(xi[0]));
	  T2 = LD(&(xi[WS(is, 3)]), ivs, &(xi[WS(is, 1)]));
	  T4 = LD(&(xi[WS(is, 2)]), ivs, &(xi[0]));
	  T5 = LD(&(xi[WS(is, 5)]), ivs, &(xi[WS(is, 1)]));
	  T7 = LD(&(xi[WS(is, 4)]), ivs, &(xi[0]));
	  T8 = LD(&(xi[WS(is, 1)]), ivs, &(xi[WS(is, 1)]));
	  {
	       V T3, Td, T6, Te, T9, Tf;
	       T3 = VSUB(T1, T2);
	       Td = VADD(T1, T2);
	       T6 = VSUB(T4, T5);
	       Te = VADD(T4, T5);
	       T9 = VSUB(T7, T8);
	       Tf = VADD(T7, T8);
	       {
		    V Tg, Ti, Ta, Tc;
		    Tg = VADD(Te, Tf);
		    Ti = VMUL(LDK(KP866025403), VSUB(Tf, Te));
		    Ta = VADD(T6, T9);
		    Tc = VMUL(LDK(KP866025403), VSUB(T9, T6));
		    {
			 V Th, Tj, Tb, Tk;
			 Th = VFNMS(LDK(KP500000000), Tg, Td);
			 Tj = VADD(Td, Tg);
			 STM2(&(xo[0]), Tj, ovs, &(xo[0]));
			 Tb = VFNMS(LDK(KP500000000), Ta, T3);
			 Tk = VADD(T3, Ta);
			 STM2(&(xo[6]), Tk, ovs, &(xo[2]));
			 {
			      V Tl, Tm, Tn, To;
			      Tl = VFMAI(Ti, Th);
			      STM2(&(xo[8]), Tl, ovs, &(xo[0]));
			      Tm = VFNMSI(Ti, Th);
			      STM2(&(xo[4]), Tm, ovs, &(xo[0]));
			      STN2(&(xo[4]), Tm, Tk, ovs);
			      Tn = VFMAI(Tc, Tb);
			      STM2(&(xo[2]), Tn, ovs, &(xo[2]));
			      STN2(&(xo[0]), Tj, Tn, ovs);
			      To = VFNMSI(Tc, Tb);
			      STM2(&(xo[10]), To, ovs, &(xo[2]));
			      STN2(&(xo[8]), Tl, To, ovs);
			 }
		    }
	       }
	  }
     }
}

static const kdft_desc desc = { 6, "n2fv_6", {12, 2, 6, 0}, &GENUS, 0, 2, 0, 0 };
void X(codelet_n2fv_6) (planner *p) {
     X(kdft_register) (p, n2fv_6, &desc);
}

#else				/* HAVE_FMA */

/* Generated by: ../../../genfft/gen_notw_c -simd -compact -variables 4 -pipeline-latency 8 -n 6 -name n2fv_6 -with-ostride 2 -include n2f.h -store-multiple 2 */

/*
 * This function contains 18 FP additions, 4 FP multiplications,
 * (or, 16 additions, 2 multiplications, 2 fused multiply/add),
 * 25 stack variables, 2 constants, and 15 memory accesses
 */
#include "n2f.h"

static void n2fv_6(const R *ri, const R *ii, R *ro, R *io, stride is, stride os, INT v, INT ivs, INT ovs)
{
     DVK(KP866025403, +0.866025403784438646763723170752936183471402627);
     DVK(KP500000000, +0.500000000000000000000000000000000000000000000);
     INT i;
     const R *xi;
     R *xo;
     xi = ri;
     xo = ro;
     for (i = v; i > 0; i = i - VL, xi = xi + (VL * ivs), xo = xo + (VL * ovs), MAKE_VOLATILE_STRIDE(is), MAKE_VOLATILE_STRIDE(os)) {
	  V T3, Td, T6, Te, T9, Tf, Ta, Tg, T1, T2, Tj, Tk;
	  T1 = LD(&(xi[0]), ivs, &(xi[0]));
	  T2 = LD(&(xi[WS(is, 3)]), ivs, &(xi[WS(is, 1)]));
	  T3 = VSUB(T1, T2);
	  Td = VADD(T1, T2);
	  {
	       V T4, T5, T7, T8;
	       T4 = LD(&(xi[WS(is, 2)]), ivs, &(xi[0]));
	       T5 = LD(&(xi[WS(is, 5)]), ivs, &(xi[WS(is, 1)]));
	       T6 = VSUB(T4, T5);
	       Te = VADD(T4, T5);
	       T7 = LD(&(xi[WS(is, 4)]), ivs, &(xi[0]));
	       T8 = LD(&(xi[WS(is, 1)]), ivs, &(xi[WS(is, 1)]));
	       T9 = VSUB(T7, T8);
	       Tf = VADD(T7, T8);
	  }
	  Ta = VADD(T6, T9);
	  Tg = VADD(Te, Tf);
	  Tj = VADD(T3, Ta);
	  STM2(&(xo[6]), Tj, ovs, &(xo[2]));
	  Tk = VADD(Td, Tg);
	  STM2(&(xo[0]), Tk, ovs, &(xo[0]));
	  {
	       V Tl, Tb, Tc, Tm;
	       Tb = VFNMS(LDK(KP500000000), Ta, T3);
	       Tc = VBYI(VMUL(LDK(KP866025403), VSUB(T9, T6)));
	       Tl = VSUB(Tb, Tc);
	       STM2(&(xo[10]), Tl, ovs, &(xo[2]));
	       Tm = VADD(Tb, Tc);
	       STM2(&(xo[2]), Tm, ovs, &(xo[2]));
	       STN2(&(xo[0]), Tk, Tm, ovs);
	       {
		    V Th, Ti, Tn, To;
		    Th = VFNMS(LDK(KP500000000), Tg, Td);
		    Ti = VBYI(VMUL(LDK(KP866025403), VSUB(Tf, Te)));
		    Tn = VSUB(Th, Ti);
		    STM2(&(xo[4]), Tn, ovs, &(xo[0]));
		    STN2(&(xo[4]), Tn, Tj, ovs);
		    To = VADD(Th, Ti);
		    STM2(&(xo[8]), To, ovs, &(xo[0]));
		    STN2(&(xo[8]), To, Tl, ovs);
	       }
	  }
     }
}

static const kdft_desc desc = { 6, "n2fv_6", {16, 2, 2, 0}, &GENUS, 0, 2, 0, 0 };
void X(codelet_n2fv_6) (planner *p) {
     X(kdft_register) (p, n2fv_6, &desc);
}

#endif				/* HAVE_FMA */
