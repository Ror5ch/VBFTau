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
	dRObj_ = iTrigObj->DeltaR(AODObj);
	if (dRObj_ < dRObj) {dRObj = dRObj_; bestObjIndex = (iTrigObj - trigContainer.begin());}
    }
    return bestObjIndex;
}

// output a tuple of TLorentzVectors that correspond to HLT objects matched to AOD objects
// using a given HLT object container and two given AOD objects
// tuple is used instead of pair because the output was easier to manage
std::tuple<TLorentzVector, TLorentzVector> matchTwoObjs(std::vector<TLorentzVector> objCands, TLorentzVector aodObjOne, TLorentzVector aodObjTwo){

    int objMatchIndexOne = simpleMatching(objCands, aodObjOne);
    int objMatchIndexTwo = simpleMatching(objCands, aodObjTwo);
    TLorentzVector tempObjOne = objCands.at(objMatchIndexOne);
    TLorentzVector tempObjTwo = objCands.at(objMatchIndexTwo);
    double dRtempObjOne = tempObjOne.DeltaR(aodObjOne);
    double dRtempObjTwo = tempObjTwo.DeltaR(aodObjTwo);
    // if AODs match to the same object index, check which has a smaller dR
    // then remove that object and rematch
    //std::cout << objCands.size() << objMatchIndexOne << objMatchIndexTwo << std::endl;
    if (objMatchIndexOne == objMatchIndexTwo){
	std::vector<TLorentzVector> tempObjCands = objCands;
	tempObjCands.erase(tempObjCands.begin() + objMatchIndexOne);
	if (dRtempObjOne < dRtempObjTwo){
	      objMatchIndexTwo = simpleMatching(tempObjCands, aodObjTwo);
	      tempObjTwo = tempObjCands.at(objMatchIndexTwo);
	}
	if (dRtempObjTwo < dRtempObjOne){
	      objMatchIndexOne = simpleMatching(tempObjCands, aodObjOne);
	      tempObjOne = tempObjCands.at(objMatchIndexOne);
	}
    }

    return std::make_tuple(tempObjOne, tempObjTwo);
}

// output a tuple of TLorentzVectors that correspond to the jet pair with
// the highest mjj of a given jet container
std::tuple<TLorentzVector, TLorentzVector> highestMassPair(std::vector<TLorentzVector> jetContainer) {
    int highestMjjCandIndex = -1;
    int mjjCandCounter = -1; //start at -1 so when the first element is added it's element zero
    float tempMjj = -1;
    float tempMjj_ = -1;
    std::vector<std::pair<int,int>> jetPairs;
    int jetContainerSize = jetContainer.size();
    for (int iJet = 0; iJet < jetContainerSize; ++iJet) {
	for (int jJet = 0; jJet < jetContainerSize; ++jJet) {
	    if (jJet >= iJet) continue;
	    // if TLorentz objects aren't overlapped, store their positions as a pair
	    if (jetContainer.at(iJet).DeltaR(jetContainer.at(jJet)) > 0.5) {
		jetPairs.push_back(std::make_pair(std::min(iJet, jJet), std::max(iJet, jJet)));
		tempMjj = (jetContainer.at(iJet) + jetContainer.at(jJet)).M();
		mjjCandCounter += 1;
		if (tempMjj_ < tempMjj) { tempMjj_ = tempMjj;	highestMjjCandIndex = mjjCandCounter;}
	    }
	}
    }
    // define two empty TLorentzVectors
    // if they aren't filled from the jet pair cands, then the output will be two
    // empty jets, whose mjj will of course be zero which therefore will not pass any
    // enforced selection
    TLorentzVector outJetOne, outJetTwo;
    outJetOne.SetPtEtaPhiE(0,0,0,0);
    outJetTwo.SetPtEtaPhiE(0,0,0,0);
    if (highestMjjCandIndex != -1) {
	outJetOne = jetContainer.at(jetPairs.at(highestMjjCandIndex).first);
	outJetTwo = jetContainer.at(jetPairs.at(highestMjjCandIndex).second);
    }
    return std::make_tuple(outJetOne, outJetTwo);
}

