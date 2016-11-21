#ifndef CALCNORMAL_CK
#define CALCNORMAL_CK

namespace calcnormal {

	double Cum_Normal( double z );
	
	//
	//     Newton法による根の計算   
	//
	void Newton( 	double & x,		//  根の初期値、戻り値は根 f(x)=c
			double c,		//  関数値
			double (*f)( double ),	//  関数
			double (*df)( double ),	//  導関数
			double acc );
}

#endif
