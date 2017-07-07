/*
** vector sort must run compiled laser.C++
*/
#include <vector>
#include<algorithm>
#include<TStyle.h>
#include<TTree.h>
#include<TH1F.h>
#include<TF1.h>
#include<TLeaf.h>
#include<TFile.h>
#include<TBranch.h>
#include<TCanvas.h>
#include<TGraph.h>
#include<TGraphErrors.h>
#include <TLorentzVector.h>
#include <TVector3.h>


int runId;
TTree* atree;
CP::TCapEvent* event;
TF1 *flin;
TF1 *fexp;
TFile *fout;
using namespace std;
float laser1(int ievent, int plane, int wire_low, int wire_high,  float startTime , float endTime , float delta );

void laser(int eventId = 9 ){
  TString tag("clusterCalibTPC-6339-10");
  //TString tag("cluster-6081-10");
  //TString tag("cluster-6152-5");
  //TString tag("cluster-6141-6");
  TString runIdTag = tag(tag.First("-")+1,4);
  runId = atoi(runIdTag.Data());
  printf(" run %i \n",runId);
  
  //TString tag("nb_pg_beam_000001_000_reco_aff7939ec5_medium");
  TString inputFileName = TString("$CAPTANA/captAna-")+tag+TString(".root");
  printf(" opening file %s \n",inputFileName.Data()); 
  TFile *infile = new TFile(inputFileName);
  if(!infile) { printf(" input file %s not found \n",inputFileName.Data()); return ; }
  atree=NULL;
  int aSize = 0;
  atree = (TTree*) infile->Get("anaTree");
  if(atree) aSize=atree->GetEntriesFast();
  printf(" anaTree with %i entries \n",aSize);

  if(aSize==0) return;

 
  flin = new TF1("flin","[0]+x*[1]",150,300);
  fexp = new TF1("fexp","expo",1500,2000);
  flin->Print();
  fexp->Print();


  char foutName[250];
  cout << tag << endl;
  sprintf(foutName,"laser-%s-event%i.root",tag.Data(),eventId);
  printf(" out file name %s \n",foutName);
  fout = new TFile(foutName,"RECREATE");
  // 246,248,250,251
  vector<float> tzero;
  vector<int> nevent;
  //nevent.push_back(246);
  //nevent.push_back(248);
  //nevent.push_back(250);
  //nevent.push_back(251);
  //nevent.push_back(0);
 
  // this access the tree 
  event = new CP::TCapEvent();
  atree->SetBranchAddress("event",&event);

  //for(unsigned is=0; is<nevent.size(); ++is) tzero.push_back( laser1(tag,nevent[is],150,250,410.,450.,.5) );
  //printf(" start times of track \n");
  //for(unsigned is=0; is<tzero.size(); ++is) printf("  event %i, %0.f microsec \n",nevent[is],tzero[is]);


//float laser1(TString tag, int ievent, int thePlane, int wire_low, int wire_high, float startTime , float stopTime , float delta )
  
  laser1(tag,eventId,1, 160 , 200 , -20, 20,  5);
  //laser1(tag,eventId,100,120,615,660,5.);
  //laser1(tag,0,10,40,2010,2300.,10.);//6152
  //laser1(tag,eventId,150,221,410.,450.,5.); //6141,event 1
  //laser1(tag,eventId,1,30,2550.,2570.,.1); //6141,event 1

  fout->ls();
  fout->Write();
}


