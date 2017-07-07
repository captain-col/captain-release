/**
** MG, December 2015 
**/
#ifndef TCAPTRACKNODE_DEFINED
#define TCAPTRACKNODE_DEFINED
#include <iostream>
#include <string>
#include <vector>
#include <TNamed.h>
#include <TLorentzVector.h>
using namespace std;

namespace CP {
    class TCapTrackNode;;
};


// class to store info for the event

class CP::TCapTrackNode: public TNamed {
	public:
		TCapTrackNode();
		~TCapTrackNode();

		void clear();
		void print(int inode);
		// data elements
    //

    double edep;
    double edepVariance;
    TLorentzVector positionVec;
    TLorentzVector positionVariance;
		
ClassDef(TCapTrackNode,1)
};
#endif

