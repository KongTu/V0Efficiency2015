#include "fitting.h"

using namespace std;

TSystem->Load("libRooFit");

using namespace RooFit;

void RapidityDistribution(){


	TFile* file1 = new TFile("/Users/kongkong/2015Research/ROOT_file/MC/EPOS/RapidityCheckEPOS/EPOS_pPb_old5M_yLAB_rpyDist_FEB_2_2015.root");
	TFile* file2 = new TFile("/Users/kongkong/2015Research/ROOT_file/data/RapidityCheckData/HM_185plus_pPb_yLAB_rpyDist_FEB_2_2015.root");

	TH1D* ks_epos;
	TH1D* la_epos;

	TH1D* ks_data;
	TH1D* la_data;

	ks_epos = (TH1D*)file1->Get("ana/ks_rpy");
	la_epos = (TH1D*)file1->Get("ana/la_rpy");

	ks_data = (TH1D*)file2->Get("ana/ks_rpy");
	la_data = (TH1D*)file2->Get("ana/la_rpy");

	TCanvas* c1 = new TCanvas();
	c1->Divide(2,1,0,0);
	c1->cd(1);

	double count_epos = ks_epos->GetEntries();
	double count_data = ks_data->GetEntries();

	ks_epos->Scale( count_data/count_epos );
	ks_data->Divide( ks_epos );
	//ks_data->GetYaxis()->SetRangeUser(0.7,1.15);
	ks_data->Draw();

	c1->cd(2);
	double count_epos = la_epos->GetEntries();
	double count_data = la_data->GetEntries();

	la_epos->Scale( count_data/count_epos );
	la_data->Divide( la_epos );
	//la_data->GetYaxis()->SetRangeUser(0.7,1.15);
	la_data->Draw();


	//TFile f1("../files/RapidityDistributionRatio.root","new");
	//ks_data->Write();
	//la_data->Write();





}