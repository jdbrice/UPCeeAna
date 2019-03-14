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
	float XpipiMaxCut = 1200.0;
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

	TH1 * hUpcEmb_TpcEffVsMass = nullptr;
	TH1 * hUpcEmb_TofEffVsMass = nullptr;

	TH1 * hUpcEmb_NHFCorr = nullptr;
	TH1 * hUpcEmb_NHDCorr = nullptr;

	TH1 * hUpcEmb_TpcNHDCorr = nullptr;


	// Tracking cuts
	int min_nHitsFit  = 20;
	int min_nHitsDedx = 10;
	float max_Dca = 1.0;
	float min_nhr = 0.52;
	float min_pT  = 0.200;
	float max_vZ  = 100;


	// used for mass, pt, pt2 dphi
	// float flatTofEff = 1.677852349; // 1.0 / 0.596


	/***************/
	// TPC level Efficiency from Embedding
	TH1 * hRecoMass = nullptr;
	TH1 * hRecoRapidity = nullptr;
	TH1 * hRecoPt = nullptr;
	TH1 * hRecoPt2 = nullptr;
	TH1 * hRecoCosTheta = nullptr;
	TH1 * hRecoDeltaPhi = nullptr; // folded2 version

	TH3 * hRecoMassPtRapidity = nullptr;
	TH3 * hRecoMassCosThetaRapidity = nullptr;
	/***************/

	/***************/
	// TOF Matching level Efficiency from Embedding
	TH1 * hTOFMass = nullptr;
	TH1 * hTOFRapidity = nullptr;
	TH1 * hTOFPt = nullptr;
	TH1 * hTOFPt2 = nullptr;
	TH1 * hTOFCosTheta = nullptr;
	TH1 * hTOFDeltaPhi = nullptr; // folded2 version

	// 3D efficiency
	TH3 * hTOFCosTheta_Rapidity_Mass = nullptr;
	/***************/


	/***************/
	// TOF Timing and PID efficiency from data driven analysis
	TH1 * hTOFPIDMass = nullptr;
	TH1 * hTOFPIDRapidity = nullptr;
	TH1 * hTOFPIDPt = nullptr;
	TH1 * hTOFPIDPt2 = nullptr;
	TH1 * hTOFPIDCosTheta = nullptr;
	TH1 * hTOFPIDDeltaPhi = nullptr; // folded2 version
	/***************/


	float x2eeEfficiencyWeight = 1.0;
	

