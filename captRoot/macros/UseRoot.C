/*************************************************

This file contains various generic root macros.

M. Gold, June 7, 200
  gROOT->LoadMacro("UseRoot.C");
*************************************************/

/*****************************************
 Define some aliases so I don't have to 
 remember/type  long commands
******************************************/

void helpMe()
{
  cout << " *************************************************************" << endl;
  cout << " *             My root hints and commands                    *" << endl;
  cout << " *************************************************************" << endl;
  cout << endl;
  cout << " To make a selector for a tree," << endl;
  cout << "     treePointer->MakeSelector(\"name\"); " << endl;
  cout << endl;
  cout << " functions(); list global function" << endl;
  cout << endl;
  cout << " loadM();     load a macro" << endl;
  cout << endl;
  cout << " browse();    launch browser" << endl;
  cout << endl;
  cout << " pwd();       print working directory" << endl;
  cout << endl;
  cout << " dir();       list histograms in current directory" << endl;
  cout << endl;
  cout << " save(\"filename\"); " << endl;
  cout << "              save hists to file" << endl;
  cout << endl;
  cout << " print();     print all canvases" << endl;
  cout << endl;
  cout << " dump(\"filename\",int x,int y);  " << endl; 
  cout << "              print all histograms to file, x by y on a page" << endl;
  cout << endl;
  cout << " readHist(Option_t* fileName)     read hists from fileName " << endl;
  cout << endl;
  cout << " TH1F* getHist(Option_t* fileName, Option_t* subDir=NULL) " << endl;
  cout << "              get hist pointer from fileName/subDir " << endl;
  cout << endl;
  cout << endl;
  cout << " void gFit(Option_t* HistName, float low = -1.0, float high = 1.0)  " << endl;
  cout << "              fit histogram to gaussian                             " << endl;
  cout << endl;
  cout << endl;
  cout << " void reading(TDirectory *inDir,TDirectory *outDir)  " << endl;
  cout << "              read all histograms including subdirs                 " << endl;
  cout << endl;
  cout << endl;



  cout << " *************************************************************" << endl;
  cout << " more to come soon...." << endl;
  cout << " *************************************************************" << endl;
}
void loadM(char* theMacro) 
{
 gROOT->LoadMacro(theMacro);
}

void browse() 
{
 browser = new TBrowser();
 gSystem->Load("libTreeViewer");
 printf(" type  tv = new TTreeViewer() for viewer \n\n");
}

void dir() 
{
  gDirectory->ls("-m");
}

void pwd()
{
  gDirectory->pwd();
}

void functions()
{
  gROOT->GetListOfGlobalFunctions()->ls();
}

/****************************************
A routine to save histograms to a file
  as given by Rene Brun via roottalk
*****************************************/
void save(char* fileName )   
{
  TDirectory *dir = gDirectory; //save pointer to current dir
  gROOT->cd();                 // move to top directory 
  TFile *f = new TFile(fileName,"recreate"); // overwrite file
  //  dir->GetList()->ls(); // write to file
  writing(f,dir);
  //  dir->GetList()->Write(); // write to file
  //f->ls();
  delete f;
  dir->cd();
}

void writing(TFile *f, TDirectory *theDir)   
{
  // save pointer to current directory
  TDirectory *cDir = gDirectory;

  cout << " writing " << theDir->GetName() << endl;
  if(theDir->GetName()!=gROOT->GetName() ) {
    f->mkdir(theDir->GetName());
    f->cd(theDir->GetName());    
    //    cout << " making " << theDir->GetName() << endl; 
  } else f->cd();

  TList *list = theDir->GetList();
  list->Write();
  // look for subdirectories
  TObject *obj=NULL;
  TIter next(list);
  while (obj = next() ) {
    if(obj->IsA()->InheritsFrom("TDirectory")) {
      TDirectory *subDir = (TDirectory*)obj; 
      writing(f,subDir);
    }
  }

  cDir->cd();
}

TFile *openFile(char* fileName="test.root")
{
  gDirectory->cd("Rint:/"); // make sure we are in default directory
  TDirectory *dir = gDirectory; //save pointer to Rint dir
  TFile *f = new TFile(fileName,"recreate"); // overwrite file
  dir->cd();
  return f; 
}



