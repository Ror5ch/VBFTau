#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <string>
#include <iomanip>
#include <tuple>

#include "TH1F.h"
#include "TH2F.h"	//won't need?
#include "TH3F.h"	//same
#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TMath.h"
#include "TSystem.h"
#include "TRandom.h"
#include "TLorentzVector.h"
#include "TRandom3.h"

#include "trigger_tree.h"

// example running on wisc server: ./trigger_selection.exe /hdfs/store/user/ballmond/merged_trigger_05092020/merged.root ./output.root new

// simpleMatching
// inputs:
// vector of TLorentzVectors, representing objects passing trigger
// TLorentzVector, representing aod object to be matched
// output:
// integer representing location of object with lowest dR between trigger objs in container and given aod object
int simpleMatching(std::vector<TLorentzVector> trigContainer, TLorentzVector aodObj) {
    int bestObjIndex = -1;
    float dRObj = 999;
    float dRObj_ = 999;
    for (int iTrigObj = 0; iTrigObj < trigContainer.size(); ++iTrigObj){
	dRObj_ = aodObj.DeltaR(trigContainer.at(iTrigObj));
	if (dRObj_ < dRObj) {dRObj = dRObj_; bestObjIndex = iTrigObj;}
    }
    return bestObjIndex;
}

std::tuple<TLorentzVector, TLorentzVector> matchTwoObjs(std::vector<TLorentzVector> objCands, TLorentzVector aodObj1, TLorentzVector aodObj2){

    int objMatchIndex1 = simpleMatching(objCands, aodObj1);
    int objMatchIndex2 = simpleMatching(objCands, aodObj2);
    TLorentzVector tempObj1 = objCands.at(objMatchIndex1);
    TLorentzVector tempObj2 = objCands.at(objMatchIndex2);
    double dRtempObj1 = tempObj1.DeltaR(aodObj1);
    double dRtempObj2 = tempObj2.DeltaR(aodObj2);
    // if AODs match to the same object index, check which has a smaller dR
    // then remove that object and rematch
    if (objMatchIndex1 == objMatchIndex2){
	std::vector<TLorentzVector> tempObjCands = objCands;
	tempObjCands.erase(tempObjCands.begin() + objMatchIndex1);
	if (dRtempObj1 < dRtempObj2){
	    objMatchIndex2 = simpleMatching(tempObjCands, aodObj2);
	    tempObj2 = tempObjCands.at(objMatchIndex2);
	}
	if (dRtempObj2 < dRtempObj1){
	    objMatchIndex1 = simpleMatching(tempObjCands, aodObj1);
	    tempObj1 = tempObjCands.at(objMatchIndex1);
	}
    }

    return std::make_tuple(tempObj1, tempObj2);
}

std::tuple<TLorentzVector, TLorentzVector> highestMjjPair(std::vector<TLorentzVector> jetContainer) {
    int highestMjjCandIndex = -1;
    int mjjCandCounter = -1; //start at -1 so when the first element is added it's element zero
    float tempMjj = -1;
    float tempMjj_ = -1;
    std::vector<std::pair<int,int>> jetPairs;
    for (int iObj = 0; iObj < jetContainer.size(); ++iObj) {
	for (int jObj = 0; jObj < jetContainer.size(); ++jObj) {
	    if (jObj >= iObj) continue;
	    // if TLorentz objects aren't overlapped, store their positions as a pair
	    if (jetContainer.at(iObj).DeltaR(jetContainer.at(jObj)) > 0.5) {
		jetPairs.push_back(std::make_pair(jObj, iObj));
		tempMjj = (jetContainer.at(iObj) + jetContainer.at(jObj)).M();
		mjjCandCounter += 1;
		if (tempMjj_ < tempMjj) { tempMjj_ = tempMjj;	highestMjjCandIndex = mjjCandCounter;}
	    }
	}
    }
    // define two empty TLorentzVectors
    // if they aren't filled from the jet pair cands, then the output will be two
    // empty jets, whose mjj will of course be zero which therefore will not pass any
    // enforced selection
    TLorentzVector outJet1, outJet2;
    outJet1.SetPtEtaPhiE(0,0,0,0);
    outJet2.SetPtEtaPhiE(0,0,0,0);
    if (highestMjjCandIndex != -1) {
	outJet1 = jetContainer.at(jetPairs.at(highestMjjCandIndex).first);
	outJet2 = jetContainer.at(jetPairs.at(highestMjjCandIndex).second);
    }
    return std::make_tuple(outJet1, outJet2);
}

//debugging functions that print kinematic info
void coutAODobjs(TLorentzVector AODobj1, TLorentzVector AODobj2) {
    std::cout << "obj #" << '\t' << "pt" << '\t' << "eta" << '\t' << "phi" << std::endl;
    std::cout << "1      " << std::setprecision(4) << AODobj1.Pt() << '\t' << AODobj1.Eta() << '\t' << AODobj1.Phi() << std::endl;
    std::cout << "2      " << std::setprecision(4) << AODobj2.Pt() << '\t' << AODobj2.Eta() << '\t' << AODobj2.Phi() << std::endl;
}

void coutL1objs(std::vector<TLorentzVector> L1ObjContainer, std::vector<TLorentzVector> AODObjContainer) {
    // assume AODObjContainer is (aodJet1, aodJet2, aodTau1, aodTau2)
    std::cout << "obj #" << '\t' << "pt" << '\t' << "eta" << '\t' << "phi" <<\
    '\t' << "dR AODJet 1" << '\t' << "dR AODJet 2" << '\t' << "dR AODTau 1" << '\t' << "dR AODTau 2" << std::endl;
    TLorentzVector tempL1Obj;
    for (int iObj = 0; iObj < L1ObjContainer.size(); ++iObj) {
	tempL1Obj = L1ObjContainer.at(iObj);
	std::cout << iObj << '\t' << tempL1Obj.Pt() << '\t' << tempL1Obj.Eta() << '\t' << tempL1Obj.Phi() << '\t' \
		  << tempL1Obj.DeltaR(AODObjContainer.at(0)) << '\t' << '\t' << tempL1Obj.DeltaR(AODObjContainer.at(1)) << '\t' << '\t' \
		  << tempL1Obj.DeltaR(AODObjContainer.at(2)) << '\t' << '\t' << tempL1Obj.DeltaR(AODObjContainer.at(3)) << std::endl;
    }
}

void dumpEventKinemInfo(int iEntry, std::string label,
                        std::vector<TLorentzVector> aodObjs, std::vector<TLorentzVector> jets, std::vector<TLorentzVector> taus) {
    // assume aodObjs is (aodJet1, aodJet2, aodTau1, aodTau2)
    std::cout << "iEntry: " << iEntry << std::endl;
    std::cout << "-------------" << label << "--------------" << std::endl;
    std::cout << "aod jet info" << std::endl;
    coutAODobjs(aodObjs.at(0), aodObjs.at(1)); 
    std::cout << "aod tau info" << std::endl;
    coutAODobjs(aodObjs.at(2), aodObjs.at(3));

    std::cout << "jet info" << std::endl;
    std::cout << "jet size " << jets.size() << std::endl;
    coutL1objs(jets, aodObjs);

    std::cout << "tau info" << std::endl;
    std::cout << "tau size " << taus.size() << std::endl;
    coutL1objs(taus, aodObjs);

    std::cout << "-----------------------------------------" << std::endl;
}

