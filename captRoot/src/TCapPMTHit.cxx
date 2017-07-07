#include "TCapPMTHit.hxx"
ClassImp(CP::TCapPMTHit)

CP::TCapPMTHit::TCapPMTHit(): TNamed("TCapPMTHit","TCapPMTHit")
{
  clear();
}

CP::TCapPMTHit::~TCapPMTHit()
{
}

void CP::TCapPMTHit::clear()
{
  geom="unknown";
  time=0;
  timeUnc=0;
  timeRms=0;
  charge=0;
  chargeUnc=0;
  position.Clear();
  positionUnc.Clear();
  positionRms.Clear();
  tstart=0;
  tstop=0;
  nsamples=0;
  qsamples.clear();		 
}

void CP::TCapPMTHit::print(int ihit)
{
  printf(" TCapPMTHit geo is %s \n",geom.c_str());
  printf(" \n \n TCapPMTHit %i  time %f timeUnc %f timeRms %f  charge %f chargeUnc %f \n",ihit,time,timeUnc,timeRms,charge,chargeUnc);
  position.Print();
  positionUnc.Print();
  positionRms.Print();
  printf("      nsamples %i start %f stop %f \n",nsamples,tstart,tstop);
  for(int i=0; i<nsamples ; ++i) printf(" %i %f ; ",i,qsamples[i]);
  printf(" end of TCapPMTHit \n\n");

}

