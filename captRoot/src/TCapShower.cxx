#include "TCapShower.hxx"
ClassImp(CP::TCapShower)

CP::TCapShower::TCapShower(): TNamed("TCapShower","TCapShower")
{
  clear();
}

CP::TCapShower::~TCapShower()
{
}

void CP::TCapShower::clear()
{
  edep=0;
  positionVec.Clear();
  positionVariance.Clear();
  dimensions=0;
  isXShower=false;
  isYShower=false;
  isZShower=false;
  directionVec.Clear();
  coneAngle=0;
  swrhits.clear();

}

void CP::TCapShower::print(int ishower)
{
  printf("\n *** TCapShower %i  edep %f cone %f  hits %i  *** ",ishower,edep,coneAngle, (int) swrhits.size() );
  for(int ihit =0; ihit < int(swrhits.size()) ; ++ihit ) swrhits[ihit].print(ihit);
}

