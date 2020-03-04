#ifndef LDDecay_H_
#define LDDecay_H_

#include "HeadIN.h"
#include "FileDeal.h"
#include "Calculate.h"
#include "TriangleRR.h"
#include "SpineBlockRR.h"

using namespace std;

void  LDdecaySNP_help()
{
	cout <<""
		"\n"
		"\tUsage: LDBlockShow  -InVCF  <in.vcf.gz>  -OutPut <outPrefix>  -Region  chr1:10000:20000\n"
		"\n"
		"\t\t-InVCF        <str>     Input SNP VCF Format\n"
		"\t\t-OutPut       <str>     OutPut File of LD Blocks\n"
		"\n"
		"\t\t-Region       <str>     In One Region to show LD info svg Figture\n"
//		"\t\t-NoShow                 Only quickly calculate the Spine blcoks\n"
		//"\t\t-Bed           <str>     In muti Region.bed file to show LD\n"
		"\n"
		"\t\t-BlockType    <int>     method to detect Block [beta]\n"
		"\t\t                        1: Gabriel Method 2 Solid Spine of LD [1]\n"
		"\t\t\n"
		"\t\t-help                   Show more Parameters and help [hewm2008 v1.03]\n"
		"\n";
}

void More_HelpLDDecay()
{
	cout<<""
		"\n"
		"\t\t More Help document please see the Manual.pdf file\n"
		"\t\t Para [-i] is show for [-InVCF], Para [-o] is show for [-OutPut], Para [-r] is show for [-RegionOne],\n"
		"\n"
		"\n"
		"\t\t-SubPop       <str>     SubGroup Sample File List[ALLsample]\n"
		"\t\t-MAF          <float>   Min minor allele frequency filter [0.05]\n"
		"\t\t-Het          <float>   Max ratio of het allele filter [0.88]\n"
		"\t\t-Miss         <float>   Max ratio of miss allele filter [0.25]\n"
		"\n"
		"\t\t-BlockCutRR    <float>       'Strong LD' high confidence interval RR cutoff for Block[0.90]\n"
		"\t\t-TagSNPCutRR   <float>       'Strong LD' high confidence interval RR cutoff for TagSNP[0.98]\n"
		"\t\t-RatioRR       <float>        Ration of Gabriel Blocks for 'Strong LD' pairwise SNP [0.85]\n"
		"\n";
		"\n";
}

int LDdecay_help01(int argc, char **argv , In3str1v * paraFA04, Para_18 * para_18)
{
	if (argc <2 ) {LDdecaySNP_help();return 0;}
	for(int i = 1; i < argc ; i++)
	{
		if(argv[i][0] != '-')
		{
			cerr << "command option error! please check." << endl;
			return 0;
		}
		string flag=argv[i] ;
		flag=replace_all(flag,"-","");

		if (flag  == "InVCF" ||  flag  == "i")
		{
			if(i + 1 == argc) {LogLackArg(flag); return 0;}
			i++;
			paraFA04->InStr1=argv[i];
		}
		else if (flag  == "SubPop"  ||  flag  == "s")
		{
			if(i + 1 == argc) {LogLackArg(flag); return 0;}
			i++;
			paraFA04->SubPop=argv[i];
		}
		else if (flag  == "InGenotype")
		{
			if(i + 1 == argc) {LogLackArg(flag); return 0;}
			i++;
			paraFA04->InStr3=argv[i];
		}
		else if (flag  ==  "OutPut" ||  flag  == "o")
		{
			if(i + 1 == argc) {LogLackArg(flag); return 0;}
			i++;
			paraFA04->InStr2=argv[i];
		}
		else if (flag  == "Het" )
		{
			if(i + 1 == argc) {LogLackArg(flag); return 0;}
			i++;
			para_18->Het=atof(argv[i]);
		}
		else if (flag == "MAF")
		{
			if(i + 1== argc) {LogLackArg(flag);return 0;}
			i++;
			para_18->MAF=atof(argv[i]);
		}
		else if (flag == "BlockCutRR")
		{
			if(i + 1== argc) {LogLackArg(flag);return 0;}
			i++;
			paraFA04->MinRR=atof(argv[i]);
			if  ( (paraFA04->MinRR)>1  || (paraFA04->MinRR)<0 )
			{
				cerr <<"\t\t-BlockCutRR  should be (0,1]\n";
				return 0;
			}
		}
		else if (flag == "RatioRR")
		{
			if(i + 1== argc) {LogLackArg(flag);return 0;}
			i++;
			paraFA04->RatioRR=atof(argv[i]);
			if  ( (paraFA04->RatioRR)>1  || (paraFA04->RatioRR)<0 )
			{
				cerr <<"\t\t-RatioRR  should be (0,1]\n";
				return 0;
			}
		}

		else if (flag == "TagSNPCutRR")
		{
			if(i + 1== argc) {LogLackArg(flag);return 0;}
			i++;
			paraFA04->TagRR=atof(argv[i]);
			if  ( (paraFA04->TagRR)>1  || (paraFA04->TagRR)<0 )
			{
				cerr <<"\t\t-BlockCutRR  should be (0,1]\n";
				return 0;
			}
		}
		else if (flag == "Miss")
		{
			if(i + 1 == argc) {LogLackArg(flag);return 0;}
			i++;
			para_18->Miss=atof(argv[i]);
		}
		else if (flag == "Region" ||   flag == "r" )
		{
			if(i + 1 == argc) {LogLackArg(flag);return 0;}
			i++;
			paraFA04->Region=argv[i];
			if ((paraFA04->Region).find(':') ==string::npos)
			{
				cerr<<"\tPara [-Region] should be [chr:Start:End],such [chr1:5000:8000]"<<endl;
				return 0;
			}
		}		
		else if (flag == "Bed" )
		{
			if(i + 1 == argc) {LogLackArg(flag);return 0;}
			i++;
			paraFA04->Bed=argv[i];
		}		
		else if (flag == "BlockType")
		{
			if(i + 1 == argc) {LogLackArg(flag);return 0;}
			i++;
			paraFA04->TF=atoi(argv[i]);
		}
		else if (flag == "help"  ||  flag == "h")
		{
			More_HelpLDDecay();return 0;
		}
		else if (flag == "NoShow")
		{
			 paraFA04->NoShow=false;
		}	
		else
		{
			cerr << "UnKnow argument -"<<flag<<endl;
			return 0;
		}
	}

	if  ( (paraFA04->InStr2).empty() ||( (paraFA04->InStr1).empty() &&  (paraFA04->InStr3).empty())  )
	{
		cerr<< "lack argument for the must"<<endl;
		return 0;
	}

	if  ( ((paraFA04->Region).empty())  &&  (paraFA04->NoShow)  )
	{
		cerr<< "\t\tPara [-Region]  and  [-NoShow] should give out one\n";
		return 0;
	}

	if ( ((paraFA04->TF)==1) &&   ((para_18->MAF)<0.05) )
	{
		(para_18->MAF)=0.05;
		cerr<<"\t\t -MAF for [-BlockType 1] should >=0.05 ; so -MAF  default 0.05 Now"<<endl;
	}

	if ( (paraFA04->TF) >2  || (paraFA04->TF) <0 )
	{
		cerr<<"\t\t-BlockType   should be  [1/2]"<<endl;
		return 0;
	}


	string Stat=(paraFA04->InStr2);
	string ext =Stat.substr(Stat.rfind('.') ==string::npos ? Stat.length() : Stat.rfind('.') + 1);

	if ( ext == "gz" )
	{
		(paraFA04->InStr2)=(paraFA04->InStr2).substr(0,(paraFA04->InStr2).length()-3);
	}

	Stat=(paraFA04->InStr2);
	ext =Stat.substr(Stat.rfind('/') ==string::npos ? Stat.length() : Stat.rfind('/') + 1);

	if (ext != "svg")
	{
		ext =Stat.substr(Stat.rfind('.') ==string::npos ? Stat.length() : Stat.rfind('.') + 1);
		if (ext == "svg")
		{
			(paraFA04->InStr2)=(paraFA04->InStr2).substr(0,(paraFA04->InStr2).length()-4);
		}
	}

	Stat=argv[0];
	GetBinPath ( Stat  ,paraFA04->BinDir);

	return 1 ;
}


