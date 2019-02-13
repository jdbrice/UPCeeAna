


void low_purity( float mchi = 3, float max_x = 15, bool exp2=true, float c1=0, float c2=20 ){

	gStyle->SetOptStat(0);
	gStyle->SetOptFit(111);


	TFile *f = new TFile( "Run10AuAu.root" );

	TH2 * hchi = (TH2*)f->Get( "chipidcut" );

	TAxis *ax = hchi->GetXaxis();
	TAxis *ay = hchi->GetYaxis();
	TH1 * hchiee = hchi->ProjectionY("hchiee", ax->FindBin(c1), ax->FindBin(c2) );
	TH1 * hchieeover = hchi->ProjectionY("hchieeover", ax->FindBin(c2), -1 );

	cout << "overflow: " << hchieeover->GetEntries() << endl;


	hchiee->GetXaxis()->SetTitleOffset(0.8);
	hchiee->GetXaxis()->SetTitle( "" );

	hchiee->GetYaxis()->SetTitle( "dN/d(#chi^{2}_{ee})" );
	hchiee->GetYaxis()->SetTitleSize(16.0 / 360.0);
	TCanvas *c = new TCanvas( "c", "c", 1200, 900 );
	c->SetTopMargin(0.02);
	c->SetRightMargin(0.02);
	c->SetLogy(1);

	gStyle->SetStatX( 0.98 );
	gStyle->SetStatY( 0.98 );

	hchiee->Rebin(2);
	hchiee->SetLineColor( TColor::GetColor( "#296D36" ) );
	hchiee->SetMarkerStyle(8);
	hchiee->SetMarkerSize(1.5);
	hchiee->SetMarkerColor( TColor::GetColor( "#296D36" ) );
	hchiee->Draw();
	hchiee->SetMaximum(1e4);
	hchiee->GetXaxis()->SetRangeUser(0, 20);
	hchiee->Draw("same pe");

	TF1 * ff = 0;
	if ( exp2 ) 
		ff = new TF1( "ff", "[0] * exp( x * [1] ) + [2] * exp([3] * (x-[4]))" );
	else 
		ff = new TF1( "ff", "[0] * exp( x * [1] ) + [2]" );
	ff->SetParameters( 2372, -0.7, 2, 0.25, 1 );
	ff->SetLineColor(kBlack);
	ff->SetLineWidth(2);
	ff->SetParLimits( 0, 0, 1e9 );
	ff->SetParLimits( 2, 0, 1e9 );
	TF1 * ffee = new TF1( "ffee", "[0] * exp( x * [1] )" );
	TF1 * ffpipi = new TF1( "ffpipi", "[0] * exp([1] * (x-[2]))" );


	hchiee->Fit( ff, "RL", "", 0, max_x );
	hchiee->Fit( ff, "RL", "", 0, max_x );
	hchiee->Fit( ff, "RL", "", 0, max_x );

	ffee->SetParameters( ff->GetParameter(0), ff->GetParameter(1));
	ffee->SetLineColor( kBlue );
	ffee->SetRange(0, 15);
	ffee->SetLineWidth(2);
	ffee->Draw("same");

	TLine * l = new TLine( 0, ff->GetParameter(2), max_x, ff->GetParameter(2) ) ;
	if ( exp2 ){
		ffpipi->SetParameters( ff->GetParameter(2), ff->GetParameter(3), ff->GetParameter(4) );
		ffpipi->SetLineColor( kRed );
		ffpipi->SetRange(0, max_x);
		ffpipi->SetLineWidth(2);
		ffpipi->Draw("same");
	} else {
		
		l->SetLineColor( kRed );
		l->SetLineWidth(3);
		l->Draw("same");
	}

	TLegend * leg = new TLegend( 0.2, 0.78, 0.6, 0.98 );
	leg->AddEntry( hchiee, "Data", "lpe" );
	leg->AddEntry( ffee, "Fit: e^{+}e^{-}", "l" );
	if ( exp2 )
		leg->AddEntry( ffpipi, "Fit: Background", "l" );
	else 
		leg->AddEntry( l, "Fit: Background", "l" );
	leg->Draw();

	float p = ffee->Integral(0, mchi) / ff->Integral(0, mchi);
	TLatex * tl = new TLatex();
	tl->SetTextFont(42);
	tl->DrawLatexNDC( 0.5, 0.6, TString::Format( "purity ( #chi^{2}_{ee} < %d ) = %0.2f%%", (int)mchi, p*100 ) );

	tl->DrawLatexNDC( 0.9, 0.03, "#chi^{2}_{ee}" );
	tl->DrawLatexNDC( 0.9, 0.03, "#chi^{2}_{ee}" );

	cout << "e+e- Purity (chi^ee < 10) = " << p << endl;
	
	c->Print( TString::Format("purity_%d_to_%d.pdf", (int)c1, (int)c2 ) );
	c->Print( TString::Format("/Users/jdb/notable/attachments/upc_ee_purity_%d_to_%d.png", (int)c1, (int)c2 ) );

}