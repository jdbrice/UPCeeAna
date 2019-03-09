

// RooBarb
#include "XmlConfig.h"
#include "TaskEngine.h"
using namespace jdb;

// STL
#include <iostream>
#include <exception>

#include "Analyzer.h"
#include "TofTagProbe.h"
#include "Fitter.h"
#include "ZDCFitter.h"
#include "ZDCMonAna.h"
#include "ZDCFitterUU.h"
#include "ZDCMonFitter.h"
#include "MagPlotter.h"

#define LOGURU_IMPLEMENTATION 1
#include "vendor/loguru.h"




int main( int argc, char* argv[] ) {
	// loguru::add_file("everything.log", loguru::Truncate, loguru::Verbosity_MAX);

	loguru::init(argc, argv);
	Logger::setGlobalLogLevel( "none" );

	TaskFactory::registerTaskRunner<MagPlotter>( "MagPlotter" );	
	TaskFactory::registerTaskRunner<Analyzer>( "Analyzer" );
	TaskFactory::registerTaskRunner<TofTagProbe>( "TofTagProbe" );
	TaskFactory::registerTaskRunner<Fitter>( "Fitter" );	
	TaskFactory::registerTaskRunner<ZDCFitter>( "ZDCFitter" );	
	TaskFactory::registerTaskRunner<ZDCFitterUU>( "ZDCFitterUU" );
	TaskFactory::registerTaskRunner<ZDCMonFitter>( "ZDCMonFitter" );
	TaskFactory::registerTaskRunner<ZDCMonAna>( "ZDCMonAna" );
	

	TaskEngine engine( argc, argv, "Analyzer" );


	return 0;
}