bool AODObjInContainer(std::vector<TLorentzVector> L1ObjContainer, std::vector<TLorentzVector> AODObjContainer, int AODObj) {
    // assume AODObjContainer is (aodJet1, aodJet2, aodTau1, aodTau2)
    bool AODObjInContainer = false;
    TLorentzVector tempObj;
    for (int iObj = 0; iObj < L1ObjContainer.size(); ++iObj) {
	tempObj = L1ObjContainer.at(iObj);
	if (tempObj.DeltaR(AODObjContainer.at(AODObj)) < 0.5) return AODObjInContainer = true;
    }

    return AODObjInContainer;
}

std::vector<TLorentzVector> hltFillWithCands(trigger_tree* inTree, std::string filterName, int objNumber){
    std::vector<float>* branchPt;
    std::vector<float>* branchEta;
    std::vector<float>* branchPhi;
    std::vector<float>* branchEnergy;

    if (filterName == "hltHpsDoublePFTauTight") {
	branchPt = inTree->hltHpsDoublePFTauTight_pt;
	branchEta = inTree->hltHpsDoublePFTauTight_eta;
	branchPhi = inTree->hltHpsDoublePFTauTight_phi;
	branchEnergy = inTree->hltHpsDoublePFTauTight_energy;
    }
    if (filterName == "hltMatchedVBFTwoTight") {
	branchPt = inTree->hltMatchedVBFTwoTight_pt;
	branchEta = inTree->hltMatchedVBFTwoTight_eta;
	branchPhi = inTree->hltMatchedVBFTwoTight_phi;
	branchEnergy = inTree->hltMatchedVBFTwoTight_energy;
    }
    if (filterName == "hltMatchedVBFIsoTauTwoTight") {
	branchPt = inTree->hltMatchedVBFIsoTauTwoTight_pt;
	branchEta = inTree->hltMatchedVBFIsoTauTwoTight_eta;
	branchPhi = inTree->hltMatchedVBFIsoTauTwoTight_phi;
	branchEnergy = inTree->hltMatchedVBFIsoTauTwoTight_energy;
    }
    std::vector<TLorentzVector> objContainer;
    TLorentzVector tempObj;
    for (int iObj = 0; iObj < objNumber; ++iObj) {
	tempObj.SetPtEtaPhiE(branchPt->at(iObj),
			     branchEta->at(iObj),
			     branchPhi->at(iObj),
			     branchEnergy->at(iObj));
	objContainer.push_back(tempObj);
    }	
    return objContainer;
}

