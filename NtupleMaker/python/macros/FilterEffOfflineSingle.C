void FilterEffOfflineSingle(char* inFileOld, char* inFileNew){

    //-------------------------------------getting data from two different files----------//
    // get file for old trig data
    TFile *oldFile = TFile::Open(inFileOld);

    TTree* oldTree = (TTree*)oldFile->Get("outTree");

    // in principle passSel for the old trigger and passSel for the new trigger are the same
    // at least for the overlap selection of datasets this macro was made for
    double passSelOld = oldTree->Draw("passSel", "passSel>0", "goff");

    // getting data from old trigger to fill to an array to be filled to a histogram later
    double passL1Old = oldTree->Draw("passL1Old", "passL1Old>0", "goff");
    double passhltHpsPFTauTrackOld = oldTree->Draw("passhltHpsPFTauTrackOld", "passhltHpsPFTauTrackOld>0", "goff");
    double passhltHpsDoublePFTauTightOld = oldTree->Draw("passhltHpsDoublePFTauTightOld", "passhltHpsDoublePFTauTightOld>0", "goff");
    double passhltHpsDoublePFTauAgainstMuonTightOld = oldTree->Draw("passhltHpsDoublePFTauAgainstMuonTightOld", "passhltHpsDoublePFTauAgainstMuonTightOld>0", "goff");
    double passhltMatchedVBFTwoTight = oldTree->Draw("passhltMatchedVBFTwoTight", "passhltMatchedVBFTwoTight>0", "goff");
    double passhltMatchedVBFOneTight = oldTree->Draw("passhltMatchedVBFOneTight", "passhltMatchedVBFOneTight>0", "goff");

    double passSelAndOldTrig = oldTree->Draw("passSelAndOldTrig", "passSelAndOldTrig>0", "goff");

    // put all the values into an array
    double rawOld[] = {passSelOld, passL1Old, passhltHpsPFTauTrackOld, \
		passhltHpsDoublePFTauTightOld, passhltHpsDoublePFTauAgainstMuonTightOld, \
		passhltHpsDoublePFTauAgainstMuonTightOld, passhltMatchedVBFTwoTight, \
		passhltMatchedVBFOneTight, passSelAndOldTrig};

    oldFile->Close();

    // get file for new trig data
    TFile *newFile = TFile::Open(inFileNew);

    TTree* newTree = (TTree*)newFile->Get("outTree");

    // see earlier comment about passSel
    double passSelNew = newTree->Draw("passSel", "passSel>0", "goff");

    // getting data from old trigger to fill to an array to be filled to a histogram later
    double passL1New = newTree->Draw("passL1New", "passL1New>0", "goff");
    double passhltHpsPFTauTrackNew = newTree->Draw("passhltHpsPFTauTrackNew", "passhltHpsPFTauTrackNew>0", "goff");
    double passhltHpsDoublePFTauTightNew = newTree->Draw("passhltHpsDoublePFTauTightNew", "passhltHpsDoublePFTauTightNew>0", "goff");
    double passhltHpsDoublePFTauAgainstMuonTightNew = newTree->Draw("passhltHpsDoublePFTauAgainstMuonTightNew", "passhltHpsDoublePFTauAgainstMuonTightNew>0", "goff");
    double passhltHpsPFTau50Tight = newTree->Draw("passhltHpsPFTau50Tight", "passhltHpsPFTau50Tight>0", "goff");
    double passhltMatchedVBFIsoTauTwoTight = newTree->Draw("passhltMatchedVBFIsoTauTwoTight", "passhltMatchedVBFIsoTauTwoTight>0", "goff");

    double passSelAndNewTrig = newTree->Draw("passSelAndNewTrig", "passSelAndNewTrig>0", "goff");

    // put all the values into an array
    double rawNew[] = {passSelNew, passL1New, passhltHpsPFTauTrackNew, \
		passhltHpsDoublePFTauTightNew, passhltHpsDoublePFTauAgainstMuonTightNew, \
		passhltHpsPFTau50Tight, passhltMatchedVBFIsoTauTwoTight, \
		passhltMatchedVBFIsoTauTwoTight, passSelAndNewTrig};
    
    //-------------------------------filling and plotting---------------------------------//
    // now that we have both containers, we can fill histograms and write them to canvases
    const char *names[9] = {"Offline Only", "Off. + L1", "Off. + Req. 1 Tau", "Off. + Req. 2nd Tau", \
			"Off. + TauID vs Muon", "Off. + 45 GeV Tau (New)", "Off. + Req. 2 Jets", \
			"Off. + 115 GeV Jet (Old)", "Off. + Trigger"};

    TH1F* oldTrigAbsEff = new TH1F("oldTrigAbsEff","", 9, 0.0, 9.0);
    TH1F* newTrigAbsEff = new TH1F("newTrigAbsEff","", 9, 0.0, 9.0);

    double oldFrac[9];
    double newFrac[9];
    size_t n = sizeof(rawOld) / sizeof(double);
    for (int i = 0; i < n; i++){

	std::cout << i << std::endl;
	oldFrac[i] = rawOld[i]/rawOld[0];
        oldTrigAbsEff->Fill(names[i], oldFrac[i]);
	std::cout << "rawOld AbsEff: " << oldFrac[i] << std::endl;
	newFrac[i] = rawNew[i]/rawNew[0];
	newTrigAbsEff->Fill(names[i], newFrac[i]);
	std::cout << "rawNew AbsEff: " << newFrac[i] << std::endl;

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

    //oldTrigAbsEff->SetAxisRange(0,1.1, "Y");

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

    c1->Print("offline_cutflowAbsEffLog.png", "png");
    //c1->Print("offline_cutflowAbsEff.png", "png");

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

    auto legendRelEff = new TLegend(0.1, 0.1, 0.4, 0.3);
    legendRelEff->SetHeader("Key", "C");
    legendRelEff->SetTextSize(0.035);
    legendRelEff->AddEntry(oldTrigRelEff, "Old Trigger Path");
    legendRelEff->AddEntry(newTrigRelEff, "New Trigger Path");
    legendRelEff->Draw();

    c2->Print("offline_cutflowRelEffLog.png", "png");
    //c2->Print("offline_cutflowRelEff.png", "png");

}
