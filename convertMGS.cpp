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

void insert_map(map<string,string>&hash,ifstream &fin1);
void pick_up_gene(ifstream &fin2,map<string,string>&hash);



//main関数
int main(int argc,char*argv[1])
{    
      ifstream fin1;
      ifstream fin2;
      

      for(int i=0;i<argc;i++){

            string ss=argv[i];
            if(ss=="-f1"){
                  fin1.open(argv[i+1]);     
            }
            if(ss=="-f2"){
                  fin2.open(argv[i+1]);     
            }
	   
      }
      
//入力ファイルが存在しなかった時の出力
      if(!fin1 || argc<=2){
            cout << endl;
            cout <<"\t"<<"C O N V E R T      M G S"<<"\n\n\n";
            
            cout <<"version 1.0" <<"\n";
            cout <<"updated 2016/11/16"<<"\t"<<"TAKAHIRO SHINODA"<<"\n\n\n";
            cout <<"convert gene matrix to MGS matrix"<<"\n\n\n";
            
            cout <<"ex."<<"\n\n";
            cout <<"Norm -f1 a.txt -f2 b.txt > hoge.tsv"<<"\n";
            cout << "-----------------------------------------------------------------------------------------" << endl;
            cout << "-f1"<<"\t\t"<<" : Input tsvfile"<< endl;
            cout << "-f2"<<"\t\t"<<" : Input tsvfile"<< endl;
            cout << "-----------------------------------------------------------------------------------------" <<"\n\n\n";

            return 1;
            
      }
      
      map<string,string> hash; //配列
      vector<string> date; //配列
      
      //input to map function
      insert_map(hash,fin1);

      //pick up gene from each MGS file
      pick_up_gene(fin2,hash);


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


void insert_map(map<string,string>&hash,ifstream &fin1)
{

      string line;
      vector<string> tmp;

      getline(fin1,line); //一行目読み飛ばし

      while(getline(fin1,line)){
            tmp=split(line,'\t');
            hash[tmp[0]]=line;
      }
      
}

void pick_up_gene(ifstream &fin2,map<string,string>&hash)
{
      string line;
      vector<string>tmp;
      ofstream fin0;
      
      getline(fin2,line);

       while(getline(fin2,line)){
            tmp=split(line,'\t');
	    fin0.open(tmp[0]);
	      for(int i=1;i<tmp.size();i++){	      
		fin0 << hash[tmp[i]] << endl;
	      }
	    fin0.close();
      }
       
}

