#ifndef ANALYZER_H
#define ANALYZER_H


#include "TreeAnalyzer.h"
#include "XmlRange.h"
#include "RooPlotLib.h"
#include "Reporter.h"
#include "FitConfidence.h"
#include "HistoBins.h"

#include "vendor/loguru.h"

#include "TNamed.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TGraphErrors.h"
#include "TLatex.h"

#include "TRandom3.h"


#include "FemtoDstFormat/BranchReader.h"
#include "FemtoPairFormat/FemtoPair.h"

#include <algorithm>
#define _USE_MATH_DEFINES
#include <math.h>


class Analyzer : public TreeAnalyzer
{
protected:

	BranchReader<FemtoPair> _fpr;
	float dTofCut = 0.2;
	float XeeXpipi = 5;

	float XeeCut = 0.2;
	float XpipiCut = 0.0;
	float ScaleFactor = 1.0;

	float ZDCMin = 0;
	float ZDCMax = 0;

	float ZDCEastMin = 0;
	float ZDCEastMax = 0;
	float ZDCWestMin = 0;
	float ZDCWestMax = 0;

	TH2 * hEffRc = nullptr;
	TH2 * hEffMc = nullptr;
	TH2 * hEff   = nullptr;
	TH2 * hRapEff  = nullptr;
	TH2 * hCosThetaEff  = nullptr;
	TH3 * hEff3D  = nullptr;

	TH2 * hSLEff   = nullptr;

	TH1 * hSampleMassEff = nullptr;
	TH1 * hSampleMassEffw = nullptr;

	TH1 * hVPMassEff = nullptr;
	TH1 * hSLMassEff = nullptr;


	// Tracking cuts
	int min_nHitsFit  = 20;
	int min_nHitsDedx = 10;
	float max_Dca = 1.0;

	

public:

	const int DEBUG = 1;
	Analyzer() {}
	~Analyzer() {}

