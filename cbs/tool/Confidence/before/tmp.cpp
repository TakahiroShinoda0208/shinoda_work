#include <iostream>
#include <iomanip>
#include <cmath>
#include "calcNormal.h"		//	ニュートン法の関数 Newton の宣言

using namespace std;
using namespace calcnormal;


double dcalc_p_normal( double z ){
	double pi = atan(1.0) * 4.0;
	double v = exp(-0.5 * z * z) / sqrt(2.0 * pi);
	return v;
}

double calc_p_normal( double z ){
	double p = Cum_Normal( z );
	return p;
}

double calc_z_normal( double p ){

	double z = 0.0;
	Newton( z, p, calc_p_normal, dcalc_p_normal, 1.0e-12 );		//	ニュートン法による根の計算
	return z;	//	p = Prob(X < z),  X ~ standard normal distribution
}

int main(){
      for(double i=50.0;i<=99.95;i+=0.05){
            double p=(i/100);
            double z = calc_z_normal( p );
            cout <<"%"<<"\t"<<(100-200*(1-p))<<"\t"<< "p" <<"\t"<<p<<"\t"<<"z"<<"\t"<<setprecision(6)<<z<<endl;
            
      }
      
      return 0;
}
