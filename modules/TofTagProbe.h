#ifndef TOF_TAG_PROBE_H
#define TOF_TAG_PROBE_H


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
#include "TGraphAsymmErrors.h"
#include "TRandom3.h"


#include "FemtoDstFormat/BranchReader.h"
#include "FemtoPairFormat/FemtoPair.h"

#include <algorithm>


class TofTagProbe : public TreeAnalyzer
{
protected:

	BranchReader<FemtoPair> _fpr;
	float XeeCut = 0.2;


public:

	const int DEBUG = 1;
	TofTagProbe() {}
	~TofTagProbe() {}

	virtual void initialize(){
		TreeAnalyzer::initialize();

		this->_fpr.setup( this->chain, "Pairs" );

		XeeCut = config.get<float>( "p.XeeCut", 5 );

		LOG_F( INFO, "XeeCut = %f", XeeCut );

		gRandom = new TRandom3();
		gRandom->SetSeed( 0 );

		book->cd();
	}
protected:

	virtual void analyzeEvent(){
		FemtoPair * pair = this->_fpr.get();

		TLorentzVector lv1, lv2, lv;
		lv1.SetPtEtaPhiM( pair->d1_mPt, pair->d1_mEta, pair->d1_mPhi, 0.0005109989461 );
		lv2.SetPtEtaPhiM( pair->d2_mPt, pair->d2_mEta, pair->d2_mPhi, 0.0005109989461 );
		lv = lv1 + lv2;

		double c_light = 29.9792458; // m / ns
		double m_electron = 0.0005109990615;

		book->fill( "events", 1 );
		if ( pair->mGRefMult > 4 ) return;
		book->fill( "events", 2 );

		if ( pair->d1_mPt  < 0.200 || pair->d2_mPt < 0.200 || abs( pair->d1_mEta ) > 1.0 || abs( pair->d2_mEta ) > 1.0 ) return;
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

		if ( abs(dTof) < 0.0001 || pair->d1_mMatchFlag == 0 || pair->d2_mMatchFlag == 0 ){
			dTof = 999;
			dTofe = 399;
		}

		////////////////////////////////////////////////////////////////////////
		/// Opposite-Sign
		////////////////////////////////////////////////////////////////////////
		if ( 0 == pair->mChargeSum ){

			if ( xee < XeeCut ){

				if ( pair->d1_mMatchFlag > 0 || pair->d2_mMatchFlag > 0 )
					book->fill( "mass1tof", lv.M() );
				if ( pair->d1_mMatchFlag > 0 && pair->d2_mMatchFlag > 0 )
					book->fill( "mass2tof", lv.M() );

				if ( lv.M() < 0.7 ){
					if ( pair->d1_mMatchFlag > 0  ){
						book->fill( "pt1tof", pair->d2_mPt );
					}
					if ( pair->d1_mMatchFlag > 0 && pair->d2_mMatchFlag > 0 ){
						book->fill( "pt2tof", pair->d2_mPt );
					}

					if ( pair->d1_mMatchFlag > 0 ){
						book->fill( "pt1tofb", pair->d2_mPt );
					}
					if ( pair->d1_mMatchFlag > 0 && pair->d2_mMatchFlag > 0 && pair->d2_mTof > 0 && abs(pair->d2_mYLocal) < 1.6 && abs(pair->d2_mZLocal) < 2.8 ){
						book->fill( "pt2tofb", pair->d2_mPt );
					}
				}
			}

		} // 0 == pair->mChargeSum
		else {
		}


	} //analyzeEvent


	virtual void postMake(){
		TreeAnalyzer::postMake();

		TH1 * h0 = book->get( "pt2tofb" );
		TH1 * h1 = book->get( "pt1tofb" );

		h0->Rebin(10);
		h1->Rebin(10);

		TGraphAsymmErrors *g = new TGraphAsymmErrors();
		g->Divide( h0, h1, "cl=0.683 b(1,1) mode" );
		g->SetName( "TofEff" );
		g->Write();

		
		LOG_F( INFO, "Complete");
	}




};


#endif

