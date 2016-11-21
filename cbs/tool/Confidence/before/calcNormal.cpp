#include <cmath>
#include "CalcIntgrt.h"		//	ガウス・ルジャンドル積分公式用クラス型 AdaptiveGL の宣言
#include "calcNormal.h"

namespace calcnormal {

	using namespace std;
	using namespace myLib;
	using namespace calcnormal;

	double knormal( double z ){
		return exp(-0.5 * z * z);
	}

	double Cum_Normal( double z ) {
		double p;
		double pi = atan(1.0) * 4.0;
		if (z == 0.0){
			p = 0.5;
		}else if(z > 0.0){
			AdaptiveGL agl;		//	積分用クラス型 AdaptiveGL のオブジェクト agl
			p = 0.5 + agl.integral( 0.0, z, knormal ) / sqrt(2.0 * pi);
		} else {
			AdaptiveGL agl;
			p = 0.5 - agl.integral( z, 0.0, knormal ) / sqrt(2.0 * pi);
		}

		return p;	//	p = Prob(X < z),  X ~ standard normal distribution
	}


	//
	//     Bisection法による根の計算    
	//
	void Bisection( double (*f)(double),
			double s,			 //   fが増加関数のとき s > 0.0
			double c,			 //   根に対する関数値
			double L_b, double U_b,		 //   根の存在区間の下限と上限
			double & Root,			 //   根  f(Root) = c
			double acc ){
		if ( (f(L_b) - c) * (f(U_b) - c) > 0.0 ){
			throw  "上限と下限の組み合わせが不適切です。";
		}
		do {
			double m = 0.5 * (L_b + U_b);
			double v = f(m);
			if ( s * (v - c) > 0.0 ) {
				U_b = m;
			} else {
				L_b = m;
			}
		} while ( (abs(U_b - L_b) >= acc * abs(U_b))
					&&
			  ( (abs(U_b) + abs(L_b)) >= 1.0e-14)	);
		Root = 0.5 * (L_b + U_b);
	}

	//
	//     Newton法による根の計算   
	//
	void Newton( 	double & x,		//  根の初期値、戻り値は根 f(x)=c
			double c,		//  関数値
			double (*f)( double ),	//  関数
			double (*df)( double ),	//  導関数
			double acc ){
		 int NStep = 0;
		 int ck = 0;
		 double x0;
		 do {
			 NStep++;
			 if (NStep > 20) {	//  20回以上繰り返しのとき
				 ck = 1;
				 break;
			 };
			 x0 = x;
			 x = x0 + (c - f(x0)) / df(x0);
		 } while ( (abs(x - x0) >= (acc * (abs(x) + abs(x0))))
					 &&
			 	( (abs(x) + abs(x0)) >= 1.0e-14 )  );

		 if (ck == 0) return;

	//	   Bisection法で計算

		 double L_b = x;
		 do {
				L_b -= 1.0;
		 } while ( f(L_b) >= c );
		 double U_b = x;
		 do {
				U_b += 1.0;
		 } while ( f(U_b) <= c );
		 Bisection( f, 1.0, c, L_b, U_b, x, acc );
		 return;
	}
}
