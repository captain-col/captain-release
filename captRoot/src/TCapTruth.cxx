#include "TCapTruth.hxx"
ClassImp(CP::TCapTruth)

CP::TCapTruth::TCapTruth(): TNamed("TCapTruth","TCapTruth")
{
  clear();
}

CP::TCapTruth::~TCapTruth()
{
}

void CP::TCapTruth::clear()
{
  RunId=0;
  EventId=0;
  SubrunId=0;
  NDrift=0;
  NCryo=0;
  NOther=0;
  //segment.clear(); 
  trajectory.clear(); 
  pvertex.clear(); 
  pparticle.clear();
}

void CP::TCapTruth::print(int ievent)
{
  printf("\n *** TCapTruth event %i Id %i traj points in drift %i cryo %i other %i **** \n", ievent,EventId,NDrift,NCryo,NOther);

  printf("      truth event %i with %i verticies:   \n", ievent,(int) pvertex.size() );
  for(int ipv =0; ipv< int(pvertex.size()) ; ++ ipv )  pvertex[ipv].print(ipv);
  
  printf("      truth event %i with %i particles:   \n", ievent,(int) pparticle.size() );
  for(int ipp =0; ipp< int(pparticle.size()) ; ++ ipp ) pparticle[ipp].print(ipp);
  
  //printf("      truth event %i with %i segments:   \n", ievent,(int) segment.size() );
  //for(int ips =0; ips< segment.size() ; ++ ips ) segment[ips].print(ips);

  printf("      truth event %i with %i trajectories:   \n", ievent,(int) trajectory.size() );
  for(int ipt =0; ipt< trajectory.size() ; ++ ipt ) trajectory[ipt].print(ipt);

}

