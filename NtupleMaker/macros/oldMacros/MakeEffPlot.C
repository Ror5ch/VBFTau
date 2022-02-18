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

void MakeEffPlot(char* filename) {

    TFile *_file0 = TFile::Open(filename);

    TTree* tree = (TTree*)_file0->Get("outTree");

    double nEvents = tree->Draw("nEvents", "nEvents>0", "goff");
    double passDiTau35Both = tree->Draw("passDiTau35Both", "passDiTau35Both>0", "goff");
    double passNewVBFBoth = tree->Draw("passNewVBFBoth", "passNewVBFBoth>0", "goff");
    double passOR = tree->Draw("passNewVBFBoth", "passDiTau35Both > 0 || passNewVBFBoth > 0", "goff");

    std::cout << nEvents << '\t' << "nEvents" << '\n' << std::endl;
    std::cout << passDiTau35Both << '\t' << "passDiTau35Both" << '\n' << std::endl;
    std::cout << passNewVBFBoth << '\t' << "passNewVBFBoth" << '\n' << std::endl;
    std::cout << passOR << '\t' << "passOR" << '\n' << std::endl;

    TH1::SetDefaultSumw2();

    TH1F* histDiTau35 = new TH1F("histDiTau35", "", 10, 0, 300);
    TH1F* histOR = new TH1F("histOR", "", 10, 0, 300);
    TH1F* histRatio = new TH1F("histRatio", "", 10, 0, 300);

    //double finalbinDiTau35 = tree->Draw("t1_ptAOD", "passDiTau35Both>0 && t1_ptAOD>300", "goff");
    //double finalbinOR = tree->Draw("t1_ptAOD", "passDiTau35Both>0 && passNewVBF>0 && t1_ptAOD>300", "goff");

    tree->Draw("t1_ptAOD >> histDiTau35", "passDiTau35Both>0", "goff");
    tree->Draw("t1_ptAOD >> histOR", "passDiTau35Both>0 || passNewVBFBoth>0", "goff");

    histDiTau35->SetBinContent(histDiTau35->GetNbinsX(), histDiTau35->GetBinContent(GetNbinsX()) + histDiTau35->GetBinContent(GetNbinsX()+1));
    histOR->SetBinContent(histOR->GetNbinsX(), histOR->GetBinContent(GetNbinsX()) + histOR->GetBinContent(GetNbinsX()+1));

    histRatio = (TH1F*)histOR->Clone();
    histRatio->Divide(histDiTau35);


    TCanvas *c1 = new TCanvas("c1", "", 600, 400);
    //gStyle->SetOptStat(kFALSE);

    histRatio->SetTitle("(New or DiTau35) over DiTau 35");

    histRatio->Draw("E");
    //auto legendAbsEff = new TLegend(0.48, 0.7, 0.9, 0.9);
    //legendAbsEff->SetHeader("Key", "C");
    //legendAbsEff->Draw();

    c1->Print("t1_ptAOD_eff.png", "png");

}
