#include "fitting.h"

using namespace std;

TSystem->Load("libRooFit");

using namespace RooFit;

void checkMultEfficiency(){

	TFile* file = new TFile("/Users/kongkong/2015Research/Efficiency/pPb2013/files/pPb_table/EPOS_pPb_30M_FEB_10_8mult.root");

	TH2D* ks_eff[8];
	TH2D* la_eff[8];

	stringstream ksEffName;
    stringstream laEffName;

    for(int mult = 0; mult < 8; mult++){

        ksEffName.str("");
        laEffName.str("");

        ksEffName << "ks_eff_";
        ksEffName << mult+1;

        laEffName << "la_eff_";
        laEffName << mult+1;


        ks_eff[mult] = (TH2D*)file->Get( ksEffName.str().c_str() );
        la_eff[mult] = (TH2D*)file->Get( laEffName.str().c_str() );
    }

    TH1D* ks_eff_mid[8];
    TH1D* la_eff_mid[8];

    for(mult = 0; mult < 8; mult++){

    	ksEffName.str("");
        laEffName.str("");

        ksEffName << "ks_eff_mid_";
        ksEffName << mult+1;

        laEffName << "la_eff_mid_";
        laEffName << mult+1;

    	ks_eff_mid[mult] = (TH1D*)ks_eff[mult]->ProjectionY(ksEffName.str().c_str(),3,3);
    	la_eff_mid[mult] = (TH1D*)la_eff[mult]->ProjectionY(laEffName.str().c_str(),3,3);
    }

	
	TLatex* ratio[4];

	ratio[0] = new TLatex(2.5,0.95,"120 < N^{offline}_{trk} < 150");
	ratio[1] = new TLatex(2.5,0.95,"150 < N^{offline}_{trk} < 185");
	ratio[2] = new TLatex(2.5,0.95,"185 < N^{offline}_{trk} < 220");
	ratio[3] = new TLatex(2.5,0.95,"220 < N^{offline}_{trk} < #infty");

 	TLine* l1 = new TLine(0,1,9.0,1.0);
	l1->SetLineWidth(2);
	l1->SetLineColor(kRed);
	l1->SetLineStyle(2);

	TCanvas* c1 = new TCanvas();
	c1->Divide(2,2,0,0);

	for(mult = 0; mult < 4; mult++){

		c1->cd(mult+1);
		ks_eff_mid[mult+4]->Divide( ks_eff_mid[0] );
		ks_eff_mid[mult+4]->SetMarkerStyle(20);
		ks_eff_mid[mult+4]->SetLineColor(kBlack);
		ks_eff_mid[mult+4]->GetYaxis()->SetTitle("eff/ratio (0<Ntrk<35)");
		ks_eff_mid[mult+4]->GetXaxis()->SetTitle("pT(GeV/c)");
		ks_eff_mid[mult+4]->SetStats(kFALSE);
		ks_eff_mid[mult+4]->SetTitle("K^{0}_{s}");
		ks_eff_mid[mult+4]->GetYaxis()->SetRangeUser(0.9,1.2);
		ks_eff_mid[mult+4]->Draw("P");
		ratio[mult]->Draw("same");
		l1->Draw("same");

	}

	TCanvas* c2 = new TCanvas();
	c2->Divide(2,2,0,0);

	for(mult = 0; mult < 4; mult++){

		c2->cd(mult+1);
		la_eff_mid[mult+4]->Divide( la_eff_mid[0] );
		la_eff_mid[mult+4]->SetMarkerStyle(20);
		la_eff_mid[mult+4]->SetLineColor(kBlack);
		la_eff_mid[mult+4]->GetYaxis()->SetTitle("eff/ratio (0<Ntrk<35)");
		la_eff_mid[mult+4]->GetXaxis()->SetTitle("pT(GeV/c)");
		la_eff_mid[mult+4]->SetStats(kFALSE);
		la_eff_mid[mult+4]->SetTitle("#Lambda/#bar{#Lambda}");
		la_eff_mid[mult+4]->GetYaxis()->SetRangeUser(0.9,1.2);
		la_eff_mid[mult+4]->Draw("P");
		ratio[mult]->Draw("same");
		l1->Draw("same");


	}




 




 }