float laser1(TString tag, int ievent, int thePlane, int wire_low, int wire_high, float startTime , float stopTime , float delta )
{
  int entry = ievent-1;
  atree->GetEntry(entry);
  event->print(entry);
  int eventId = event->EventId;

   vector<float> tvec(0);
   vector<float> tsort(0);
   vector<float> dtvec(0);
   vector<float> xvec(0);
   vector<float> twec(0);
   vector<float> xwec(0);
   vector<float> qvec(0);
   vector<float> dqvec(0);
   vector<int> vwire(0);

  std::vector<CP::TCapHit> fhits= event->hits;
  printf(" number of calib hits in this event is %i \n",(int) fhits.size());
   
  if(fhits.size()==0) return 0;
 

  // x plane 
   vector<float> tvec1(0);
   vector<float> xvec1(0);
  // u plane 
   vector<float> tvec2(0);
   vector<float> xvec2(0);
  // v plane 
   vector<float> tvec3(0);
   vector<float> xvec3(0);
   


   // Loop over all entries of the TTree or TChain.
   for(int ihit =0 ; ihit<fhits.size() ; ++ihit) {
     CP::TCapHit ahit = fhits[ihit];
     ahit.print(entry);
     //if(ahit.q>5.0E3) continue;
     float hitTime =ahit.t*1E-3; // convert to mircroseconds 
     if(ahit.plane==0) {
       tvec1.push_back(hitTime);
       xvec1.push_back(ahit.wire);
     }
     if(ahit.plane==1) {
       tvec2.push_back(hitTime);
       xvec2.push_back(ahit.wire);
     }
     if(ahit.plane==2) {
       tvec3.push_back(hitTime);
       xvec3.push_back(ahit.wire);
     }
     
   }

  printf(" hits passing on plane 0 = %i plane 1 = %i plane 2 = %i\n",tvec1.size(),tvec2.size(),tvec3.size());

  char gatitle[80];
  char catitle[80];
  TCanvas *ca=NULL;
  if(tvec1.size()>0) {
    sprintf(gatitle,"run%i-Event%i-x-plane",runId,eventId);
    sprintf(catitle,"time-wire-run%i-Event%i-x-plane",runId,eventId);
    ca = new TCanvas(catitle,catitle);
    TGraph *gaxt = new TGraph(tvec1.size(),&(xvec1[0]),&(tvec1[0]));
    gaxt->SetTitle(gatitle);
    gaxt->GetHistogram()->GetXaxis()->SetTitle("wire x plane "); 
    gaxt->GetHistogram()->GetYaxis()->SetTitle("time ({#mu}s)"); 
    gaxt->GetHistogram()->GetYaxis()->SetRangeUser(-1600,3200); 
    gaxt->SetMarkerStyle(21);
    gaxt->SetMarkerSize(.4);
    gaxt->SetMarkerColor(kBlue);
    gaxt->Draw("ap");
    ca->Print(".pdf");
   }

  //return 0;

   if(tvec2.size()>0) {
    sprintf(gatitle,"run%i-Event%i-U-plane",runId,eventId);
    sprintf(catitle,"time-wire-run%i-Event%i-U-plane",runId,eventId);
    TCanvas *cau = new TCanvas(catitle,catitle);
    TGraph *gaut = new TGraph(tvec2.size(),&(xvec2[0]),&(tvec2[0]));
    gaut->SetTitle(gatitle);
    gaut->GetHistogram()->GetXaxis()->SetTitle("wire U plane "); 
    gaut->GetHistogram()->GetYaxis()->SetTitle("time ({#mu}s)"); 
    gaut->GetHistogram()->GetYaxis()->SetRangeUser(-1600,3200); 
    gaut->SetMarkerStyle(21);
    gaut->SetMarkerSize(.4);
    gaut->SetMarkerColor(kBlue);
    gaut->Draw("ap");
    cau->Print(".pdf");
   }

    
   if(tvec3.size()>0) {
   sprintf(gatitle,"run%i-Event%i-V-plane",runId,eventId);
    sprintf(catitle,"time-wire-run%i-Event%i-V-plane",runId,eventId);
    TCanvas *cav = new TCanvas(catitle,catitle);
    TGraph *gavt = new TGraph(tvec3.size(),&(xvec3[0]),&(tvec3[0]));
    gavt->SetTitle(gatitle);
    gavt->GetHistogram()->GetXaxis()->SetTitle("wire V plane "); 
    gavt->GetHistogram()->GetYaxis()->SetTitle("time ({#mu}s)"); 
    gavt->GetHistogram()->GetYaxis()->SetRangeUser(-1600,3200); 
    gavt->SetMarkerStyle(21);
    gavt->SetMarkerSize(.4);
    gavt->SetMarkerColor(kBlue);
    gavt->Draw("ap");
    cav->Print(".pdf");

   }

   // Loop over all entries of the TTree or TChain.
   for(int ihit =0 ; ihit<fhits.size() ; ++ihit) {
     CP::TCapHit ahit = fhits[ihit];
     if(ahit.plane!=thePlane) continue;
     float hitTime =ahit.t*1E-3; // convert to mircroseconds 
     twec.push_back(hitTime);
     xwec.push_back(ahit.wire);
     if(ahit.q<1) continue;
     //if(ahit.t>1000E3) continue;
     //if(ahit.t<0) continue;
     //if(ahit.dq/ahit.q>0.2) continue;
     if(ahit.wire<wire_low||ahit.wire>wire_high) continue;
     //if(hitTime<startTime || hitTime>stopTime ) continue;
     vwire.push_back(ahit.wire);
     tsort.push_back(hitTime);
     tvec.push_back(hitTime);
     dtvec.push_back(0.);
     xvec.push_back(ahit.wire);
     qvec.push_back(ahit.q);
     dqvec.push_back(ahit.dq);
     ahit.print(ihit);
     //printf(" %i q %f dq %f (%f) wire %i time = %f \n",ihit,ahit.q,ahit.dq,ahit.dq/ahit.q,ahit.wire,hitTime);
   }

   if(tsort.size()==0) { printf(" !!!!!!!!!!!!!!!!! no hits passed cuts ! \n"); return 0; }

   sort(tsort.begin(),tsort.end());

  printf(" SUMMARY plane %i  wires (%i,%i) times (%.2f,%.2f) delta %.2f \n",thePlane, wire_low, wire_high,startTime,stopTime,delta);
   printf("tsort : ");
   for(unsigned iw =0; iw<tsort.size(); ++iw) printf(" %i) %f; ",iw,tsort[iw]);
   printf("\n");
   

  // summed charge
  char htitle[80];
  float nbins = (tsort[tsort.size()-1]-tsort[0])/delta;
  sprintf(htitle,"qsum-run%i-Event%i-DeltaT=%0.f",runId,eventId,delta);
  TH1F *hsum = new TH1F(htitle,htitle,nbins,tsort[0],tsort[tsort.size()-1]+delta);

  sprintf(htitle,"qsumsq-run%i-Event%i-DeltaT=%0.f",runId,eventId,delta);
  TH1F *hsumsq = new TH1F(htitle,htitle,nbins,tsort[0],tsort[tsort.size()-1]+delta);


  sprintf(htitle,"qerr-run%i-Event%i-DeltaT=%0.f",runId,eventId,delta);
  TH1F *hqerr = new TH1F(htitle,htitle,nbins,tsort[0],tsort[tsort.size()-1]+delta);


  sprintf(htitle,"norm-run%i-Event%i-DeltaT=%0.f",runId,eventId,delta);
  TH1F *hnorm = new TH1F(htitle,htitle,nbins,tsort[0],tsort[tsort.size()-1]+delta);
  hsum->Sumw2();
  for(unsigned iq=0; iq<qvec.size() ; ++iq) {
    int ibin = hsum->FindBin(tvec[iq]);
    hsum->SetBinContent(ibin,   hsum->GetBinContent(ibin)+qvec[iq]);
    hsumsq->SetBinContent(ibin, hsumsq->GetBinContent(ibin)+pow(qvec[iq],2.));
    hqerr->SetBinContent(ibin,  hqerr->GetBinContent(ibin)+pow((dqvec[iq]/qvec[iq]),2.0));
    hnorm->SetBinContent(ibin,  hnorm->GetBinContent(ibin)+1.0);
  }

  //for(int ibin = 1; ibin<=hsum->GetNbinsX(); ++ibin)  hsum->SetBinError(ibin, hsum->GetBinContent(ibin)*sqrt(hqerr->GetBinContent(ibin))/hnorm->GetBinContent(ibin));
  for(int ibin = 1; ibin<=hsum->GetNbinsX(); ++ibin)  {
    float qnorm = hnorm->GetBinContent(ibin);
    if(qnorm<1) continue;
    float qsum2 = hsumsq->GetBinContent(ibin)/qnorm;
    float qsum =  hsum->GetBinContent(ibin)/qnorm;
    float qerr2 =  qsum2*hqerr->GetBinContent(ibin);
    float qrms=0;
    if(qnorm>1) qrms = sqrt(qsum2-qsum*qsum);
    else qrms= sqrt(qsum); //sqrt(qerr2);
    printf(" %i qnorm %.0f qsum2 %E qsum2^2 %E qerr %E qrms = %E \n",ibin, qnorm, qsum2 , qsum*qsum, sqrt(qerr2),qrms );
    hsum->SetBinError(ibin, qrms);
    //hsum->SetBinContent(ibin, qsum);
  }

  //hsum->Print("all");

  printf(" summed plot number of bins %i \n",hsum->GetNbinsX());
  for(int ibin = 1; ibin<=hsum->GetNbinsX(); ++ibin) if(hsum->GetBinContent(ibin)>0) printf(" ... %i %f q = %f +/- %f (%f)  \n",
      ibin,hsum->GetBinCenter(ibin),hsum->GetBinContent(ibin),hsum->GetBinError(ibin),hsum->GetBinError(ibin)/hsum->GetBinContent(ibin));


  gStyle->SetOptFit(1);

  char gtitle[80];
  char ctitle[80];
  sprintf(gtitle,"run%i-Event%i",runId,eventId);
  sprintf(ctitle,"time-wire-run%i-Event%i",runId,eventId);
  TCanvas *c1 = new TCanvas(ctitle,ctitle);
  TGraph *gxt = new TGraph(xvec.size(),&(xvec[0]),&(tvec[0]));
  gxt->SetTitle(gtitle);
  gxt->GetHistogram()->GetXaxis()->SetTitle("wire"); 
  gxt->GetHistogram()->GetYaxis()->SetTitle("time (#mu s)");
  gxt->SetMarkerStyle(21);
  gxt->SetMarkerSize(.4);
  gxt->SetMarkerColor(kBlue);
  gxt->Fit("flin","R");
  gxt->Draw("ap");
  c1->Print(".pdf");


  char gqtitle[80];
  char cqtitle[80];
  sprintf(gqtitle,"charge-vs-time-run%i-Event%i",runId,eventId);
  sprintf(cqtitle,"charge-time-run%i-Event%i",runId,eventId);
  TCanvas *cq1 = new TCanvas(cqtitle,cqtitle);
  TGraphErrors *gqt = new TGraphErrors(tvec.size(),&(tvec[0]),&(qvec[0]),&(dtvec[0]),&(dqvec[0]));
  gqt->SetTitle(gqtitle);
  gqt->SetMarkerStyle(21);
  gqt->SetMarkerSize(.4);
  gqt->SetMarkerColor(kBlue);
  gqt->GetHistogram()->GetYaxis()->SetTitle("charge"); 
  gqt->GetHistogram()->GetXaxis()->SetTitle("time (#mu s)"); 
  gqt->Draw("ap");
  cq1->Print(".pdf");


  
  char c2title[80];
  sprintf(c2title,"summed-charge-time-run%i-Event%i",runId,eventId);
  TCanvas *c2 = new TCanvas(c2title,c2title);
  //c2->SetLogy();
  hsum->Fit("fexp");
  double tau = -1./fexp->GetParameter(1);
  double tauError = fexp->GetParError(1)/fexp->GetParameter(1)/fexp->GetParameter(1);
  char sumTitle[80];
  char yTitle[80];
  sprintf(sumTitle,"#sum q (%.0f#mus) ",delta);
  sprintf(yTitle,"time (#mus) #tau = %0.2f #pm %0.2f",tau,tauError);
  hsum->SetMarkerStyle(21);
  hsum->SetMarkerSize(.4);
  hsum->SetMarkerColor(kBlue);
  hsum->GetYaxis()->SetTitle(sumTitle); 
  hsum->GetXaxis()->SetTitle(yTitle); 
  hsum->Draw("");
  c2->Print(".pdf");

  fout->Append(hsum);
  if(ca) fout->Append(ca);
  fout->Append(c1);
  fout->Append(c2);
  fout->Append(cq1);

  float timeZero = tvec[0];

  return timeZero;

}