std::tuple<int, int> highestMassPairNew(std::vector<TLorentzVector> jetContainer) {
  int highestMjjPairIndex = -1;
  int mjjCandCounter = -1;
  float compareMjj = -1;
  float highestMjj = -1;
  std::vector<std::pair<int,int>> jetPairs;
  int jetContainerSize = jetContainer.size();
  //std::cout << "start debug---------------------" << std::endl;
  //std::cout << jetContainerSize << std::endl;
  for (int iJet = 0; iJet < jetContainerSize; ++iJet) {
    for (int jJet = iJet + 1; jJet < jetContainerSize; ++jJet) {
      //std::cout << iJet << '\t' << jJet << std::endl;
      //std::cout << jetContainer.at(iJet).DeltaR(jetContainer.at(jJet)) << std::endl;
      if (jetContainer.at(iJet).DeltaR(jetContainer.at(jJet)) > 0.5) {
        jetPairs.push_back(std::make_pair(std::min(iJet,jJet),std::max(iJet,jJet)));
        compareMjj = (jetContainer.at(iJet) + jetContainer.at(jJet)).M();
        //std::cout << compareMjj << std::endl;
        mjjCandCounter += 1;
        if (compareMjj > highestMjj) { highestMjj = compareMjj; highestMjjPairIndex = mjjCandCounter; }
      }
    }
  }
  //std::cout << highestMjjPairIndex << std::endl;
  if (highestMjjPairIndex != -1)  return std::make_tuple(jetPairs.at(highestMjjPairIndex).first, jetPairs.at(highestMjjPairIndex).second);
  else { return std::make_tuple(-1, -1); }
}

float highestMassOfPair(std::vector<TLorentzVector> jetsRmvOlTaus, std::vector<TLorentzVector> taus) {
  float mjotjot_ = 0; float tempMjotjot_ = 0;
  int jetSize = jetsRmvOlTaus.size();
  std::vector<TLorentzVector> combined;
  combined.insert(combined.begin(), jetsRmvOlTaus.begin(), jetsRmvOlTaus.end());
  combined.insert(combined.end(), taus.begin(), taus.end());
  int combinedSize = combined.size();
  for (int iObj = 0; iObj < combinedSize; ++iObj) {
    for (int jObj = 0; jObj < combinedSize; ++jObj) {
      if (jObj >= iObj) continue;
      //if (iObj >= jetSize && jObj >= jetSize ) continue; // should exclude 2tau case
      tempMjotjot_ = (combined.at(iObj) + combined.at(jObj)).M();
      if (tempMjotjot_ > mjotjot_) mjotjot_ = tempMjotjot_;
    }
  }
  return mjotjot_;
}

// overloaded function to use when given two containers 
// pairing mode can either use both containers combined for unrestricted mass pairs
// or each container individually such that one object must come from each
std::tuple<TLorentzVector, TLorentzVector> highestMassPair(std::vector<TLorentzVector> jetContainer, std::vector<TLorentzVector> tauContainer, std::string pairingMode) {
    // initialize variables
    int highestMassCandIndex = -1;
    int massCandCounter = -1; //start at -1 so when the first element is added it's element zero
    float tempMass = -1;
    float tempMass_ = -1;
    std::vector<std::pair<int,int>> objPairs;
    std::vector<TLorentzVector> combinedContainer;

    TLorentzVector outObjOne, outObjTwo;
    outObjOne.SetPtEtaPhiE(0,0,0,0);
    outObjTwo.SetPtEtaPhiE(0,0,0,0);

    if (pairingMode.find("Any") == std::string::npos && 
	pairingMode.find("OneJetOneTau") == std::string::npos) 
	std::cout << "specify valid pairingMode for highestMassPair function" << std::endl;

    int jetContainerSize = jetContainer.size();
    int tauContainerSize = tauContainer.size();
    // decide what to loop over from pairingMode variable
    if (pairingMode == "OneJetOneTau") {
	for (int iJet = 0; iJet < jetContainerSize; ++iJet) {
	    for (int iTau = 0; iTau < tauContainerSize; ++iTau) {
		objPairs.push_back(std::make_pair(iJet, iTau));
		tempMass = (jetContainer.at(iJet) + tauContainer.at(iTau)).M();
		massCandCounter += 1;
		if (tempMass_ < tempMass) { tempMass_ = tempMass;	highestMassCandIndex = massCandCounter;}
	    }
	}
	if (highestMassCandIndex != -1) {
	    outObjOne = jetContainer.at(objPairs.at(highestMassCandIndex).first);  // jet
	    outObjTwo = tauContainer.at(objPairs.at(highestMassCandIndex).second); // tau
	}
    }
    bool overlapped = false;
    if (pairingMode == "Any") {
	combinedContainer.insert(combinedContainer.begin(), jetContainer.begin(), jetContainer.end());
	combinedContainer.insert(combinedContainer.end(), tauContainer.begin(), tauContainer.end());
	int combinedContainerSize = combinedContainer.size();
	for (int iObj = 0; iObj < combinedContainerSize; ++iObj) {
	    for (int jObj = 0; jObj < combinedContainerSize; ++jObj) {
		if (jObj >= iObj) continue;
		overlapped = (combinedContainer.at(iObj).DeltaR(combinedContainer.at(jObj)) < 0.5);
		if (iObj < jetContainerSize && jObj < jetContainerSize && overlapped) continue; // jets overlapped, rarely happens
		if (iObj >= jetContainerSize && jObj >= jetContainerSize && overlapped) continue; // taus overlapped, rarely happens
		// if (overlapped) continue; this line would essentially impose overlap removal at L1, do not include
		objPairs.push_back(std::make_pair(jObj, iObj));
		tempMass = (combinedContainer.at(iObj) + combinedContainer.at(jObj)).M();
		massCandCounter += 1;
		if (tempMass_ < tempMass) {tempMass_ = tempMass;	highestMassCandIndex = massCandCounter;}
	    }
	}
	if (highestMassCandIndex != -1) {
	    outObjOne = combinedContainer.at(objPairs.at(highestMassCandIndex).first);
	    outObjTwo = combinedContainer.at(objPairs.at(highestMassCandIndex).second);
	}
    }

    // if outObjOne & Two aren't filled from the pair cands, then the output will be two
    // empty objects, whose mjj will of course be zero which therefore will not pass any
    // enforced selection

    return std::make_tuple(outObjOne, outObjTwo);
}


