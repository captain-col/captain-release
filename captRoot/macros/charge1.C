/*
** vector sort must run compiled laser.C++
*/
#include <fstream>
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
enum {XPL,VPL,UPL,NPLANES};
bool isMC;

void charge1(int iev=13) {
 
  //TString tag("cluster-6389-12");
  //TString tag("cluster-6388-50");
  //TString tag("mc_pg_muon-20-n100");
  TString tag("mc_pg_muon-20-100_reco-short-lifetime");  
  isMC = false;
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

  atree=NULL;
  int aSize = 0;
  atree = (TTree*) infile->Get("anaTree");
  if(atree) aSize=atree->GetEntriesFast();
  printf(" anaTree with %i entries \n",aSize);

  if(aSize==0) return;
  // this access the tree 
  event = new CP::TCapEvent();
  atree->SetBranchAddress("event",&event);

 /*for(int entry=0; entry < atree->GetEntriesFast(); ++entry) {
    atree->GetEntry(entry);
    printf(" .... entry %i eventId %i \n ",entry,event->EventId);
  }*/
 
    if(iev==45) laser1(tag,45,0,80,125,-10,135,5);
    if(iev==47) laser1(tag,47,0,10,40,-500,-300,5);
    if(iev==41) laser1(tag,41,0,0,38,900,1150,5);
    if(iev==23) laser1(tag,23,0,60,100,-110,100,5);
    if(iev==15)  laser1(tag,15,0,240,275,1100,1500,5);
    if(iev==14) laser1(tag,14,0,200,275,100,200,5);
    if(iev==50) laser1(tag,50,0,200,245,-50,100,5);
    if(iev==8) laser1(tag,8,0,30,45,1800,1900,5);
    if(iev==6) laser1(tag,6,0,80,130,-200,300,5);
    if(iev==12) laser1(tag,12,0,0,60,-20,60,5);
    // this was data if(iev ==13) laser1(tag,13,0,320,400,200,500,10);
    if(iev ==13) laser1(tag,13,0,320,400,320,380,5);
    
    if(iev ==1) laser1(tag,1,0,340,350,310,340,1);
 
  fout->ls();
  fout->Write();
}


