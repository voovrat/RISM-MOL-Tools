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
/* Generated on Sat Nov 15 21:06:04 EST 2008 */

#include "codelet-rdft.h"

#ifdef HAVE_FMA

/* Generated by: ../../../genfft/gen_r2cb -fma -reorder-insns -schedule-for-pipeline -compact -variables 4 -pipeline-latency 4 -sign 1 -n 25 -name r2cb_25 -include r2cb.h */

/*
 * This function contains 152 FP additions, 120 FP multiplications,
 * (or, 32 additions, 0 multiplications, 120 fused multiply/add),
 * 115 stack variables, 44 constants, and 50 memory accesses
 */
#include "r2cb.h"

static void r2cb_25(R *R0, R *R1, R *Cr, R *Ci, stride rs, stride csr, stride csi, INT v, INT ivs, INT ovs)
{
     DK(KP979740652, +0.979740652857618686258237536568998933733477632);
     DK(KP438153340, +0.438153340021931793654057951961031291699532119);
     DK(KP1_752613360, +1.752613360087727174616231807844125166798128477);
     DK(KP963507348, +0.963507348203430549974383005744259307057084020);
     DK(KP1_606007150, +1.606007150877320829666881187140752009270929701);
     DK(KP1_721083328, +1.721083328735889354196523361841037632825608373);
     DK(KP1_011627398, +1.011627398597394192215998921771049272931807941);
     DK(KP595480289, +0.595480289600000014706716770488118292997907308);
     DK(KP641441904, +0.641441904830606407298806329068862424939687989);
     DK(KP452413526, +0.452413526233009763856834323966348796985206956);
     DK(KP1_809654104, +1.809654104932039055427337295865395187940827822);
     DK(KP933137358, +0.933137358350283770603023973254446451924190884);
     DK(KP1_666834356, +1.666834356657377354817925100486477686277992119);
     DK(KP1_842354653, +1.842354653930286640500894870830132058718564461);
     DK(KP1_082908895, +1.082908895072625554092571180165639018104066379);
     DK(KP662318342, +0.662318342759882818626911127577439236802190210);
     DK(KP576710603, +0.576710603632765877371579268136471017090111488);
     DK(KP484291580, +0.484291580564315559745084187732367906918006201);
     DK(KP1_937166322, +1.937166322257262238980336750929471627672024806);
     DK(KP1_898359647, +1.898359647016882523151110931686726543423167685);
     DK(KP1_386580726, +1.386580726567734802700860150804827247498955921);
     DK(KP904730450, +0.904730450839922351881287709692877908104763647);
     DK(KP1_115827804, +1.115827804063668528375399296931134075984874304);
     DK(KP634619297, +0.634619297544148100711287640319130485732531031);
     DK(KP470564281, +0.470564281212251493087595091036643380879947982);
     DK(KP499013364, +0.499013364214135780976168403431725276668452610);
     DK(KP1_996053456, +1.996053456856543123904673613726901106673810439);
     DK(KP559154169, +0.559154169276087864842202529084232643714075927);
     DK(KP683113946, +0.683113946453479238701949862233725244439656928);
     DK(KP730409924, +0.730409924561256563751459444999838399157094302);
     DK(KP549754652, +0.549754652192770074288023275540779861653779767);
     DK(KP256756360, +0.256756360367726783319498520922669048172391148);
     DK(KP451418159, +0.451418159099103183892477933432151804893354132);
     DK(KP846146756, +0.846146756728608505452954290121135880883743802);
     DK(KP1_902113032, +1.902113032590307144232878666758764286811397268);
     DK(KP062914667, +0.062914667253649757225485955897349402364686947);
     DK(KP939062505, +0.939062505817492352556001843133229685779824606);
     DK(KP951056516, +0.951056516295153572116439333379382143405698634);
     DK(KP559016994, +0.559016994374947424102293417182819058860154590);
     DK(KP250000000, +0.250000000000000000000000000000000000000000000);
     DK(KP1_118033988, +1.118033988749894848204586834365638117720309180);
     DK(KP2_000000000, +2.000000000000000000000000000000000000000000000);
     DK(KP500000000, +0.500000000000000000000000000000000000000000000);
     DK(KP618033988, +0.618033988749894848204586834365638117720309180);
     INT i;
     for (i = v; i > 0; i = i - 1, R0 = R0 + ovs, R1 = R1 + ovs, Cr = Cr + ivs, Ci = Ci + ivs, MAKE_VOLATILE_STRIDE(rs), MAKE_VOLATILE_STRIDE(csr), MAKE_VOLATILE_STRIDE(csi)) {
	  E T1H, T24, T22, T1W, T1Y, T1X, T1Z, T23;
	  {
	       E T1G, Tu, T5, T1F, Tr, Te, T2o, T1N, T2a, T1t, TR, T1K, T29, T1u, TG;
	       E TU, TT, Tn, T1d, T1Q, T2p, T1T, T12, T1P, T1a;
	       {
		    E T1, T2, T3, Ts, Tt;
		    Ts = Ci[WS(csi, 5)];
		    Tt = Ci[WS(csi, 10)];
		    T1 = Cr[0];
		    T2 = Cr[WS(csr, 5)];
		    T3 = Cr[WS(csr, 10)];
		    T1G = FMS(KP618033988, Ts, Tt);
		    Tu = FMA(KP618033988, Tt, Ts);
		    {
			 E Tx, Tw, T1M, TQ, TM, T1J, TF, TL;
			 {
			      E T6, TH, TO, TP, TB, TI, Td, TJ, TE, T4, Tq, TK;
			      T6 = Cr[WS(csr, 1)];
			      T4 = T2 + T3;
			      Tq = T2 - T3;
			      TH = Ci[WS(csi, 1)];
			      {
				   E Ta, T9, Tb, T7, T8, Tp;
				   T7 = Cr[WS(csr, 6)];
				   T8 = Cr[WS(csr, 4)];
				   Tp = FNMS(KP500000000, T4, T1);
				   T5 = FMA(KP2_000000000, T4, T1);
				   Ta = Cr[WS(csr, 11)];
				   TO = T7 - T8;
				   T9 = T7 + T8;
				   T1F = FNMS(KP1_118033988, Tq, Tp);
				   Tr = FMA(KP1_118033988, Tq, Tp);
				   Tb = Cr[WS(csr, 9)];
				   {
					E TC, TD, Tz, TA, Tc;
					Tz = Ci[WS(csi, 6)];
					TA = Ci[WS(csi, 4)];
					TP = Tb - Ta;
					Tc = Ta + Tb;
					TC = Ci[WS(csi, 11)];
					TB = Tz + TA;
					TI = Tz - TA;
					TD = Ci[WS(csi, 9)];
					Td = T9 + Tc;
					Tx = T9 - Tc;
					TJ = TC - TD;
					TE = TC + TD;
				   }
			      }
			      Te = T6 + Td;
			      Tw = FNMS(KP250000000, Td, T6);
			      T1M = FMA(KP618033988, TO, TP);
			      TQ = FNMS(KP618033988, TP, TO);
			      TK = TI + TJ;
			      TM = TI - TJ;
			      T1J = FNMS(KP618033988, TB, TE);
			      TF = FMA(KP618033988, TE, TB);
			      TL = FNMS(KP250000000, TK, TH);
			      T2o = TK + TH;
			 }
			 {
			      E Tf, T14, T1b, T1c, Tm, TY, T15, T16, T11, T17, T19, T18;
			      Tf = Cr[WS(csr, 2)];
			      {
				   E T1L, TN, T1I, Ty;
				   T1L = FNMS(KP559016994, TM, TL);
				   TN = FMA(KP559016994, TM, TL);
				   T1I = FNMS(KP559016994, Tx, Tw);
				   Ty = FMA(KP559016994, Tx, Tw);
				   T1N = FMA(KP951056516, T1M, T1L);
				   T2a = FNMS(KP951056516, T1M, T1L);
				   T1t = FNMS(KP951056516, TQ, TN);
				   TR = FMA(KP951056516, TQ, TN);
				   T1K = FMA(KP951056516, T1J, T1I);
				   T29 = FNMS(KP951056516, T1J, T1I);
				   T1u = FMA(KP951056516, TF, Ty);
				   TG = FNMS(KP951056516, TF, Ty);
				   T14 = Ci[WS(csi, 2)];
			      }
			      {
				   E Tg, Th, Tj, Tk;
				   Tg = Cr[WS(csr, 7)];
				   Th = Cr[WS(csr, 3)];
				   Tj = Cr[WS(csr, 12)];
				   Tk = Cr[WS(csr, 8)];
				   {
					E TW, Ti, Tl, TX, TZ, T10;
					TW = Ci[WS(csi, 7)];
					T1b = Th - Tg;
					Ti = Tg + Th;
					T1c = Tj - Tk;
					Tl = Tj + Tk;
					TX = Ci[WS(csi, 3)];
					TZ = Ci[WS(csi, 12)];
					T10 = Ci[WS(csi, 8)];
					Tm = Ti + Tl;
					TU = Tl - Ti;
					TY = TW + TX;
					T15 = TW - TX;
					T16 = TZ - T10;
					T11 = TZ + T10;
				   }
			      }
			      TT = FNMS(KP250000000, Tm, Tf);
			      Tn = Tf + Tm;
			      T17 = T15 + T16;
			      T19 = T16 - T15;
			      T1d = FNMS(KP618033988, T1c, T1b);
			      T1Q = FMA(KP618033988, T1b, T1c);
			      T18 = FNMS(KP250000000, T17, T14);
			      T2p = T17 + T14;
			      T1T = FNMS(KP618033988, TY, T11);
			      T12 = FMA(KP618033988, T11, TY);
			      T1P = FMA(KP559016994, T19, T18);
			      T1a = FNMS(KP559016994, T19, T18);
			 }
		    }
	       }
	       {
		    E T1R, T1e, T1q, T1U, T13, T1r, T2b, T28, T25, T2i, T2k;
		    {
			 E T2m, To, T26, T27, TV, T1S;
			 T2m = Te - Tn;
			 To = Te + Tn;
			 TV = FNMS(KP559016994, TU, TT);
			 T1S = FMA(KP559016994, TU, TT);
			 T26 = FMA(KP951056516, T1Q, T1P);
			 T1R = FNMS(KP951056516, T1Q, T1P);
			 T1e = FNMS(KP951056516, T1d, T1a);
			 T1q = FMA(KP951056516, T1d, T1a);
			 T27 = FNMS(KP951056516, T1T, T1S);
			 T1U = FMA(KP951056516, T1T, T1S);
			 T13 = FNMS(KP951056516, T12, TV);
			 T1r = FMA(KP951056516, T12, TV);
			 {
			      E T2g, T2q, T2s, T2h, T2n, T2r, T2l;
			      T2g = FMA(KP939062505, T29, T2a);
			      T2b = FNMS(KP939062505, T2a, T29);
			      R0[0] = FMA(KP2_000000000, To, T5);
			      T2l = FNMS(KP500000000, To, T5);
			      T2q = FMA(KP618033988, T2p, T2o);
			      T2s = FNMS(KP618033988, T2o, T2p);
			      T28 = FNMS(KP062914667, T27, T26);
			      T2h = FMA(KP062914667, T26, T27);
			      T2n = FMA(KP1_118033988, T2m, T2l);
			      T2r = FNMS(KP1_118033988, T2m, T2l);
			      T25 = FMA(KP1_902113032, T1G, T1F);
			      T1H = FNMS(KP1_902113032, T1G, T1F);
			      T2i = FMA(KP846146756, T2h, T2g);
			      T2k = FNMS(KP451418159, T2g, T2h);
			      R0[WS(rs, 10)] = FMA(KP1_902113032, T2q, T2n);
			      R1[WS(rs, 2)] = FNMS(KP1_902113032, T2q, T2n);
			      R0[WS(rs, 5)] = FMA(KP1_902113032, T2s, T2r);
			      R1[WS(rs, 7)] = FNMS(KP1_902113032, T2s, T2r);
			 }
		    }
		    {
			 E TS, T1f, T1p, Tv, T2e, T1o, T1m, T2d, T1k, T1l, T2c;
			 TS = FNMS(KP256756360, TR, TG);
			 T1k = FMA(KP256756360, TG, TR);
			 T1l = FMA(KP549754652, T13, T1e);
			 T1f = FNMS(KP549754652, T1e, T13);
			 T1p = FMA(KP1_902113032, Tu, Tr);
			 Tv = FNMS(KP1_902113032, Tu, Tr);
			 T2e = FMA(KP730409924, T2b, T28);
			 T2c = FNMS(KP730409924, T2b, T28);
			 T1o = FNMS(KP683113946, T1k, T1l);
			 T1m = FMA(KP559154169, T1l, T1k);
			 R1[WS(rs, 1)] = FNMS(KP1_996053456, T2c, T25);
			 T2d = FMA(KP499013364, T2c, T25);
			 {
			      E T1C, T1E, T1y, T1w;
			      {
				   E T1s, T1v, T1i, T1h, T1n, T1j;
				   {
					E T1A, T1B, T2f, T2j, T1g;
					T1A = FNMS(KP470564281, T1q, T1r);
					T1s = FMA(KP470564281, T1r, T1q);
					T1v = FNMS(KP634619297, T1u, T1t);
					T1B = FMA(KP634619297, T1t, T1u);
					T2f = FMA(KP1_115827804, T2e, T2d);
					T2j = FNMS(KP1_115827804, T2e, T2d);
					T1i = FNMS(KP904730450, T1f, TS);
					T1g = FMA(KP904730450, T1f, TS);
					R1[WS(rs, 11)] = FMA(KP1_386580726, T2i, T2f);
					R0[WS(rs, 4)] = FNMS(KP1_386580726, T2i, T2f);
					R1[WS(rs, 6)] = FMA(KP1_898359647, T2k, T2j);
					R0[WS(rs, 9)] = FNMS(KP1_898359647, T2k, T2j);
					R1[0] = FMA(KP1_937166322, T1g, Tv);
					T1h = FNMS(KP484291580, T1g, Tv);
					T1C = FNMS(KP576710603, T1B, T1A);
					T1E = FMA(KP662318342, T1A, T1B);
				   }
				   T1n = FNMS(KP1_082908895, T1i, T1h);
				   T1j = FMA(KP1_082908895, T1i, T1h);
				   R1[WS(rs, 10)] = FMA(KP1_842354653, T1m, T1j);
				   R0[WS(rs, 3)] = FNMS(KP1_842354653, T1m, T1j);
				   R1[WS(rs, 5)] = FMA(KP1_666834356, T1o, T1n);
				   R0[WS(rs, 8)] = FNMS(KP1_666834356, T1o, T1n);
				   T1y = FNMS(KP933137358, T1v, T1s);
				   T1w = FMA(KP933137358, T1v, T1s);
			      }
			      {
				   E T1O, T20, T21, T1V, T1x, T1z, T1D;
				   T1O = FNMS(KP549754652, T1N, T1K);
				   T20 = FMA(KP549754652, T1K, T1N);
				   T21 = FMA(KP634619297, T1R, T1U);
				   T1V = FNMS(KP634619297, T1U, T1R);
				   R0[WS(rs, 2)] = FNMS(KP1_809654104, T1w, T1p);
				   T1x = FMA(KP452413526, T1w, T1p);
				   T24 = FNMS(KP641441904, T20, T21);
				   T22 = FMA(KP595480289, T21, T20);
				   T1z = FNMS(KP1_011627398, T1y, T1x);
				   T1D = FMA(KP1_011627398, T1y, T1x);
				   R1[WS(rs, 9)] = FNMS(KP1_721083328, T1C, T1z);
				   R0[WS(rs, 7)] = FMA(KP1_721083328, T1C, T1z);
				   R0[WS(rs, 12)] = FMA(KP1_606007150, T1E, T1D);
				   R1[WS(rs, 4)] = FNMS(KP1_606007150, T1E, T1D);
				   T1W = FNMS(KP963507348, T1V, T1O);
				   T1Y = FMA(KP963507348, T1V, T1O);
			      }
			 }
		    }
	       }
	  }
	  R0[WS(rs, 1)] = FMA(KP1_752613360, T1W, T1H);
	  T1X = FNMS(KP438153340, T1W, T1H);
	  T1Z = FMA(KP979740652, T1Y, T1X);
	  T23 = FNMS(KP979740652, T1Y, T1X);
	  R0[WS(rs, 11)] = FMA(KP1_666834356, T22, T1Z);
	  R1[WS(rs, 3)] = FNMS(KP1_666834356, T22, T1Z);
	  R1[WS(rs, 8)] = FNMS(KP1_606007150, T24, T23);
	  R0[WS(rs, 6)] = FMA(KP1_606007150, T24, T23);
     }
}

