void PrintORCounts(char* filename) { 

  TFile *_file0 = TFile::Open(filename);
  TTree* tree = (TTree*)_file0->Get("outTree");

  double nEvents = tree->Draw("nEvents", "nEvents>0", "goff");
  std::cout << nEvents << '\t' << "Events Skimmed" << '\n' << std::endl;

  // Old VBF Couting
  double passOldVBFHLT = tree->Draw("passOldVBFHLT", "passOldVBFHLT>0", "goff");
  double passOldVBFOff = tree->Draw("passOldVBFOff", "passOldVBFOff>0", "goff");
  double passOldVBFBoth = tree->Draw("passOldVBFBoth", "passOldVBFBoth>0", "goff");
  double matchedBothOld = tree->Draw("matchedBothOld", "matchedBothOld>0", "goff");

  std::cout << "Old VBF" << '\n'
            << passOldVBFHLT << '\t' << "Pass HLT" << '\n'
            << passOldVBFOff << '\t' << "Pass Offline" << '\n'
            << passOldVBFBoth << '\t' << "Pass Both" << '\n'
            << matchedBothOld << '\t' << "Matched Both" << '\n'
            << std::endl;

  // New VBF Couting
  double passNewVBFHLT = tree->Draw("passNewVBFHLT", "passNewVBFHLT>0", "goff");
  double passNewVBFOff = tree->Draw("passNewVBFOff", "passNewVBFOff>0", "goff");
  double passNewVBFBoth = tree->Draw("passNewVBFBoth", "passNewVBFBoth>0", "goff");
  double matchedBothNew = tree->Draw("matchedBothNew", "matchedBothNew>0", "goff");

  std::cout << "New VBF" << '\n'
            << passNewVBFHLT << '\t' << "Pass HLT" << '\n'
            << passNewVBFOff << '\t' << "Pass Offline" << '\n'
            << passNewVBFBoth << '\t' << "Pass Both" << '\n'
            << matchedBothNew << '\t' << "Matched Both" << '\n'
            << std::endl;

  // DiTau Counting 
  double passDiTau32HLT = tree->Draw("passDiTau32HLT", "passDiTau32HLT>0", "goff");
  double passDiTau32Off = tree->Draw("passDiTau32Off", "passDiTau32Off>0", "goff");
  double passDiTau32Both = tree->Draw("passDiTau32Both", "passDiTau32Both>0", "goff");

  std::cout << "DiTau32" << '\n' 
            << passDiTau32HLT << '\t' << "Pass HLT" << '\n'
            << passDiTau32Off << '\t' << "Pass Offline" << '\n'
            << passDiTau32Both << '\t' << "Pass Both" << '\n'
            << std::endl;

  double passDiTau35HLT = tree->Draw("passDiTau35HLT", "passDiTau35HLT>0", "goff");
  double passDiTau35Off = tree->Draw("passDiTau35Off", "passDiTau35Off>0", "goff");
  double passDiTau35Both = tree->Draw("passDiTau35Both", "passDiTau35Both>0", "goff");

  std::cout << "DiTau35" << '\n' 
            << passDiTau35HLT << '\t' << "Pass HLT" << '\n'
            << passDiTau35Off << '\t' << "Pass Offline" << '\n'
            << passDiTau35Both << '\t' << "Pass Both" << '\n'
            << std::endl;

  // OR Counting "Both" with matching (not available for DiTau)
  double passOROldDiTau32Matching = tree->Draw("nEvents", "passOldVBFBoth>0 || matchedBothOld>0 || passDiTau32Both>0", "goff");
  double passORNewDiTau32Matching = tree->Draw("nEvents", "passNewVBFBoth>0 || matchedBothNew>0 || passDiTau32Both>0", "goff");
  double passOROldNewDiTau32Matching = tree->Draw("nEvents", "passOldVBFBoth>0 || matchedBothOld>0 || passNewVBFBoth>0 || matchedBothNew>0 || passDiTau32Both>0", "goff");
  double passOROldDiTau35Matching = tree->Draw("nEvents", "passOldVBFBoth>0 || matchedBothOld>0 || passDiTau35Both>0", "goff");
  double passORNewDiTau35Matching = tree->Draw("nEvents", "passNewVBFBoth>0 || matchedBothNew>0 || passDiTau35Both>0", "goff");
  double passOROldNewDiTau35Matching = tree->Draw("nEvents", "passOldVBFBoth>0 || matchedBothOld>0 || passNewVBFBoth>0 || matchedBothNew>0 || passDiTau35Both>0", "goff");
  // OR Counting "Both" no matching (not available for DiTau)
  double passOROldDiTau32 = tree->Draw("nEvents", "passOldVBFBoth>0 || passDiTau32Both>0", "goff");
  double passORNewDiTau32 = tree->Draw("nEvents", "passNewVBFBoth>0 || passDiTau32Both>0", "goff");
  double passOROldNewDiTau32 = tree->Draw("nEvents", "passOldVBFBoth>0 || passNewVBFBoth>0 || passDiTau32Both>0", "goff");
  double passOROldDiTau35 = tree->Draw("nEvents", "passOldVBFBoth>0 || passDiTau35Both>0", "goff");
  double passORNewDiTau35 = tree->Draw("nEvents", "passNewVBFBoth>0 || passDiTau35Both>0", "goff");
  double passOROldNewDiTau35 = tree->Draw("nEvents", "passOldVBFBoth>0 || passNewVBFBoth>0 || passDiTau35Both>0", "goff");
 
  std::cout << "ORs with Matching between HLT and AOD for Old and New (not available for DiTau)" << '\n'
            << passOROldDiTau32Matching << '\t' << "Pass Old OR DiTau32" << '\n'
            << passORNewDiTau32Matching << '\t' << "Pass New OR DiTau32" << '\n'
            << passOROldNewDiTau32Matching << '\t' << "Pass Old OR New OR DiTau32" << '\n'
            << passOROldDiTau35Matching << '\t' << "Pass Old OR DiTau35" << '\n'
            << passORNewDiTau35Matching << '\t' << "Pass New OR DiTau35" << '\n'
            << passOROldNewDiTau35Matching << '\t' << "Pass Old OR New OR DiTau35" << '\n'
            << "ORs with No Matching between HLT and AOD" << '\n'
            << passOROldDiTau32 << '\t' << "Pass Old OR DiTau32" << '\n'
            << passORNewDiTau32 << '\t' << "Pass New OR DiTau32" << '\n'
            << passOROldNewDiTau32 << '\t' << "Pass Old OR New OR DiTau32" << '\n'
            << passOROldDiTau35 << '\t' << "Pass Old OR DiTau35" << '\n'
            << passORNewDiTau35 << '\t' << "Pass New OR DiTau35" << '\n'
            << passOROldNewDiTau35 << '\t' << "Pass Old OR New OR DiTau35" << '\n'
            << std::endl;

}
