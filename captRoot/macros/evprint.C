#include <vector>
#include <TLorentzVector.h>
#include <TVector3.h>

enum {NTRK=0,NCLU,NSHO,UNKN,ALL};
int eventTypes[ALL+1];
float feventTypes[ALL+1];

void evprint(int entry=0)
{
 
  TString tag("cluster-6388-50");
  // now get captana data file
  TString directory("PDSF_DATA/");
  //TString tag("cluster-6300-n500-Cosmics");
  TString inputFileName = directory + TString("captAna-")+tag+TString(".root");
  cout << " opening " << inputFileName << endl;
  TFile *infile = new TFile(inputFileName,"READONLY");
  if(!infile) { printf(" input file %s not found \n",inputFileName.Data()); return ; }
  
  //TString tag("nb_pg_beam_000007_000_reco_de803004d1_medium");
  //TString tag("nb_pg_beam_000001_000_reco_aff7939ec5_medium");
  ///TString inputFileName = TString("$CAPTANA/captAna-")+tag+TString(".root");
  TTree *atree=NULL;
  int aSize = 0;
  atree = (TTree*) infile->Get("anaTree");
  if(atree) aSize=atree->GetEntriesFast();
  printf(" anaTree with %i entries \n",aSize);

  if(aSize==0) return;

  // this access the tree 
  CP::TCapEvent* event = new CP::TCapEvent();
  atree->SetBranchAddress("event",&event);
  CP::TCapTruth* truth = new CP::TCapTruth();
  atree->SetBranchAddress("truth",&truth);
    
  atree->GetEntry(entry);
  event->print(entry);
  truth->print(entry);
}
