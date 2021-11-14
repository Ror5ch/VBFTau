// Use this macro to make a cutflow after running an analyzer on your data.
// It's necessary that the analyzer is run on the data because it implments a
// correction to the NtupleMaker HLT decisions.
//
// to run this macro, open root
// root -l
// load the macro
// .L macros/MakeCutflowFromOuttree()
// and then execute it on the file you made with the analyzer
// .x MakeCutflowFromOuttree("filename.root")
//

void MakeCutflowFromOuttree(char* filename, int plotting) {

    TFile *_file0 = TFile::Open(filename);

    TTree* tree = (TTree*)_file0->Get("outTree");

    double nEvents = tree->Draw("nEvents", "nEvents>0", "goff");

    std::cout << nEvents << '\t' << "nEvents" << '\n' << std::endl;

    // Old VBF path and variables for cutflow
    double passhltL1VBFDiJetOR = tree->Draw("passhltL1VBFDiJetOR", "passhltL1VBFDiJetOR>0", "goff");
    double passhltHpsDoublePFTau20Old = tree->Draw("passhltHpsDoublePFTau20Old", "passhltHpsDoublePFTau20Old>0", "goff");
    double passhltHpsDoublePFTauTightOld = tree->Draw("passhltHpsDoublePFTauTightOld", "passhltHpsDoublePFTauTightOld>0", "goff");
    double passhltHpsDoublePFTauAgainstMuonTightOld = tree->Draw("passhltHpsDoublePFTauAgainstMuonTightOld", "passhltHpsDoublePFTauAgainstMuonTightOld>0", "goff");
    double passhltMatchedVBFTwoTight = tree->Draw("passhltMatchedVBFTwoTight", "passhltMatchedVBFTwoTight>0", "goff");
    double passhltMatchedVBFOneTight = tree->Draw("passhltMatchedVBFOneTight", "passhltMatchedVBFOneTight>0", "goff");
    double passOldVBFHLT = tree->Draw("passOldVBFHLT", "passOldVBFHLT>0", "goff");

    // vertical lists are easier to copy and paste
    std::cout << "Old VBF HLT Filter Counts" << std::endl;
    std::cout << passhltL1VBFDiJetOR << '\t' << "passhltL1VBFDiJetOR" << '\n'
              << passhltHpsDoublePFTau20Old << '\t' << "passhltHpsDoublePFTau20Old" << '\n' 
              << passhltHpsDoublePFTauTightOld << '\t' << "passhltHpsDoublePFTauTightOld" << '\n'
              << passhltHpsDoublePFTauAgainstMuonTightOld << '\t' << "passhltHpsDoublePFTauAgainstMuonTightOld" << '\n'
              << passhltMatchedVBFTwoTight << '\t' << "passhltMatchedVBFTwoTight" << '\n'
              << passhltMatchedVBFOneTight << '\t' << "passhltMatchedVBFOneTight" << '\n'
              << passOldVBFHLT << '\t' << "passOldVBFHLT" << '\n'
              << std::endl;

    // New VBF path and variables for cutflow
    double passhltL1VBFDiJetIsoTau = tree->Draw("passhltL1VBFDiJetIsoTau", "passhltL1VBFDiJetIsoTau>0", "goff");
    double passhltHpsDoublePFTau20New = tree->Draw("passhltHpsDoublePFTau20New", "passhltHpsDoublePFTau20New>0", "goff");
    double passhltHpsDoublePFTauTightNew = tree->Draw("passhltHpsDoublePFTauTightNew", "passhltHpsDoublePFTauTightNew>0", "goff");
    double passhltHpsDoublePFTauAgainstMuonTightNew = tree->Draw("passhltHpsDoublePFTauAgainstMuonTightNew", "passhltHpsDoublePFTauAgainstMuonTightNew>0", "goff");
    double passhltHpsPFTau50Tight = tree->Draw("passhltHpsPFTau50Tight", "passhltHpsPFTau50Tight>0", "goff");
    double passhltMatchedVBFIsoTauTwoTight = tree->Draw("passhltMatchedVBFIsoTauTwoTight", "passhltMatchedVBFIsoTauTwoTight>0", "goff");
    double passNewVBFHLT = tree->Draw("passNewVBFHLT", "passNewVBFHLT>0", "goff");

    // vertical lists are easier to copy and paste
    std::cout << "New VBF HLT Filter Counts" << std::endl;
    std::cout << passhltL1VBFDiJetIsoTau << '\t' << "passhltL1VBFDiJetIsoTau" << '\n'
              << passhltHpsDoublePFTau20New << '\t' << "passhltHpsDoublePFTau20New" << '\n'
              << passhltHpsDoublePFTauTightNew << '\t' << "passhltHpsDoublePFTauTightNew" << '\n'
              << passhltHpsDoublePFTauAgainstMuonTightNew << '\t' << "passhltHpsDoublePFTauAgainstMuonTightNew" << '\n'
              << passhltHpsPFTau50Tight << '\t' << "passhltHpsPFTau50Tight" << '\n'
              << passhltMatchedVBFIsoTauTwoTight << '\t' << "passhltMatchedVBFIsoTauTwoTight" << '\n'
              << passNewVBFHLT << '\t' << "passNewVBFHLT" << '\n'
              << std::endl;

    if (plotting) {

    // arrays holding above values
    // repeated where filters don't match / no counterpart exists

    double rawOld[] = {passhltL1VBFDiJetOR, passhltHpsDoublePFTau20Old, \
		passhltHpsDoublePFTauTightOld, passhltHpsDoublePFTauAgainstMuonTightOld, \
		passhltHpsDoublePFTauAgainstMuonTightOld, passhltMatchedVBFTwoTight, \
		passhltMatchedVBFOneTight, passOldVBFHLT};
    double rawNew[] = {passhltL1VBFDiJetIsoTau, passhltHpsDoublePFTau20New, \
		passhltHpsDoublePFTauTightNew, passhltHpsDoublePFTauAgainstMuonTightNew, \
		passhltHpsPFTau50Tight, passhltMatchedVBFIsoTauTwoTight, \
		passhltMatchedVBFIsoTauTwoTight, passNewVBFHLT};

    const char *names[8] = {"L1", "Req. 1 Tau", "Req. 2nd Tau", \
			"TauID vs Muon", "45 GeV Tau (New)", "Req. 2 Jets", \
			"115 GeV Jet (Old)", "Passed All Filters"};

    TH1F* oldHLTAbsEff = new TH1F("oldHLTAbsEff","", 8, 0.0, 8.0);
    TH1F* newHLTAbsEff = new TH1F("newHLTAbsEff","", 8, 0.0, 8.0);

    double oldFrac[8];
    double newFrac[8];
    size_t n = sizeof(rawOld) / sizeof(double);
    for (int i = 0; i < n; ++i) {
      oldFrac[i] = rawOld[i]/rawOld[0];
      oldHLTAbsEff->Fill(names[i], oldFrac[i]);

      newFrac[i] = rawNew[i]/rawNew[0];
      newHLTAbsEff->Fill(names[i], newFrac[i]);
    }

    TCanvas *c1 = new TCanvas("c1", "", 600, 400);
    //c1->SetLogy();
    gStyle->SetOptStat(kFALSE);

    oldHLTAbsEff->SetTitle("HLT Filter Absolute Efficiency Cutflow;; Efficiency");
    oldHLTAbsEff->GetXaxis()->SetLabelSize(0.039);

    oldHLTAbsEff->Draw("hist");
    oldHLTAbsEff->SetLineColor(1);
    newHLTAbsEff->SetLineStyle(7);
    newHLTAbsEff->SetLineColor(9);
    newHLTAbsEff->Draw("hist SAME");

    auto legendAbsEff = new TLegend(0.48, 0.7, 0.9, 0.9);
    legendAbsEff->SetHeader("Key", "C");
    legendAbsEff->AddEntry(oldHLTAbsEff, "Old HLT Path");
    legendAbsEff->AddEntry(newHLTAbsEff, "New HLT Path");
    legendAbsEff->Draw();

    //c1->Print("cutflowAbsEffLog.png", "png");
    c1->Print("cutflowAbsEff.png", "png");


    TH1F* oldHLTRelEff = new TH1F("oldHLTRelEff", "", 7, 0.0, 7.0);
    TH1F* newHLTRelEff = new TH1F("newHLTRelEff", "", 7, 0.0, 7.0);
   
    for (int i = 1; i < n; i++) {
      if (i == 7) {
        oldHLTRelEff->Fill(names[i], oldFrac[i]/oldFrac[i-1]);
        newHLTRelEff->Fill(names[i], newFrac[i]/newFrac[i-2]);
      }
      else if (i == 5) {
        oldHLTRelEff->Fill(names[i], oldFrac[i]/oldFrac[i-2]);
        newHLTRelEff->Fill(names[i], newFrac[i]/newFrac[i-1]);
      }
      else{
        oldHLTRelEff->Fill(names[i], oldFrac[i]/oldFrac[i-1]);
        newHLTRelEff->Fill(names[i], newFrac[i]/newFrac[i-1]);
      }
    }

    TCanvas *c2 = new TCanvas("c2", "", 600, 400);
    //c2->SetLogy();
    gStyle->SetOptStat(kFALSE);

    oldHLTRelEff->SetTitle("HLT Filter Relative Efficiency Cutflow;; Efficiency");
    oldHLTRelEff->GetXaxis()->SetLabelSize(0.039);

    oldHLTRelEff->SetAxisRange(0,1.1, "Y");
    
    oldHLTRelEff->Draw("hist");
    oldHLTRelEff->SetLineColor(1);
    newHLTRelEff->SetLineStyle(7);
    newHLTRelEff->SetLineColor(9);
    newHLTRelEff->Draw("hist SAME");

    auto legendRelEff = new TLegend(0.1, 0.7, 0.4, 0.9);
    legendRelEff->SetHeader("Key", "C");
    legendRelEff->SetTextSize(0.035);
    legendRelEff->AddEntry(oldHLTRelEff, "Old HLT Path");
    legendRelEff->AddEntry(newHLTRelEff, "New HLT Path");
    legendRelEff->Draw();

    //c2->Print("cutflowRelEffLog.png", "png");
    c2->Print("cutflowRelEff.png", "png");
    } // end if statement for plotting

}
