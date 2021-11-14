void PrintMatchingCounts(char* filename) { 

  TFile *_file0 = TFile::Open(filename);
  TTree* tree = (TTree*)_file0->Get("outTree");

  double nEvents = tree->Draw("nEvents", "nEvents>0", "goff");
  std::cout << nEvents << '\t' << "Events Skimmed" << '\n' << std::endl;

  // Old VBF Couting
  double passOldVBFHLT = tree->Draw("passOldVBFHLT", "passOldVBFHLT>0", "goff");
  double passOldVBFOff = tree->Draw("passOldVBFOff", "passOldVBFOff>0", "goff");
  double passOldVBFBoth = tree->Draw("passOldVBFBoth", "passOldVBFBoth>0", "goff");
  double matchedJetsOld = tree->Draw("matchedJetsOld", "matchedJetsOld>0", "goff");
  double matchedTausOld = tree->Draw("matchedTausOld", "matchedTausOld>0", "goff");
  double matchedBothOld = tree->Draw("matchedBothOld", "matchedBothOld>0", "goff");

  std::cout << "Old VBF" << '\n'
            << passOldVBFHLT << '\t' << "Pass HLT" << '\n'
            << passOldVBFOff << '\t' << "Pass Offline" << '\n'
            << passOldVBFBoth << '\t' << "Pass Both" << '\n'
            << matchedJetsOld << '\t' << "Matched Jets" << '\n'
            << matchedTausOld << '\t' << "Matched Taus" << '\n'
            << matchedBothOld << '\t' << "Matched Both" << '\n'
            << std::endl;

  // New VBF Couting
  double passNewVBFHLT = tree->Draw("passNewVBFHLT", "passNewVBFHLT>0", "goff");
  double passNewVBFOff = tree->Draw("passNewVBFOff", "passNewVBFOff>0", "goff");
  double passNewVBFBoth = tree->Draw("passNewVBFBoth", "passNewVBFBoth>0", "goff");
  double matchedJetsNew = tree->Draw("matchedJetsNew", "matchedJetsNew>0", "goff");
  double matchedTausNew = tree->Draw("matchedTausNew", "matchedTausNew>0", "goff");
  double matchedBothNew = tree->Draw("matchedBothNew", "matchedBothNew>0", "goff");

  std::cout << "New VBF" << '\n'
            << passNewVBFHLT << '\t' << "Pass HLT" << '\n'
            << passNewVBFOff << '\t' << "Pass Offline" << '\n'
            << passNewVBFBoth << '\t' << "Pass Both" << '\n'
            << matchedJetsNew << '\t' << "Matched Jets" << '\n'
            << matchedTausNew << '\t' << "Matched Taus" << '\n'
            << matchedBothNew << '\t' << "Matched Both" << '\n'
            << std::endl;

}