// outputs a vector of objects from container one cross-cleaned wrt objects from container two
// names are jets and taus bc I don't think this will be used for any other purpose
std::vector<TLorentzVector> crossCleanJetsDep(std::vector<TLorentzVector> jetObjs, std::vector<TLorentzVector> tauObjs) {
    std::vector<TLorentzVector> crossCleanedJets;
    std::cout << "check function for bug: crossCleanJets" << std::endl;
    for (int iJet = 0; iJet < jetObjs.size(); ++iJet) {
	bool clean = true;
	    for (int iTau = 0; iTau < tauObjs.size(); ++iTau) {
		if (jetObjs.at(iJet).DeltaR(tauObjs.at(iTau)) < 0.5) clean = false;
	    }
	if (clean) crossCleanedJets.push_back(jetObjs.at(iJet));
    }
    return crossCleanedJets;	
}

// outputs a vector of objects from container one cross-cleaned wrt objects from container two
// names are jets and taus bc I don't think this will be used for any other purpose
std::vector<TLorentzVector> crossCleanJets(std::vector<TLorentzVector> jetObjs, std::vector<TLorentzVector> tauObjs) {
    std::vector<TLorentzVector> crossCleanedJets;
    int jetObjsSize = jetObjs.size();
    int tauObjsSize = tauObjs.size();
    //int counter = 0;
    //std::cout << "jetObjsSize: " << jetObjsSize << std::endl;
    //std::cout << "tauObjsSize: " << tauObjsSize << std::endl;
    if (jetObjsSize >= 2 && tauObjsSize >= 1) {
      for (int iJet = 0; iJet < jetObjsSize; ++iJet) {
        bool jetIsNotTau = true;
        //std::cout << "iJet: " << iJet << std::endl;
        //if (counter < 2) { //jet is no longer checked once two matched taus are found
	  for (int iTau = 0; iTau < tauObjsSize; ++iTau) {
            float dR = jetObjs.at(iJet).DeltaR(tauObjs.at(iTau));
            //if (dR < 0.5) std::cout << "\033[0;31m" << dR << "\033[0m" << std::endl;
            //else {std::cout << dR << std::endl;} 
	    if (dR < 0.5) jetIsNotTau = false;
          }
        //}
        //if (!jetIsNotTau) counter += 1;
        if (jetIsNotTau) crossCleanedJets.push_back(jetObjs.at(iJet));
      }
    }
    else {crossCleanedJets = jetObjs;}
    //std::cout << "ccJetsSize: " << crossCleanedJets.size() << std::endl;
    return crossCleanedJets;	
}

