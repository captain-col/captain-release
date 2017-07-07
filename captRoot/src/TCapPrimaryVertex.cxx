#include "TCapPrimaryVertex.hxx"

ClassImp(CP::TCapPrimaryVertex);

CP::TCapPrimaryVertex::TCapPrimaryVertex() 
{
  clear();
} 

CP::TCapPrimaryVertex::~TCapPrimaryVertex()
{ 
}

void CP::TCapPrimaryVertex::print(int iv){
  printf(" %i) vertex id %i t/position(%.2f,%.2f,%.2f,%.2f) \n",iv,VertexId,Position.T(),Position.X(),Position.Y(),Position.Z());

  printf("         with %i particles: ", (int) Particles.size() );
  for(int ipp =0; ipp< int(Particles.size()) ; ++ ipp ) printf("  %i ; ", Particles[ipp]);
  printf("\n");
}

void CP::TCapPrimaryVertex::clear() 
{
   VertexId=0;
   Position.SetXYZT(0,0,0,0);
   Particles.clear();
   Ninfo=0;
   Generator.Clear();
   Reaction.Clear();
}
