BEGIN{
OFS="\t"
sum01=0;
sum02=0;
sum03=0;
sum04=0;
sum05=0;
sum06=0;
sum07=0;
sum08=0;
sum09=0;
sum10=0;
sum11=0;
sum12=0;
sum13=0;
sum14=0;
sum15=0;
sum16=0;
sum17=0;
sum18=0;
sum19=0;
sum20=0;
sum21=0;
sum22=0;
sum23=0;
sum24=0;
sum25=0;
sum26=0;
sum27=0;
sum28=0;
sum29=0;
sum30=0;
sum31=0;
sum32=0;
sum33=0;
sum34=0;
sum35=0;
sum36=0;
sum37=0;
sum38=0;
sum39=0;
sum40=0;
sum41=0;
sum42=0;

}
{
sum01+=$2;
sum02+=$3;
sum03+=$4;
sum04+=$5;
sum05+=$6;
sum06+=$7;
sum07+=$8;
sum08+=$9;
sum09+=$10;
sum10+=$11;
sum11+=$12;
sum12+=$13;
sum13+=$14;
sum14+=$15;
sum15+=$16;
sum16+=$17;
sum17+=$18;
sum18+=$19;
sum19+=$20;
sum20+=$21;
sum21+=$22;
sum22+=$23;
sum23+=$24;
sum24+=$25;
sum25+=$26;
sum26+=$27;
sum27+=$28;
sum28+=$29;
sum29+=$30;
sum30+=$31;
sum31+=$32;
sum32+=$33;
sum33+=$34;
sum34+=$35;
sum35+=$36;
sum36+=$37;
sum37+=$38;
sum38+=$39;
sum39+=$40;
sum40+=$41;
sum41+=$42;
sum42+=$43;
}
END{
    print file,sum01,sum02,sum03,sum04,sum05,sum06,sum07,sum08,sum09,sum10,sum11,sum12,sum13,sum14,sum15,sum16,sum17,sum18,sum19,sum20,sum21,sum22,sum23,sum24,sum25,sum26,sum27,sum28,sum29,sum30,sum31,sum32,sum33,sum34,sum35,sum36,sum37,sum38,sum39,sum40,sum41,sum42
}

