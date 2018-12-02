


void checkEff(){
	gStyle->SetOptStat(0);
	TCanvas * can0 = new TCanvas( "can", "", 1200, 900 );
	can0->SetTopMargin( 0.05 );
	can0->SetBottomMargin( 0.13 );
	can0->SetRightMargin( 0.05 );
	TFile *f = new TFile( "Run10AuAu.root" );


	TH2 * hulsid2 = (TH2*)f->Get( "ulsid2" );
	TH2 * hwulsid2 = (TH2*)f->Get( "wulsid2" );

	TH2 * hTpcEff = (TH2*)f->Get( "hTpcEff" );

	TH2 * hpt2id2 = (TH2*)f->Get( "pt2id2" );
	TH2 * hwpt2id2 = (TH2*)f->Get( "wpt2id2" );

	TH2 * hxeedTof = (TH2*)f->Get( "xeedTof" );

	int iMaxPt = hulsid2->GetYaxis()->FindBin( 0.150 );

	TH1 * hmass = hulsid2->ProjectionX("hmass", 1, iMaxPt);
	TH1 * hwmass = hwulsid2->ProjectionX("hwmass", 1, iMaxPt);


	int iMinMass = hulsid2->GetXaxis()->FindBin( 0.4 );
	int iMaxMass = hulsid2->GetXaxis()->FindBin( 0.76 );

	TH1 * hpt = hulsid2->ProjectionY("hpt", iMinMass, iMaxMass);
	TH1 * hwpt = hwulsid2->ProjectionY("hwpt", iMinMass, iMaxMass);

	TH1 * hpt2 = hpt2id2->ProjectionY("hpt2", iMinMass, iMaxMass);
	TH1 * hwpt2 = hwpt2id2->ProjectionY("hwpt2", iMinMass, iMaxMass);

	TH2 * hulsid = (TH2*)f->Get( "ulsid" );
	TH2 * hulsidtof = (TH2*)f->Get( "ulsidtof" );
	TH1 * h1ulsid = hulsid->ProjectionX( "h1ulsid", 1, iMaxPt );
	TH1 * h1ulsidtof = hulsidtof->ProjectionX( "h1ulsidtof", 1, iMaxPt );
	TH1 * h1ulsidtofpid = hulsid2->ProjectionX( "h1ulsidtofpid", 1, iMaxPt );

	// hpt->Rebin(20);
	// hwpt->Rebin(20);

	hmass->Rebin(20);
	hwmass->Rebin(20);

	hmass->Scale( 1.0 / hmass->Integral() );
	hwmass->Scale( 1.0 / hwmass->Integral() );
	hmass->SetLineColor(kBlack);
	hmass->SetMarkerColor(kBlack);
	hmass->SetMarkerStyle( 23 );
	hmass->Draw();
	hwmass->SetLineColor(kRed);
	hwmass->SetMarkerColor(kRed);
	hwmass->SetMarkerStyle( 29 );
	hwmass->Draw("same");

	TLegend * leg=new TLegend( 0.6, 0.6, 0.9, 0.9 );
	leg->SetBorderSize(0);
	leg->AddEntry( hmass, "Raw" );
	leg->AddEntry( hwmass, "Corrected" );
	leg->Draw("same");

	/**********************************************/
	can0->Print( "Run10AuAu_effCheck_mass.pdf" );

	TCanvas * can1 = new TCanvas( "can1", "", 1200, 900 );
	can1->SetTopMargin( 0.05 );
	can1->SetBottomMargin( 0.13 );
	can1->SetRightMargin( 0.05 );

	TH1 * hmassRatio = (TH1*)hwmass->Clone( "hmassRatio" );
	hmassRatio->Divide( hmass );
	hmassRatio->GetYaxis()->SetTitle( "Raw / Corrected (normalized)" );
	hmassRatio->Draw("hist");
	/**********************************************/
	can1->Print( "Run10AuAu_effCheck_massRatio.pdf" );


	TCanvas * can = new TCanvas( "can2", "", 1200, 900 );
	can->SetTopMargin( 0.05 );
	can->SetBottomMargin( 0.13 );
	can->SetRightMargin( 0.05 );

	hpt->Scale( 1.0 / hpt->Integral() );
	hwpt->Scale( 1.0 / hwpt->Integral() );
	hpt->GetXaxis()->SetRangeUser( 0, 0.15 );
	
	hpt->SetLineColor(kBlack);
	hpt->SetMarkerColor(kBlack);
	hpt->SetMarkerStyle( 23 );
	hpt->SetTitle( ";p_{T}^{ee} (GeV/c); dN/dp_{T}^{ee} (GeV/c)" );
	hpt->Draw();
	hwpt->SetLineColor(kRed);
	hwpt->SetMarkerColor(kRed);
	hwpt->SetMarkerStyle( 29 );
	hwpt->Draw("same");
	can->SetLogy(0);

	leg=new TLegend( 0.6, 0.6, 0.9, 0.9 );
	leg->SetBorderSize(0);
	leg->AddEntry( hpt, "Raw" );
	leg->AddEntry( hwpt, "Corrected" );
	leg->Draw("same");

	/**********************************************/
	can->Print( "Run10AuAu_effCheck_pt.pdf" );

	can = new TCanvas( "can3", "", 1200, 900 );
	can->SetTopMargin( 0.05 );
	can->SetBottomMargin( 0.13 );
	can->SetRightMargin( 0.05 );

	TH1 * hptRatio = (TH1*)hwpt->Clone( "hPTRatio" );
	hptRatio->Divide( hpt );
	can->SetLogy(0);

	hptRatio->SetTitle( ";p_{T}^{ee} (GeV/c); dN/dp_{T}^{ee} (GeV/c)" );
	hptRatio->GetYaxis()->SetTitle( "Raw / Corrected (normalized)" );
	hptRatio->GetXaxis()->SetRangeUser( 0, 0.150 );
	hptRatio->GetYaxis()->SetRangeUser( 0.8, 1.20 );
	hptRatio->Draw("hist");

	/**********************************************/
	can->Print( "Run10AuAu_effCheck_ptRatio.pdf" );


	can = new TCanvas( "can4", "", 1200, 900 );
	can->SetTopMargin( 0.05 );
	can->SetBottomMargin( 0.13 );
	can->SetRightMargin( 0.05 );

	hpt2->SetTitle( ";p_{T}^{2} (GeV/c)^{2}; dN/dp_{T}^{2} (GeV/c)^{-2}" );
	hpt2->Scale( 1.0 / hpt2->Integral() );
	hwpt2->Scale( 1.0 / hwpt2->Integral() );
	hpt2->GetXaxis()->SetRangeUser( 0, 0.03 );
	
	hpt2->SetLineColor(kBlack);
	hpt2->SetMarkerColor(kBlack);
	hpt2->SetMarkerStyle( 23 );
	hpt2->Draw();
	hwpt2->SetLineColor(kRed);
	hwpt2->SetMarkerColor(kRed);
	hwpt2->SetMarkerStyle( 29 );
	hwpt2->Draw("same");
	can->SetLogy(1);

	leg=new TLegend( 0.6, 0.6, 0.9, 0.9 );
	leg->SetBorderSize(0);
	leg->AddEntry( hpt2, "Raw" );
	leg->AddEntry( hwpt2, "Corrected" );
	leg->Draw("same");

	/**********************************************/
	can->Print( "Run10AuAu_effCheck_pt2.pdf" );

	can = new TCanvas( "can5", "", 1200, 900 );
	can->SetTopMargin( 0.05 );
	can->SetBottomMargin( 0.13 );
	can->SetRightMargin( 0.05 );

	TH1 * hpt2Ratio = (TH1*)hwpt2->Clone( "hpt2Ratio" );
	hpt2Ratio->Divide( hpt2 );

	can->SetLogy(0);

	hpt2Ratio->GetXaxis()->SetRangeUser( 0, 0.025 );
	hpt2Ratio->GetYaxis()->SetRangeUser( 0.8, 1.20 );
	// hpt2Ratio->Fit( "pol1", "R", "", 0, 0.15 );
	hpt2Ratio->GetYaxis()->SetTitle( "Raw / Corrected (normalized)" );
	hpt2Ratio->Draw("hist");

	/**********************************************/
	can->Print( "Run10AuAu_effCheck_pt2Ratio.pdf" );

	can = new TCanvas( "can6", "", 1200, 900 );
	can->SetTopMargin( 0.05 );
	can->SetBottomMargin( 0.13 );
	can->SetRightMargin( 0.13 );
	
	hTpcEff->GetXaxis()->SetTitle( "p_{T}^{ee} (GeV/c)" );
	hTpcEff->GetYaxis()->SetTitle( "M_{ee} (GeV/c^{2})" );
	hTpcEff->SetTitle( "" );
	hTpcEff->GetYaxis()->SetRangeUser( 0, 2.6 );
	hTpcEff->GetXaxis()->SetRangeUser( 0, 3 );
	hTpcEff->Draw("colz");

	can->Print( "tpcEffRun10AuAu.png" );


	/**********************************************/
	TH1 * h1xeedTof = hxeedTof->ProjectionX("h1xeedTof");
	h1xeedTof->GetXaxis()->SetRangeUser( 0, 20 );
	TF1 * fExpo = new TF1( "expo", "expo", 0, 3 );
	h1xeedTof->Fit(fExpo, "R", "", 0, 3);
	h1xeedTof->GetXaxis()->SetTitle( "#chi^{2}_{ee}" );
	h1xeedTof->GetYaxis()->SetTitle( "Counts" );
	h1xeedTof->SetTitle("");
	h1xeedTof->SetLineWidth( 2 );
	h1xeedTof->Draw( "pe" );

	TLatex tl;
	tl.SetTextFont(42);
	tl.SetTextSize( 18 / 360.0 );
	tl.DrawLatexNDC( 0.4, 0.8, "f = A e^{#chi^{2} / B}" );
	tl.DrawLatexNDC( 0.4, 0.75, Form( "#chi^{2} / ndof = %.1f / %d = %.1f", fExpo->GetChisquare(), fExpo->GetNDF(), (fExpo->GetChisquare() / (float)fExpo->GetNDF()) ) );
	tl.DrawLatexNDC( 0.4, 0.70, Form( "#varepsilon(#chi^{2}_{ee}<5) = %0.2f", (fExpo->Integral( 0, 5 ) / fExpo->Integral( 0, 10 )) ) );

	fExpo->SetLineWidth(3);

	fExpo->DrawClone("same");
	fExpo->SetLineStyle( kDashed );
	fExpo->SetRange( 0, 20 );
	// fExpo->SetLineWidth(2);
	fExpo->DrawClone("same");
	can->SetLogy(1);
	can->Print( "chieeEff.pdf" );


	/**********************************************/

	can->SetLogy(0);
	h1ulsid->Sumw2();
	h1ulsidtof->Sumw2();
	h1ulsid->Rebin(20);
	h1ulsidtof->Rebin(20);
	h1ulsidtof->Divide( h1ulsid );
	h1ulsidtof->GetYaxis()->SetTitle( "(TOFMatch && Valid TOF ) / ( TOFMatch )" );
	TF1 * fpol0 = new TF1( "fpol0", "pol0", 0, 5 );
	h1ulsidtof->Fit("fpol0");
	
	h1ulsidtof->Draw( "hist" );
	tl.DrawLatexNDC( 0.17, 0.90, Form( "#varepsilon = %0.2f #pm %0.2f", fpol0->GetParameter(0), fpol0->GetParError(0) ) );
	fpol0->Draw("same");
	can->Print( "tofCalibEff.pdf" );

	/**********************************************/
	can->SetLogy(0);
	h1ulsid->Sumw2();
	h1ulsidtofpid->Sumw2();
	h1ulsidtofpid->Rebin(20);
	h1ulsidtofpid->Divide( h1ulsid );
	h1ulsidtofpid->GetYaxis()->SetTitle( "(TOFMatch && Valid TOF && PID ) / ( TOFMatch )" );
	fpol0 = new TF1( "fpol0", "pol0", 0, 5 );
	h1ulsidtofpid->Fit("fpol0");
	
	h1ulsidtofpid->Draw( "hist" );
	tl.DrawLatexNDC( 0.17, 0.90, Form( "#varepsilon = %0.2f #pm %0.2f", fpol0->GetParameter(0), fpol0->GetParError(0) ) );
	fpol0->Draw("same");
	can->Print( "tofCalibPidEff.pdf" );


}