/****************************************
A routine to save tree to a file
*****************************************/
void saveTree(char* fileName="myTree.root")   
{
  gROOT->cd("Rint:");
  TDirectory *rdir = gDirectory; //save pointer to Rint dir

  tv__tree = (TTree *) gROOT->FindObject("stn");
  TTree *tnew = tv__tree->CloneTree();


  if(tnew) {
    TFile *f = new TFile(fileName,"recreate"); // overwrite file
    cout << "appending " << t->GetName() << endl;
    f->Append(t);
    f->ls();
    delete f;   // automatic upon deletion  f->Close();
  }
 

}



/***********************************
 a method to print all the canvases
************************************/
void print(char* exten="gif", char * tag="") // exten is file extention 
{
	TIter next(gROOT->GetListOfCanvases());
  char fname[200];
  TCanvas *c;
  int iprint=0;
  while(c = (TCanvas*) next() ) {
    sprintf(fname,"%s%s%s%s",c->GetName(),tag,".",exten);  
    cout << fname << endl;
    c->Print(fname);
    ++iprint;
  }
  cout << " printed " << iprint << " canvases " << endl;
}


void readHist(TFile *f, bool recursive=true, TDirectory *toDir=NULL) 
{
  //gDirectory->cd("Rint:/"); // make sure we are in default directory
	gROOT->cd();
  TDirectory *topDir = gDirectory; //save pointer to Rint dir
  if(f->IsZombie()) { // check that file is opened
    cout <<" Sorry, file " << fileName << " not opened !! " << endl;
    return;
  }
  f->cd();
  reading(gDirectory,topDir,recursive);
  topDir->cd();
  delete f;
}


void readHist(char* fileName, bool recursive=true, TDirectory *toDir=NULL) 
{
  if(!toDir) toDir = gDirectory;
  else toDir->cd();
  //gDirectory->cd("Rint:/"); // make sure we are in default directory
  TDirectory *topDir = gDirectory; //save pointer to Rint dir
  TFile *f = new TFile(fileName); // open in read mode
  if(f->IsZombie()) { // check that file is opened
    cout <<" Sorry, file " << fileName << " not opened !! " << endl;
    return;
  }
  f->cd();
  reading(gDirectory,topDir,recursive);
  topDir->cd();
  delete f;
}



/****************************************
A routine to get histograms from a file 
as given by Rene Brun.

  Apparently, it's not just enough to read the histograms,
  but you have to put them in the directory via,

void SetDirectory(TDirectory *dir) 

 By default when an histogram is created, it is added to the list
 of histogram objects in the current directory in memory.
 Remove reference to this histogram from current directory and add
 reference to new directory dir. dir can be 0 in which case the
 histogram does not belong to any directory.
****************************************************************************/

void readHistDir(char* fileName, char* saveToSubDir=NULL, char* subDir=NULL) 
{
  gDirectory->cd("Rint:/"); // make sure we are in default directory
  TDirectory *topDir = gDirectory; //save pointer to Rint dir
  TFile *f = new TFile(fileName); // open in read mode
  if(f->IsZombie()) { // check that file is opened
    cout <<" Sorry, file " << fileName << " not opened !! " << endl;
    return;
  }

  // check save to subdir option
  if( saveToSubDir != NULL ) {
    topDir->cd(saveToSubDir);  
    TDirectory *saveDir = gDirectory;
  } else {
    TDirectory *saveDir = topDir;
  }
  saveDir->cd(); 
  cout << " saving to    " << gDirectory->pwd() << endl;

  // check read from subdir option
  if( subDir!=NULL )  { 
    f->cd(subDir);
  } else {
    f->cd();
  }
  cout << " reading from " << gDirectory->pwd() << endl;
  
  //read all objects in current directory in memory
  gDirectory->ReadAll(); 
  TIter next(gDirectory->GetList());
  TObject *obj;
  TH1 *h;
  int i1=0;  int i2=0; int i3=0;
  while (( obj = next())) {
    // remember that TH2 also inherits from TH1
    if (obj->InheritsFrom("TH2")) {
      TH2 *h2 = (TH2*)obj;
      h2->SetDirectory(saveDir);
      ++i2;
    } else if (obj->InheritsFrom("TH1")) {
      TH1 *h1 = (TH1*)obj;
      h1->SetDirectory(saveDir);
      ++i1;
    } else if (obj->InheritsFrom("TGraphErrors")) {
      TGraphErrors *h1 = (TGraphErrors*)obj;
      h1->SetDirectory(saveDir);
      ++i3;
    }
  }
  delete f;
  cout << " have read " << i1 << " 1D and " << i2 << " 2D histograms  and " << i3 << " TGraphErrors " << endl;
  //saveDir->ls();
}  


