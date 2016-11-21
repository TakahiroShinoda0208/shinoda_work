#include <iostream>//標準データ入出力
#include <fstream>//ファイルの入出力
#include <vector>//vector(動的配列クラス)
#include <string>//string(文字列クラス)
#include <sstream>//文字列の入出力
#include <unordered_map>//unordered_map関数の導入
#include <map>//map関数の導入
#include <set>//set関数の導入
#include <stdlib.h>//絶対値を用いるための関数
#include <algorithm>    // std::copy
#include<iomanip>//少数点以下表示
#include<time.h>
#include <math.h> //平方根の使用
using namespace std;

//関数プロトタイプ宣言
vector<string> split(const string &str, char sep);
void set_vector(vector<double> &oa,vector<double> &ca,vector<string> &b,ifstream &fin1);
void conf_co(ifstream &fin2,double &in,double &out);
void calculate(vector<double>&open_rate,vector<double>&close_rate,vector<string>&date,ifstream &fin2,double &in,double &out,int &day);



//main関数
int main(int argc,char*argv[1])
{    
      ifstream fin1;
      ifstream fin2;
      
      int day=300;
      double in=50; //正常値信頼区間の信頼係数
      double out=90; //外れ値信頼区間の信頼係数
      int flag=0;
      

      for(int i=0;i<argc;i++){

            string ss=argv[i];
            if(ss=="-f"){
                  fin1.open(argv[i+1]);     
            }
            if(ss=="-C"){
                  fin2.open(argv[i+1]);     
            }
            if(ss=="-day"){
                  day=atoi(argv[i+1]);     
            }
            if(ss=="-in"){
                  in=atof(argv[i+1]);     
            }
            if(ss=="-out"){
                  out=atof(argv[i+1]);     
            }
            if(ss=="-open"){
                  flag=1;
            }

            
      }
      
//入力ファイルが存在しなかった時の出力
      if(!fin1 || argc<=2){
            cout << endl;
            cout <<"\t"<<"N  O  R  M"<<"\n\n\n";
            
            cout <<"version 1.0" <<"\n";
            cout <<"updated 2016/11/13"<<"\t"<<"TAKAHIRO SHINODA"<<"\n\n\n";
            cout <<"output confidence region"<<"\n\n\n";
            
            cout << "This is the tool for analyis of stock data." <<"\n\n\n";
            cout <<"ex."<<"\n\n";
            cout <<"Norm -f 1657_7.tsv -day 180 > hoge.tsv"<<"\n";
            cout << "-----------------------------------------------------------------------------------------" << endl;
            cout << "-f"<<"\t\t"<<" : Input tsvfile"<< endl;
            cout << "-C"<<"\t\t"<<" : Input Confidence coefficient"<< endl;
            cout << "-day"<<"\t\t"<<" : day for calculation for deviation rate "<<"\t\t"<<"[default 300]"<< endl;
            cout << "-in"<<"\t\t"<<" : normal interval region "<<"\t\t\t\t"<<"[default 50]"<< endl;
            cout << "-out"<<"\t\t"<<" : outlier interval region  "<<"\t\t\t\t"<<"[default 95]"<< endl;
            //cout << "-open"<<"\t\t"<<" : use opening price "<<"\t\t\t\t"<<"[default closing price]"<< endl;
            cout << "-----------------------------------------------------------------------------------------" <<"\n\n\n";

            return 1;
            
      }
      
      vector<double> close_price; //配列
      vector<double> open_price; //配列
      vector<string> date; //配列
      
      

      //deviation rateをvectorに格納
      set_vector(open_price,close_price,date,fin1);

      
      
      //信頼係数保存
      conf_co(fin2,in,out);

      //各日にちの信頼区間を推定
      calculate(open_price,close_price,date,fin2,in,out,day);
      


      fin1.close();
      fin2.close();
      return 0;
}



//split関数
vector<string> split(const string &str, char sep)
{
      vector<string> v;
      stringstream ss(str);
      string buffer;
      while( getline(ss, buffer, sep) ) {
            v.push_back(buffer);     
      }
      return v;     
}


void set_vector(vector<double>&oa,vector<double>&ca,vector<string>&b,ifstream &fin1)
{
//a : 修正後終値のvector , b : 日にち

      string line;
      string name;
      vector<string> tmp;
      double aa;

      while(getline(fin1,line)){
            tmp=split(line,'\t');
            aa=stof(tmp[2]);
            ca.push_back(aa);
            aa=stof(tmp[1]);
            oa.push_back(aa);
            b.push_back(tmp[0]);            
      }
      
}

void conf_co(ifstream &fin2,double &in,double &out)
{
      string line;
      vector<string>tmp;
      map<double,double>mp;
      while(getline(fin2,line)){
            tmp=split(line,'\t');
            mp[stof(tmp[1])]=stof(tmp[5]);
      }
      
      in = mp[in];
      out= mp[out];
      
}



void calculate(vector<double>&open_rate,vector<double>&target,vector<string>&date,ifstream &fin2,double &in,double &out,int &day)
{
      int y=0;
      double sum=0;
      double average=0;
      double deviation=0;
      vector<double> devi;
      double out_cri1=0;
      double out_cri2=0;
      double in_cri1=0;
      double in_cri2=0;
      

      //最初の計算日までデータ省略
      for(int i=0;i<day;i++){
            sum+=target[i];
            devi.push_back(target[i]);      
      }


      for(int i=day;i<target.size();i++){
            average = sum/(double)day;
            deviation =0;
            
            for(int j=0;j<day;j++){
                  deviation+=((devi[j]-average)*(devi[j]-average));
            }

            deviation=sqrt(deviation/(day-1));            
            
            //基準の計算
            //out_cri1= average - (out*deviation/sqrt(day));
            //out_cri2= average + (out*deviation/sqrt(day));
            //in_cri1= average - (in*deviation/sqrt(day));
            //in_cri2= average + (in*deviation/sqrt(day));

            out_cri1= average - (out*deviation);
            out_cri2= average + (out*deviation);
            in_cri1= average - (in*deviation);
            in_cri2= average + (in*deviation);
            
            //出力
            cout << date[i] <<"\t" << open_rate[i] <<"\t"<<target[i]<<"\t"<<out_cri1<<"\t"<<in_cri1<<"\t"<<in_cri2<<"\t"<<out_cri2<< endl;      

            //出力pre

            //out_cri1= average - (out*deviation);
            //out_cri2= average + (out*deviation);
            //in_cri1= average - (in*deviation);
            //in_cri2= average + (in*deviation);

            //cout << date[i] <<"\t" << open_rate[i] <<"\t"<<target[i]<<"\t"<<sum<<"\t"<<day<<"\t"<<average<<"\t"<<deviation<<"\t"<<out_cri1<<"\t"<<in_cri1<<"\t"<<in_cri2<<"\t"<<out_cri2<< endl;      
            
            //sum・vectorの入れ替え
            sum = sum - target[i-day] + target[i];
            devi.erase(devi.begin());
            devi.push_back(target[i]);
            
      }
}
