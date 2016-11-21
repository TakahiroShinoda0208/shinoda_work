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
a00=0;
a01=0;
a02=0;

}
{
      if($1=="損益"){total+=$2};
      if($1=="損益" && $2 > 0){plus0+=$2;plus1++}
      else if($1=="損益" && $2 == 0){equal0+=$2;equal1++}
      else if($1=="損益" && $2 < 0){minus0+=$2;minus1++};
      if($1=="損益" && max < $2){max=$2};
      if($1=="損益" && min > $2){min=$2};
      if($1=="利益"){a00+=$3};
      if($1=="損害"){a01+=$3};
      if($1=="同等"){a02+=$3};
      
}
END{
      print "total : "total,"trans : "(a00+a01+a02),"win : "a00/(a00+a01+a02)

}

