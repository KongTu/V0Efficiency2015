#include "fitting.h"

using namespace std;

TSystem->Load("libRooFit");

using namespace RooFit;

void eposHijingDifference(){

	gStyle->SetErrorX(0);

	TFile* file1 = new TFile("/Users/kongkong/2015Research/Efficiency/pPb2013/files/Hijing_pPb_10M_eta_v6.root");
	TFile* file2 = new TFile("/Users/kongkong/2015Research/Efficiency/pPb2013/files/EPOS_25M_v1.root");

	//TFile* file2 = new TFile("/Users/kongkong/2014Research/Code/Jet'study/gitV0sRatio/3MCsamples_comparison/epos_pPb_5M_eta_v4.root");
	
	TH1D* ks_eff_pPb[6];
	TH1D* la_eff_pPb[6];

	TH1D* ks_eff_epos[6];
	TH1D* la_eff_epos[6];

	stringstream ksName;
	stringstream laName;

	for(int eta = 0; eta < 6; eta++){

		ksName.str("");
		laName.str("");

		ksName << "ks_eff_pPb_";
		ksName << eta+1;

		laName << "la_eff_pPb_";
		laName << eta+1;;

		ks_eff_pPb[eta] = (TH1D*)file1->Get(ksName.str().c_str());
		la_eff_pPb[eta] = (TH1D*)file1->Get(laName.str().c_str());

		ksName.str("");
		laName.str("");

		ksName << "ks_eff_epos25_";
		ksName << eta+1;

		laName << "la_eff_epos25_";
		laName << eta+1;;

		ks_eff_epos[eta] = (TH1D*)file2->Get(ksName.str().c_str());
		la_eff_epos[eta] = (TH1D*)file2->Get(laName.str().c_str());
	
	}

 	TLine* l1 = new TLine(0,1,9.0,1.0);
	l1->SetLineWidth(2);
	l1->SetLineColor(kRed);
	l1->SetLineStyle(2);

	TLatex* ratio[6];
    ratio[0] = new TLatex(1.65,1.5,"-2.4 < #eta < -1.6");
    ratio[1] = new TLatex(1.65,1.5,"-1.6 < #eta < -0.8");
    ratio[2] = new TLatex(1.65,1.5,"-0.8 < #eta < 0");
    ratio[3] = new TLatex(1.65,1.5,"0 < #eta < 0.8");
    ratio[4] = new TLatex(1.65,1.5,"0.8 < #eta < 1.6");
    ratio[5] = new TLatex(1.65,1.5,"1.6 < #eta < 2.4");

	TCanvas* c2 = new TCanvas();
	c2->Divide(2,3,0,0);

	for(eta = 0; eta < 6; eta++){

		c2->cd(eta+1);
		ks_eff_epos[eta]->Divide( ks_eff_pPb[eta] );
		ks_eff_epos[eta]->SetYTitle("epos/pPb eff");
	    ks_eff_epos[eta]->SetXTitle("pT(GeV/c)");
	    ks_eff_epos[eta]->SetTitle("K^{0}_{s}");
	    ks_eff_epos[eta]->SetMarkerStyle(20);
	    ks_eff_epos[eta]->SetLineColor(kBlack);
	 	ks_eff_epos[eta]->GetYaxis()->SetRangeUser(0.2,2);
	 	ks_eff_epos[eta]->GetYaxis()->SetTitleSize(0.06);
	 	ks_eff_epos[eta]->GetYaxis()->SetLabelSize(0.06);
	 	ks_eff_epos[eta]->GetXaxis()->SetTitleSize(0.06);
	 	ks_eff_epos[eta]->GetXaxis()->SetLabelSize(0.06);
	 	ks_eff_epos[eta]->GetYaxis()->SetTitleOffset(0.75);
	 	ks_eff_epos[eta]->SetStats(kFALSE);
	    ks_eff_epos[eta]->Draw();
	    ratio[eta]->SetTextSize(0.07);
	    ratio[eta]->Draw("same");
	    l1->Draw("same");

	}
















}