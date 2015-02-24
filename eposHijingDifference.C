#include "fitting.h"

using namespace std;

TSystem->Load("libRooFit");

using namespace RooFit;

void eposHijingDifference(){

	gStyle->SetErrorX(0);

	//TFile* file1 = new TFile("/Users/kongkong/2015Research/Efficiency/pPb2013/files/Hijing_pPb_10M_eta_v6.root");
	//TFile* file2 = new TFile("/Users/kongkong/2015Research/Efficiency/pPb2013/files/EPOS_25M_v1.root");
	
	TFile* file1 = new TFile("/Users/kongkong/2014Research/Code/Jet'study/gitV0sRatio/eposEfficiencyRapidityTable/EPOSeffTable_withVTXreweight_5M_Nov14_rapidity_v3_26ks_pTbins.root");
	TFile* file2 = new TFile("/Users/kongkong/2014Research/Code/Jet'study/gitV0sRatio/eposEfficiencyRapidityTable/EPOSeffTable_new25M_JAN20_rapidity_v2_26ks_pTbins.root");

	TH1D* ks_eff_5M[6];
	TH1D* la_eff_5M[6];

	TH1D* ks_eff_25M[6];
	TH1D* la_eff_25M[6];

	stringstream ksName;
	stringstream laName;

	for(int rpy = 0; rpy < 5; rpy++){

		ksName.str("");
		laName.str("");

		ksName << "ks_eff_rpy_vtx_";
		ksName << rpy+1;

		laName << "la_eff_rpy_vtx_";
		laName << rpy+1;;

		ks_eff_5M[rpy] = (TH1D*)file1->Get(ksName.str().c_str());
		la_eff_5M[rpy] = (TH1D*)file1->Get(laName.str().c_str());

		ksName.str("");
		laName.str("");

		ksName << "ks_eff_rpy_vtx_";
		ksName << rpy+1;

		laName << "la_eff_rpy_vtx_";
		laName << rpy+1;;

		ks_eff_25M[rpy] = (TH1D*)file2->Get(ksName.str().c_str());
		la_eff_25M[rpy] = (TH1D*)file2->Get(laName.str().c_str());
	
	}

 	TLine* l1 = new TLine(0,1,9.0,1.0);
	l1->SetLineWidth(2);
	l1->SetLineColor(kRed);
	l1->SetLineStyle(2);

	TLatex* ratio[5];

    ratio[0] = new TLatex(1.65,1.5,"-2.87 < y^{}_{cm} < -1.8");
    ratio[1] = new TLatex(1.65,1.5,"-1.8 < y^{}_{cm} < -0.9");
    ratio[2] = new TLatex(1.65,1.5,"-0.9 < y^{}_{cm} < 0");
    ratio[3] = new TLatex(1.65,1.5,"0 < y^{}_{cm} < 0.93");
    ratio[4] = new TLatex(1.65,1.5,"0.93 < y^{}_{cm} < 1.93");

	TCanvas* c2 = new TCanvas();
	c2->Divide(2,3,0,0);

	for(rpy = 0; rpy < 5; rpy++){

		c2->cd(rpy+1);
		la_eff_25M[rpy]->Divide( la_eff_5M[rpy] );
		la_eff_25M[rpy]->SetYTitle("epos25M/5M eff");
	    la_eff_25M[rpy]->SetXTitle("pT(GeV/c)");
	    //la_eff_25M[rpy]->SetTitle("K^{0}_{s}");
	    la_eff_25M[rpy]->SetTitle("#Lambda+#bar{#Lambda}");
	    la_eff_25M[rpy]->SetMarkerStyle(20);
	    la_eff_25M[rpy]->SetLineColor(kBlack);
	 	la_eff_25M[rpy]->GetYaxis()->SetRangeUser(0.2,2);
	 	la_eff_25M[rpy]->GetYaxis()->SetTitleSize(0.06);
	 	la_eff_25M[rpy]->GetYaxis()->SetLabelSize(0.06);
	 	la_eff_25M[rpy]->GetXaxis()->SetTitleSize(0.06);
	 	la_eff_25M[rpy]->GetXaxis()->SetLabelSize(0.06);
	 	la_eff_25M[rpy]->GetYaxis()->SetTitleOffset(0.75);
	 	la_eff_25M[rpy]->SetStats(kFALSE);
	    la_eff_25M[rpy]->Draw();
	    ratio[rpy]->SetTextSize(0.07);
	    ratio[rpy]->Draw("same");
	    l1->Draw("same");

	}
















}