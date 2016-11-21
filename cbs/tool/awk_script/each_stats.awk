BEGIN{
OFS="\t"
total=0;
plus0=0;
plus1=0;
equal0=0;
equal1=0;
minus0=0;
minus1=0;
max=-100;
min=100;
}
{
      total+=$10;
      if($10 > 0){plus0+=$10;plus1++}
      else if($10 == 0){equal0+=$10;equal1++}
      else if($10 < 0){minus0+=$10;minus1++};
      if(max < $10){max=$10};
      if(min > $10){min=$10};
      
}
END{
      print "損益\t",total
      print "最大値\t",max
      print "最小値\t",min
      print "利益\t",plus0,"\t",plus1
      print "損害\t",minus0,"\t",minus1
      print "同等\t",equal0,"\t",equal1
}

