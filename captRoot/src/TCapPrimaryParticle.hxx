#ifndef TCapPrimaryParticle_hxx_seen
#define TCapPrimaryParticle_hxx_seen

#include <string>
#include <vector>

#include <TObject.h>
#include <TLorentzVector.h>


namespace CP {
    class TCapPrimaryParticle;
}

/// A class to save a G4 trajectory into a root output file without linking to
/// geant.  A trajectory is the truth information about the path of a particle
/// through the G4 simulation. It saves the parent trajectory that generated
/// this particle, the initial momentum of the particle, and the path followed
/// by the particle in the detector.  
class CP::TCapPrimaryParticle: public TObject {
  public :
    TCapPrimaryParticle();
    virtual ~TCapPrimaryParticle();
    void clear();
    void print(int ip);

    /// The vertex id that this particle comes from.
    Int_t TrackId;
    Int_t VertexId;
    Int_t ParentId;
    Int_t PDG;
    Float_t Mass;
    Int_t Charge;
    TLorentzVector Momentum;
ClassDef(TCapPrimaryParticle,3)    
 };
#endif
