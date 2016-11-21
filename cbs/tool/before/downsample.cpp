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

//main関数
int main(int argc,char*argv[])
{    
      ifstream fin0;
      int freq=0;
      
      for(int i=0;i<argc;i++){
            string ss=argv[i];
            
            if(ss=="-f"){            
                  fin0.open(argv[i+1]);
            }
            if(ss=="-l"){            
                  freq=atof(argv[i+1]);
            }
            
      }
      


//入力ファイルが存在しなかった時の出力
      if(!fin0 || argc<=1){
            cout << endl;
            cout <<"\t"<<"DOWNSAMPLING"<<"\n\n\n";
            
            cout <<"version 1.0" <<"\n";
            cout <<"updated 2016/11/05"<<"\t"<<"TAKAHIRO SHINODA"<<"\n\n\n";
            cout << "β version." <<"\n";

            cout <<"e.g."<<"\n\n";
            cout <<"downsample -f input_file -l 1000 > hoge.tsv"<<"\n";
            cout << "-----------------------------------------------------------------------------------------" << endl;
            cout << "-f"<<"\t\t"<<" : input file which you want to downsample."<< endl;
            cout << "-l"<<"\t\t"<<" : interval for skipping the line."<< endl;
            cout << "-----------------------------------------------------------------------------------------" <<"\n\n\n";

            return 1;
            
      }
      
      string line;
      int z=0;

      getline(fin0,line);
      cout <<line<<endl;

      
      while(getline(fin0,line)){
            z++;
            if(z==freq){
                  cout << line << endl;
                  z=0;
            }
      }
      


      
      return 0;
      
}
