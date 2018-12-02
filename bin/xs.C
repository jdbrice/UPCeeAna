




void xs(){

	TCanvas * can = new TCanvas( "can", "", 1200, 900 );
	can->SetTopMargin( 0.05 );
	can->SetBottomMargin( 0.13 );
	can->SetRightMargin( 0.05 );


	gStyle->SetOptStat( 0 );
	gStyle->SetOptFit( 111 );
	TString Run = "Run10";
	// TFile * fData = new TFile( "Run10AuAu.root" );
	TFile * fData = new TFile( Form("%sAuAu.root", Run.Data() ) );
	// TFile * fData = new TFile( Form("%sUU.root", Run.Data() ) );


	double LUMI = 679262 * (0.801742919 );
	// factor of 0.801 comes from fact that I only analyzed ~80 of the triggered events

	TH2 * h2Mass = (TH2*)fData->Get( "wulsid2" );
	TH1 * hevents = (TH1*)fData->Get( "events" );

	TH2 * h2rapid2 = (TH2*)fData->Get( "wrapid2" );
	TH2 * h2pt2id2 = (TH2*)fData->Get( "wpt2id2" );

	TH2 * h2id = (TH2*)fData->Get( "ulsid" );
	TH2 * h2id2 = (TH2*)fData->Get( "ulsid2" );

	TH1 * hid = h2id->ProjectionX( "hid" );
	TH1 * hid2 = h2id2->ProjectionX( "hid2" );
	
	TH1 * hid2R = h2id2->ProjectionX( "hid2R" );
	TH1 * hidR = h2id->ProjectionX( "hidR" );

	hidR->Rebin(10);
	hid2R->Rebin(10);
	hidR->Sumw2();
	hid2R->Sumw2();
	hid2R->Divide( hidR );
	hid2R->GetXaxis()->SetTitle( "M_{ee} (GeV/c)^{2}" );
	hid2R->GetYaxis()->SetTitle( "#Delta#Delta TOF / #chi_{ee}" );
	hid2R->GetXaxis()->SetRangeUser(0.0, 1.5);
	hid2R->GetYaxis()->SetRangeUser(0.0, 1.1);
	hid2R->Fit( "pol0", "R", "", 0.4, 0.76 );
	// hid2R->Draw( "hpe" );


	can->Print( Form("%sAuAu_datadriven_ddTOF_eff.pdf", Run.Data() ) );
	can->Print( Form("%sAuAu_datadriven_ddTOF_eff.png", Run.Data() ) );
	can->Print( Form("%sAuAu_datadriven_ddTOF_eff.eps", Run.Data() ) );



	TFile *fSL = new TFile( "../../STARLight2PairDst/bin/batchAuAu0_starlight.root" );
	// TFile *fSL = new TFile( "../../STARLight2PairDst/bin/Run12UU_starlight.root" );
	
	TH1 * hSLmass = (TH1*)fSL->Get( "mass" );
	TH1 * hSLrap = (TH1*)fSL->Get( "y_m0" );
	TH1 * hSLPt = (TH1*)fSL->Get( "pT_m0" );
	TH1 * hSLPt2 = (TH1*)fSL->Get( "pT2_m0" );

	TH1 * hMass = h2Mass->ProjectionX("hMass", 1, h2Mass->GetYaxis()->FindBin( 0.200 ));

	TH1 * hrapid2 = h2rapid2->ProjectionY("hrapid2", h2rapid2->GetXaxis()->FindBin( 0.4 ), h2rapid2->GetXaxis()->FindBin( 0.76 ));
	TH1 * hpt2id2 = h2pt2id2->ProjectionY("hpt2id2", h2pt2id2->GetXaxis()->FindBin( 0.4 ), h2pt2id2->GetXaxis()->FindBin( 0.76 ));

	TH1 * hPt = h2Mass->ProjectionY("hPt", h2Mass->GetXaxis()->FindBin( 0.400 ), h2Mass->GetXaxis()->FindBin( 0.760 ));

	

	hSLmass->Rebin(2);
	hSLmass->Scale( 0.217568 / hSLmass->Integral(), "width" );
	hSLmass->SetLineColor(kRed);
	hSLmass->GetXaxis()->SetTitle( "M_{ee} (GeV/c^{2})" );
	hSLmass->GetYaxis()->SetTitle( "#frac{d#sigma(XnXn)}{dM} (mb)" );
	hSLmass->SetLineWidth(3);
	hSLmass->SetMaximum( 0.85 );
	hSLmass->Draw("hist l");



	hMass->Rebin(40);
	hMass->Scale( 1.08 / ( 0.6 ) ); // vtxLoss and vertex finding efficiency
	hMass->Scale( 2.395 ); // XnXn corr factor average RELDIS + STARLIGHT from PRC 96
	// hMass->Scale( 2.17 ); // XnXn corr factor  Landau extrapolation in PRC 96
	hMass->Scale( 1.0, "width" ); // bin width dm
	hMass->Scale( 1.0 / 0.97 ); // chi^2_ee Eff

	// hMass->Scale( 1.0 / 0.82 ); // tof PID Eff not applied, already included in the weighted spectra
	
	

	if ( "Run10" == Run ){
		hMass->Scale( 1.0 / LUMI ); // Lumi
	}

	if ( "Run12" == Run ){
		hMass->Scale( 1.0 / 274000.0 ); // Lumi
	}




	hMass->SetMarkerStyle( 21 );
	hMass->SetLineWidth(2);
	hMass->Draw("same");

	TLegend * leg = new TLegend( 0.40, 0.70, 0.945, 0.945 );
	leg->SetBorderSize(0);
	leg->AddEntry( hSLmass, "STARLight (#gamma#gamma#rightarrow e^{+}e^{-})", "l" );
	leg->AddEntry( hMass, "UPC Au+Au at #sqrt{s_{NN} } = 200 GeV", "pe" );
	leg->Draw();



	can->Print( Form("%sAuAu_dsigmadM_linear.pdf", Run.Data() ) );
	can->SetLogy(1);

	// hSLmass->GetXaxis()->SetRangeUser(0, 3);
	hSLmass->GetYaxis()->SetRangeUser(1e-3, 2);


	can->Print( Form("%sAuAu_dsigmadM_logy.pdf", Run.Data() ) );
	can->Print( Form("%sAuAu_dsigmadM_logy.png", Run.Data() ) );
	can->Print( Form("%sAuAu_dsigmadM_logy.eps", Run.Data() ) );

	can->Print( "Figure2a.pdf" );
	can->Print( "Figure2a.png" );
	can->Print( "Figure2a.eps" );


	can->SetLogy(0);
	//only in m0
	TAxis * slX = hSLmass->GetXaxis();
	float m0xs = 0.217568 * hSLmass->Integral( slX->FindBin( 0.4 ), slX->FindBin( 0.76 ) ) / hSLmass->Integral(); 
	hSLrap->Scale( m0xs / hSLrap->Integral(), "width" ); // scale to cross section
	hSLrap->SetLineColor(kRed);
	hSLrap->GetXaxis()->SetTitle( "y_{ee} (GeV/c^{2})" );
	hSLrap->GetYaxis()->SetTitle( "#frac{d#sigma(XnXn)}{dy^{ee}} (mb)" );
	hSLrap->SetLineWidth(3);
	hSLrap->SetMaximum( 0.85 );
	hSLrap->GetXaxis()->SetRangeUser( -1.2, 1.2 );
	hSLrap->GetYaxis()->SetTitleOffset( 0.8 );
	hSLrap->Draw("hist l");

	// hMass->Rebin(40);
	// hMass->Scale( 1.0 / hevents->GetBinContent(2) ); // Nevts
	// hMass->Scale( 1.0 / ((0.679 + 0.859)/2.0) ); // Lumi
	
	
	// if ( "Run11" == Run ){
	// 	hMass->Scale( 1.0 / 859000 ); // Lumi
	// }
	
	// hMass->Scale( 1.0 / 0.12 );
	hrapid2->Scale( 1.08 / ( 0.6 ) );
	// hrapid2->Scale( 0.217568 );
	hrapid2->Scale( 2.395 ); // XnXn corr factor average RELDIS + STARLIGHT from PRC 96
	// hrapid2->Scale( 2.17 ); // XnXn corr factor  Landau extrapolation in PRC 96
	hrapid2->Scale( 1.0, "width" ); // VtxLoss and dm
	hrapid2->Scale( 1.0 / 0.97 ); // chi^2_ee Eff
	// hrapid2->Scale( 1 / 1.12 );

	if ( "Run10" == Run ){
		hrapid2->Scale( 1.0 / LUMI ); // Lumi
	}

	if ( "Run12" == Run ){
		hrapid2->Scale( 1.0 / 274000.0 ); // Lumi
	}




	hrapid2->SetMarkerStyle( 21 );
	hrapid2->SetLineWidth(2);
	hrapid2->Draw("same");

	can->Print( Form("%sAuAu_dsigmady_linear.pdf", Run.Data() ) );
	can->Print( Form("%sAuAu_dsigmady_linear.png", Run.Data() ) );
	can->Print( Form("%sAuAu_dsigmady_linear.eps", Run.Data() ) );

	can->SetLogy(1);

	can->Print( Form("%sAuAu_dsigmady_logy.pdf", Run.Data() ) );
	can->Print( Form("%sAuAu_dsigmady_logy.png", Run.Data() ) );
	can->Print( Form("%sAuAu_dsigmady_logy.eps", Run.Data() ) );


	can->SetLogy(0);

	hSLPt->Scale( m0xs / hSLPt->Integral(), "width" ); // scale to cross section
	hSLPt->SetLineColor(kRed);
	hSLPt->GetXaxis()->SetTitle( "p_{T} (GeV/c)" );
	hSLPt->GetYaxis()->SetTitle( "#frac{d#sigma(XnXn)}{dp_{T}} (mb)" );
	hSLPt->GetYaxis()->SetTitleOffset(0.75);
	hSLPt->SetLineWidth(3);
	hSLPt->SetMaximum( 5.0 );
	hSLPt->GetXaxis()->SetRangeUser( 0, 0.2 );
	hSLPt->Draw("hist l");

	hPt->Rebin(5);
	hPt->Scale( 1.08 / ( 0.6 ) );
	// hPt->Scale( 0.217568 );
	hPt->Scale( 2.395 ); // XnXn corr factor average RELDIS + STARLIGHT from PRC 96
	// hPt->Scale( 2.17 ); // XnXn corr factor  Landau extrapolation in PRC 96
	hPt->Scale( 1.0, "width" ); // VtxLoss and dm
	hPt->Scale( 1.0 / 0.97 ); // chi^2_ee Eff
	// hPt->Scale( 1 / 1.12 );

	if ( "Run10" == Run ){
		hPt->Scale( 1.0 / LUMI ); // Lumi
	}
	if ( "Run12" == Run ){
		hPt->Scale( 1.0 / 274000.0 ); // Lumi
	}




	hPt->SetMarkerStyle( 21 );
	hPt->SetLineWidth(2);
	hPt->Draw("same");

	can->Print( Form("%sAuAu_dsigmadpT_linear.pdf", Run.Data() ) );
	can->Print( Form("%sAuAu_dsigmadpT_linear.png", Run.Data() ) );
	can->Print( Form("%sAuAu_dsigmadpT_linear.eps", Run.Data() ) );

	can->SetLogy(1);
	hSLPt->SetMaximum( 5.0 );
	hSLPt->SetMinimum( 1e-2 );
	hSLPt->GetXaxis()->SetRangeUser( 0, 0.2 );

	can->Print( Form("%sAuAu_dsigmadpT_logy.pdf", Run.Data() ) );


	/************************************************************************************************/


	can->SetLogy(1);
	hSLPt2->Scale( m0xs / hSLPt2->Integral(), "width" ); // scale to cross section
	hSLPt2->SetLineColor(kRed);
	hSLPt2->GetXaxis()->SetTitle( "p_{T}^{2} (GeV/c)^{2}" );
	hSLPt2->GetYaxis()->SetTitle( "#frac{d#sigma(XnXn)}{dp_{T}^{2} } (mb)" );
	hSLPt2->GetYaxis()->SetTitleOffset(0.75);
	hSLPt2->SetLineWidth(3);
	hSLPt2->SetMaximum( 3e2 );
	hSLPt2->SetMinimum( 2e-2 );
	hSLPt2->GetXaxis()->SetRangeUser( 0, 0.02 );
	hSLPt2->Draw("hist l");

	hpt2id2->Rebin(5);
	hpt2id2->Scale( 1.08 / ( 0.6 ) );
	hpt2id2->Scale( 2.395 ); // XnXn corr factor average RELDIS + STARLIGHT from PRC 96
	// hpt2id2->Scale( 2.17 ); // XnXn corr factor  Landau extrapolation in PRC 96
	hpt2id2->Scale( 1.0, "width" ); // VtxLoss and dm
	hpt2id2->Scale( 1.0 / 0.97 ); // chi^2_ee Eff

	if ( "Run10" == Run ){
		hpt2id2->Scale( 1.0 / LUMI ); // Lumi
	}

	if ( "Run12" == Run ){
		hpt2id2->Scale( 1.0 / 274000.0 ); // Lumi
	}




	hpt2id2->SetMarkerStyle( 21 );
	hpt2id2->SetLineWidth(2);
	hpt2id2->Draw("same");

	leg = new TLegend( 0.40, 0.70, 0.945, 0.945 );
	leg->SetBorderSize(0);
	leg->AddEntry( hSLPt2, "STARLight (#gamma#gamma#rightarrow e^{+}e^{-})", "l" );
	leg->AddEntry( hpt2id2, "UPC Au+Au at #sqrt{s_{NN} } = 200 GeV", "pe" );
	leg->Draw();

	can->Print( Form("%sAuAu_dsigmadpT2_logy.pdf", Run.Data() ) );
	can->Print( Form("%sAuAu_dsigmadpT2_logy.png", Run.Data() ) );
	can->Print( Form("%sAuAu_dsigmadpT2_logy.eps", Run.Data() ) );

	can->Print( "Figure2b.pdf" );
	can->Print( "Figure2b.png" );
	can->Print( "Figure2b.eps" );

}