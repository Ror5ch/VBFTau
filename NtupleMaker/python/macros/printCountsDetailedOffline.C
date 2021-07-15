void printCountsDetailedOffline(char* inFileOld, char* inFileNew){

    //-------------------------------------getting data from two different files----------//
    // get file for old trig data
    TFile *oldFile = TFile::Open(inFileOld);

    TTree* oldTree = (TTree*)oldFile->Get("outTree");

    // in principle passSel for the old trigger and passSel for the new trigger are the same
    // at least for the overlap selection of datasets this macro was made for
    double passBaseOld = oldTree->Draw("passBase", "passBase>0", "goff");
    double passBaseAndOldTrig = oldTree->Draw("passBaseAndOldTrig", "passBaseAndOldTrig>0", "goff");
    double passOldTrig = oldTree->Draw("passOldTrig", "passOldTrig>0", "goff");
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
    double passBaseNew = newTree->Draw("passBase", "passBase>0", "goff");
    double passBaseAndNewTrig = newTree->Draw("passBaseAndNewTrig", "passBaseAndNewTrig>0", "goff");
    double passNewTrig = newTree->Draw("passNewTrig", "passNewTrig>0", "goff");
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

    double oldFrac[9];
    double newFrac[9];
    size_t n = sizeof(rawOld) / sizeof(double);

    double diff;

    std::cout << "Differences in Absolute Efficiency of Filters after Offline Selection" << std::endl;
    std::cout << "old val " << '\t' << "new val " << '\t' << "difference " << '\t' << "label " << std::endl;
    for (int i = 0; i < n; i++){

	oldFrac[i] = rawOld[i]/rawOld[0];
	newFrac[i] = rawNew[i]/rawNew[0];

	diff = oldFrac[i] - newFrac[i];

	std::cout << oldFrac[i] << '\t' << newFrac[i] << '\t' << diff << '\t' << names[i] << std::endl;

    }

    std::cout << '\n' << std::endl;

    std::cout << "Event Numbers" << std::endl;
    std::cout << "events passing base for old or new sel (should be same) " << passBaseOld << ' ' << passBaseNew << std::endl;
    std::cout << "events passing old or new sel (sel are same) = " << passSelOld << ' ' << passSelNew << std::endl;
    std::cout << "pass base and old trig: " << passBaseAndOldTrig << '\t' << " pass base and new trig: " << passBaseAndNewTrig << std::endl;
    std::cout << "pass old trig: " << passOldTrig << '\t' << "pass new trig: " << passNewTrig << std::endl;
    std::cout << "old " << '\t' << "new " << '\t' << "difference " << '\t' << "label" << std::endl;
    for (int i = 0; i < n; i++){

	std::cout << rawOld[i] << '\t' << rawNew[i] << '\t' << rawOld[i] - rawNew[i] << '\t' << names[i] << std::endl;

    }

  /*** 
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
***/
}
