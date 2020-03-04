#!/bin/sh
#$ -S /bin/sh
echo Start Time : 
date
echo g++	-g -O2 LDBlockShow.cpp		-lm -lc -lz  -L/usr/lib/ -L./include/zlib/	-o	../bin/LDBlockShow
g++	-g -O2 LDBlockShow.cpp		-lm -lc -lz  -L/usr/lib/ -L./include/zlib/	-o	../bin/LDBlockShow
echo done see the [ ../bin/LDBlockShow  ]
echo End Time : 
date
