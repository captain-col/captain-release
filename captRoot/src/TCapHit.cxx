#include "TCapHit.hxx"
ClassImp(CP::TCapHit)

CP::TCapHit::TCapHit(): TNamed("TCapHit","TCapHit")
{
  clear();
}

CP::TCapHit::~TCapHit()
{
}

void CP::TCapHit::clear()
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
  noise=0;
  tstart=0;
  tstop=0;
  nsamples=0;
  qpeak=0;
  qsamples.clear();
}

void CP::TCapHit::print(int ihit)
{
  printf(" TCapHit %i ev %i crate %i fem %i asic %i nchan %i plane %i wire %i q %f dq %f  t %f rmst %f noise %f samples %i(%u)  \n",
      ihit,iev,crate,fem,asic,nchan,plane,wire,q,dq,t,rmst,noise, nsamples,qsamples.size() );
}

