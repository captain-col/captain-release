#include "TCapPrimaryParticle.hxx"

ClassImp(CP::TCapPrimaryParticle);

CP::TCapPrimaryParticle::TCapPrimaryParticle() 
{
  clear();
} 

CP::TCapPrimaryParticle::~TCapPrimaryParticle()
{ 
}

void CP::TCapPrimaryParticle::print(int ip) {
  printf("%i) Particle Id %i VertexId %i ParentId %i PDG %i, Mass %f, Charge %i MomentumEP(%f,%f,%f,%f) \n",
      ip,TrackId,VertexId,ParentId,PDG,Mass,Charge,Momentum.T(),Momentum.X(),Momentum.Y(),Momentum.Z());

}

void CP::TCapPrimaryParticle::clear() 
{
  TrackId=0;
  ParentId=0;
  VertexId=0;
  PDG=0;
  Mass=0;
  Charge=0;
  Momentum.SetPxPyPzE(0,0,0,0);
}
