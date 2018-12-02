


void fitPt2( int iSys = 0 ){


	TFile *tfin = NULL;

	if ( iSys == 0 )
		tfin = new TFile( "Run11AuAu.root" );
	else 
		tfin = new TFile( "Run12UU.root" );

	TH2 * h2 = (TH2*)tfin->Get( "pt2id2" );

	TAxis *ax = h2->GetXaxis();
	TH1 * h = h2->ProjectionY( "h1", ax->FindBin(0.4), ax->FindBin(0.76) );
	// TH1 * h = h2->ProjectionY( "h1", ax->FindBin(0.76), ax->FindBin(1.2) );
	// TH1 * h = h2->ProjectionY( "h1", ax->FindBin(1.2), ax->FindBin(2.6) );

	TF1 * ff = new TF1( "ff", "[0] * exp(  [1]*x )", 0.0005, 0.005 );

	h->Fit( ff, "R", "", 0.0002, 0.005 );

	// ff->SetRange( 0.0001, 0.01 );
	ff->SetRange( 0.0002, 0.005 );
	TH1 * hff = ff->GetHistogram();

	hff->Draw("same");
	cout << "sqrt(<pT^2>)" << sqrt( -1.0 / ff->GetParameter( 1 ) ) << endl;;

}