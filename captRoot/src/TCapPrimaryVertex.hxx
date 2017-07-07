#ifndef TCapPrimaryVertex_hxx_seen
#define TCapPrimaryVertex_hxx_seen

#include <string>
#include <vector>

#include <TObject.h>
#include <TLorentzVector.h>
#include <TString.h>


namespace CP {
    class TCapPrimaryVertex;
}

/// Create the G4Vertices tree in the TruthDir directory to save information
/// about the MC primary vertices and particles.  The MC informaion is in a
/// tree called "G4Vertices" in the "TruthDir" directory of the DST file. The
/// tree contains the Vertex vector with a TG4Vertex object for every vertex,
/// and the Particle vector of TG4Particle for every particle attached to a
/// vertex.  The tree is defined as:
///
/// * TruthDir/G4Vertices -- A tree for the primary particles started in G4.
///
///   * Vertex (std::vector<TG4Vertex>) A branch of TG4Vertex objects sorted
///         by the vertex number.
///
///   * Particle (std::vector<TG4Particle>) A branch of TG4Particle objects
///         sorted by primary particle id.
///                 

class CP::TCapPrimaryVertex: public TObject {
  public :
    TCapPrimaryVertex();
    virtual ~TCapPrimaryVertex();
    void clear();
    void print(int i);

    Int_t VertexId;
    TLorentzVector Position;
    TString Generator;
    TString Reaction;
    int Ninfo; // number of info particles

    /// A vector of id numbers for the truth particles associated with this vertex.
    std::vector<Int_t> Particles;
    
ClassDef(TCapPrimaryVertex,1)
};
#endif
