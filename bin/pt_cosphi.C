
void setAxisLabels( TAxis* a ){
	a->SetLabelOffset(0.02);
	a->SetNdivisions(-502);
	a->ChangeLabel(2,-1,-1,-1,-1,-1,"#frac{#pi}{4}");
	a->ChangeLabel(-1,-1,-1,-1,-1,-1,"#frac{#pi}{2}");
}


void pt_cosphi( string n = "Run10AuAu.root" ){

	gStyle->SetOptFit(111);
	gStyle->SetOptStat(0);

	TFile *f = new TFile( n.c_str() );

	TH2 * h2=(TH2*)f->Get("wdeltaPhi_pd1_fold_pt");
	TAxis * ax = h2->GetXaxis();
	int ipt1 = 25; // center = 0.0245
	int ipt2 = 45; // center = 0.0445
	int ipt3 = ax->FindBin( 0.120 );

	TH1 * hpt[3] = {NULL, NULL, NULL};
	hpt[0] = h2->ProjectionY( "hpt0", 1, ipt1 );
	hpt[1] = h2->ProjectionY( "hpt1", ipt1, ipt2 );
	hpt[2] = h2->ProjectionY( "hpt2", ipt2, ipt3 );

	setAxisLabels(hpt[0]->GetXaxis());
	setAxisLabels(hpt[1]->GetXaxis());
	setAxisLabels(hpt[2]->GetXaxis());
	

	for ( int i = 0; i < 3; i++ ){
		hpt[i]->SetLineWidth(2);
	}

	TCanvas *c1 = new TCanvas( "c1", "", 1200, 900 );

	hpt[0]->SetLineColor( TColor::GetColor( "#AAAAAA" ) );
	hpt[1]->SetLineColor( TColor::GetColor( "#000000" ) );
	hpt[2]->SetLineColor( TColor::GetColor( "#0000ff" ) );


	hpt[0]->SetMinimum( 300 );
	hpt[0]->SetMaximum( 900 );
	hpt[0]->DrawClone();
	hpt[1]->DrawClone("same");
	hpt[2]->DrawClone("same");

	TLegend *leg = new TLegend( 0.5, 0.6, 0.9, 0.9 );
	leg->AddEntry( hpt[0], "0 < p_{T}^{ee} < 25 MeV/c", "le" );
	leg->AddEntry( hpt[1], "25 < p_{T}^{ee} < 45 MeV/c", "le" );
	leg->AddEntry( hpt[2], "45 < p_{T}^{ee} < 120 MeV/c", "le" );
	leg->Draw("same");

	TF1 * f1 = new TF1( "f1", "[0] *( 1 + [1] * 0.01 * cos( 4 * x ) +  [2] * 0.01 * cos( 2*x ) )" );
	TF1 * f2 = new TF1( "f2", "[0] *( 1 + [1] * 0.01 * cos( 4 * x ) +  [2] * 0.01 * cos( 2*x ) )" );
	TF1 * f3 = new TF1( "f3", "[0] *( 1 + [1] * 0.01 * cos( 4 * x ) +  [2] * 0.01 * cos( 2*x ) )" );

	f1->SetParName( 1, "4 #phi (%)" );
	f1->SetParName( 2, "2 #phi (%)" );

	f2->SetParName( 1, "4 #phi (%)" );
	f2->SetParName( 2, "2 #phi (%)" );

	f3->SetParName( 1, "4 #phi (%)" );
	f3->SetParName( 2, "2 #phi (%)" );

	TCanvas *c2 = new TCanvas( "c2", "", 1200, 900 );

	hpt[0]->SetTitle( "0 < p_{T}^{ee} < 25 MeV/c" );
	hpt[0]->Fit( f1, "R", "", 0, 1.5 );
	c2->Print( "/Users/jdb/notable/attachments/cos_4phi_vs_pt0_25.png" );
	c2 = new TCanvas( "c3", "", 1200, 900 );
	hpt[1]->SetTitle( "25 < p_{T}^{ee} < 45 MeV/c" );
	hpt[1]->Fit( f2, "R", "", 0, 1.5 );
	c2->Print( "/Users/jdb/notable/attachments/cos_4phi_vs_pt25_45.png" );
	c2 = new TCanvas( "c4", "", 1200, 900 );
	hpt[2]->SetTitle( "45 < p_{T}^{ee} < 120 MeV/c" );
	hpt[2]->Fit( f3, "R", "", 0, 1.5 );
	c2->Print( "/Users/jdb/notable/attachments/cos_4phi_vs_pt45_120.png" );
	// TLegend *leg = new TLegend( 0.5, 0.6, 0.9, 0.9 );
	// leg->AddEntry( hpt[0], "0 < p_{T}^{ee} < 25 MeV/c", "le" );
	// leg->AddEntry( hpt[1], "25 < p_{T}^{ee} < 45 MeV/c", "le" );
	// leg->AddEntry( hpt[2], "45 < p_{T}^{ee} < 120 MeV/c", "le" );
	// leg->Draw("same");

	
	
	// gStyle->SetStatW(0.4);

	// c1->Print( "/Users/jdb/notable/attachments/upcee_deltaPhi_foldpi4_frac_allM.png" );

}