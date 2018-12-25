#ifndef ZDC_FITTER_UU_H
#define ZDC_FITTER_UU_H

#include "HistoAnalyzer.h"
#include "vendor/loguru.h"

#include "RooPlotLib.h"
#include "TLatex.h"
#include "TLine.h"
#include "TF2.h"

TF1 * fgnUU1 = nullptr;
TF1 * fgnUU2 = nullptr;
TF1 * fgnUU3 = nullptr;
TF1 * fgnUU4 = nullptr;
TF1 * fegnUU1 = nullptr;


Double_t expgauss( Double_t *x, Double_t *p ){
	double x0 = x[0];
	double A = p[0];
	double l = p[1];
	double s = p[2];
	double k = p[3];
	
	double N0 = A/exp( -0.5 * pow( (k), 2 ) );
	double N1 = A/exp( k*k/0.5 - k*k) ;
	if ( (x0 - l) / s < k ){
		
		return (N0) * exp( -0.5 * pow( (x0-l)/s, 2 ) );
	} else {
		return  (N1) * exp( k*k/0.5 - k *( (x0-l)/s ) );
	}
	return 0;
}

Double_t zdc_UU_multi_gaus(Double_t *x, Double_t *p){

	// if ( rejectPsi2S &&  x[0] > 3.6 && x[0] < 3.8 ){
	// 	TF1::RejectPoint();
	// 	return 0;
	// }

	double x0    = x[0];
	double A0    = p[0];
	double m0    = p[1];
	double sigma = p[2];
	double A1    = p[3];
	double m1    = p[4];
	double sigma1= p[5];
	double A2    = p[6];
	double m2    = p[7];
	double sigma2= p[8];
	double k2    = p[9];
	double p0    = p[10];

	fgnUU1->SetParameters( A0, m0, sigma );
	fgnUU2->SetParameters( A1, m1, sigma1 );
	// fgnUU3->SetParameters( A2, m2, sigma2 );
	fegnUU1->SetParameters( A2, m2, sigma2, k2 );
	
	return fgnUU1->Eval( x0 ) + fgnUU2->Eval( x0 ) + fegnUU1->Eval( x0 ) + p0;
}

Double_t zdc_UU_free_gaus(Double_t *x, Double_t *p){

	// if ( rejectPsi2S &&  x[0] > 3.6 && x[0] < 3.8 ){
	// 	TF1::RejectPoint();
	// 	return 0;
	// }

	double x0    = x[0];
	double A0    = p[0];
	double m0    = p[1];
	double sigma0= p[2];
	double A1    = p[3];
	double m1    = p[4];
	double sigma1= p[5];
	double A2    = p[6];
	double m2    = p[7];
	double sigma2= p[8];
	double A3    = p[9];
	double m3    = p[10];
	double sigma3= p[11];
	double A4    = p[12];
	double m4    = p[13];
	double sigma4= p[14];
	double k4= p[15];

	fgnUU1->SetParameters( A0, m0, sigma0 );
	fgnUU2->SetParameters( A1, m1, sigma1 );
	fgnUU3->SetParameters( A2, m2, sigma2 );
	fgnUU4->SetParameters( A3, m3, sigma3 );
	fegnUU1->SetParameters( A4, m4, sigma4, k4 );

	//expgauss( x, &p[9] )
	return fgnUU1->Eval( x0 ) + fgnUU2->Eval( x0 ) + fgnUU3->Eval( x0 ) + fgnUU4->Eval( x0 ) + fegnUU1->Eval( x0 );
}


class ZDCFitterUU : public HistoAnalyzer
{
public:
	ZDCFitterUU() {}
	~ZDCFitterUU() {}

	TCanvas * can = nullptr;
	TCanvas * can2 = nullptr;

	double lambda1 = -1;
	double sigma1 = -1;

	double lambda2 = -1;
	double sigma2 = -1;


