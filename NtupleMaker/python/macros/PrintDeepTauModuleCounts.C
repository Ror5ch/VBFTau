void PrintDeepTauModuleCounts(char* filename) {

  TFile *_file0 = TFile::Open(filename);


  TTree* tree = (TTree*)_file0->Get("demo/vbf");

  double hltL1Filter = tree->Draw("runNumber", "passhltL1VBFDiJetIsoTau>0", "goff");
  double nnFilter = tree->Draw("runNumber", "passhltL2VBFIsoTauNNFilter>0", "goff");
  double doubleDeep20TausFilter = tree->Draw("runNumber", "passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch>0", "goff");
  double singleDeep45TauL1HLTMatchingFilter = tree->Draw("runNumber", "passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched>0", "goff");
  double twoMatchedJetsFilter = tree->Draw("runNumber", "passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20>0", "goff");

  double hltVBFTwoDeepTauDecision = tree->Draw("runNumber", "passVBFPlusTwoDeepTauHLT>0","goff");
  double hltVBFTwoDeepTauDecisionPure = tree->Draw("runNumber", "passVBFPlusTwoDeepTauHLT>0 && passDeepDiTau35HLT<1 && passInclusiveVBFHLT<1", "goff");
  double hltTwoDeepTauDecision = tree->Draw("runNumber", "passDeepDiTau35HLT>0", "goff");
  double hltInclusiveVBFDecision = tree->Draw("runNumber", "passInclusiveVBFHLT>0", "goff");
  double hltAND = tree->Draw("runNumber", "passInclusiveVBFHLT>0 && passDeepDiTau35HLT>0", "goff");
  double hltVBFTwoTauDecision = tree->Draw("runNumber", "passVBFPlusTwoTauHLT>0", "goff");

  std::cout << hltL1Filter << '\n'
            << nnFilter << '\n'
            << doubleDeep20TausFilter << '\n'
            << singleDeep45TauL1HLTMatchingFilter << '\n'
            << twoMatchedJetsFilter << '\n'
            << '\n'
            << std::endl;

  std::cout << hltVBFTwoDeepTauDecision << '\n'
            << hltVBFTwoDeepTauDecisionPure << '\n'
            << '\n'
            << hltTwoDeepTauDecision << '\n'
            << hltInclusiveVBFDecision << '\n'
            << hltVBFTwoTauDecision << '\n'
            << hltAND << '\n'
            << std::endl;

}
