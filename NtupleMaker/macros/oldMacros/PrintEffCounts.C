void PrintEffCounts(char* filename) { 

  TFile *_file0 = TFile::Open(filename);
  TTree* tree = (TTree*)_file0->Get("outTree");

  double nEvents = tree->Draw("nEvents", "nEvents>0", "goff");
  std::cout << nEvents << '\t' << "Events Skimmed" << '\n' << std::endl;

  // VBF Paths
  double passInclusiveVBFBoth = tree->Draw("nEvents", "passInclusiveVBFBoth>0", "goff");
  double passVBFPlusTwoTauBoth = tree->Draw("nEvents", "passVBFPlusTwoTauBoth>0", "goff");
  double passVBFPlusTwoDeepTauBoth = tree->Draw("nEvents", "passVBFPlusTwoDeepTauBoth>0", "goff");
  
  // DiTau Paths
  double passDiTau32Both = tree->Draw("nEvents", "passDiTau32Both>0", "goff");
  double passDiTau34Both = tree->Draw("nEvents", "passDiTau34Both>0", "goff");
  double passDiTau35Both = tree->Draw("nEvents", "passDiTau35Both>0", "goff");

  // DeepDiTau Paths
  double passDeepDiTau34Both = tree->Draw("nEvents", "passDeepDiTau34Both", "goff");
  double passDeepDiTau35Both = tree->Draw("nEvents", "passDeepDiTau35Both", "goff");

  // ORs
  double passInclusiveVBFORDiTau34 = tree->Draw("nEvents", "passInclusiveVBFBoth>0 || passDiTau34Both>0", "goff");
  double passInclusiveVBFORDiTau35 = tree->Draw("nEvents", "passInclusiveVBFBoth>0 || passDiTau35Both>0", "goff");

  double passVBFPlusTwoTauORDiTau34 = tree->Draw("nEvents", "passVBFPlusTwoTauBoth>0 || passDiTau34Both>0", "goff");
  double passVBFPlusTwoTauORDiTau35 = tree->Draw("nEvents", "passVBFPlusTwoTauBoth>0 || passDiTau35Both>0", "goff");

  double passVBFPlusTwoDeepTauORDiTau34 = tree->Draw("nEvents", "passVBFPlusTwoDeepTauBoth>0 || passDiTau34Both>0", "goff");
  double passVBFPlusTwoDeepTauORDiTau35 = tree->Draw("nEvents", "passVBFPlusTwoDeepTauBoth>0 || passDiTau35Both>0", "goff");

  double passVBFPlusTwoDeepTauORDeepDiTau34 = tree->Draw("nEvents", "passVBFPlusTwoDeepTauBoth>0 || passDeepDiTau34Both>0", "goff");
  double passVBFPlusTwoDeepTauORDeepDiTau35 = tree->Draw("nEvents", "passVBFPlusTwoDeepTauBoth>0 || passDeepDiTau35Both>0", "goff");

  double passTripleOR34 = tree->Draw("nEvents", "passInclusiveVBFBoth>0 || passVBFPlusTwoTauBoth>0 || passDiTau34Both>0", "goff");
  double passTripleOR34HalfDeep = tree->Draw("nEvents", "passInclusiveVBFBoth>0 || passVBFPlusTwoDeepTauBoth>0 || passDiTau34Both>0", "goff");
  double passTripleORDeep34 = tree->Draw("nEvents", "passInclusiveVBFBoth>0 || passVBFPlusTwoDeepTauBoth>0 || passDeepDiTau34Both>0", "goff");

  double passTripleOR35 = tree->Draw("nEvents", "passInclusiveVBFBoth>0 || passVBFPlusTwoTauBoth>0 || passDiTau35Both>0", "goff");
  double passTripleOR35HalfDeep = tree->Draw("nEvents", "passInclusiveVBFBoth>0 || passVBFPlusTwoDeepTauBoth>0 || passDiTau35Both>0", "goff");
  double passTripleORDeep35 = tree->Draw("nEvents", "passInclusiveVBFBoth>0 || passVBFPlusTwoDeepTauBoth>0 || passDeepDiTau35Both>0", "goff");
  
 
  std::cout << "counts" << '\t' << "label" << '\n'
            << passInclusiveVBFBoth << '\t' << "Inclusive VBF" << '\n'
            << passVBFPlusTwoTauBoth <<  '\t' << "VBF Plus Two Tau" << '\n'
            << passVBFPlusTwoDeepTauBoth <<  '\t' << "VBF Plus Two Deep Tau" << '\n'
            << passDiTau32Both <<  '\t' << "DiTau 32" << '\n'
            << passDiTau34Both <<  '\t' << "DiTau 34" << '\n'
            << passDiTau35Both <<  '\t' << "DiTau 35" << '\n'
            << passDeepDiTau34Both <<  '\t' << "Deep DiTau34" << '\n'
            << passDeepDiTau35Both <<  '\t' << "Deep DiTau35" << '\n'
            << "ORs" << '\n'
            << passInclusiveVBFORDiTau34 <<  '\t' << "Inc. OR DiTau 34" << '\n'
            << passInclusiveVBFORDiTau35 <<  '\t' << "Inc. OR DiTau 35" << '\n'
            << passVBFPlusTwoTauORDiTau34 <<  '\t' << "VBF Plus Two Tau OR DiTau34" << '\n'
            << passVBFPlusTwoTauORDiTau35 <<  '\t' << "VBF Plus Two Tau OR DiTau35" << '\n'
            << passVBFPlusTwoDeepTauORDiTau34 << '\t' << "VBF Plus Two Deep Tau OR DiTau34" << '\n' 
            << passVBFPlusTwoDeepTauORDiTau35 << '\t' << "VBF Plus Two Deep Tau OR DiTau35" << '\n' 
            << passVBFPlusTwoDeepTauORDeepDiTau34 <<  '\t' << "VBF Plus Two Deep Tau OR Deep DiTau34" << '\n'
            << passVBFPlusTwoDeepTauORDeepDiTau35 <<  '\t' << "VBF Plus Two Deep Tau OR Deep DiTau35" << '\n'
            << "Triple OR" << '\n'
            << passTripleOR34 <<  '\t' << "Inc. OR VBF Plus Two Tau OR DiTau 34" << '\n'
            << passTripleOR35 <<  '\t' << "Inc. OR VBF Plus Two Tau OR DiTau 35" << '\n'
            << passTripleOR34HalfDeep << '\t' << "Inc. OR VBF Plus Two Deep Tau OR DiTau34" << '\n' 
            << passTripleOR35HalfDeep << '\t' << "Inc. OR VBF Plus Two Deep Tau OR DiTau35" << '\n' 
            << passTripleORDeep34 <<  '\t' << "Inc. OR VBF Plus Two Deep Tau OR Deep DiTau 34" << '\n'
            << passTripleORDeep35 <<  '\t' << "Inc. OR VBF Plus Two Deep Tau OR Deep DiTau 35" << '\n'
            << std::endl;

}
