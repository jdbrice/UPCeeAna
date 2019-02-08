


void cosphi( string n = "Run10AuAu.root" ){

	TFile *f = new TFile( n.c_str() );

	TH1 * h1=(TH1*)f->Get("wdeltaPhi_pd1_fold");
	TH1 * h0 = (TH1*)h1->Clone("h0");
	TH1 * h2=(TH1*)f->Get("wdeltaPhi_pd1");
	TH1 * h3=(TH1*)f->Get("wdeltaPhi_pd1_2fold");
	
	
	gStyle->SetOptFit(111);
	
	// gStyle->SetStatW(0.4);

	TCanvas *c1 = new TCanvas( "c1", "", 1200, 900 );
	h0->Draw("pe");
	TF1 * f0 = new TF1( "f2", "[0] + [1] * cos( 4 * x )" );
	h0->Fit( f0, "R", "", 0, 1.55 );

	TCanvas *c2 = new TCanvas( "c2", "", 1200, 900 );
	h1->Draw("pe");
	TAxis* a = h1->GetXaxis();
	a->SetLabelOffset(0.02);
	a->SetNdivisions(-502);
	a->ChangeLabel(2,-1,-1,-1,-1,-1,"#frac{#pi}{4}");
	a->ChangeLabel(-1,-1,-1,-1,-1,-1,"#frac{#pi}{2}");

	// TF1 * f1 = new TF1( "f2", "[0] + [1] * cos( 4 * x ) +  [2] * cos( 2*x )" );
	TF1 * f1 = new TF1( "f2", "[0] *( 1 + [1] * cos( 4 * x ) +  [2] * cos( 2*x ) )" );
	f1->SetParName( 1, "4 #phi (%)" );
	f1->SetParName( 2, "2 #phi (%)" );
	h1->Fit( f1, "R", "", 0, 1.55 );

	cout << "Asym: " << f1->GetParameter(1) / f1->GetParameter(0) << " +/- " << f1->GetParError(1) / f1->GetParameter(0) << endl;
	cout << "Relative Error: " << (f1->GetParError(1) / f1->GetParameter(0)) / (f1->GetParameter(1) / f1->GetParameter(0)) << endl;
	cout << "nSigma : " << (f1->GetParameter(1) / f1->GetParameter(0)) / (f1->GetParError(1) / f1->GetParameter(0)) << endl;

	c2->Print( "cos4phi.png" );
	c2->Print( "/Users/jdb/notable/attachments/upcee_deltaPhi_foldpi2.png" );

	TCanvas *c3 = new TCanvas( "c3", "", 1200, 900 );
	TF1 * f2 = new TF1( "f2", "[0] + [1] * cos( 4 * x ) + [2]*cos(2*x)" );
	// h2->Rebin(4);
	h2->Draw("pe");
	h2->Fit( f2, "R", "", -3.14, 3.14 );

	cout << "Asym: " << (f2->GetParameter(1) / f2->GetParameter(0)) << " +/- " << (f2->GetParError(1) / f2->GetParameter(0)) << endl;
	cout << "Relative Error: " << (f2->GetParError(1) / f2->GetParameter(0)) / (f2->GetParameter(1) / f2->GetParameter(0)) << endl;
	cout << "nSigma : " << (f2->GetParameter(1) / f2->GetParameter(0)) / (f2->GetParError(1) / f2->GetParameter(0)) << endl;


	TCanvas *c4 = new TCanvas( "c4", "", 1200, 900 );
	c4->SetBottomMargin( 0.15 );
	c4->SetLeftMargin( 0.15 );
	c4->SetRightMargin( 0.05 );
	gStyle->SetStatX(0.55);
	TF1 * f3 = new TF1( "f3", "[0] + [1] * cos( 4 * x )" );
	// h2->Rebin(4);
	h3->SetTitle( ";#phi^{ee} - #phi^{e}; dN/d#Delta#phi" );
	// h3->GetXaxis()->CenterTitle();
	h3->GetXaxis()->SetTitleOffset( 1.4 );
	h3->GetYaxis()->SetTitleOffset( 1.4 );

	f3->SetParName( 1, "4 #phi" );
	f3->SetParName( 2, "2 #phi" );
	h3->Draw("pe");
	h3->Fit( f3, "RE", "", 0, TMath::Pi()/4.0 );

	a = h3->GetXaxis();
	a->SetLabelOffset(0.02);
	a->SetNdivisions(-502);
	a->ChangeLabel(2,-1,-1,-1,-1,-1,"#frac{#pi}{8}");
	a->ChangeLabel(-1,-1,-1,-1,-1,-1,"#frac{#pi}{4}");



	cout << "Asym: " << (f3->GetParameter(1) / f3->GetParameter(0)) << " +/- " << (f3->GetParError(1) / f3->GetParameter(0)) << endl;
	cout << "Relative Error: " << (f3->GetParError(1) / f3->GetParameter(0)) / (f3->GetParameter(1) / f3->GetParameter(0)) << endl;
	cout << "nSigma : " << (f3->GetParameter(1) / f3->GetParameter(0)) / (f3->GetParError(1) / f3->GetParameter(0)) << endl;

	c4->Print( "/Users/jdb/notable/attachments/upcee_deltaPhi_foldpi4.png" );





	TCanvas *c5 = new TCanvas( "c5", "", 1200, 900 );
	c5->SetBottomMargin( 0.15 );
	c5->SetLeftMargin( 0.15 );
	c5->SetRightMargin( 0.05 );
	gStyle->SetStatX(0.55);
	TF1 * f4 = new TF1( "f4", "[0] *( 1 + [1] * cos( 4 * x ))" );
	// h2->Rebin(4);
	h3->SetTitle( ";#phi^{ee} - #phi^{e}; dN/d#Delta#phi" );
	// h3->GetXaxis()->CenterTitle();
	h3->GetXaxis()->SetTitleOffset( 1.4 );
	h3->GetYaxis()->SetTitleOffset( 1.4 );

	f4->SetParName( 1, "4 #phi (%)" );
	h3->Draw("pe");
	h3->Fit( f4, "RE", "", 0, TMath::Pi()/4.0 );

	a = h3->GetXaxis();
	a->SetLabelOffset(0.02);
	a->SetNdivisions(-502);
	a->ChangeLabel(2,-1,-1,-1,-1,-1,"#frac{#pi}{8}");
	a->ChangeLabel(-1,-1,-1,-1,-1,-1,"#frac{#pi}{4}");



	cout << "Asym: " << (f4->GetParameter(1) / f4->GetParameter(0)) << " +/- " << (f4->GetParError(1) / f4->GetParameter(0)) << endl;
	cout << "Relative Error: " << (f4->GetParError(1) / f4->GetParameter(0)) / (f4->GetParameter(1) / f4->GetParameter(0)) << endl;
	cout << "nSigma : " << (f4->GetParameter(1) / f4->GetParameter(0)) / (f4->GetParError(1) / f4->GetParameter(0)) << endl;

	c5->Print( "/Users/jdb/notable/attachments/upcee_deltaPhi_foldpi4_frac.png" );

}