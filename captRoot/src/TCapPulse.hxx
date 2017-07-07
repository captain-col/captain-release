/**
** MG, March 1 2016 
**/
#ifndef TCAPPULSE_DEFINED
#define TCAPPULSE_DEFINED
#include <iostream>
#include <string>
#include <vector>
#include <TNamed.h>
#include <TVector3.h>
#include <TLorentzVector.h>
using namespace std;

namespace CP {
    class TCapPulse;;
};


// class to store info for the event

class CP::TCapPulse: public TNamed {
	public:
		TCapPulse();
		~TCapPulse();

		void clear();
		void print(int ipulse);

    /// The geometry node that was hit
    Int_t fGeomId;

    /// The measured charge for this hit.
    Float_t fCharge;

    /// The uncertainty in the measured charge.
    Float_t fChargeUncertainty;

    /// The measured "time" for this hit.
    Float_t fTime;

    /// The uncertainty for the timing.
    Float_t fTimeUncertainty;

    /// The RMS of the timing.
    Float_t fTimeRMS;

    /// The time of the first sample in the hit.
    Float_t fTimeStart;

    /// The time of the last sample in the hit.
    Float_t fTimeStop;

    /// The charge samples in the hit.
    std::vector<Float_t> fTimeSamples;
    
    /// This is set to true if the fast access fields below have been
    /// initialized.
    bool fInitialized; //! Don't Save

    /// The central position of the hit.  This is the center of the wire in
    /// the global coordinate system.
    TVector3 fPosition; //! Don't Save

    /// The uncertainty of the hit position in local coordinates
    TVector3 fUncertainty; //! Don't Save

    /// The spread of the hit position in local coordinates
    TVector3 fRMS; //! Don't Save

    /// The rotation of the hit.
    //TMatrixD fRotation; //! Don't Save   
   		
ClassDef(TCapPulse,1)
};
#endif