	virtual void initialize(){
		TreeAnalyzer::initialize();

		this->_fpr.setup( this->chain, "Pairs" );

		dTofCut = config.get<float>( "p.dTofCut", 0.2 );
		XeeXpipi = config.get<float>( "p.XeeXpipi", 5 );

		XeeCut = config.get<float>( "p.XeeCut", 5 );
		XpipiCut = config.get<float>( "p.XpipiCut", 0 );

		ZDCEastMin = config.get<float>( "p.ZDCEast:min", 50 );
		ZDCEastMax = config.get<float>( "p.ZDCEast:max", 1200 );

		ZDCWestMin = config.get<float>( "p.ZDCWest:min", 50 );
		ZDCWestMax = config.get<float>( "p.ZDCWest:max", 1200 );

		// string ZDCMode = config.get<string>( "p.ZDCMode", "all" );
		// ZDCMin = 50;
		// ZDCMax = 1200;
		// if ( "1n1n" == ZDCMode ){
		// 	ZDCMax = 300;
		// } else if ( "XnXn" == ZDCMode ){
		// 	ZDCMin = 300;
		// }

		LOG_F( INFO, "dTofCut = %f", dTofCut );
		
		LOG_F( INFO, "XeeXpipi = %f", XeeXpipi );
		LOG_F( INFO, "XeeCut = %f", XeeCut );
		// LOG_F( INFO, "XpipiCut = %f", XpipiCut );

		// LOG_F( INFO, "ZDC Cuts = ( %f, %f )", ZDCMin, ZDCMax );
		LOG_F( INFO, "ZDCEast Cuts = ( %f, %f )", ZDCEastMin, ZDCEastMax );
		LOG_F( INFO, "ZDCWest Cuts = ( %f, %f )", ZDCWestMin, ZDCWestMax );
		LOG_F( INFO, "1.0/ScaleFactor( %s ) = %f", config.get<string>("mod").c_str(), 1.0 / ScaleFactor );

		gRandom = new TRandom3();
		gRandom->SetSeed( 0 );

		min_nHitsFit  = config.get<int>( "p.min_nHitsFit", 20 );
		min_nHitsDedx = config.get<int>( "p.min_nHitsDedx", 10 );
		max_Dca       = config.get<float>( "p.max_Dca", 1.0 );
		
		LOG_F( INFO, "min_nHitsFit = %d" , min_nHitsFit  );
		LOG_F( INFO, "min_nHitsDedx = %d" , min_nHitsDedx  );
		LOG_F( INFO, "max_Dca = %f", max_Dca );
		

		TFile *f = new TFile( "/Users/jdb/bnl/work/upc/data/Cen60_80_VP_pairEff.root" );
		hEffMc = (TH2*)f->Get("hMCAcc1virtualphotoneehist");
		hEffRc = (TH2*)f->Get("hRCvirtualphotoneehistRun10");
		hEff = (TH2*)hEffRc->Clone( "hTpcEff" );
		hEff->Divide( hEffMc );

		TH1 * hVPMassEffRc = hEffRc->ProjectionY( "hVPMassEffRc", hEffRc->GetXaxis()->FindBin(0.050), hEffRc->GetXaxis()->FindBin(0.150) );
		TH1 * hVPMassEffMc = hEffMc->ProjectionY( "hVPMassEffMc", hEffMc->GetXaxis()->FindBin(0.050), hEffMc->GetXaxis()->FindBin(0.150) );
		hVPMassEff = (TH1*)hVPMassEffRc->Clone( "hVPMassEff" );
		hVPMassEff->Divide( hVPMassEffMc );

		TFile *fSLEff = new TFile( "/Users/jdb/bnl/work/upc/data/Cen60_80_GammaGamma_pairEff.root" );
		TH2 * hSLEffMc = (TH2*)fSLEff->Get("hMCAcc1gammagammaeehist");
		TH2 * hSLEffRc = (TH2*)fSLEff->Get("hRCgammagammaeehistRun10");
		hSLEff = (TH2*)hSLEffRc->Clone( "hSLEff" );
		hSLEff->Divide( hSLEffMc );

		TH1 * hSLMassEffRc = hSLEffRc->ProjectionY( "hSLMassEffRc", hSLEffRc->GetXaxis()->FindBin(0.050), hSLEffRc->GetXaxis()->FindBin(0.150) );
		TH1 * hSLMassEffMc = hSLEffMc->ProjectionY( "hSLMassEffMc", hSLEffMc->GetXaxis()->FindBin(0.050), hSLEffMc->GetXaxis()->FindBin(0.150) );
		hSLMassEff = (TH1*)hSLMassEffRc->Clone( "hSLMassEff" );
		hSLMassEff->Divide( hSLMassEffMc );

		LOG_F( INFO, "Making 3D eff factor" );
		TFile *fRap = new TFile( "/Users/jdb/bnl/work/upc/data/lowPt_EffvsRapidity_Cen6080.root" );
		TH3 * hRap3EffMc = (TH3*)fRap->Get("hMCAcc1MeevsPtvsRapidity_loweePt");
		TH3 * hRap3EffRc = (TH3*)fRap->Get("hRCAcc1MeevsPtvsRapidityRun10_loweePt");
		LOG_F( INFO, "3D eff tables: %p, %p", hRap3EffMc, hRap3EffRc );
		TH2 * hRap2EffMc = (TH2*)hRap3EffMc->Project3D("xy")->Clone("hRap2EffMc");
		TH2 * hRap2EffRc = (TH2*)hRap3EffRc->Project3D("xy")->Clone("hRap2EffRc");

		// 2D histo is (pT, rap) = (x, y)
		hRapEff = (TH2*)hRap2EffRc->Clone( "hTpcEffRap" );
		hRapEff->Divide( hRap2EffMc );

		// 3D histo is (rap, pT, mass) = (x, y, z)
		hEff3D = (TH3*)hRap3EffRc->Clone("hEff3D");
		hEff3D->Divide( hRap3EffMc );

		TH3 * hCosThetaEffMc = (TH3*)fRap->Get("hMCAcc1CosThetavsMee_loweePt");
		TH3 * hCosThetaEffRc = (TH3*)fRap->Get("hRCAcc1CosThetavsMeeRun10_loweePt");
		LOG_F( INFO, "CosTheta eff tables: %p, %p", hCosThetaEffMc, hCosThetaEffRc );

		hCosThetaEff = (TH2*)hCosThetaEffRc->Clone( "hTpcEffCosTheta" );
		hCosThetaEff->Divide( hCosThetaEffMc );
		
		book->cd();

		hVPMassEff->Write();
		hSLMassEff->Write();

		hSampleMassEff = (TH1*)hSLMassEff->Clone( "hSampleMassEff" );
		hSampleMassEff->Reset();
		hSampleMassEffw = (TH1*)hSLMassEff->Clone( "hSampleMassEffw" );
		hSampleMassEffw->Reset();

		hEffMc->Write();
		hEffRc->Write();
		hEff->Write();
	}
protected:


