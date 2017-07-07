#include "TCapTrackNode.hxx"
ClassImp(CP::TCapTrackNode)

CP::TCapTrackNode::TCapTrackNode(): TNamed("TCapTrackNode","TCapTrackNode")
{
  clear();
}

CP::TCapTrackNode::~TCapTrackNode()
{
}

void CP::TCapTrackNode::clear()
{
  edep=0;
  edepVariance=0;
  positionVec.Clear();
  positionVariance.Clear();
}

void CP::TCapTrackNode::print(int inode)
{
  printf("\n *** TCapTrackNode %i edep %.3f var %.3f *** ",inode,edep,edepVariance);
  printf("position  (%.3f,%.3f,%.3f) variance (%.3f,%.3f,%.3f)   \n ",positionVec.X(),positionVec.Y(),positionVec.Z(),
      positionVariance.X(),positionVariance.Y(),positionVariance.Z() );
}