public:

	const int DEBUG = 1;
	Analyzer() {}
	~Analyzer() {}


	void setup_shuai_eff(){
		LOG_SCOPE_FUNCTION(INFO);
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
	}

	void setup_emb_eff(){
		LOG_SCOPE_FUNCTION(INFO);

		// string filename_TPC_EFF = config.get<string>( "p.TpcEff", "/Users/jdb/bnl/work/upc/embedding/output_eff_mass_NOMINAL.root" );
		// LOG_F( INFO, "TpcEff = %s", filename_TPC_EFF.c_str() );

		// TFile * fUpcEmbTpc = new TFile( filename_TPC_EFF.c_str() );
		// hUpcEmb_TpcEffVsMass = (TH1F*)fUpcEmbTpc->Get( "eff_mMass" )->Clone( "hUpcEmb_TpcEffVsMass" );
		// TFile * fUpcEmbTof = new TFile( "/Users/jdb/bnl/work/upc/embedding/shuai/AuAu200_pairEff/output/eff.root" );
		// hUpcEmb_TofEffVsMass = (TH1F*)fUpcEmbTof->Get( "eff_mass" )->Clone( "hUpcEmb_TofEffVsMass" );

		// LOG_F( INFO, "hUpcEmb_TpcEffVsMass=%p", hUpcEmb_TpcEffVsMass );
		// LOG_F( INFO, "hUpcEmb_TofEffVsMass=%p", hUpcEmb_TofEffVsMass );


		// TFile * fUpcEmbNHFCorr = new TFile( "/Users/jdb/bnl/work/upc/embedding/nhitsfit/output_corr.root" );
		// hUpcEmb_NHFCorr = (TH1F*)fUpcEmbNHFCorr->Get( "hCorr" )->Clone( "hUpcEmb_NHFCorr" );

		// TFile * fUpcEmbNHDCorr = new TFile( "/Users/jdb/bnl/work/upc/embedding/nhitsdedx/output_corr.root" );
		// hUpcEmb_NHDCorr = (TH1F*)fUpcEmbNHDCorr->Get( "hCorr" )->Clone( "hUpcEmb_NHDCorr" );

		



		string EFFICIENCY = config.get<string>( "p.EFFICIENCY", "NOMINAL" );
		LOG_F( INFO, "EFFICIENCY = %s", EFFICIENCY.c_str() );

		/********************************************************************************************/
		// Setup the NHDedx correction
		TFile * fUpcEmbTpcNHDCorr = new TFile( TString::Format( "/Users/jdb/bnl/work/upc/embedding/nhitsdedx/output_tpc_corr_%s.root", EFFICIENCY.c_str() ) );
		hUpcEmb_TpcNHDCorr = (TH1F*)fUpcEmbTpcNHDCorr->Get( "hCorr" )->Clone( "hUpcEmb_TpcNHDCorr" );

		/********************************************************************************************/

		LOG_F( INFO, "hUpcEmb_NHDCorr=%p", hUpcEmb_NHDCorr );


		/********************************************************************************************/
		// Setup the embedding RECO efficiency (final used versions)
		TFile * fReco = new TFile(  TString::Format("/Users/jdb/bnl/work/upc/embedding/output_eff_mass_%s.root", EFFICIENCY.c_str()) );
		hRecoMass = (TH1*)fReco->Get("eff_mMass")->Clone( "hRecoMass" );
		fReco = new TFile(  TString::Format("/Users/jdb/bnl/work/upc/embedding/output_eff_pt_%s.root", EFFICIENCY.c_str()) );
		hRecoPt = (TH1*)fReco->Get("eff_mPt")->Clone( "hRecoPt" );
		fReco = new TFile(  TString::Format("/Users/jdb/bnl/work/upc/embedding/output_eff_pt2_%s.root", EFFICIENCY.c_str()) );
		hRecoPt2 = (TH1*)fReco->Get("eff_mPt2")->Clone( "hRecoPt2" );
		fReco = new TFile(  TString::Format("/Users/jdb/bnl/work/upc/embedding/output_eff_rap_%s.root", EFFICIENCY.c_str()) );
		hRecoRapidity = (TH1*)fReco->Get("eff_mRapidity")->Clone( "hRecoRapidity" );
		fReco = new TFile(  TString::Format("/Users/jdb/bnl/work/upc/embedding/output_eff_CosTheta_%s.root", EFFICIENCY.c_str()) );
		hRecoCosTheta = (TH1*)fReco->Get("eff_mCosTheta")->Clone( "hRecoCosTheta" );
		fReco = new TFile(  TString::Format("/Users/jdb/bnl/work/upc/embedding/output_eff_DeltaPhi_%s.root", EFFICIENCY.c_str()) );
		hRecoDeltaPhi = (TH1*)fReco->Get("eff_mDeltaPhi")->Clone( "hRecoDeltaPhi" );

		fReco = new TFile(  TString::Format("/Users/jdb/bnl/work/upc/embedding/output_eff_3D_mpty_%s.root", EFFICIENCY.c_str()) );
		hRecoMassPtRapidity = (TH3*)fReco->Get("eff")->Clone( "hRecoMassPtRapidity" );
		fReco = new TFile(  TString::Format("/Users/jdb/bnl/work/upc/embedding/output_eff_3D_mcty_%s.root", EFFICIENCY.c_str()) );
		hRecoMassCosThetaRapidity = (TH3*)fReco->Get("eff")->Clone( "hRecoMassCosThetaRapidity" );


		{
			LOG_SCOPE_F( INFO, "TPC Reco Efficiency Tables" );
			LOG_F( INFO, "hRecoMass     = %p", hRecoMass );
			LOG_F( INFO, "hRecoPt       = %p", hRecoPt );
			LOG_F( INFO, "hRecoPt2      = %p", hRecoPt2 );
			LOG_F( INFO, "hRecoRapidity = %p", hRecoRapidity );
			LOG_F( INFO, "hRecoCosTheta = %p", hRecoCosTheta );
			LOG_F( INFO, "hRecoDeltaPhi = %p", hRecoDeltaPhi );
			LOG_F( INFO, "hRecoMassPtRapidity = %p", hRecoMassPtRapidity );	
			LOG_F( INFO, "hRecoMassCosThetaRapidity = %p", hRecoMassCosThetaRapidity );
		}


		/********************************************************************************************/
		// Setup the TOF efficiency (final used version)
		TFile *fTOF = new TFile( TString::Format("/Users/jdb/bnl/work/upc/McFemtoDstAnalysis/bin/TOF_efficiency_y2017_TpcRS_%s.root", EFFICIENCY.c_str()) );
		hTOFMass     = (TH1*)fTOF->Get( "tof_eff_mass" )->Clone( "hTOFMass" );
		hTOFPt       = (TH1*)fTOF->Get( "tof_eff_pt" )->Clone( "hTOFPt" );
		hTOFPt2      = (TH1*)fTOF->Get( "tof_eff_pt2" )->Clone( "hTOFPt2" );
		hTOFRapidity = (TH1*)fTOF->Get( "tof_eff_y" )->Clone( "hTOFRapidity" );
		hTOFCosTheta = (TH1*)fTOF->Get( "tof_eff_costheta" )->Clone( "hTOFCosTheta" );
		hTOFDeltaPhi = (TH1*)fTOF->Get( "tof_eff_dphi2" )->Clone( "hTOFDeltaPhi" );
		hTOFCosTheta_Rapidity_Mass = (TH3*)fTOF->Get( "tof_eff_costheta_y_mass" )->Clone( "hTOFCosTheta_Rapidity_Mass" );

		{
			LOG_SCOPE_F( INFO, "TOF Matching Efficiency Tables" );
			
			LOG_F( INFO, "hTOFMass     = %p", hTOFMass );
			LOG_F( INFO, "hTOFPt       = %p", hTOFPt );
			LOG_F( INFO, "hTOFPt2      = %p", hTOFPt2 );
			LOG_F( INFO, "hTOFRapidity = %p", hTOFRapidity );
			LOG_F( INFO, "hTOFCosTheta = %p", hTOFCosTheta );
			LOG_F( INFO, "hTOFDeltaPhi = %p", hTOFDeltaPhi );
			LOG_F( INFO, "hTOFCosTheta_Rapidity_Mass = %p", hTOFCosTheta_Rapidity_Mass );
		}



		/********************************************************************************************/
		// Setup the TOF PID efficiency (final used version) - this is the efficiency of TIMING + DeltaDeltaTOF over TOF Matching
		TFile *fTOFPID = new TFile( "/Users/jdb/bnl/work/upc/studies/dd_tof/output_ddTOF_eff_cut_over_match_0_4.root" );
		hTOFPIDMass     = (TH1*)fTOFPID->Get( "m_eff" )->Clone( "hTOFPIDMass" );
		hTOFPIDPt       = (TH1*)fTOFPID->Get( "pt_eff" )->Clone( "hTOFPIDPt" );
		// hTOFPIDPt2      = (TH1*)fTOFPID->Get( "pt2_eff" )->Clone( "hTOFPIDPt2" );
		hTOFPIDRapidity = (TH1*)fTOFPID->Get( "y_eff" )->Clone( "hTOFPIDRapidity" );
		hTOFPIDCosTheta = (TH1*)fTOFPID->Get( "ct_eff" )->Clone( "hTOFPIDCosTheta" );
		hTOFPIDDeltaPhi = (TH1*)fTOFPID->Get( "dphi_eff" )->Clone( "hTOFPIDDeltaPhi" ); // (0 - pi/2)
		{
			LOG_SCOPE_F( INFO, "TOF PID Efficiency Tables" );
			
			LOG_F( INFO, "hTOFPIDMass     = %p", hTOFPIDMass );
			LOG_F( INFO, "hTOFPIDPt       = %p", hTOFPIDPt );
			LOG_F( INFO, "hTOFPIDPt2      = %p", hTOFPIDPt2 );
			LOG_F( INFO, "hTOFPIDRapidity = %p", hTOFPIDRapidity );
			LOG_F( INFO, "hTOFPIDCosTheta = %p", hTOFPIDCosTheta );
			LOG_F( INFO, "hTOFPIDDeltaPhi = %p", hTOFPIDDeltaPhi );
		}

	}

	virtual void initialize(){
		LOG_SCOPE_FUNCTION(INFO);
		TreeAnalyzer::initialize();

		LOG_F( INFO, "Initialize" );
		this->_fpr.setup( this->chain, "Pairs" );

		{
			LOG_SCOPE_F(INFO, "PID Cuts");

			dTofCut = config.get<float>( "p.dTofCut", 0.2 );
			XeeXpipi = config.get<float>( "p.XeeXpipi", 5 );
			XeeCut = config.get<float>( "p.XeeCut", 5 );
			XpipiCut = config.get<float>( "p.XpipiCut", 0 );

			LOG_F( INFO, "dTofCut = %f", dTofCut );
			LOG_F( INFO, "XeeXpipi = %f", XeeXpipi );
			LOG_F( INFO, "XeeCut = %f", XeeCut );
			LOG_F( INFO, "XpipiCut = %f", XpipiCut );
		}


		gRandom = new TRandom3();
		gRandom->SetSeed( 0 );

		min_nHitsFit  = config.get<int>( "p.min_nHitsFit", 20 );
		min_nHitsDedx = config.get<int>( "p.min_nHitsDedx", 15 );
		max_Dca       = config.get<float>( "p.max_Dca", 1.0 );
		min_nhr       = config.get<float>( "p.min_nhr", 0.52 );
		min_pT        = config.get<float>( "p.min_pT", 0.52 );
		max_vZ        = config.get<float>( "p.max_vZ", 100 );
		
		{
			LOG_SCOPE_F(INFO, "Analysis Cuts");
			LOG_F( INFO, "min_nHitsFit = %d" , min_nHitsFit  );
			LOG_F( INFO, "min_nHitsDedx = %d" , min_nHitsDedx  );
			LOG_F( INFO, "max_Dca = %f", max_Dca );
			LOG_F( INFO, "min_nhr = %f", min_nhr );
			LOG_F( INFO, "min_pT = %f", min_pT );
			LOG_F( INFO, "max_vZ = %f", max_vZ );
		}
		

		
		setup_shuai_eff();
		setup_emb_eff();
		book->cd();

		hSampleMassEff = (TH1*)hSLMassEff->Clone( "hSampleMassEff" );
		hSampleMassEff->Reset();
		hSampleMassEffw = (TH1*)hSLMassEff->Clone( "hSampleMassEffw" );
		hSampleMassEffw->Reset();


		// Set the X2ee Cut efficiency factor
		// Separate analysis see AN
		if ( XeeCut > 8 )
			x2eeEfficiencyWeight = 1.0;
		if ( 4 == (int)XeeCut )
			x2eeEfficiencyWeight = 1.059550466; // = (1.0 / 0.94379648);
		if ( 2 == (int)XeeCut )
			x2eeEfficiencyWeight = 1.312872461; // = (1.0 / 0.76168861);


	}