	float tpcEfficiencyWeight( float p, float m ){

		TAxis * ax = hEff->GetXaxis();
		TAxis * ay = hEff->GetYaxis();

		int ip = ax->FindBin( p );
		int im = ay->FindBin( m );

		float v = hEff->GetBinContent( ip, im );
		if ( 0 == v || 1.0/v != 1.0/v )
			return 0;

		hSampleMassEff->Fill( m, v );
		hSampleMassEffw->Fill( m );

		// cout << "Eff( m="<<m << ", p=" << p << " ) = " << v << endl;

		return 1.0 / ( v );

	}

	float tpcEfficiencyWeight( float m ){

		TAxis * ax = hVPMassEff->GetXaxis();

		int im = ax->FindBin( m );

		float v = hVPMassEff->GetBinContent( im );
		if ( 0 == v || 1.0/v != 1.0/v )
			return 0;

		// cout << "E1D (pT = " << pt << " ) = " << v << endl;

		return 1.0 / ( v );

	}

	float tpcEfficiencyWeightSL( float pt ){

		TAxis * ax = hSLMassEff->GetXaxis();

		int ipt = ax->FindBin( pt );

		float v = hSLMassEff->GetBinContent( ipt );
		if ( 0 == v || 1.0/v != 1.0/v )
			return 0;

		return 1.0 / ( v );

	}

	float tpcEfficiencyWeightSL( float p, float m ){

		TAxis * ax = hSLEff->GetXaxis();
		TAxis * ay = hSLEff->GetYaxis();

		int ip = ax->FindBin( p );
		int im = ay->FindBin( m );

		float v = hSLEff->GetBinContent( ip, im );
		if ( 0 == v || 1.0/v != 1.0/v )
			return 0;

		return 1.0 / ( v );

	}


	float tpcEfficiencyWeightCosTheta( float m, float costheta ){

		TAxis * ax = hCosThetaEff->GetXaxis();
		TAxis * ay = hCosThetaEff->GetYaxis();

		int ix = ax->FindBin( m );
		int iy = ay->FindBin( costheta );

		float v = ( hCosThetaEff->GetBinContent( ix, iy ) );
		if ( 0 == v || 1.0/v != 1.0/v )
			return 0;

		return 1.0 / v;

	}

	float tpcEfficiencyWeight( float p, float m, float y ){

		TAxis * ax = hEff3D->GetXaxis();
		TAxis * ay = hEff3D->GetYaxis();
		TAxis * az = hEff3D->GetZaxis();

		int iX = ax->FindBin( y );
		int iY = ay->FindBin( p );
		int iZ = az->FindBin( m );

		float v = ( hEff3D->GetBinContent( iX, iY, iZ ) );
		if ( 0 == v || 1.0/v != 1.0/v )
			return 0;
		return 1.0 / ( hEff3D->GetBinContent( iX, iY, iZ ) );

	}

