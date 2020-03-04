#ifndef EHH_H_
#define EHH_H_

using namespace std;


string int2str( unsigned short int val )
{
	ostringstream out;
	out<<val;
	return out.str();
}


int Region_Triangle_RR(In3str1v * paraFA04, Para_18 * para_18 , map <string,map <llong, vector <BaseType> > >  & SNPList, int & Flag_for_pro)
{

	string StatRR  =(paraFA04->InStr2)+".TriangleRR.gz";
	string StatSite=(paraFA04->InStr2)+".site.gz";
	string StatBlocks=(paraFA04->InStr2)+".blocks.gz";
	ogzstream OUTAA ((StatRR).c_str());
	if(!OUTAA.good())
	{
		cerr << "open OUT File error: "<<StatRR<<endl;
		return 0;
	}

	ogzstream OUTBB ((StatSite).c_str());
	if(!OUTBB.good())
	{
		cerr << "open OUT File error: "<<StatSite<<endl;
		return 0;
	}

	ogzstream OUTCC ((StatBlocks).c_str());
	if(!OUTCC.good())
	{
		cerr << "open OUT File error: "<<StatBlocks<<endl;
		return 0;
	}

	vector<string> inf;
	split((paraFA04->Region),inf,":");
	llong StartSite=atoi(inf[1].c_str());
	llong EndSite=atoi(inf[2].c_str());

	string chrName=inf[0];
	unsigned short int ValueE=2;
	map <string,map <llong, vector <BaseType> > >  :: iterator itSNP=SNPList.find(chrName);
	if (itSNP == SNPList.end())
	{
		cerr<<"\t\tInPut Para -Region  chromosome ["<<chrName<<"]  can't be found in the SNP dataset\n";		
		return 0;
	}  

	llong BeginRegion=StartSite;   if (BeginRegion<0) { BeginRegion=0;}	
	llong EndRegion=EndSite;

	map<llong, vector <BaseType> >  :: iterator key2=(itSNP->second).begin(); ;

	map <llong, vector <BaseType> >  NewSNPList ;

	int count =0 ;
	int TotalSNP=0;

	statementVar Var;
	Var.Asize= (key2->second).size();

	for(  ; key2!=(itSNP->second).end(); key2++)
	{
		if ( ( key2->first )<  BeginRegion)
		{
			continue;
		}
		if  ( ( key2->first )> EndRegion)
		{
			break;
		}
		TotalSNP++;
		NewSNPList.insert(map <llong, vector <BaseType> >  :: value_type(key2->first,(key2->second))) ;
	}

	cout<<"##Start Region Cal...\t :"<<chrName<<" "<<BeginRegion<<" "<<EndRegion<<"; In This Region TotalSNP Number is "<<TotalSNP<<endl;
	if (TotalSNP < 3)
	{
		cerr<<"LDBlocks should be with Region SNP Number  > 3 \n";
		return 0;
	}
	else if ( TotalSNP > 168888)
	{
		cerr<<"Warning: LDBlocks Region SNP Number too much,you may use the small region or more stringent conditions to filter the SNP\n";
	}

	//TotalSNP++;
	double **ArrRR = new double *[TotalSNP];
	llong *ArrSite = new llong [TotalSNP];
	bool *TFSite = new bool [TotalSNP];

	for( int i = 0; i < TotalSNP; i++ )
	{
		ArrRR[i] = new double [TotalSNP];
		TFSite[i]=false;
		ArrSite[i]=0;
		for (int j =0 ; j< TotalSNP ; j++)
		{
			ArrRR[i][j]=1.00;
		}
	}



	double CalResult;
	key2=NewSNPList.begin();
	map<llong, vector <BaseType> >  :: iterator key2_se ;
	int Count=0;

	for(  ; key2!=NewSNPList.end(); key2++ )
	{
		OUTBB<<chrName<<"\t"<<(key2->first)<<endl;
		ArrSite[Count]=(key2->first);

		key2_se=key2  ;  key2_se++ ;
		int SedCount=Count+1;

		if ( key2_se!=NewSNPList.end() )
		{

			cal_RR_MA(key2->second , key2_se->second ,CalResult, Var);

			OUTAA<<setprecision(3)<<setiosflags(ios::right)<<setiosflags(ios::fixed)<<CalResult;

			ArrRR[Count][SedCount]=CalResult;
			ArrRR[SedCount][Count]=CalResult;

			key2_se++ ;
			SedCount++;
			for(  ; key2_se!=NewSNPList.end();  key2_se++)
			{
				cal_RR_MA(key2->second , key2_se->second ,CalResult, Var);
				OUTAA<<"\t"<<setprecision(3)<<setiosflags(ios::right)<<setiosflags(ios::fixed)<<CalResult;
				ArrRR[Count][SedCount]=CalResult;
				ArrRR[SedCount][Count]=CalResult;
				SedCount++;
			}
			OUTAA<<endl;
		}

		Count++;
	}

	OUTAA.close();
	OUTBB.close();

	//cerr<<paraFA04->MinRR<<"\t"<<paraFA04->TagRR<<endl;
	OUTCC<<"#chr\tStart\tEnd\tSNPNumber\tTagSNPList\n";
	cerr<<"find blocks...\n";
	if (  (paraFA04->TF)==1 )
	{
		int  SiteStart=0;
		int  SiteEnd=TotalSNP-1;
		while ( SiteStart < TotalSNP )
		{
			for ( SiteEnd=TotalSNP-1   ;  SiteStart<SiteEnd ;SiteEnd--)
			{
				int CountALL=0;
				int CountHLD=0;
				for (int ii=SiteStart+1  ; ii<=SiteEnd  ; ii++)
				{
					CountALL++;
					if (ArrRR[SiteStart][ii]>(paraFA04->MinRR))
					{
						CountHLD++;
					}
				}

				for (int ii=SiteEnd-1  ; ii>SiteStart  ; ii--)
				{
					CountALL++;
					if (ArrRR[SiteStart][SiteEnd]>(paraFA04->MinRR))
					{
						CountHLD++;
					}
				}

				if ( CountHLD >= (CountALL*(paraFA04->RatioRR)))
				{
					break;
				}
			}

			if  ( SiteEnd>SiteStart)
			{
				int Length=SiteEnd-SiteStart;

				OUTCC<<chrName<<"\t"<<ArrSite[SiteStart]<<"\t"<<ArrSite[SiteEnd]<<"\t"<<Length+1<<"\t"<<ArrSite[SiteStart];
				TFSite[SiteStart]=true;
				for (int RREE=SiteStart+1; RREE<=SiteEnd; RREE++)
				{
					bool TrunF=true ;
					for (int kk=SiteStart ; kk<RREE ; kk++)
					{
						if ( (TFSite[kk])  &&  (ArrRR[kk][RREE]>(paraFA04->TagRR)) )
						{
							TrunF=false;
						}
					}
					TFSite[RREE]=TrunF;
					if (TrunF){OUTCC<<","<<ArrSite[RREE];}
				}
				OUTCC<<"\n";

			}
			SiteStart=SiteEnd+1;
		}
	}
	else if  ( (paraFA04->TF)==2 )
	{
		int  Length=0;
		int  SiteStart=0;
		int  SiteEnd=0;
		for (int ii=1 ; ii< TotalSNP ; ii++)
		{
			if (ArrRR[ii][ii-1]>(paraFA04->MinRR))
			{
				if  (Length==0)	
				{
					SiteStart=ii-1;
					SiteEnd=ii;
					Length=1;
				}
				else
				{
					SiteEnd=ii;
					Length++;
				}
			}
			else
			{
				if  (Length>2)
				{
					OUTCC<<chrName<<"\t"<<ArrSite[SiteStart]<<"\t"<<ArrSite[SiteEnd]<<"\t"<<Length+1<<"\t"<<ArrSite[SiteStart];
					TFSite[SiteStart]=true;
					for (int RREE=SiteStart+1; RREE<=SiteEnd; RREE++)
					{
						bool TrunF=true ;
						for (int kk=SiteStart ; kk<RREE ; kk++)
						{
							if ( (TFSite[kk])  &&  (ArrRR[kk][RREE]>(paraFA04->TagRR)) )
							{
								TrunF=false;
							}
						}
						TFSite[RREE]=TrunF;
						if (TrunF){OUTCC<<","<<ArrSite[RREE];}
					}
					OUTCC<<"\n";
				}
				Length=0;
			}
			//			cerr<<Length<<"\t"<<ArrRR[ii][ii-1]<<"\t"<<ii<<endl;
		}
	}

	OUTCC.close();

	for(int i = 0; i <TotalSNP; i++)
	{
		delete[] ArrRR[i];
	}
	delete[] ArrRR;
	delete[] ArrSite;
	delete[] TFSite;





	string binPath=(paraFA04->BinDir)+"/ShowLDSVG";

	if ( access(binPath.c_str(), 0) == 0 )
	{		
		string cc=binPath+"\t-InPreFix\t"+(paraFA04->InStr2)+"\t-OutPut\t"+(paraFA04->InStr2)+".svg";
		std::system(cc.c_str()) ;
	}	
	else
	{
		char   buf[2048]={'\0'};
		string cc="which  ShowLDSVG  2> /dev/null ";
		memset( buf, '\0', sizeof(buf) );
		FILE   *stream ;
		stream=popen(cc.c_str(),"r") ;
		fread( buf, sizeof(char), sizeof(buf), stream);
		binPath=buf;
		binPath=binPath.substr(0,binPath.length()-1);

		cc=binPath+"\t-InPreFix\t"+(paraFA04->InStr2)+"\t-OutPut\t"+(paraFA04->InStr2)+".svg";
		if (binPath == "")
		{
			cout <<"\twarning: can't find the [ShowLDSVG] in your $PATH ; no png Figure Out"<<endl;
			cout <<"\t\tShowLDSVG\t"<<cc<<endl;
		}
		else
		{
			//		cc=cc+"; convert  "+(paraFA04->InStr2)+".svg\t\t"+(paraFA04->InStr2)+".png";
			std::system(cc.c_str()) ;
		}
	}

	return 1;


}












#endif