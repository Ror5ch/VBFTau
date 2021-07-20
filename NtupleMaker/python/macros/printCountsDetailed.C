void printCountsDetailed(char* filename){

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

    double oldFrac[9];
    double newFrac[9];
    size_t n = sizeof(rawOld) / sizeof(double);


    double diff;
    std::cout << "Difference Between Absolute Efficiencies " << std::endl;
    std::cout << "nEvents = " << nEvents << std::endl;
    std::cout << "old val " << '\t' << "new val " << '\t' << "difference " << '\t' << "label" << std::endl;
    for (int i = 0; i < n; i++){
	oldFrac[i] = rawOld[i]/rawOld[0];
	newFrac[i] = rawNew[i]/rawNew[0];
	diff = oldFrac[i] - newFrac[i];
	std::cout << oldFrac[i] << '\t' << newFrac[i] << '\t' << diff << '\t' << names[i] << std::endl;
    }

    std::cout << '\n' << std::endl;
    std::cout << "Event Numbers " << std::endl;
    std::cout << "pass old trig: " << passOldTrigTight << '\t' << "pass new trig: " << passNewTrigTight << std::endl;
    std::cout << "old " << '\t' << "new " << '\t' << "diff " << '\t' << "label" << std::endl;
    for (int i = 0; i < n; i++){
	std::cout << rawOld[i] << '\t' << rawNew[i] << '\t' << rawOld[i] - rawNew[i] << '\t' << names[i] << std::endl;
    }

}
