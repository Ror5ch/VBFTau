void FilterEffFixNtuple(char* inFileOld, char* inFileNew, char* inFileNewBroken, int log){

    //-------------------------------------getting data from two different files----------//
    // get file for old trig data
    TFile *oldFile = TFile::Open(inFileOld);

    TTree* oldTree = (TTree*)oldFile->Get("outTree");

    // in principle passSel for the old trigger and passSel for the new trigger are the same
    // at least for the overlap selection of datasets this macro was made for
    double passSelOld = 2108405;//oldTree->Draw("passSel", "passSel>0", "goff");

    // getting data from old trigger to fill to an array to be filled to a histogram later
    double passL1Old = oldTree->Draw("passL1Old", "passL1Old>0", "goff");
    double passhltHpsPFTauTrackOld = oldTree->Draw("passhltHpsPFTauTrackOld", "passhltHpsPFTauTrackOld>0", "goff");
    double passhltHpsDoublePFTauTightOld = oldTree->Draw("passhltHpsDoublePFTauTightOld", "passhltHpsDoublePFTauTightOld>0", "goff");
    double passhltHpsDoublePFTauAgainstMuonTightOld = oldTree->Draw("passhltHpsDoublePFTauAgainstMuonTightOld", "passhltHpsDoublePFTauAgainstMuonTightOld>0", "goff");
    double passhltMatchedVBFTwoTight = oldTree->Draw("passhltMatchedVBFTwoTight", "passhltMatchedVBFTwoTight>0", "goff");
    double passhltMatchedVBFOneTight = oldTree->Draw("passhltMatchedVBFOneTight", "passhltMatchedVBFOneTight>0", "goff");

    double passOldTrig = oldTree->Draw("passOldTrig", "passOldTrig>0", "goff");

    // put all the values into an array
    //double rawOld[] = {passSelOld, passL1Old, passhltHpsPFTauTrackOld, \
		passhltHpsDoublePFTauTightOld, passhltHpsDoublePFTauAgainstMuonTightOld, \
		passhltHpsDoublePFTauAgainstMuonTightOld, passhltMatchedVBFTwoTight, \
		passhltMatchedVBFOneTight, passOldTrig};
    double rawOld[] = {passSelOld, passL1Old, \
		passhltHpsDoublePFTauAgainstMuonTightOld, passhltHpsDoublePFTauAgainstMuonTightOld,\
		passhltMatchedVBFTwoTight, passOldTrig};

    oldFile->Close();

    // get file for new trig data
    TFile *newFile = TFile::Open(inFileNew);

    TTree* newTree = (TTree*)newFile->Get("outTree");

    // see earlier comment about passSel
    double passSelNew = 2108405;//newTree->Draw("passSel", "passSel>0", "goff");

    // getting data from old trigger to fill to an array to be filled to a histogram later
    double passL1New = newTree->Draw("passL1New", "passL1New>0", "goff");
    double passhltHpsPFTauTrackNew = newTree->Draw("passhltHpsPFTauTrackNew", "passhltHpsPFTauTrackNew>0", "goff");
    double passhltHpsDoublePFTauTightNew = newTree->Draw("passhltHpsDoublePFTauTightNew", "passhltHpsDoublePFTauTightNew>0", "goff");
    double passhltHpsDoublePFTauAgainstMuonTightNew = newTree->Draw("passhltHpsDoublePFTauAgainstMuonTightNew", "passhltHpsDoublePFTauAgainstMuonTightNew>0", "goff");
    double passhltHpsPFTau50Tight = newTree->Draw("passhltHpsPFTau50Tight", "passhltHpsPFTau50Tight>0", "goff");
    double passhltMatchedVBFIsoTauTwoTight = newTree->Draw("passhltMatchedVBFIsoTauTwoTight", "passhltMatchedVBFIsoTauTwoTight>0", "goff");

    double passNewTrig = newTree->Draw("passNewTrig", "passNewTrig>0", "goff");

    // put all the values into an array
    //double rawNew[] = {passSelNew, passL1New, passhltHpsPFTauTrackNew, \
		passhltHpsDoublePFTauTightNew, passhltHpsDoublePFTauAgainstMuonTightNew, \
		passhltHpsPFTau50Tight, passhltMatchedVBFIsoTauTwoTight, \
		passhltMatchedVBFIsoTauTwoTight, passNewTrig};
    double rawNew[] = {passSelNew, passL1New, \
		passhltHpsDoublePFTauAgainstMuonTightNew, \
		passhltHpsPFTau50Tight, passhltMatchedVBFIsoTauTwoTight, \
		passNewTrig};

    newFile->Close();

    // get file for new trig data
    TFile *newFileBroken = TFile::Open(inFileNewBroken);

    TTree* newTreeBroken = (TTree*)newFileBroken->Get("outTree");

    // see earlier comment about passSel
    double passNewBroken = 1264114;//newTreeBroken->Draw("passSel", "passSel>0", "goff");

    // getting data from old trigger to fill to an array to be filled to a histogram later
    double passL1NewBroken = newTreeBroken->Draw("passL1New", "passL1New>0", "goff");
    double passhltHpsPFTauTrackNewBroken = newTreeBroken->Draw("passhltHpsPFTauTrackNew", "passhltHpsPFTauTrackNew>0", "goff");
    double passhltHpsDoublePFTauTightNewBroken = newTreeBroken->Draw("passhltHpsDoublePFTauTightNew", "passhltHpsDoublePFTauTightNew>0", "goff");
    double passhltHpsDoublePFTauAgainstMuonTightNewBroken = newTreeBroken->Draw("passhltHpsDoublePFTauAgainstMuonTightNew", "passhltHpsDoublePFTauAgainstMuonTightNew>0", "goff");
    double passhltHpsPFTau50TightBroken = newTreeBroken->Draw("passhltHpsPFTau50Tight", "passhltHpsPFTau50Tight>0", "goff");
    double passhltMatchedVBFIsoTauTwoTightBroken = newTreeBroken->Draw("passhltMatchedVBFIsoTauTwoTight", "passhltMatchedVBFIsoTauTwoTight>0", "goff");

    double passNewTrigBroken = newTreeBroken->Draw("passNewTrig", "passNewTrig>0", "goff");

    // put all the values into an array
    //double rawNewBroken[] = {passNewBroken, passL1NewBroken, passhltHpsPFTauTrackNewBroken, \
		passhltHpsDoublePFTauTightNewBroken, passhltHpsDoublePFTauAgainstMuonTightNewBroken, \
		passhltHpsPFTau50TightBroken, passhltMatchedVBFIsoTauTwoTightBroken, \
		passhltMatchedVBFIsoTauTwoTightBroken, passNewTrigBroken};

    double rawNewBroken[] = {passNewBroken, passL1NewBroken, \
		passhltHpsDoublePFTauAgainstMuonTightNewBroken, \
		passhltHpsPFTau50TightBroken, passhltMatchedVBFIsoTauTwoTightBroken, \
		passNewTrigBroken};

    
    //-------------------------------filling and plotting---------------------------------//
    // now that we have both containers, we can fill histograms and write them to canvases
    /***
    const char *names[9] = {"None", "L1", "Req. 1 Tau", "Req. 2nd Tau", \
			"TauID vs Muon", "50 GeV Tau (New)", "Req. 2 Jets", \
			"115 GeV Jet (Old)", "Passed All Filters"};
    ***/
    const char *names[6] = {"None", "L1", "Req. 2nd Tau", \
			"45 GeV Tau (New)", "Req. 2 Jets", \
			"Passed Trigger Decision"};

    TH1F* oldTrigAbsEff = new TH1F("oldTrigAbsEff","", 5, 0.0, 5.0);
    TH1F* newTrigAbsEff = new TH1F("newTrigAbsEff","", 5, 0.0, 5.0);
    TH1F* newTrigAbsEffBroken = new TH1F("newTrigAbsEffBroken","", 5, 0.0, 5.0);

    double oldFrac[6];
    double newFrac[6];
    double newFracBroken[6];
    size_t n = sizeof(rawOld) / sizeof(double);
    for (int i = 0; i < n-1; i++){

	//std::cout << i << std::endl;
	std::cout << "Event # at label: " << names[i] << std::endl;
	oldFrac[i] = rawOld[i]/rawOld[0];
        oldTrigAbsEff->Fill(names[i], oldFrac[i]);
	//std::cout << "rawOld AbsEff: " << oldFrac[i] << std::endl;
	newFrac[i] = rawNew[i]/rawNew[0];
	newTrigAbsEff->Fill(names[i], newFrac[i]);
	//std::cout << "rawNew AbsEff: " << newFrac[i] << std::endl;
	newFracBroken[i] = rawNewBroken[i]/rawNewBroken[0];
	newTrigAbsEffBroken->Fill(names[i], newFracBroken[i]);
	//std::cout << "rawNewBroken AbsEff: " << newFracBroken[i] << std::endl;
	//
	std::cout << rawOld[i] << '\t' << rawNew[i] << '\t' << rawNewBroken[i] << std::endl;

    }

    TH1F* oldTrigRelEff = new TH1F("oldTrigRelEff", "", 4, 0.0, 4.0);
    TH1F* newTrigRelEff = new TH1F("newTrigRelEff", "", 4, 0.0, 4.0);
    TH1F* newTrigRelEffBroken = new TH1F("newTrigRelEffBroken", "", 4, 0.0, 4.0);
   
    for (int i = 1; i < n-1; i++){

	if (i == 8){
	    oldTrigRelEff->Fill(names[i], oldFrac[i]/oldFrac[i-1]);
	    newTrigRelEff->Fill(names[i], newFrac[i]/newFrac[i-2]);
	    newTrigRelEffBroken->Fill(names[i], newFracBroken[i]/newFracBroken[i-2]);
	}

	else if(i == 6){
	    oldTrigRelEff->Fill(names[i], oldFrac[i]/oldFrac[i-2]);
	    newTrigRelEff->Fill(names[i], newFrac[i]/newFrac[i-1]);
	    newTrigRelEffBroken->Fill(names[i], newFracBroken[i]/newFracBroken[i-1]);
	}

	else{
	    oldTrigRelEff->Fill(names[i], oldFrac[i]/oldFrac[i-1]);
	    newTrigRelEff->Fill(names[i], newFrac[i]/newFrac[i-1]);
	    newTrigRelEffBroken->Fill(names[i], newFracBroken[i]/newFracBroken[i-1]);
	}

    } 

    TCanvas *c1 = new TCanvas("c1", "", 600, 400);
    gStyle->SetOptStat(kFALSE);

    if (log == 1) c1->SetLogy();
    else oldTrigAbsEff->SetAxisRange(0,1.1, "Y");

    oldTrigAbsEff->SetTitle("Trigger Filter Absolute Efficiency Cutflow;; Efficiency");
    oldTrigAbsEff->GetXaxis()->SetLabelSize(0.039);


    oldTrigAbsEff->Draw("hist");
    oldTrigAbsEff->SetLineColor(1);
    newTrigAbsEff->SetLineStyle(7);
    newTrigAbsEff->SetLineColor(9);
    newTrigAbsEff->Draw("hist SAME");
    newTrigAbsEffBroken->SetLineStyle(2);
    newTrigAbsEffBroken->SetLineColor(2);
    newTrigAbsEffBroken->Draw("hist SAME");

    auto legendAbsEff = new TLegend(0.48, 0.7, 0.9, 0.9);
    legendAbsEff->SetHeader("Key", "C");
    legendAbsEff->AddEntry(oldTrigAbsEff, "Old Trigger Path");
    legendAbsEff->AddEntry(newTrigAbsEff, "New Trigger Path w/ Eta Fix");
    legendAbsEff->AddEntry(newTrigAbsEffBroken, "New Trigger Path w/o Eta Fix");
    legendAbsEff->Draw();

    if (log == 1) c1->Print("offline_cutflowAbsEffLog.png", "png");
    else c1->Print("offline_cutflowAbsEff.png", "png");

    TCanvas *c2 = new TCanvas("c2", "", 600, 400);
    gStyle->SetOptStat(kFALSE);

    if (log == 1) c2->SetLogy();
    else oldTrigRelEff->SetAxisRange(0,1.1, "Y");

    oldTrigRelEff->SetTitle("Trigger Filter Relative Efficiency Cutflow;; Efficiency");
    oldTrigRelEff->GetXaxis()->SetLabelSize(0.039);

    oldTrigRelEff->Draw("hist");
    oldTrigRelEff->SetLineColor(1);
    newTrigRelEff->SetLineStyle(7);
    newTrigRelEff->SetLineColor(9);
    newTrigRelEff->Draw("hist SAME");
    newTrigRelEffBroken->SetLineStyle(2);
    newTrigRelEffBroken->SetLineColor(2);
    newTrigRelEffBroken->Draw("hist SAME");

    auto legendRelEff = new TLegend(0.1, 0.7, 0.5, 0.9);
    legendRelEff->SetHeader("Key", "C");
    legendRelEff->SetTextSize(0.035);
    legendRelEff->AddEntry(oldTrigRelEff, "Old Trigger Path");
    legendRelEff->AddEntry(newTrigRelEff, "New Trigger Path w/ Eta Fix");
    legendRelEff->AddEntry(newTrigRelEffBroken, "New Trigger Path w/o Eta Fix");
    legendRelEff->Draw();

    if (log == 1) c2->Print("offline_cutflowRelEffLog.png", "png");
    else c2->Print("offline_cutflowRelEff.png", "png");

}