/*******************************************
 get pointer to histogram from directory
********************************************/
TH1F* getHist(char* DirName, char* HistName) 
{
  TDirectory *topDir = gDirectory;
  topDir->cd(DirName);
  TH1F *h = (TH1F*) gDirectory->FindObject(HistName);
  topDir->cd();
  return h;
}


/*******************************************
 get pointer to histogram from directory
********************************************/
TH1F* getHist(TDirectory *dir, char* HistName) 
{
  return = (TH1F*) dir->FindObject(HistName);
}


/*******************************************
 get pointer to histogram from directory
********************************************/
TH2F* getHist2F(char* DirName, char* HistName ) 
{
  gDirectory->cd("Rint:/");
  TDirectory *topDir = gDirectory;
  topDir->cd(DirName);
  return (TH2F*) gDirectory->FindObject(HistName);
}

TH1F* get1F(char *name)
{
  return (TH1F*) gDirectory->FindObject(name);
}


TH1F* fetchTH1F(TDirectory *fdir, char* name)
{
  TH1F *h=NULL;
  TIter nextkey(fdir->GetListOfKeys());
  while (key = (TKey*)nextkey()) {
    fdir->cd();
    obj = key->ReadObj();
    if (obj->IsA()->InheritsFrom("TDirectory")) continue; 
    if (obj->IsA()->InheritsFrom("TH1F") && 
	TString(obj->GetName())==TString(name)) h = (TH1F*) obj;
  }
  if(!h) cout << " fetch failed to find " << name << endl;
  return h;
}


TH1F* get1Fi(char *tag, int i)
{
  char name[10];
  sprintf(name,"%s%d",tag,i);
  return (TH1F*) gDirectory->FindObject(name);
}

/****************************************
A routine to plot all histograms in file
named fname.root and printed to fname.ps
*****************************************/
void dump(char *fname, int x=3, int y=3, int page=10)
{ 
  int page_cnt, hist_per_page, i;  
  // construct in/out names
  char fileName[30]; char psName[30];
  sprintf(fileName,"%s%s",fname,".root");
  sprintf(psName,"%s%s",fname,".ps");
  
  //open input file
  TFile *f1 = new TFile(fileName);
  if(f1->IsZombie()) {
    cout <<" Sorry, file " << fileName << " not opened !! " << endl;
    return;
  }
  cout << " output file is " << psName << endl;
  
  TCanvas *c1 = new TCanvas("c1");
  TPostScript *ps = new TPostScript(psName,112);
  c1->Divide(x,y);
  hist_per_page = x*y; 
  TIter next(f1->GetListOfKeys());       //make an iterator on list of keys
  TKey *key;
  while (page_cnt < page) {
    ps->NewPage();
    i=1;
    while (hist_per_page >= i) {
      c1->cd(i);
      key = (TKey*)next();             //get next key on the file
      if (!key) break;                 //if no more keys, key=0
      TObject *obj = key->ReadObj();   //read object associated to key
      if (obj->InheritsFrom("TH1")) {  //interested by histograms only
	obj->Draw();                  //draw histogram with default option
	i++;
      } else if (obj->InheritsFrom("TH2")) {
	obj->Draw();                  //draw histogram with default option
	i++;
      }
    }
    c1->Update();
    if (!key) break;
    page_cnt++;     
  }
}
/*******************************************
 fit histogram to gaussian
********************************************/
void gFit(char* HistName, float low = -1.0, float high = 1.0)
{
  TH1F* hi = (TH1F*)  gDirectory->FindObject(HistName);
  TF1* gfit = new TF1("gfit","gaus",-1.,1.);
  gfit->SetRange(low,high);
  hi->Fit("gfit","r");   
  hi->Draw();
  delete gfit;
}

