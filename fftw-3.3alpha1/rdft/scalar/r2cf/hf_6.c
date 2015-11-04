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
/* Generated on Sat Nov 15 20:56:14 EST 2008 */

#include "codelet-rdft.h"

#ifdef HAVE_FMA

/* Generated by: ../../../genfft/gen_hc2hc -fma -reorder-insns -schedule-for-pipeline -compact -variables 4 -pipeline-latency 4 -n 6 -dit -name hf_6 -include hf.h */

/*
 * This function contains 46 FP additions, 32 FP multiplications,
 * (or, 24 additions, 10 multiplications, 22 fused multiply/add),
 * 47 stack variables, 2 constants, and 24 memory accesses
 */
#include "hf.h"

static void hf_6(R *cr, R *ci, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DK(KP866025403, +0.866025403784438646763723170752936183471402627);
     DK(KP500000000, +0.500000000000000000000000000000000000000000000);
     INT m;
     for (m = mb, W = W + ((mb - 1) * 10); m < me; m = m + 1, cr = cr + ms, ci = ci - ms, W = W + 10, MAKE_VOLATILE_STRIDE(rs)) {
	  E T11, T12, T14, T13;
	  {
	       E T1, TV, TX, T7, Tn, Tq, TO, TR, TB, Tl, To, TH, Tt, Tw, Ts;
	       E Tp, Tv;
	       T1 = cr[0];
	       TV = ci[0];
	       {
		    E T3, T6, T2, T5;
		    T3 = cr[WS(rs, 3)];
		    T6 = ci[WS(rs, 3)];
		    T2 = W[4];
		    T5 = W[5];
		    {
			 E Ta, Td, Tg, TM, Tb, Tj, Tf, Tc, Ti, TW, T4, T9;
			 Ta = cr[WS(rs, 2)];
			 Td = ci[WS(rs, 2)];
			 TW = T2 * T6;
			 T4 = T2 * T3;
			 T9 = W[2];
			 Tg = cr[WS(rs, 5)];
			 TX = FNMS(T5, T3, TW);
			 T7 = FMA(T5, T6, T4);
			 TM = T9 * Td;
			 Tb = T9 * Ta;
			 Tj = ci[WS(rs, 5)];
			 Tf = W[8];
			 Tc = W[3];
			 Ti = W[9];
			 {
			      E TN, Te, TL, Tk, TK, Th, Tm;
			      Tn = cr[WS(rs, 4)];
			      TK = Tf * Tj;
			      Th = Tf * Tg;
			      TN = FNMS(Tc, Ta, TM);
			      Te = FMA(Tc, Td, Tb);
			      TL = FNMS(Ti, Tg, TK);
			      Tk = FMA(Ti, Tj, Th);
			      Tq = ci[WS(rs, 4)];
			      Tm = W[6];
			      TO = TL - TN;
			      TR = TN + TL;
			      TB = Te + Tk;
			      Tl = Te - Tk;
			      To = Tm * Tn;
			      TH = Tm * Tq;
			 }
			 Tt = cr[WS(rs, 1)];
			 Tw = ci[WS(rs, 1)];
			 Ts = W[0];
			 Tp = W[7];
			 Tv = W[1];
		    }
	       }
	       {
		    E TA, T8, TI, Tr, TG, Tx, TF, Tu;
		    TA = T1 + T7;
		    T8 = T1 - T7;
		    TF = Ts * Tw;
		    Tu = Ts * Tt;
		    TI = FNMS(Tp, Tn, TH);
		    Tr = FMA(Tp, Tq, To);
		    TG = FNMS(Tv, Tt, TF);
		    Tx = FMA(Tv, Tw, Tu);
		    {
			 E TY, TU, TP, TT, TD, T10, Tz, TZ, TQ, TE;
			 T11 = TX + TV;
			 TY = TV - TX;
			 {
			      E TJ, TS, TC, Ty;
			      TJ = TG - TI;
			      TS = TI + TG;
			      TC = Tr + Tx;
			      Ty = Tr - Tx;
			      TU = TO + TJ;
			      TP = TJ - TO;
			      TT = TR - TS;
			      T12 = TR + TS;
			      T14 = TB - TC;
			      TD = TB + TC;
			      T10 = Ty - Tl;
			      Tz = Tl + Ty;
			      TZ = FMA(KP500000000, TU, TY);
			 }
			 cr[0] = TA + TD;
			 TQ = FNMS(KP500000000, TD, TA);
			 ci[WS(rs, 2)] = T8 + Tz;
			 TE = FNMS(KP500000000, Tz, T8);
			 cr[WS(rs, 3)] = TU - TY;
			 cr[WS(rs, 2)] = FNMS(KP866025403, TT, TQ);
			 ci[WS(rs, 1)] = FMA(KP866025403, TT, TQ);
			 ci[0] = FNMS(KP866025403, TP, TE);
			 cr[WS(rs, 1)] = FMA(KP866025403, TP, TE);
			 ci[WS(rs, 4)] = FMA(KP866025403, T10, TZ);
			 cr[WS(rs, 5)] = FMS(KP866025403, T10, TZ);
		    }
	       }
	  }
	  ci[WS(rs, 5)] = T12 + T11;
	  T13 = FNMS(KP500000000, T12, T11);
	  ci[WS(rs, 3)] = FMA(KP866025403, T14, T13);
	  cr[WS(rs, 4)] = FMS(KP866025403, T14, T13);
     }
}

