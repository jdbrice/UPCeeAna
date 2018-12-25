#ifndef FITTER_H
#define FITTER_H

#include "HistoAnalyzer.h"
#include "vendor/loguru.h"

#include "RooPlotLib.h"
#include "TLatex.h"

class Fitter : public HistoAnalyzer
{
public:
	Fitter() {}
	~Fitter() {}

	double fitMin = 0;
	double fitMax = 0.1;


	virtual void initialize(){
		HistoAnalyzer::initialize();
	}


	TF1* expoFit( TH1 * h, float *mean, float *error ){

		TF1 * ff = new TF1( TString::Format( "%s_ff", h->GetName() ), "[0] * exp(  [1]*x )", 0.0015, 0.006 );
		h->Fit( ff, "R", "", 0.0005, 0.006 );

		*mean = sqrt( -1.0 / ff->GetParameter( 1 ) );
		cout << "mean = " << *mean << endl;
		*error = abs( sqrt( -1.0 / (ff->GetParameter( 1 ) + ff->GetParError( 1 ) ) ) - *mean );
		cout << "error = " << *error << endl;

		ff->Write();

		return ff;
	}

	void computeMean( TH1 * h, TF1 * ff, float *mean, float *error ){

		ff->SetRange( 0, 1000 );
		cout << "fit mean = " << sqrt(-1.0 / ff->GetParameter(1)) << endl;
		double wxs = 0;
		double ws = 0;
		// double n = 0;
		for ( int i= 1; i < h->GetXaxis()->GetNbins(); i++ ){
			double x = h->GetBinCenter( i );
			double bw = h->GetBinWidth( i );
			double w = h->GetBinContent( i );
			double wf = ff->Eval( x ) ;
			if ( x < 0.007 ){
				wxs += w * x;
				ws += w;
			} else {
				wxs += wf * x;
				ws += wf;
			}
			
		}

		*mean = sqrt(wxs / ws);

	}

