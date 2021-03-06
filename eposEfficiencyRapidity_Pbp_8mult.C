#include "fitting.h"

using namespace std;

TSystem->Load("libRooFit");

using namespace RooFit;

void eposEfficiencyRapidity_Pbp_8mult(){

	TFile* file[8];
	file[0] = new TFile("/Users/kongkong/2015Research/ROOT_file/MC/EPOS/newEPOS_lab_mult/Mult_EPOS_RootFile/EPOS_Mult_1_FEB_10_2015.root");
	file[1] = new TFile("/Users/kongkong/2015Research/ROOT_file/MC/EPOS/newEPOS_lab_mult/Mult_EPOS_RootFile/EPOS_Mult_2_FEB_10_2015.root");
	file[2] = new TFile("/Users/kongkong/2015Research/ROOT_file/MC/EPOS/newEPOS_lab_mult/Mult_EPOS_RootFile/EPOS_Mult_3_FEB_10_2015.root");
	file[3] = new TFile("/Users/kongkong/2015Research/ROOT_file/MC/EPOS/newEPOS_lab_mult/Mult_EPOS_RootFile/EPOS_Mult_4_FEB_10_2015.root");
	file[4] = new TFile("/Users/kongkong/2015Research/ROOT_file/MC/EPOS/newEPOS_lab_mult/Mult_EPOS_RootFile/EPOS_Mult_5_FEB_10_2015.root");
	file[5] = new TFile("/Users/kongkong/2015Research/ROOT_file/MC/EPOS/newEPOS_lab_mult/Mult_EPOS_RootFile/EPOS_Mult_6_FEB_10_2015.root");
	file[6] = new TFile("/Users/kongkong/2015Research/ROOT_file/MC/EPOS/newEPOS_lab_mult/Mult_EPOS_RootFile/EPOS_Mult_7_FEB_10_2015.root");
	file[7] = new TFile("/Users/kongkong/2015Research/ROOT_file/MC/EPOS/newEPOS_lab_mult/Mult_EPOS_RootFile/EPOS_Mult_8_FEB_10_2015.root");
	
	TH3D* ksHist[8];
	TH3D* laHist[8];
	TH3D* xiHist[8];

	TH3D* genksHist[8];
	TH3D* genlaHist[8];

	for(int mult = 0; mult < 8; mult++){

		ksHist[mult] = (TH3D*)file[mult]->Get("ana/InvMass_ks_underlying");
		laHist[mult] = (TH3D*)file[mult]->Get("ana/InvMass_la_underlying");
		genksHist[mult] = (TH3D*)file[mult]->Get("ana/genKS_underlying");
		genlaHist[mult] = (TH3D*)file[mult]->Get("ana/genLA_underlying");
		xiHist[mult] = (TH3D*)file[mult]->Get("ana/XiDaughter");
	}

	TH1D* ks_mass[8][5][26];
	TH1D* la_mass[8][5][20];
	TH1D* genks_mass[8][5][26];
	TH1D* genla_mass[8][5][20];
	TH1D* xiHist_mass[8][5][20];

    double pTbinsBound[] = {6,8,10,12,14,16,18,20,22,24,26,28,30,34,38,42,46,50,56,66,90};
    double la_ptbins[] = {0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.4,2.6,2.8,3.0,3.4,3.8,4.2,4.6,5.0,5.6,6.6,9.0};

    double ks_pTbinsBound[27] = {1,3,4,5,6,7,8,9,10,12,14,16,18,20,22,24,26,28,30,34,38,42,46,50,56,66,90};
    double ks_ptbins[27] = {0.1,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.4,2.6,2.8,3.0,3.4,3.8,4.2,4.6,5.0,5.6,6.6,9.0};
    double ks_binwidth[26] = {0.2,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.4,0.4,0.4,0.4,0.4,0.6,1.0,2.4};

    double rpybins[6] = {16,23,30,38,45,54};

    stringstream ksHistName;
    stringstream laHistName;
    stringstream xiHistName;

    for(mult = 0; mult < 8; mult++){

    for ( int rpy = 0; rpy < 5; rpy++){

    	for (int pt = 0; pt < 26; pt++){

    		ksHistName.str("");

    		ksHistName << "ks_";
    		ksHistName << mult+1;
    		ksHistName << "_";
	        ksHistName << rpy+1;
	        ksHistName << "_";
	        ksHistName << pt;

	        ks_mass[mult][rpy][pt] = ksHist[mult]->ProjectionZ( ksHistName.str().c_str(),rpybins[rpy]+1,rpybins[rpy+1],ks_pTbinsBound[pt]+1,ks_pTbinsBound[pt+1] );

	        ksHistName.str("");

         	ksHistName << "genks_";
         	ksHistName << mult+1;
    		ksHistName << "_";
	        ksHistName << rpy+1;
	        ksHistName << "_";
	        ksHistName << pt;

	        genks_mass[mult][rpy][pt] = genksHist[mult]->ProjectionZ( ksHistName.str().c_str(),rpybins[rpy]+1,rpybins[rpy+1],ks_pTbinsBound[pt]+1,ks_pTbinsBound[pt+1] );

    	}

	    for (pt = 0; pt < 20; pt++){

	        laHistName.str("");
	        xiHistName.str("");

	        laHistName << "la_";
	        laHistName << mult+1;
    		laHistName << "_";
	        laHistName << rpy+1;
	        laHistName << "_";
	        laHistName << pt;

	        xiHistName << "xiDau_";
	        xiHistName << mult+1;
    		xiHistName << "_";
	        xiHistName << rpy+1;
	        xiHistName << "_";
	        xiHistName << pt;

	        la_mass[mult][rpy][pt] = laHist[mult]->ProjectionZ( laHistName.str().c_str(),rpybins[rpy]+1,rpybins[rpy+1],pTbinsBound[pt]+1,pTbinsBound[pt+1] );
	        xiHist_mass[mult][rpy][pt] = xiHist[mult]->ProjectionZ( xiHistName.str().c_str(),rpybins[rpy]+1,rpybins[rpy+1],pTbinsBound[pt]+1,pTbinsBound[pt+1] );

	  
	        laHistName.str("");

	        laHistName << "genla_";
	        laHistName << mult+1;
    		laHistName << "_";
          	laHistName << rpy+1;
	        laHistName << "_";
	        laHistName << pt;

	        genla_mass[mult][rpy][pt] = genlaHist[mult]->ProjectionZ( laHistName.str().c_str(),rpybins[rpy]+1,rpybins[rpy+1],pTbinsBound[pt]+1,pTbinsBound[pt+1] );
	   	
	   	}
   	}
   }
    
   	int genksYield[8][5][26];
   	int genlaYield[8][5][20];

   	for( mult = 0; mult < 8; mult++){

   		for ( rpy = 0; rpy < 5; rpy++){

	   		for( pt = 0; pt < 26; pt++){

	   			genksYield[mult][rpy][pt] = genks_mass[mult][rpy][pt]->GetEntries();
	   		}
		   	
		   	for (pt = 0; pt < 20; pt++){

		   		genlaYield[mult][rpy][pt] = genla_mass[mult][rpy][pt]->GetEntries();

		   	}
   		}	
   	}


   	double ksYield[8][5][26];
   	double laYield[8][5][20];

   	for(mult = 0; mult < 8; mult++){

	   	for ( rpy = 0; rpy < 5; rpy++){

	   		for (pt = 0; pt < 26; pt++){

	   			ksYield[mult][rpy][pt] = ks_YieldCal( ks_mass[mult][rpy][pt] );

	   		}

		   	for (pt = 0; pt < 20; pt++){
		
				la_mass[mult][rpy][pt]->Add( xiHist_mass[mult][rpy][pt],-1 );
		   			laYield[mult][rpy][pt] = la_YieldCal( la_mass[mult][rpy][pt] );
		   	}
   		}
   	}
   	

/**
 * Efficiency in differentrpy bins:
 

 	TH1D* ks_eff_rpy[5];
 	TH1D* la_eff_rpy[5];
 	
 	stringstream ks_effName;
 	stringstream la_effName;

 	for (rpy = 0; rpy < 5; rpy++){

 		ks_effName.str("");
 		ks_effName << "ks_eff_Pbp_epos5_";
 		ks_effName << rpy + 1;
 		ks_eff_rpy[rpy] = new TH1D(ks_effName.str().c_str(), ks_effName.str().c_str(),26,ks_ptbins);

 		la_effName.str("");
 		la_effName << "la_eff_Pbp_epos5_";
 		la_effName << rpy + 1;
 		la_eff_rpy[rpy] = new TH1D(la_effName.str().c_str(), la_effName.str().c_str(),20,ptbins);

 		for (pt = 0; pt < 26; pt++){
 			
 			ks_eff_rpy[rpy]->SetBinContent(pt+1, ksYield[rpy][pt]/genksYield[rpy][pt]);
 				ks_eff_rpy[rpy]->SetBinError(pt+1, errorCal( ksYield[rpy][pt], genksYield[rpy][pt] ) );
		}

		for (pt = 0; pt < 20; pt++){

 			la_eff_rpy[rpy]->SetBinContent(pt+1, laYield[rpy][pt]/genlaYield[rpy][pt]);
 				la_eff_rpy[rpy]->SetBinError(pt+1, errorCal( laYield[rpy][pt], genlaYield[rpy][pt] ) );
 		}
 	}

/**
 * 2D efficiency Table:
 */

 	double rpybins_fill[6] = {-1.9,-1.2,-0.5,0.3,1.0,1.9};

 	TH2D* ks_eff[8]; 
 	TH2D* la_eff[8];

 	for( mult = 0; mult < 8; mult++){
	   	
 		ksHistName.str("");
 		laHistName.str("");

 		ksHistName << "ks_eff_";
 		ksHistName << mult+1;

 		laHistName << "la_eff_";
 		laHistName << mult+1;

 		ks_eff[mult] = new TH2D( ksHistName.str().c_str(), ksHistName.str().c_str(),5,rpybins_fill,26,ks_ptbins);
 		la_eff[mult] = new TH2D( laHistName.str().c_str(), laHistName.str().c_str(),5,rpybins_fill,20,la_ptbins);

	   	for ( rpy = 0; rpy < 5; rpy++){

	   		for( pt = 0; pt < 26; pt++){

	   			double temp_ks = ksYield[mult][rpy][pt]/genksYield[mult][rpy][pt];

	   			ks_eff[mult]->SetBinContent(rpy+1,pt+1, temp_ks );
		   			ks_eff[mult]->SetBinError(rpy+1,pt+1, errorCal(ksYield[mult][rpy][pt], genksYield[mult][rpy][pt]) );


	   		}

		   	for ( pt = 0; pt < 20; pt++){
		   		
		   		double temp_la = laYield[mult][rpy][pt]/genlaYield[mult][rpy][pt];

		   		la_eff[mult]->SetBinContent(rpy+1,pt+1, temp_la );
		   			la_eff[mult]->SetBinError(rpy+1,pt+1, errorCal(laYield[mult][rpy][pt], genlaYield[mult][rpy][pt]) );

		   	}
	   	}
   }
   	

   	TFile f1("EPOS_Pbp_30M_FEB_10_8mult.root","new");
   
   	for ( mult = 0; mult < 8; mult++){

   		ks_eff[mult]->Write();
   		la_eff[mult]->Write();
   	}



}