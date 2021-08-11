#include <vector>
#include <string>

#include "TLorentzVector.h"

// output an integer pointing to the location of the object in given container with lowest dR
// to given AOD object. Used by matchTwoObjs function
int simpleMatching(std::vector<TLorentzVector> trigContainer, TLorentzVector AODObj) {
    int bestObjIndex = -1;
    float dRObj = 999;
    float dRObj_ = 999;
    for (std::vector<TLorentzVector>::const_iterator iTrigObj = trigContainer.begin(); iTrigObj != trigContainer.end(); ++iTrigObj) {
    //for (int iTrigObj = 0; iTrigObj < trigContainer.size(); ++iTrigObj){
	dRObj_ = iTrigObj->DeltaR(AODObj);//aodObj.DeltaR(trigContainer.at(iTrigObj));
	if (dRObj_ < dRObj) {dRObj = dRObj_; bestObjIndex = (iTrigObj - trigContainer.begin());}
    }
    return bestObjIndex;
}

// output a tuple of TLorentzVectors that correspond to HLt objects matched to AOD objects
// using a given HLT object container and two given AOD objects
// tuple is used instead of pair because the output was easier to manage
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

// output a tuple of TLorentzVectors that correspond to the jet pair with
// the highest mjj of a given jet container
std::tuple<TLorentzVector, TLorentzVector> highestMassPair(std::vector<TLorentzVector> jetContainer, int firstContainerSize, int secondContainerSize = 0, int objSearchMode = 0) {
    // objSearchMode:
    // 0 - no exclusions applied
    // 1 - only 1 jet and 1 tau combinations are allowed
    // 2 - double tau combinations are excluded
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

// outputs a vector of objects from container one cross-cleaned wrt objects from container two
// names are jets and taus bc I don't think this will be used for any other purpose
std::vector<TLorentzVector> crossCleanJets(std::vector<TLorentzVector> jetObjs, std::vector<TLorentzVector> tauObjs) {
    std::vector<TLorentzVector> crossCleanedJets;
    for (int iJet = 0; iJet < jetObjs.size(); ++iJet) {
	bool clean = true;
	    for (int iTau = 0; iTau < tauObjs.size(); ++iTau) {
		if (jetObjs.at(iJet).DeltaR(tauObjs.at(iTau)) < 0.5) clean = false;
	    }
	if (clean) crossCleanedJets.push_back(jetObjs.at(iJet));
    }
    return crossCleanedJets;	
}

// outputs to terminal 2 AOD objects' information
void coutAODobjs(TLorentzVector AODobj1, TLorentzVector AODobj2) {
    std::cout << "obj #" << '\t' << "pt" << '\t' << "eta" << '\t' << "phi" << std::endl;
    std::cout << "1      " << std::setprecision(4) << AODobj1.Pt() << '\t' << AODobj1.Eta() << '\t' << AODobj1.Phi() << std::endl;
    std::cout << "2      " << std::setprecision(4) << AODobj2.Pt() << '\t' << AODobj2.Eta() << '\t' << AODobj2.Phi() << std::endl;
}

// outputs to terminal all object info in a container of TLorentzVectors,
// including dR with all AOD objects (2 jets and 2 taus)
void coutL1objs(std::vector<TLorentzVector> L1ObjContainer, std::vector<TLorentzVector> AODObjContainer) {
    // assume AODObjContainer is (aodJet1, aodJet2, aodTau1, aodTau2)
    std::cout << "obj #" << '\t' << "pt" << '\t' << "eta" << '\t' << "phi" <<\
    '\t' << "dR AODJet 1" << '\t' << "dR AODJet 2" << '\t' << "dR AODTau 1" << '\t' << "dR AODTau 2" << std::endl;
    for (std::vector<TLorentzVector>::const_iterator iObj = L1ObjContainer.begin(); iObj != L1ObjContainer.end(); ++iObj) {
	std::cout << (iObj - L1ObjContainer.begin()) << '\t' << std::setprecision(4) \
		  << iObj->Pt() << '\t' << iObj->Eta() << '\t' << iObj->Phi() << '\t' \
		  << iObj->DeltaR(AODObjContainer.at(0)) << '\t' << '\t' << iObj->DeltaR(AODObjContainer.at(1)) << '\t' << '\t' \
		  << iObj->DeltaR(AODObjContainer.at(2)) << '\t' << '\t' << iObj->DeltaR(AODObjContainer.at(3)) << std::endl;
    }
}

// outputs to terminal all kinem info at once of AOD objs and L1 objs using both functions above
void dumpEventKinemInfo(int iEntry, std::string label,
                        std::vector<TLorentzVector> AODObjs, std::vector<TLorentzVector> jets, std::vector<TLorentzVector> taus) {
    // assume AODObjs is (aodJet1, aodJet2, aodTau1, aodTau2)
    std::cout << "iEntry: " << iEntry << std::endl;
    std::cout << "-------------" << label << "--------------" << std::endl;
    std::cout << "aod jet info" << std::endl;
    coutAODobjs(AODObjs.at(0), AODObjs.at(1)); 
    std::cout << "aod tau info" << std::endl;
    coutAODobjs(AODObjs.at(2), AODObjs.at(3));

    std::cout << "jet info" << std::endl;
    std::cout << "jet size " << jets.size() << std::endl;
    coutL1objs(jets, AODObjs);

    std::cout << "tau info" << std::endl;
    std::cout << "tau size " << taus.size() << std::endl;
    coutL1objs(taus, AODObjs);

    std::cout << "-----------------------------------------" << std::endl;
}

// outputs a boolean variable if an AOD object is matched in a container of L1 objects
int objInContainer(std::vector<TLorentzVector> L1ObjContainer, TLorentzVector Obj) {
    int objInContainer = 0;
    for (std::vector<TLorentzVector>::const_iterator iObj = L1ObjContainer.begin(); iObj != L1ObjContainer.end(); ++iObj) {
	if (iObj->DeltaR(Obj) < 0.5) return objInContainer = 1;
    }
    return objInContainer;
}

// fills a std::vector<TLorentzVector> container using input tree and a string identifying the branches to use
// "optional" ptCut can be applied, set to zero if no cut is desired
// looking into a better way to implement this (switch-case statement won't work with strings)
std::vector<TLorentzVector> hltFillWithCands(trigger_tree* inTree, std::string filterName, int objNumber, int ptCut = 0) {
    std::vector<float>* branchPt;
    std::vector<float>* branchEta;
    std::vector<float>* branchPhi;
    std::vector<float>* branchEnergy;

    bool found = false;

    if (!found && filterName == "hltHpsDoublePFTauTight") {
	branchPt = inTree->hltHpsDoublePFTauTight_pt;
	branchEta = inTree->hltHpsDoublePFTauTight_eta;
	branchPhi = inTree->hltHpsDoublePFTauTight_phi;
	branchEnergy = inTree->hltHpsDoublePFTauTight_energy;
	found = true;
    }
    if (!found && filterName == "hltMatchedVBFTwoTight") {
	branchPt = inTree->hltMatchedVBFTwoTight_pt;
	branchEta = inTree->hltMatchedVBFTwoTight_eta;
	branchPhi = inTree->hltMatchedVBFTwoTight_phi;
	branchEnergy = inTree->hltMatchedVBFTwoTight_energy;
	found = true;
    }
    if (!found && filterName == "hltMatchedVBFIsoTauTwoTight") {
	branchPt = inTree->hltMatchedVBFIsoTauTwoTight_pt;
	branchEta = inTree->hltMatchedVBFIsoTauTwoTight_eta;
	branchPhi = inTree->hltMatchedVBFIsoTauTwoTight_phi;
	branchEnergy = inTree->hltMatchedVBFIsoTauTwoTight_energy;
	found = true;
    }
    if (!found && filterName == "jetL1Primitives") {
	branchPt = inTree->jetL1PrimitivesPt;
	branchEta = inTree->jetL1PrimitivesEta;
	branchPhi = inTree->jetL1PrimitivesPhi;
	branchEnergy = inTree->jetL1PrimitivesEnergy;
	found = true;
    }
    if (!found && filterName == "tauL1Primitives") {
	branchPt = inTree->tauL1PrimitivesPt;
	branchEta = inTree->tauL1PrimitivesEta;
	branchPhi = inTree->tauL1PrimitivesPhi;
	branchEnergy = inTree->tauL1PrimitivesEnergy;
	found = true;
    }
    if (!found && filterName == "hltL1VBFDiJetOR") {
	branchPt = inTree->hltL1VBFDiJetOR_pt;
	branchEta = inTree->hltL1VBFDiJetOR_eta;
	branchPhi = inTree->hltL1VBFDiJetOR_phi;
	branchEnergy = inTree->hltL1VBFDiJetOR_energy;
	found = true;
    }
    if (!found && filterName == "hltL1VBFDiJetIsoTau_taus") {
	branchPt = inTree->hltL1VBFDiJetIsoTau_tauPt;
	branchEta = inTree->hltL1VBFDiJetIsoTau_tauEta;
	branchPhi = inTree->hltL1VBFDiJetIsoTau_tauPhi;
	branchEnergy = inTree->hltL1VBFDiJetIsoTau_tauEnergy;
	found = true;
    }
    if (!found && filterName == "hltL1VBFDiJetIsoTau_jets") {
	branchPt = inTree->hltL1VBFDiJetIsoTau_jetPt;
	branchEta = inTree->hltL1VBFDiJetIsoTau_jetEta;
	branchPhi = inTree->hltL1VBFDiJetIsoTau_jetPhi;
	branchEnergy = inTree->hltL1VBFDiJetIsoTau_jetEnergy;
	found = true;
    }
    if (!found && filterName == "hltL1sDoubleTauBigOR") {
	branchPt = inTree->hltL1sDoubleTauBigOR_pt;
	branchEta = inTree->hltL1sDoubleTauBigOR_eta;
	branchPhi = inTree->hltL1sDoubleTauBigOR_phi;
	branchEnergy = inTree->hltL1sDoubleTauBigOR_energy;
	found = true;
    }

    std::vector<TLorentzVector> objContainer;
    TLorentzVector tempObj;
    for (int iObj = 0; iObj < objNumber; ++iObj) {
	tempObj.SetPtEtaPhiE(branchPt->at(iObj),
			     branchEta->at(iObj),
			     branchPhi->at(iObj),
			     branchEnergy->at(iObj));
	if (tempObj.Pt() > ptCut) objContainer.push_back(tempObj);
    }	
    return objContainer;
}

// increment counters if the AOD object is in the specified container
void incIfMatchOneAODObj(int &jetCounter, int &tauCounter, int &bothCounter, std::vector<TLorentzVector> jetContainer, std::vector<TLorentzVector> tauContainer, TLorentzVector AODObj) {
    int AODObjInJetContainer = objInContainer(jetContainer, AODObj);
    int AODObjInTauContainer = objInContainer(tauContainer, AODObj);
    jetCounter += AODObjInJetContainer;
    tauCounter += AODObjInTauContainer;
    bothCounter += (AODObjInJetContainer && AODObjInTauContainer);
}
// increment counters if the AOD objects are in the specified container
void incIfMatchAllAODObjs(int &jetCounter, int &tauCounter, int &bothCounter, std::vector<TLorentzVector> jetContainer, std::vector<TLorentzVector> tauContainer, std::vector<TLorentzVector> AODContainer) {
    int AODJetsInJetContainer = (objInContainer(jetContainer, AODContainer.at(0)) && objInContainer(jetContainer, AODContainer.at(1)));
    int AODTausInTauContainer = (objInContainer(tauContainer, AODContainer.at(2)) && objInContainer(tauContainer, AODContainer.at(3)));
    jetCounter += AODJetsInJetContainer;
    tauCounter += AODTausInTauContainer;
    bothCounter += (AODJetsInJetContainer && AODTausInTauContainer);
}
