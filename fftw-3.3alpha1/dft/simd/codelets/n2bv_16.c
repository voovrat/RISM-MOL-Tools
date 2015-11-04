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
/* Generated on Sat Nov 15 20:45:49 EST 2008 */

#include "codelet-dft.h"

#ifdef HAVE_FMA

/* Generated by: ../../../genfft/gen_notw_c -fma -reorder-insns -schedule-for-pipeline -simd -compact -variables 4 -pipeline-latency 8 -sign 1 -n 16 -name n2bv_16 -with-ostride 2 -include n2b.h -store-multiple 2 */

/*
 * This function contains 72 FP additions, 34 FP multiplications,
 * (or, 38 additions, 0 multiplications, 34 fused multiply/add),
 * 62 stack variables, 3 constants, and 40 memory accesses
 */
#include "n2b.h"

static void n2bv_16(const R *ri, const R *ii, R *ro, R *io, stride is, stride os, INT v, INT ivs, INT ovs)
{
     DVK(KP923879532, +0.923879532511286756128183189396788286822416626);
     DVK(KP414213562, +0.414213562373095048801688724209698078569671875);
     DVK(KP707106781, +0.707106781186547524400844362104849039284835938);
     INT i;
     const R *xi;
     R *xo;
     xi = ii;
     xo = io;
     for (i = v; i > 0; i = i - VL, xi = xi + (VL * ivs), xo = xo + (VL * ovs), MAKE_VOLATILE_STRIDE(is), MAKE_VOLATILE_STRIDE(os)) {
	  V T7, Tu, TF, TB, T13, TL, TO, TX, TC, Te, TP, Th, TQ, Tk, TW;
	  V T16;
	  {
	       V TH, TU, Tz, Tf, TK, TV, TA, TM, Ta, TN, Td, Tg, Ti, Tj;
	       {
		    V T1, T2, T4, T5, To, Tp, Tr, Ts;
		    T1 = LD(&(xi[0]), ivs, &(xi[0]));
		    T2 = LD(&(xi[WS(is, 8)]), ivs, &(xi[0]));
		    T4 = LD(&(xi[WS(is, 4)]), ivs, &(xi[0]));
		    T5 = LD(&(xi[WS(is, 12)]), ivs, &(xi[0]));
		    To = LD(&(xi[WS(is, 2)]), ivs, &(xi[0]));
		    Tp = LD(&(xi[WS(is, 10)]), ivs, &(xi[0]));
		    Tr = LD(&(xi[WS(is, 14)]), ivs, &(xi[0]));
		    Ts = LD(&(xi[WS(is, 6)]), ivs, &(xi[0]));
		    {
			 V T8, TI, Tq, TJ, Tt, T9, Tb, Tc, T3, T6;
			 T8 = LD(&(xi[WS(is, 1)]), ivs, &(xi[WS(is, 1)]));
			 TH = VSUB(T1, T2);
			 T3 = VADD(T1, T2);
			 TU = VSUB(T4, T5);
			 T6 = VADD(T4, T5);
			 TI = VSUB(To, Tp);
			 Tq = VADD(To, Tp);
			 TJ = VSUB(Tr, Ts);
			 Tt = VADD(Tr, Ts);
			 T9 = LD(&(xi[WS(is, 9)]), ivs, &(xi[WS(is, 1)]));
			 Tb = LD(&(xi[WS(is, 5)]), ivs, &(xi[WS(is, 1)]));
			 Tc = LD(&(xi[WS(is, 13)]), ivs, &(xi[WS(is, 1)]));
			 T7 = VSUB(T3, T6);
			 Tz = VADD(T3, T6);
			 Tf = LD(&(xi[WS(is, 15)]), ivs, &(xi[WS(is, 1)]));
			 TK = VADD(TI, TJ);
			 TV = VSUB(TI, TJ);
			 TA = VADD(Tq, Tt);
			 Tu = VSUB(Tq, Tt);
			 TM = VSUB(T8, T9);
			 Ta = VADD(T8, T9);
			 TN = VSUB(Tb, Tc);
			 Td = VADD(Tb, Tc);
			 Tg = LD(&(xi[WS(is, 7)]), ivs, &(xi[WS(is, 1)]));
			 Ti = LD(&(xi[WS(is, 3)]), ivs, &(xi[WS(is, 1)]));
			 Tj = LD(&(xi[WS(is, 11)]), ivs, &(xi[WS(is, 1)]));
		    }
	       }
	       TF = VADD(Tz, TA);
	       TB = VSUB(Tz, TA);
	       T13 = VFNMS(LDK(KP707106781), TK, TH);
	       TL = VFMA(LDK(KP707106781), TK, TH);
	       TO = VFNMS(LDK(KP414213562), TN, TM);
	       TX = VFMA(LDK(KP414213562), TM, TN);
	       TC = VADD(Ta, Td);
	       Te = VSUB(Ta, Td);
	       TP = VSUB(Tf, Tg);
	       Th = VADD(Tf, Tg);
	       TQ = VSUB(Tj, Ti);
	       Tk = VADD(Ti, Tj);
	       TW = VFMA(LDK(KP707106781), TV, TU);
	       T16 = VFNMS(LDK(KP707106781), TV, TU);
	  }
	  {
	       V TY, TR, Tl, TD;
	       TY = VFMA(LDK(KP414213562), TP, TQ);
	       TR = VFNMS(LDK(KP414213562), TQ, TP);
	       Tl = VSUB(Th, Tk);
	       TD = VADD(Th, Tk);
	       {
		    V TS, T17, TZ, T14;
		    TS = VADD(TO, TR);
		    T17 = VSUB(TO, TR);
		    TZ = VSUB(TX, TY);
		    T14 = VADD(TX, TY);
		    {
			 V TE, TG, Tm, Tv;
			 TE = VSUB(TC, TD);
			 TG = VADD(TC, TD);
			 Tm = VADD(Te, Tl);
			 Tv = VSUB(Te, Tl);
			 {
			      V T18, T1a, TT, T11;
			      T18 = VFMA(LDK(KP923879532), T17, T16);
			      T1a = VFNMS(LDK(KP923879532), T17, T16);
			      TT = VFNMS(LDK(KP923879532), TS, TL);
			      T11 = VFMA(LDK(KP923879532), TS, TL);
			      {
				   V T15, T19, T10, T12;
				   T15 = VFNMS(LDK(KP923879532), T14, T13);
				   T19 = VFMA(LDK(KP923879532), T14, T13);
				   T10 = VFNMS(LDK(KP923879532), TZ, TW);
				   T12 = VFMA(LDK(KP923879532), TZ, TW);
				   {
					V T1b, T1c, T1d, T1e;
					T1b = VADD(TF, TG);
					STM2(&(xo[0]), T1b, ovs, &(xo[0]));
					T1c = VSUB(TF, TG);
					STM2(&(xo[16]), T1c, ovs, &(xo[0]));
					T1d = VFMAI(TE, TB);
					STM2(&(xo[8]), T1d, ovs, &(xo[0]));
					T1e = VFNMSI(TE, TB);
					STM2(&(xo[24]), T1e, ovs, &(xo[0]));
					{
					     V Tw, Ty, Tn, Tx;
					     Tw = VFNMS(LDK(KP707106781), Tv, Tu);
					     Ty = VFMA(LDK(KP707106781), Tv, Tu);
					     Tn = VFNMS(LDK(KP707106781), Tm, T7);
					     Tx = VFMA(LDK(KP707106781), Tm, T7);
					     {
						  V T1f, T1g, T1h, T1i;
						  T1f = VFNMSI(T1a, T19);
						  STM2(&(xo[6]), T1f, ovs, &(xo[2]));
						  T1g = VFMAI(T1a, T19);
						  STM2(&(xo[26]), T1g, ovs, &(xo[2]));
						  STN2(&(xo[24]), T1e, T1g, ovs);
						  T1h = VFNMSI(T18, T15);
						  STM2(&(xo[22]), T1h, ovs, &(xo[2]));
						  T1i = VFMAI(T18, T15);
						  STM2(&(xo[10]), T1i, ovs, &(xo[2]));
						  STN2(&(xo[8]), T1d, T1i, ovs);
						  {
						       V T1j, T1k, T1l, T1m;
						       T1j = VFNMSI(T12, T11);
						       STM2(&(xo[30]), T1j, ovs, &(xo[2]));
						       T1k = VFMAI(T12, T11);
						       STM2(&(xo[2]), T1k, ovs, &(xo[2]));
						       STN2(&(xo[0]), T1b, T1k, ovs);
						       T1l = VFMAI(T10, TT);
						       STM2(&(xo[18]), T1l, ovs, &(xo[2]));
						       STN2(&(xo[16]), T1c, T1l, ovs);
						       T1m = VFNMSI(T10, TT);
						       STM2(&(xo[14]), T1m, ovs, &(xo[2]));
						       {
							    V T1n, T1o, T1p, T1q;
							    T1n = VFMAI(Ty, Tx);
							    STM2(&(xo[4]), T1n, ovs, &(xo[0]));
							    STN2(&(xo[4]), T1n, T1f, ovs);
							    T1o = VFNMSI(Ty, Tx);
							    STM2(&(xo[28]), T1o, ovs, &(xo[0]));
							    STN2(&(xo[28]), T1o, T1j, ovs);
							    T1p = VFMAI(Tw, Tn);
							    STM2(&(xo[20]), T1p, ovs, &(xo[0]));
							    STN2(&(xo[20]), T1p, T1h, ovs);
							    T1q = VFNMSI(Tw, Tn);
							    STM2(&(xo[12]), T1q, ovs, &(xo[0]));
							    STN2(&(xo[12]), T1q, T1m, ovs);
						       }
						  }
					     }
					}
				   }
			      }
			 }
		    }
	       }
	  }
     }
}