// outputs to terminal 2 AOD objects' information
void coutAODobjs(TLorentzVector AODobjOne, TLorentzVector AODobjTwo) {
    std::cout << "obj #" << '\t' << "pt" << '\t' << "eta" << '\t' << "phi" << std::endl;
    std::cout << "1      " << std::setprecision(4) << AODobjOne.Pt() << '\t' << AODobjOne.Eta() << '\t' << AODobjOne.Phi() << std::endl;
    std::cout << "2      " << std::setprecision(4) << AODobjTwo.Pt() << '\t' << AODobjTwo.Eta() << '\t' << AODobjTwo.Phi() << std::endl;
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
// remove objNumber as an input by making it a variable of every branch via
// objNumber = inTree->branchName_variable->size();
std::vector<TLorentzVector> hltFillWithCands(trigger_tree* inTree, std::string filterName, int objNumber, int ptCut = 0) {
    std::vector<float>* branchPt;
    std::vector<float>* branchEta;
    std::vector<float>* branchPhi;
    std::vector<float>* branchEnergy;

    double etaCut = 0;
    if (filterName == "tauL1Primitives" ||
        filterName == "hltL1sDoubleTauBigOR" ||
        filterName == "hltL1VBFDiJetIsoTau_taus" ||
        filterName == "hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon" ||
        filterName == "hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon" ||
        filterName == "hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch" ||
        filterName == "hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched") {
    etaCut = 2.1;}

    if (filterName == "jetL1Primitives" ||
        filterName == "hltL1VBFDiJetOR" ||
        filterName == "hltL1VBFDiJetIsoTau_jets" ||
        filterName == "hltRealDijetFilter" ||
        filterName == "hltVBFLooseIDPFDummyFilter" ||
        filterName == "hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20" || 
        filterName == "hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20" || 
        filterName == "hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20" ||
        filterName == "hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20" ||
        filterName == "hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20") {
    etaCut = 4.7;}

    bool found = false;

    if (!found && filterName == "tauL1Primitives") {
	branchPt = inTree->tauL1PrimitivesPt;
	branchEta = inTree->tauL1PrimitivesEta;
	branchPhi = inTree->tauL1PrimitivesPhi;
	branchEnergy = inTree->tauL1PrimitivesEnergy;
	found = true;
    }
    if (!found && filterName == "hltL1sDoubleTauBigOR") {
	branchPt = inTree->hltL1sDoubleTauBigOR_pt;
	branchEta = inTree->hltL1sDoubleTauBigOR_eta;
	branchPhi = inTree->hltL1sDoubleTauBigOR_phi;
	branchEnergy = inTree->hltL1sDoubleTauBigOR_energy;
	found = true;
    }
    if (!found && filterName == "hltL1VBFDiJetIsoTau_taus") {
	branchPt = inTree->hltL1VBFDiJetIsoTau_tauPt;
	branchEta = inTree->hltL1VBFDiJetIsoTau_tauEta;
	branchPhi = inTree->hltL1VBFDiJetIsoTau_tauPhi;
	branchEnergy = inTree->hltL1VBFDiJetIsoTau_tauEnergy;
	found = true;
    }
    if (!found && filterName == "hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon") {
        branchPt = inTree->hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_pt;
        branchEta = inTree->hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_eta;
        branchPhi = inTree->hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_phi;
        branchEnergy = inTree->hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_energy;
        found = true;
    }
    if (!found && filterName == "hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon") {
        branchPt = inTree->hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon_pt;
        branchEta = inTree->hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon_eta;
        branchPhi = inTree->hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon_phi;
        branchEnergy = inTree->hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon_energy;
        found = true;
    }
    if (!found && filterName == "hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch") {
        branchPt = inTree->hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_pt;
        branchEta = inTree->hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_eta;
        branchPhi = inTree->hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_phi;
        branchEnergy = inTree->hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_energy;
        found = true;
    }
    if (!found && filterName == "hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched") {
        branchPt = inTree->hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_pt;
        branchEta = inTree->hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_eta;
        branchPhi = inTree->hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_phi;
        branchEnergy = inTree->hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_energy;
        found = true;
    }

    // jets
    if (!found && filterName == "jetL1Primitives") {
	branchPt = inTree->jetL1PrimitivesPt;
	branchEta = inTree->jetL1PrimitivesEta;
	branchPhi = inTree->jetL1PrimitivesPhi;
	branchEnergy = inTree->jetL1PrimitivesEnergy;
	found = true;
    }
    if (!found && filterName == "hltL1VBFDiJetOR") {
	branchPt = inTree->hltL1VBFDiJetOR_pt;
	branchEta = inTree->hltL1VBFDiJetOR_eta;
	branchPhi = inTree->hltL1VBFDiJetOR_phi;
	branchEnergy = inTree->hltL1VBFDiJetOR_energy;
	found = true;
    }
    if (!found && filterName == "hltL1VBFDiJetIsoTau_jets") {
	branchPt = inTree->hltL1VBFDiJetIsoTau_jetPt;
	branchEta = inTree->hltL1VBFDiJetIsoTau_jetEta;
	branchPhi = inTree->hltL1VBFDiJetIsoTau_jetPhi;
	branchEnergy = inTree->hltL1VBFDiJetIsoTau_jetEnergy;
	found = true;
    }
    if (!found && filterName == "hltRealDijetFilter") {
        branchPt = inTree->hltRealDijetFilter_pt;
        branchEta = inTree->hltRealDijetFilter_eta;
        branchPhi = inTree->hltRealDijetFilter_phi;
        branchEnergy = inTree->hltRealDijetFilter_energy;
        found = true;
    }
    if (!found && filterName == "hltVBFLooseIDPFDummyFilter") {
        branchPt = inTree->hltVBFLooseIDPFDummyFilter_pt;
        branchEta = inTree->hltVBFLooseIDPFDummyFilter_eta;
        branchPhi = inTree->hltVBFLooseIDPFDummyFilter_phi;
        branchEnergy = inTree->hltVBFLooseIDPFDummyFilter_energy;
        found = true;
    }
    if (!found && filterName == "hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20") {
	branchPt = inTree->hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_pt;
	branchEta = inTree->hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_eta;
	branchPhi = inTree->hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_phi;
	branchEnergy = inTree->hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_energy;
	found = true;
    }
    if (!found && filterName == "hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20") {
        branchPt = inTree->hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_pt;
        branchEta = inTree->hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_eta;
        branchPhi = inTree->hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_phi;
        branchEnergy = inTree->hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_energy;
        found = true;
    }
    if (!found && filterName == "hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20") {
	branchPt = inTree->hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_pt;
	branchEta = inTree->hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_eta;
	branchPhi = inTree->hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_phi;
	branchEnergy = inTree->hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_energy;
	found = true;
    }
    if (!found && filterName == "hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched") {
        branchPt = inTree->hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_pt;
        branchEta = inTree->hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_eta;
        branchPhi = inTree->hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_phi;
        branchEnergy = inTree->hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_energy;
        found = true;
    }
    if (!found && filterName == "hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20") {
        branchPt = inTree->hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_pt;
        branchEta = inTree->hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_eta;
        branchPhi = inTree->hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_phi;
        branchEnergy = inTree->hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_energy;
        found = true;
    }


    std::vector<TLorentzVector> objContainer;
    TLorentzVector tempObj;
    for (int iObj = 0; iObj < objNumber; ++iObj) {
	tempObj.SetPtEtaPhiE(branchPt->at(iObj),
			     branchEta->at(iObj),
			     branchPhi->at(iObj),
			     branchEnergy->at(iObj));
	if (tempObj.Pt() >= ptCut && tempObj.Eta() <= etaCut) objContainer.push_back(tempObj);
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

int ManfredLogic(std::vector<TLorentzVector> jets, std::vector<TLorentzVector> taus) {
  int tausSize = taus.size();
  int jetsSize = jets.size();

  //std::cout << "TauSize: " << tausSize << " JetSize: " << jetsSize << std::endl;
  for (int iTau = 0; iTau < tausSize; ++iTau) {
    for (int iJet = 0; iJet < jetsSize; ++iJet) {
      float dR_iJet = jets.at(iJet).DeltaR(taus.at(iTau));
      if (dR_iJet < 0.5) continue;
      for (int jJet = iJet+1; jJet < jetsSize; ++jJet) {
        //std::cout << "Tau: " << iTau << " Jet1: " << iJet << " Jet2: " << jJet << std::endl;
        float dR_jJet = jets.at(jJet).DeltaR(taus.at(iTau));
        if (dR_jJet < 0.5) continue;
        //std::cout << dR_iJet << " dR_iJet " << dR_jJet << " dR_jJet " << std::endl;
        float mjj = (jets.at(iJet) + jets.at(jJet)).M();
        //std::cout << mjj << " mjj" << std::endl;
        if (mjj >= 450) return 1;
      }
    }
  }
  return 0;

}
