#include "TCapTrajectory.hxx"
ClassImp(CP::TCapTrajectory);

CP::TCapTrajectory::TCapTrajectory() 
{
  clear();
} 

CP::TCapTrajectory::~TCapTrajectory()
{ 
}

void CP::TCapTrajectory::clear() 
{
  TrajId=0;  
  ParentId=0;  
  PrimaryId=0;  
  PDG=0;  
  Mass=0;   
  Charge=0;  
  // each element in vector corresponds to a point on the particle path
  Position.clear();
  Momentum.clear();
  Region.clear();
  segments.clear();

}

void CP::TCapTrajectory::print(int itraj){
  printf(" %i) TCapTrajectory: id %i  parent %i  primary %i  PDG %i  mass %.3f  charge %i positions %i momenta %i regions %i \n ",itraj,
      TrajId, ParentId, PrimaryId, PDG, Mass, Charge, (int) Position.size(), (int) Momentum.size(), (int) Region.size()  );
  if(itraj==0) return;
  // detailed info 
  for(unsigned int ip=0; ip< Position.size(); ++ip)
    printf("     traj region %i  time/position (%.2f,%.2f,%.2f,%.2f) 3 momentum (%.2f %.2f %.2f) \n",Region[ip],
        Position[ip].T(),Position[ip].X(),Position[ip].Y(),Position[ip].Z(),Momentum[ip].X(),Momentum[ip].Y(),Momentum[ip].Z() );
  printf("      traj  %i with %i segments:   \n",itraj, (int) segments.size() );
  for(int iseg =0; iseg< int(segments.size()) ; ++ iseg ) segments[iseg].print(iseg);
  
}
