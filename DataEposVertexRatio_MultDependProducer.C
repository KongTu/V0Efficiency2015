#include "fitting.h"

using namespace std;

TSystem->Load("libRooFit");

using namespace RooFit;

void DataEposVertexRatio_MultDependProducer(){

	TFile* file1 = new TFile("/Users/kongkong/2015Research/ROOT_file/MC/EPOS/EPOS_25M_JAN12_2015.root");
	//TFile* file1 = new TFile("/Users/kongkong/2014Research/ROOT_file/newEPOSsample/EPOS_TH3D_Nov21_vtx_2014.root");

	TFile* file2[8];

	file2[0] = new TFile("/Users/kongkong/2014Research/ROOT_file/new_pPb_sample/MB_Nov10_0_35.root");
	file2[1] = new TFile("/Users/kongkong/2014Research/ROOT_file/new_pPb_sample/MB_Nov10_35_60.root");
	file2[2] = new TFile("/Users/kongkong/2014Research/ROOT_file/new_pPb_sample/MB_Nov10_60_90.root");
	file2[3] = new TFile("/Users/kongkong/2014Research/ROOT_file/new_pPb_sample/MB_Nov10_90_120.root");
	file2[4] = new TFile("/Users/kongkong/2015Research/ROOT_file/data/vertexCheck/Data_Mult_120_150_FEB_4_2015.root");
	file2[5] = new TFile("/Users/kongkong/2015Research/ROOT_file/data/vertexCheck/Data_Mult_150_185_FEB_4_2015.root");
	file2[6] = new TFile("/Users/kongkong/2015Research/ROOT_file/data/vertexCheck/Data_Mult_185_220_FEB_4_2015.root");
	file2[7] = new TFile("/Users/kongkong/2015Research/ROOT_file/data/vertexCheck/Data_Mult_220plus_FEB_4_2015.root");

	stringstream dataName;

	TH1D* vertex_data[8];
	for(int mult = 0; mult < 8; mult++){

		dataName.str("");
		dataName << "data_";
		dataName << mult+1;

		vertex_data[mult] = (TH1D*)file2[mult]->Get("ana/vertexDistZ")->Clone( dataName.str().c_str() );
	}

	TH1D* vertex_epos = (TH1D*)file1->Get("ana/vertexDistZ")->Clone("epos");

	for(mult = 0; mult < 8; mult++){

		double ratio1 = (vertex_epos->GetEntries()/vertex_data[mult]->GetEntries());
		vertex_data[mult]->Scale( ratio1 );
		vertex_data[mult]->Divide( vertex_epos );

	}

	TLatex* ratio[8];

    ratio[0] = new TLatex(-5,0.8,"0 < N^{offline}_{trk} < 35");
    ratio[1] = new TLatex(-5,0.8,"35 < N^{offline}_{trk} < 60");
    ratio[2] = new TLatex(-5,0.8,"60 < N^{offline}_{trk} < 90");
    ratio[3] = new TLatex(-5,0.8,"90 < N^{offline}_{trk} < 120");
    ratio[4] = new TLatex(-5,0.8,"120 < N^{offline}_{trk} < 150");
    ratio[5] = new TLatex(-5,0.8,"150 < N^{offline}_{trk} < 185");
    ratio[6] = new TLatex(-5,0.8,"185 < N^{offline}_{trk} < 220");
    ratio[7] = new TLatex(-5,0.8,"220 < N^{offline}_{trk} < #infty");

	TCanvas* c1 = new TCanvas();
	c1->Divide(4,2,0,0);
	for(mult = 0; mult < 8; mult++){

		c1->cd(mult+1);
		gPad->SetTicks();
		vertex_data[mult]->GetYaxis()->SetTitle("data/epos vertexRatio");
		vertex_data[mult]->GetYaxis()->SetRangeUser(0,2.2);
		vertex_data[mult]->SetStats(kFALSE);
		vertex_data[mult]->Draw();
		ratio[mult]->Draw("same");

	}
	

	TFile f1("vertex_epos_multDepend.root","new");
	for(mult = 0; mult < 8; mult++){

		vertex_data[mult]->Write();
	}
	

}