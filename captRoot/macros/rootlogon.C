{
  TString arch=gSystem->GetBuildArch();
  cout << " arch is " << arch << endl;
  gSystem->Load("$BRIDGE/captRoot/Linux-Scientific-6.7-x86_64/libcaptRoot.so");
  gInterpreter->AddIncludePath("." );
  gInterpreter->AddIncludePath("$BRIDGE/captRoot/src" );
// many are old and no longer work, but i use the simple ones often
  gROOT->LoadMacro("$BRIDGE/captRoot/macros/UseRoot.C");
  cout << " loading: ";
  ("\n this is ROOT \n");
  printf(" type  tv = new TTreeViewer(\"anaTree\") for viewer \n\n");
  printf("\n type helpMe() for my help \n");
}
