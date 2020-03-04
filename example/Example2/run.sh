#!/bin/sh
#$ -S /bin/sh
#Version1.0	hewm@genomics.org.cn	2020-02-07
echo Start Time : 
date
#../../bin/ShowLDSVG	-InPreFix	../Example1/out	-OutPut	out.svg	-InGWAS	gwas.pvlue	
../../bin/ShowLDSVG	-InPreFix	../Example1/out	-OutPut	out.svg	-InGWAS	gwas.pvlue -Cutline  7	
echo End Time : 
date