/*****************************************************
   recursively read all histograms from fdir to rdir
*******************************************************/

void reading(TDirectory *fdir,TDirectory *rdir, bool recursive=true) 
{
  TObject *obj=NULL;
  TIter nextkey(fdir->GetListOfKeys());
  while (key = (TKey*)nextkey()) {
    fdir->cd();
    obj = key->ReadObj();
    if (obj->IsA()->InheritsFrom("TTree")) { //case of a TTree or TNtuple
      t1 = (TTree*)obj;
      t1->SetDirectory(rdir);
    } elseif(obj->IsA()->InheritsFrom("TH1")) { //case of TH1 or TProfile
      h1 = (TH1*)obj;
      h1->SetDirectory(rdir);
    } elseif(obj->IsA()->InheritsFrom("TH2")) { //case of TH2
      h2 = (TH2*)obj;
      h2->SetDirectory(rdir);
    } elseif(obj->IsA()->InheritsFrom("TDirectory")&&recursive) { 
      //case of TDirectory... recursion
      cout << " found TDirectory " << obj->GetName() << endl;
      TDirectory *subDir = (TDirectory*)obj;
      subDir->cd();
      gDirectory->pwd();      
      reading(subDir,rdir->mkdir(subDir->GetName()));
    }
  }
}
void drawColor( TH1 *h, UShort_t c=kBlack, char *opt="")
{
  if(!h) return;
  //  cout << h->GetName() << endl;
  h->SetMarkerColor(c);  
  h->SetLineColor(c);  
  h->SetLineWidth(2);
  h->Draw(opt);
}

void drawColor(char *HistName, UShort_t c=kBlack, char *opt="")
{
  TH1* h = (TH1*)  gDirectory->FindObject(HistName);
  if(!h) return;
  //  cout << h->GetName() << endl;
  h->SetMarkerColor(c);  
  h->SetLineColor(c);
  h->SetLineWidth(2);  
  h->Draw(opt);
}



void drawFill(char *HistName, UShort_t c=kBlack, char *opt="h")
{
  TH1* h = (TH1*)  gDirectory->FindObject(HistName);
  if(!h) return;
  //  cout << h->GetName() << endl;
  h->SetMarkerColor(c);  
  h->SetLineColor(c);  
  h->SetFillColor(c);
  h->Draw(opt);
  //  h->SetFillColor(0);
}


void htit(TH1 *h, char *xtit, char *ytit="")
{
  if(!h) return;
  h->GetYaxis()->SetTitle(ytit);
  h->GetXaxis()->SetTitle(xtit);
}

void htit(char *HistName, char *xtit, char *ytit="")
{
  TH1* h = (TH1*)  gDirectory->FindObject(HistName);
  if(!h) return;
  h->GetYaxis()->SetTitle(ytit);
  h->GetXaxis()->SetTitle(xtit);
}
// turn on errors
void setErrors()
{
  TIter next(gDirectory->GetList());
  TObject *0bj;  TH1 *h;
  while (( obj = next())) {
    if (obj->InheritsFrom("TH1")) {
      TH1 *h1 = (TH1*) obj;
      h1->Sumw2(); //h1->SetStats(false);
    }
  }
}
// turn on errors
void setTitles()
{
  TIter next(gDirectory->GetList());
  TObject *0bj;  TH1 *h;
  while (( obj = next())) {
    if (obj->InheritsFrom("TH1")) {
      TH1 *h1 = (TH1*) obj;
      h1->SetXTitle(h1->GetTitle());
    }
  }
}


void setHistStyles(int color=kBlack, bool stat=true)
{
  TIter next(gDirectory->GetList());
  TObject *0bj;  TH1 *h;
  while (( obj = next())) {
    if (obj->InheritsFrom("TH1")) {
      TH1 *h1 = (TH1*) obj;
      h1->SetLineWidth(2);
      h1->SetLineColor(color);
      //h->SetXTitle(h->GetTitle());
      h1->SetStats(stat);
    }
  }
}





