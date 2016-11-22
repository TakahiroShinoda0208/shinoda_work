#!/bin/sh

#ファイルの場所
PLA=/home/local/27636/stud013/Project/shinoda_work/cbs/tool

#各種ツール

Judge=${PLA}/before/Judge 
Devi=${PLA}/Devi #移動平均乖離率の計算
Norm=${PLA}/before/Norm #各日にちごとに信頼区間を計算
Norm2=${PLA}/before/Norm2 #各日にちごとに信頼区間を計算(旧来の算出方法)
sep=${PLA}/awk_script/each_stats.awk #各通貨の結果を要約

#データファイル
Con=${PLA}/../Confidence/Confidence_coefficient #標本標準偏差データ


#変数指定
price="close"
OUT=70
INN=40
DOWNSAMPLE=2880
DAY=800

#変数を定義
NUM=7
IN=`basename $1`
FILE=${IN/.tsv/}
ORIGINAL=${IN/_${DOWNSAMPLE}.tsv/}
TSV=${FILE}.tsv

#aliasを貼る

#ln -s $1 ./


#乖離率を計算

$Devi -f $TSV -dev $NUM >${FILE}_tmp.tsv

#移動平均信頼区間を計算

$Norm -f ${FILE}_tmp.tsv -C $Con -day $DAY -in $INN -out $OUT >${FILE}_${NUM}.tsv
#$Norm2 -f ${FILE}_tmp.tsv -C $Con -day $DAY -in $INN -out $OUT >${FILE}_${NUM}.tsv
#rm ${FILE}_tmp.tsv


#売買する日を判定する(売買 日付 判定値 金額)

#$Judge -f0 $FILE.tsv -f1 ${FILE}_${NUM}.tsv -cut 5 -x $A $B $C $D > ${FILE}.result.tsv


#statsをまとめた表を出力
#awk -f $sep ${FILE}.result.tsv > ${FILE}.stats.tsv