static const kdft_desc desc = { 16, "n2bv_16", {38, 0, 34, 0}, &GENUS, 0, 2, 0, 0 };
void X(codelet_n2bv_16) (planner *p) {
     X(kdft_register) (p, n2bv_16, &desc);
}

#else				/* HAVE_FMA */

/* Generated by: ../../../genfft/gen_notw_c -simd -compact -variables 4 -pipeline-latency 8 -sign 1 -n 16 -name n2bv_16 -with-ostride 2 -include n2b.h -store-multiple 2 */

/*
 * This function contains 72 FP additions, 12 FP multiplications,
 * (or, 68 additions, 8 multiplications, 4 fused multiply/add),
 * 38 stack variables, 3 constants, and 40 memory accesses
 */
#include "n2b.h"

static void n2bv_16(const R *ri, const R *ii, R *ro, R *io, stride is, stride os, INT v, INT ivs, INT ovs)
{
     DVK(KP382683432, +0.382683432365089771728459984030398866761344562);
     DVK(KP923879532, +0.923879532511286756128183189396788286822416626);
     DVK(KP707106781, +0.707106781186547524400844362104849039284835938);
     INT i;
     const R *xi;
     R *xo;
     xi = ii;
     xo = io;
     for (i = v; i > 0; i = i - VL, xi = xi + (VL * ivs), xo = xo + (VL * ovs), MAKE_VOLATILE_STRIDE(is), MAKE_VOLATILE_STRIDE(os)) {
	  V Tp, T13, Tu, TY, Tm, T14, Tv, TU, T7, T16, Tx, TN, Te, T17, Ty;
	  V TQ;
	  {
	       V Tn, To, TX, Ts, Tt, TW;
	       Tn = LD(&(xi[WS(is, 4)]), ivs, &(xi[0]));
	       To = LD(&(xi[WS(is, 12)]), ivs, &(xi[0]));
	       TX = VADD(Tn, To);
	       Ts = LD(&(xi[0]), ivs, &(xi[0]));
	       Tt = LD(&(xi[WS(is, 8)]), ivs, &(xi[0]));
	       TW = VADD(Ts, Tt);
	       Tp = VSUB(Tn, To);
	       T13 = VADD(TW, TX);
	       Tu = VSUB(Ts, Tt);
	       TY = VSUB(TW, TX);
	  }
	  {
	       V Ti, TS, Tl, TT;
	       {
		    V Tg, Th, Tj, Tk;
		    Tg = LD(&(xi[WS(is, 2)]), ivs, &(xi[0]));
		    Th = LD(&(xi[WS(is, 10)]), ivs, &(xi[0]));
		    Ti = VSUB(Tg, Th);
		    TS = VADD(Tg, Th);
		    Tj = LD(&(xi[WS(is, 14)]), ivs, &(xi[0]));
		    Tk = LD(&(xi[WS(is, 6)]), ivs, &(xi[0]));
		    Tl = VSUB(Tj, Tk);
		    TT = VADD(Tj, Tk);
	       }
	       Tm = VMUL(LDK(KP707106781), VSUB(Ti, Tl));
	       T14 = VADD(TS, TT);
	       Tv = VMUL(LDK(KP707106781), VADD(Ti, Tl));
	       TU = VSUB(TS, TT);
	  }
	  {
	       V T3, TL, T6, TM;
	       {
		    V T1, T2, T4, T5;
		    T1 = LD(&(xi[WS(is, 1)]), ivs, &(xi[WS(is, 1)]));
		    T2 = LD(&(xi[WS(is, 9)]), ivs, &(xi[WS(is, 1)]));
		    T3 = VSUB(T1, T2);
		    TL = VADD(T1, T2);
		    T4 = LD(&(xi[WS(is, 5)]), ivs, &(xi[WS(is, 1)]));
		    T5 = LD(&(xi[WS(is, 13)]), ivs, &(xi[WS(is, 1)]));
		    T6 = VSUB(T4, T5);
		    TM = VADD(T4, T5);
	       }
	       T7 = VFNMS(LDK(KP382683432), T6, VMUL(LDK(KP923879532), T3));
	       T16 = VADD(TL, TM);
	       Tx = VFMA(LDK(KP382683432), T3, VMUL(LDK(KP923879532), T6));
	       TN = VSUB(TL, TM);
	  }
	  {
	       V Ta, TO, Td, TP;
	       {
		    V T8, T9, Tb, Tc;
		    T8 = LD(&(xi[WS(is, 15)]), ivs, &(xi[WS(is, 1)]));
		    T9 = LD(&(xi[WS(is, 7)]), ivs, &(xi[WS(is, 1)]));
		    Ta = VSUB(T8, T9);
		    TO = VADD(T8, T9);
		    Tb = LD(&(xi[WS(is, 3)]), ivs, &(xi[WS(is, 1)]));
		    Tc = LD(&(xi[WS(is, 11)]), ivs, &(xi[WS(is, 1)]));
		    Td = VSUB(Tb, Tc);
		    TP = VADD(Tb, Tc);
	       }
	       Te = VFMA(LDK(KP923879532), Ta, VMUL(LDK(KP382683432), Td));
	       T17 = VADD(TO, TP);
	       Ty = VFNMS(LDK(KP382683432), Ta, VMUL(LDK(KP923879532), Td));
	       TQ = VSUB(TO, TP);
	  }
	  {
	       V T1b, T1c, T1d, T1e;
	       {
		    V T15, T18, T19, T1a;
		    T15 = VSUB(T13, T14);
		    T18 = VBYI(VSUB(T16, T17));
		    T1b = VSUB(T15, T18);
		    STM2(&(xo[24]), T1b, ovs, &(xo[0]));
		    T1c = VADD(T15, T18);
		    STM2(&(xo[8]), T1c, ovs, &(xo[0]));
		    T19 = VADD(T13, T14);
		    T1a = VADD(T16, T17);
		    T1d = VSUB(T19, T1a);
		    STM2(&(xo[16]), T1d, ovs, &(xo[0]));
		    T1e = VADD(T19, T1a);
		    STM2(&(xo[0]), T1e, ovs, &(xo[0]));
	       }
	       {
		    V T1f, T1g, T1h, T1i;
		    {
			 V TV, T11, T10, T12, TR, TZ;
			 TR = VMUL(LDK(KP707106781), VSUB(TN, TQ));
			 TV = VBYI(VSUB(TR, TU));
			 T11 = VBYI(VADD(TU, TR));
			 TZ = VMUL(LDK(KP707106781), VADD(TN, TQ));
			 T10 = VSUB(TY, TZ);
			 T12 = VADD(TY, TZ);
			 T1f = VADD(TV, T10);
			 STM2(&(xo[12]), T1f, ovs, &(xo[0]));
			 T1g = VSUB(T12, T11);
			 STM2(&(xo[28]), T1g, ovs, &(xo[0]));
			 T1h = VSUB(T10, TV);
			 STM2(&(xo[20]), T1h, ovs, &(xo[0]));
			 T1i = VADD(T11, T12);
			 STM2(&(xo[4]), T1i, ovs, &(xo[0]));
		    }
		    {
			 V Tr, TB, TA, TC;
			 {
			      V Tf, Tq, Tw, Tz;
			      Tf = VSUB(T7, Te);
			      Tq = VSUB(Tm, Tp);
			      Tr = VBYI(VSUB(Tf, Tq));
			      TB = VBYI(VADD(Tq, Tf));
			      Tw = VSUB(Tu, Tv);
			      Tz = VSUB(Tx, Ty);
			      TA = VSUB(Tw, Tz);
			      TC = VADD(Tw, Tz);
			 }
			 {
			      V T1j, T1k, T1l, T1m;
			      T1j = VADD(Tr, TA);
			      STM2(&(xo[10]), T1j, ovs, &(xo[2]));
			      STN2(&(xo[8]), T1c, T1j, ovs);
			      T1k = VSUB(TC, TB);
			      STM2(&(xo[26]), T1k, ovs, &(xo[2]));
			      STN2(&(xo[24]), T1b, T1k, ovs);
			      T1l = VSUB(TA, Tr);
			      STM2(&(xo[22]), T1l, ovs, &(xo[2]));
			      STN2(&(xo[20]), T1h, T1l, ovs);
			      T1m = VADD(TB, TC);
			      STM2(&(xo[6]), T1m, ovs, &(xo[2]));
			      STN2(&(xo[4]), T1i, T1m, ovs);
			 }
		    }
		    {
			 V TF, TJ, TI, TK;
			 {
			      V TD, TE, TG, TH;
			      TD = VADD(Tu, Tv);
			      TE = VADD(T7, Te);
			      TF = VADD(TD, TE);
			      TJ = VSUB(TD, TE);
			      TG = VADD(Tp, Tm);
			      TH = VADD(Tx, Ty);
			      TI = VBYI(VADD(TG, TH));
			      TK = VBYI(VSUB(TH, TG));
			 }
			 {
			      V T1n, T1o, T1p, T1q;
			      T1n = VSUB(TF, TI);
			      STM2(&(xo[30]), T1n, ovs, &(xo[2]));
			      STN2(&(xo[28]), T1g, T1n, ovs);
			      T1o = VADD(TJ, TK);
			      STM2(&(xo[14]), T1o, ovs, &(xo[2]));
			      STN2(&(xo[12]), T1f, T1o, ovs);
			      T1p = VADD(TF, TI);
			      STM2(&(xo[2]), T1p, ovs, &(xo[2]));
			      STN2(&(xo[0]), T1e, T1p, ovs);
			      T1q = VSUB(TJ, TK);
			      STM2(&(xo[18]), T1q, ovs, &(xo[2]));
			      STN2(&(xo[16]), T1d, T1q, ovs);
			 }
		    }
	       }
	  }
     }
}

static const kdft_desc desc = { 16, "n2bv_16", {68, 8, 4, 0}, &GENUS, 0, 2, 0, 0 };
void X(codelet_n2bv_16) (planner *p) {
     X(kdft_register) (p, n2bv_16, &desc);
}

#endif				/* HAVE_FMA */
