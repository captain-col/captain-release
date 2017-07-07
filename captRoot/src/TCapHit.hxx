/**
** MG, December 2015 
**/
#ifndef TCAPHIT_DEFINED
#define TCAPHIT_DEFINED
#include <iostream>
#include <string>
#include <TNamed.h>
#include <vector>

using namespace std;

namespace CP {
    class TCapHit;;
};


// class to store info for the event

class CP::TCapHit: public TNamed {
	public:
		TCapHit();
		~TCapHit();

		void clear();
		void print(int ihit=0);
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
		Float_t noise;
		Float_t  tstart;
		Float_t tstop;
    Int_t  nsamples;
    Float_t qpeak;
		std::vector<Float_t>  qsamples;		
ClassDef(TCapHit,3)
};
#endif

