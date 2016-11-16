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

void sum_map(ifstream &fin1,string &name);

//main関数
int main(int argc,char*argv[1])
{    
      ifstream fin1;
      ifstream fin2;
      string name;

      for(int i=0;i<argc;i++){

            string ss=argv[i];
            if(ss=="-f1"){
	      fin1.open(argv[i+1]);     
	      name=argv[i+1];
            }
	    
      }
      
//入力ファイルが存在しなかった時の出力
      if(!fin1 || argc<=2){
            cout << endl;
            cout <<"\t"<<"C O N V E R T      M G S 2"<<"\n\n\n";
            
            cout <<"version 1.0" <<"\n";
            cout <<"updated 2016/11/16"<<"\t"<<"TAKAHIRO SHINODA"<<"\n\n\n";
            cout <<"convert gene matrix to MGS matrix"<<"\n\n\n";
            
            cout <<"ex."<<"\n\n";
            cout <<"Norm -f1 a.txt -f2 b.txt > hoge.tsv"<<"\n";
            cout << "-----------------------------------------------------------------------------------------" << endl;
            cout << "-f1"<<"\t\t"<<" : Input tsvfile"<< endl;
            cout << "-----------------------------------------------------------------------------------------" <<"\n\n\n";
	    
            return 1;
            
      }
      

      //input to map function
      sum_map(fin1,name);
      

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


void sum_map(ifstream &fin1,string &name)
{

      string line;
      vector<string> tmp;
      map<int,long double> hash;
      int count=0;

      getline(fin1,line); //一行目だけ特別処理
      tmp=split(line,'\t');
      count=(int)tmp.size();

      for(int i=1;i<tmp.size();i++){
	hash[i]=0;
      }
      for(int i=1;i<tmp.size();i++){
	hash[i]+=stod(tmp[i]);
      }
      

      while(getline(fin1,line)){
	tmp=split(line,'\t');
	for(int i=1;i<tmp.size();i++){
	  hash[i]=stod(tmp[i]);
	}
      }

      
      for(int i=1;i<count;i++){
	
	if(i!=(count-1)){
	  if(i==1){
	    cout << name <<"\t";
	  }	  
	    cout << hash[i] <<"\t";
	}
	else{
	  cout << hash[i] << endl;
	}
	
      }
      
}

