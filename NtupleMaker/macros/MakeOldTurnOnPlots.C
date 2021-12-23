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

void MakeOldTurnOnPlots(char* filename, int key) {

    TFile *_file0 = TFile::Open(filename);

    TTree* tree = (TTree*)_file0->Get("outTree");

    double nEvents = tree->Draw("nEvents", "nEvents>0", "goff");
    double passNewVBFBoth = tree->Draw("passNewVBFBoth", "passNewVBFBoth>0", "goff");

    std::cout << nEvents << '\t' << "nEvents" << '\n' << std::endl;
    std::cout << passNewVBFBoth << '\t' << "passNewVBFBoth" << '\n' << std::endl;

    TH1::SetDefaultSumw2();

    TCanvas *c1 = new TCanvas("c1", "", 600, 400);
    gStyle->SetOptStat(kFALSE);

    if (key == 0) {
      TH1F* h_t1TOnum = new TH1F("h_t1TOnum", "", 15, 0, 150);
      TH1F* h_t1TOdem = new TH1F("h_t1TOdem", "", 15, 0, 150);
      TH1F* h_t1TOratio = new TH1F("h_t1TOratio", "", 15, 0, 150);

      tree->Draw("t1_ptAOD >> h_t1TOnum", "passt1TO>0 && matchedBothNew>0","goff");
      tree->Draw("t1_ptAOD >> h_t1TOdem", "passt1TO>0","goff");

      h_t1TOratio = (TH1F*)h_t1TOnum->Clone();
      h_t1TOratio->Divide(h_t1TOdem);

      h_t1TOratio->SetTitle("t1_pt Turn-On Plot");
      h_t1TOratio->GetYaxis()->SetRange(0,1);
      h_t1TOratio->Draw("E");

      c1->Print("t1_pt_turnon.png", "png");
    }

    if (key == 1) {
      TH1F* h_t2TOnum = new TH1F("h_t2TOnum", "", 10, 0, 100);
      TH1F* h_t2TOdem = new TH1F("h_t2TOdem", "", 10, 0, 100);
      TH1F* h_t2TOratio = new TH1F("h_t2TOratio", "", 10, 0, 100);

      tree->Draw("t2_ptAOD >> h_t2TOnum", "passt2TO>0 && matchedBothNew>0", "goff");
      tree->Draw("t2_ptAOD >> h_t2TOdem", "passt2TO>0", "goff");

      h_t2TOratio = (TH1F*)h_t2TOnum->Clone();
      h_t2TOratio->Divide(h_t2TOdem);

      h_t2TOratio->SetTitle("t2_pt Turn-On Plot");
      h_t2TOratio->Draw("E");

      c1->Print("t2_pt_turnon.png", "png");
    }

    if (key == 2) {
      TH1F* h_j1TOnum = new TH1F("h_j1TOnum", "", 10, 0, 300);
      TH1F* h_j1TOdem = new TH1F("h_j1TOdem", "", 10, 0, 300);
      TH1F* h_j1TOratio = new TH1F("h_j1TOratio", "", 10, 0, 300);

      tree->Draw("j1_ptAOD >> h_j1TOnum", "passj1TO>0 && matchedBothNew>0", "goff");
      tree->Draw("j1_ptAOD >> h_j1TOdem", "passj1TO>0", "goff");

      h_j1TOratio = (TH1F*)h_j1TOnum->Clone();
      h_j1TOratio->Divide(h_j1TOdem);

      h_j1TOratio->SetTitle("j1_pt Turn-On Plot");
      h_j1TOratio->Draw("E");

      c1->Print("j1_pt_turnon.png", "png");
    }

    if (key == 3) {
      TH1F* h_j2TOnum = new TH1F("h_j2TOnum", "", 10, 20, 120);
      TH1F* h_j2TOdem = new TH1F("h_j2TOdem", "", 10, 20, 120);
      TH1F* h_j2TOratio = new TH1F("h_j2TOratio", "", 10, 20, 120);

      tree->Draw("j2_ptAOD >> h_j2TOnum", "passj2TO>0 && matchedBothNew>0", "goff");
      tree->Draw("j2_ptAOD >> h_j2TOdem", "passj2TO>0", "goff");

      h_j2TOratio = (TH1F*)h_j2TOnum->Clone();
      h_j2TOratio->Divide(h_j2TOdem);

      h_j2TOratio->SetTitle("j2_pt Turn-On Plot");
      h_j2TOratio->Draw("E");

      c1->Print("j2_pt_turnon.png", "png");
    }

    if (key == 4) {
      TH1F* h_mjjTOnum = new TH1F("h_mjjTOnum", "", 9, 400, 1500);
      TH1F* h_mjjTOdem = new TH1F("h_mjjTOdem", "", 9, 400, 1500);
      TH1F* h_mjjTOratio = new TH1F("h_mjjTOratio", "", 9, 400, 1500);

      tree->Draw("mjjAOD >> h_mjjTOnum", "passmjjTO>0 && matchedBothNew>0", "goff");
      tree->Draw("mjjAOD >> h_mjjTOdem", "passmjjTO>0", "goff");

      h_mjjTOratio = (TH1F*)h_mjjTOnum->Clone();
      h_mjjTOratio->Divide(h_mjjTOdem);

      h_mjjTOratio->SetTitle("mjj_pt Turn-On Plot");
      h_mjjTOratio->Draw("E");

      c1->Print("mjj_turnon.png", "png");
    }

}
