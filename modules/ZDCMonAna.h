#ifndef ZDCMON_ANALYZER_H
#define ZDCMON_ANALYZER_H


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
#include "FemtoDstFormat/FemtoEvent.h"


#include <algorithm>
#define _USE_MATH_DEFINES
#include <math.h>


class ZDCMonAna : public TreeAnalyzer
{
protected:

	BranchReader<FemtoEvent> _fe;

public:

	const int DEBUG = 1;
	ZDCMonAna() {}
	~ZDCMonAna() {}

	virtual void initialize(){
		LOG_SCOPE_FUNCTION(INFO);
		TreeAnalyzer::initialize();

		this->_fe.setup( this->chain, "Event" );

	}
protected:


	virtual void analyzeEvent(){
		FemtoEvent * event = this->_fe.get();


		book->fill( "vz", event->mPrimaryVertex_mX3 );

		if ( abs(event->mPrimaryVertex_mX3) > 100 ) return;
		// cout << "event->mBBCWest = " << event->mBBCWest << endl;

		UShort_t bits = event->mLastDsmBit[1]; // bits 16 - 31
		UShort_t BBCE = (bits >> 1) & 1U;
		UShort_t BBCW = (bits >> 2) & 1U;

		// LOG_F( INFO, "BBC-E=%d, BBC-W=%d, bits=%d", BBCE, BBCW, bits );

		book->fill( "AllBBCWest", event->mBBCWest );
		book->fill( "AllBBCEast", event->mBBCEast );

		book->fill( "AllZDCWest", event->mZDCWest );
		book->fill( "AllZDCEast", event->mZDCEast );

		if ( 0 == BBCE && 0 == BBCW ){
			book->fill( "BBCWestVeto", event->mBBCWest );
			book->fill( "BBCEastVeto", event->mBBCEast );
		}

		if ( 0 == BBCE && 0 == BBCW && event->mGRefMult <= 4 && event->mZDCWest < 1200 && event->mZDCEast < 1200 && event->mNTracks == 2 ){
			book->fill( "BBCWest", event->mBBCWest );
			book->fill( "BBCEast", event->mBBCEast );

			book->fill( "ZDCWest", event->mZDCWest );
			book->fill( "ZDCEast", event->mZDCEast );

			book->fill( "TofMultTrg", event->mTofMultTrg );
			book->fill( "TofMultTrg_vs_Offline", event->mNBTofHits, event->mTofMultTrg );

			if ( event->mNBTofMatched > 0 )
				book->fill( "TofMultTrg_over_Offline_Matched", event->mNBTofHits, event->mTofMultTrg );
			if ( event->mNBTofHits > 0 && event->mTofMultTrg > 0 && event->mTofMultTrg < 30 )
				book->fill( "TofMultTrg_over_Offline",(float)event->mTofMultTrg/(float)event->mNBTofHits );
			if ( event->mNBTofMatched == 0 )
				book->fill( "TofMultTrg0Matched", event->mTofMultTrg );
			if ( event->mNBTofMatched == 1 )
				book->fill( "TofMultTrg1Matched", event->mTofMultTrg );
			if ( event->mNBTofMatched == 2 )
				book->fill( "TofMultTrg2Matched", event->mTofMultTrg );
			if ( event->mNBTofMatched > 2 )
				book->fill( "TofMultTrg2PlusMatched", event->mTofMultTrg );
		}


		book->fill( "events", 1 );
		if ( event->mZDCWest < 1200 && event->mZDCEast < 1200 && event->mTofMultTrg >= 2 && event->mTofMultTrg <= 6 ){
			book->fill( "events", 2 );

			if ( 0 == BBCE )
				book->fill( "events", 3 );
			if ( 0 == BBCW )
				book->fill( "events", 4 );
			if ( 0 == BBCW && 0 == BBCE )
				book->fill( "events", 5 );

			if ( event->mGRefMult <= 4 ){
				book->fill( "events", 6 );
				if ( 0 == BBCW && 0 == BBCE )
					book->fill( "events", 7 );
				if ( event->mNTracks == 2 ){
					book->fill( "events", 8 );
					if ( 0 == BBCW && 0 == BBCE )
						book->fill( "events", 9 );
				}

			}
		} // ZDC + TOFMULT


		if ( 0 == BBCE && 0 == BBCW && event->mTofMultTrg >= 2 && event->mTofMultTrg <= 6 ){
			book->fill( "ZDCNoCut0", event->mZDCEast, event->mZDCWest );
			book->fill( "ZDCWestNoCut0", event->mZDCWest );
			book->fill( "ZDCEastNoCut0", event->mZDCEast );

			if ( event->mGRefMult <= 4 ){
				book->fill( "ZDCWestNoCut1", event->mZDCWest );
				book->fill( "ZDCEastNoCut1", event->mZDCEast );				
				book->fill( "ZDCNoCut1", event->mZDCEast, event->mZDCWest );
			}

			if ( event->mNBTofMatched >= 1 ){
				book->fill( "ZDCNoCut2", event->mZDCEast, event->mZDCWest );
			}
		}



	} //analyzeEvent





	virtual void postMake(){
		TreeAnalyzer::postMake();


	}

};


#endif
