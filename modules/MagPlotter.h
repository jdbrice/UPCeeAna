#ifndef MAG_PLOTTER_H
#define MAG_PLOTTER_H

#include "RooPlotLib.h"
#include "HistoAnalyzer.h"
#include "vendor/loguru.h"

#include "TLatex.h"
#include "TLegend.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TLine.h"

#include "FitConfidence.h"

class MagPlotter : public HistoAnalyzer
{
public:
	MagPlotter() {}
	~MagPlotter() {}

	virtual void initialize(){
		HistoAnalyzer::initialize();
	}

	virtual void make(){
		LOG_F( INFO, "make" );

		book->cd();

		gStyle->SetLineWidth(2);

		int Nbins = 500;
		TH1F * hAll = new TH1F( "bAll", ";#LTB^{2}#GT (fm^{-4}); #LTp_{T}^{2}#GT (MeV/c^{2})", Nbins, -5, 50 );
		TH1F * hAuAu = new TH1F( "bAuAu", ";#LTB^{2}#GT (fm^{-4}); #LTp_{T}^{2}#GT (MeV/c^{2})", Nbins, -5, 50 );
		TH1F * hUU = new TH1F( "bUU", ";#LTB^{2}#GT (fm^{-4}); #LTp_{T}^{2}#GT (MeV/c^{2})", Nbins, -5, 50 );

		TH1F * hAuAu6080 = new TH1F( "bAuAu6080", ";#LTB^{2}#GT (fm^{-4}); #LTp_{T}^{2}#GT (MeV/c^{2})", Nbins, -5, 50 );
		TH1F * hAuAu4060 = new TH1F( "bAuAu4060", ";#LTB^{2}#GT (fm^{-4}); #LTp_{T}^{2}#GT (MeV/c^{2})", Nbins, -5, 50 );
		TH1F * hUU6080   = new TH1F( "bUU6080", ";#LTB^{2}#GT (fm^{-4}); #LTp_{T}^{2}#GT (MeV/c^{2})", Nbins, -5, 50 );
		TH1F * hUU4060   = new TH1F( "bUU4060", ";#LTB^{2}#GT (fm^{-4}); #LTp_{T}^{2}#GT (MeV/c^{2})", Nbins, -5, 50 );
		TH1F * hUPC2004  = new TH1F( "bUPC2004", ";#LTB^{2}#GT (fm^{-4}); #LTp_{T}^{2}#GT (MeV/c^{2})", Nbins, -5, 50 );
		TH1F * hUPCAuAu  = new TH1F( "bUPCAuAu", ";#LTB^{2}#GT (fm^{-4}); #LTp_{T}^{2}#GT (MeV/c^{2})", Nbins, -5, 50 );
		TH1F * hUPCUU    = new TH1F( "bUPCUU", ";#LTB^{2}#GT (fm^{-4}); #LTp_{T}^{2}#GT (MeV/c^{2})", Nbins, -5, 50 );

		TH1F * hUPCJPsi    = new TH1F( "bUPCJPsi", ";#LTB^{2}#GT (fm^{-4}); #LTp_{T}^{2}#GT (MeV/c^{2})", Nbins, -5, 50 );
		TH1F * hUUJPsi    = new TH1F( "bUUJPsi", ";#LTB^{2}#GT (fm^{-4}); #LTp_{T}^{2}#GT (MeV/c^{2})", Nbins, -5, 50 );
		TH1F * hAuAuJPsi    = new TH1F( "bAuAuJPsi", ";#LTB^{2}#GT (fm^{-4}); #LTp_{T}^{2}#GT (MeV/c^{2})", Nbins, -5, 50 );

		TH1F * hZha    = new TH1F( "bZha", ";#LTB^{2}#GT (fm^{-4}); #LTp_{T}^{2}#GT (MeV/c^{2})", Nbins, -5, 50 );
		TH1F * hSLAuAu = new TH1F( "bSLAuAu", ";#LTB^{2}#GT (fm^{-4}); #LTp_{T}^{2}#GT (MeV/c^{2})", Nbins, -5, 50 );
		TH1F * hSLUU = new TH1F( "bSLUU", ";#LTB^{2}#GT (fm^{-4}); #LTp_{T}^{2}#GT (MeV/c^{2})", Nbins, -5, 50 );
		TH1F * hAllFit = new TH1F( "bAllFit", ";#LTB^{2}#GT (fm^{-4}); #LTp_{T}^{2}#GT (MeV/c^{2})", Nbins, -5, 50 );

		double vx[1], vy[1], ey[1], ex[1];
		vx[0] = 30.761675;
		vy[0] = 1849.8600;
		ey[0] = 194.4051;
		ex[0] = 5.0;

		TGraphErrors *gUU6080 = new TGraphErrors(1, vx, vy, ex, ey);


		// U+U 60-80%
		// <B^2> = 30.761675

		// Au+Au 60-80%
		// <B^2> = 33.076850

		TAxis* x = hUU6080->GetXaxis();
		// U+U in 60-80%
		hUU6080->SetBinContent( x->FindBin( 30.761675 ), 1849.8600 );
		hUU6080->SetBinError( x->FindBin( 30.761675 ), 194.4051 );
		// U+U in 40-60%
		hUU4060->SetBinContent( x->FindBin( 41.4 ), 2097.47 );
		hUU4060->SetBinError( x->FindBin( 41.4 ), 707.52 );

		// Au+Au in 60-80%
		hAuAu6080->SetBinContent( x->FindBin( 33.076850 ), 2586.7396 );
		hAuAu6080->SetBinError( x->FindBin( 33.076850 ), 255.31719 );
		// Au+Au in 40-60%
		hAuAu4060->SetBinContent( x->FindBin( 42.3 ), 2054.64 );
		hAuAu4060->SetBinError( x->FindBin( 42.3 ), 618.5 );

		// UPC 2004 Au+AU
		hUPC2004->SetBinContent( x->FindBin( 1.0 ), 1327.02 );
		hUPC2004->SetBinError( x->FindBin( 1.0 ), 429.388 );

		// UPC Au+Au (NEW)
		// 1439.602421220649+/-30.353674400000003
		hUPCAuAu->SetBinContent( x->FindBin( 1.3 ), 1439.602421220649 );
		hUPCAuAu->SetBinError( x->FindBin( 1.3 ), 30.353674400000003 );

		// UPC U+U (NEW)
		// 1266.2270341190558+/-32.0256756
		hUPCUU->SetBinContent( x->FindBin( 1.6 ), 1266.2270 );
		hUPCUU->SetBinError( x->FindBin( 1.6 ), 32.0256756 );

		hZha->SetBinContent( x->FindBin( 0.0 ), 1259.5401 );
		hZha->SetBinError( x->FindBin( 0.0 ), 0.001 );

		hSLAuAu->SetBinContent( x->FindBin( 0.0 ), 1398.76 );
		hSLAuAu->SetBinError( x->FindBin( 0.0 ), 0.001 );

		hSLUU->SetBinContent( x->FindBin( 0.0 ), 1169.64 );
		hSLUU->SetBinError( x->FindBin( 0.0 ), 0.001 );

		// 1127.952225+/-350.29155
		// 1015.0595999999999+/-173.637 // dEdx only
		//hUPCJPsi->SetBinContent( x->FindBin( 0.5 ), 1127.952225 );
		//hUPCJPsi->SetBinError( x->FindBin( 0.5 ), 350.29155 );

		// U+U J/Psi Wangmei
		//2070.25+/-500.5
		//hUUJPsi->SetBinContent( x->FindBin( 44 ), 2070.25 );
		//hUUJPsi->SetBinError( x->FindBin( 44 ), 500.5 );

		// Au+Au J/Psi Wangmei
		// 1406.25+/-187.5
		//hAuAuJPsi->SetBinContent( x->FindBin( 46 ), 1406.25 );
		//hAuAuJPsi->SetBinError( x->FindBin( 46 ), 187.5 );


		hAll->Add( hUU6080 );
		hAll->Add( hUU4060 );

		hAll->Add( hAuAu6080 );
		hAll->Add( hAuAu4060 );

		hAll->Add( hUPCUU );
		hAll->Add( hUPCAuAu );
		// hAll->Add( hUPC2004 );

		hAuAu->Add( hAuAu6080 );
		hAuAu->Add( hAuAu4060 );
		hAuAu->Add( hUPCAuAu );

		hUU->Add( hUU6080 );
		hUU->Add( hUU4060 );
		hUU->Add( hUPCUU );

		TF1 * ffAll = new TF1( "ffAll", "pol1" );
		ffAll->SetRange( 0, 50 );
		hAll->Fit( ffAll, "NR", "", 0, 50 );

		TF1 * ffAuAu = new TF1( "ffAuAu", "pol1" );
		ffAuAu->SetRange( 0, 50 );
		hAuAu->Fit( ffAuAu, "NR", "", 0, 50 );

		TH1 * hCLffAuAu = FitConfidence::fitCL( ffAuAu, "hCLffAuAu", .68, 500, 0, 50 );

		TF1 * ffUU = new TF1( "ffUU", "pol1" );
		ffUU->SetRange( 0, 50 );
		hUU->Fit( ffUU, "NR", "", 0, 50 );
		TH1 * hCLffUU = FitConfidence::fitCL( ffUU, "hCLffUU", .68, 500, 0, 50 );



		gStyle->SetOptStat(0);
		TCanvas *can = new TCanvas( "can", "", 950, 600 );
		can->SetTopMargin( 0.05 );
		can->SetBottomMargin( 0.12 );
		can->SetRightMargin( 0.05 );
		can->SetLeftMargin( 0.13 );


		hUU6080->SetMaximum( 3000 );
		hUU6080->SetMinimum( 1100 );
		
		RooPlotLib rpl;

		rpl.style( hUU6080 ) .set( config, "style.hUU6080" );
		rpl.style( hUU4060 ) .set( config, "style.hUU4060" );
		rpl.style( hAuAu4060 ) .set( config, "style.hAuAu4060" );
		rpl.style( hAuAu6080 ) .set( config, "style.hAuAu6080" );
		rpl.style( hUPC2004 ) .set( config, "style.hUPC2004" );
		rpl.style( hUPCUU ) .set( config, "style.hUPCUU" );
		rpl.style( hUPCAuAu ) .set( config, "style.hUPCAuAu" );
		rpl.style( hUPCJPsi ) .set( config, "style.hUPCJPsi" );
		rpl.style( hUUJPsi ) .set( config, "style.hUUJPsi" );
		rpl.style( hAuAuJPsi ) .set( config, "style.hAuAuJPsi" );
		rpl.style( hZha ) .set( config, "style.hZha" );
		rpl.style( hSLAuAu ) .set( config, "style.hSLAuAu" );
		rpl.style( hSLUU ) .set( config, "style.hSLUU" );

		rpl.style( ffAuAu ) .set( config, "style.ffAuAu" );
		rpl.style( hCLffAuAu ).set( config, "style.hCLffAuAu" );
		rpl.style( ffUU ) .set( config, "style.ffUU" );
		rpl.style( hCLffUU ).set( config, "style.hCLffUU" );



		hUU6080->Draw( "e" );
		hUU4060->Draw( "same e" );
		hAuAu4060->Draw( "same pe" );
		hAuAu6080->Draw( "same pe" );
		hUPC2004->Draw( "same pe" );
		hUPCUU->Draw( "same pe" );
		hUPCAuAu->Draw( "same pe" );
		hUPCJPsi->Draw( "same pe" );
		hUUJPsi->Draw( "same pe" );
		hAuAuJPsi->Draw( "same pe" );
		// hZha->Draw( "same pe" );
		// hSLAuAu->Draw( "same pe" );
		// hSLUU->Draw( "same pe" );

		TLine *tl = new TLine();
		
		if ( true == config.get<bool>( "drawSTARLight", false ) ){
			rpl.style( tl ).set( config, "style.hSLAuAu" );
			tl->DrawLine( -1, 1398.76, 0, 1398.76 );
			
			rpl.style( tl ).set( config, "style.hSLUU" );
			tl->DrawLine( -1, 1169.64, 0, 1169.64 );
		}


		// ffAll->Draw("same");
		if ( true == config.get<bool>( "drawFits", false ) ){
			ffAuAu->Draw("same");
			ffUU->Draw("same");

			hCLffAuAu->Draw("same E3");
			hCLffUU->Draw("same E3");
		}
		


		

		// gUU6080->Draw( "pE1" );

		TLatex lt;
		lt.SetTextFont(42);
		lt.SetTextSize(16.0 / 360.0);
		lt.DrawLatexNDC( 0.52, 0.22, "0.40 < M_{ee} < 0.76 GeV/c^{2}" );
		lt.DrawLatexNDC( 0.48, 0.17, "2004 UPC : 0.14 < M_{ee} < 0.265 GeV/c^{2}" );

		TLegend * leg1 = new TLegend( 0.15, 0.51, 0.60, 0.9 );
		leg1->SetNColumns(2);
		leg1->SetBorderSize(0);
		leg1->AddEntry( hUU6080, "60-80% U+U", "pE1" );
		leg1->AddEntry( hAuAu6080, "60-80% Au+Au", "pE1" );

		leg1->AddEntry( hUU4060, "40-60% U+U", "pE1" );
		leg1->AddEntry( hAuAu4060, "40-60% Au+Au", "pE1" );

		leg1->AddEntry( hUPCUU, "UPC U+U", "pE1" );
		leg1->AddEntry( hUPCAuAu, "UPC Au+Au", "pE1" );
		leg1->AddEntry( hUPC2004, "UPC Au+Au (2004)", "pE1" );
		// use the fit objects because they have the same color for now
		if ( true == config.get<bool>( "drawSTARLight", false ) ){
			leg1->AddEntry( hSLAuAu, "#splitline{#gamma#gamma #rightarrow ee}{(STARLight Au+Au)}", "l" );
			leg1->AddEntry( hSLUU, "#splitline{#gamma#gamma #rightarrow ee}{(STARLight U+U)}", "l" );
		}
		// leg1->AddEntry( hZha, "#gamma#gamma #rightarrow ee (Zha et al.)", "p" );
		leg1->Draw("Same");

		// TLegend * leg2 = new TLegend( 0.3, 0.2, 0.9, 0.3 );
		// leg2->SetNColumns(3);
		// leg2->SetBorderSize(0);
		// leg2->AddEntry( hUPCJPsi, "UPC J/#psi / 2", "pE1" );
		// leg2->AddEntry( hUUJPsi, "U+U J/#psi / 2 (Wangmei)", "pE1" );
		// leg2->AddEntry( hAuAuJPsi, "Au+Au J/#psi / 2 (Wangmei)", "pE1" );
		// leg2->Draw("same");


		if ( true == config.get<bool>( "drawFits", false ) ){
			TLegend * leg2 = new TLegend( 0.5, 0.2, 0.9, 0.3 );
			leg2->SetNColumns(2);
			leg2->SetBorderSize(0);
			leg2->AddEntry( hCLffAuAu, "Au+Au Fit #pm1#sigma", "lf" );
			leg2->AddEntry( hCLffUU, "U+U Fit #pm1#sigma", "lf" );
			// leg2->AddEntry( hUUJPsi, "U+U J/#psi / 2 (Wangmei)", "pE1" );
			// leg2->AddEntry( hAuAuJPsi, "Au+Au J/#psi / 2 (Wangmei)", "pE1" );
			leg2->Draw("same");
		}

		TString SLmod = "_SL";
		if ( false == config.get<bool>( "drawSTARLight", false ) ){
			SLmod = "";
		}
		TString fitmod = "_fit";
		if ( false == config.get<bool>( "drawFits", false ) ){
			fitmod = "";
		}

		
		can->Print( Form("meanpT2_vs_meanB2%s%s.pdf", SLmod.Data(), fitmod.Data()) );
		can->Print( Form("meanpT2_vs_meanB2%s%s.eps", SLmod.Data(), fitmod.Data()) );
		can->Print( Form("meanpT2_vs_meanB2%s%s.png", SLmod.Data(), fitmod.Data()) );
		



	}
	
};

#endif