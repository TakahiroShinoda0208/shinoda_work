#ifndef CALCINTGRL_CK
#define CALCINTGRL_CK

namespace myLib {
	//
	//	ガウス・ルジャンドルの積分公式による適応的方法
	//	岡本安晴（2009）「統計学を学ぶための数学入門[下]」培風館、pp. 117-118.
	class AdaptiveGL {
		public:
			double (*f)(double);
			AdaptiveGL(){}
			virtual ~AdaptiveGL(){}

			double integral( double a, double b, double (*func)(double));
			void   calcIntegral( double & s0, double a, double b );
			double Gauss_Legendre( double a, double b );
	};

}  

#endif