float laser1(TString atag, int eventId, int thePlane,  int wire_low, int wire_high, float startTime , float stopTime , float delta )
{
  char chtag[120];
  sprintf(chtag,"event-%i-plane%i-wires%i-%i-times-%.0f-%.0f",eventId, thePlane, wire_low, wire_high,startTime,stopTime);
  TString tag(chtag);
  printf(" calling laser1: event %i plane %i  wires (%i,%i) times (%.0f,%.0f) delta %.1f tag=%s\n",
      eventId, thePlane, wire_low, wire_high,startTime,stopTime,delta,tag.Data());

  //return false;


  bool ifound=false;
  for(int entry=0; entry < atree->GetEntriesFast(); ++entry) {
    atree->GetEntry(entry);
    if(event->EventId == eventId ) {
      ifound=true;
      break;
    }
  }
  if(!ifound) {
    printf(" event not found %i \n",eventId);
    return -1.;
  }

   event->print(entry);
   vector<float> tvec(0);
   vector<float> tsort(0);
   vector<float> dtvec(0);
   vector<float> xvec(0);
   vector<float> dxvec(0);
   vector<float> twec(0);
   vector<float> xwec(0);
   vector<float> qvec(0);
   vector<float> dqvec(0);

  std::vector<CP::TCapHit> fhits= event->hits;
  printf(" number of calib hits in %i event is %i \n",eventId,(int) fhits.size());

   
  if(fhits.size()==0) return 0;
 

  // x plane 
   vector<float> tvec0(0);
   vector<float> xvec0(0);
  // u plane 
   vector<float> tvec1(0);
   vector<float> xvec1(0);
  // v plane 
   vector<float> tvec2(0);
   vector<float> xvec2(0);
   


   // Loop over all entries of the TTree or TChain.
   for(int ihit =0 ; ihit<fhits.size() ; ++ihit) {
     CP::TCapHit ahit = fhits[ihit];
     //ahit.print(entry);
     float hitTime =ahit.t*1E-3; // convert to mircroseconds
     //if(ahit.plane!=thePlane) continue; 
     //if(ahit.wire<wire_low||ahit.wire>wire_high) continue;
     //if(hitTime<startTime || hitTime>stopTime ) continue;
      

     if(ahit.plane==0) {
       tvec0.push_back(hitTime);
       xvec0.push_back(ahit.wire);
     }
     if(ahit.plane==1) {
       tvec1.push_back(hitTime);
       xvec1.push_back(ahit.wire);
     }
     if(ahit.plane==2) {
       tvec2.push_back(hitTime);
       xvec2.push_back(ahit.wire);
     }
     
   }
   // Loop over all entries of the TTree or TChain.
   for(int ihit =0 ; ihit<fhits.size() ; ++ihit) {
     CP::TCapHit ahit = fhits[ihit];
     float hitTime =ahit.t*1E-3; // convert to mircroseconds 
     printf(" hit in track  %i q %f dq %f (%f) wire %i time = %f \n",ihit,ahit.q,ahit.dq,ahit.dq/ahit.q,ahit.wire,hitTime);
     if(ahit.plane!=thePlane) continue;
     float hitDt =ahit.dt*1E-3; // convert to mircroseconds 
     twec.push_back(hitTime);
     int wire = ahit.wire;
     if(wire<150&&!isMC) {
       if(wire%2==0) wire = wire-1;
       else wire=wire+1;
     } else if(!isMC){
       if(wire%2==0) wire = wire+1;
       else wire=wire-1;     
     }
     xwec.push_back(wire);
     if(ahit.q<1) continue;
     if(ahit.wire<wire_low||ahit.wire>wire_high) continue;
     if(hitTime<startTime || hitTime>stopTime ) continue;
     tsort.push_back(hitTime);
     tvec.push_back(hitTime);
     dtvec.push_back(hitDt);
     xvec.push_back(wire);
     dxvec.push_back(0);
     qvec.push_back(ahit.q);
     // dq has changed in clusterCalib
     //dqvec.push_back(qrt(ahit.q));
     float wnoise = pow(ahit.noise,2.0)*float(ahit.nsamples);
     float wq = ahit.q;
     float qerr = sqrt(wnoise+wq);
     dqvec.push_back(qerr);
     //ahit.print();
   }


    printf(" \n\n plotting all hits for plane %i \n",thePlane);

    char gatitle[120];
    char catitle[120];
    if(thePlane==0) {
    sprintf(gatitle,"run%i-Event-%i-x-plane-%s",runId,eventId,tag.Data());
    sprintf(catitle,"all-time-wire-run%i-Event-%i-x-plane-%s",runId,eventId,tag.Data());
    TCanvas *ca = new TCanvas(catitle,catitle);
    TGraph *gaxt = new TGraph(tvec0.size(),&(xvec0[0]),&(tvec0[0]));
    gaxt->SetTitle(gatitle);
    gaxt->GetHistogram()->GetXaxis()->SetTitle("wire x plane "); 
    gaxt->GetHistogram()->GetYaxis()->SetTitle("time ({#mu}s)"); 
    gaxt->SetMarkerStyle(21);
    gaxt->SetMarkerSize(.4);
    gaxt->SetMarkerColor(kBlue);
    gaxt->Draw("ap");
    ca->Print(".pdf");
    fout->Append(ca);

    
    } else if(thePlane==2) {

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
    cau->Print(".pdf");
    fout->Append(cau);

    } else if(thePlane==1) {

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
    cav->Print(".pdf");
    fout->Append(cav);
    }



   if(tsort.size()==0) { printf(" !!!!!!!!!!!!!!!!! no hits passed cuts ! \n"); return 0; }
   printf("  hits passed cuts = %i \n", tsort.size() ); 
   if(tsort.size()<3) return;



   sort(tsort.begin(),tsort.end());

   printf("tsort : ");
   for(unsigned iw =0; iw<tsort.size(); ++iw) printf(" %i) %f; ",iw,tsort[iw]);
   printf("\n");
   
  fout->cd();
  // summed charge
  char htitle[120];
  float nbins = (tsort[tsort.size()-1]-tsort[0])/delta;
  sprintf(htitle,"qsumUn-%s",tag.Data());
  TH1F *hsumUn = new TH1F(htitle,htitle,nbins,tsort[0],tsort[tsort.size()-1]+delta);
  hsumUn->Sumw2();
  hsumUn->Print();

  sprintf(htitle,"qsumsq-%s",tag.Data());
  TH1F *hsumsq = new TH1F(htitle,htitle,nbins,tsort[0],tsort[tsort.size()-1]+delta);


  sprintf(htitle,"qerr-%s",tag.Data());
  TH1F *hqerr = new TH1F(htitle,htitle,nbins,tsort[0],tsort[tsort.size()-1]+delta);


  sprintf(htitle,"qnorm-%s",tag.Data());
  // make the sum for each bin, store in histograms
  TH1F *hnorm = new TH1F(htitle,htitle,nbins,tsort[0],tsort[tsort.size()-1]+delta);
  for(unsigned iq=0; iq<qvec.size() ; ++iq) {
    int ibin = hsumUn->FindBin(tvec[iq]);
    hsumUn->SetBinContent(ibin,   hsumUn->GetBinContent(ibin)+qvec[iq]);
    hsumsq->SetBinContent(ibin, hsumsq->GetBinContent(ibin)+pow(qvec[iq],2.));
    hqerr->SetBinContent(ibin,  hqerr->GetBinContent(ibin)+pow((dqvec[iq]/qvec[iq]),2.0));
    hnorm->SetBinContent(ibin,  hnorm->GetBinContent(ibin)+1.0);
  }
  sprintf(htitle,"qsum-%s",tag.Data());
  TH1F *hsum = new TH1F(htitle,htitle,nbins,tsort[0],tsort[tsort.size()-1]+delta);
  hsum->Sumw2();
  hsum->Print();
  
  // calculate qrms for each bin
  //for(int ibin = 1; ibin<=hsum->GetNbinsX(); ++ibin)  hsum->SetBinError(ibin, hsum->GetBinContent(ibin)*qrt(hqerr->GetBinContent(ibin))/hnorm->GetBinContent(ibin));
  for(int ibin = 1; ibin<=hsum->GetNbinsX(); ++ibin)  {
    float qnorm = hnorm->GetBinContent(ibin);
    if(qnorm<1) continue;
    float qsum2 = hsumsq->GetBinContent(ibin)/qnorm;
    float qsum =  hsumUn->GetBinContent(ibin)/qnorm;
    float qerr =  qsum*sqrt(hqerr->GetBinContent(ibin));
    float qrms=0;
    if(qnorm>1) qrms = sqrt(qsum2-qsum*qsum);
    else qrms=qerr;
    float low = hsumUn->GetBinLowEdge(ibin);
    float up = low + hsumUn->GetBinWidth(ibin);
    printf(" %i qnorm %0.f (%0.1f,%0.1f) qsum2 %E qsum2^2 %E qerr %E qrms = %E \n",ibin, qnorm,low,up, qsum2 , qsum*qsum, qerr,qrms );
    hsum->SetBinContent(ibin, qsum);
    hsum->SetBinError(ibin, qrms);
  }

  //hsum->Print("all");

  /*
  printf(" summed plot number of bins %i \n",hsum->GetNbinsX());
  for(int ibin = 1; ibin<=hsum->GetNbinsX(); ++ibin) if(hsum->GetBinContent(ibin)>0) printf(" ... %i %f q = %f +/- %f (%f)  \n",
      ibin,hsum->GetBinCenter(ibin),hsum->GetBinContent(ibin),hsum->GetBinError(ibin),hsum->GetBinError(ibin)/hsum->GetBinContent(ibin));
  */


  gStyle->SetOptFit(1);

  char gtitle[120];
  char ctitle[120];
  TGraphErrors *gxt = new TGraphErrors(xvec.size(),&(xvec[0]),&(tvec[0]),&(dxvec[0]),&(dtvec[0]));
  sprintf(gtitle,"run%i-Event%i-%s-hits-%i",runId,eventId,tag.Data(),gxt->GetN());
  sprintf(ctitle,"time-vs-wire-run%i-Event%i-%s-hits-%i",runId,eventId,tag.Data(),gxt->GetN());
  TCanvas *c1 = new TCanvas(ctitle,ctitle);
  gxt->SetTitle(gtitle);
  gxt->GetHistogram()->GetXaxis()->SetTitle("wire"); 
  gxt->GetHistogram()->GetYaxis()->SetTitle("time (#mu s)");
  gxt->SetMarkerStyle(21);
  gxt->SetMarkerSize(.4);
  gxt->SetMarkerColor(kBlue);
  printf(" >>>>>>>>>>>>>>> fitting %s %i <<<<<<<<<<<<<<<<<<< \n",gtitle,gxt->GetN());
  flin = new TF1("flin","[0]+x*[1]",xvec.front(),xvec.back());
  gxt->Fit("flin");
  flin->Print();
  gxt->Draw("ap");
  c1->Print(".pdf");
  fout->Append(c1);

  // fit function
  TF1* fexp = new TF1("fexp","expo",tvec.front(),tvec.back());
  

  char c2title[120];
  sprintf(c2title,"average-charge-time-run%i-Event%i-%s",runId,eventId,tag.Data());
  TCanvas *c2 = new TCanvas(c2title,c2title);
  //c2->SetLogy();
  //hsum->Fit("fexp");
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
  fout->Append(c1);
  fout->Append(c2);


  char gqtitle[120];
  char cqtitle[120];
  TGraphErrors *gqt = new TGraphErrors(tvec.size(),&(tvec[0]),&(qvec[0]),&(dtvec[0]),&(dqvec[0]));
  sprintf(gqtitle,"charge-vs-time-run%i-Event%i%s-hits-%i",runId,eventId,tag.Data(),gqt->GetN());
  sprintf(cqtitle,"charge-time-run%i-Event%i%s-hits-%i",runId,eventId,tag.Data(),gqt->GetN());
  gqt->SetTitle(gqtitle);
  gqt->SetMarkerStyle(21);
  gqt->SetMarkerSize(.4);
  gqt->SetMarkerColor(kBlue);
  gqt->GetHistogram()->GetYaxis()->SetTitle("charge"); 
  gqt->GetHistogram()->GetXaxis()->SetTitle("time (#mu s)"); 
  /*TCanvas *cq1 = new TCanvas(cqtitle,cqtitle);
  gqt->Draw("ap");
  cq1->Print(".pdf");
  */


  TGraph* grfit=gqt;

  if(grfit->GetN()==0) return -1;
  TF1* ffexp = new TF1("ffexp","expo",tvec.front(),tvec.back());
  
  
  float timeZero = tvec[0];
  char c3title[120];
  sprintf(c3title,"charge-time-fit-run%i-Event%i-%s-hits-%i",runId,eventId,tag.Data(),grfit->GetN());
  TCanvas *c3 = new TCanvas(c3title,c3title);
  //c2->SetLogy();
  printf(" \n\n *******   par 1 %f error %f \n",ffexp->GetParameter(1),ffexp->GetParError(1));
  grfit->Fit("ffexp");
  double tau = -1./ffexp->GetParameter(1);
  double tauError = ffexp->GetParError(1)/ffexp->GetParameter(1)/ffexp->GetParameter(1);
  char sumTitle[80];
  char yTitle[80];
  sprintf(sumTitle,"charge ");
  sprintf(yTitle,"time (#mus) #tau = %0.2f #pm %0.2f",tau,tauError);
  grfit->Print();  
  grfit->SetMarkerStyle(21);
  grfit->SetMarkerSize(.4);
  grfit->SetMarkerColor(kBlue);
  grfit->GetHistogram()->GetYaxis()->SetTitle(sumTitle); 
  grfit->GetHistogram()->GetXaxis()->SetTitle(yTitle); 
  grfit->Draw("ap");
  c2->Print(".pdf");
  fout->Append(c3);

  return timeZero;

}