int main(int argc, char *argv[])
{
	In3str1v *paraFA04 = new In3str1v;
	Para_18 * para_18 = new Para_18 ;
	if ((LDdecay_help01(argc, argv, paraFA04, para_18)==0))
	{
		delete paraFA04 ;
		delete para_18 ;
		return 1;
	}

	(paraFA04->InInt)=(paraFA04->InInt)*1000;

	//	char buf[1024*1024]; 	setbuf(stdout, buf);
	//*///////////////////////////Test  Out File is OK ///////////////////////////////*//
	string Stat=(paraFA04->InStr2);
	Stat=(paraFA04->InStr2)+".blocks.gz";	
	ogzstream OUTTest ((Stat).c_str());
	if((!OUTTest.good()))
	{
		cerr << "open OUT File error: "<<Stat<<endl;
		delete para_18;
		delete paraFA04 ; return 1;
	}
	OUTTest.close();


	map <string,map <llong, vector <BaseType> > >  SNPList ;
	int Flag_for_pro=0;

	/////*               VCF   IN Deal //////////////////////*////
	if (!(paraFA04->InStr1).empty())
	{
		bool PhaseVCF=DeleVCFPhase(paraFA04->InStr1);
		if  ( PhaseVCF )
		{
			if ((paraFA04->SubPop).empty())
			{
				Read_VCF_IN_Phase( paraFA04, para_18 , SNPList, Flag_for_pro);
			}
			else
			{
				Read_SubPopVCF_IN_Phase( paraFA04, para_18 , SNPList, Flag_for_pro);
			}
		}
		else
		{
			if ((paraFA04->SubPop).empty())
			{
				Read_VCF_IN( paraFA04, para_18 , SNPList, Flag_for_pro);
			}
			else
			{
				Read_SubPopVCF_IN( paraFA04, para_18 , SNPList, Flag_for_pro);
			}
		}
	}

	/////*               Genotype IN Deal //////////////////////*////
	if (!(paraFA04->InStr3).empty())
	{
		if  ((paraFA04->SubPop).empty())
		{
			Read_Genotype_IN(paraFA04, para_18 ,SNPList,Flag_for_pro);
		}
		else
		{
			Read_SubPopGenotype_IN(paraFA04, para_18 ,  SNPList , Flag_for_pro );
		}
	}



	//*///////////////////////////PairWise Compare//////////////////////////////////*//

	if ((paraFA04->NoShow))
	{
		Region_Triangle_RR(paraFA04, para_18 ,SNPList,  Flag_for_pro);
	}
	else
	{
		SpineBlockRRFun(paraFA04, para_18 ,SNPList,  Flag_for_pro);
	}

	//	PairWiseComNewOUT_A(paraFA04, para_18 , SNPList, Flag_for_pro );

	delete para_18 ;
	delete paraFA04 ;
	return 0;

}


#endif // LDDecay_H_ //
///////// swimming in the sky and flying in the sea ////////////


