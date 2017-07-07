#include "TCapReconHit.hxx"
ClassImp(CP::TCapReconHit)

CP::TCapReconHit::TCapReconHit(): TNamed("TCapReconHit","TCapReconHit")
{
  clear();
}

CP::TCapReconHit::~TCapReconHit()
{
}

void CP::TCapReconHit::clear()
{
  iev=0;
  crate=0;
  fem=0;
  asic=0;
  nchan=0;
  plane=0;
  wire=0;
  q=0;
  dq=0;
  x=0;
  dx=0;
  y=0;
  dy=0;
  z=0;
  dz=0;
  t=0;
  dt=0;
  rmst=0;
  position.Clear();
  positionUnc.Clear();
  positionRMS.Clear();
  nconstituents=0;
  ndigits=0;
  conhits.clear(); 
  
}

void CP::TCapReconHit::print(int ihit)
{
  printf(" TCapReconHit %i (%i) ev %i crate %i fem %i asic %i nchan %i plane %i wire %i q %f dq %f  t %f rmst %f XYZ (%f,%f,%f) \n",
      ihit,(int) conhits.size() ,iev,crate,fem,asic,nchan,plane,wire,q,dq,t,rmst,position.X(),position.Y(),position.Z() );
}

void CP::TCapReconHit::print(int ihit, std::vector<CP::TCapHit> hits )
{
  printf(" TCapReconHit %i (%i) ev %i crate %i fem %i asic %i nchan %i plane %i wire %i q %f dq %f  t %f rmst %f XYZ (%f,%f,%f) \n",
      ihit,(int) conhits.size() ,iev,crate,fem,asic,nchan,plane,wire,q,dq,t,rmst,position.X(),position.Y(),position.Z() );
  for(unsigned icon=0; icon< conhits.size() ; ++icon) { 
    //printf(" icon %i \n",icon);
    hits[conhits[icon]].print(conhits[icon]);
  };

}

