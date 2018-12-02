


void make_ZDC_demo(){


	TChain *c = new TChain( "FemtoDst" );
	c->Add( "../../data/FemtoDst_Run14AuAuMid.root" );

	c->Draw( "mZDCEast : mZDCWest >>hZDCEastWest( 1300, 0, 1300, 1300, 0, 1300 )", "" );

	TH1 * hEW = (TH1*)gDirectory->Get( "hZDCEastWest" );

	TFile * f = new TFile( "ZDC_demo.root" , "RECREATE");
	hEW->Write();


}