	virtual void initialize(){
		HistoAnalyzer::initialize();

		fgnUU1 = new TF1( "fgnUU1", "gaus" );
		fgnUU2 = new TF1( "fgnUU2", "gaus" );
		fgnUU3 = new TF1( "fgnUU3", "gaus" );
		fgnUU4 = new TF1( "fgnUU4", "gaus" );

		fegnUU1 = new TF1( "fegnUU1", expgauss, 0, 400, 4 );

		fgnUU1->SetRange( 0, 1300 );
		fgnUU2->SetRange( 0, 1300 );
		fgnUU3->SetRange( 0, 1300 );
		fgnUU4->SetRange( 0, 1300 );
		fegnUU1->SetRange( 0, 1300 );

	}


	void fitZDC( string name, TH1 * h, string note = "" ){
		cout <<  "#####################################################" << endl;
		cout <<  "################" << name << ":" << note <<  endl;
		cout <<  "#####################################################" << endl;

		RooPlotLib rpl;
		rpl.link( &config );

		h->Sumw2();
		TF1 * fZDC = nullptr;
		TString fitName = Form( "%s_%s", name.c_str(), note.c_str() );
		int fitType = 0;
		// if ( "Run11AuAu" == config.get<string>("mod") )
		// 	fitType = 1;

		if ( 0 == fitType){
			fZDC = new TF1( fitName, zdc_UU_multi_gaus, 30, 1200, 11 );
			//                       0,   1,  2,     3,   4,     5,   6,     7,    8
			fZDC->SetParameters( 80000, 51, 5, 20000, 410, 60, 0.5 );

			fZDC->SetParLimits( 0, 0, 1e10 );
			fZDC->SetParLimits( 1, 40, 55 );
			fZDC->SetParLimits( 2, 2, 40 );
			
			fZDC->SetParLimits( 3, 0, 1e10 );
			fZDC->SetParLimits( 4, 100, 200 );
			fZDC->SetParLimits( 5, 20, 40 );

			fZDC->SetParLimits( 6, 0, 1e10 );
			fZDC->SetParLimits( 7, 100, 300 );
			fZDC->SetParLimits( 8, 20, 300 );
			fZDC->SetParLimits( 9, 0, 1000 );

			// if ( lambda1 > 0 )
			// 	fZDC->FixParameter( 1, lambda1 );
			// if ( sigma1 > 0 )
				// fZDC->FixParameter( 2, sigma1 );
			
			
			
			h->Fit( fZDC, "RNL", "", 30, 1200 );
			h->Fit( fZDC, "RN", "", 30, 1200 );
		}

		if ( 1 == fitType ){
			fZDC = new TF1( fitName, zdc_UU_free_gaus, 25, 1200, 16 );
			//                       0,   1,  2,     3,   4,     5,      6,  7,   8
			fZDC->SetParameters( 6690.0, 45, 5, 20000, 110,     20, 20000, 610, 40 );
			// fZDC->SetParameter( 9, 5000 );
			// fZDC->SetParameter( 10, 1200 );
			// fZDC->SetParameter( 11, 1200 );

			fZDC->SetParLimits( 0, 0, 1e10 );
			fZDC->SetParLimits( 1, 40, 55 );
			fZDC->SetParLimits( 2, 2, 15 );

			fZDC->SetParLimits( 3, 0, 1e10 );
			fZDC->SetParLimits( 4, 10, 30 );
			fZDC->SetParLimits( 5, 5, 30 );

			fZDC->SetParLimits( 6, 0, 1e10 );
			// fZDC->SetParLimits( 7, 150, 200 );
			fZDC->FixParameter( 7, 156 );
			// fZDC->SetParLimits( 8, 20, 100 );
			fZDC->FixParameter( 8, 60 );
			
			fZDC->SetParLimits( 9, 0, 1e10 );
			fZDC->SetParLimits( 10, 200, 300 );
			// fZDC->FixParameter( 10, 208 );
			// fZDC->SetParLimits( 11, 120, 150 );
			fZDC->FixParameter( 11, 120 );

			fZDC->SetParLimits( 12, 0, 1e10 );
			fZDC->SetParLimits( 13, 200, 900 );
			fZDC->SetParLimits( 14, 120, 150 );
			fZDC->SetParLimits( 15, 0, 500 );

			


			h->Fit( fZDC, "RNL", "", 35, 1200 );
			h->Fit( fZDC, "RN", "", 35, 1200 );
		}
		
		
		

		rpl.style( h ).set( "style.hist" );
		rpl.style( fZDC ).set( "style.fitsum" );
		rpl.style( fgnUU1 ).set( "style.fgnUU1" );
		rpl.style( fgnUU2 ).set( "style.fgnUU2" );
		rpl.style( fgnUU3 ).set( "style.fgnUU3" );
		rpl.style( fgnUU4 ).set( "style.fgnUU4" );
		rpl.style( fegnUU1 ).set( "style.fgnUU4" );

		TLine *lp0 = new TLine( 0, fZDC->GetParameter(10),1200, fZDC->GetParameter(10) );
		lp0->SetLineColor(kGray);
		

		fZDC->SetNpx(1200);
		fgnUU1->SetNpx(1200);
		fgnUU2->SetNpx(1200);
		fgnUU3->SetNpx(1200);
		fgnUU4->SetNpx(1200);
		fegnUU1->SetNpx(1200);

		h->SetTitle("");
		h->GetXaxis()->SetTitle( TString::Format("ADC %s", name.c_str()) );
		h->Draw("hist pe");
		// gPad->SetLogy(1);
		
		fgnUU1->Draw("same");
		fgnUU2->Draw("same");
		fgnUU3->Draw("same");
		// fgnUU4->Draw("same");

		lp0->Draw("same");
		
		fgnUU4->Draw("same");
		fegnUU1->Draw("same");
		fZDC->Draw("same");

		gPad->SetLogy(0);

		double hI = h->Integral( h->GetXaxis()->FindBin( 400 ), h->GetXaxis()->FindBin( 1200 ) );
		double fI = fegnUU1->Integral( 400, 1200 ) / h->GetBinWidth( 15 );
		LOG_F( INFO, "hI = %f", hI );
		LOG_F( INFO, "fI = %f", fI );


		// h->Draw("same pe");

		TLatex tl;
		tl.SetTextFont( 42 );
		tl.SetTextSize( 12 / 360.0 );
		if ( 0 == fitType ){
			tl.DrawLatexNDC( 0.6, 0.85, TString::Format( "A1 = %0.0f #pm %0.0f", fZDC->GetParameter( 0 ), fZDC->GetParError( 0 ) ) );
			tl.DrawLatexNDC( 0.6, 0.82, TString::Format(  "#lambda1 = %0.1f #pm %0.1f", fZDC->GetParameter( 1 ), fZDC->GetParError( 1 ) ) );
			tl.DrawLatexNDC( 0.6, 0.79, TString::Format( "#sigma1 = %0.1f #pm %0.1f", fZDC->GetParameter( 2 ), fZDC->GetParError( 2 ) ) );
			tl.DrawLatexNDC( 0.6, 0.76, TString::Format( "A2 = %0.0f #pm %0.0f", fZDC->GetParameter( 3 ), fZDC->GetParError( 3 ) ) );
			tl.DrawLatexNDC( 0.6, 0.73, TString::Format(  "#lambda2 = %0.1f #pm %0.1f", fZDC->GetParameter( 4 ), fZDC->GetParError( 4 ) ) );
			tl.DrawLatexNDC( 0.6, 0.70, TString::Format( "#sigma2 = %0.0f #pm %0.0f", fZDC->GetParameter( 5 ), fZDC->GetParError( 5 ) ) );
			tl.DrawLatexNDC( 0.6, 0.67, TString::Format(  "A3 = %0.1f #pm %0.1f", fZDC->GetParameter( 6 ), fZDC->GetParError( 6 ) ) );
			tl.DrawLatexNDC( 0.6, 0.64, TString::Format( "#lambda43 = %0.0f #pm %0.0f", fZDC->GetParameter( 7 ), fZDC->GetParError( 7 ) ) );
			tl.DrawLatexNDC( 0.6, 0.61, TString::Format(  "#sigma3 = %0.1f #pm %0.1f", fZDC->GetParameter( 8 ), fZDC->GetParError( 8 ) ) );
			tl.DrawLatexNDC( 0.6, 0.57, TString::Format(  "k3 = %0.3f #pm %0.3f", fZDC->GetParameter( 9 ), fZDC->GetParError( 9 ) ) );
			tl.DrawLatexNDC( 0.6, 0.54, TString::Format(  "p0 = %0.1f #pm %0.1f", fZDC->GetParameter( 10 ), fZDC->GetParError( 10 ) ) );

			tl.DrawLatexNDC( 0.6, 0.50, TString::Format("#chi^2 / ndf = %0.2f / %d = %0.2f", fZDC->GetChisquare(), fZDC->GetNDF(), fZDC->GetChisquare() / (float)fZDC->GetNDF() ) );

			if ( "" != note )
				tl.DrawLatexNDC( 0.6, 0.46, TString::Format(  "Other ZDC #approx %s", note.c_str() ) );
		}


		

		if ( 1 == fitType ){
			tl.DrawLatexNDC( 0.5, 0.85, TString::Format( "A1 = %0.1f #pm %0.1f", fZDC->GetParameter( 0 ), fZDC->GetParError( 0 ) ) );
			tl.DrawLatexNDC( 0.5, 0.82, TString::Format(  "#lambda1 = %0.1f #pm %0.1f", fZDC->GetParameter( 1 ), fZDC->GetParError( 1 ) ) );
			tl.DrawLatexNDC( 0.5, 0.79, TString::Format( "#sigma1 = %0.1f #pm %0.1f", fZDC->GetParameter( 2 ), fZDC->GetParError( 2 ) ) );
			tl.DrawLatexNDC( 0.5, 0.76, TString::Format( "A2 = %0.1f #pm %0.1f", fZDC->GetParameter( 3 ), fZDC->GetParError( 3 ) ) );
			tl.DrawLatexNDC( 0.5, 0.73, TString::Format(  "#lambda2 = %0.1f #pm %0.1f", fZDC->GetParameter( 4 ), fZDC->GetParError( 4 ) ) );
			tl.DrawLatexNDC( 0.5, 0.70, TString::Format( "#sigma2 = %0.1f #pm %0.1f", fZDC->GetParameter( 5 ), fZDC->GetParError( 5 ) ) );
			tl.DrawLatexNDC( 0.5, 0.67, TString::Format( "A3 = %0.1f #pm %0.1f", fZDC->GetParameter( 6 ), fZDC->GetParError( 6 ) ) );
			tl.DrawLatexNDC( 0.5, 0.64, TString::Format(  "#lambda3 = %0.1f #pm %0.1f", fZDC->GetParameter( 7 ), fZDC->GetParError( 7 ) ) );
			tl.DrawLatexNDC( 0.5, 0.61, TString::Format( "#sigma3 = %0.1f #pm %0.1f", fZDC->GetParameter( 8 ), fZDC->GetParError( 8 ) ) );
			// tl.DrawLatexNDC( 0.5, 0.58, TString::Format( "A4 = %0.1f #pm %0.1f", fZDC->GetParameter( 9 ), fZDC->GetParError( 9 ) ) );
			// tl.DrawLatexNDC( 0.5, 0.55, TString::Format(  "#lambda4 = %0.1f #pm %0.1f", fZDC->GetParameter( 10 ), fZDC->GetParError( 10 ) ) );
			// tl.DrawLatexNDC( 0.5, 0.52, TString::Format( "#sigma4 = %0.1f #pm %0.1f", fZDC->GetParameter( 11 ), fZDC->GetParError( 11 ) ) );
			tl.DrawLatexNDC( 0.5, 0.49, TString::Format("#chi^2 / ndf = %0.2f / %d = %0.2f", fZDC->GetChisquare(), fZDC->GetNDF(), fZDC->GetChisquare() / (float)fZDC->GetNDF() ) );

			if ( "" != note )
				tl.DrawLatexNDC( 0.5, 0.45, TString::Format(  "Other ZDC #approx %s", note.c_str() ) );
		}

		tl.SetTextSize( 18 / 360.0 );
		tl.DrawLatexNDC( 0.3, 0.92, config.get<string>("title").c_str() );
		tl.DrawLatexNDC( 0.6, 0.92, (name).c_str() );
		can->Print( TString::Format("%s_%s%sFit.pdf", config.get<string>( "mod" ).c_str(), name.c_str(), note.c_str() ) );


		h->GetXaxis()->SetRangeUser( 1, 150 );
		double cl = 31;
		TLine * cutLow = new TLine( cl, 0, cl, fZDC->GetParameter(0) );
		cutLow->SetLineColor( kGray + 2);
		cutLow->Draw("same");

		double ch = fZDC->GetParameter(1) + fZDC->GetParameter(2) * 2;
		TLine * cutHigh = new TLine( ch, 0, ch, fZDC->GetParameter(0) );
		cutHigh->SetLineColor( kGray + 2);
		cutHigh->Draw("same");

		can->Print( TString::Format("%s_%s%sFit_Selected.pdf", config.get<string>( "mod" ).c_str(), name.c_str(), note.c_str() ) );

		cout << "purity: " << fgnUU1->Integral(cl, ch) / fZDC->Integral( cl, ch ) << endl;
		cout << "efficiency: " << fgnUU1->Integral(cl, ch) / fgnUU1->Integral(0, 1000) << endl;


		cout << "Boundaries:" << endl;
		cout << "1n < " << (fZDC->GetParameter( 1 ) + fZDC->GetParameter( 4 ))/2.0 << endl;
		cout << "2n:" << (fZDC->GetParameter( 1 ) + fZDC->GetParameter( 4 ))/2.0 << " - " << (fZDC->GetParameter( 4 ) + fZDC->GetParameter( 6 ))/2.0 << endl;
		cout << "3n:" << (fZDC->GetParameter( 4 ) + fZDC->GetParameter( 6 ))/2.0 << " - " << (fZDC->GetParameter( 6 ) + fZDC->GetParameter( 8 ))/2.0 << endl;
		cout << "4n > " << (fZDC->GetParameter( 6 ) + fZDC->GetParameter( 8 ))/2.0 << endl;

		if ( "" == note ){
			lambda1 = fZDC->GetParameter(1);
			sigma1 = fZDC->GetParameter(2);
		}

		fZDC->Write();

	}


