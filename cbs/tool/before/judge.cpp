#include <iostream>//標準データ入出力
#include <fstream>//ファイルの入出力
#include <vector>//vector(動的配列クラス)
#include <string>//string(文字列クラス)
#include <sstream>//文字列の入出力
#include <unordered_map>//unordered_map関数の導入
#include <map>//map関数の導入
#include <set>//set関数の導入
#include <stdlib.h>//絶対値を用いるための関数
#include <algorithm>// std::copy
#include<iomanip>//少数点以下表示
#include<time.h>
using namespace std;

//構造体宣言
struct Struct
{
      string way;
      string date;
      double devi;
      double value;
      string num;

      Struct(string a, string b,double c=0,double d=0,string e=0)
      {
            // デフォルト引数
            this->way = a;
            this->date = b;
            this->devi = c;
            this->value = d;
            this->num = e;
      }     
};
//関数プロトタイプ宣言
vector<string> split(const string &str, char sep);
void judge(ifstream &fin0,ifstream &fin1,int flagx,int cut,int highprice);


//main関数
int main(int argc,char*argv[])
{    
      ifstream fin0;
      ifstream fin1;
      int flag=0; //始値で売買するか、終値で売買するか
      int cut=0;//取引上限日数
      int highprice=100000;//取引最大価格
      
      for(int i=0;i<argc;i++){

            string ss=argv[i];
            if(ss=="-f0"){
                  fin0.open(argv[i+1]);     
            }
            
            if(ss=="-f1"){
                  fin1.open(argv[i+1]);     
            }

            if(ss=="-open"){
                  flag=1;     
            }

            if(ss=="-cut"){
                  cut=atof(argv[i+1]);     
            }

//最終的には、 信頼区間と銘柄が一覧になったファイルを取り込んで、それを読み込むような形式にしたい。
            if(ss=="-hprice"){
                  highprice=atof(argv[i+1]);
                  
            }
            
            
      }

      
//入力ファイルが存在しなかった時の出力
      if(!fin1 || argc<=5){
            cout << endl;
            cout <<"\t"<<"J  U  D  G  E"<<"\n\n\n";
            
            cout <<"version 1.4" <<"\n";
            cout <<"updated 2016/11/20"<<"\t"<<"TAKAHIRO SHINODA"<<"\n\n\n";
            cout << "β version. Test tool for FX data." <<"\n";
            cout << "change int to double for map function." <<"\n\n\n";
            cout <<"e.g."<<"\n\n";
            cout <<"FX -f0 aiueo.tsv -cut 5  > hoge.tsv"<<"\n";
            cout << "-----------------------------------------------------------------------------------------" << endl;
            cout << "-f0"<<"\t\t"<<" : input tsv file format of stock data"<< endl;
            cout << "-f1"<<"\t\t"<<" : input tsv file format of diviation rate"<< endl;
            cout << "-cut"<<"\t\t"<<" : the maximum limitation of date to deal"<<"\t"<<"[default none]"<< endl;
            cout << "-open"<<"\t\t"<<" : judge by using opening price "<<"\t\t"<<"[default none(close)]"<< endl;
            cout << "-hprice"<<"\t\t"<<" : the maximum price of dealing"<<"\t\t\t"<<"[default 100000]"<< endl;
            cout <<"\t\t"<<"   in the above example, A and D is Confidence interval(lower and upper)"<< endl;
            cout <<"\t\t"<<"   in the above example, B and C is Stable interval(lower and upper)"<< endl;
            cout << "-----------------------------------------------------------------------------------------" <<"\n\n\n";

            return 1;
            
      }
      

      judge(fin0,fin1,flag,cut,highprice);      
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


void judge(ifstream &fin0,ifstream &fin1,int flagx,int cut,int highprice)
{
      //使用するflag及び変数
      string line;
      double aa=0;
      int flag=0;
      int flag2=0;
      int flag3=0;
      int z=0;
      map<string,double> mp;
      vector<string> tmp;
      vector<Struct> box;

      //信頼区間・安定区間
      double x1=0; //信頼区間min
      double x2=0; //安定区間min
      double x3=0; //安定区間max
      double x4=0; //信頼区間max


      while(getline(fin0,line)){
            tmp= split(line,'\t');            
            switch(flagx){
            case 0: //closing priceで売買する場合
                  mp[tmp[0]]=stod(tmp[6]);             
                  break;
            case 1: //opening priceで売買する場合
                  mp[tmp[0]]=stod(tmp[1]);            
                  break;
            default:
                  break;
            }

      }

      while(getline(fin1,line)){

            tmp = split(line,'\t');

            //opening priceかcloseing priceの判断

            switch(flagx){
            case 0: //closing priceで売買する場合
                  aa = stod(tmp[2]);
                  break;
            case 1: //opening priceで売買する場合
                  aa = stod(tmp[1]);
                  break;
            default:
                  break;
            }

            z++;
            //取引最大日数で取引打ち切り
            if(flag3==1){
                 if(z==cut){
                       if(box[0].way=="sell"){
                              flag2=1;
                        }else{
                              flag2=2;
                        } 
                  }
            }            

            //信頼区間の代入
            x1=stod(tmp[3]);
            x2=stod(tmp[3]);
            x3=stod(tmp[3]);
            x4=stod(tmp[3]);



            //移動平均乖離率で外れ値を記録した日を入り日、正常値に戻った日を出日として売買を行う。
            //highprice : 入り日の基準に株価が100円以下であるかを追加する。(30/10/2016)

            switch(flag){
            case 0:
                  if(aa >= x4 && mp[tmp[0]]<=highprice){
                        flag=1;
                        Struct a0("sell",tmp[0],aa,mp[tmp[0]],tmp[2]);
                        box.push_back(a0);
                        flag3=1;
                        z=0;
                  }
                  if(aa <= x1 && mp[tmp[0]]<=highprice){
                        flag=2;
                        Struct a0("buy",tmp[0],aa,mp[tmp[0]],tmp[2]);
                        box.push_back(a0);
                        flag3=1;
                        z=0;
                  }
                  break;
            case 1:
                  if(aa<=x3 ||flag2==1){
                        flag=0;
                        flag2=0;
                        flag3=0;
                        Struct a0("buy",tmp[0],aa,mp[tmp[0]],tmp[2]);
                        box.push_back(a0);
                        
                        cout << box[0].way << "\t" << box[0].date <<"\t"<< box[0].devi <<"\t"<<  box[0].value <<"\t";
                        cout << box[1].way << "\t" << box[1].date <<"\t"<< box[1].devi <<"\t"<<  box[1].value <<"\t";
                        cout <<"損益"<<"\t"<<( box[0].value - box[1].value)<<"\t"<<"日数"<<"\t"<<z<<"\t"<<box[0].num<< endl;

                        box.clear(); 
                        z=0;
                        
                  }
                  break;
                  
            case 2:     
                  if(aa>=x2 || flag2==2){
                        flag=0;
                        flag2=0;
                        flag3=0;
                        Struct a0("sell",tmp[0],aa,mp[tmp[0]],tmp[2]);
                        box.push_back(a0);

                              cout << box[0].way << "\t" << box[0].date <<"\t"<< box[0].devi <<"\t"<<  box[0].value <<"\t";
                              cout << box[1].way << "\t" << box[1].date <<"\t"<< box[1].devi <<"\t"<<  box[1].value <<"\t";
                              cout <<"損益"<<"\t"<<( box[1].value - box[0].value)<<"\t"<<"日数"<<"\t"<<z<<"\t"<<box[0].num<< endl;

                        box.clear();
                        z=0;
                  }
                  break;
                  
            default:
                  cout <<"フラッグが正常に機能していません。"<<endl;
                  break;
            }
      }      
}
