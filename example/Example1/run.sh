#!/bin/sh
#$ -S /bin/sh
#Version1.0	hewm@genomics.cn	2020-01-10
echo Start Time : 
date
../../bin/LDBlockShow   -InVCF Test.vcf.gz   -OutPut  out   -Region  Ghir_D11:24100000:24200000
echo End Time : 
date