int main(int argc, char** argv)	{
    //myMap1 = new map<std::string, TH1F*>(); // i think this is for generalized naming/name fixing of different files
    //////////////////////////////////////
    // Input Arguments			//
    // 1) Input Path			//
    // 2) Output Path			//
    //////////////////////////////////////
    std::string in = *(argv + 1);
    std::string out = *(argv + 2);
    std::string inName = in;
    std::string outName = out;
    TFile *fIn = TFile::Open(inName.c_str());
    TTree* treePtr = (TTree*) fIn->Get("demo/vbf");
    trigger_tree* inTree = new trigger_tree (treePtr);

    // Open input file and make new output file, also declare necessary variables
    TTree *outTree = new TTree("outTree", "outTree");
    outTree->SetDirectory(0);

    // vars for AOD selection, which change depending on the trigger being studied
    float t1_pt_cut, t2_pt_cut;
    float j1_pt_cut, j2_pt_cut;
    float mjj_cut;

    std::string whichTrigger = *(argv + 3);
    std::string oldTrigString = "old";
    std::string newTrigString = "new";

    int triggerFlag = 2;
    if (whichTrigger.find(oldTrigString) == std::string::npos && 
	whichTrigger.find(newTrigString) == std::string::npos) {
	std::cout << "specify whether this is the new trigger or the old trigger with \"old\" or \"new\" as the 3rd argument" << std::endl;
	return 0; //prevents rest of code from running
    }
    // offline selection should be consistently 5 GeV above HLT thresholds
    if ( whichTrigger.find(oldTrigString) != std::string::npos){
	t1_pt_cut = 25;//80;//50;//25;
	t2_pt_cut = 25;//40;//25;
	j1_pt_cut = 120;
	j2_pt_cut = 45;
	mjj_cut = 700;
	std::cout << "trigger: " << oldTrigString << std::endl;
	triggerFlag = 0;
    }
    if ( whichTrigger.find(newTrigString) != std::string::npos){
	t1_pt_cut = 50;//80;//50;
	t2_pt_cut = 25;//40;//25;
	j1_pt_cut = 45;//120;//45;
	j2_pt_cut = 45;
	mjj_cut = 550;//700;//550;
	std::cout << "trigger: " << newTrigString << std::endl;
	triggerFlag = 1;
    }

    float minimal_tau_pt_cut = 20;
    float minimal_jet_pt_cut = 35;

    // hlt vars
    int vecSizeHpsTau;
    int vecSizeVBFOne;
    int vecSizeVBFTwo;
    int vecSizeVBFIsoTauTwo;
    int vecSizeHpsTau50;
    
    float j1_pt, j1_eta, j1_phi, j1_energy; 
    float j2_pt, j2_eta, j2_phi, j2_energy; 
    float mjj;

    float t1_pt, t1_eta, t1_phi, t1_energy;
    float t2_pt, t2_eta, t2_phi, t2_energy;
   
    // AOD vars 
    int vecSizeAODJet;
    int vecSizeAODTau;

    // A is for AOD
    float j1_pt_A, j1_eta_A, j1_phi_A, j1_energy_A; 
    float j2_pt_A, j2_eta_A, j2_phi_A, j2_energy_A; 
    float mjj_A;

    float t1_pt_A, t1_eta_A, t1_phi_A, t1_energy_A;
    float t2_pt_A, t2_eta_A, t2_phi_A, t2_energy_A;

    int deepTauVSjet, deepTauVSmu, deepTauVSele;
    int jetID;

    // vars for matching
    float dRj1, dRj2, dRt1, dRt2;

    std::vector<TLorentzVector> tauCandidates, jetCandidates;
    std::vector<TLorentzVector> tauTempCandidates, jetTempCandidates;
    std::vector<TLorentzVector> triggerTauCandidates, triggerJetCandidates;
    std::vector<TLorentzVector> triggerJetTempCandidates;

    std::vector<float> mjjCandidates;
    std::vector<std::pair<int,int>> jetMjjPairs;

    float mjjCandidatePair;
    std::vector<std::pair<int,int>> jetCandsLocs; // jet candidate locations

    // offline filter eff cutflow flag vars
    int passL1Old;
    int passhltHpsDoublePFTau20Old;
    int passhltHpsDoublePFTauTightOld;
    int passhltHpsDoublePFTauAgainstMuonTightOld;
    int passhltMatchedVBFTwoTight;
    int passhltMatchedVBFOneTight;

    int passL1New;
    int passhltHpsDoublePFTau20New;
    int passhltHpsDoublePFTauTightNew;
    int passhltHpsDoublePFTauAgainstMuonTightNew;
    int passhltHpsPFTau50Tight;
    int passhltMatchedVBFIsoTauTwoTight;

    // normal offline flag vars
    // delete these when you have time
    // basic or "preselection" should never be used as it has no physical meaning.
    // this is kind of like tying your shoes together from an analysis standpoint
    int passBase;
    int passBaseAndOldTrig;
    int passBaseOldTrigAndMatchedTaus;
    int passBaseOldTrigAndMatchedJets;
    int passBaseOldTrigAndMatchedBoth;
    int passBaseAndNewTrig;
    int passBaseNewTrigAndMatchedTaus;
    int passBaseNewTrigAndMatchedJets;
    int passBaseNewTrigAndMatchedBoth;

    int passSel;
    int passOldTrig;
    int passNewTrig;
    int passSelAndOldTrig;
    int passSelAndNewTrig;
    int matchedTaus;
    int matchedJets;
    int matchedBoth;
    int passSelOldTrigAndMatchedTaus;
    int passSelOldTrigAndMatchedJets;
    int passSelOldTrigAndMatchedBoth;
    int passSelNewTrigAndMatchedTaus;
    int passSelNewTrigAndMatchedJets;
    int passSelNewTrigAndMatchedBoth;

    int overlapped;
   
    int nEvents, runNumber, lumiBlock, eventNumberID;
 
    // filled data branches
    //
    outTree->Branch("nEvents", &nEvents);
    outTree->Branch("runNumber", &runNumber);
    outTree->Branch("lumiBlock", &lumiBlock);
    outTree->Branch("eventNumberID", &eventNumberID);
    // hlt vars
    outTree->Branch("j1_pt", &j1_pt);
    outTree->Branch("j1_eta", &j1_eta);
    outTree->Branch("j1_phi", &j1_phi);
    outTree->Branch("j2_pt", &j2_pt);
    outTree->Branch("j2_eta", &j2_eta);
    outTree->Branch("j2_phi", &j2_phi);
    outTree->Branch("mjj", &mjj);
    outTree->Branch("t1_pt", &t1_pt);
    outTree->Branch("t1_eta", &t1_eta);
    outTree->Branch("t1_phi", &t1_phi);
    outTree->Branch("t2_pt", &t2_pt);
    outTree->Branch("t2_eta", &t2_eta);
    outTree->Branch("t2_phi", &t2_phi);
    // AOD vars
    outTree->Branch("j1_pt_A", &j1_pt_A);
    outTree->Branch("j1_eta_A", &j1_eta_A);
    outTree->Branch("j1_phi_A", &j1_phi_A);
    outTree->Branch("j2_pt_A", &j2_pt_A);
    outTree->Branch("j2_eta_A", &j2_eta_A);
    outTree->Branch("j2_phi_A", &j2_phi_A);
    outTree->Branch("mjj_A", &mjj_A);
    outTree->Branch("t1_pt_A", &t1_pt_A);
    outTree->Branch("t1_eta_A", &t1_eta_A);
    outTree->Branch("t1_phi_A", &t1_phi_A);
    outTree->Branch("t2_pt_A", &t2_pt_A);
    outTree->Branch("t2_eta_A", &t2_eta_A);
    outTree->Branch("t2_phi_A", &t2_phi_A);
    outTree->Branch("deepTauVSjet", &deepTauVSjet);
    outTree->Branch("deepTauVSmu", &deepTauVSmu);
    outTree->Branch("deepTauVSele", &deepTauVSele);
    // matched vars
    outTree->Branch("dRj1", &dRj1);
    outTree->Branch("dRj2", &dRj2);
    outTree->Branch("dRt1", &dRt1);
    outTree->Branch("dRt2", &dRt2);
    outTree->Branch("matchedTaus", &matchedTaus);
    outTree->Branch("matchedJets", &matchedJets);
    outTree->Branch("matchedBoth", &matchedBoth);
    // offline filter eff cutflow vars
    // path for old trigger
    outTree->Branch("passL1Old", &passL1Old);
    outTree->Branch("passhltHpsDoublePFTau20Old", &passhltHpsDoublePFTau20Old);
    outTree->Branch("passhltHpsDoublePFTauTightOld", &passhltHpsDoublePFTauTightOld);
    outTree->Branch("passhltHpsDoublePFTauAgainstMuonTightOld", &passhltHpsDoublePFTauAgainstMuonTightOld);
    outTree->Branch("passhltMatchedVBFTwoTight", &passhltMatchedVBFTwoTight);
    outTree->Branch("passhltMatchedVBFOneTight", &passhltMatchedVBFOneTight);
    // path for new trigger
    outTree->Branch("passL1New", &passL1New);
    outTree->Branch("passhltHpsDoublePFTau20New", &passhltHpsDoublePFTau20New);
    outTree->Branch("passhltHpsDoublePFTauTightNew", &passhltHpsDoublePFTauTightNew);
    outTree->Branch("passhltHpsDoublePFTauAgainstMuonTightNew", &passhltHpsDoublePFTauAgainstMuonTightNew);
    outTree->Branch("passhltHpsPFTau50Tight", &passhltHpsPFTau50Tight);
    outTree->Branch("passhltMatchedVBFIsoTauTwoTight", &passhltMatchedVBFIsoTauTwoTight);

    // flag vars
    outTree->Branch("passBase", &passBase);
    outTree->Branch("passBaseAndOldTrig", &passBaseAndOldTrig);
    outTree->Branch("passBaseOldTrigAndMatchedTaus", &passBaseOldTrigAndMatchedTaus);
    outTree->Branch("passBaseOldTrigAndMatchedJets", &passBaseOldTrigAndMatchedJets);
    outTree->Branch("passBaseOldTrigAndMatchedBoth", &passBaseOldTrigAndMatchedBoth);
    outTree->Branch("passBaseAndNewTrig", &passBaseAndNewTrig);
    outTree->Branch("passBaseNewTrigAndMatchedTaus", &passBaseNewTrigAndMatchedTaus);
    outTree->Branch("passBaseNewTrigAndMatchedJets", &passBaseNewTrigAndMatchedJets);
    outTree->Branch("passBaseNewTrigAndMatchedBoth", &passBaseNewTrigAndMatchedBoth);
    outTree->Branch("passSel", &passSel);
    outTree->Branch("passOldTrig", &passOldTrig);
    outTree->Branch("passNewTrig", &passNewTrig);
    outTree->Branch("passSelAndOldTrig", &passSelAndOldTrig);
    outTree->Branch("passSelAndNewTrig", &passSelAndNewTrig);
    outTree->Branch("passSelOldTrigAndMatchedTaus", &passSelOldTrigAndMatchedTaus);
    outTree->Branch("passSelOldTrigAndMatchedJets", &passSelOldTrigAndMatchedJets);
    outTree->Branch("passSelOldTrigAndMatchedBoth", &passSelOldTrigAndMatchedBoth);
    outTree->Branch("passSelNewTrigAndMatchedTaus", &passSelNewTrigAndMatchedTaus);
    outTree->Branch("passSelNewTrigAndMatchedJets", &passSelNewTrigAndMatchedJets);
    outTree->Branch("passSelNewTrigAndMatchedBoth", &passSelNewTrigAndMatchedBoth);

    TH1F *min_cutflow = new TH1F("","",5,0,5);
    TH1F *sel_cutflow = new TH1F("","",7,0,7);

    //int sameTauPassSel = 0; 

    int numMatchedJets = 0;
    int numMatchedTaus = 0;
    int numMatchedBoth = 0;

    int numPassSel = 0;
    int numPassSelAndOldTrig = 0;
    int numPassSelAndNewTrig = 0;
    int numPassSelAndOR = 0;
    int passSelL1JetL1Tau = 0;
    int matchedTwiceL1OldDitau = 0;
    int passOldAndNewL1 = 0;
    int matchedTwiceL1OldNew = 0;

    int viableBeforeRmvOl = 0;
    int viableAfterRmvOl = 0;
    int viableAfterMjj = 0;
    int jetsMatchedBeforeRmvOl = 0;  
    int tauMatchedBeforeRmvOl = 0;
    int objsMatchedBeforeRmvOl = 0;
    int bothJetsMatchedAfterRmvOl = 0;
    int oneJetMatchedAfterRmvOl = 0;

    // Event Loop
    // for-loop of fewer events is useful to test code without heavy I/O to terminal from cout statements
    for (int iEntry = 0; iEntry < 60001; ++iEntry) {
    //for (int iEntry = 0; iEntry < inTree->GetEntries(); ++iEntry) {
	inTree->GetEntry(iEntry);
	if (iEntry % 10000 == 0) std::cout << std::to_string(iEntry) << std::endl;

	nEvents = inTree->nEvents;
	runNumber = inTree->runNumber;
	lumiBlock = inTree->lumiBlock;
	eventNumberID = inTree->eventNumberID;

	//--------------------initialize all flags to zero, clear vectors-------------------------//

	dRj1 = 999;
	dRj2 = 999;
	dRt1 = 999;
	dRt2 = 999;	
	
	// offline trigger filter cutflow efficiency flags	
	// old trigger path
	passL1Old = 0;
	passhltHpsDoublePFTau20Old = 0;
        passhltHpsDoublePFTauTightOld = 0;
	passhltHpsDoublePFTauAgainstMuonTightOld = 0;
    	passhltMatchedVBFTwoTight = 0;
 	passhltMatchedVBFOneTight = 0;
	// new trigger path
	passL1New = 0;
	passhltHpsDoublePFTau20New = 0;
	passhltHpsDoublePFTauTightNew = 0;
	passhltHpsDoublePFTauAgainstMuonTightNew = 0;
	passhltHpsPFTau50Tight = 0;
	passhltMatchedVBFIsoTauTwoTight = 0; 
	
	// base selection flags (usually not checked anymore, "minimal" cuts are arbitrary so they're not physically meaningful)
	passBase = 0;
	passBaseAndOldTrig = 0;
	passBaseOldTrigAndMatchedTaus = 0;	
	passBaseOldTrigAndMatchedJets = 0;	
	passBaseOldTrigAndMatchedBoth = 0;	
	passBaseAndNewTrig = 0;
	passBaseNewTrigAndMatchedTaus = 0;	
	passBaseNewTrigAndMatchedJets = 0;	
	passBaseNewTrigAndMatchedBoth = 0;	

	// full selection + trigger firing + matching flags
	passSel = 0;
	passOldTrig = 0;
	passNewTrig = 0;
	passSelAndOldTrig = 0;
	passSelAndNewTrig = 0;
	matchedTaus = 0;
	matchedJets = 0;
	matchedBoth = 0;
	passSelOldTrigAndMatchedTaus = 0;
	passSelOldTrigAndMatchedJets = 0;
	passSelOldTrigAndMatchedBoth = 0;
	passSelNewTrigAndMatchedTaus = 0;
	passSelNewTrigAndMatchedJets = 0;
	passSelNewTrigAndMatchedBoth = 0;

	overlapped = 0;

	tauCandidates.clear();	
	jetCandidates.clear();

	triggerTauCandidates.clear();
	triggerJetCandidates.clear();


	//---------------------apply minimal selection------------------------------//
	min_cutflow->Fill(0.0,1.0); // fill cutflow before any selection

	vecSizeAODTau = inTree->tauPt->size(); // number of taus in event
	vecSizeAODJet = inTree->jetPt->size(); // number of jets in event
	//minimal selection common to both triggers//
	// check the number of objects in the event, need at least two of each
	if (vecSizeAODTau < 2) continue;
	min_cutflow->Fill(1.0,1.0);
	if (vecSizeAODJet < 2) continue;
	min_cutflow->Fill(2.0,1.0); // fill cutflow with events that have 2 taus and 2 jets
	// check kinematics and ID of tau objects, store good taus
	for (int iTau = 0; iTau < vecSizeAODTau; ++iTau){

	    deepTauVSjet = inTree->tauByMediumDeepTau2017v2p1VSjet->at(iTau) > 0.5;
	    deepTauVSmu = inTree->tauByVLooseDeepTau2017v2p1VSmu->at(iTau) > 0.5;
            deepTauVSele = inTree->tauByVVVLooseDeepTau2017v2p1VSe->at(iTau) > 0.5;
	
	    if (!deepTauVSjet || !deepTauVSmu || !deepTauVSele) continue;

	    if ( inTree->tauPt->at(iTau) < minimal_tau_pt_cut ) continue;
	    if ( inTree->tauEta->at(iTau) > 2.1 ) continue;
	    TLorentzVector tauCand;
	    tauCand.SetPtEtaPhiE(inTree->tauPt->at(iTau),
				     inTree->tauEta->at(iTau), 
				     inTree->tauPhi->at(iTau), 
				     inTree->tauEnergy->at(iTau));

	    tauCandidates.push_back(tauCand);
	}


	// continues inside for-loops don't skip the events, so you need to check the size of
	// the container you skipped adding events to and then impose a condition on that instead
	// check that we have at least 2 good taus to work with
	if (tauCandidates.size() < 2) continue;

	// as keti proposed, take first two AOD taus that aren't overlapped
	// tauCandidates are already ordered by pt (this was checked with simple cout statements)
	TLorentzVector aodTau1, aodTau2;
	aodTau1.SetPtEtaPhiE(tauCandidates.at(0).Pt(), tauCandidates.at(0).Eta(), tauCandidates.at(0).Phi(), tauCandidates.at(0).Energy());
	for (int iTau = 1; iTau < tauCandidates.size(); ++iTau){
	    aodTau2.SetPtEtaPhiE(tauCandidates.at(iTau).Pt(),
				 tauCandidates.at(iTau).Eta(),
				 tauCandidates.at(iTau).Phi(),
				 tauCandidates.at(iTau).Energy());
	    if (aodTau1.DeltaR(aodTau2) > 0.5) break; // if taus are not overlapped, leave the for loop
	}
	// check that the tau didn't make it all the way through the loop without breaking
	// I think this is unlikely but it's good to be redundant
	if (aodTau1.DeltaR(aodTau2) < 0.5) continue; 

	min_cutflow->Fill(3.0,1.0); // fill cutflow with events that have 2 or more good taus
	sel_cutflow->Fill(0.0,1.0); // start of smaller cutflow graph (keep two just for scaling purposes)

	// check kinematics and ID of jet objects, store good jets
	for (int iJet = 0; iJet < vecSizeAODJet; ++iJet){

	    if (inTree->jetID->at(iJet) < 6) continue; // jetID is 2 if it passes loose, and 6 if it passes loose and tight

	    if (inTree->jetPt->at(iJet) < minimal_jet_pt_cut) continue;
	    if (fabs(inTree->jetEta->at(iJet) > 4.7)) continue;
	    TLorentzVector jetCand;
	    jetCand.SetPtEtaPhiE(inTree->jetPt->at(iJet), 
				     inTree->jetEta->at(iJet), 
				     inTree->jetPhi->at(iJet), 
				     inTree->jetEn->at(iJet));
	    // if a jetCandidate looks like it could be either tau we already selected, don't store it
	    bool jetCandIsTau = false;
	    if (aodTau1.DeltaR(jetCand) < 0.5) jetCandIsTau = true;
	    if (aodTau2.DeltaR(jetCand) < 0.5) jetCandIsTau = true;

	    if (!jetCandIsTau) jetCandidates.push_back(jetCand);
	}
	// check that we have at least two good jets
	if (jetCandidates.size() < 2) continue;

	// fill aod jets with pair of jets that produced the largest mjj value
	// from cout statements, aodJet1 was verified to be leading jet
	TLorentzVector aodJet1, aodJet2;
        std::tie(aodJet1, aodJet2) = highestMjjPair(jetCandidates);

	// calculate mjj of AOD jets
	mjj_A = (aodJet1 + aodJet2).M();
	if (mjj_A == 0) continue;

	min_cutflow->Fill(4.0,1.0);
	sel_cutflow->Fill(1.0,1.0);

	passBase = 1;

        std::vector<TLorentzVector> aodObjs;
	aodObjs.push_back(aodJet1);
	aodObjs.push_back(aodJet2);
	aodObjs.push_back(aodTau1);
	aodObjs.push_back(aodTau2);

	//-----------------------tighter selection guided by trigger specific cutoffs---------------//


	passSel = 1;

	if (aodTau1.Pt() < t2_pt_cut || aodTau2.Pt() < t2_pt_cut) passSel = 0; //continue;
	//else {sel_cutflow->Fill(5.0,1.0);}
	sel_cutflow->Fill(2.0,1.0);
	
	if (aodTau1.Pt() < t1_pt_cut) passSel = 0; //continue;
	//else {sel_cutflow->Fill(6.0,1.0);}
	sel_cutflow->Fill(3.0,1.0);

	if (aodJet1.Pt() < j2_pt_cut || aodJet2.Pt() < j2_pt_cut) passSel = 0; //continue;
	//else {sel_cutflow->Fill(7.0,1.0);}
	sel_cutflow->Fill(4.0,1.0);

	if (aodJet1.Pt() < j1_pt_cut) passSel = 0; //continue;
	//else {sel_cutflow->Fill(8.0,1.0);}
	sel_cutflow->Fill(5.0,1.0);

	if (mjj_A < mjj_cut) passSel = 0; //continue;
	//else {sel_cutflow->Fill(9.0,1.0);}
	sel_cutflow->Fill(6.0,1.0);

	if (passSel) numPassSel += 1;

	//-----------------------try to match AOD and HLT objects-----------------------------------//
	
	// get number of objects in tau and jet trigger filters
	vecSizeHpsTau = inTree->hltHpsDoublePFTauTight_pt->size(); // at least two taus > 20 GeV filter, common to both
	vecSizeVBFTwo = inTree->hltMatchedVBFTwoTight_pt->size();  // at least two jets > 45 GeV filter, old trigger
	vecSizeVBFOne = inTree->hltMatchedVBFOneTight_pt->size();  // one jet > 115 GeV filter, old trigger
	vecSizeVBFIsoTauTwo = inTree->hltMatchedVBFIsoTauTwoTight_pt->size(); // at least two jets > 45 GeV filter and iso tau present, new trigger
	vecSizeHpsTau50 = inTree->hltHpsPFTau50Tight_pt->size(); // at least one tau > 50 GeV filter, new trigger

	TLorentzVector trigTau1, trigTau2, trigJet1, trigJet2;//, aodJet1, aodJet2;
	if (vecSizeHpsTau >= 2 && ((vecSizeVBFTwo >= 2 && vecSizeVBFOne >= 1 && triggerFlag == 0) 
				|| (vecSizeVBFIsoTauTwo >= 2 && vecSizeHpsTau50 >= 1 && triggerFlag == 1))  ){
	    // fill trigger tau candidates for either trigger from 20 GeV tau filter
	    triggerTauCandidates = hltFillWithCands(inTree, "hltHpsDoublePFTauTight", vecSizeHpsTau);
	    /***
	    for (int iTriggerTau = 0; iTriggerTau < vecSizeHpsTau; ++iTriggerTau){
		TLorentzVector triggerTauCand;
		triggerTauCand.SetPtEtaPhiE(inTree->hltHpsDoublePFTauTight_pt->at(iTriggerTau),
					    inTree->hltHpsDoublePFTauTight_eta->at(iTriggerTau),
					    inTree->hltHpsDoublePFTauTight_phi->at(iTriggerTau),
					    inTree->hltHpsDoublePFTauTight_energy->at(iTriggerTau));
		triggerTauCandidates.push_back(triggerTauCand);
	    }
***/
	    TLorentzVector triggerJetCand;
	    // fill trigger jet candidates for old trigger
	    if (vecSizeVBFTwo >= 2 && vecSizeVBFOne >= 1 && triggerFlag == 0) {
		triggerJetCandidates = hltFillWithCands(inTree, "hltMatchedVBFTwoTight", vecSizeVBFTwo);
/***
		for (int iTriggerJet = 0; iTriggerJet < vecSizeVBFTwo; ++iTriggerJet){
		    triggerJetCand.SetPtEtaPhiE(inTree->hltMatchedVBFTwoTight_pt->at(iTriggerJet),
						inTree->hltMatchedVBFTwoTight_eta->at(iTriggerJet),
	    					inTree->hltMatchedVBFTwoTight_phi->at(iTriggerJet),
	    					inTree->hltMatchedVBFTwoTight_energy->at(iTriggerJet));
		    triggerJetCandidates.push_back(triggerJetCand);
		}
***/
	    }

	    // fill trigger jet candidates for new trigger
	    if (vecSizeVBFIsoTauTwo >= 2 && vecSizeHpsTau50 >= 1 && triggerFlag == 1) {

		triggerJetCandidates = hltFillWithCands(inTree, "hltMatchedVBFIsoTauTwoTight", vecSizeVBFIsoTauTwo);
/***
		for (int iTriggerJet = 0; iTriggerJet < vecSizeVBFIsoTauTwo; ++iTriggerJet){
		    triggerJetCand.SetPtEtaPhiE(inTree->hltMatchedVBFIsoTauTwoTight_pt->at(iTriggerJet),
						inTree->hltMatchedVBFIsoTauTwoTight_eta->at(iTriggerJet),
	    					inTree->hltMatchedVBFIsoTauTwoTight_phi->at(iTriggerJet),
	    					inTree->hltMatchedVBFIsoTauTwoTight_energy->at(iTriggerJet));
		    triggerJetCandidates.push_back(triggerJetCand);
		}
***/
	    }

	    // match AOD and HLT jets and taus

	    // tie is a handy method for assigning tuple output
            std::tie(trigJet1, trigJet2) = matchTwoObjs(triggerJetCandidates, aodJet1, aodJet2);
            dRj1 = trigJet1.DeltaR(aodJet1);
            dRj2 = trigJet2.DeltaR(aodJet2);


	    std::tie(trigTau1, trigTau2) = matchTwoObjs(triggerTauCandidates, aodTau1, aodTau2);
	    dRt1 = trigTau1.DeltaR(aodTau1);
	    dRt2 = trigTau2.DeltaR(aodTau2);

	    mjj = (trigJet1 + trigJet2).M();


	    // check that same type objects are not overlapped
	    if (trigTau1.DeltaR(trigTau2) < 0.5 || trigJet1.DeltaR(trigJet2) < 0.5 ) overlapped = 1;

	    // check that different objecs are not overlapped
	    if (trigTau1.DeltaR(trigJet1) < 0.5 || trigTau1.DeltaR(trigJet2) < 0.5 ||
		trigTau2.DeltaR(trigJet1) < 0.5 || trigTau2.DeltaR(trigJet2) < 0.5) overlapped = 1;
	}

	//------------------------------fill flags and output tree-----------------------------------//
	// passSel 
	// passBase alredy defined near start

	passOldTrig = inTree->passOldTrigTight->at(0);
	passNewTrig = inTree->passNewTrigTight->at(0);

	// filling offline selection && pass trigger flags
	if (passSel && passOldTrig ) {passSelAndOldTrig = 1; numPassSelAndOldTrig += 1;} // && triggerFlag == 0 removed
	if (passSel && passNewTrig ) {passSelAndNewTrig = 1; numPassSelAndNewTrig += 1;} // && triggerFlag == 1 removed


	// if all the dRs are less than 0.5, then we've matched AOD to reco HLT
	if (dRt1 < 0.5 && dRt2 < 0.5 && !overlapped) {matchedTaus = 1; numMatchedTaus += 1;}
	if (dRj1 < 0.5 && dRj2 < 0.5 && !overlapped) {matchedJets = 1; numMatchedJets += 1;}
	if (matchedTaus && matchedJets) {matchedBoth = 1; numMatchedBoth += 1;}

	if (matchedTaus && passSelAndOldTrig) passSelOldTrigAndMatchedTaus = 1;
	if (matchedJets && passSelAndOldTrig) passSelOldTrigAndMatchedJets = 1;
	if (matchedBoth && passSelAndOldTrig) passSelOldTrigAndMatchedBoth = 1;

	if (matchedTaus && passSelAndNewTrig) passSelNewTrigAndMatchedTaus = 1;
	if (matchedJets && passSelAndNewTrig) passSelNewTrigAndMatchedJets = 1;
	if (matchedBoth && passSelAndNewTrig) passSelNewTrigAndMatchedBoth = 1;
/***
	// OR pass
	if (passSel && (passOldTrig || passNewTrig) && (triggerFlag == 0 || triggerFlag == 1)) numPassSelAndOR += 1;

	// -----------------------------------------L1 object investigation -----------------------------//
	// passes offline selection, passes old L1, passes new L1
	if (passSel && inTree->hltL1VBFDiJetOR_pt->size() >= 2 && \
		(inTree->hltL1VBFDiJetIsoTau_tauPt->size() >=1 && inTree->hltL1VBFDiJetIsoTau_jetPt->size() >= 2)){
	    passOldAndNewL1 += 1;
    	    // get L1Jets from old VBF trigger
    	    // if their pT is < 35 don't store them bc they wouldn't pass new VBF L1
    	    std::vector<TLorentzVector> passL1JetCands;
    	    TLorentzVector passL1Jet;
    	    for (int iOldJet = 0; iOldJet < inTree->hltL1VBFDiJetOR_pt->size(); ++iOldJet){
		passL1Jet.SetPtEtaPhiE(inTree->hltL1VBFDiJetOR_pt->at(iOldJet),
    			inTree->hltL1VBFDiJetOR_eta->at(iOldJet),
    			inTree->hltL1VBFDiJetOR_phi->at(iOldJet),
    			inTree->hltL1VBFDiJetOR_energy->at(iOldJet));
		if (passL1Jet.Pt() > 35) passL1JetCands.push_back(passL1Jet);
    	    }

    	    // get L1Taus from new VBF trigger
    	    // if their pT is < 45 don't store them bc they wouldn't pass new VBF L1
    	    std::vector<TLorentzVector> passL1TauCands;
    	    TLorentzVector passL1Tau;
    	    for (int iNewTau = 0; iNewTau < inTree->hltL1VBFDiJetIsoTau_tauPt->size(); ++iNewTau){
    		passL1Tau.SetPtEtaPhiE(inTree->hltL1VBFDiJetIsoTau_tauPt->at(iNewTau),
    				inTree->hltL1VBFDiJetIsoTau_tauEta->at(iNewTau),
    				inTree->hltL1VBFDiJetIsoTau_tauPhi->at(iNewTau),
    				inTree->hltL1VBFDiJetIsoTau_tauEnergy->at(iNewTau));
		if (passL1Tau.Pt() > 45) passL1TauCands.push_back(passL1Tau);
	    }
	    if (AODObjInContainer(passL1JetCands, aodObjs, 0) && AODObjInContainer(passL1TauCands, aodObjs, 0)) matchedTwiceL1OldNew += 1;

	    //dumpEventKinemInfo(iEntry, "passed old and new L1", aodObjs, passL1JetCands, passL1TauCands);

	}
	
	// passes offline selection, passes old L1, doesn't pass new L1
	int jetNum, tauNum;
	if (passSel && inTree->hltL1VBFDiJetOR_pt->size() >= 2 && inTree->hltL1sDoubleTauBigOR_pt->size() >= 2 && //passOldTrig &&
		(inTree->hltL1VBFDiJetIsoTau_tauPt->size() < 1 || inTree->hltL1VBFDiJetIsoTau_jetPt->size() < 2)) { 

	    jetNum = inTree->hltL1VBFDiJetOR_pt->size(); 	// # jets from old trigger
	    tauNum = inTree->hltL1sDoubleTauBigOR_pt->size(); 	// # taus from ditau trigger

	    if (jetNum >= 2 && tauNum >= 1) { // only need one tau from ditau trigger, except it won't fire unless there's at least two

		passSelL1JetL1Tau += 1;

		// get L1Jets from old VBF trigger
		// if their pT is < 35 don't store them bc they wouldn't pass new VBF L1
		std::vector<TLorentzVector> L1JetCands;
		TLorentzVector L1Jet;
		for (int iOldJet = 0; iOldJet < jetNum; ++iOldJet){
		    L1Jet.SetPtEtaPhiE(inTree->hltL1VBFDiJetOR_pt->at(iOldJet),
				inTree->hltL1VBFDiJetOR_eta->at(iOldJet),
				inTree->hltL1VBFDiJetOR_phi->at(iOldJet),
				inTree->hltL1VBFDiJetOR_energy->at(iOldJet));
		    if (L1Jet.Pt() > 35) L1JetCands.push_back(L1Jet); 
		}

		// get L1Taus from ditau trigger
		// if their pT is < 45 don't store them bc they wouldn't pass new VBF L1
		std::vector<TLorentzVector> L1TauCands;
		TLorentzVector L1Tau;
		for (int iNewTau = 0; iNewTau < tauNum; ++iNewTau){
		    L1Tau.SetPtEtaPhiE(inTree->hltL1sDoubleTauBigOR_pt->at(iNewTau),
				inTree->hltL1sDoubleTauBigOR_eta->at(iNewTau),
				inTree->hltL1sDoubleTauBigOR_phi->at(iNewTau),
				inTree->hltL1sDoubleTauBigOR_energy->at(iNewTau));
		    if (L1Tau.Pt() > 45) L1TauCands.push_back(L1Tau); 
		}


		// if we have at least 2 jets and at least 1 tau passing new VBF L1, event may be viable 
		if (L1JetCands.size() >= 2 && L1TauCands.size() >= 1) {
 		    viableBeforeRmvOl += 1;

		    // see if event obj matches AOD before overlap removal

                    TLorentzVector jetMatch1, jetMatch2;
                    double dRAODJet1, dRAODJet2;
		    // tie is a handy method for assigning tuple output
                    std::tie(jetMatch1, jetMatch2) = matchTwoObjs(L1JetCands, aodJet1, aodJet2);
                    dRAODJet1 = jetMatch1.DeltaR(aodJet1);
                    dRAODJet2 = jetMatch2.DeltaR(aodJet2);

		    if (dRAODJet1 < 0.5 && dRAODJet2 < 0.5) jetsMatchedBeforeRmvOl += 1;

		    TLorentzVector tauMatch;
		    int tauMatchIndex = -1;
		    double dRAODTau1;
		    double dRAODTau2;		
		    tauMatchIndex = simpleMatching(L1TauCands, aodTau1);
		    tauMatch = L1TauCands.at(tauMatchIndex);
		    dRAODTau1 = tauMatch.DeltaR(aodTau1);
		    tauMatchIndex = simpleMatching(L1TauCands, aodTau2);
		    tauMatch = L1TauCands.at(tauMatchIndex);
		    dRAODTau2 = tauMatch.DeltaR(aodTau2);
		    if (dRAODTau1 < 0.5 || dRAODTau2 < 0.5) tauMatchedBeforeRmvOl += 1; 

		    if (dRAODJet1 < 0.5 && dRAODJet2 < 0.5 && (dRAODTau1 < 0.5 || dRAODTau2 < 0.5)) objsMatchedBeforeRmvOl += 1;
		}

		if (AODObjInContainer(L1JetCands, aodObjs, 0) && AODObjInContainer(L1TauCands, aodObjs, 0)) matchedTwiceL1OldDitau += 1;

		// cross-clean L1 jets and taus
		// taus get priority, so if an obj from L1 jets is overlapped with an obj from L1 taus
		// then don't store that L1 jet to the new cross-cleaned container of L1 jets
		std::vector<TLorentzVector> crossCleanedL1Jets;
		for (int iJetCand = 0; iJetCand < L1JetCands.size(); ++iJetCand){
		    bool clean = true;
		    for (int iTauCand = 0; iTauCand < L1TauCands.size(); ++iTauCand){
			if (L1TauCands.at(iTauCand).DeltaR(L1JetCands.at(iJetCand)) < 0.5) {//plot dR
			    clean = false;
			}
		    }
		    if (clean) crossCleanedL1Jets.push_back(L1JetCands.at(iJetCand));
		}
				
		// if you have at least two jets in the cross-cleaned container, then the event is still viable
		// all that's left to check is the Mjj of the L1 cross-cleaned jets
		if (crossCleanedL1Jets.size() >= 2 && L1TauCands.size() >= 1) {

		    //dumpEventKinemInfo(iEntry, "cc jets", aodObjs, crossCleanedL1Jets, L1TauCands);

		    viableAfterRmvOl += 1;

		    // see if event obj matches AOD even after overlap removal
		    TLorentzVector cleanedJetMatch1, cleanedJetMatch2;
		    double dRCleanedJetAODJet1, dRCleanedJetAODJet2;
		    std::tie(cleanedJetMatch1, cleanedJetMatch2) = matchTwoObjs(crossCleanedL1Jets, aodJet1, aodJet2);
		    dRCleanedJetAODJet1 = cleanedJetMatch1.DeltaR(aodJet1);
		    dRCleanedJetAODJet2 = cleanedJetMatch2.DeltaR(aodJet2);

		    if (dRCleanedJetAODJet1 < 0.5 || dRCleanedJetAODJet2 < 0.5) oneJetMatchedAfterRmvOl += 1;
		    if (dRCleanedJetAODJet1 < 0.5 && dRCleanedJetAODJet2 < 0.5) bothJetsMatchedAfterRmvOl += 1;

		    TLorentzVector cleanedJet1, cleanedJet2;
        	    std::tie(cleanedJet1, cleanedJet2) = highestMjjPair(crossCleanedL1Jets);

		    // calculate mjj of two highest mjj cleaned jets
		    float temp_mjj = (cleanedJet1 + cleanedJet2).M();
		    if (temp_mjj > 450) viableAfterMjj +=1;//continue;

		}
		else{continue;}//dumpEventKinemInfo(iEntry, "failed after overlap removal", aodObjs, L1JetCands, L1TauCands);
	    }
	}
***/
	// old trigger filter cutflow eff flags
	if (passSel && triggerFlag == 0 && inTree->hltL1VBFDiJetOR_pt->size() >= 2) {
	    passL1Old = inTree->passhltL1VBFDiJetOR;
	}

	if (passL1Old && inTree->hltHpsDoublePFTau20_pt->size() >= 2) {
	    passhltHpsDoublePFTau20Old = inTree->passhltHpsDoublePFTau20;
	}

	if (passhltHpsDoublePFTau20Old && inTree->hltHpsDoublePFTauTight_pt->size() >= 2) {
	    passhltHpsDoublePFTauTightOld = inTree->passhltHpsDoublePFTauTight; 
	}

	if (passhltHpsDoublePFTauTightOld && inTree->hltHpsDoublePFTauAgainstMuonTight_pt->size() >= 2) {
	    passhltHpsDoublePFTauAgainstMuonTightOld = inTree->passhltHpsDoublePFTauAgainstMuonTight;
	}

	if (passhltHpsDoublePFTauAgainstMuonTightOld && inTree->hltMatchedVBFTwoTight_pt->size() >= 2) {
	    passhltMatchedVBFTwoTight = inTree->passhltMatchedVBFTwoTight;
	}

	if (passhltMatchedVBFTwoTight && inTree->hltMatchedVBFOneTight_pt->size() >= 1) {
	    passhltMatchedVBFOneTight = inTree->passhltMatchedVBFOneTight;
	}

	// new trigger filter cutflow eff flags
	if (passSel && triggerFlag == 1 && inTree->hltL1VBFDiJetIsoTau_tauPt->size() >= 1
					&& inTree->hltL1VBFDiJetIsoTau_jetPt->size() >= 2) {
	    passL1New = inTree->passhltL1VBFDiJetIsoTau;
	}

	if (passL1New && inTree->hltHpsDoublePFTau20_pt->size() >= 2) {
	    passhltHpsDoublePFTau20New = inTree->passhltHpsDoublePFTau20;
	}

	if (passhltHpsDoublePFTau20New && inTree->hltHpsDoublePFTauTight_pt->size() >= 2) {
	    passhltHpsDoublePFTauTightNew = inTree->passhltHpsDoublePFTauTight;
	}

	if (passhltHpsDoublePFTauTightNew && inTree->hltHpsDoublePFTauAgainstMuonTight_pt->size() >= 2) {
	    passhltHpsDoublePFTauAgainstMuonTightNew = inTree->passhltHpsDoublePFTauAgainstMuonTight;
	}

	if (passhltHpsDoublePFTauAgainstMuonTightNew && inTree->hltHpsPFTau50Tight_pt->size() >= 1) {
	    passhltHpsPFTau50Tight = inTree->passhltHpsPFTau50Tight;
	}

	if (passhltHpsPFTau50Tight && inTree->hltMatchedVBFIsoTauTwoTight_pt->size() >= 2) {
	    passhltMatchedVBFIsoTauTwoTight = inTree->passhltMatchedVBFIsoTauTwoTight;
	}
	
        // fill kine branches with matched AOD
        if (passSel){
	    t1_pt_A = aodTau1.Pt();
	    t1_eta_A = aodTau1.Eta();
	    t1_phi_A = aodTau1.Phi();
	    t1_energy_A = aodTau1.Energy();
	    t2_pt_A = aodTau2.Pt();
	    t2_eta_A = aodTau2.Eta();
	    t2_phi_A = aodTau2.Phi();
	    t2_energy_A = aodTau2.Energy();

	    j1_pt_A = aodJet1.Pt();
	    j1_eta_A = aodJet1.Eta();
	    j1_eta_A = aodJet1.Phi();
	    j1_energy_A = aodJet1.Energy();
	    j2_pt_A = aodJet2.Pt();
	    j2_eta_A = aodJet2.Eta();
	    j2_eta_A = aodJet2.Phi();
	    j2_energy_A = aodJet2.Energy();
	}

        outTree->Fill();
    }// end event loop


    std::cout << numPassSel << '\t' << "Passed Sel." << std::endl << \
		"Sel (t1 pt, t2 pt, j1 pt, j2 pt, mjj): " << t1_pt_cut << '\t' << t2_pt_cut << '\t' << j1_pt_cut << '\t' << j2_pt_cut << '\t' << mjj_cut << std::endl << \
		numPassSelAndOldTrig << '\t' << "Passed Sel. and Old Trigger (ignore if not Old selection)" << std::endl << \
		numPassSelAndNewTrig << '\t' << "Passed Sel. and New Trigger (ignore if not New selection)" << std::endl << \
		std::endl;
/***
		numPassSelAndOR << '\t' << "Passed Sel. and OR (ignore if not OR selection)" << std::endl << \
		passOldAndNewL1 << '\t' << "Passed Sel., Passed Old VBF L1, Passed New VBF L1" << std::endl << \
		matchedTwiceL1OldNew << '\t' << "Number of Times Leading AOD Jet was Matched in Both L1 Jet and L1 Tau Containers" << std::endl << \
		passSelL1JetL1Tau << '\t' << "Passed Sel., Passed Old VBF L1, Passed Ditau L1, Failed New VBF L1" << std::endl << \
		matchedTwiceL1OldDitau << '\t' << "Number of Times Leading AOD Jet was Matched in Both L1 Jet and L1 Tau Containers" << std::endl << \
		"Below is applied to 2nd cateogry (Failed New VBF L1)" << std::endl << \
		viableBeforeRmvOl << '\t' << "Passed Double 35 Jet pT, 45 tau pT" << std::endl << \
		//jetsMatchedBeforeRmvOl << '\t' << "Two Jets Matched Before Overlap Removal" << std::endl << \
		//tauMatchedBeforeRmvOl << '\t' << "Tau Matched Before Overlap Removal" << std::endl << \
		//
		objsMatchedBeforeRmvOl << '\t' << "Two Jets and One Tau Matched Before Overlap Removal" << std::endl << \
		"Overlap Removal Performed" << std::endl << \
		viableAfterRmvOl << '\t' << "At Least Two Jets Remain After Overlap Removal" << std::endl << \
		oneJetMatchedAfterRmvOl << '\t' << "At Least One Jet is Matched After Overlap Removal" << std::endl << \
		bothJetsMatchedAfterRmvOl << '\t' << "Both Jets Matched After Overlap Removal" << std::endl << \
		viableAfterMjj << '\t' << "Dijet Pair Passing Mjj > 450 GeV" << std::endl;
***/
    std::cout << numMatchedJets << '\t' << "matched jets" << std::endl << \
		numMatchedTaus << '\t' << "matched taus" << std::endl << \
		numMatchedBoth << '\t' << "matched both" << std::endl;

    std::string outputFileName = outName;
    TFile *fOut = TFile::Open(outputFileName.c_str(),"RECREATE");
    fOut->cd();

    min_cutflow->SetName("MinCutflow");
    min_cutflow->Write();
    sel_cutflow->SetName("SelCutflow");
    sel_cutflow->Write();


    outTree->Write();
    fOut->Close();
    return 0;
}