	virtual void make(){
		LOG_F( INFO, "make" );

		book->cd();

		fitMin = config.get<double>( "p.fitRange:min", 0 );
		fitMax = config.get<double>( "p.fitRange:max", 0.1 );


		// TH1 * hms0 = get<TH1>( "hPt2Mass0" );
		// TH1 * hms1 = get<TH1>( "hPt2Mass1" );
		// TH1 * hms2 = get<TH1>( "hPt2Mass2" );

		// hms0->Rebin(2);
		// hms1->Rebin(2);
		// hms2->Rebin(2);

		TH2 * h2pt2 = get<TH2>( "pt2id2" );
		TString effMod = "raw";
		if ( config.get<bool>( "p.useEff", false ) ){
			h2pt2 = get<TH2>( "wpt2id2" );
			LOG_F( INFO, "Using efficiency corrected spectra" );
			effMod = "eff";
		}
		TAxis * ax = h2pt2->GetXaxis();
		TH1 *hms0 = h2pt2->ProjectionY( "hPt2Mass0", ax->FindBin( 0.4 ), ax->FindBin( 0.76 ) );
		TH1 *hms1 = h2pt2->ProjectionY( "hPt2Mass1", ax->FindBin( 0.76 ), ax->FindBin( 1.2 ) );
		TH1 *hms2 = h2pt2->ProjectionY( "hPt2Mass2", ax->FindBin( 1.2 ), ax->FindBin( 2.6 ) );
		// TH1 *hms1 = h2pt2->ProjectionY( "hPt2Mass1", ax->FindBin( 0.76 ), ax->FindBin( 1.2 ) );
		// TH1 *hms2 = h2pt2->ProjectionY( "hPt2Mass2", ax->FindBin( 1.2 ), ax->FindBin( 2.6 ) );

		float m0spt2 = 0;
		float m1spt2 = 0;
		float m2spt2 = 0;

		float m0spt2e = 0;
		float m1spt2e = 0;
		float m2spt2e = 0;

		TF1 * ff0 = expoFit( hms0, &m0spt2, &m0spt2e );
		TF1 * ff1 = expoFit( hms1, &m1spt2, &m1spt2e );
		TF1 * ff2 = expoFit( hms2, &m2spt2, &m2spt2e );

		float fm0spt2 = m0spt2;
		float fm1spt2 = m1spt2;
		float fm2spt2 = m2spt2;

		float fm0spt2e = m0spt2e;
		float fm1spt2e = m1spt2e;
		float fm2spt2e = m2spt2e;
		
		computeMean( hms0, ff0, &m0spt2, &m0spt2e );
		computeMean( hms1, ff1, &m1spt2, &m1spt2e );
		computeMean( hms2, ff2, &m2spt2, &m2spt2e );

		RooPlotLib rpl;

		TCanvas *can = new TCanvas( "can", "", 1900, 1200 );
		can->SetLeftMargin( 0.12 );
		can->SetRightMargin( 0.07 );
		can->SetBottomMargin( 0.14 );
		can->SetTopMargin( 0.05 );

		gStyle->SetOptStat(0);
		ff0->SetNpx( 5000 );
		rpl.style( hms0 ).set( config, "style.pt2" );
		hms0->Draw( "pe" );

		// ff0->SetRange( fitMin, fitMax );
		cout << "fitRange: "<< fitMin << ", " << fitMax << endl;
		// rpl.style( ff0 ).set( "line-color", "#F00" ).draw("same");

		ff0->SetRange( 0, 1 );
		rpl.style( ff0 ).set( "line-color", "#F00" ).set( "line-style", 2 ).draw("same");

		TLatex lt;
		lt.SetTextSize( 14 / 360.0 );
		lt.DrawLatexNDC( .5, .85, TString::Format( "0.4 < M_{ee} < 0.76 GeV/c^{2}") );
		lt.DrawLatexNDC( .5, .78, TString::Format( "fit #chi^2 / NDF = %0.3f / %0.1f = %0.3f", ff0->GetChisquare(), (float)ff0->GetNDF(), ff0->GetChisquare()/(float)ff0->GetNDF() ) );
		lt.DrawLatexNDC( .5, .7, TString::Format( "fit: #sqrt{<pT^{2}>} = %0.2f #pm %0.2f MeV/c", (1000*fm0spt2), (1000*fm0spt2e) ) );
		lt.DrawLatexNDC( .5, .63, TString::Format( "data+fit: #sqrt{<pT^{2}>} = %0.3f MeV/c", (1000*m0spt2) ) );
		gPad->SetLogy(1);
		can->Print( Form( "%s_%s_fit0.pdf", (config.get<string>("mod")+config.get<string>("ver")).c_str(), effMod.Data() ) );
		

		// Second mass bin
		ff1->SetNpx( 5000 );
		rpl.style( hms1 ).set( config, "style.pt2" );
		hms1->Draw( "pe" );

		ff1->SetRange( 0, 1 );
		rpl.style( ff1 ).set( "line-color", "#F00" ).set( "line-style", 2 ).draw("same");

		
		lt.SetTextSize( 14 / 360.0 );
		lt.DrawLatexNDC( .5, .85, TString::Format( "0.76 < M_{ee} < 1.2 GeV/c^{2}") );
		lt.DrawLatexNDC( .5, .78, TString::Format( "fit #chi^2 / NDF = %0.3f / %0.1f = %0.3f", ff1->GetChisquare(), (float)ff1->GetNDF(), ff1->GetChisquare()/(float)ff1->GetNDF() ) );
		lt.DrawLatexNDC( .5, .7, TString::Format( "fit: #sqrt{<pT^{2}>} = %0.2f #pm %0.2f MeV/c", (1000*fm1spt2), (1000*fm1spt2e) ) );
		lt.DrawLatexNDC( .5, .63, TString::Format( "data+fit: #sqrt{<pT^{2}>} = %0.3f MeV/c", (1000*m1spt2) ) );
		
		gPad->SetLogy(1);
		can->Print( Form( "%s_%s_fit1.pdf", (config.get<string>("mod")+config.get<string>("ver")).c_str(), effMod.Data() ) );


		can->Clear();

		// Third mass bin
		ff2->SetNpx( 5000 );
		rpl.style( hms2 ).set( config, "style.pt2" );
		hms2->Draw( "pe" );

		ff2->SetRange( 0, 1 );
		rpl.style( ff2 ).set( "line-color", "#F00" ).set( "line-style", 2 ).draw("same");

		
		lt.SetTextSize( 14 / 360.0 );
		lt.DrawLatexNDC( .5, .85, TString::Format( "1.2 < M_{ee} < 2.6 GeV/c^{2}") );
		lt.DrawLatexNDC( .5, .78, TString::Format( "fit #chi^2 / NDF = %0.3f / %0.1f = %0.3f", ff2->GetChisquare(), (float)ff2->GetNDF(), ff2->GetChisquare()/(float)ff2->GetNDF() ) );
		lt.DrawLatexNDC( .5, .7, TString::Format( "fit: #sqrt{<pT^{2}>} = %0.2f #pm %0.2f MeV/c", (1000*fm2spt2), (1000*fm2spt2e) ) );
		lt.DrawLatexNDC( .5, .63, TString::Format( "data+fit: #sqrt{<pT^{2}>} = %0.3f MeV/c", (1000*m2spt2) ) );
		// gPad->SetLogy(1);
		can->Update();
		can->Print( Form( "%s_%s_fit2.pdf", (config.get<string>("mod")+config.get<string>("ver")).c_str(), effMod.Data() ) );
		

		cout << "Mean pt2 = " << m0spt2 << ", fit = " << fm0spt2 << ", hist = " << hms0->GetMean() << endl;
		cout << "Mean pt2 = " << m1spt2 << ", fit = " << fm1spt2 << ", hist = " << hms1->GetMean() << endl;
		cout << "Mean pt2 = " << m2spt2 << ", fit = " << fm2spt2 << ", hist = " << hms2->GetMean() << endl;

		book->makeAll( config, nodePath + ".histograms" );
		TH1 * h = book->get( "meanPt2" );

		h->SetBinContent( 1, (m0spt2 * 1000) );
		h->SetBinContent( 2, (m1spt2 * 1000) );
		h->SetBinContent( 3, (m2spt2 * 1000) );

		h->SetBinError( 1, (fm0spt2e) * 1000 );
		h->SetBinError( 2, (fm1spt2e) * 1000 );
		h->SetBinError( 3, (fm2spt2e) * 1000 );

		TH1 * hm = book->get( "meanPt2Model" );
		hm->SetBinContent( 1, 35.4932 );
		hm->SetBinContent( 2, 41.4201 );
		hm->SetBinContent( 3, 46.468 );



	}
	
};

#endif