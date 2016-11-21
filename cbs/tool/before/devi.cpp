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
using namespace std;

//関数プロトタイプ宣言
vector<string> split(const string &str, char sep);
void set_vector(vector<double> &oa,vector<double> &ca,vector<string> &b,ifstream &fin1);
void deviation_rate(vector<double> &oa,vector<double> &ca,vector<string>&b,int &x);
void RSI(vector<double>&a,vector<string>&b,int &x);
void PHY(vector<double>&a,vector<string>&b,int &x);

//main関数
int main(int argc,char*argv[1])
{    
      ifstream fin1;
      ofstream fon1;
      ofstream fon2;
      ofstream fon3;
      
      int dev=7; //default 移動平均乖離率
      int rsi=7; //RSI
      int phy=7; //Phycological line
      
      int flag=0;
      

      for(int i=0;i<argc;i++){

            string ss=argv[i];
            if(ss=="-f"){
                  fin1.open(argv[i+1]);     
            }
            if(ss=="-dev"){
                  dev=atoi(argv[i+1]);     
                  flag=1;
            }
//            if(ss=="-rsi"){
//                  rsi=atoi(argv[i+1]);     
//                  flag=2;
//            }
//            if(ss=="-phy"){
//                  phy=atoi(argv[i+1]);     
//                  flag=3;
//            }
            
      }
      
//入力ファイルが存在しなかった時の出力
      if(!fin1 || argc<=2){
            cout << endl;
            cout <<"\t"<<"D  E  V  I  A  T  I  O  N"<<"\n\n\n";
            
            cout <<"version 1.3" <<"\n";
            cout <<"updated 2016/11/13"<<"\t"<<"TAKAHIRO SHINODA"<<"\n\n\n";
            cout <<"DEV output BOTH opening deviation rate and closing deviation rate"<<"\n\n\n";
            
            cout <<"ex."<<"\n\n";
            cout <<"STOCK -f aiueo.tsv -dev 5 > hoge.tsv"<<"\n";
            cout << "-----------------------------------------------------------------------------------------" << endl;
            cout << "-f"<<"\t\t"<<" : Input tsvfile"<< endl;
            cout << "-dev"<<"\t\t"<<" : deviation rate"<<"\t\t\t\t"<<"[default 7]"<< endl;
            //cout << "-rsi"<<"\t\t"<<" : RSI(relative strength index)"<<"\t\t\t"<<"[default 7]"<< endl;
            //cout << "-phy"<<"\t\t"<<" : Phycological line"<<"\t\t\t\t"<<"[default 7]"<< endl;
            cout << "-----------------------------------------------------------------------------------------" <<"\n\n\n";

            return 1;
            
      }
      
      vector<double> close_price; //配列
      vector<double> open_price; //配列
      vector<string> date; //配列

      set_vector(open_price,close_price,date,fin1);
      
      switch(flag){
      case 1:
            deviation_rate(open_price,close_price,date,dev);
            break;
            
      case 2:
            //RSI(close_price,date,rsi);
            break;
            
      case 3:
            //PHY(close_price,date,phy);
            break;
      default :
            cout <<"flagが作動していません。終了します。"<<endl;
            break;
      }

      fin1.close();
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
            tmp= split(line,'\t');
            aa=stof(tmp[6]);
            ca.push_back(aa);
            aa=stof(tmp[1]);
            oa.push_back(aa);
            b.push_back(tmp[0]);            
      }
      
}

void deviation_rate(vector<double>&oa,vector<double>&ca,vector<string>&b,int &x)
{
      int y=0;
      double sum=0;
      double average=0;
      double close_rate =0;
      double open_rate =0;
      
      for(int i=oa.size()-1;i>=0;i--){
            y++;
            if(y>x){
                  average = sum/x;
                  close_rate = (ca[i]/average)-1;
                  open_rate = (oa[i]/average)-1;
                  cout << b[i] <<"\t" << open_rate <<"\t"<<close_rate<< endl;
                  sum = sum - oa[i+x] + oa[i];
            }
            else{
                  sum+= oa[i];
            }
            
      }
}

//FXで使うのであれば、for文の+.-部分を全て直す必要あり
void RSI(vector<double>&a,vector<string>&b,int &x)
{
      int y=0;
      double sum=0;
      double sum1=0;
      double rate =0;
      double p=0;
      vector<double> aa;
      
      for(int i=0;i<a.size()-1;i++){
            p=a[i+1]-a[i];
            aa.push_back(p);
      }
      
      for(int i=aa.size()-1;i>=0;i--){
            y++;
                  
            if(y>=x){
                  if(aa[i]>0){
                        sum+=aa[i];
                        sum1+=aa[i];
                  }
                  else if(aa[i]<0){
                        sum+=-aa[i];
                  }
                  else{
                  
                  }
                  

                  rate=sum1/sum*100;
                  cout << b[i] << "\t" << rate <<"\t"<<0<<endl;
                  //cout << b[i] << "\t" << rate <<endl;
                  p=aa[i+x-1];

                  if(p>0){
                        sum-=p;
                        sum1-=p;
                  }     
                  else if(p<0){
                        sum+=p;
                  }
                  else{
                  
                  }
                  
                  
            }
            else{
                  if(aa[i]>=0){
                        sum+=aa[i];
                        sum1+=aa[i];
                  } 
                  else{
                        sum+=-aa[i];
                  }                  
            }
            
            
      }
}

void PHY(vector<double>&a,vector<string>&b,int &x)
{
      int y=0;
      double sum=0;
      double sum1=0;
      double rate =0;
      double p=0;
      vector<double> aa;
      
      for(int i=1;i<=a.size()-1;i++){
            p=a[i]-a[i+1];
            aa.push_back(p);
      }
      
      for(int i=aa.size()-1;i>=0;i--){
            y++;
                  
            if(y>=x){
                  if(aa[i]>0){
                        sum1+=1;
                  }
                  else if(aa[i]==0){
                        sum1+=0.5;
                  }
                  
                  rate=sum1/x*100;
                  cout << b[i] << "\t" << rate <<"\t"<<0<<endl;
                  //cout << b[i] << "\t" << rate << endl;
                  p=aa[i+x-1];

                  if(p>0){
                        sum1-=1;
                  }     
                  else if(p==0){
                        sum1-=0.5;
                  }

            }else{
                  
                  if(aa[i]>0){
                        sum1+=1;
                  }
                  
                  else if(aa[i]==0){
                        sum1+=0.5;
                        
                  }
                  
                  
            }
      }
}