	// TH2 * cloneRange( TString n, TH2 * h2, double x1, double x2, double y1, double y2 ){

	// 	int bx1 = hEW->GetXaxis()->FindBin(x1);
	// 	int bx2 = hEW->GetXaxis()->FindBin(x2);

	// 	int by1 = hEW->GetYaxis()->FindBin(y1);
	// 	int by2 = hEW->GetYaxis()->FindBin(y2);


	// 	TH2 * h2o = new TH2( n, "", (bx2-bx1), x1, x2, (by2-by1), y1, y2 );


	// }


	virtual void make(){
		LOG_F( INFO, "make" );

		book->cd();

		// TH2 * hEW = get<TH2>( "ZDCEastWestAnalyzed" );
		TH2 * hEW = get<TH2>( "ZDCEastWest" );
		// 

		gStyle->SetOptStat(0);

		can = new TCanvas( "can1", "", 1600, 1200 );
		can->SetLeftMargin( 0.12 );
		can->SetRightMargin( 0.07 );
		can->SetBottomMargin( 0.12 );

		TH1 * h1W = hEW->ProjectionX( "h1W" );

		// make roughly 1n, 2n, 3n, 4n projs
		hEW->GetYaxis()->SetRangeUser( 0, 287 );
		TH1 * h1W1n = hEW->ProjectionX( "h1W1n" );
		hEW->GetYaxis()->SetRangeUser( 287, 528 );
		TH1 * h1W2n = hEW->ProjectionX( "h1W2n" );
		hEW->GetYaxis()->SetRangeUser( 528, 862 );
		TH1 * h1W3n = hEW->ProjectionX( "h1W3n" );
		hEW->GetYaxis()->SetRangeUser( 862, 1200 );
		TH1 * h1W4n = hEW->ProjectionX( "h1W4n" );

		h1W->Draw();
		can->Print( TString::Format("%s_ZDCWest.pdf", config.get<string>("mod").c_str() ) );

		hEW->GetYaxis()->SetRangeUser( 0, 1200 );
		TH1 * h1E = hEW->ProjectionY( "h1E" );

		// make roughly 1n, 2n, 3n, 4n projs
		hEW->GetXaxis()->SetRangeUser( 0, 287 );
		TH1 * h1E1n = hEW->ProjectionY( "h1E1n" );
		hEW->GetXaxis()->SetRangeUser( 287, 528 );
		TH1 * h1E2n = hEW->ProjectionY( "h1E2n" );
		hEW->GetXaxis()->SetRangeUser( 528, 862 );
		TH1 * h1E3n = hEW->ProjectionY( "h1E3n" );
		hEW->GetXaxis()->SetRangeUser( 862, 1200 );
		TH1 * h1E4n = hEW->ProjectionY( "h1E4n" );
		h1E->Draw();
		can->Print( TString::Format("%s_ZDCEast.pdf", config.get<string>("mod").c_str() ) );

		hEW->GetXaxis()->SetRangeUser( 0, 1200 );
		hEW->GetYaxis()->SetRangeUser( 0, 1200 );

		TH2 * hEWrb = (TH2*)hEW->Clone( "hEWrb" );
		// hEWrb->RebinX( 4 );
		// hEWrb->RebinY( 4 );
		hEWrb->Draw("colz");
		hEWrb->GetXaxis()->SetTitle( "ZDC East" );
		hEWrb->GetYaxis()->SetTitle( "ZDC West" );
		hEWrb->GetYaxis()->SetTitleOffset( 1.2 );
		hEWrb->SetTitle( config.get<string>( "title" ).c_str() );
		can->SetLeftMargin( 0.12 );
		can->SetRightMargin( 0.17 );
		can->SetBottomMargin( 0.12 );
		can->SetLogz(1);
		can->Print( TString::Format("%s_ZDCEastWest.png", config.get<string>("mod").c_str() ) );
		can->SetLogz(0);
		can->SetLeftMargin( 0.12 );
		can->SetRightMargin( 0.07 );
		can->SetBottomMargin( 0.12 );


		// hEWrb->GetXaxis()->SetRangeUser( 0, 300 );
		// hEWrb->GetYaxis()->SetRangeUser( 0, 300 );
		// hEWrb->Draw("colz");
		// can->Print( "ZDCEastWest1n1n.png" );


		int bx1 = hEW->GetXaxis()->FindBin(30);
		int bx2 = hEW->GetXaxis()->FindBin(140);

		int by1 = hEW->GetYaxis()->FindBin(30);
		int by2 = hEW->GetYaxis()->FindBin(130);

		cout << "x (30-140) = (" << bx1 << ", " << bx2 << ")" << endl;
		cout << "y (30-130) = (" << by1 << ", " << by2 << ")" << endl;

		double Ibc = hEW->Integral( bx1, bx2, by1, by2 );
		double Itotal = hEW->Integral(1, 30, 1, 30);

		cout << "Bin count 1n1n (30-140) x (30-130) : " << Ibc << endl;
		cout << "Bin count total: " << Itotal << endl;


		fitZDC( "ZDCEast", h1E );

		fitZDC( "ZDCEast", h1E1n, "1n" );
		fitZDC( "ZDCEast", h1E2n, "2n" );
		fitZDC( "ZDCEast", h1E3n, "3n" );

		lambda1 = -1;
		sigma1 = -1;

		fitZDC( "ZDCWest", h1W );
		fitZDC( "ZDCWest", h1W1n, "1n" );
		fitZDC( "ZDCWest", h1W2n, "2n" );
		fitZDC( "ZDCWest", h1W3n, "3n" );

		// fitZDC( "ZDCEast", h1E4n, "4n" );
		// cout << "East 1n Max = " << fgnUU1->GetParameter( 1 ) + fgnUU1->GetParameter( 2 ) * 3;
		
		// fitZDC( "ZDCWest", h1W4n, "4n" );
		// cout << "West 1n Max = " << fgnUU1->GetParameter( 1 ) + fgnUU1->GetParameter( 2 ) * 3;


	}
	
};

#endif