TH1F *makeInt(TH1F *h1)
{
  //create hint1 filled with the bins integral of h1
  if(!h1) return NULL;

  TString name = TString(h1->GetName()) + TString("_int");
  TString title = TString(h1->GetTitle()) + TString(" integral");
  TH1F *hint1 = h1->Clone(name.Data());
  hint1->Reset();
  hint1->SetTitle(title.Data());
  Float_t sum = 0;
  float tot = h1->Integral();
  for (int i=1 ; i< h1->GetNbinsX() ; ++i) {
    sum += h1->GetBinContent(i)/tot;
    hint1->SetBinContent(i,sum);
  }
  return hint1;
}



TH1F *makeNorm(TH1F *h1, float norm=1)
{
  //create hint1 filled with the bins integral of h1
  if(!h1) return NULL;

  TString name = TString(h1->GetName()) + TString("_norm");
  TString title = TString(h1->GetTitle()) + TString(" norm ");
  TH1F *hint1 = h1->Clone(name.Data());
  hint1->Reset();
  hint1->SetTitle(title.Data());
  float tot = h1->Integral();
  if(tot==0) return;
  for (int i=1 ; i<= h1->GetNbinsX() ; ++i) {
    float sum = h1->GetBinContent(i)/tot*norm;
    float err = h1->GetBinError(i)/tot*norm;
    hint1->SetBinContent(i,sum);
    hint1->SetBinError(i,err);
  }
  return hint1;
}



void wAve(TH1F *h1, float &w, float &e, int ilow=1, int ihigh=0)  // waited average
{
  //create hint1 filled with the bins integral of h1
  if(!h1) return NULL;
  if(ihigh<ilow||ihigh>h1->GetNbinsX()) ihigh = h1->GetNbinsX();
  w=0;
  e=0;
  float sum; 
  float err;
  if(h1->Integral()==0) return;
  float nbins=0;
  for(int i=ilow ; i<= ihigh; ++i)  if(h1->GetBinContent(i)>0) ++nbins;
  //  cout << " weighted average of points " << h1->GetTitle() << endl;
  for(int i=ilow ; i<= ihigh ; ++i) {
    sum = h1->GetBinContent(i);
    err = h1->GetBinError(i);
    // cout << "    " << i << " "<< sum << "  "<< err << endl;
    if(sum==0) continue;
    if(err>0) {
      w += sum/err/err;
      e += 1/err/err;
    } else {
      w += 1/nbins;
    }
  }
  if(e==0) return;
  w = w/e;
  e = sqrt(1/e);
  //  cout << "  result   "<< w << "  "<< e << endl;
}



TH1F *hScaled(TH1F *h1, float scale=1)
{
  //create hint1 filled with the bins integral of h1
  if(!h1) return NULL;

  TString name = TString(h1->GetName()) + TString("_scale");
  TString title = TString(h1->GetTitle()) + TString(" scale ");
  TH1F *hint1 = h1->Clone(name.Data());
  hint1->Reset();
  hint1->SetTitle(title.Data());
  float tot = h1->Integral();
  for (int i=1 ; i<= h1->GetNbinsX() ; ++i) {
    float sum = h1->GetBinContent(i)*scale;
    float err = h1->GetBinError(i)*scale;
    hint1->SetBinContent(i,sum);
    hint1->SetBinError(i,err);
  }
  return hint1;
}


void setStyle(TStyle *sty)
{
  sty->SetOptTitle(0);
  // Get rid of all the nasty color 19 everywhere:
  sty->SetTitleFillColor(kWhite) ;
  sty->SetFrameFillColor(kWhite) ;
  sty->SetFillColor(kWhite) ;
  sty->SetCanvasColor(kWhite) ;
  sty->SetPadColor(kWhite) ;
  sty->SetStatColor(kWhite) ;
}


double arcTan(double pt, double pz)
{
  double a = TMath::ATan2(pt,pz);
  if(a<0) a += TMath::Pi();
  return a*180/TMath::Pi();  
}


void frac(int p , int n)
{
  float r = 0;
  float e = 0;
  if(n>0) {
    r = float(p)/float(n);
    e = sqrt(float(p)*float(n-p)/pow(float(n),3));
  }
  cout.precision(4) ;
  cout << p << " / " << n << " = " << r << "+/-" << e << endl;
}
