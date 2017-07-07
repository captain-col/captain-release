/**
** MG, December 2015 
**/
#ifndef TCAPTRACK_DEFINED
#define TCAPTRACK_DEFINED
#include <iostream>
#include <string>
#include <vector>
#include <TNamed.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TCapReconHit.hxx>
#include <TCapHit.hxx>
#include <TCapTrackNode.hxx>
using namespace std;

namespace CP {
    class TCapTrack;;
};


// class to store info for the event

class CP::TCapTrack: public TNamed {
	public:
		TCapTrack();
		~TCapTrack();

		void clear();
		void print(int itrack);
		void print(int itrack,	std::vector<CP::TCapHit> hits );
		// data elements
		double edep;

    ///  track starting position.
    TLorentzVector positionVec;

    ///  track starting position uncertainty.
    TLorentzVector positionVariance;

    ///  number of (non-free) spacial dimensions 
    int dimensions;

    /// Check if this track has X information.
    bool  isXTrack;

    /// Check if this track has Y information.
    bool isYTrack;

    /// Check if this track has Z information.
    bool isZTrack;

    ///  track direction.
    TVector3 directionVec;

    ///  track mass.  The mass is not limited to the mass of a "known"
    /// particle, but represents a fitted value based on dEdX, or other
    /// measured properties.
    double mass;

    ///  width of the track.
    double width;

  /// goodness of fit for the reconstruction.
    double quality;
    

    double length;

    /// number of degrees of freedom in the reconstruction.
    int ndof;

    /*
    TLorentzVector frontPos;
    TLorentzVector frontVar;
    TVector3 frontDir;
    TVector3 frontDvar;
    TLorentzVector backPos;
    TLorentzVector backVar;
    TVector3 backDir;
    TVector3 backDvar;
    */

      
    std::vector<CP::TCapReconHit> trkhits;
    std::vector<CP::TCapTrackNode> nodes;
		
ClassDef(TCapTrack,3)
};
#endif

