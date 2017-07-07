/**
** MG, December 2015 
**/
#ifndef TCAPEVENT_DEFINED
#define TCAPEVENT_DEFINED
#include <iostream>
#include <string>
#include <TNamed.h>
#include <TTree.h>
#include <vector>
#include <TCapHit.hxx>
#include <TCapPMTHit.hxx>
#include <TCapReconHit.hxx>
#include <TCapTrack.hxx>
#include <TCapCluster.hxx>
#include <TCapShower.hxx>
using namespace std;

namespace CP {
    class TCapEvent;;
};


// class to store info for the event

class CP::TCapEvent: public TNamed {
	public:
		TCapEvent();
		~TCapEvent();

		void clear();
		void print(int ievent=0);
		// data elements
		Int_t           RunId;
		Int_t           EventId;
		Int_t           SubrunId;
		ULong_t timestamp;
		ULong_t nanoseconds; 
		std::vector<CP::TCapHit> hits;
		std::vector<CP::TCapPMTHit> phits;
		std::vector<CP::TCapTrack> tracks;
		std::vector<CP::TCapCluster> clusters;
		std::vector<CP::TCapShower> showers;
		
ClassDef(TCapEvent,3)
};
#endif

