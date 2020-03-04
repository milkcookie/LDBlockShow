
# LDBlockShow
<b>LDBlockShow: a fast and effective tool for Show Region Linkage disequilibrium heatmap Figure analysis based on variant call format files</b>


###  1) Install
------------

<b> [Download](https://github.com/BGI-shenzhen/LDBlockShow/archive/v1.03.tar.gz) </b>

</br>
Method1 For <b>linux/Unix</b> and <b> macOS </b>
<pre>
        git clone https://github.com/BGI-shenzhen/LDBlockShow.git
        chmod 755 configure; ./configure;
        make;
        mv LDBlockShow  bin/;    #     [rm *.o]
</pre>

**Note:** If fail to link,try to <b>re-install</b> the libraries [**_zlib_**](https://zlib.net/)


Method2 For <b>linux/Unix</b> and <b> macOS </b>
<pre>
        tar -zxvf  LDBlockShowXXX.tar.gz
        cd LDBlockShowXXX;
        cd src;
        make ; make clean                            # or [sh make.sh]
        ../bin/LDBlockShow
</pre>
**Note:** If fail to link,try to <b>re-install</b> the libraries [**_zlib_**](https://zlib.net/)


###  2) Introduction
------------
Linkage disequilibrium (LD) Blocks [1] is the most important and most common analysis in the population resequencing[2]. Special in the self-pollinated crops, the LD Blocks for Special region (seletion region,gwas region) is show more detailed information to pick the Specified genes.
Compared with the other two softwares, the results of LDBlocksShow are the same and use less computing resources (DataSet at 1000 sample with 1000 sites). For ordinary users, LDBlocksShow is more friendly and simple to use

|     Software     |   Mem (G)   |  Cpu Time (h)   |       Result       |
|:----------------:|:------------|:----------------|:-------------------|
| Haploview4.2.jar |      95     |       36        |    HeatMap+Block   |
| R:Ldheatmap 0.99 |      1      |       48        |       HeatMap      |
| LDBlockShow 1.03 |      1      |       1         | HeatMap+Block+GWAS |


* <b> Parameter description</b>
```php
 ./bin/LDBlockShow

	Usage: LDBlockShow  -InVCF  <in.vcf.gz>  -OutPut <outPrefix>  -Region  chr1:10000:20000

		-InVCF        <str>     Input SNP VCF Format
		-OutPut       <str>     OutPut File of LD Blocks

		-Region       <str>     In One Region to show LD info svg Figture

		-BlockType    <int>     method to detect Block [beta]
		                        1: Gabriel Method 2 Solid Spine of LD [1]

		-help                   Show more Parameters and help [hewm2008 v1.03]

```

###  3) Example
------------

See more detailed Usage in the <b>[Chinese Documentation](https://github.com/BGI-shenzhen/LDBlockShow/blob/master/LDBlocksShow_Manual.pdf)</b>
and see the example and  Manual.pdf for more detailed


* Example 1)  show Figure with Defaut LD Blocks

<pre>
../../bin/LDBlockShow   -InVCF Test.vcf.gz   -OutPut  out   -Region  Ghir_D11:24100000:24200000
</pre>
Example Result Show
![out.png](https://github.com/BGI-shenzhen/LDBlockShow/blob/master/example/Example1/out.png)


* Example 2)  show Figure with Defaut LD Blocks   + GWAS
```
#../../bin/ShowLDSVG	-InPreFix	../Example1/out	-OutPut	out.svg	-InGWAS	gwas.pvlue
../../bin/ShowLDSVG	-InPreFix	../Example1/out	-OutPut	out.svg	-InGWAS	gwas.pvlue -Cutline  7
```
Example Result Show
![out.png](https://github.com/BGI-shenzhen/LDBlockShow/blob/master/example/Example2/out.png)


* Example 3) show Figure with Plinks LD Blocks
```
./plink-1.9/plink	--vcf	../Example1/Test.vcf.gz	--geno	0.1	-maf 0.01 --blocks  no-pheno-req --out	plink	--allow-extra-chr
cp  ../Example1/out.* ./;  
rm  out.blocks.gz  ; mv    plink.blocks.det   out.blocks ; gzip  out.blocks ; rm  plink.*
../../bin/ShowLDSVG  -InPreFix   ./out   -OutPut out.svg 
```
Example Result Show will be the same with Example 1)

* Exampl 4) show Figure with Plinks LD Blocks  + GWAS
```
#../../bin/ShowLDSVG	-InPreFix	../Example3/out	-OutPut	out.svg	-InGWAS	gwas.pvlue
../../bin/ShowLDSVG	-InPreFix	../Example3/out	-OutPut	out.svg	-InGWAS	gwas.pvlue -Cutline  7
```
Example Result Show will be the same with Example 2)




###  4) Results
------------
A LD heatMap images which I draw before.

![out.png](https://github.com/BGI-shenzhen/LDBlockShow/blob/master/example/Fig/out.png)

###  5) Discussing
------------
- [:email:](https://github.com/BGI-shenzhen/LDBlockShow) hewm2008@gmail.com / hewm2008@qq.com
- join the<b><i> QQ Group : 125293663</b></i>

######################swimming in the sky and flying in the sea #############################
