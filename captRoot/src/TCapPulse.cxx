#include "TCapPulse.hxx"
ClassImp(CP::TCapPulse)

CP::TCapPulse::TCapPulse(): TNamed("TCapPulse","TCapPulse")
{
  clear();
}

CP::TCapPulse::~TCapPulse()
{
}

void CP::TCapPulse::clear()
{
  fGeomId=0;
  fCharge=0;
  fChargeUncertainty=0;
  fTime=0;
  fTimeUncertainty=0;
  fTimeRMS=0;
  fTimeStart=0;
  fTimeStop=0;
  fTimeSamples.clear();
  fInitialized=0; //! Don't Save
  fPosition.Clear(); //! Don't Save
  fUncertainty.Clear(); //! Don't Save
  fRMS.Clear(); //! Don't Save
}

void CP::TCapPulse::print(int ipulse)
{
  printf("\n *** TCapPulse %i  q %f time %f  samples %i  *** ",ipulse,fCharge,fTime, (int) fTimeSamples.size() );
}

