


void TofEff(  ){

	TFile * f = new TFile( "Run10AuAu.root" );

	TH1F * hm0 = (TH1F*)f->Get( "mass0tof" );
	TH1F * hm1 = (TH1F*)f->Get( "mass1tof" );
	TH1F * hm2 = (TH1F*)f->Get( "mass2tof" );

	double bins[] = {0.00, 0.05, 0.10, 0.40, 0.50, 0.60, 0.70, 0.80, 1.00, 1.5, 2.0, 3.0};
	int nbins=11;

	hm0 = (TH1F*)hm0->Rebin(nbins, "hm0", bins);
	hm1 = (TH1F*)hm1->Rebin(nbins, "hm1", bins);
	hm2 = (TH1F*)hm2->Rebin(nbins, "hm2", bins);

	hm0->Sumw2();
	hm1->Sumw2();
	hm2->Sumw2();

	TH1* heff1 = (TH1*)hm2->Clone("heff1");
	TH1* heff2 = (TH1*)hm2->Clone("heff2");

	heff1->Divide(heff1, hm1, 1, 1, "B");
	heff2->Divide(heff2, hm0, 1, 1, "B");

	TCanvas *c1 = new TCanvas( "c1", "", 100, 100, 600, 600 );
	heff1->Draw("pe");

	TCanvas *c2 = new TCanvas( "c2", "", 700, 100, 600, 600 );
	heff2->Draw("pe");
}