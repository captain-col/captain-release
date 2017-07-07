/**
** MG, December 2015 
**/
#ifndef TCAPPMTHIT_DEFINED
#define TCAPPMTHIT_DEFINED
#include <iostream>
#include <string>
#include <TNamed.h>
#include <TVector3.h>
#include <vector>

using namespace std;

namespace CP {
    class TCapPMTHit;;
};


// class to store info for the event

class CP::TCapPMTHit: public TNamed {
	public:
		TCapPMTHit();
		~TCapPMTHit();

		void clear();
		void print(int ihit=0);
		// data elements
    std::string geom;
	  Float_t time;
	  Float_t timeUnc;
	  Float_t timeRms;
	  Float_t charge;
	  Float_t chargeUnc;
    TVector3 position;
    TVector3 positionUnc;
    TVector3 positionRms;
    Float_t tstart;
    Float_t tstop;
    Int_t  nsamples;
		std::vector<Float_t>  qsamples;		 
		ClassDef(TCapPMTHit,1)
};
#endif