	virtual void analyzeEvent(){
		FemtoPair * pair = this->_fpr.get();

		TLorentzVector lv1, lv2, lv;
		lv1.SetPtEtaPhiM( pair->d1_mPt, pair->d1_mEta, pair->d1_mPhi, 0.0005109989461 );
		lv2.SetPtEtaPhiM( pair->d2_mPt, pair->d2_mEta, pair->d2_mPhi, 0.0005109989461 );
		lv = lv1 + lv2;

		double c_light = 29.9792458; // m / ns
		double m_electron = 0.0005109990615;
		// double m_electron = 0.0005109990615;
		// double m_electron = 0.139;

		
		book->fill( "ZDCEast", pair->mZDCEast );
		book->fill( "ZDCWest", pair->mZDCWest );
		book->fill( "ZDCEastWest", pair->mZDCEast, pair->mZDCWest );
		// if ( pair->mZDCEast < ZDCEastMin || pair->mZDCEast > ZDCEastMax || pair->mZDCWest < ZDCWestMin || pair->mZDCWest > ZDCWestMax ) return;
		// if ( abs(pair->mVertexZ) > 50 ) return;
		book->fill( "ZDCEastWestSelected", pair->mZDCEast, pair->mZDCWest );

		if ( fabs(pair->mVertexZ) > 100 ) return;
		// if ( fabs(pair->mVertexZ) > 30 ) return;

		book->fill( "events", 1 );
		if ( pair->mGRefMult > 4 ) return;
		book->fill( "events", 2 );

		// if ( pair->d1_mMatchFlag == 0 || pair->d2_mMatchFlag == 0 ) return;
		if ( pair->d1_mPt  < 0.200 || pair->d2_mPt < 0.200 || abs( pair->d1_mEta ) > 1.0 || abs( pair->d2_mEta ) > 1.0 ) return;
		// if ( abs( pair->d1_mEta ) > 1.0 || abs( pair->d2_mEta ) > 1.0 ) return;
		
		if ( pair->d1_mNHitsFit < min_nHitsFit || pair->d2_mNHitsFit < min_nHitsFit ) return;
		if ( pair->d1_mNHitsDedx < min_nHitsDedx || pair->d2_mNHitsDedx < min_nHitsDedx ) return;
		
		if ( pair->d1_mDCA > max_Dca ) return; 
		if ( pair->d2_mDCA > max_Dca ) return; 

		book->fill( "events", 3 );

		if ( abs(lv.Rapidity()) > 1 ) return;
		book->fill( "events", 4 );

		double xpipi = pow( pair->d1_mNSigmaPion, 2 ) + pow( pair->d2_mNSigmaPion, 2 );
		double xee   = pow( pair->d1_mNSigmaElectron, 2 ) + pow( pair->d2_mNSigmaElectron, 2 );

		double dTof = pair->d1_mTof - pair->d2_mTof;
		double dLen = (pair->d1_mLength ) - (pair->d2_mLength ) ;

		double p1 = lv1.P();
		double p2 = lv2.P();
		double l1 = pair->d1_mLength;// + gRandom->Gaus(0, 10);
		double l2 = pair->d2_mLength;// + gRandom->Gaus(0, 10);
		double tofe1 = sqrt( l1*l1 / (c_light*c_light) * ( 1 + (m_electron*m_electron)/(p1*p1) ) );
		double tofe2 = sqrt( l2*l2 / (c_light*c_light) * ( 1 + (m_electron*m_electron)/(p2*p2) ) );
		double dTofe = tofe1 - tofe2;

		// if ( pair->d1_mMatchFlag == 0 || pair->d2_mMatchFlag == 0 )
		// 	return;

		if ( abs(dTof) < 0.0001 || pair->d1_mMatchFlag == 0 || pair->d2_mMatchFlag == 0 ){
			dTof = 9999;
			dTofe = 399;
		}

		////////////////////////////////////////////////////////////////////////
		/// Opposite-Sign
		////////////////////////////////////////////////////////////////////////
		if ( 0 == pair->mChargeSum ){
			
			book->fill( "uls", lv.M(), lv.Pt(), ScaleFactor );
			book->fill( "dedx", lv1.P(), pair->d1_mNSigmaElectron );
			book->fill( "dedx", -lv2.P(), pair->d2_mNSigmaElectron );

			
			book->fill( "chipid", xpipi, xee );

			if ( xee < XeeCut && XeeXpipi * xee < xpipi ){
				book->fill( "ulsid", lv.M(), lv.Pt(), ScaleFactor );
				book->fill( "chipidSel", xpipi, xee );

				if ( pair->d1_mTof > 0 && pair->d2_mTof > 0 ){
					book->fill( "ulsidtof", lv.M(), lv.Pt() );
				}

				if ( pair->d1_mMatchFlag > 0 || pair->d2_mMatchFlag > 0 )
					book->fill( "mass1tof", lv.M() );
				if ( pair->d1_mMatchFlag > 0 && pair->d2_mMatchFlag > 0 )
					book->fill( "mass2tof", lv.M() );

				if ( lv.M() < 0.4 ){
					if ( pair->d1_mMatchFlag > 0 && pair->d1_mTof > 0 ){
						book->fill( "pt1tof", pair->d2_mPt );
					}
					if ( pair->d1_mMatchFlag > 0 && pair->d1_mTof > 0 && pair->d2_mMatchFlag > 0 && pair->d2_mTof > 0){
						book->fill( "pt2tof", pair->d2_mPt );
					}
				}
			}




			if ( pair->d1_mMatchFlag > 0 && pair->d2_mMatchFlag > 0 ){
				book->fill( "deltaTof", dTof );
				book->fill( "deltaLen", dLen / c_light );
				book->fill( "deltaTofe", dTofe );
				book->fill( "ddeltaTof", dTof - dTofe );
				// book->fill( "ddeltaTofvsmaxp", std::max( p1, p2 ), dTof - dTofe );
				// book->fill( "ddeltaTofvsminp", std::min( p1, p2 ), dTof - dTofe );
				// book->fill( "ddeltaTofvssump", ( p1 + p2 ), dTof - dTofe );


				float beta = dTof / dLen;
				beta = tofe1 / l1 ;

				float m2 = p1 * p1 * ( 1./beta/beta - 1 );
				book->fill( "msquared", p1, m2 );
			}
			

			book->fill( "xeedTof", xee, (dTof - dTofe) );
			// if ( p1 < 0.4 && p2 < 0.4 && p1 > 0.2 && p2 > 0.2 ) 
			book->fill( "xpipidTof", xpipi, (dTof - dTofe) );

			if ( abs(dTof - dTofe) < dTofCut ){
				book->fill( "chipidcut", xpipi, xee );


				book->fill( "dedxcut", lv1.P(), pair->d1_mNSigmaElectron );
				book->fill( "dedxcut", -lv2.P(), pair->d2_mNSigmaElectron );
				book->fill( "nSigE1_nSigE2_cut", pair->d1_mNSigmaElectron, pair->d2_mNSigmaElectron );
			}

			book->fill( "nSigE1_nSigE2", pair->d1_mNSigmaElectron, pair->d2_mNSigmaElectron );


			if ( xee < XeeCut && abs(dTof - dTofe) < dTofCut && XeeXpipi * xee < xpipi ){
				book->fill( "nSigE1_nSigE2_sel", pair->d1_mNSigmaElectron, pair->d2_mNSigmaElectron );
				book->fill( "ZDCEastWestAnalyzed", pair->mZDCEast, pair->mZDCWest );
				book->fill( "ulsid2", lv.M(), lv.Pt(), ScaleFactor );
				book->fill( "rapid2", lv.M(), lv.Rapidity(), ScaleFactor );
				book->fill( "pt2id2", lv.M(), lv.Pt() * lv.Pt(), ScaleFactor );

				book->fill( "mvsephi", lv1.Phi(), lv.M() );
				book->fill( "mvspphi", lv2.Phi(), lv.M() );
				book->fill( "mvsdphi", lv1.DeltaPhi( lv2 ), lv.M() );

				book->fill( "wulsid2", lv.M(), lv.Pt(), tpcEfficiencyWeightSL( lv.Pt(), lv.M() ) );
				book->fill( "w1ulsid2", lv.M(), lv.Pt(), tpcEfficiencyWeightSL( lv.M() ) );

				book->fill( "wvpulsid2", lv.M(), lv.Pt(), tpcEfficiencyWeight( lv.Pt(), lv.M() ) );
				book->fill( "wvp1ulsid2", lv.M(), lv.Pt(), tpcEfficiencyWeight( lv.M() ) );
				book->fill( "wrapid2", lv.M(), lv.Rapidity(), tpcEfficiencyWeight( lv.Pt(), lv.M() ) );
				book->fill( "wpt2id2", lv.M(), lv.Pt() * lv.Pt(), tpcEfficiencyWeight( lv.Pt(), lv.M() ) );

				if ( pair->d1_mEta > 0 )
					book->fill( "mNHits_mPhi_etap_pos", pair->d1_mPhi, pair->d1_mNHitsFit );
				else 
					book->fill( "mNHits_mPhi_etan_pos", pair->d1_mPhi, pair->d1_mNHitsFit );
				if ( pair->d2_mEta > 0 )
					book->fill( "mNHits_mPhi_etap_neg", pair->d2_mPhi, pair->d2_mNHitsFit );
				else 
					book->fill( "mNHits_mPhi_etan_neg", pair->d2_mPhi, pair->d2_mNHitsFit );

				// LOG_F( INFO, "3D eff factor (%f, %f, %f) = %f", lv.Pt(), lv.M(), lv.Rapidity(), tpcEfficiencyWeight( lv.Pt(), lv.M(), lv.Rapidity() ) );
				float e3d = tpcEfficiencyWeight( lv.Pt(), lv.M(), lv.Rapidity() );
				book->fill( "w3ulsid2", lv.M(), lv.Pt(), e3d );
				book->fill( "w3rapid2", lv.M(), lv.Rapidity(), e3d );
				book->fill( "w3pt2id2", lv.M(), lv.Pt() * lv.Pt(), e3d );

				TLorentzVector lvPositron = lv2;
				lvPositron.Boost( -(lv.BoostVector()) );
				TVector3 vbeam(0, 0, 1.0);

				TVector3 vPositron( lvPositron.Px(), lvPositron.Py(), lvPositron.Pz() );
				float costheta = cos( vPositron.Angle( vbeam ) );

				book->fill( "w3costhetaid2", lv.M(), abs(costheta), tpcEfficiencyWeight( lv.Pt(), lv.M() ) );
				book->fill( "w2costhetaid2", lv.M(), abs(costheta), tpcEfficiencyWeightCosTheta( lv.M(), abs(costheta) ) );


				book->fill( "chipidcutSel", xpipi, xee );
				book->fill( "xeedTofSel", xee, (dTof - dTofe) );

				double aco = 1.0 - fabs( lv1.DeltaPhi( lv2 ) ) / TMath::Pi();
				double asym = fabs( ( lv1.Pt() - lv2.Pt() ) / (lv1.Pt() + lv2.Pt()) ); 
				book->fill( "aco", lv.M(), aco );
				book->fill( "asym", lv.M(), asym );

				if ( lv.M() > 0.4 && lv.M() < 0.76 ){
					
					TVector3 vParent( lv.Px(), lv.Py(), lv.Pz() );
					TVector3 vD1( lv1.Px(), lv1.Py(), lv1.Pz() );
					TVector3 vD2( lv2.Px(), lv2.Py(), lv2.Pz() );
					
					book->fill( "deltaPhi_pd1", lv1.DeltaPhi( lv ) );
					book->fill( "deltaPhi_pd2", lv.DeltaPhi( lv2 ) );

					book->fill( "deltaPhi_pd1_fold", foldPi(lv1.DeltaPhi( lv )) );

					book->fill( "wdeltaPhi_pd1", lv1.DeltaPhi( lv ), tpcEfficiencyWeight( lv.Pt(), lv.M() ) );
					book->fill( "wdeltaPhi_pd2", lv.DeltaPhi( lv2 ), tpcEfficiencyWeight( lv.Pt(), lv.M() ) );

					book->fill( "wdeltaPhi_pd1_fold", foldPi(lv1.DeltaPhi( lv )), tpcEfficiencyWeight( lv.Pt(), lv.M() ) );
					book->fill( "wdeltaPhi_pd1_2fold", foldPi2(lv1.DeltaPhi( lv )), tpcEfficiencyWeight( lv.Pt(), lv.M() ) );


					book->fill( "deltaAngle_pd1", vD2.Angle( vD1 ) );
					book->fill( "deltaAngle_pd2", vParent.Angle( vD2 ) );

					book->fill( "wdeltaPhi_pd1_fold_pt", lv.Pt(), foldPi(lv1.DeltaPhi( lv )), tpcEfficiencyWeight( lv.Pt(), lv.M() ) );

				}

				if ( lv.M() > 0.4 && lv.M() < 3.0 ){
					book->fill( "wdeltaPhi_pd1_fold_all", foldPi(lv1.DeltaPhi( lv )), tpcEfficiencyWeight( lv.Pt(), lv.M() ) );
					book->fill( "wdeltaPhi_pd1_2fold_all", foldPi2(lv1.DeltaPhi( lv )), tpcEfficiencyWeight( lv.Pt(), lv.M() ) );
				}

				book->fill( "deltaPhi_pd1_fold_mass", lv.M(), foldPi(lv1.DeltaPhi( lv )) );
				book->fill( "wdeltaPhi_pd1_fold_mass", lv.M(), foldPi(lv1.DeltaPhi( lv )), tpcEfficiencyWeight( lv.Pt(), lv.M() ) );

				book->fill( "mDCA", pair->d1_mDCA );
				book->fill( "mDCA", pair->d2_mDCA );

				book->fill( "mDCA_mPt", pair->d1_mPt, pair->d1_mDCA );
				book->fill( "mDCA_mPt", pair->d2_mPt, pair->d2_mDCA );

				book->fill( "mNHitsFit", pair->d2_mNHitsFit );
				book->fill( "mNHitsFit", pair->d2_mNHitsFit );
				
				// LOG_F( INFO, "lv1.Phi()=%f, lv2.Phi()=%f, deltaPhi/pi=%f", lv1.Phi(), lv2.Phi(), aco );
				// LOG_F( INFO, "asym=%f", fabsasym  );
			}




		} // 0 == pair->mChargeSum
		else {
			book->fill( "ls", lv.M(), lv.Pt(), ScaleFactor );
			if ( xee < XeeCut )
				book->fill( "lsid", lv.M(), lv.Pt(), ScaleFactor );
			if ( xee < XeeCut && abs(dTof - dTofe) < dTofCut )
				book->fill( "lsid2", lv.M(), lv.Pt(), ScaleFactor );
		}


	} //analyzeEvent

