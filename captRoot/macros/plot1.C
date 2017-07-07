#include <vector>
#include <TLorentzVector.h>
#include <TVector3.h>
#include <TFile.h>
#include <TH1F.h>
#include <TTree.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <TCapEvent.hxx>
#include <TCapHit.hxx>

enum {NHITS=0,NTRK,NCLU,NSHO,UNKN,ALL};
int eventTypes[ALL+1];
float feventTypes[ALL+1];
enum {NFEM=16};
enum {NASIC=4};

void plot1(int entry=0)
{
  //TString tag("clusterCalibTPC-6339");
  //TString tag("recon-clusterCalibTPC-6336NEVEvent40");
//  TString tag("reconclusterCalibTPC-6300-n50");
  //TString tag("mc_pg_muon-20-n100");
  //TString tag("cluster-6389-12");
  TString tag("mc_pg_muon-20-100_reco-short-lifetime");     //mc_pg_muon-20-n100");
  bool isMC = false;
  if(tag.Contains("pg")) isMC = true;
  char foutName[250];
  sprintf(foutName,"charge-%s.root",tag.Data());
  printf(" out file name %s \n",foutName);
  fout = new TFile(foutName,"RECREATE");
  //TString directory("PDSF_DATA/");
  TString directory("$BRIDGE/WNRoffline/");
 
  // now get captana data file
  //TString tag("cluster-6300-n500-Cosmics");
  TString inputFileName = directory + TString("captAna-")+tag+TString(".root");
  cout << " opening " << inputFileName << endl;
  TFile *infile = new TFile(inputFileName,"READONLY");
  if(!infile) { printf(" input file %s not found \n",inputFileName.Data()); return ; }
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
 

  TH1F* hHitXCharge = new TH1F("HitXCharge"," X charge ",1000,0,1.0E5);
  TH1F* hHitUCharge = new TH1F("HitUCharge"," U charge ",1000,0,1.0E5);
  TH1F* hHitVCharge = new TH1F("HitVCharge"," V charge ",1000,0,1.0E5);
  //TH1F* hNoiseCharge = new TH1F("NoiseCharge"," bad channel charge ",10000,0,5.0E6);
  //TH1F* hQuality = new TH1F("Quality"," track quality ",1000,0,100);
  //TH1F* hQualityDOF = new TH1F("QualityDOF"," track quality/dof ",100,0,10);

  // this access the tree 
  CP::TCapEvent* event = new CP::TCapEvent();
  atree->SetBranchAddress("event",&event);

   vector<float> tvec0(0);
   vector<float> xvec0(0);
   vector<float> tveca(0);
   vector<float> xveca(0);

  // u plane 
   vector<float> tvec1(0);
   vector<float> xvec1(0);
  // v plane 
   vector<float> tvec2(0);
   vector<float> xvec2(0);
   

    atree->GetEntry(entry);
    int runId = event->RunId;
    int eventId = event->EventId;

    printf(" run %i event %i hits %i \n",runId, eventId, (int) event->hits.size());
  
   // Loop over all entries of the TTree or TChain.
   
    tvec0.clear();
    xvec0.clear();
    tvec1.clear();
    xvec1.clear();
    tvec2.clear();
    xvec2.clear();

   std::vector<CP::TCapHit> fhits= event->hits;
   for(unsigned ihit =0 ; ihit<fhits.size() ; ++ihit) {
     CP::TCapHit ahit = fhits[ihit];
     //ahit.print(ihit);
     Int_t iev = ahit.iev;
		 Int_t crate = ahit.crate;
		 Int_t fem = ahit.fem;
		 Int_t asic = ahit.asic;
		 Int_t nchan = ahit.nchan;
		 Int_t plane = ahit.plane;
		 Int_t wire = ahit.wire;
     if(plane!=0) continue;
     //if(wire<160) continue;
     //if(wire>180) continue;
     //if(ahit.t>2200000.) continue;
     //if(ahit.t<2145000.) continue;
     //if(ahit.t>2200000.) continue;
     float hitTime =ahit.t*1E-3; // convert to mircroseconds
     printf(" %i) plane %i wire %i time %f %f \n",ihit,plane,wire,ahit.t,hitTime);
     if(wire<150&&!isMC) {
     if(wire%2==0) wire = wire - 1;
     else wire = wire + 1;
     } else if(!isMC) {
     if(wire%2==0) wire = wire + 1;
     else wire = wire - 1;
     }

     if(ahit.plane==0) {
       tvec0.push_back(hitTime);
       xvec0.push_back(wire);
       tveca.push_back(hitTime);
       xveca.push_back(ahit.wire);

       hHitXCharge->Fill(ahit.q);
     }
     if(ahit.plane==1) {
       tvec1.push_back(hitTime);
       xvec1.push_back(wire);
       hHitVCharge->Fill(ahit.q);
     }
     if(ahit.plane==2) {
       tvec2.push_back(hitTime);
       xvec2.push_back(wire);
       hHitUCharge->Fill(ahit.q);
     }
     
   }
    char gatitle[120];
    char catitle[120];

    printf("sizes are  %lu %lu %lu \n ",xvec0.size(),xvec1.size(),xvec2.size());
    if(tvec0.size()>0) { 
    sprintf(gatitle,"run%i-Event-%i-x-plane-%s",runId,eventId,tag.Data());
    sprintf(catitle,"all-time-wire-run%i-Event-%i-x-plane-%s",runId,eventId,tag.Data());
    TCanvas *ca = new TCanvas(catitle,catitle);
    TGraph *gaxt = new TGraph(tvec0.size(),&(xvec0[0]),&(tvec0[0]));
    TGraph *gaat = new TGraph(tveca.size(),&(xveca[0]),&(tveca[0]));

    gaxt->SetTitle(gatitle);
    gaxt->GetHistogram()->GetXaxis()->SetTitle("wire x plane "); 
    gaxt->GetHistogram()->GetYaxis()->SetTitle("time ({#mu}s)"); 
    gaxt->SetMarkerStyle(21);
    gaxt->SetMarkerSize(.4);
    gaxt->SetMarkerColor(kBlue);
    gaat->SetMarkerColor(kRed);
    gaat->SetMarkerStyle(21);
    gaat->SetMarkerSize(.4);

    gaxt->Draw("ap");
    gaat->Draw("p");
    //fout->Append(ca);
    }
    return;
    //
     
    if(tvec1.size()>0) {
    sprintf(gatitle,"run%i-Event-%i-v-plane-%s",runId,eventId,tag.Data());
    sprintf(catitle,"all-time-wire-run%i-Event-%i-v-plane-%s",runId,eventId,tag.Data());
    TCanvas *cav = new TCanvas(catitle,catitle);
    TGraph *gavt = new TGraph(tvec1.size(),&(xvec1[0]),&(tvec1[0]));
    gavt->SetTitle(gatitle);
    gavt->GetHistogram()->GetXaxis()->SetTitle("wire v plane "); 
    gavt->GetHistogram()->GetYaxis()->SetTitle("time ({#mu}s)"); 
    gavt->SetMarkerStyle(21);
    gavt->SetMarkerSize(.4);
    gavt->SetMarkerColor(kBlue);
    gavt->Draw("ap");
    //fout->Append(cav);
    }


    if(tvec2.size()>0) {
    sprintf(gatitle,"run%i-Event-%i-u-plane-%s",runId,eventId,tag.Data());
    sprintf(catitle,"all-time-wire-run%i-Event-%i-u-plane-%s",runId,eventId,tag.Data());
    TCanvas *cau = new TCanvas(catitle,catitle);
    TGraph *gaut = new TGraph(tvec2.size(),&(xvec2[0]),&(tvec2[0]));
    gaut->SetTitle(gatitle);
    gaut->GetHistogram()->GetXaxis()->SetTitle("wire u plane "); 
    gaut->GetHistogram()->GetYaxis()->SetTitle("time ({#mu}s)"); 
    gaut->SetMarkerStyle(21);
    gaut->SetMarkerSize(.4);
    gaut->SetMarkerColor(kBlue);
    gaut->Draw("ap");
    }
    //fout->Append(cau);

}
