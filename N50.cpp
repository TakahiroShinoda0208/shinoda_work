// fastaファイル
//genomesize N50 N50(下限あり)

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
void genome(vector<string>&b,vector<string>&a,ifstream &fin1);
double N50(vector<string>&a,double &sum,double &max,int &maxn,double &min);
double Ncount(vector<string>&a,double&gc);

//main関数
int main(int argc,char*argv[1])
{    
      //引数が足らない時のError
      if(argc<2){ cout << "please input arguement" <<endl; return 1;}      
      ifstream fin1(argv[1]);
      if(!fin1){ cout << "ファイル1を読み込めませんでした。\n";return 1;}

      //refgenomeの格納
      vector<string>a; //配列
      vector<string>b; //配列のID
      genome(b,a,fin1);
      fin1.close();


      int maxn =0;
      double sum=0;
      double max=0;
      double min=0;
      double gc=0;
      double h=N50(a,sum,max,maxn,min);
      double hh=Ncount(a,gc);
      double hhh=hh/sum*100;
      double GC=gc/sum*100;
      string maxname=b[maxn].erase(0,1);
      

      cout << "scaffold : " << a.size()<<endl;
      cout <<"N50 : "<< h << endl;
      cout <<"Average : "<< sum/a.size() << endl;
      cout <<"max length : "<< (long long int)max <<endl;
      cout <<"max name : "<<maxname<<endl;
      cout <<"min length : "<< (long long int)min <<endl;
      cout <<"totallength(include N) : "<< (long long int)sum << endl;
      cout <<"totallength(except N) : " << (long long int)(sum-hh) <<endl;
      cout <<"Npercent : "<<setprecision(5) <<hhh << endl;
      cout <<"GCcontent : "<<setprecision(5) <<GC << endl;

      cout << "end\n";
      return 0;
}

//genome配列切り出し関数
void genome(vector<string>&b,vector<string>&a,ifstream &fin1)
{
      string line;
      string h;
      double z=0;
      
      //最初の一行だけ先に配列に格納
      getline(fin1,line);
      b.push_back(line);  
      //残りのデータを格納していく
      while(getline(fin1,line)){
            if(line.find('>') != string::npos){
                  b.push_back(line);
                  z=1;
            }
            else{
                  if(z==1){
                        a.push_back(h); h =""; z =0; h += line;
                  }
                  else{
                        h += line;
                  }
            }
      }
      //最後に残っているhをaに格納する。
      a.push_back(h);
}


double N50(vector<string>&a,double &sum,double &max,int &maxn,double &min)
{
      vector<double>aint;//配列の長さ
      vector<double>defa;
      
      double sum2=0;
      double n=0;
      double hsum =0;
      
      for(int i=0;i<a.size();i++){
            //ファイルに出力処理
            //cout <<b[i]<<'\n'<< a[i].size() << endl;
            aint.push_back((double)a[i].size());
            sum+=(double)a[i].size(); 
      }
      defa = aint;  
      sort(aint.begin(),aint.end(),greater<double>());
      hsum = sum/2;
      max = aint[0];
      min = aint[aint.size()-1];
      
      for(int i=0;i<aint.size();i++){
            //cout <<aint[i]<<endl;
            sum2+=aint[i];
            if(hsum<sum2){
                  n=aint[i];
                  //cout <<"N50 : "<< n <<endl;
                  break;
            }
      }
      
      for(int i=0;i<defa.size();i++){
            if(max==defa[i]){
                  maxn = i;
                  break;
            }
      }

      return n;
      
}


double Ncount(vector<string>&a,double&gc)
{
      double aa=0;
      
      for(int i=0;i<a.size();i++){            
            for(int j=0;j<a[i].size();j++){
                  if(a[i].at(j)=='N'||a[i].at(j)=='n'){
                        aa++;
                  }else if(a[i].at(j)=='G'||a[i].at(j)=='C'){
                        gc++;           
                  }
                  
            }
      }
      return aa;
      
}
