#include <vector>
#include <TLorentzVector.h>
#include <TVector3.h>

enum {NTRK=0,NCLU,NSHO,UNKN,ALL};
int eventTypes[ALL+1];
float feventTypes[ALL+1];

void wnr()
{
  TString tag("reco-6081-n1");
  //TString tag("nb_pg_beam_000001_000_reco_aff7939ec5_medium");
  TString inputFileName = TString("$CAPTANA/captAna-")+tag+TString(".root");
  printf(" opening file %s \n",inputFileName.Data()); 
  TFile *infile = new TFile(inputFileName);
  TTree *atree=NULL;
  int aSize = 0;
  atree = (TTree*) infile->Get("anaTree");
  if(atree) aSize=atree->GetEntriesFast();
  printf(" anaTree with %i entries \n",aSize);

  if(aSize==0) return;
  // open ouput file and make some histograms
  TString outputFileName = TString("captRoot-")+tag+TString(".root");
  TFile *outfile = new TFile(outputFileName,"recreate");
  printf(" opening output file %s \n",outputFileName.Data());
 
  TH1I* hNumTrack = new TH1I("NumTrack","recon tracks/event",50,0,50); 
  TH1F* hTrackCharge = new TH1F("TrackCharge"," summed charge ",100,0,5.0E6);
  TNtuple *ntTracks = new TNtuple("ntTracks","tracks ","ev:trk:q:t:x:y:z");
  

  // this access the tree 
  CP::TCapEvent* event = new CP::TCapEvent();
  atree->SetBranchAddress("event",&event);

  for(int ityp = NTRK; ityp <ALL+1; ++ityp) { eventTypes[ityp]=0; feventTypes[ityp]=0;} 

  for(int entry = 0; entry<aSize; ++entry) { // tree is filled once per event
    atree->GetEntry(entry);

    /*
       printf(" %i) event %i #hits %i #tracks %i truth verticies %i particles %i trajectories %i  \n",
       entry,event->EventId,(int) event->hits.size(), (int) event->tracks.size(),
       (int) truth->pvertex.size(), (int) truth->pparticle.size(), (int) truth->trajectory.size());
       */
    if(eventTypes[ALL]>0)
      for(int ityp = NTRK; ityp <ALL; ++ityp)  feventTypes[ityp] = 100.0*float(eventTypes[ityp])/float(eventTypes[ALL]);
    if(entry%1000==0) {
      printf(" summary all %i tracks  %i (%.2f %)  clusters %i (%.2f %)  showers %i (%.2f %)  nothing %i (%.2f %) \n ",eventTypes[ALL],
          eventTypes[NTRK],feventTypes[NTRK],
          eventTypes[NCLU],feventTypes[NCLU],
          eventTypes[NSHO],feventTypes[NSHO],
          eventTypes[UNKN],feventTypes[UNKN]);
    }
            
    //printf(" event %i tracks %i clusters %i showers %i \n",entry,(int) event->tracks.size(),(int) event->showers.size(), (int) event->clusters.size() );
    if(event->tracks.size()>0) { 
      printf(" event %i has %i tracks \n",entry,(int) event->tracks.size());
      ++eventTypes[NTRK];
    } 
    if(event->clusters.size()>0) {
      printf(" event %i has %i clusters \n",entry, (int) event->clusters.size());
      ++eventTypes[NCLU]; 
    }
    if(event->showers.size()>0) { 
      printf(" event %i has %i showers \n",entry, (int) event->showers.size());
      ++eventTypes[NSHO]; 
    }
    if(event->tracks.size()==0&&event->clusters.size()==0&&event->showers.size()==0) ++eventTypes[UNKN]; 
    ++eventTypes[ALL];
    // recon plots 
    // loop over all reconstructed tracks in the event
    for(unsigned itrk = 0; itrk<event->tracks.size(); ++itrk) {
      float trackq=0;
      unsigned numTrackHits = event->tracks[itrk].hits.size();
      for(unsigned ihit = 0; ihit<numTrackHits; ++ihit) {
        float qtrk = event->tracks[itrk].hits[ihit].q;
        float ttrk = event->tracks[itrk].hits[ihit].t;
        float xtrk = event->tracks[itrk].hits[ihit].x;
        float ytrk = event->tracks[itrk].hits[ihit].y;
        float ztrk = event->tracks[itrk].hits[ihit].z;
        int evtrk = event->tracks[itrk].hits[ihit].iev;
        trackq += qtrk;
        ntTracks->Fill(float(entry),float(itrk),qtrk,ttrk,xtrk,ytrk,ztrk);
      }
      hTrackCharge->Fill(trackq);
    }
  
  }
     if(eventTypes[ALL]>0)
        for(int ityp = NTRK; ityp <ALL; ++ityp)  feventTypes[ityp] = 100.0*float(eventTypes[ityp])/float(eventTypes[ALL]);
     printf(" summary all %i tracks  %i (%.2f %)  clusters %i (%.2f %)  showers %i (%.2f %)  nothing %i (%.2f %) \n ",eventTypes[ALL],
         eventTypes[NTRK],feventTypes[NTRK],
         eventTypes[NCLU],feventTypes[NCLU],
         eventTypes[NSHO],feventTypes[NSHO],
         eventTypes[UNKN],feventTypes[UNKN]);
  

  outfile->Write();
}
