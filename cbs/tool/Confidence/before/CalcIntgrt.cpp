#include "CalcIntgrt.h"
#include <cmath>

using namespace std;
using namespace myLib;

namespace myLib {

	//
	//	ガウス・ルジャンドルの積分公式による適応的方法
	//	岡本安晴（2009）「統計学を学ぶための数学入門[下]」培風館、pp. 117-118.

	double AdaptiveGL::integral(double a, double b, double (*func)(double)){
		f = func;
		double v = 0.0;
		calcIntegral( v, a, b );
		return v;
	}


	void AdaptiveGL::calcIntegral(double & s0, double a, double b){
		double s1 = Gauss_Legendre( a, 0.5*(a + b) );
		double s2 = Gauss_Legendre( 0.5*(a + b), b );
		if (((abs( s0 - s1 - s2 ) < (1.0e-14)*abs(s1 + s2))
			|| 
			((abs(s0) + abs(s1 + s2)) < 1.0e-14))
			&&
			(abs(b - a) < 1.0)){
				s0 = s1 + s2;
				return;
		}
		else{
				calcIntegral( s1, a, 0.5*(a + b) );
				calcIntegral( s2, 0.5*(a + b), b );
				s0 = s1 + s2;
				return;
		}
	}


	double AdaptiveGL::Gauss_Legendre(double a, double b){
		double x0[9] = {
		    		-9.68160239507626090E-0001,
				-8.36031107326635794E-0001,
				-6.13371432700590397E-0001,
				-3.24253423403808929E-0001,
				 0.00000000000000000E+0000,
				 3.24253423403808929E-0001,
				 6.13371432700590397E-0001,
				 8.36031107326635794E-0001,
				 9.68160239507626090E-0001
				};
		double w[9] = {
				8.12743883615744120E-0002,
				1.80648160694857404E-0001,
				2.60610696402935462E-0001,
				3.12347077040002840E-0001,
				3.30239355001259763E-0001,
				3.12347077040002840E-0001,
				2.60610696402935462E-0001,
				1.80648160694857404E-0001,
				8.12743883615744120E-0002  
				};

		double v1 = 0.0;
		double i_w = b - a;
		double xi;
		for (int i = 0; i < 9; i++){
			xi = (0.5 * i_w * x0[i]) + (0.5 * (b + a));
			v1 += w[i] * f(xi);
		}
		v1 = 0.5 * i_w * v1;
		return v1;
	}

}  

