BEGIN{
OFS="\t"
total=0;
a00=0;
a01=0;
a02=0;

}
{
      if($1=="損益"){total+=$2};
      if($1=="利益"){a00+=$3};
      if($1=="損害"){a01+=$3};
      if($1=="同等"){a02+=$3};
      
}
END{
      print downsample,num,day,norm,out,inn,total,total/(a00+a01+a02),a00/(a00+a01+a02)
}

