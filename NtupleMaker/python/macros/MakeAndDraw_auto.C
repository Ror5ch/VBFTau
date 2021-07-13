void MakeAndDraw_auto(char* filename){

    // get file
    TFile *_file0 = TFile::Open(filename);
    // get TTree (must go thru demo directory where the tree is stored)
    TTree* tree = (TTree*)_file0->Get("demo/vbf");    

    //-------------------get data to be used in histos------------//

    // nEvents
    double nEvents = tree->Draw("nEvents", "nEvents>0", "goff");

    // old trigger filters and final decision
    double passhltL1VBFDiJetOR = tree->Draw("passhltL1VBFDiJetOR", "passhltL1VBFDiJetOR>0", "goff");
    double passhltHpsPFTauTrackOld = tree->Draw("passhltHpsPFTauTrack", "passhltL1VBFDiJetOR>0 && passhltHpsPFTauTrack>0", "goff");
    double passhltHpsDoublePFTauTightOld = tree->Draw("passhltHpsDoublePFTauTight", "passhltL1VBFDiJetOR>0 && passhltHpsPFTauTrack>0 && passhltHpsDoublePFTauTight>0", "goff");
    double passhltHpsDoublePFTauAgainstMuonTightOld = tree->Draw("passhltHpsDoublePFTauAgainstMuonTight", "passhltL1VBFDiJetOR>0 && passhltHpsPFTauTrack>0 && passhltHpsDoublePFTauTight>0 && passhltHpsDoublePFTauAgainstMuonTight>0", "goff"); 
    double passhltMatchedVBFTwoTight = tree->Draw("passhltMatchedVBFTwoTight", "passhltL1VBFDiJetOR>0 && passhltHpsPFTauTrack>0 && passhltHpsDoublePFTauTight>0 && passhltHpsDoublePFTauAgainstMuonTight>0 && passhltMatchedVBFTwoTight>0", "goff");
    double passhltMatchedVBFOneTight = tree->Draw("passhltMatchedVBFOneTight", "passhltL1VBFDiJetOR>0 && passhltHpsPFTauTrack>0 && passhltHpsDoublePFTauTight>0 && passhltHpsDoublePFTauAgainstMuonTight>0 && passhltMatchedVBFTwoTight>0 && passhltMatchedVBFOneTight>0", "goff");

    double passOldTrigTight = tree->Draw("passOldTrigTight", "passOldTrigTight>0", "goff");

    // new trigger filters and final decision
    double passhltL1VBFDiJetIsoTau = tree->Draw("passhltL1VBFDiJetIsoTau", "passhltL1VBFDiJetIsoTau>0", "goff");
    double passhltHpsPFTauTrackNew = tree->Draw("passhltHpsPFTauTrack", "passhltL1VBFDiJetIsoTau>0 && passhltHpsPFTauTrack>0", "goff");
    double passhltHpsDoublePFTauTightNew = tree->Draw("passhltHpsDoublePFTauTight", "passhltL1VBFDiJetIsoTau>0 && passhltHpsPFTauTrack>0 && passhltHpsDoublePFTauTight>0", "goff");
    double passhltHpsDoublePFTauAgainstMuonTightNew = tree->Draw("passhltHpsDoublePFTauAgainstMuonTight", "passhltL1VBFDiJetIsoTau>0 && passhltHpsPFTauTrack>0 && passhltHpsDoublePFTauTight>0 && passhltHpsDoublePFTauAgainstMuonTight>0", "goff"); 
    double passhltHpsPFTau50Tight = tree->Draw("passhltHpsPFTau50Tight", "passhltL1VBFDiJetIsoTau>0 && passhltHpsPFTauTrack>0 && passhltHpsDoublePFTauTight>0 && passhltHpsDoublePFTauAgainstMuonTight>0 && passhltHpsPFTau50Tight>0", "goff");
    double passhltMatchedVBFIsoTauTwoTight = tree->Draw("passhltMatchedVBFIsoTauTwoTight", "passhltL1VBFDiJetIsoTau>0 && passhltHpsPFTauTrack>0 && passhltHpsDoublePFTauTight>0 && passhltHpsDoublePFTauAgainstMuonTight>0 && passhltHpsPFTau50Tight>0 && passhltMatchedVBFIsoTauTwoTight>0", "goff");

    double passNewTrigTight = tree->Draw("passNewTrigTight", "passNewTrigTight>0", "goff");

    // filters common to both triggers
    //double passhltHpsPFTauTrack = tree->Draw("passhltHpsPFTauTrack", "passhltHpsPFTauTrack>0", "goff");
    //double passhltHpsDoublePFTauTight = tree->Draw("passhltHpsDoublePFTauTight", "passhltHpsDoublePFTauTight>0", "goff");
    //double passhltHpsDoublePFTauAgainstMuonTight = tree->Draw("passhltHpsDoublePFTauAgainstMuonTight", "passhltHpsDoublePFTauAgainstMuonTight>0", "goff"); 

    // arrays holding these values
    // zeros where filters don't match / no counterpart exists
    double rawOld[] = {nEvents, passhltL1VBFDiJetOR, passhltHpsPFTauTrackOld, \
		passhltHpsDoublePFTauTightOld, passhltHpsDoublePFTauAgainstMuonTightOld, \
		passhltHpsDoublePFTauAgainstMuonTightOld, passhltMatchedVBFTwoTight, \
		passhltMatchedVBFOneTight, passOldTrigTight};
    double rawNew[] = {nEvents, passhltL1VBFDiJetIsoTau, passhltHpsPFTauTrackNew, \
		passhltHpsDoublePFTauTightNew, passhltHpsDoublePFTauAgainstMuonTightNew, \
		passhltHpsPFTau50Tight, passhltMatchedVBFIsoTauTwoTight, \
		passhltMatchedVBFIsoTauTwoTight, passNewTrigTight};

    //-----------------------------make histos-------------------//

    const char *names[9] = {"None", "L1", "Req. 1 Tau", "Req. 2nd Tau", \
			"TauID vs Muon", "50 GeV Tau (New)", "Req. 2 Jets", \
			"115 GeV Jet (Old)", "Passed All Filters"};

    TH1F* oldTrigAbsEff = new TH1F("oldTrigAbsEff","", 9, 0.0, 9.0);
    TH1F* newTrigAbsEff = new TH1F("newTrigAbsEff","", 9, 0.0, 9.0);

    double oldFrac[9];
    double newFrac[9];
    size_t n = sizeof(rawOld) / sizeof(double);
    for (int i = 0; i < n; i++){

	oldFrac[i] = rawOld[i]/rawOld[0];
        oldTrigAbsEff->Fill(names[i], oldFrac[i]);
	//std::cout << "rawoldabseff: " << oldFrac[i] << std::endl;
	newFrac[i] = rawNew[i]/rawNew[0];
	newTrigAbsEff->Fill(names[i], newFrac[i]);
	//std::cout << "rawnewabseff: " << newFrac[i] << std::endl;

    }

    TH1F* oldTrigRelEff = new TH1F("oldTrigRelEff", "", 8, 0.0, 8.0);
    TH1F* newTrigRelEff = new TH1F("newTrigRelEff", "", 8, 0.0, 8.0);
   
    for (int i = 1; i < n; i++){

	if (i == 8){
	    oldTrigRelEff->Fill(names[i], oldFrac[i]/oldFrac[i-1]);
	    newTrigRelEff->Fill(names[i], newFrac[i]/newFrac[i-2]);
	}

	else if(i == 6){
	    oldTrigRelEff->Fill(names[i], oldFrac[i]/oldFrac[i-2]);
	    newTrigRelEff->Fill(names[i], newFrac[i]/newFrac[i-1]);
	}

	else{
	    oldTrigRelEff->Fill(names[i], oldFrac[i]/oldFrac[i-1]);
	    newTrigRelEff->Fill(names[i], newFrac[i]/newFrac[i-1]);
	}

    } 

    TCanvas *c1 = new TCanvas("c1", "", 600, 400);
    c1->SetLogy();
    gStyle->SetOptStat(kFALSE);

    oldTrigAbsEff->SetTitle("Trigger Filter Absolute Efficiency Cutflow;; Efficiency");
    oldTrigAbsEff->GetXaxis()->SetLabelSize(0.039);

    oldTrigAbsEff->Draw("hist");
    oldTrigAbsEff->SetLineColor(1);
    newTrigAbsEff->SetLineStyle(7);
    newTrigAbsEff->SetLineColor(9);
    newTrigAbsEff->Draw("hist SAME");

    auto legendAbsEff = new TLegend(0.48, 0.7, 0.9, 0.9);
    legendAbsEff->SetHeader("Key", "C");
    legendAbsEff->AddEntry(oldTrigAbsEff, "Old Trigger Path");
    legendAbsEff->AddEntry(newTrigAbsEff, "New Trigger Path");
    legendAbsEff->Draw();

    c1->Print("cutflowAbsEffLog.png", "png");
    //c1->Print("cutflowAbsEff.png", "png");

    TCanvas *c2 = new TCanvas("c2", "", 600, 400);
    c2->SetLogy();
    gStyle->SetOptStat(kFALSE);

    oldTrigRelEff->SetTitle("Trigger Filter Relative Efficiency Cutflow;; Efficiency");
    oldTrigRelEff->GetXaxis()->SetLabelSize(0.039);

    //oldTrigRelEff->SetAxisRange(0,1.1, "Y");
    
    oldTrigRelEff->Draw("hist");
    oldTrigRelEff->SetLineColor(1);
    newTrigRelEff->SetLineStyle(7);
    newTrigRelEff->SetLineColor(9);
    newTrigRelEff->Draw("hist SAME");

    auto legendRelEff = new TLegend(0.1, 0.7, 0.4, 0.9);
    legendRelEff->SetHeader("Key", "C");
    legendRelEff->SetTextSize(0.035);
    legendRelEff->AddEntry(oldTrigRelEff, "Old Trigger Path");
    legendRelEff->AddEntry(newTrigRelEff, "New Trigger Path");
    legendRelEff->Draw();

    c2->Print("cutflowRelEffLog.png", "png");
    //c2->Print("cutflowRelEff.png", "png");
}
