#全パラメータベンチマーク用ツール

#ファイル場所指定
PLA=~/Documents/Stock/investment/shinoda-work/fx/benchmark4


#各種ツール
Judge=${PLA}/before/Judge
Devi=${PLA}/Devi #移動平均乖離率の計算
Norm=${PLA}/before/Norm #各日にちごとに信頼区間を計算
Norm2=${PLA}/before/Norm2 #各日にちごとに信頼区間を計算(旧来の算出方法)
sep=${PLA}/awk_script/each_stats.awk #各通貨の結果を要約
Bench=${PLA}/awk_script/sep.collect.bench.awk #ベンチマーク用

#データファイル
Con=${PLA}/../Confidence/Confidence_coefficient #標本標準偏差データ

cd ./

# ファイルは720分割したファイルのみを引数として与える。あとは自動設定

file=$1
TSV=`basename $1`
FILE=${TSV/.tsv/}
ORIGINAL=${TSV/_720.tsv/}



#全パラメータforloop

for a in `seq 720 720 1440`
do
    file=${TSV/_720.tsv/_${a}.tsv}

    for b in `seq 5 1 20` 
    do
	#ここでtmpファイルを計算しちゃう
	CUT=`expr ${b} - 2`
	$Devi -f $file -dev $b >${FILE}_tmp.tsv
	

	for c in `seq 100 100 1000`
	do	    


	    for d in `seq 1 1 2`
	    do


		for e in `seq 50 1 99`
		do

		    for f in `seq 20 1 70`

		    do
			
		#ここでnumファイルを計算しちゃう
			if [ $d = 1 ]; then
			    $Norm -f ${FILE}_tmp.tsv -C $Con -day $c -in $f -out $e > ${FILE}_${b}.tsv
			else
			    $Norm2 -f ${FILE}_tmp.tsv -C $Con -day $c -in $f -out $e > ${FILE}_${b}.tsv
			fi
			
		#売買日判断
			$Judge -f0 $FILE.tsv -f1 ${FILE}_${b}.tsv -cut $CUT  > ${FILE}.result.tsv
			
		#statsをまとめた表を出力
			awk -f $sep ${FILE}.result.tsv > ${FILE}.stats.tsv
			awk -f $Bench downsample=$a num=$b day=$c norm=$d out=$e inn=$f ${FILE}.stats.tsv >> $FILE.bench
			
		#いらないファイルの削除
			rm ${FILE}.result.tsv
			rm ${FILE}.stats.tsv
			
		    done			    
		done		
	    done
	done
	
	rm ${FILE}_tmp.tsv
	
    done
done

