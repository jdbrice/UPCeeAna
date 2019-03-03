

void margins( TCanvas * c ){
	c->SetTopMargin( 0.03 );
	c->SetBottomMargin( 0.13 );
	c->SetRightMargin( 0.05 );
	c->SetLeftMargin( 0.13 );
}


TH1 * backSlice( TH2 * h2, float xpipi ){

	int i = h2->GetXaxis()->FindBin( xpipi );
	TH1* hB = h2->ProjectionY( TString::Format( "bSlice%d", i ), i );
	hB->SetLineColor( kRed );
	hB->SetLineWidth( 2 );
	hB->SetMarkerColor( kRed );
	hB->SetMarkerStyle( 8 );
	return hB;
}


void purity_slices( float xpipi = 30 ) {

	gStyle->SetOptStat(0);

	TFile *f = new TFile( "Run10AuAu.root" );

	TH2 * hSel = (TH2*)f->Get( "chipidcutSel" );
	TH2 * hNoSel = (TH2*)f->Get( "chipidcutNoSel" );


	TH1 * hSel1 = hSel->ProjectionY( "hSel1", hSel->GetXaxis()->FindBin(xpipi), -1 );

	TCanvas * c1 = new TCanvas( "c1", "", 1200, 900 );
	margins( c1 );
	hSel1->SetMarkerStyle( 8 );
	hSel1->SetMarkerColor( kBlack );
	hSel1->SetLineColor( kBlack );
	hSel1->SetLineWidth( 2 );
	hSel1->GetXaxis()->SetRangeUser(0, 15);
	hSel1->GetYaxis()->SetTitle( "dN/d#chi^{2}_{ee}" );
	hSel1->GetXaxis()->SetTitle( "#chi^{2}_{ee}" );
	hSel1->Draw( "hist" );
	hSel1->Draw( "same pe" );

	TH1 * hB = backSlice( hNoSel, xpipi );
	hB->Draw("same hist");
	hB->Draw("same pe");
	TLine * lCut = new TLine( (xpipi/3), hSel1->GetMinimum(), (xpipi/3), hSel1->GetMaximum() / 2.0 );
	lCut->SetLineColor(kBlue);
	lCut->SetLineStyle(5);
	lCut->SetLineWidth(2);
	lCut->Draw();

	TLegend * leg = new TLegend( 0.6, 0.8, 0.95, 0.97 );
	leg->AddEntry( hSel1, "Selected Signal" );
	leg->AddEntry( hB, "Background" );
	leg->Draw();

	TLatex tl;
	tl.SetTextFont(42);
	tl.DrawLatexNDC( 0.4, 0.90, TString::Format("#chi^{2}_{#pi#pi} > %d", (int)xpipi) );



	gPad->SetLogy(1);

	c1->Print( TString::Format("purity_slice_X2pipi_%d.pdf", (int)xpipi) );
	c1->Print( TString::Format("purity_slice_X2pipi_%d.png", (int)xpipi) );


}