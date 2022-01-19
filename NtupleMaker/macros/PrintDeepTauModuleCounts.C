void PrintDeepTauModuleCounts(char* filename) {

  TFile *_file0 = TFile::Open(filename);

  TTree* tree = (TTree*)_file0->Get("outTree");

  double hltL1Filter = tree->Draw("nEvents", "passhltL1VBFDiJetIsoTau>0 && passVBFPlusTwoTauOff>0", "goff");
  double nnFilter = tree->Draw("nEvents", "passhltL2VBFIsoTauNNFilter>0 && passVBFPlusTwoTauOff>0", "goff");
  double doubleDeep20TausFilter = tree->Draw("nEvents", "passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch>0 && passVBFPlusTwoTauOff>0", "goff");
  double singleDeep45TauL1HLTMatchingFilter = tree->Draw("nEvents", "passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched>0 && passVBFPlusTwoTauOff>0", "goff");
  double twoMatchedJetsFilter = tree->Draw("nEvents", "passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20>0 && passVBFPlusTwoTauOff>0", "goff");

  double hltVBFTwoDeepTauDecision = tree->Draw("nEvents", "passVBFPlusTwoDeepTauHLT>0 && passVBFPlusTwoTauOff>0","goff");
  double passSelectionOnly = tree->Draw("nEvents", "passVBFPlusTwoTauOff>0", "goff");
  double passSelectionToo = tree->Draw("nEvents", "passVBFPlusTwoDeepTauBoth>0", "goff");

  std::cout << hltL1Filter << '\n'
            << nnFilter << '\n'
            << doubleDeep20TausFilter << '\n'
            << singleDeep45TauL1HLTMatchingFilter << '\n'
            << twoMatchedJetsFilter << '\n'
            << hltVBFTwoDeepTauDecision << '\n'
            << passSelectionToo << '\n'
            << '\n'
            << std::endl;

  double variableHolder[] = {hltL1Filter, nnFilter, doubleDeep20TausFilter, singleDeep45TauL1HLTMatchingFilter, twoMatchedJetsFilter, hltVBFTwoDeepTauDecision, passSelectionToo}; //i've gotta learn pyRoot

  const char *names[7] = {"L1", "L2NN", "2Deep20Taus", "1Deep45Tau", "2Jets35", "passHLT", "passMatching"};

  TH1F* cutflowDeepTau = new TH1F("cutflowDeepTau", "", 7, 0.0, 7.0);

  std::cout << passSelectionOnly << '\t' << "pass selection only" << std::endl;
  double fraction[7];
  size_t n = sizeof(fraction) / sizeof(double);
  for (int i = 0; i < n; ++i) {
    fraction[i] = variableHolder[i]/passSelectionOnly;
    std::cout << fraction[i] << '\t' << "fraction passing filter " << names[i] << std::endl;
    cutflowDeepTau->Fill(names[i], variableHolder[i]/passSelectionOnly);
  }

  TCanvas *c1 = new TCanvas("c1", "", 600, 400);

  gStyle->SetOptStat(kFALSE);

  cutflowDeepTau->SetTitle("HLT PassOffline Filter Absolute Efficiency Cutflow;; Efficiency");
  cutflowDeepTau->GetXaxis()->SetLabelSize(0.039);
  cutflowDeepTau->GetYaxis()->SetRangeUser(0.6,1.1);

  cutflowDeepTau->Draw("hist");
  cutflowDeepTau->SetLineColor(1);

  auto legendAbsEff = new TLegend(0.48, 0.7, 0.9, 0.9);
  legendAbsEff->SetHeader("Key", "C");
  legendAbsEff->AddEntry(cutflowDeepTau, "Deep Tau HLT Path");
  legendAbsEff->Draw();

  c1->Print("cutflowDeepTauAbsEff.png", "png");
}