protected:

	/**************************************************/
	// Applies the hHitsDedx correction
	float upcEmbTpcNHDCorr( float pt ){
		
		if ( pt >= 1.0 ) 
			pt = 0.9;

		TAxis * ax = hUpcEmb_TpcNHDCorr->GetXaxis();

		int im = ax->FindBin( pt );
		float v = 1 - hUpcEmb_TpcNHDCorr->Interpolate( pt );

		if ( 0 == v || 1.0/v != 1.0/v )
			return 0;
		return 1.0/v ;
	}

	/**************************************************/
	// Generic 1D efficiency correction
	float weight1DEff( TH1 * table, float x ){
		assert( table );

		float v = table->Interpolate( x );
		if ( 0 == v || 1.0/v != 1.0/v ){
			// LOG_F( ERROR, "ERROR in efficiency table=%p, x=%f", table, x );
			return 0;
		}

		return 1/v;
	}

	/**************************************************/
	// Generic 3D efficiency correction
	float weight3DEff( TH3 * table, float x, float y, float z ){
		assert( table );

		int iX = table->GetXaxis()->FindBin(x);
		int iY = table->GetYaxis()->FindBin(y);
		int iZ = table->GetZaxis()->FindBin(z);
		bool interp = true;
		if ( iX <= 1 || iX >= table->GetXaxis()->GetNbins() - 1 ){
			// LOG_F( WARNING, "x=%f, out of range with bin=%d", x, iX );
			interp = false;
		}
		if ( iY <= 1 || iY >= table->GetYaxis()->GetNbins() - 1 ){
			// LOG_F( WARNING, "y=%f, out of range with bin=%d", y, iY );
			interp = false;
		}
		if ( iZ <= 1 || iZ >= table->GetZaxis()->GetNbins() - 1 ){
			// LOG_F( WARNING, "z=%f, out of range with bin=%d", z, iZ );
			interp = false;
		}


		float v = 0;

		if ( false == interp ){
			v = table->GetBinContent( iX, iY, iZ );
		} else {
			v = table->Interpolate( x, y, z );
		}
		if ( 0 == v || 1.0/v != 1.0/v ){
			// LOG_F( ERROR, "ERROR in efficiency table=%p, x=%f", table, x );
			return 0;
		}

		return 1.0/v;
	}


	bool passX2( double x2ee, double x2pipi ){
		if ( x2ee < XeeCut && XeeXpipi * x2ee < x2pipi && x2pipi < XpipiMaxCut )
			return true;
		return false;
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
		book->fill( "ZDCEastWestSelected", pair->mZDCEast, pair->mZDCWest );

		if ( fabs(pair->mVertexZ) > max_vZ ) return;

		book->fill( "events", 1 );
		if ( pair->mGRefMult > 4 ) return;
		book->fill( "events", 2 );

		if ( pair->d1_mPt  < min_pT || pair->d2_mPt < min_pT ) return;
		if ( abs( pair->d1_mEta ) > 1.0 || abs( pair->d2_mEta ) > 1.0 ) return;

		if ( abs(lv.Rapidity()) > 1 ) return;
		book->fill( "events", 3 );
		
		if ( pair->d1_mDCA > max_Dca ) return; 
		if ( pair->d2_mDCA > max_Dca ) return; 

		bool passTrackQA = true;
		if ( pair->d1_mNHitsFit < min_nHitsFit || pair->d2_mNHitsFit < min_nHitsFit ) { passTrackQA = false; }
		if ( fabs(pair->d1_mNHitsFit) / (float)pair->d1_mNHitsMax < 0.52 || fabs(pair->d2_mNHitsFit) / (float)pair->d2_mNHitsMax < 0.52 ) { passTrackQA = false; }
		if ( pair->d1_mNHitsDedx < min_nHitsDedx || pair->d2_mNHitsDedx < min_nHitsDedx ) { passTrackQA = false; }


		eventWithoutTrackQA( pair );
		if ( false == passTrackQA ){
			return;
		}	
		book->fill( "events", 4 );

		/***************************************************************************************/
		// Compute the PID variables
		double x2pipi = pow( pair->d1_mNSigmaPion, 2 ) + pow( pair->d2_mNSigmaPion, 2 );
		double x2ee   = pow( pair->d1_mNSigmaElectron, 2 ) + pow( pair->d2_mNSigmaElectron, 2 );

		double dTof = pair->d1_mTof - pair->d2_mTof;
		double dLen = (pair->d1_mLength ) - (pair->d2_mLength ) ;

		double p1 = lv1.P();
		double p2 = lv2.P();
		double l1 = pair->d1_mLength;// + gRandom->Gaus(0, 10);
		double l2 = pair->d2_mLength;// + gRandom->Gaus(0, 10);
		double tofe1 = sqrt( l1*l1 / (c_light*c_light) * ( 1 + (m_electron*m_electron)/(p1*p1) ) );
		double tofe2 = sqrt( l2*l2 / (c_light*c_light) * ( 1 + (m_electron*m_electron)/(p2*p2) ) );
		double dTofe = tofe1 - tofe2;
		/***************************************************************************************/


		// Check for TOF information (match and timing)
		if ( abs(dTof) < 0.0001 || pair->d1_mMatchFlag == 0 || pair->d2_mMatchFlag == 0 ){
			dTof = 9999;
			dTofe = 399;
		}

		/***************************************************************************************/
		// Compute the cos(theta)
		TLorentzVector lvPositron = lv2;
		lvPositron.Boost( -(lv.BoostVector()) );
		TVector3 vbeam(0, 0, 1.0);

		TVector3 vPositron( lvPositron.Px(), lvPositron.Py(), lvPositron.Pz() );
		float costheta = abs(cos( vPositron.Angle( vbeam ) ));
		/***************************************************************************************/




		/***************************************************************************************/
		// compute the deltaPhi between parent and daughter
		TVector3 vParent( lv.Px(), lv.Py(), lv.Pz() );
		TVector3 vD1( lv1.Px(), lv1.Py(), lv1.Pz() );
		TVector3 vD2( lv2.Px(), lv2.Py(), lv2.Pz() );

		float dPhi_pd1       = lv1.DeltaPhi( lv );
		float dPhi_pd1_fold  = foldPi( dPhi_pd1 );
		float dPhi_pd1_fold2 = foldPi2( dPhi_pd1 );
		/***************************************************************************************/

		/***************************************************************************************/
		/// Like Sign
		if ( 0 != pair->mChargeSum ){
			book->fill( "ls", lv.M(), lv.Pt(), ScaleFactor );
			if ( x2ee < XeeCut )
				book->fill( "lsid", lv.M(), lv.Pt(), ScaleFactor );
			if ( x2ee < XeeCut && abs(dTof - dTofe) < dTofCut )
				book->fill( "lsid2", lv.M(), lv.Pt(), ScaleFactor );
			return;
		}

		/***************************************************************************************/
		/// everything else is unlike sign
		/***************************************************************************************/


		float corrNHD         = upcEmbTpcNHDCorr( pair->d1_mPt ) * upcEmbTpcNHDCorr( pair->d2_mPt );
		float w_RECO_mass     = weight1DEff( hRecoMass, lv.M() );
		float w_RECO_pt       = weight1DEff( hRecoPt, lv.Pt() );
		float w_RECO_pt2      = weight1DEff( hRecoPt2, lv.Pt()*lv.Pt() );
		float w_RECO_y        = weight1DEff( hRecoRapidity, lv.Rapidity() );
		float w_RECO_CosTheta = weight1DEff( hRecoCosTheta, costheta );
		float w_RECO_mpty     = weight3DEff( hRecoMassPtRapidity, lv.Rapidity(), lv.Pt(), lv.M() );
		float w_RECO_mcty     = weight3DEff( hRecoMassPtRapidity, lv.Rapidity(), costheta, lv.M() );


		float w_TOF_3D       = weight3DEff( hTOFCosTheta_Rapidity_Mass, lv.M(), lv.Rapidity(), costheta );
		float w_TOF_mass     = weight1DEff( hTOFMass, lv.M() );
		float w_TOF_pt       = weight1DEff( hTOFPt, lv.Pt() );
		float w_TOF_pt2      = weight1DEff( hTOFPt2, lv.Pt()*lv.Pt() );
		float w_TOF_y        = weight1DEff( hTOFRapidity, lv.Rapidity() );
		float w_TOF_CosTheta = weight1DEff( hTOFCosTheta, costheta );


		float w_TOFPID_mass     = weight1DEff( hTOFPIDMass, lv.M() );
		float w_TOFPID_pt       = weight1DEff( hTOFPIDPt, lv.Pt() );
		float w_TOFPID_pt2      = weight1DEff( hTOFPIDPt, lv.Pt() ); // can be added later, but just use pT for now
		float w_TOFPID_y        = weight1DEff( hTOFPIDRapidity, lv.Rapidity() );
		float w_TOFPID_CosTheta = weight1DEff( hTOFPIDCosTheta, costheta );


		book->fill( "x2eedTof", x2ee, (dTof - dTofe) );
		book->fill( "x2pipidTof", x2pipi, (dTof - dTofe) );
		book->fill( "mass_deltaTof", lv.M(), abs(dTof - dTofe) );
		book->fill( "nSigE1_nSigE2", pair->d1_mNSigmaElectron, pair->d2_mNSigmaElectron );


		book->fill( "uls", lv.M(), lv.Pt(), ScaleFactor );
		book->fill( "dedx", lv1.P(), pair->d1_mNSigmaElectron );
		book->fill( "dedx", -lv2.P(), pair->d2_mNSigmaElectron );
		book->fill( "chipid", x2pipi, x2ee );
		book->fill( "mass_chipid", lv.M(), x2ee );
		book->fill( "y_chipid", lv.Rapidity(), x2ee );
		book->fill( "pt_chipid", lv.Pt(), x2ee );
		book->fill( "pt2_chipid", lv.Pt()*lv.Pt(), x2ee );
		book->fill( "ct_chipid", costheta, x2ee );
		if ( lv.M() > 0.4 && lv.M() < 3.0 ) book->fill( "dphi_chipid", dPhi_pd1_fold, x2ee );


		/***************************************************************************************/
		if ( passX2( x2ee, x2pipi ) ){

			book->fill( "tpc_signal_pt_mass", lv.M(), w_RECO_mass );

			book->fill( "ulsid", lv.M(), lv.Pt(), ScaleFactor );
			// book->fill( "w1ulsid", lv.M(), lv.Pt(), upcEmbTpcEffW( lv.M() ) );
			// float totalCorr = upcEmbTpcEffW( lv.M() ) * upcEmbTpcNHDCorr( pair->d1_mPt ) * upcEmbTpcNHDCorr( pair->d2_mPt );
			// book->fill( "wculsid", lv.M(), lv.Pt(), totalCorr );
			// book->fill( "wulsid", lv.M(), lv.Pt(), upcEmbTpcEffW( lv.M() ) );

			book->fill( "chipidSel", x2pipi, x2ee );
			book->fill( "mass_chipidSel", lv.M(), x2ee );
			book->fill( "y_chipidSel", lv.Rapidity(), x2ee );
			book->fill( "pt_chipidSel", lv.Pt(), x2ee );
			book->fill( "pt2_chipidSel", lv.Pt()*lv.Pt(), x2ee );
			book->fill( "ct_chipidSel", costheta, x2ee );
			if ( lv.M() > 0.4 && lv.M() < 3.0 ) book->fill( "dphi_chipidSel", dPhi_pd1_fold, x2ee );

			if ( pair->d1_mTof > 0 && pair->d2_mTof > 0 ){
				book->fill( "ulsidtof", lv.M(), lv.Pt() );
			}

			book->fill( "mass0tof", lv.M() );
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

			book->fill( "notof_mNHitsFit_mPt_pos", pair->d1_mPt, pair->d1_mNHitsFit - 1 );
			book->fill( "notof_mNHitsFit_mPt_neg", pair->d2_mPt, pair->d2_mNHitsFit - 1 );

			book->fill( "notof_mNHitsDedx_mPt_pos", pair->d1_mPt, pair->d1_mNHitsDedx );
			book->fill( "notof_mNHitsDedx_mPt_neg", pair->d2_mPt, pair->d2_mNHitsDedx );

			if ( lv.M() > 0.4 && lv.M() < 0.76 ){
				
				TVector3 vParent( lv.Px(), lv.Py(), lv.Pz() );
				TVector3 vD1( lv1.Px(), lv1.Py(), lv1.Pz() );
				TVector3 vD2( lv2.Px(), lv2.Py(), lv2.Pz() );
				
				// book->fill( "tpc_wdeltaPhi_pd1_fold", foldPi(lv1.DeltaPhi( lv )), totalCorr );
				// book->fill( "tpc_wdeltaPhi_pd1_2fold", foldPi2(lv1.DeltaPhi( lv )), totalCorr );

			}

		} // PASS TPC PID ONLY


		// Rough PION Selection
		if ( x2pipi < 2 ){
			book->fill( "pimass0tof", lv.M() );
			if ( pair->d1_mMatchFlag > 0 || pair->d2_mMatchFlag > 0 )
				book->fill( "pimass1tof", lv.M() );
			if ( pair->d1_mMatchFlag > 0 && pair->d2_mMatchFlag > 0 )
				book->fill( "pimass2tof", lv.M() );
		}

		/***************************************************************************************/
		// Both tracks matched to TOF
		if ( pair->d1_mMatchFlag > 0 && pair->d2_mMatchFlag > 0 ){
			book->fill( "deltaTof", dTof );
			book->fill( "deltaLen", dLen / c_light );
			book->fill( "deltaTofe", dTofe );
			book->fill( "ddeltaTof", dTof - dTofe );

			float beta = dTof / dLen;
			beta = tofe1 / l1 ;

			float m2 = p1 * p1 * ( 1./beta/beta - 1 );
			book->fill( "msquared", p1, m2 );

			book->fill( "chipidmatch", x2pipi, x2ee );
			book->fill( "mass_chipidmatch", lv.M(), x2ee );
			book->fill( "y_chipidmatch", lv.Rapidity(), x2ee );
			book->fill( "pt_chipidmatch", lv.Pt(), x2ee );
			book->fill( "pt2_chipidmatch", lv.Pt()*lv.Pt(), x2ee );
			book->fill( "ct_chipidmatch", costheta, x2ee );
			if ( lv.M() > 0.4 && lv.M() < 3.0 ) book->fill( "dphi_chipidmatch", dPhi_pd1_fold, x2ee );

			if ( pair->d1_mTof >= 0 && pair->d2_mTof >= 0 ){
				book->fill( "chipidtime", x2pipi, x2ee );
				book->fill( "mass_chipidtime", lv.M(), x2ee );
				book->fill( "y_chipidtime", lv.Rapidity(), x2ee );
				book->fill( "pt_chipidtime", lv.Pt(), x2ee );
				book->fill( "pt2_chipidtime", lv.Pt()*lv.Pt(), x2ee );
				book->fill( "ct_chipidtime", costheta, x2ee );
				if ( lv.M() > 0.4 && lv.M() < 3.0 ) book->fill( "dphi_chipidtime", dPhi_pd1_fold, x2ee );
			}

		}
		

		/***************************************************************************************/
		// Both tracks matched to TOF + pass timing cut
		if ( abs(dTof - dTofe) < dTofCut ){
			book->fill( "chipidcut", x2pipi, x2ee );
			book->fill( "mass_chipidcut", lv.M(), x2ee );
			book->fill( "y_chipidcut", lv.Rapidity(), x2ee );
			book->fill( "pt_chipidcut", lv.Pt(), x2ee );
			book->fill( "pt2_chipidcut", lv.Pt()*lv.Pt(), x2ee );
			book->fill( "ct_chipidcut", costheta, x2ee );
			if ( lv.M() > 0.4 && lv.M() < 3.0 ) book->fill( "dphi_chipidcut", dPhi_pd1_fold, x2ee );


			book->fill( "dedxcut", lv1.P(), pair->d1_mNSigmaElectron );
			book->fill( "dedxcut", -lv2.P(), pair->d2_mNSigmaElectron );
			book->fill( "nSigE1_nSigE2_cut", pair->d1_mNSigmaElectron, pair->d2_mNSigmaElectron );

			book->fill( "mass_dX2", lv.M(), x2ee - x2pipi );
		}


		/***************************************************************************************/
		// DeltaDelta TOF PID Cut
		if ( abs(dTof - dTofe) < dTofCut ) {
			// dEdx PID cuts using X2ee and X2pipi
			if ( passX2( x2ee, x2pipi ) ){
				book->fill( "nSigE1_nSigE2_sel", pair->d1_mNSigmaElectron, pair->d2_mNSigmaElectron );
				book->fill( "ZDCEastWestAnalyzed", pair->mZDCEast, pair->mZDCWest );
				book->fill( "ulsid2", lv.M(), lv.Pt(), ScaleFactor );
				book->fill( "rapid2", lv.M(), lv.Rapidity(), ScaleFactor );
				book->fill( "pt2id2", lv.M(), lv.Pt() * lv.Pt(), ScaleFactor );

				book->fill( "mvsephi", lv1.Phi(), lv.M() );
				book->fill( "mvspphi", lv2.Phi(), lv.M() );
				book->fill( "mvsdphi", lv1.DeltaPhi( lv2 ), lv.M() );

				// float upcembeffw1d = upcEmbTpcEffW( lv.M() ) * upcEmbTofEffW( lv.M() );
				// book->fill( "wulsid2", lv.M(), lv.Pt(), upcembeffw1d );
				// book->fill( "wTPCulsid2", lv.M(), lv.Pt(), upcEmbTpcEffW( lv.M() ) );
				// book->fill( "wTOFulsid2", lv.M(), lv.Pt(), upcEmbTofEffW( lv.M() ) );
				// book->fill( "wOLDulsid2", lv.M(), lv.Pt(), tpcEfficiencyWeightSL( lv.Pt(), lv.M() ) );
				// book->fill( "w1ulsid2", lv.M(), lv.Pt(), upcembeffw1d );
				// book->fill( "w1OLDulsid2", lv.M(), lv.Pt(), tpcEfficiencyWeightSL( lv.M() ) );


				

				// LOG_F( INFO, "corrNHD = %f ( pt1=%f, pt2=%f, M=%f )", corrNHD, pair->d1_mPt, pair->d2_mPt, lv.M()  );
				if ( lv.Pt() < 0.15 ){
					//  Main signal histogram

					/*******************************/
					// RAW Signal
					book->fill( "signal0_pt_mass", lv.M(), lv.Pt() );
					book->fill( "signal0_y_mass", lv.M(), lv.Rapidity() );
					book->fill( "signal0_pt2_mass", lv.M(), lv.Pt()*lv.Pt() ); 
					book->fill( "signal0_costheta_mass", lv.M(), costheta );
					book->fill( "signal0_dphi0_mass", lv.M(), dPhi_pd1 );
					book->fill( "signal0_dphi1_mass", lv.M(), dPhi_pd1_fold );
					book->fill( "signal0_dphi2_mass", lv.M(), dPhi_pd1_fold2 );

					
					float w_RECO = w_RECO_mcty;
					/*******************************/
					// RAW Signal + TPC Eff
					book->fill( "signal1_pt_mass", lv.M(), lv.Pt(), w_RECO );
					book->fill( "signal1_y_mass", lv.M(), lv.Rapidity(), w_RECO );
					book->fill( "signal1_pt2_mass", lv.M(), lv.Pt()*lv.Pt(), w_RECO ); 
					book->fill( "signal1_costheta_mass", lv.M(), costheta, w_RECO );
					book->fill( "signal1_dphi0_mass", lv.M(), dPhi_pd1, w_RECO );
					book->fill( "signal1_dphi1_mass", lv.M(), dPhi_pd1_fold, w_RECO );
					book->fill( "signal1_dphi2_mass", lv.M(), dPhi_pd1_fold2, w_RECO );

					float w_TOF = w_TOF_3D;
					/*******************************/
					// RAW Signal + TPC Eff + TOF
					book->fill( "signal2_pt_mass", lv.M(), lv.Pt(), w_RECO *  w_TOF );
					book->fill( "signal2_y_mass", lv.M(), lv.Rapidity(), w_RECO *  w_TOF );
					book->fill( "signal2_pt2_mass", lv.M(), lv.Pt()*lv.Pt(), w_RECO *  w_TOF ); 
					book->fill( "signal2_costheta_mass", lv.M(), costheta, w_RECO *  w_TOF );
					book->fill( "signal2_dphi0_mass", lv.M(), dPhi_pd1, w_RECO * w_TOF );
					book->fill( "signal2_dphi1_mass", lv.M(), dPhi_pd1_fold, w_RECO * w_TOF );
					book->fill( "signal2_dphi2_mass", lv.M(), dPhi_pd1_fold2, w_RECO * w_TOF );

					/*******************************/
					// RAW Signal + TPC Eff + TOF + TOF PID
					book->fill( "signal3_pt_mass", lv.M(), lv.Pt(), w_RECO *  w_TOF * w_TOFPID_y );
					book->fill( "signal3_y_mass", lv.M(), lv.Rapidity(), w_RECO *  w_TOF * w_TOFPID_y );
					book->fill( "signal3_pt2_mass", lv.M(), lv.Pt()*lv.Pt(), w_RECO *  w_TOF * w_TOFPID_mass ); 
					book->fill( "signal3_costheta_mass", lv.M(), costheta, w_RECO *  w_TOF * w_TOFPID_CosTheta );
					book->fill( "signal3_dphi0_mass", lv.M(), dPhi_pd1, w_RECO * w_TOF * w_TOFPID_mass );
					book->fill( "signal3_dphi1_mass", lv.M(), dPhi_pd1_fold, w_RECO * w_TOF * w_TOFPID_mass );
					book->fill( "signal3_dphi2_mass", lv.M(), dPhi_pd1_fold2, w_RECO * w_TOF * w_TOFPID_mass );

					/*******************************/
					// RAW Signal + TPC Eff + TOF + TOF PID + NHDCorr
					book->fill( "signal4_pt_mass", lv.M(), lv.Pt(), w_RECO *  w_TOF * w_TOFPID_y * corrNHD );
					book->fill( "signal4_y_mass", lv.M(), lv.Rapidity(), w_RECO *  w_TOF * w_TOFPID_y * corrNHD );
					book->fill( "signal4_pt2_mass", lv.M(), lv.Pt()*lv.Pt(), w_RECO *  w_TOF * w_TOFPID_mass * corrNHD ); 
					book->fill( "signal4_costheta_mass", lv.M(), costheta, w_RECO *  w_TOF * w_TOFPID_CosTheta * corrNHD );
					book->fill( "signal4_dphi0_mass", lv.M(), dPhi_pd1, w_RECO * w_TOF * w_TOFPID_mass * corrNHD );
					book->fill( "signal4_dphi1_mass", lv.M(), dPhi_pd1_fold, w_RECO * w_TOF * w_TOFPID_mass * corrNHD );
					book->fill( "signal4_dphi2_mass", lv.M(), dPhi_pd1_fold2, w_RECO * w_TOF * w_TOFPID_mass * corrNHD );

					/*******************************/
					// RAW Signal + TPC Eff + TOF + TOF PID + NHDCorr + X2eeEfficiency
					book->fill( "signal4_pt_mass", lv.M(), lv.Pt(), w_RECO *  w_TOF * w_TOFPID_y * corrNHD * x2eeEfficiencyWeight );
					book->fill( "signal4_y_mass", lv.M(), lv.Rapidity(), w_RECO *  w_TOF * w_TOFPID_y * corrNHD * x2eeEfficiencyWeight );
					book->fill( "signal4_pt2_mass", lv.M(), lv.Pt()*lv.Pt(), w_RECO *  w_TOF * w_TOFPID_mass * corrNHD * x2eeEfficiencyWeight ); 
					book->fill( "signal4_costheta_mass", lv.M(), costheta, w_RECO *  w_TOF * w_TOFPID_CosTheta * corrNHD * x2eeEfficiencyWeight );
					book->fill( "signal4_dphi0_mass", lv.M(), dPhi_pd1, w_RECO * w_TOF * w_TOFPID_mass * corrNHD * x2eeEfficiencyWeight );
					book->fill( "signal4_dphi1_mass", lv.M(), dPhi_pd1_fold, w_RECO * w_TOF * w_TOFPID_mass * corrNHD * x2eeEfficiencyWeight );
					book->fill( "signal4_dphi2_mass", lv.M(), dPhi_pd1_fold2, w_RECO * w_TOF * w_TOFPID_mass * corrNHD * x2eeEfficiencyWeight );


					book->fill( "signal1d_mass", lv.M(), w_RECO_mass * w_TOF * w_TOFPID_mass );
					book->fill( "signal3d_mass", lv.M(), w_RECO * w_TOF_3D * w_TOFPID_mass );
					book->fill( "signal3dNHD_mass", lv.M(), w_RECO * w_TOF_3D * w_TOFPID_mass * corrNHD );
					
				}

				// book->fill( "wvpulsid2", lv.M(), lv.Pt(), tpcEfficiencyWeight( lv.Pt(), lv.M() ) );
				// book->fill( "wvp1ulsid2", lv.M(), lv.Pt(), tpcEfficiencyWeight( lv.M() ) );
				// book->fill( "wrapid2", lv.M(), lv.Rapidity(), tpcEfficiencyWeight( lv.Pt(), lv.M() ) );
				// book->fill( "wpt2id2", lv.M(), lv.Pt() * lv.Pt(), tpcEfficiencyWeight( lv.Pt(), lv.M() ) );

				book->fill( "noCorr",  lv.M() );
				// float corrNHF = upcEmbNHFCorr( pair->d1_mPt ) * upcEmbNHFCorr( pair->d2_mPt );
				// float corrNHD = upcEmbNHDCorr( pair->d1_mPt ) * upcEmbNHDCorr( pair->d2_mPt );
				// book->fill( "nhfCorr", lv.M(), corrNHF );
				book->fill( "nhdCorr", lv.M(), corrNHD );
				// book->fill( "nhCorr",  lv.M(), corrNHF * corrNHD );

				// book->fill( "wculsid2", lv.M(), lv.Pt(), upcembeffw1d * corrNHF * corrNHD );


				/***************************************************/
				// Track quality 
				if ( pair->d1_mEta > 0 )
					book->fill( "mNHits_mPhi_etap_pos", pair->d1_mPhi, pair->d1_mNHitsFit );
				else 
					book->fill( "mNHits_mPhi_etan_pos", pair->d1_mPhi, pair->d1_mNHitsFit );
				if ( pair->d2_mEta > 0 )
					book->fill( "mNHits_mPhi_etap_neg", pair->d2_mPhi, pair->d2_mNHitsFit );
				else 
					book->fill( "mNHits_mPhi_etan_neg", pair->d2_mPhi, pair->d2_mNHitsFit );

				book->fill( "mNHitsFit_mPt_pos", pair->d1_mPt, pair->d1_mNHitsFit - 1 );
				book->fill( "mNHitsFit_mPt_neg", pair->d2_mPt, pair->d2_mNHitsFit - 1 );

				book->fill( "mNHitsDedx_mPt_pos", pair->d1_mPt, pair->d1_mNHitsDedx );
				book->fill( "mNHitsDedx_mPt_neg", pair->d2_mPt, pair->d2_mNHitsDedx );

				book->fill( "mNHitsFit_Dedx_pos", pair->d1_mNHitsDedx, pair->d1_mNHitsFit - 1 );
				book->fill( "mNHitsFit_Dedx_neg", pair->d2_mNHitsDedx, pair->d2_mNHitsFit - 1 );


				// LOG_F( INFO, "3D eff factor (%f, %f, %f) = %f", lv.Pt(), lv.M(), lv.Rapidity(), tpcEfficiencyWeight( lv.Pt(), lv.M(), lv.Rapidity() ) );
				// float e3d = tpcEfficiencyWeight( lv.Pt(), lv.M(), lv.Rapidity() );
				// book->fill( "w3ulsid2", lv.M(), lv.Pt(), e3d );
				// book->fill( "w3culsid2", lv.M(), lv.Pt(), e3d * corrNHD );
				// book->fill( "w3rapid2", lv.M(), lv.Rapidity(), e3d );
				// book->fill( "w3pt2id2", lv.M(), lv.Pt() * lv.Pt(), e3d );

				

				// book->fill( "w3costhetaid2", lv.M(), abs(costheta), tpcEfficiencyWeight( lv.Pt(), lv.M() ) );
				// book->fill( "w2costhetaid2", lv.M(), abs(costheta), tpcEfficiencyWeightCosTheta( lv.M(), abs(costheta) ) );


				book->fill( "chipidcutSel", x2pipi, x2ee );
				book->fill( "mass_chipidcutSel", lv.M(), x2ee );
				book->fill( "y_chipidcutSel", lv.Rapidity(), x2ee );
				book->fill( "pt_chipidcutSel", lv.Pt(), x2ee );
				book->fill( "pt2_chipidcutSel", lv.Pt()*lv.Pt(), x2ee );
				book->fill( "ct_chipidcutSel", costheta, x2ee );
				if ( lv.M() > 0.4 && lv.M() < 3.0 ) book->fill( "dphi_chipidcutSel", dPhi_pd1_fold, x2ee );
				book->fill( "x2eedTofSel", x2ee, (dTof - dTofe) );

				double aco = 1.0 - fabs( lv1.DeltaPhi( lv2 ) ) / TMath::Pi();
				double asym = fabs( ( lv1.Pt() - lv2.Pt() ) / (lv1.Pt() + lv2.Pt()) ); 
				book->fill( "aco", lv.M(), aco );
				book->fill( "asym", lv.M(), asym );

				if ( lv.M() > 0.4 && lv.M() < 0.76 ){
					book->fill( "deltaPhi_pd1", lv1.DeltaPhi( lv ) );
					book->fill( "deltaPhi_pd2", lv.DeltaPhi( lv2 ) );

					book->fill( "deltaPhi_pd1_fold", foldPi(lv1.DeltaPhi( lv )) );

					// book->fill( "wdeltaPhi_pd1", lv1.DeltaPhi( lv ), tpcEfficiencyWeight( lv.Pt(), lv.M() ) );
					// book->fill( "wdeltaPhi_pd2", lv.DeltaPhi( lv2 ), tpcEfficiencyWeight( lv.Pt(), lv.M() ) );

					// book->fill( "wdeltaPhi_pd1_fold", foldPi(lv1.DeltaPhi( lv )), tpcEfficiencyWeight( lv.Pt(), lv.M() ) );
					// book->fill( "wdeltaPhi_pd1_2fold", foldPi2(lv1.DeltaPhi( lv )), tpcEfficiencyWeight( lv.Pt(), lv.M() ) );


					book->fill( "deltaAngle_pd1", vD2.Angle( vD1 ) );
					book->fill( "deltaAngle_pd2", vParent.Angle( vD2 ) );

					// book->fill( "wdeltaPhi_pd1_fold_pt", lv.Pt(), foldPi(lv1.DeltaPhi( lv )), tpcEfficiencyWeight( lv.Pt(), lv.M() ) );

				}

				if ( lv.M() > 0.4 && lv.M() < 3.0 ){
					// book->fill( "wdeltaPhi_pd1_fold_all", foldPi(lv1.DeltaPhi( lv )), tpcEfficiencyWeight( lv.Pt(), lv.M() ) );
					// book->fill( "wdeltaPhi_pd1_2fold_all", foldPi2(lv1.DeltaPhi( lv )), tpcEfficiencyWeight( lv.Pt(), lv.M() ) );
				}

				book->fill( "deltaPhi_pd1_fold_mass", lv.M(), foldPi(lv1.DeltaPhi( lv )) );
				// book->fill( "wdeltaPhi_pd1_fold_mass", lv.M(), foldPi(lv1.DeltaPhi( lv )), tpcEfficiencyWeight( lv.Pt(), lv.M() ) );

				book->fill( "mDCA", pair->d1_mDCA );
				book->fill( "mDCA", pair->d2_mDCA );

				book->fill( "mDCA_mPt", pair->d1_mPt, pair->d1_mDCA );
				book->fill( "mDCA_mPt", pair->d2_mPt, pair->d2_mDCA );

				book->fill( "mNHitsFit", pair->d2_mNHitsFit );
				book->fill( "mNHitsFit", pair->d2_mNHitsFit );
				
				// LOG_F( INFO, "lv1.Phi()=%f, lv2.Phi()=%f, deltaPhi/pi=%f", lv1.Phi(), lv2.Phi(), aco );
				// LOG_F( INFO, "asym=%f", fabsasym  );

			} // end X2ee and X2pipi cuts
			else {
				book->fill( "chipidcutNoSel", x2pipi, x2ee );
				book->fill( "mass_chipidcutNoSel", lv.M(), x2ee );
				book->fill( "y_chipidcutNoSel", lv.Rapidity(), x2ee );
				book->fill( "pt_chipidcutNoSel", lv.Pt(), x2ee );
				book->fill( "pt2_chipidcutNoSel", lv.Pt()*lv.Pt(), x2ee );
				book->fill( "ct_chipidcutNoSel", costheta, x2ee );
				if ( lv.M() > 0.4 && lv.M() < 3.0 ) book->fill( "dphi_chipidcutNoSel", dPhi_pd1_fold, x2ee );
			}
		} // end DeltaDeltaTof cuts



	} //analyzeEvent



	void eventWithoutTrackQA(FemtoPair * pair){

		TLorentzVector lv1, lv2, lv;
		lv1.SetPtEtaPhiM( pair->d1_mPt, pair->d1_mEta, pair->d1_mPhi, 0.0005109989461 );
		lv2.SetPtEtaPhiM( pair->d2_mPt, pair->d2_mEta, pair->d2_mPhi, 0.0005109989461 );
		lv = lv1 + lv2;

		double c_light = 29.9792458; // m / ns
		double m_electron = 0.0005109990615;

		double xpipi = pow( pair->d1_mNSigmaPion, 2 ) + pow( pair->d2_mNSigmaPion, 2 );
		double x2ee   = pow( pair->d1_mNSigmaElectron, 2 ) + pow( pair->d2_mNSigmaElectron, 2 );


		if ( 0 == pair->mChargeSum ){
			if ( x2ee < XeeCut && XeeXpipi * x2ee < xpipi && xpipi < XpipiMaxCut ){
				book->fill( "failed_notof_mNHitsFit_mPt_pos", pair->d1_mPt, pair->d1_mNHitsFit - 1 );
				book->fill( "failed_notof_mNHitsFit_mPt_neg", pair->d2_mPt, pair->d2_mNHitsFit - 1 );

				book->fill( "failed_notof_mNHitsDedx_mPt_pos", pair->d1_mPt, pair->d1_mNHitsDedx );
				book->fill( "failed_notof_mNHitsDedx_mPt_neg", pair->d2_mPt, pair->d2_mNHitsDedx );
			}
		}
	} //eventWithoutTrackQA()




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