static const tw_instr twinstr[] = {
     {TW_FULL, 1, 6},
     {TW_NEXT, 1, 0}
};

static const hc2hc_desc desc = { 6, "hf_6", twinstr, &GENUS, {24, 10, 22, 0} };

void X(codelet_hf_6) (planner *p) {
     X(khc2hc_register) (p, hf_6, &desc);
}
#else				/* HAVE_FMA */

/* Generated by: ../../../genfft/gen_hc2hc -compact -variables 4 -pipeline-latency 4 -n 6 -dit -name hf_6 -include hf.h */

/*
 * This function contains 46 FP additions, 28 FP multiplications,
 * (or, 32 additions, 14 multiplications, 14 fused multiply/add),
 * 23 stack variables, 2 constants, and 24 memory accesses
 */
#include "hf.h"

static void hf_6(R *cr, R *ci, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DK(KP500000000, +0.500000000000000000000000000000000000000000000);
     DK(KP866025403, +0.866025403784438646763723170752936183471402627);
     INT m;
     for (m = mb, W = W + ((mb - 1) * 10); m < me; m = m + 1, cr = cr + ms, ci = ci - ms, W = W + 10, MAKE_VOLATILE_STRIDE(rs)) {
	  E T7, TS, Tv, TO, Tt, TJ, Tx, TF, Ti, TI, Tw, TC;
	  {
	       E T1, TM, T6, TN;
	       T1 = cr[0];
	       TM = ci[0];
	       {
		    E T3, T5, T2, T4;
		    T3 = cr[WS(rs, 3)];
		    T5 = ci[WS(rs, 3)];
		    T2 = W[4];
		    T4 = W[5];
		    T6 = FMA(T2, T3, T4 * T5);
		    TN = FNMS(T4, T3, T2 * T5);
	       }
	       T7 = T1 - T6;
	       TS = TN + TM;
	       Tv = T1 + T6;
	       TO = TM - TN;
	  }
	  {
	       E Tn, TE, Ts, TD;
	       {
		    E Tk, Tm, Tj, Tl;
		    Tk = cr[WS(rs, 4)];
		    Tm = ci[WS(rs, 4)];
		    Tj = W[6];
		    Tl = W[7];
		    Tn = FMA(Tj, Tk, Tl * Tm);
		    TE = FNMS(Tl, Tk, Tj * Tm);
	       }
	       {
		    E Tp, Tr, To, Tq;
		    Tp = cr[WS(rs, 1)];
		    Tr = ci[WS(rs, 1)];
		    To = W[0];
		    Tq = W[1];
		    Ts = FMA(To, Tp, Tq * Tr);
		    TD = FNMS(Tq, Tp, To * Tr);
	       }
	       Tt = Tn - Ts;
	       TJ = TE + TD;
	       Tx = Tn + Ts;
	       TF = TD - TE;
	  }
	  {
	       E Tc, TA, Th, TB;
	       {
		    E T9, Tb, T8, Ta;
		    T9 = cr[WS(rs, 2)];
		    Tb = ci[WS(rs, 2)];
		    T8 = W[2];
		    Ta = W[3];
		    Tc = FMA(T8, T9, Ta * Tb);
		    TA = FNMS(Ta, T9, T8 * Tb);
	       }
	       {
		    E Te, Tg, Td, Tf;
		    Te = cr[WS(rs, 5)];
		    Tg = ci[WS(rs, 5)];
		    Td = W[8];
		    Tf = W[9];
		    Th = FMA(Td, Te, Tf * Tg);
		    TB = FNMS(Tf, Te, Td * Tg);
	       }
	       Ti = Tc - Th;
	       TI = TA + TB;
	       Tw = Tc + Th;
	       TC = TA - TB;
	  }
	  {
	       E TG, Tu, Tz, TK, Ty, TH;
	       TG = KP866025403 * (TC + TF);
	       Tu = Ti + Tt;
	       Tz = FNMS(KP500000000, Tu, T7);
	       ci[WS(rs, 2)] = T7 + Tu;
	       cr[WS(rs, 1)] = Tz + TG;
	       ci[0] = Tz - TG;
	       TK = KP866025403 * (TI - TJ);
	       Ty = Tw + Tx;
	       TH = FNMS(KP500000000, Ty, Tv);
	       cr[0] = Tv + Ty;
	       ci[WS(rs, 1)] = TH + TK;
	       cr[WS(rs, 2)] = TH - TK;
	  }
	  {
	       E TP, TL, TQ, TR, TT, TU;
	       TP = KP866025403 * (Tt - Ti);
	       TL = TF - TC;
	       TQ = FMA(KP500000000, TL, TO);
	       cr[WS(rs, 3)] = TL - TO;
	       ci[WS(rs, 4)] = TP + TQ;
	       cr[WS(rs, 5)] = TP - TQ;
	       TR = KP866025403 * (Tw - Tx);
	       TT = TI + TJ;
	       TU = FNMS(KP500000000, TT, TS);
	       cr[WS(rs, 4)] = TR - TU;
	       ci[WS(rs, 5)] = TT + TS;
	       ci[WS(rs, 3)] = TR + TU;
	  }
     }
}

static const tw_instr twinstr[] = {
     {TW_FULL, 1, 6},
     {TW_NEXT, 1, 0}
};

static const hc2hc_desc desc = { 6, "hf_6", twinstr, &GENUS, {32, 14, 14, 0} };

void X(codelet_hf_6) (planner *p) {
     X(khc2hc_register) (p, hf_6, &desc);
}
#endif				/* HAVE_FMA */
