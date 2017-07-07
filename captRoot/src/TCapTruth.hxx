/**
** MG, December 2015 
**/
#ifndef TCAPTRUTH_DEFINED
#define TCAPTRUTH_DEFINED
#include <iostream>
#include <string>
#include <TNamed.h>
#include <TTree.h>
#include <vector>
#include <TCapHitSegment.hxx>
#include <TCapTrajectory.hxx>
#include <TCapPrimaryVertex.hxx>
#include <TCapPrimaryParticle.hxx>
using namespace std;

namespace CP {
    class TCapTruth;;
};


// class to store info for the event

class CP::TCapTruth: public TNamed {
	public:
		TCapTruth();
		~TCapTruth();

		void clear();
		void print(int ievent=0);
		// data elements
    Int_t           RunId;
    Int_t           EventId;
    Int_t           SubrunId;
    Int_t           NDrift;
    Int_t           NCryo;
    Int_t           NOther;
    //std::vector<CP::TCapHitSegment> segment; contained in trajectory
    std::vector<CP::TCapTrajectory> trajectory;
		std::vector<CP::TCapPrimaryVertex> pvertex;
		std::vector<CP::TCapPrimaryParticle> pparticle;
		
ClassDef(TCapTruth,3)
};
#endif

