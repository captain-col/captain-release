#include <vector>
#include <TLorentzVector.h>
#include <TVector3.h>

enum {NTRK=0,NCLU,NSHO,UNKN,ALL};
int eventTypes[ALL+1];
float feventTypes[ALL+1];

void ana()
{
  TString tag("nb_pg_beam_000007_000_reco_de803004d1_medium");
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
 
  TH1I* hNumTraject = new TH1I("NumTraject","truth trajectories/event",50,0,50); 
  TH1I* hNumTrack = new TH1I("NumTrack","recon tracks/event",50,0,50); 
  TH1F* hPrimaryEnergyStart = new TH1F("PrimaryEnergyStart"," primary start energy (MeV) ",100,0,1000);
  TH1F* hPrimaryEnergyEnd = new TH1F("PrimaryEnergyEnd"," primary end energy (MeV) ",100,0,1000);
  TH1F* hPrimaryEnergyLoss = new TH1F("PrimaryEnergyLoss"," primary energy loss (MeV) ",100,0,1000);

  TH1F* hTrackCharge = new TH1F("TrackCharge"," summed charge ",100,0,5.0E6);

  TNtuple *ntTruth = new TNtuple("ntTruth","truth kinematics","pdg:mass:estart:eend");
  TNtuple *ntTruthTraj = new TNtuple("ntTruthTraj","truth trajectories","mass:length:estart:eend");
  TNtuple *ntKinetic = new TNtuple("ntKinetic","event kinematics","eloss:trackq");
  

  // this access the tree 
  CP::TCapEvent* event = new CP::TCapEvent();
  atree->SetBranchAddress("event",&event);
  CP::TCapTruth* truth = new CP::TCapTruth();
  atree->SetBranchAddress("truth",&truth);

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
    //truth plots
    int numTrajects=(int) truth->trajectory.size();
    int numTracks= (int) event->tracks.size();
    hNumTraject->Fill(numTrajects);
    hNumTrack->Fill(numTracks);
    TLorentzVector momentumStart = truth->pparticle[0].Momentum;
    unsigned end = truth->pparticle.size()-1;

    int pdg = truth->pparticle[0].PDG;
    float massStart = truth->pparticle[0].Mass;
    float massEnd = truth->pparticle[end].Mass;
      
    TLorentzVector momentumEnd = truth->pparticle[end].Momentum;
    hPrimaryEnergyStart->Fill(momentumStart.Energy()-massStart);
    hPrimaryEnergyEnd->Fill(momentumEnd.Energy()-massEnd);
    hPrimaryEnergyLoss->Fill(momentumStart.Energy() - momentumEnd.Energy());
    //momentum0.Print();
    float energyLoss = momentumStart.Energy() - momentumEnd.Energy();
    ntTruth->Fill(float(pdg),massStart,momentumStart.Energy()-massStart,momentumEnd.Energy()-massEnd);
    vector<float> tLoss;
    // trajectories
    for(unsigned itr = 0; itr < truth->trajectory.size(); ++itr) {
      CP::TCapTrajectory ctrajectory =  truth->trajectory[itr];
      int Id = ctrajectory.TrajId;
      int Parent=  ctrajectory.ParentId;
      int Primary = ctrajectory.PrimaryId; 
      int PDG= ctrajectory.PDG;
      int Mass= ctrajectory.Mass;
      int Charge = ctrajectory.Charge;
      std::vector<TLorentzVector> Position = ctrajectory.Position;
      std::vector<TVector3> Momentum = ctrajectory.Momentum;
      std::vector<Int_t>   Region = ctrajectory.Region;
      TVector3 pstart = Position[0].Vect();
      unsigned end = Position.size()-1;
      TVector3 pend = Position[end].Vect();
      TVector3 pdiff = pstart-pend;
      // these containers all have the same size
      //printf(" trj %i %i %i %i \n", Id, (int) Position.size(), Momentum.size(), Region.size());
      ntTruthTraj->Fill(float(Mass),pdiff.Mag(),Momentum[0].Mag(),Momentum[end].Mag());
      float loss = Momentum[0].Mag()-Momentum[end].Mag();
      tLoss.push_back(loss);
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
      for(unsigned ihit = 0; ihit<numTrackHits; ++ihit) trackq += event->tracks[itrk].hits[ihit].q;
      //printf(" itrk %i q %f \n",itrk,trackq);
      hTrackCharge->Fill(trackq);
      float minDiff = 1E9;
      float bestLoss =0;
      // find best loss match
      for(unsigned ind = 0; ind<tLoss.size(); ++ind) {
        float diff = abs(tLoss[ind]-trackq);
        if(diff<minDiff) { 
          minDiff = diff;
          bestLoss = tLoss[ind];
        }
      }       
      ntKinetic->Fill(bestLoss,trackq);
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
