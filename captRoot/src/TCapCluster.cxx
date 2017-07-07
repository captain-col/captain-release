#include "TCapCluster.hxx"
ClassImp(CP::TCapCluster)

CP::TCapCluster::TCapCluster(): TNamed("TCapCluster","TCapCluster")
{
  //fMoments.ResizeTo(3,3);
  clear();
}

CP::TCapCluster::~TCapCluster()
{
}

void CP::TCapCluster::clear()
{
  edep=0;
  edepVariance=0;
  dimensions=0;
  positionVec.Clear();
  positionVariance.Clear();
  isXCluster=false;
  isYCluster=false;
  isZCluster=false;
  longAxis.Clear();
  majorAxis.Clear();
  minorAxis.Clear();
  longExtent=0;
  majorExtent=0;
  minorExtent=0;
  
  hits.clear();
  //fMoments.Clear();
  for(int i=0; i<3; ++i) for(int j=0; j<3; ++j) moments[i][j]=0; 
}

void CP::TCapCluster::setMoments(float xx, float yy, float zz, float xy, float xz, float yz) 
{
    moments[0][0] = xx;
    moments[1][1] = yy;
    moments[2][2] = zz;
    moments[1][2] = xy;
    moments[1][0] = xy;
    moments[0][2] = xz;
    moments[2][0] = xz;
    moments[1][2] = yz;
    moments[2][1] = yz;
}


void CP::TCapCluster::print(int icluster )
{
  printf("\n *** TCapCluster %i edep %.3f var %.3f is XYZ(%i,%i,%i) with %i hits  *** \n",
      icluster,edep,edepVariance,isXCluster, isYCluster, isZCluster, (int) hits.size() );
  printf(" long  axis (%.3f,%.3f,%.3f) extent %.3f \n",longAxis.X(),longAxis.Y(),longAxis.Z(),longExtent);
  printf(" major axis (%.3f,%.3f,%.3f) extent %.3f \n",majorAxis.X(),majorAxis.Y(),majorAxis.Z(),majorExtent);
  printf(" minor axis (%.3f,%.3f,%.3f) extent %.3f \n",minorAxis.X(),minorAxis.Y(),minorAxis.Z(),minorExtent);
  printf("position  (%.3f,%.3f,%.3f) variance (%.3f,%.3f,%.3f)   \n ",positionVec.X(),positionVec.Y(),positionVec.Z(),
      positionVariance.X(),positionVariance.Y(),positionVariance.Z() );
  printf(" moments : \n");
  for(int i=0; i<3; ++i) {
    for(int j=0; j<3; ++j) printf(" %.3f , ",moments[i][j]); 
    printf(" \n");
  }
  for(int ihit =0; ihit < int(hits.size()) ; ++ihit ) hits[ihit].print(ihit);
  
}

