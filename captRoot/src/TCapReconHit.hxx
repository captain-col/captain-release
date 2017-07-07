/**
** MG, December 2015 
**/
#ifndef TCAPRECONHIT_DEFINED
#define TCAPRECONHIT_DEFINED
#include <iostream>
#include <string>
#include <TNamed.h>
#include <TVector3.h>
#include <TCapHit.hxx>
using namespace std;

namespace CP {
    class TCapReconHit;;
};


// class to store info for the event

class CP::TCapReconHit: public TNamed {
	public:
		TCapReconHit();
		~TCapReconHit();

		void clear();
		void print(int ihit=0);
		void print(int ihit,std::vector<CP::TCapHit> hits );
		// data elements
		Int_t iev;
		Int_t crate;
		Int_t fem;
		Int_t asic;
		Int_t nchan;
		Int_t plane;
		Int_t  wire;
		Float_t q;
		Float_t dq;
		Float_t x;
		Float_t dx;
		Float_t y;
		Float_t dy;
		Float_t z;
		Float_t dz;
		Float_t t;
		Float_t dt;
		Float_t rmst;
    Int_t nconstituents;
    Int_t ndigits;
    vector<Int_t> conhits; // coresponding cluster
    TVector3 position;
    TVector3 positionUnc;
    TVector3 positionRMS;
ClassDef(TCapReconHit,1)
};
#endif

