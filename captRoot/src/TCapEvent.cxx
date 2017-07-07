#include "TCapEvent.hxx"
ClassImp(CP::TCapEvent)

CP::TCapEvent::TCapEvent(): TNamed("TCapEvent","TCapEvent")
{
  clear();
}

CP::TCapEvent::~TCapEvent()
{
}

void CP::TCapEvent::clear()
{
  RunId=0;
  EventId=0;
  SubrunId=0;
  timestamp=0;
  nanoseconds=0;
  hits.clear(); 
  phits.clear(); 
  tracks.clear();
  clusters.clear();
  showers.clear();
}

void CP::TCapEvent::print(int ievent)
{
  printf("\n *** TCapEvent reconstructed event %i, Id %i with %i hits %i tracks %i showers %i clusters *** ",
      ievent,EventId,(int) hits.size(),(int) tracks.size(), (int) showers.size(), (int) clusters.size() );
  printf("  trigtime = %lu sec +  %lu usec \n", timestamp,nanoseconds );
  for(int itr =0; itr< int(tracks.size()); ++itr)   tracks[itr].print(itr,hits);
  for(int itr =0; itr< int(showers.size()); ++itr)  showers[itr].print(itr);
  for(int itr =0; itr< int(clusters.size()); ++itr) clusters[itr].print(itr);
}