static const kr2c_desc desc = { 25, "r2cb_25", {32, 0, 120, 0}, &GENUS };

void X(codelet_r2cb_25) (planner *p) {
     X(kr2c_register) (p, r2cb_25, &desc);
}

#else				/* HAVE_FMA */

/* Generated by: ../../../genfft/gen_r2cb -compact -variables 4 -pipeline-latency 4 -sign 1 -n 25 -name r2cb_25 -include r2cb.h */

/*
 * This function contains 152 FP additions, 98 FP multiplications,
 * (or, 100 additions, 46 multiplications, 52 fused multiply/add),
 * 65 stack variables, 21 constants, and 50 memory accesses
 */
#include "r2cb.h"

static void r2cb_25(R *R0, R *R1, R *Cr, R *Ci, stride rs, stride csr, stride csi, INT v, INT ivs, INT ovs)
{
     DK(KP425779291, +0.425779291565072648862502445744251703979973042);
     DK(KP904827052, +0.904827052466019527713668647932697593970413911);
     DK(KP535826794, +0.535826794978996618271308767867639978063575346);
     DK(KP844327925, +0.844327925502015078548558063966681505381659241);
     DK(KP876306680, +0.876306680043863587308115903922062583399064238);
     DK(KP481753674, +0.481753674101715274987191502872129653528542010);
     DK(KP968583161, +0.968583161128631119490168375464735813836012403);
     DK(KP248689887, +0.248689887164854788242283746006447968417567406);
     DK(KP062790519, +0.062790519529313376076178224565631133122484832);
     DK(KP998026728, +0.998026728428271561952336806863450553336905220);
     DK(KP728968627, +0.728968627421411523146730319055259111372571664);
     DK(KP684547105, +0.684547105928688673732283357621209269889519233);
     DK(KP250000000, +0.250000000000000000000000000000000000000000000);
     DK(KP587785252, +0.587785252292473129168705954639072768597652438);
     DK(KP951056516, +0.951056516295153572116439333379382143405698634);
     DK(KP559016994, +0.559016994374947424102293417182819058860154590);
     DK(KP500000000, +0.500000000000000000000000000000000000000000000);
     DK(KP2_000000000, +2.000000000000000000000000000000000000000000000);
     DK(KP1_118033988, +1.118033988749894848204586834365638117720309180);
     DK(KP1_175570504, +1.175570504584946258337411909278145537195304875);
     DK(KP1_902113032, +1.902113032590307144232878666758764286811397268);
     INT i;
     for (i = v; i > 0; i = i - 1, R0 = R0 + ovs, R1 = R1 + ovs, Cr = Cr + ivs, Ci = Ci + ivs, MAKE_VOLATILE_STRIDE(rs), MAKE_VOLATILE_STRIDE(csr), MAKE_VOLATILE_STRIDE(csi)) {
	  E Tu, T1G, T5, Tr, T1F, TN, TO, Te, TR, T27, T1r, T1N, TG, T26, T1q;
	  E T1K, T1a, T1b, Tn, T1e, T2a, T1u, T1U, T13, T29, T1t, T1R, Ts, Tt;
	  Ts = Ci[WS(csi, 5)];
	  Tt = Ci[WS(csi, 10)];
	  Tu = FMA(KP1_902113032, Ts, KP1_175570504 * Tt);
	  T1G = FNMS(KP1_902113032, Tt, KP1_175570504 * Ts);
	  {
	       E T1, T4, Tp, T2, T3, Tq;
	       T1 = Cr[0];
	       T2 = Cr[WS(csr, 5)];
	       T3 = Cr[WS(csr, 10)];
	       T4 = T2 + T3;
	       Tp = KP1_118033988 * (T2 - T3);
	       T5 = FMA(KP2_000000000, T4, T1);
	       Tq = FNMS(KP500000000, T4, T1);
	       Tr = Tp + Tq;
	       T1F = Tq - Tp;
	  }
	  {
	       E T6, Td, TI, Tw, TH, TB, TE, TM;
	       T6 = Cr[WS(csr, 1)];
	       TN = Ci[WS(csi, 1)];
	       {
		    E T7, T8, T9, Ta, Tb, Tc;
		    T7 = Cr[WS(csr, 6)];
		    T8 = Cr[WS(csr, 4)];
		    T9 = T7 + T8;
		    Ta = Cr[WS(csr, 11)];
		    Tb = Cr[WS(csr, 9)];
		    Tc = Ta + Tb;
		    Td = T9 + Tc;
		    TI = Ta - Tb;
		    Tw = KP559016994 * (T9 - Tc);
		    TH = T7 - T8;
	       }
	       {
		    E Tz, TA, TK, TC, TD, TL;
		    Tz = Ci[WS(csi, 6)];
		    TA = Ci[WS(csi, 4)];
		    TK = Tz - TA;
		    TC = Ci[WS(csi, 11)];
		    TD = Ci[WS(csi, 9)];
		    TL = TC - TD;
		    TB = Tz + TA;
		    TO = TK + TL;
		    TE = TC + TD;
		    TM = KP559016994 * (TK - TL);
	       }
	       Te = T6 + Td;
	       {
		    E TJ, T1L, TQ, T1M, TP;
		    TJ = FMA(KP951056516, TH, KP587785252 * TI);
		    T1L = FNMS(KP951056516, TI, KP587785252 * TH);
		    TP = FNMS(KP250000000, TO, TN);
		    TQ = TM + TP;
		    T1M = TP - TM;
		    TR = TJ + TQ;
		    T27 = T1M - T1L;
		    T1r = TQ - TJ;
		    T1N = T1L + T1M;
	       }
	       {
		    E TF, T1J, Ty, T1I, Tx;
		    TF = FMA(KP951056516, TB, KP587785252 * TE);
		    T1J = FNMS(KP951056516, TE, KP587785252 * TB);
		    Tx = FNMS(KP250000000, Td, T6);
		    Ty = Tw + Tx;
		    T1I = Tx - Tw;
		    TG = Ty - TF;
		    T26 = T1I + T1J;
		    T1q = Ty + TF;
		    T1K = T1I - T1J;
	       }
	  }
	  {
	       E Tf, Tm, T15, TT, T14, TY, T11, T19;
	       Tf = Cr[WS(csr, 2)];
	       T1a = Ci[WS(csi, 2)];
	       {
		    E Tg, Th, Ti, Tj, Tk, Tl;
		    Tg = Cr[WS(csr, 7)];
		    Th = Cr[WS(csr, 3)];
		    Ti = Tg + Th;
		    Tj = Cr[WS(csr, 12)];
		    Tk = Cr[WS(csr, 8)];
		    Tl = Tj + Tk;
		    Tm = Ti + Tl;
		    T15 = Tj - Tk;
		    TT = KP559016994 * (Ti - Tl);
		    T14 = Tg - Th;
	       }
	       {
		    E TW, TX, T17, TZ, T10, T18;
		    TW = Ci[WS(csi, 7)];
		    TX = Ci[WS(csi, 3)];
		    T17 = TW - TX;
		    TZ = Ci[WS(csi, 12)];
		    T10 = Ci[WS(csi, 8)];
		    T18 = TZ - T10;
		    TY = TW + TX;
		    T1b = T17 + T18;
		    T11 = TZ + T10;
		    T19 = KP559016994 * (T17 - T18);
	       }
	       Tn = Tf + Tm;
	       {
		    E T16, T1S, T1d, T1T, T1c;
		    T16 = FMA(KP951056516, T14, KP587785252 * T15);
		    T1S = FNMS(KP951056516, T15, KP587785252 * T14);
		    T1c = FNMS(KP250000000, T1b, T1a);
		    T1d = T19 + T1c;
		    T1T = T1c - T19;
		    T1e = T16 + T1d;
		    T2a = T1T - T1S;
		    T1u = T1d - T16;
		    T1U = T1S + T1T;
	       }
	       {
		    E T12, T1Q, TV, T1P, TU;
		    T12 = FMA(KP951056516, TY, KP587785252 * T11);
		    T1Q = FNMS(KP951056516, T11, KP587785252 * TY);
		    TU = FNMS(KP250000000, Tm, Tf);
		    TV = TT + TU;
		    T1P = TU - TT;
		    T13 = TV - T12;
		    T29 = T1P + T1Q;
		    T1t = TV + T12;
		    T1R = T1P - T1Q;
	       }
	  }
	  {
	       E T2m, To, T2l, T2q, T2s, T2o, T2p, T2r, T2n;
	       T2m = KP1_118033988 * (Te - Tn);
	       To = Te + Tn;
	       T2l = FNMS(KP500000000, To, T5);
	       T2o = TO + TN;
	       T2p = T1b + T1a;
	       T2q = FNMS(KP1_902113032, T2p, KP1_175570504 * T2o);
	       T2s = FMA(KP1_902113032, T2o, KP1_175570504 * T2p);
	       R0[0] = FMA(KP2_000000000, To, T5);
	       T2r = T2m + T2l;
	       R1[WS(rs, 2)] = T2r - T2s;
	       R0[WS(rs, 10)] = T2r + T2s;
	       T2n = T2l - T2m;
	       R0[WS(rs, 5)] = T2n - T2q;
	       R1[WS(rs, 7)] = T2n + T2q;
	  }
	  {
	       E T2i, T2k, T25, T2c, T2d, T2e, T2j, T2f;
	       {
		    E T2g, T2h, T28, T2b;
		    T2g = FMA(KP684547105, T26, KP728968627 * T27);
		    T2h = FMA(KP998026728, T29, KP062790519 * T2a);
		    T2i = FNMS(KP1_902113032, T2h, KP1_175570504 * T2g);
		    T2k = FMA(KP1_902113032, T2g, KP1_175570504 * T2h);
		    T25 = T1F + T1G;
		    T28 = FNMS(KP684547105, T27, KP728968627 * T26);
		    T2b = FNMS(KP998026728, T2a, KP062790519 * T29);
		    T2c = T28 + T2b;
		    T2d = FNMS(KP500000000, T2c, T25);
		    T2e = KP1_118033988 * (T28 - T2b);
	       }
	       R1[WS(rs, 1)] = FMA(KP2_000000000, T2c, T25);
	       T2j = T2e + T2d;
	       R0[WS(rs, 4)] = T2j - T2k;
	       R1[WS(rs, 11)] = T2j + T2k;
	       T2f = T2d - T2e;
	       R1[WS(rs, 6)] = T2f - T2i;
	       R0[WS(rs, 9)] = T2f + T2i;
	  }
	  {
	       E T1m, T1o, Tv, T1g, T1h, T1i, T1n, T1j;
	       {
		    E T1k, T1l, TS, T1f;
		    T1k = FMA(KP248689887, TG, KP968583161 * TR);
		    T1l = FMA(KP481753674, T13, KP876306680 * T1e);
		    T1m = FNMS(KP1_902113032, T1l, KP1_175570504 * T1k);
		    T1o = FMA(KP1_902113032, T1k, KP1_175570504 * T1l);
		    Tv = Tr - Tu;
		    TS = FNMS(KP248689887, TR, KP968583161 * TG);
		    T1f = FNMS(KP481753674, T1e, KP876306680 * T13);
		    T1g = TS + T1f;
		    T1h = FNMS(KP500000000, T1g, Tv);
		    T1i = KP1_118033988 * (TS - T1f);
	       }
	       R1[0] = FMA(KP2_000000000, T1g, Tv);
	       T1n = T1i + T1h;
	       R0[WS(rs, 3)] = T1n - T1o;
	       R1[WS(rs, 10)] = T1n + T1o;
	       T1j = T1h - T1i;
	       R1[WS(rs, 5)] = T1j - T1m;
	       R0[WS(rs, 8)] = T1j + T1m;
	  }
	  {
	       E T1C, T1E, T1p, T1w, T1x, T1y, T1D, T1z;
	       {
		    E T1A, T1B, T1s, T1v;
		    T1A = FMA(KP844327925, T1q, KP535826794 * T1r);
		    T1B = FNMS(KP425779291, T1u, KP904827052 * T1t);
		    T1C = FNMS(KP1_902113032, T1B, KP1_175570504 * T1A);
		    T1E = FMA(KP1_902113032, T1A, KP1_175570504 * T1B);
		    T1p = Tr + Tu;
		    T1s = FNMS(KP844327925, T1r, KP535826794 * T1q);
		    T1v = FMA(KP425779291, T1t, KP904827052 * T1u);
		    T1w = T1s - T1v;
		    T1x = FNMS(KP500000000, T1w, T1p);
		    T1y = KP1_118033988 * (T1s + T1v);
	       }
	       R0[WS(rs, 2)] = FMA(KP2_000000000, T1w, T1p);
	       T1D = T1x + T1y;
	       R1[WS(rs, 4)] = T1D - T1E;
	       R0[WS(rs, 12)] = T1E + T1D;
	       T1z = T1x - T1y;
	       R0[WS(rs, 7)] = T1z - T1C;
	       R1[WS(rs, 9)] = T1C + T1z;
	  }
	  {
	       E T22, T24, T1H, T1W, T1X, T1Y, T23, T1Z;
	       {
		    E T20, T21, T1O, T1V;
		    T20 = FMA(KP481753674, T1K, KP876306680 * T1N);
		    T21 = FMA(KP844327925, T1R, KP535826794 * T1U);
		    T22 = FNMS(KP1_902113032, T21, KP1_175570504 * T20);
		    T24 = FMA(KP1_902113032, T20, KP1_175570504 * T21);
		    T1H = T1F - T1G;
		    T1O = FNMS(KP481753674, T1N, KP876306680 * T1K);
		    T1V = FNMS(KP844327925, T1U, KP535826794 * T1R);
		    T1W = T1O + T1V;
		    T1X = FNMS(KP500000000, T1W, T1H);
		    T1Y = KP1_118033988 * (T1O - T1V);
	       }
	       R0[WS(rs, 1)] = FMA(KP2_000000000, T1W, T1H);
	       T23 = T1Y + T1X;
	       R1[WS(rs, 3)] = T23 - T24;
	       R0[WS(rs, 11)] = T23 + T24;
	       T1Z = T1X - T1Y;
	       R0[WS(rs, 6)] = T1Z - T22;
	       R1[WS(rs, 8)] = T1Z + T22;
	  }
     }
}

static const kr2c_desc desc = { 25, "r2cb_25", {100, 46, 52, 0}, &GENUS };

void X(codelet_r2cb_25) (planner *p) {
     X(kr2c_register) (p, r2cb_25, &desc);
}

#endif				/* HAVE_FMA */
