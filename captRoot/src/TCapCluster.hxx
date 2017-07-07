/**
** MG, December 2015 
**/
#ifndef TCAPCLUSTER_DEFINED
#define TCAPCLUSTER_DEFINED
#include <iostream>
#include <string>
#include <vector>
#include <TNamed.h>
#include <TVector3.h>
#include <TLorentzVector.h>
//#include <TMatrixTSym.h> 
#include <TCapReconHit.hxx>
using namespace std;

namespace CP {
    class TCapCluster;;
};


// class to store info for the event

class CP::TCapCluster: public TNamed {
 
	public:
    typedef TMatrixTSym<float> MomentMatrix;

		TCapCluster();
		~TCapCluster();

    void setMoments(float xx, float yy, float zz, float xy, float xz, float yz);  

		void clear();
		void print(int icluster);
		// data elements
		Float_t edep;
		Float_t edepVariance;
    Int_t dimensions;

    ///  cluster starting position.
    TLorentzVector positionVec;

    ///  track starting position uncertainty.
    TLorentzVector positionVariance;

    /// Check if this cluster has X information.
    Bool_t isXCluster;

    /// Check if this cluster has Y information.
    Bool_t isYCluster;

    /// Check if this cluster has Z information.
    Bool_t isZCluster;

    //TMatrixTSym<float> fMoments;

    Float_t moments[3][3];

    TVector3 longAxis;
    TVector3 majorAxis;
    TVector3 minorAxis;
    double longExtent;
    double majorExtent;
    double minorExtent;
    

    std::vector<CP::TCapReconHit> hits;
		
ClassDef(TCapCluster,1)
};
#endif

