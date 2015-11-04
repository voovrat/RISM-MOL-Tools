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
/* Generated on Sat Nov 15 20:43:57 EST 2008 */

#include "codelet-dft.h"

#ifdef HAVE_FMA

/* Generated by: ../../../genfft/gen_notw_c -fma -reorder-insns -schedule-for-pipeline -simd -compact -variables 4 -pipeline-latency 8 -n 25 -name n1fv_25 -include n1f.h */

/*
 * This function contains 224 FP additions, 193 FP multiplications,
 * (or, 43 additions, 12 multiplications, 181 fused multiply/add),
 * 215 stack variables, 67 constants, and 50 memory accesses
 */
#include "n1f.h"

static void n1fv_25(const R *ri, const R *ii, R *ro, R *io, stride is, stride os, INT v, INT ivs, INT ovs)
{
     DVK(KP792626838, +0.792626838241819413632131824093538848057784557);
     DVK(KP876091699, +0.876091699473550838204498029706869638173524346);
     DVK(KP803003575, +0.803003575438660414833440593570376004635464850);
     DVK(KP617882369, +0.617882369114440893914546919006756321695042882);
     DVK(KP242145790, +0.242145790282157779872542093866183953459003101);
     DVK(KP968583161, +0.968583161128631119490168375464735813836012403);
     DVK(KP999544308, +0.999544308746292983948881682379742149196758193);
     DVK(KP683113946, +0.683113946453479238701949862233725244439656928);
     DVK(KP559154169, +0.559154169276087864842202529084232643714075927);
     DVK(KP904730450, +0.904730450839922351881287709692877908104763647);
     DVK(KP829049696, +0.829049696159252993975487806364305442437946767);
     DVK(KP831864738, +0.831864738706457140726048799369896829771167132);
     DVK(KP916574801, +0.916574801383451584742370439148878693530976769);
     DVK(KP894834959, +0.894834959464455102997960030820114611498661386);
     DVK(KP809385824, +0.809385824416008241660603814668679683846476688);
     DVK(KP447417479, +0.447417479732227551498980015410057305749330693);
     DVK(KP860541664, +0.860541664367944677098261680920518816412804187);
     DVK(KP897376177, +0.897376177523557693138608077137219684419427330);
     DVK(KP876306680, +0.876306680043863587308115903922062583399064238);
     DVK(KP681693190, +0.681693190061530575150324149145440022633095390);
     DVK(KP560319534, +0.560319534973832390111614715371676131169633784);
     DVK(KP855719849, +0.855719849902058969314654733608091555096772472);
     DVK(KP237294955, +0.237294955877110315393888866460840817927895961);
     DVK(KP949179823, +0.949179823508441261575555465843363271711583843);
     DVK(KP904508497, +0.904508497187473712051146708591409529430077295);
     DVK(KP997675361, +0.997675361079556513670859573984492383596555031);
     DVK(KP262346850, +0.262346850930607871785420028382979691334784273);
     DVK(KP763932022, +0.763932022500210303590826331268723764559381640);
     DVK(KP992114701, +0.992114701314477831049793042785778521453036709);
     DVK(KP690983005, +0.690983005625052575897706582817180941139845410);
     DVK(KP952936919, +0.952936919628306576880750665357914584765951388);
     DVK(KP998026728, +0.998026728428271561952336806863450553336905220);
     DVK(KP570584518, +0.570584518783621657366766175430996792655723863);
     DVK(KP669429328, +0.669429328479476605641803240971985825917022098);
     DVK(KP923225144, +0.923225144846402650453449441572664695995209956);
     DVK(KP906616052, +0.906616052148196230441134447086066874408359177);
     DVK(KP956723877, +0.956723877038460305821989399535483155872969262);
     DVK(KP522616830, +0.522616830205754336872861364785224694908468440);
     DVK(KP945422727, +0.945422727388575946270360266328811958657216298);
     DVK(KP912575812, +0.912575812670962425556968549836277086778922727);
     DVK(KP982009705, +0.982009705009746369461829878184175962711969869);
     DVK(KP921078979, +0.921078979742360627699756128143719920817673854);
     DVK(KP734762448, +0.734762448793050413546343770063151342619912334);
     DVK(KP951056516, +0.951056516295153572116439333379382143405698634);
     DVK(KP958953096, +0.958953096729998668045963838399037225970891871);
     DVK(KP867381224, +0.867381224396525206773171885031575671309956167);
     DVK(KP269969613, +0.269969613759572083574752974412347470060951301);
     DVK(KP244189809, +0.244189809627953270309879511234821255780225091);
     DVK(KP845997307, +0.845997307939530944175097360758058292389769300);
     DVK(KP772036680, +0.772036680810363904029489473607579825330539880);
     DVK(KP132830569, +0.132830569247582714407653942074819768844536507);
     DVK(KP120146378, +0.120146378570687701782758537356596213647956445);
     DVK(KP987388751, +0.987388751065621252324603216482382109400433949);
     DVK(KP893101515, +0.893101515366181661711202267938416198338079437);
     DVK(KP786782374, +0.786782374965295178365099601674911834788448471);
     DVK(KP869845200, +0.869845200362138853122720822420327157933056305);
     DVK(KP447533225, +0.447533225982656890041886979663652563063114397);
     DVK(KP494780565, +0.494780565770515410344588413655324772219443730);
     DVK(KP578046249, +0.578046249379945007321754579646815604023525655);
     DVK(KP522847744, +0.522847744331509716623755382187077770911012542);
     DVK(KP059835404, +0.059835404262124915169548397419498386427871950);
     DVK(KP066152395, +0.066152395967733048213034281011006031460903353);
     DVK(KP603558818, +0.603558818296015001454675132653458027918768137);
     DVK(KP667278218, +0.667278218140296670899089292254759909713898805);
     DVK(KP559016994, +0.559016994374947424102293417182819058860154590);
     DVK(KP250000000, +0.250000000000000000000000000000000000000000000);
     DVK(KP618033988, +0.618033988749894848204586834365638117720309180);
     INT i;
     const R *xi;
     R *xo;
     xi = ri;
     xo = ro;
     for (i = v; i > 0; i = i - VL, xi = xi + (VL * ivs), xo = xo + (VL * ovs), MAKE_VOLATILE_STRIDE(is), MAKE_VOLATILE_STRIDE(os)) {
	  V T1g, T1k, T1I, T24, T2a, T1G, T1A, T1l, T1B, T1H, T1d;
	  {
	       V T2z, T1q, Ta, T9, T3n, Ty, Tl, T2O, T2W, T2l, T2s, TV, T1i, T1K, T1S;
	       V T3z, T3t, Tk, T3o, Tp, T2g, T2N, T2V, T2o, T2t, T1a, T1j, T1J, T1R, Tz;
	       V Tt, TA, Tw;
	       {
		    V T1, T5, T6, T2, T3;
		    T1 = LD(&(xi[0]), ivs, &(xi[0]));
		    T5 = LD(&(xi[WS(is, 10)]), ivs, &(xi[0]));
		    T6 = LD(&(xi[WS(is, 15)]), ivs, &(xi[WS(is, 1)]));
		    T2 = LD(&(xi[WS(is, 5)]), ivs, &(xi[WS(is, 1)]));
		    T3 = LD(&(xi[WS(is, 20)]), ivs, &(xi[0]));
		    {
			 V TH, TW, TK, TS, T10, T8, TN, TT, T17, TZ, T11;
			 TH = LD(&(xi[WS(is, 2)]), ivs, &(xi[0]));
			 TW = LD(&(xi[WS(is, 3)]), ivs, &(xi[WS(is, 1)]));
			 {
			      V TI, TJ, TL, T7, T1p, T4, T1o, TM, TX, TY;
			      TI = LD(&(xi[WS(is, 7)]), ivs, &(xi[WS(is, 1)]));
			      TJ = LD(&(xi[WS(is, 22)]), ivs, &(xi[0]));
			      TL = LD(&(xi[WS(is, 12)]), ivs, &(xi[0]));
			      T7 = VADD(T5, T6);
			      T1p = VSUB(T5, T6);
			      T4 = VADD(T2, T3);
			      T1o = VSUB(T2, T3);
			      TM = LD(&(xi[WS(is, 17)]), ivs, &(xi[WS(is, 1)]));
			      TX = LD(&(xi[WS(is, 8)]), ivs, &(xi[0]));
			      TK = VADD(TI, TJ);
			      TS = VSUB(TI, TJ);
			      TY = LD(&(xi[WS(is, 23)]), ivs, &(xi[WS(is, 1)]));
			      T10 = LD(&(xi[WS(is, 13)]), ivs, &(xi[WS(is, 1)]));
			      T2z = VFNMS(LDK(KP618033988), T1o, T1p);
			      T1q = VFMA(LDK(KP618033988), T1p, T1o);
			      Ta = VSUB(T4, T7);
			      T8 = VADD(T4, T7);
			      TN = VADD(TL, TM);
			      TT = VSUB(TM, TL);
			      T17 = VSUB(TX, TY);
			      TZ = VADD(TX, TY);
			      T11 = LD(&(xi[WS(is, 18)]), ivs, &(xi[0]));
			 }
			 {
			      V Tc, T2m, T19, Tn, To, Tr, Tj, T16, T2n, Ts, Tu, Tv;
			      {
				   V TU, T2j, TO, TQ, T12, T18;
				   Tc = LD(&(xi[WS(is, 1)]), ivs, &(xi[WS(is, 1)]));
				   T9 = VFNMS(LDK(KP250000000), T8, T1);
				   T3n = VADD(T1, T8);
				   TU = VFNMS(LDK(KP618033988), TT, TS);
				   T2j = VFMA(LDK(KP618033988), TS, TT);
				   TO = VADD(TK, TN);
				   TQ = VSUB(TN, TK);
				   T12 = VADD(T10, T11);
				   T18 = VSUB(T10, T11);
				   Ty = LD(&(xi[WS(is, 4)]), ivs, &(xi[0]));
				   {
					V T3r, T15, T13, Tf, Ti, T2k, TR, TP, T3s, T14;
					{
					     V Td, Te, Tg, Th;
					     Td = LD(&(xi[WS(is, 6)]), ivs, &(xi[0]));
					     Te = LD(&(xi[WS(is, 21)]), ivs, &(xi[WS(is, 1)]));
					     Tg = LD(&(xi[WS(is, 11)]), ivs, &(xi[WS(is, 1)]));
					     Th = LD(&(xi[WS(is, 16)]), ivs, &(xi[0]));
					     TP = VFNMS(LDK(KP250000000), TO, TH);
					     T3r = VADD(TH, TO);
					     T2m = VFNMS(LDK(KP618033988), T17, T18);
					     T19 = VFMA(LDK(KP618033988), T18, T17);
					     T15 = VSUB(T12, TZ);
					     T13 = VADD(TZ, T12);
					     Tf = VADD(Td, Te);
					     Tn = VSUB(Td, Te);
					     To = VSUB(Th, Tg);
					     Ti = VADD(Tg, Th);
					}
					T2k = VFMA(LDK(KP559016994), TQ, TP);
					TR = VFNMS(LDK(KP559016994), TQ, TP);
					Tr = LD(&(xi[WS(is, 24)]), ivs, &(xi[0]));
					T3s = VADD(TW, T13);
					T14 = VFNMS(LDK(KP250000000), T13, TW);
					Tj = VADD(Tf, Ti);
					Tl = VSUB(Tf, Ti);
					T2O = VFNMS(LDK(KP667278218), T2k, T2j);
					T2W = VFMA(LDK(KP603558818), T2j, T2k);
					T2l = VFMA(LDK(KP066152395), T2k, T2j);
					T2s = VFNMS(LDK(KP059835404), T2j, T2k);
					TV = VFNMS(LDK(KP522847744), TU, TR);
					T1i = VFMA(LDK(KP578046249), TR, TU);
					T1K = VFNMS(LDK(KP494780565), TR, TU);
					T1S = VFMA(LDK(KP447533225), TU, TR);
					T16 = VFNMS(LDK(KP559016994), T15, T14);
					T2n = VFMA(LDK(KP559016994), T15, T14);
					T3z = VSUB(T3r, T3s);
					T3t = VADD(T3r, T3s);
					Ts = LD(&(xi[WS(is, 9)]), ivs, &(xi[WS(is, 1)]));
					Tu = LD(&(xi[WS(is, 19)]), ivs, &(xi[WS(is, 1)]));
					Tv = LD(&(xi[WS(is, 14)]), ivs, &(xi[0]));
				   }
			      }
			      Tk = VFNMS(LDK(KP250000000), Tj, Tc);
			      T3o = VADD(Tc, Tj);
			      Tp = VFNMS(LDK(KP618033988), To, Tn);
			      T2g = VFMA(LDK(KP618033988), Tn, To);
			      T2N = VFMA(LDK(KP066152395), T2n, T2m);
			      T2V = VFNMS(LDK(KP059835404), T2m, T2n);
			      T2o = VFMA(LDK(KP869845200), T2n, T2m);
			      T2t = VFNMS(LDK(KP786782374), T2m, T2n);
			      T1a = VFNMS(LDK(KP893101515), T19, T16);
			      T1j = VFMA(LDK(KP987388751), T16, T19);
			      T1J = VFNMS(LDK(KP120146378), T19, T16);
			      T1R = VFMA(LDK(KP132830569), T16, T19);
			      Tz = VADD(Ts, Tr);
			      Tt = VSUB(Tr, Ts);
			      TA = VADD(Tv, Tu);
			      Tw = VSUB(Tu, Tv);
			 }
		    }
	       }
	       {
		    V T2p, T2I, T2u, T2C, Tx, T2d, T2X, T34, T2P, T3b, T2b, Tb, T2Q, T2Z, T2h;
		    V T2w, Tq, T1e, T1M, T1U, TE, T2c, T3q, T3y;
		    T2p = VFNMS(LDK(KP772036680), T2o, T2l);
		    T2I = VFMA(LDK(KP772036680), T2o, T2l);
		    T2u = VFMA(LDK(KP772036680), T2t, T2s);
		    T2C = VFNMS(LDK(KP772036680), T2t, T2s);
		    {
			 V TD, TB, Tm, T2f, T3p, TC;
			 Tx = VFMA(LDK(KP618033988), Tw, Tt);
			 T2d = VFNMS(LDK(KP618033988), Tt, Tw);
			 TD = VSUB(Tz, TA);
			 TB = VADD(Tz, TA);
			 Tm = VFMA(LDK(KP559016994), Tl, Tk);
			 T2f = VFNMS(LDK(KP559016994), Tl, Tk);
			 T2X = VFMA(LDK(KP845997307), T2W, T2V);
			 T34 = VFNMS(LDK(KP845997307), T2W, T2V);
			 T2P = VFNMS(LDK(KP845997307), T2O, T2N);
			 T3b = VFMA(LDK(KP845997307), T2O, T2N);
			 T2b = VFNMS(LDK(KP559016994), Ta, T9);
			 Tb = VFMA(LDK(KP559016994), Ta, T9);
			 T3p = VADD(Ty, TB);
			 TC = VFMS(LDK(KP250000000), TB, Ty);
			 T2Q = VFNMS(LDK(KP522847744), T2g, T2f);
			 T2Z = VFMA(LDK(KP578046249), T2f, T2g);
			 T2h = VFMA(LDK(KP893101515), T2g, T2f);
			 T2w = VFNMS(LDK(KP987388751), T2f, T2g);
			 Tq = VFNMS(LDK(KP244189809), Tp, Tm);
			 T1e = VFMA(LDK(KP269969613), Tm, Tp);
			 T1M = VFMA(LDK(KP667278218), Tm, Tp);
			 T1U = VFNMS(LDK(KP603558818), Tp, Tm);
			 TE = VFNMS(LDK(KP559016994), TD, TC);
			 T2c = VFMA(LDK(KP559016994), TD, TC);
			 T3q = VADD(T3o, T3p);
			 T3y = VSUB(T3o, T3p);
		    }
		    {
			 V T1Z, T25, T1P, T22, T1X, TG, T1b, T28, T1t, T1y, T1x, T1E, T1Q, T1Y;
			 {
			      V T26, T1L, T1T, TF, T1f, T1W, T3m, T3g, T2M, T2G, T39, T3j, T21, T1O, T20;
			      V T27;
			      T26 = VFMA(LDK(KP867381224), T1K, T1J);
			      T1L = VFNMS(LDK(KP867381224), T1K, T1J);
			      T20 = VFNMS(LDK(KP958953096), T1S, T1R);
			      T1T = VFMA(LDK(KP958953096), T1S, T1R);
			      {
				   V T2R, T2Y, T2e, T2v, T1N, T1V;
				   T2R = VFNMS(LDK(KP494780565), T2c, T2d);
				   T2Y = VFMA(LDK(KP447533225), T2d, T2c);
				   T2e = VFMA(LDK(KP120146378), T2d, T2c);
				   T2v = VFNMS(LDK(KP132830569), T2c, T2d);
				   TF = VFNMS(LDK(KP667278218), TE, Tx);
				   T1f = VFMA(LDK(KP603558818), Tx, TE);
				   T1N = VFMA(LDK(KP869845200), TE, Tx);
				   T1V = VFNMS(LDK(KP786782374), Tx, TE);
				   {
					V T3A, T3C, T3w, T3u;
					T3A = VMUL(LDK(KP951056516), VFMA(LDK(KP618033988), T3z, T3y));
					T3C = VMUL(LDK(KP951056516), VFNMS(LDK(KP618033988), T3y, T3z));
					T3w = VSUB(T3q, T3t);
					T3u = VADD(T3q, T3t);
					{
					     V T2B, T2x, T2H, T2i;
					     T2B = VFMA(LDK(KP734762448), T2w, T2v);
					     T2x = VFNMS(LDK(KP734762448), T2w, T2v);
					     T2H = VFNMS(LDK(KP734762448), T2h, T2e);
					     T2i = VFMA(LDK(KP734762448), T2h, T2e);
					     {
						  V T30, T35, T3c, T2S, T3v;
						  T30 = VFNMS(LDK(KP921078979), T2Z, T2Y);
						  T35 = VFMA(LDK(KP921078979), T2Z, T2Y);
						  T3c = VFMA(LDK(KP982009705), T2R, T2Q);
						  T2S = VFNMS(LDK(KP982009705), T2R, T2Q);
						  T1W = VFMA(LDK(KP912575812), T1V, T1U);
						  T1Z = VFNMS(LDK(KP912575812), T1V, T1U);
						  T1O = VFMA(LDK(KP912575812), T1N, T1M);
						  T25 = VFNMS(LDK(KP912575812), T1N, T1M);
						  ST(&(xo[0]), VADD(T3u, T3n), ovs, &(xo[0]));
						  T3v = VFNMS(LDK(KP250000000), T3u, T3n);
						  {
						       V T2y, T2J, T2q, T2D;
						       T2y = VFMA(LDK(KP945422727), T2x, T2u);
						       T2J = VFMA(LDK(KP522616830), T2x, T2I);
						       T2q = VFMA(LDK(KP956723877), T2p, T2i);
						       T2D = VFNMS(LDK(KP522616830), T2i, T2C);
						       {
							    V T3e, T31, T36, T2T;
							    T3e = VFMA(LDK(KP906616052), T30, T2X);
							    T31 = VFNMS(LDK(KP906616052), T30, T2X);
							    T36 = VFNMS(LDK(KP923225144), T2S, T2P);
							    T2T = VFMA(LDK(KP923225144), T2S, T2P);
							    {
								 V T3k, T3d, T3x, T3B;
								 T3k = VFNMS(LDK(KP669429328), T3b, T3c);
								 T3d = VFMA(LDK(KP570584518), T3c, T3b);
								 T3x = VFMA(LDK(KP559016994), T3w, T3v);
								 T3B = VFNMS(LDK(KP559016994), T3w, T3v);
								 {
								      V T2A, T2K, T2r, T2E;
								      T2A = VMUL(LDK(KP998026728), VFMA(LDK(KP952936919), T2z, T2y));
								      T2K = VFNMS(LDK(KP690983005), T2J, T2u);
								      T2r = VFMA(LDK(KP992114701), T2q, T2b);
								      T2E = VFMA(LDK(KP763932022), T2D, T2p);
								      {
									   V T32, T3a, T37, T3h;
									   T32 = VMUL(LDK(KP998026728), VFNMS(LDK(KP952936919), T2z, T31));
									   T3a = VFMA(LDK(KP262346850), T31, T2z);
									   T37 = VFNMS(LDK(KP997675361), T36, T35);
									   T3h = VFNMS(LDK(KP904508497), T36, T34);
									   {
										V T2U, T33, T3l, T3f;
										T2U = VFMA(LDK(KP949179823), T2T, T2b);
										T33 = VFNMS(LDK(KP237294955), T2T, T2b);
										T3l = VFNMS(LDK(KP669429328), T3e, T3k);
										T3f = VFMA(LDK(KP618033988), T3e, T3d);
										ST(&(xo[WS(os, 20)]), VFMAI(T3A, T3x), ovs, &(xo[0]));
										ST(&(xo[WS(os, 5)]), VFNMSI(T3A, T3x), ovs, &(xo[WS(os, 1)]));
										ST(&(xo[WS(os, 15)]), VFNMSI(T3C, T3B), ovs, &(xo[WS(os, 1)]));
										ST(&(xo[WS(os, 10)]), VFMAI(T3C, T3B), ovs, &(xo[0]));
										{
										     V T2L, T2F, T38, T3i;
										     T2L = VFMA(LDK(KP855719849), T2K, T2H);
										     ST(&(xo[WS(os, 22)]), VFMAI(T2A, T2r), ovs, &(xo[0]));
										     ST(&(xo[WS(os, 3)]), VFNMSI(T2A, T2r), ovs, &(xo[WS(os, 1)]));
										     T2F = VFNMS(LDK(KP855719849), T2E, T2B);
										     T38 = VFMA(LDK(KP560319534), T37, T34);
										     T3i = VFNMS(LDK(KP681693190), T3h, T35);
										     ST(&(xo[WS(os, 23)]), VFMAI(T32, T2U), ovs, &(xo[WS(os, 1)]));
										     ST(&(xo[WS(os, 2)]), VFNMSI(T32, T2U), ovs, &(xo[0]));
										     T3m = VMUL(LDK(KP951056516), VFNMS(LDK(KP876306680), T3l, T3a));
										     T3g = VMUL(LDK(KP951056516), VFNMS(LDK(KP949179823), T3f, T3a));
										     T2M = VMUL(LDK(KP951056516), VFNMS(LDK(KP992114701), T2L, T2z));
										     T2G = VFMA(LDK(KP897376177), T2F, T2b);
										     T39 = VFNMS(LDK(KP949179823), T38, T33);
										     T3j = VFNMS(LDK(KP860541664), T3i, T33);
										     T21 = VFMA(LDK(KP447417479), T1O, T20);
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
			      T1P = VFNMS(LDK(KP809385824), T1O, T1L);
			      ST(&(xo[WS(os, 17)]), VFMAI(T2M, T2G), ovs, &(xo[WS(os, 1)]));
			      ST(&(xo[WS(os, 8)]), VFNMSI(T2M, T2G), ovs, &(xo[0]));
			      ST(&(xo[WS(os, 12)]), VFMAI(T3g, T39), ovs, &(xo[0]));
			      ST(&(xo[WS(os, 13)]), VFNMSI(T3g, T39), ovs, &(xo[WS(os, 1)]));
			      ST(&(xo[WS(os, 7)]), VFMAI(T3m, T3j), ovs, &(xo[WS(os, 1)]));
			      ST(&(xo[WS(os, 18)]), VFNMSI(T3m, T3j), ovs, &(xo[0]));
			      T22 = VFMA(LDK(KP690983005), T21, T1L);
			      T27 = VFMA(LDK(KP447417479), T1W, T26);
			      T1X = VFMA(LDK(KP894834959), T1W, T1T);
			      {
				   V T1r, T1s, T1v, T1w;
				   T1r = VFNMS(LDK(KP916574801), T1f, T1e);
				   T1g = VFMA(LDK(KP916574801), T1f, T1e);
				   T1k = VFNMS(LDK(KP831864738), T1j, T1i);
				   T1s = VFMA(LDK(KP831864738), T1j, T1i);
				   T1v = VFNMS(LDK(KP829049696), TF, Tq);
				   TG = VFMA(LDK(KP829049696), TF, Tq);
				   T1b = VFMA(LDK(KP831864738), T1a, TV);
				   T1w = VFNMS(LDK(KP831864738), T1a, TV);
				   T28 = VFNMS(LDK(KP763932022), T27, T1T);
				   T1t = VFMA(LDK(KP904730450), T1s, T1r);
				   T1y = VFNMS(LDK(KP904730450), T1s, T1r);
				   T1x = VFMA(LDK(KP559154169), T1w, T1v);
				   T1E = VFNMS(LDK(KP683113946), T1v, T1w);
			      }
			 }
			 T1Q = VFNMS(LDK(KP992114701), T1P, Tb);
			 T1Y = VMUL(LDK(KP951056516), VFNMS(LDK(KP992114701), T1X, T1q));
			 {
			      V T1u, T1F, T1z, T1h, T1c, T23, T29;
			      T23 = VFNMS(LDK(KP999544308), T22, T1Z);
			      T29 = VFNMS(LDK(KP999544308), T28, T25);
			      T1I = VMUL(LDK(KP951056516), VFMA(LDK(KP968583161), T1t, T1q));
			      T1u = VFNMS(LDK(KP242145790), T1t, T1q);
			      T1F = VFMA(LDK(KP617882369), T1y, T1E);
			      T1z = VFMA(LDK(KP559016994), T1y, T1x);
			      T1h = VFNMS(LDK(KP904730450), T1b, TG);
			      T1c = VFMA(LDK(KP904730450), T1b, TG);
			      ST(&(xo[WS(os, 21)]), VFNMSI(T1Y, T1Q), ovs, &(xo[WS(os, 1)]));
			      ST(&(xo[WS(os, 4)]), VFMAI(T1Y, T1Q), ovs, &(xo[0]));
			      T24 = VFNMS(LDK(KP803003575), T23, Tb);
			      T2a = VMUL(LDK(KP951056516), VFNMS(LDK(KP803003575), T29, T1q));
			      T1G = VMUL(LDK(KP951056516), VFNMS(LDK(KP876306680), T1F, T1u));
			      T1A = VMUL(LDK(KP951056516), VFMA(LDK(KP968583161), T1z, T1u));
			      T1l = VFNMS(LDK(KP904730450), T1k, T1h);
			      T1B = VADD(T1g, T1h);
			      T1H = VFMA(LDK(KP968583161), T1c, Tb);
			      T1d = VFNMS(LDK(KP242145790), T1c, Tb);
			 }
		    }
	       }
	  }
	  ST(&(xo[WS(os, 9)]), VFMAI(T2a, T24), ovs, &(xo[WS(os, 1)]));
	  ST(&(xo[WS(os, 16)]), VFNMSI(T2a, T24), ovs, &(xo[0]));
	  {
	       V T1m, T1C, T1n, T1D;
	       T1m = VFNMS(LDK(KP618033988), T1l, T1g);
	       T1C = VFNMS(LDK(KP683113946), T1B, T1k);
	       ST(&(xo[WS(os, 24)]), VFMAI(T1I, T1H), ovs, &(xo[0]));
	       ST(&(xo[WS(os, 1)]), VFNMSI(T1I, T1H), ovs, &(xo[WS(os, 1)]));
	       T1n = VFNMS(LDK(KP876091699), T1m, T1d);
	       T1D = VFMA(LDK(KP792626838), T1C, T1d);
	       ST(&(xo[WS(os, 19)]), VFMAI(T1A, T1n), ovs, &(xo[WS(os, 1)]));
	       ST(&(xo[WS(os, 6)]), VFNMSI(T1A, T1n), ovs, &(xo[0]));
	       ST(&(xo[WS(os, 14)]), VFMAI(T1G, T1D), ovs, &(xo[0]));
	       ST(&(xo[WS(os, 11)]), VFNMSI(T1G, T1D), ovs, &(xo[WS(os, 1)]));
	  }
     }
}

static const kdft_desc desc = { 25, "n1fv_25", {43, 12, 181, 0}, &GENUS, 0, 0, 0, 0 };
void X(codelet_n1fv_25) (planner *p) {
     X(kdft_register) (p, n1fv_25, &desc);
}

#else				/* HAVE_FMA */

/* Generated by: ../../../genfft/gen_notw_c -simd -compact -variables 4 -pipeline-latency 8 -n 25 -name n1fv_25 -include n1f.h */

/*
 * This function contains 224 FP additions, 140 FP multiplications,
 * (or, 146 additions, 62 multiplications, 78 fused multiply/add),
 * 115 stack variables, 40 constants, and 50 memory accesses
 */
#include "n1f.h"

static void n1fv_25(const R *ri, const R *ii, R *ro, R *io, stride is, stride os, INT v, INT ivs, INT ovs)
{
     DVK(KP809016994, +0.809016994374947424102293417182819058860154590);
     DVK(KP309016994, +0.309016994374947424102293417182819058860154590);
     DVK(KP770513242, +0.770513242775789230803009636396177847271667672);
     DVK(KP1_274847979, +1.274847979497379420353425623352032390869834596);
     DVK(KP992114701, +0.992114701314477831049793042785778521453036709);
     DVK(KP250666467, +0.250666467128608490746237519633017587885836494);
     DVK(KP637423989, +0.637423989748689710176712811676016195434917298);
     DVK(KP1_541026485, +1.541026485551578461606019272792355694543335344);
     DVK(KP125333233, +0.125333233564304245373118759816508793942918247);
     DVK(KP1_984229402, +1.984229402628955662099586085571557042906073418);
     DVK(KP248689887, +0.248689887164854788242283746006447968417567406);
     DVK(KP1_937166322, +1.937166322257262238980336750929471627672024806);
     DVK(KP497379774, +0.497379774329709576484567492012895936835134813);
     DVK(KP968583161, +0.968583161128631119490168375464735813836012403);
     DVK(KP904827052, +0.904827052466019527713668647932697593970413911);
     DVK(KP851558583, +0.851558583130145297725004891488503407959946084);
     DVK(KP425779291, +0.425779291565072648862502445744251703979973042);
     DVK(KP1_809654104, +1.809654104932039055427337295865395187940827822);
     DVK(KP844327925, +0.844327925502015078548558063966681505381659241);
     DVK(KP1_071653589, +1.071653589957993236542617535735279956127150691);
     DVK(KP481753674, +0.481753674101715274987191502872129653528542010);
     DVK(KP1_752613360, +1.752613360087727174616231807844125166798128477);
     DVK(KP535826794, +0.535826794978996618271308767867639978063575346);
     DVK(KP1_688655851, +1.688655851004030157097116127933363010763318483);
     DVK(KP963507348, +0.963507348203430549974383005744259307057084020);
     DVK(KP876306680, +0.876306680043863587308115903922062583399064238);
     DVK(KP998026728, +0.998026728428271561952336806863450553336905220);
     DVK(KP125581039, +0.125581039058626752152356449131262266244969664);
     DVK(KP684547105, +0.684547105928688673732283357621209269889519233);
     DVK(KP1_457937254, +1.457937254842823046293460638110518222745143328);
     DVK(KP062790519, +0.062790519529313376076178224565631133122484832);
     DVK(KP1_996053456, +1.996053456856543123904673613726901106673810439);
     DVK(KP1_369094211, +1.369094211857377347464566715242418539779038465);
     DVK(KP728968627, +0.728968627421411523146730319055259111372571664);
     DVK(KP293892626, +0.293892626146236564584352977319536384298826219);
     DVK(KP475528258, +0.475528258147576786058219666689691071702849317);
     DVK(KP250000000, +0.250000000000000000000000000000000000000000000);
     DVK(KP587785252, +0.587785252292473129168705954639072768597652438);
     DVK(KP951056516, +0.951056516295153572116439333379382143405698634);
     DVK(KP559016994, +0.559016994374947424102293417182819058860154590);
     INT i;
     const R *xi;
     R *xo;
     xi = ri;
     xo = ro;
     for (i = v; i > 0; i = i - VL, xi = xi + (VL * ivs), xo = xo + (VL * ovs), MAKE_VOLATILE_STRIDE(is), MAKE_VOLATILE_STRIDE(os)) {
	  V T7, T1g, T26, Ta, T2R, T2N, T2O, T2P, T19, T1Y, T16, T1Z, T1a, T2v, T1l;
	  V T2m, TU, T21, TR, T22, TV, T2u, T1k, T2l, T2K, T2L, T2M, TE, T1R, TB;
	  V T1S, TF, T2r, T1i, T2j, Tp, T1U, Tm, T1V, Tq, T2s, T1h, T2i;
	  {
	       V T8, T6, T1f, T3, T1e, T25, T9;
	       T8 = LD(&(xi[0]), ivs, &(xi[0]));
	       {
		    V T4, T5, T1, T2;
		    T4 = LD(&(xi[WS(is, 10)]), ivs, &(xi[0]));
		    T5 = LD(&(xi[WS(is, 15)]), ivs, &(xi[WS(is, 1)]));
		    T6 = VADD(T4, T5);
		    T1f = VSUB(T4, T5);
		    T1 = LD(&(xi[WS(is, 5)]), ivs, &(xi[WS(is, 1)]));
		    T2 = LD(&(xi[WS(is, 20)]), ivs, &(xi[0]));
		    T3 = VADD(T1, T2);
		    T1e = VSUB(T1, T2);
	       }
	       T7 = VMUL(LDK(KP559016994), VSUB(T3, T6));
	       T1g = VFMA(LDK(KP951056516), T1e, VMUL(LDK(KP587785252), T1f));
	       T25 = VMUL(LDK(KP951056516), T1f);
	       T26 = VFNMS(LDK(KP587785252), T1e, T25);
	       T9 = VADD(T3, T6);
	       Ta = VFNMS(LDK(KP250000000), T9, T8);
	       T2R = VADD(T8, T9);
	  }
	  {
	       V TO, T13, TN, TT, TP, TS, T12, T18, T14, T17, T15, TQ;
	       TO = LD(&(xi[WS(is, 2)]), ivs, &(xi[0]));
	       T13 = LD(&(xi[WS(is, 3)]), ivs, &(xi[WS(is, 1)]));
	       {
		    V TH, TI, TJ, TK, TL, TM;
		    TH = LD(&(xi[WS(is, 7)]), ivs, &(xi[WS(is, 1)]));
		    TI = LD(&(xi[WS(is, 22)]), ivs, &(xi[0]));
		    TJ = VADD(TH, TI);
		    TK = LD(&(xi[WS(is, 12)]), ivs, &(xi[0]));
		    TL = LD(&(xi[WS(is, 17)]), ivs, &(xi[WS(is, 1)]));
		    TM = VADD(TK, TL);
		    TN = VMUL(LDK(KP559016994), VSUB(TJ, TM));
		    TT = VSUB(TK, TL);
		    TP = VADD(TJ, TM);
		    TS = VSUB(TH, TI);
	       }
	       {
		    V TW, TX, TY, TZ, T10, T11;
		    TW = LD(&(xi[WS(is, 8)]), ivs, &(xi[0]));
		    TX = LD(&(xi[WS(is, 23)]), ivs, &(xi[WS(is, 1)]));
		    TY = VADD(TW, TX);
		    TZ = LD(&(xi[WS(is, 13)]), ivs, &(xi[WS(is, 1)]));
		    T10 = LD(&(xi[WS(is, 18)]), ivs, &(xi[0]));
		    T11 = VADD(TZ, T10);
		    T12 = VMUL(LDK(KP559016994), VSUB(TY, T11));
		    T18 = VSUB(TZ, T10);
		    T14 = VADD(TY, T11);
		    T17 = VSUB(TW, TX);
	       }
	       T2N = VADD(TO, TP);
	       T2O = VADD(T13, T14);
	       T2P = VADD(T2N, T2O);
	       T19 = VFMA(LDK(KP475528258), T17, VMUL(LDK(KP293892626), T18));
	       T1Y = VFNMS(LDK(KP293892626), T17, VMUL(LDK(KP475528258), T18));
	       T15 = VFNMS(LDK(KP250000000), T14, T13);
	       T16 = VADD(T12, T15);
	       T1Z = VSUB(T15, T12);
	       T1a = VFNMS(LDK(KP1_369094211), T19, VMUL(LDK(KP728968627), T16));
	       T2v = VFMA(LDK(KP1_996053456), T1Y, VMUL(LDK(KP062790519), T1Z));
	       T1l = VFMA(LDK(KP1_457937254), T19, VMUL(LDK(KP684547105), T16));
	       T2m = VFNMS(LDK(KP998026728), T1Z, VMUL(LDK(KP125581039), T1Y));
	       TU = VFMA(LDK(KP475528258), TS, VMUL(LDK(KP293892626), TT));
	       T21 = VFNMS(LDK(KP293892626), TS, VMUL(LDK(KP475528258), TT));
	       TQ = VFNMS(LDK(KP250000000), TP, TO);
	       TR = VADD(TN, TQ);
	       T22 = VSUB(TQ, TN);
	       TV = VFNMS(LDK(KP963507348), TU, VMUL(LDK(KP876306680), TR));
	       T2u = VFMA(LDK(KP1_688655851), T21, VMUL(LDK(KP535826794), T22));
	       T1k = VFMA(LDK(KP1_752613360), TU, VMUL(LDK(KP481753674), TR));
	       T2l = VFNMS(LDK(KP844327925), T22, VMUL(LDK(KP1_071653589), T21));
	  }
	  {
	       V Tj, Ty, Ti, To, Tk, Tn, Tx, TD, Tz, TC, TA, Tl;
	       Tj = LD(&(xi[WS(is, 1)]), ivs, &(xi[WS(is, 1)]));
	       Ty = LD(&(xi[WS(is, 4)]), ivs, &(xi[0]));
	       {
		    V Tc, Td, Te, Tf, Tg, Th;
		    Tc = LD(&(xi[WS(is, 6)]), ivs, &(xi[0]));
		    Td = LD(&(xi[WS(is, 21)]), ivs, &(xi[WS(is, 1)]));
		    Te = VADD(Tc, Td);
		    Tf = LD(&(xi[WS(is, 11)]), ivs, &(xi[WS(is, 1)]));
		    Tg = LD(&(xi[WS(is, 16)]), ivs, &(xi[0]));
		    Th = VADD(Tf, Tg);
		    Ti = VMUL(LDK(KP559016994), VSUB(Te, Th));
		    To = VSUB(Tf, Tg);
		    Tk = VADD(Te, Th);
		    Tn = VSUB(Tc, Td);
	       }
	       {
		    V Tr, Ts, Tt, Tu, Tv, Tw;
		    Tr = LD(&(xi[WS(is, 9)]), ivs, &(xi[WS(is, 1)]));
		    Ts = LD(&(xi[WS(is, 24)]), ivs, &(xi[0]));
		    Tt = VADD(Tr, Ts);
		    Tu = LD(&(xi[WS(is, 14)]), ivs, &(xi[0]));
		    Tv = LD(&(xi[WS(is, 19)]), ivs, &(xi[WS(is, 1)]));
		    Tw = VADD(Tu, Tv);
		    Tx = VMUL(LDK(KP559016994), VSUB(Tt, Tw));
		    TD = VSUB(Tu, Tv);
		    Tz = VADD(Tt, Tw);
		    TC = VSUB(Tr, Ts);
	       }
	       T2K = VADD(Tj, Tk);
	       T2L = VADD(Ty, Tz);
	       T2M = VADD(T2K, T2L);
	       TE = VFMA(LDK(KP475528258), TC, VMUL(LDK(KP293892626), TD));
	       T1R = VFNMS(LDK(KP293892626), TC, VMUL(LDK(KP475528258), TD));
	       TA = VFNMS(LDK(KP250000000), Tz, Ty);
	       TB = VADD(Tx, TA);
	       T1S = VSUB(TA, Tx);
	       TF = VFNMS(LDK(KP1_688655851), TE, VMUL(LDK(KP535826794), TB));
	       T2r = VFNMS(LDK(KP425779291), T1S, VMUL(LDK(KP1_809654104), T1R));
	       T1i = VFMA(LDK(KP1_071653589), TE, VMUL(LDK(KP844327925), TB));
	       T2j = VFMA(LDK(KP851558583), T1R, VMUL(LDK(KP904827052), T1S));
	       Tp = VFMA(LDK(KP475528258), Tn, VMUL(LDK(KP293892626), To));
	       T1U = VFNMS(LDK(KP293892626), Tn, VMUL(LDK(KP475528258), To));
	       Tl = VFNMS(LDK(KP250000000), Tk, Tj);
	       Tm = VADD(Ti, Tl);
	       T1V = VSUB(Tl, Ti);
	       Tq = VFNMS(LDK(KP497379774), Tp, VMUL(LDK(KP968583161), Tm));
	       T2s = VFMA(LDK(KP963507348), T1U, VMUL(LDK(KP876306680), T1V));
	       T1h = VFMA(LDK(KP1_937166322), Tp, VMUL(LDK(KP248689887), Tm));
	       T2i = VFNMS(LDK(KP481753674), T1V, VMUL(LDK(KP1_752613360), T1U));
	  }
	  {
	       V T2Q, T2S, T2T, T2X, T2Y, T2V, T2W, T2Z, T2U;
	       T2Q = VMUL(LDK(KP559016994), VSUB(T2M, T2P));
	       T2S = VADD(T2M, T2P);
	       T2T = VFNMS(LDK(KP250000000), T2S, T2R);
	       T2V = VSUB(T2K, T2L);
	       T2W = VSUB(T2N, T2O);
	       T2X = VBYI(VFMA(LDK(KP951056516), T2V, VMUL(LDK(KP587785252), T2W)));
	       T2Y = VBYI(VFNMS(LDK(KP587785252), T2V, VMUL(LDK(KP951056516), T2W)));
	       ST(&(xo[0]), VADD(T2R, T2S), ovs, &(xo[0]));
	       T2Z = VSUB(T2T, T2Q);
	       ST(&(xo[WS(os, 10)]), VADD(T2Y, T2Z), ovs, &(xo[0]));
	       ST(&(xo[WS(os, 15)]), VSUB(T2Z, T2Y), ovs, &(xo[WS(os, 1)]));
	       T2U = VADD(T2Q, T2T);
	       ST(&(xo[WS(os, 5)]), VSUB(T2U, T2X), ovs, &(xo[WS(os, 1)]));
	       ST(&(xo[WS(os, 20)]), VADD(T2X, T2U), ovs, &(xo[0]));
	  }
	  {
	       V T2t, T2y, T2z, T2w, T1T, T1W, T1X, T2c, T2d, T2e, T29, T2a, T2b, T20, T23;
	       V T24, T2p, T2o, T2q, T28, T2D, T2C, T2E, T2x, T2F;
	       T2t = VSUB(T2r, T2s);
	       T2y = VADD(T2i, T2j);
	       T2z = VSUB(T2l, T2m);
	       T2w = VSUB(T2u, T2v);
	       T1T = VFNMS(LDK(KP125333233), T1S, VMUL(LDK(KP1_984229402), T1R));
	       T1W = VFMA(LDK(KP1_457937254), T1U, VMUL(LDK(KP684547105), T1V));
	       T1X = VSUB(T1T, T1W);
	       T2c = VFNMS(LDK(KP1_996053456), T21, VMUL(LDK(KP062790519), T22));
	       T2d = VFMA(LDK(KP1_541026485), T1Y, VMUL(LDK(KP637423989), T1Z));
	       T2e = VSUB(T2c, T2d);
	       T29 = VFNMS(LDK(KP1_369094211), T1U, VMUL(LDK(KP728968627), T1V));
	       T2a = VFMA(LDK(KP250666467), T1R, VMUL(LDK(KP992114701), T1S));
	       T2b = VSUB(T29, T2a);
	       T20 = VFNMS(LDK(KP770513242), T1Z, VMUL(LDK(KP1_274847979), T1Y));
	       T23 = VFMA(LDK(KP125581039), T21, VMUL(LDK(KP998026728), T22));
	       T24 = VSUB(T20, T23);
	       {
		    V T2k, T2n, T2A, T2B;
		    T2k = VSUB(T2i, T2j);
		    T2n = VADD(T2l, T2m);
		    T2p = VADD(T2k, T2n);
		    T2o = VMUL(LDK(KP559016994), VSUB(T2k, T2n));
		    T2q = VFNMS(LDK(KP250000000), T2p, T26);
		    T28 = VSUB(Ta, T7);
		    T2A = VADD(T2s, T2r);
		    T2B = VADD(T2u, T2v);
		    T2D = VADD(T2A, T2B);
		    T2C = VMUL(LDK(KP559016994), VSUB(T2A, T2B));
		    T2E = VFNMS(LDK(KP250000000), T2D, T28);
	       }
	       {
		    V T2I, T2J, T27, T2f;
		    T2I = VBYI(VADD(T26, T2p));
		    T2J = VADD(T28, T2D);
		    ST(&(xo[WS(os, 2)]), VADD(T2I, T2J), ovs, &(xo[0]));
		    ST(&(xo[WS(os, 23)]), VSUB(T2J, T2I), ovs, &(xo[WS(os, 1)]));
		    T27 = VBYI(VSUB(VADD(T1X, T24), T26));
		    T2f = VADD(T28, VADD(T2b, T2e));
		    ST(&(xo[WS(os, 3)]), VADD(T27, T2f), ovs, &(xo[WS(os, 1)]));
		    ST(&(xo[WS(os, 22)]), VSUB(T2f, T27), ovs, &(xo[0]));
	       }
	       T2x = VBYI(VADD(T2o, VADD(T2q, VFNMS(LDK(KP587785252), T2w, VMUL(LDK(KP951056516), T2t)))));
	       T2F = VFMA(LDK(KP951056516), T2y, VFMA(LDK(KP587785252), T2z, VADD(T2C, T2E)));
	       ST(&(xo[WS(os, 7)]), VADD(T2x, T2F), ovs, &(xo[WS(os, 1)]));
	       ST(&(xo[WS(os, 18)]), VSUB(T2F, T2x), ovs, &(xo[0]));
	       {
		    V T2G, T2H, T2g, T2h;
		    T2G = VBYI(VADD(T2q, VSUB(VFMA(LDK(KP587785252), T2t, VMUL(LDK(KP951056516), T2w)), T2o)));
		    T2H = VFMA(LDK(KP587785252), T2y, VSUB(VFNMS(LDK(KP951056516), T2z, T2E), T2C));
		    ST(&(xo[WS(os, 12)]), VADD(T2G, T2H), ovs, &(xo[0]));
		    ST(&(xo[WS(os, 13)]), VSUB(T2H, T2G), ovs, &(xo[WS(os, 1)]));
		    T2g = VFMA(LDK(KP309016994), T2b, VFNMS(LDK(KP809016994), T2e, VFNMS(LDK(KP587785252), VADD(T23, T20), VFNMS(LDK(KP951056516), VADD(T1W, T1T), T28))));
		    T2h = VBYI(VSUB(VFNMS(LDK(KP587785252), VADD(T2c, T2d), VFNMS(LDK(KP809016994), T24, VFNMS(LDK(KP951056516), VADD(T29, T2a), VMUL(LDK(KP309016994), T1X)))), T26));
		    ST(&(xo[WS(os, 17)]), VSUB(T2g, T2h), ovs, &(xo[WS(os, 1)]));
		    ST(&(xo[WS(os, 8)]), VADD(T2g, T2h), ovs, &(xo[0]));
	       }
	  }
	  {
	       V T1p, T1u, T1w, T1q, T1B, T1C, T1D, T1L, T1M, T1N, T1I, T1J, T1K, T1E, T1F;
	       V T1G, T1n, T1r, T1s, Tb, T1c, T1v, T1x, T1t, T1y;
	       T1p = VSUB(TF, Tq);
	       T1u = VSUB(T1i, T1h);
	       T1w = VSUB(T1l, T1k);
	       T1q = VSUB(TV, T1a);
	       T1B = VFMA(LDK(KP1_688655851), Tp, VMUL(LDK(KP535826794), Tm));
	       T1C = VFMA(LDK(KP1_541026485), TE, VMUL(LDK(KP637423989), TB));
	       T1D = VSUB(T1B, T1C);
	       T1L = VFMA(LDK(KP851558583), TU, VMUL(LDK(KP904827052), TR));
	       T1M = VFMA(LDK(KP1_984229402), T19, VMUL(LDK(KP125333233), T16));
	       T1N = VADD(T1L, T1M);
	       T1I = VFNMS(LDK(KP844327925), Tm, VMUL(LDK(KP1_071653589), Tp));
	       T1J = VFNMS(LDK(KP1_274847979), TE, VMUL(LDK(KP770513242), TB));
	       T1K = VADD(T1I, T1J);
	       T1E = VFNMS(LDK(KP425779291), TR, VMUL(LDK(KP1_809654104), TU));
	       T1F = VFNMS(LDK(KP992114701), T16, VMUL(LDK(KP250666467), T19));
	       T1G = VADD(T1E, T1F);
	       {
		    V T1j, T1m, TG, T1b;
		    T1j = VADD(T1h, T1i);
		    T1m = VADD(T1k, T1l);
		    T1n = VADD(T1j, T1m);
		    T1r = VFMS(LDK(KP250000000), T1n, T1g);
		    T1s = VMUL(LDK(KP559016994), VSUB(T1m, T1j));
		    Tb = VADD(T7, Ta);
		    TG = VADD(Tq, TF);
		    T1b = VADD(TV, T1a);
		    T1c = VADD(TG, T1b);
		    T1v = VFNMS(LDK(KP250000000), T1c, Tb);
		    T1x = VMUL(LDK(KP559016994), VSUB(TG, T1b));
	       }
	       {
		    V T1d, T1o, T1H, T1O;
		    T1d = VADD(Tb, T1c);
		    T1o = VBYI(VADD(T1g, T1n));
		    ST(&(xo[WS(os, 1)]), VSUB(T1d, T1o), ovs, &(xo[WS(os, 1)]));
		    ST(&(xo[WS(os, 24)]), VADD(T1d, T1o), ovs, &(xo[0]));
		    T1H = VADD(Tb, VADD(T1D, T1G));
		    T1O = VBYI(VADD(T1g, VSUB(T1K, T1N)));
		    ST(&(xo[WS(os, 21)]), VSUB(T1H, T1O), ovs, &(xo[WS(os, 1)]));
		    ST(&(xo[WS(os, 4)]), VADD(T1H, T1O), ovs, &(xo[0]));
	       }
	       T1t = VBYI(VADD(VFMA(LDK(KP587785252), T1p, VMUL(LDK(KP951056516), T1q)), VSUB(T1r, T1s)));
	       T1y = VFMA(LDK(KP587785252), T1u, VFNMS(LDK(KP951056516), T1w, VSUB(T1v, T1x)));
	       ST(&(xo[WS(os, 11)]), VADD(T1t, T1y), ovs, &(xo[WS(os, 1)]));
	       ST(&(xo[WS(os, 14)]), VSUB(T1y, T1t), ovs, &(xo[0]));
	       {
		    V T1z, T1A, T1P, T1Q;
		    T1z = VBYI(VADD(VFNMS(LDK(KP587785252), T1q, VMUL(LDK(KP951056516), T1p)), VADD(T1r, T1s)));
		    T1A = VFMA(LDK(KP951056516), T1u, VADD(T1x, VFMA(LDK(KP587785252), T1w, T1v)));
		    ST(&(xo[WS(os, 6)]), VADD(T1z, T1A), ovs, &(xo[0]));
		    ST(&(xo[WS(os, 19)]), VSUB(T1A, T1z), ovs, &(xo[WS(os, 1)]));
		    T1P = VBYI(VADD(T1g, VFMA(LDK(KP309016994), T1K, VFMA(LDK(KP587785252), VSUB(T1F, T1E), VFNMS(LDK(KP951056516), VADD(T1B, T1C), VMUL(LDK(KP809016994), T1N))))));
		    T1Q = VFMA(LDK(KP309016994), T1D, VFMA(LDK(KP951056516), VSUB(T1I, T1J), VFMA(LDK(KP587785252), VSUB(T1M, T1L), VFNMS(LDK(KP809016994), T1G, Tb))));
		    ST(&(xo[WS(os, 9)]), VADD(T1P, T1Q), ovs, &(xo[WS(os, 1)]));
		    ST(&(xo[WS(os, 16)]), VSUB(T1Q, T1P), ovs, &(xo[0]));
	       }
	  }
     }
}

static const kdft_desc desc = { 25, "n1fv_25", {146, 62, 78, 0}, &GENUS, 0, 0, 0, 0 };
void X(codelet_n1fv_25) (planner *p) {
     X(kdft_register) (p, n1fv_25, &desc);
}

#endif				/* HAVE_FMA */