	double foldPi( double phi ){
		double aphi = fabs( phi );
		if ( aphi > M_PI/2 )
			aphi = aphi - M_PI/2;
		return aphi;
	}

	double foldPi2( double phi ){
		double aphi = fabs( phi );
		if ( aphi > M_PI/2.0 )
			aphi =  aphi - M_PI/2;
		if ( aphi > M_PI/4.0 )
			aphi = M_PI/4.0 - aphi;
		return aphi;
	}


	void expoFit( TH1 * h, float *mean, float *error ){

		TF1 * ff = new TF1( TString::Format( "%s_ff", h->GetName() ), "[0] * exp(  [1]*x )", 0.001, 0.006 );
		h->Fit( ff, "R", "", 0.0005, 0.006 );

		*mean = sqrt( -1.0 / ff->GetParameter( 1 ) );
		cout << "mean = " << *mean << endl;
		*error = abs( sqrt( -1.0 / (ff->GetParameter( 1 ) + ff->GetParError( 1 ) ) ) - *mean );
		cout << "error = " << *error << endl;

		ff->Write();

		return;
	}


	virtual void postMake(){
		TreeAnalyzer::postMake();

		RooPlotLib rpl;
		rpl.link( book );

		TH2*hulsid2 = book->get2D( "wulsid2" );
		TAxis * ax = hulsid2->GetXaxis();
		TH1 *hptms0 = hulsid2->ProjectionY( "hPtMass0", ax->FindBin( 0.4 ), ax->FindBin( 0.76 ) );
		TH1 *hptms1 = hulsid2->ProjectionY( "hPtMass1", ax->FindBin( 0.76 ), ax->FindBin( 1.2 ) );
		TH1 *hptms2 = hulsid2->ProjectionY( "hPtMass2", ax->FindBin( 1.2 ), ax->FindBin( 2.6 ) );
		
		TH2*h2pt2 = book->get2D( "wpt2id2" );
		ax = h2pt2->GetXaxis();
		TH1 *hms0 = h2pt2->ProjectionY( "hPt2Mass0", ax->FindBin( 0.4 ), ax->FindBin( 0.76 ) );
		TH1 *hms1 = h2pt2->ProjectionY( "hPt2Mass1", ax->FindBin( 0.76 ), ax->FindBin( 1.2 ) );
		TH1 *hms2 = h2pt2->ProjectionY( "hPt2Mass2", ax->FindBin( 1.2 ), ax->FindBin( 2.6 ) );

		float m0spt2 = 0;
		float m1spt2 = 0;
		float m2spt2 = 0;

		float m0spt2e = 0;
		float m1spt2e = 0;
		float m2spt2e = 0;

		expoFit( hms0, &m0spt2, &m0spt2e );
		expoFit( hms1, &m1spt2, &m1spt2e );
		expoFit( hms2, &m2spt2, &m2spt2e );

		TH1 * h = book->get( "meanPt2" );

		h->SetBinContent( 1, (m0spt2 * 1000) );
		h->SetBinContent( 2, (m1spt2 * 1000) );
		h->SetBinContent( 3, (m2spt2 * 1000) );

		h->SetBinError( 1, (m0spt2e) * 1000 );
		h->SetBinError( 2, (m1spt2e) * 1000 );
		h->SetBinError( 3, (m2spt2e) * 1000 );

		TH1 * hm = book->get( "meanPt2Model" );
		hm->SetBinContent( 1, 35.4932 );
		hm->SetBinContent( 2, 41.4201 );
		hm->SetBinContent( 3, 46.468 );
		
		LOG_F( INFO, "Complete");
	}




};


#endif

