#include "TCapTrack.hxx"
ClassImp(CP::TCapTrack)

CP::TCapTrack::TCapTrack(): TNamed("TCapTrack","TCapTrack")
{
  clear();
}

CP::TCapTrack::~TCapTrack()
{
}

void CP::TCapTrack::clear()
{
  edep=0;
  positionVec.Clear();
  positionVariance.Clear();
  dimensions=0;
  length=0;
  isXTrack=false;
  isYTrack=false;
  isZTrack=false;
  directionVec.Clear();
  mass=0;
  width=0;
  quality=-1;
  ndof=0;
  trkhits.clear();
  nodes.clear();

  /*
  frontPos.Clear();
  frontVar.Clear();
  frontDir.Clear();
  frontDvar.Clear();
  backPos.Clear();
  backVar.Clear();
  backDir.Clear();
  backDvar.Clear();
  */
}

void CP::TCapTrack::print(int itrack)
{
  printf("\n *** TCapTrack %i quality %.3f dof %i dim. %i length %.2f edep %.2E (is XYZ(%i,%i,%i)  with %i hits %i nodes *** ",itrack,quality,ndof,dimensions,length,edep,isXTrack,isYTrack,isZTrack,
      (int) trkhits.size(), (int) nodes.size() );
  printf(" direction (%.3f,%.3f,%.3f)  position  (%.3f,%.3f,%.3f)  variance (%.3f,%.3f,%.3f)   \n ",
      directionVec.X(),directionVec.Y(),directionVec.Z(),
      positionVec.X(),positionVec.Y(),positionVec.Z(),
      positionVariance.X(),positionVariance.Y(),positionVariance.Z() );
  for(int ihit =0; ihit < int(trkhits.size()) ; ++ihit ) trkhits[ihit].print(ihit);
  for(int inode =0; inode < int(nodes.size()) ; ++inode ) nodes[inode].print(inode);
}

void CP::TCapTrack::print(int itrack,std::vector<CP::TCapHit> hits )
{
  printf("\n *** TCapTrack %i quality %.3f dof %i dim. %i length %.2f edep %.2E (is XYZ(%i,%i,%i)  with %i hits %i nodes *** ",itrack,quality,ndof,dimensions,length,edep,isXTrack,isYTrack,isZTrack,
      (int) trkhits.size(), (int) nodes.size() );
  printf(" direction (%.3f,%.3f,%.3f)  position  (%.3f,%.3f,%.3f)  variance (%.3f,%.3f,%.3f)   \n ",
      directionVec.X(),directionVec.Y(),directionVec.Z(),
      positionVec.X(),positionVec.Y(),positionVec.Z(),
      positionVariance.X(),positionVariance.Y(),positionVariance.Z() );
  for(int ihit =0; ihit < int(trkhits.size()) ; ++ihit ) trkhits[ihit].print(ihit,hits);
  for(int inode =0; inode < int(nodes.size()) ; ++inode ) nodes[inode].print(inode);
}

