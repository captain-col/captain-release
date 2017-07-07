/**
** MG, December 2015 
**/
#ifndef TCAPSHOWER_DEFINED
#define TCAPSHOWER_DEFINED
#include <iostream>
#include <string>
#include <vector>
#include <TNamed.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TCapReconHit.hxx>
using namespace std;

namespace CP {
    class TCapShower;;
};


// class to store info for the event

class CP::TCapShower: public TNamed {
	public:
		TCapShower();
		~TCapShower();

		void clear();
		void print(int ishower);
		// data elements
		double edep;

    ///  track starting position.
    TLorentzVector positionVec;

    ///  track starting position uncertainty.
    TLorentzVector positionVariance;

    ///  number of (non-free) spacial dimensions 
    int dimensions;

    /// Check if this track has X information.
    bool  isXShower;

    /// Check if this track has Y information.
    bool isYShower;

    /// Check if this track has Z information.
    bool isZShower;

    ///  track direction.
    TVector3 directionVec;

    double coneAngle;

    std::vector<CP::TCapReconHit> swrhits;
		
ClassDef(TCapShower,3)
};
#endif

