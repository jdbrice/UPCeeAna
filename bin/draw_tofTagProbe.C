


void draw_tofTagProbe(){

	TCanvas * can = new TCanvas( "can", "", 1200, 900 );
	can->SetTopMargin( 0.05 );
	can->SetBottomMargin( 0.13 );
	can->SetRightMargin( 0.05 );


	gStyle->SetOptStat( 0 );

	TFile *f = new TFile( "TofTagProbe_Run12UU.root" );
	TGraph * g = (TGraph*)f->Get("TofEff");

	TH1 * h = new TH1F( "h", "h", 500, 0, 1.5 );
	h->SetMaximum(1.0);
	h->SetMinimum(0.0);
	h->SetTitle("");
	h->GetXaxis()->SetTitle( "p_{T}^{e} (GeV/c)" );
	h->GetYaxis()->SetTitle( "#varepsilon TOF Matching + timing" );
	h->Draw();
	g->Draw("same");

	can->Print( "tofTagProbe_Efficiency.pdf" );

}