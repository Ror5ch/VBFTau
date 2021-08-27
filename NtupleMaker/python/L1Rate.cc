#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <set>
#include <string>
#include <iomanip>
#include <tuple>

#include "TH1F.h"
#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TLorentzVector.h"

#include "trigger_tree.h"
#include "trigger_selection.h"

// example running on wisc server: ./trigger_selection.exe /hdfs/store/user/ballmond/merged_trigger_05092020/merged.root ./output.root new


int main(int argc, char** argv)	{

    // Open input file and make new output file, also declare necessary variables
    std::string inName = *(argv + 1);
    std::string outName = *(argv + 2);

    TFile *fIn = TFile::Open(inName.c_str());
    TTree* treePtr = (TTree*) fIn->Get("demo/vbf");
    trigger_tree* inTree = new trigger_tree (treePtr);

    TTree *outTree = new TTree("outTree", "outTree");
    outTree->SetDirectory(0);

    int triggerFlag = 4;

    // run variables
    int nEvents, runNumber, lumiBlock;
    unsigned long long eventNumberID;

    // hlt variables
    float j1_pt, j1_eta, j1_phi, j1_energy; 
    float j2_pt, j2_eta, j2_phi, j2_energy; 
    float mjj;
    float t1_pt, t1_eta, t1_phi, t1_energy;
    float t2_pt, t2_eta, t2_phi, t2_energy;
   
    bool passedAnL1;

    // filled data branches
    outTree->Branch("nEvents", &nEvents);
    outTree->Branch("runNumber", &runNumber);
    outTree->Branch("lumiBlock", &lumiBlock);
    outTree->Branch("eventNumberID", &eventNumberID);
    // L1 vars
    outTree->Branch("j1_pt", &j1_pt);
    outTree->Branch("j1_eta", &j1_eta);
    outTree->Branch("j1_phi", &j1_phi);
    outTree->Branch("j1_energy", &j1_energy);
    outTree->Branch("j2_pt", &j2_pt);
    outTree->Branch("j2_eta", &j2_eta);
    outTree->Branch("j2_phi", &j2_phi);
    outTree->Branch("j2_energy", &j2_energy);
    outTree->Branch("mjj", &mjj);
    outTree->Branch("t1_pt", &t1_pt);
    outTree->Branch("t1_eta", &t1_eta);
    outTree->Branch("t1_phi", &t1_phi);
    outTree->Branch("t1_energy", &t1_energy);
    outTree->Branch("t2_pt", &t2_pt);
    outTree->Branch("t2_eta", &t2_eta);
    outTree->Branch("t2_phi", &t2_phi);
    outTree->Branch("t2_energy", &t2_energy);

    outTree->Branch("passedAnL1", &passedAnL1);

    // ad hoc variables for testing

    bool L1SeedCaseZeroZero, L1SeedCaseZero, L1SeedCaseOne, L1SeedCaseTwo, L1SeedCaseThree;
    L1SeedCaseZeroZero = L1SeedCaseZero = L1SeedCaseOne = L1SeedCaseTwo = L1SeedCaseThree = false;

    std::set <int> lumis;

    // Event Loop
    // for-loop of fewer events is useful to test code without heavy I/O to terminal from cout statements
    //for (int iEntry = 0; iEntry < 1000001; ++iEntry) {
    int totalEntries = inTree->GetEntries();
    for (int iEntry = 14100000; iEntry < 14400000; ++iEntry) {
	inTree->GetEntry(iEntry);
	if (iEntry % 100000 == 0) std::cout << std::to_string(iEntry) << std::endl;

	runNumber = inTree->runNumber;

	//if (runNumber != 323976) continue;
	if (runNumber != 324077) continue;

	lumiBlock = inTree->lumiBlock;
	eventNumberID = inTree->eventNumberID;
	lumis.insert(lumiBlock);	

	nEvents += 1; // incremented since event is in the run

	// -----------------------------------------L1 investigation -----------------------------//
	int primL1TauSize = inTree->tauL1PrimitivesPt->size();
	int primL1JetSize = inTree->jetL1PrimitivesPt->size();
	TLorentzVector objOne, objTwo; // two objects used for invariant mass, mjj in most cases
	double twoObjMass;

	// it's technically better to define these all once outside of the main loop
	int primL1JetPtCut = 35;
	int primL1TauPtCut = 35;
	int primL1IsoTau40PtCut = 40;
	int primL1IsoTau45PtCut = 45;
	// testing multiple possible L1s, pay attention to the booleans,,,
	bool smallerContainers = false;

	bool oldVBFwL1Prim = false; //L1_Jet110_Jet35_Mass_Min620
	bool newVBFwL1Prim = true; //L1_DoubleJet35_IsoTau45_Mjj450_RmvOl
	bool L1_DoubleJet35_DoubleIsoTau40_MassAnyTwo400_RmvOl = false;
	bool L1_DoubleJet35_IsoTau45_MassAnyTwo400_RmvOl = false; // this seed is most like new vbf seed
	bool L1_Jet35_Tau35_MassJetTau450_IsoTau45_RmvOl = false;

	passedAnL1 = false;

	L1SeedCaseZeroZero = oldVBFwL1Prim;
	L1SeedCaseZero = newVBFwL1Prim;
	L1SeedCaseOne = L1_DoubleJet35_DoubleIsoTau40_MassAnyTwo400_RmvOl;
	L1SeedCaseTwo = L1_DoubleJet35_IsoTau45_MassAnyTwo400_RmvOl;
	L1SeedCaseThree = L1_Jet35_Tau35_MassJetTau450_IsoTau45_RmvOl;

	bool objOneIsJet, objTwoIsJet, objOneIsTau, objTwoIsTau;
	objOneIsJet = objTwoIsJet = objOneIsTau = objTwoIsTau = false;

	TLorentzVector L1_Jet1, L1_Jet2, L1_Tau1, L1_Tau2;
	TLorentzVector emptyVec;
	emptyVec.SetPtEtaPhiE(0,0,0,0);
	L1_Jet1 = emptyVec; L1_Jet2 = emptyVec; L1_Tau1 = emptyVec; L1_Tau2 = emptyVec;

	// fill standard containers, jet container, tau container, and isoTau container
	// primitive containers not sorted by Pt or by M
	std::vector<TLorentzVector> jetL1Primitives = hltFillWithCands(inTree, "jetL1Primitives", primL1JetSize, primL1JetPtCut);
	int jetPrimSize = jetL1Primitives.size();
	std::vector<TLorentzVector> tauL1Primitives = hltFillWithCands(inTree, "tauL1Primitives", primL1TauSize, primL1TauPtCut);
	int tauPrimSize = tauL1Primitives.size();

	if (smallerContainers && jetPrimSize > 3 && tauPrimSize > 3) {
	    jetL1Primitives.resize(3);
	    jetPrimSize = jetL1Primitives.size();
	    tauL1Primitives.resize(3);
	    tauPrimSize = tauL1Primitives.size();
	}

	std::vector<TLorentzVector> isoTau40L1Primitives;
	for (int iTau = 0; iTau < tauPrimSize; ++iTau) {
	    if (tauL1Primitives.at(iTau).Pt() > primL1IsoTau40PtCut && inTree->tauL1PrimitivesIso->at(iTau))
		isoTau40L1Primitives.push_back(tauL1Primitives.at(iTau));
	}
	int isoTau40PrimSize = isoTau40L1Primitives.size();

	std::vector<TLorentzVector> isoTau45L1Primitives;
	for (int iTau = 0; iTau < isoTau40PrimSize; ++iTau) {
	    if (isoTau40L1Primitives.at(iTau).Pt() > primL1IsoTau45PtCut) 
		isoTau45L1Primitives.push_back(isoTau40L1Primitives.at(iTau));
	}
	int isoTau45PrimSize = isoTau45L1Primitives.size();

	// perform cross cleaning (cc) (Wrt = with respect to)
	std::vector<TLorentzVector> crossCleanedL1PrimJetsWrtTau35 = crossCleanJets(jetL1Primitives, tauL1Primitives);
	int ccWrtTau35L1JetPrimSize = crossCleanedL1PrimJetsWrtTau35.size();

	std::vector<TLorentzVector> crossCleanedL1PrimJetsWrtIsoTau40 = crossCleanJets(jetL1Primitives, isoTau40L1Primitives);
	int ccWrtIsoTau40L1JetPrimSize = crossCleanedL1PrimJetsWrtIsoTau40.size();

	std::vector<TLorentzVector> crossCleanedL1PrimJetsWrtIsoTau45 = crossCleanJets(jetL1Primitives, isoTau45L1Primitives);
	int ccWrtIsoTau45L1JetPrimSize = crossCleanedL1PrimJetsWrtIsoTau45.size();

	if (oldVBFwL1Prim && jetPrimSize >= 2) {
	    std::tie(objOne, objTwo) = highestMassPair(jetL1Primitives);
	    twoObjMass = (objOne + objTwo).M();
	    double jetOnePt = objOne.Pt();
	    double jetTwoPt = objTwo.Pt();
	    bool someJetGreaterThan110GeV = false;
	    for (int iJet = 0; iJet < jetPrimSize; ++iJet) {
	        if (jetL1Primitives.at(iJet).Pt() >= 110) someJetGreaterThan110GeV = true;
	    }
	    if (twoObjMass > 620 && (((jetOnePt >= 110 && jetTwoPt >= 35) || (jetOnePt >= 35 && jetTwoPt >= 110))
			|| (jetOnePt >= 35 && jetTwoPt >= 35 && someJetGreaterThan110GeV)) ){ 
		passedAnL1 = true; 
		objOneIsJet = true;
		objTwoIsJet = true;
		objOneIsTau = false;
		objTwoIsTau = false;

		if (jetOnePt >= jetTwoPt) {
		    L1_Jet1 = objOne;
		    L1_Jet2 = objTwo;
		}
		if (jetOnePt < jetTwoPt) {
		    L1_Jet1 = objTwo;
		    L1_Jet2 = objOne;
		}
	    }
	}

	if (newVBFwL1Prim && ccWrtIsoTau45L1JetPrimSize >= 2 && isoTau45PrimSize >= 1 ) {
	    // check mjj
            std::tie(objOne, objTwo) = highestMassPair(crossCleanedL1PrimJetsWrtIsoTau45);
	    twoObjMass = (objOne + objTwo).M();
            if (twoObjMass > 450) {
		passedAnL1 = true;

		objOneIsJet = objInContainer(crossCleanedL1PrimJetsWrtIsoTau45, objOne);
		objTwoIsJet = objInContainer(crossCleanedL1PrimJetsWrtIsoTau45, objTwo);
	    	objOneIsTau = objInContainer(isoTau45L1Primitives, objOne);
	    	objTwoIsTau = objInContainer(isoTau45L1Primitives, objTwo);

		if (objOne.Pt() >= objTwo.Pt()) {
		    L1_Jet1 = objOne;
		    L1_Jet2 = objTwo;
		}
		if (objOne.Pt() < objTwo.Pt()) {
		    L1_Jet1 = objTwo;
		    L1_Jet2 = objOne;
		}
		L1_Tau1 = isoTau45L1Primitives.at(0);

		//std::cout << "objOneIsJet: " << objOneIsJet << std::endl;
		//std::cout << "objTwoIsJet: " << objTwoIsJet << std::endl;
		//std::cout << "objOneIsTau: " << objOneIsTau << std::endl;
		//std::cout << "objTwoIsTau: " << objTwoIsTau << std::endl;
	    }
	} // end newVBFwL1Prim if statement

	if (L1_DoubleJet35_DoubleIsoTau40_MassAnyTwo400_RmvOl && ccWrtIsoTau40L1JetPrimSize >= 2 && isoTau40PrimSize >= 2) {
	    // check two object mass
	    std::tie(objOne, objTwo) = highestMassPair(crossCleanedL1PrimJetsWrtIsoTau40, isoTau45L1Primitives, "Any");
	    twoObjMass = (objOne + objTwo).M();
	    if (twoObjMass > 400) {
		passedAnL1 = true;

	    	objOneIsJet = objInContainer(crossCleanedL1PrimJetsWrtIsoTau40, objOne);
	    	objTwoIsJet = objInContainer(crossCleanedL1PrimJetsWrtIsoTau40, objTwo);
	    	objOneIsTau = objInContainer(isoTau45L1Primitives, objOne);
	    	objTwoIsTau = objInContainer(isoTau45L1Primitives, objTwo);

		if (objOneIsJet && !objOneIsTau && !objTwoIsJet && objTwoIsTau) {
		    L1_Jet1 = objOne; L1_Tau1 = objTwo;
		}
		if (!objOneIsJet && objOneIsTau && objTwoIsJet && !objTwoIsTau) {
		    L1_Jet1 = objTwo; L1_Tau1 = objOne;
		}
		if (objOneIsJet && !objOneIsTau && objTwoIsJet && !objTwoIsTau) {
		    if (objOne.Pt() >= objTwo.Pt()) {
			L1_Jet1 = objOne;
			L1_Jet2 = objTwo;
		    }
		    if (objOne.Pt() < objTwo.Pt()) {
			L1_Jet1 = objTwo;
			L1_Jet2 = objOne;
		    }
		    L1_Tau1 = isoTau45L1Primitives.at(0);
		}
		if (!objOneIsJet && objOneIsTau && !objTwoIsJet && objTwoIsTau) {
		    L1_Jet1 = crossCleanedL1PrimJetsWrtIsoTau40.at(0); 
		    if (objOne.Pt() >= objTwo.Pt()) {
			L1_Tau1 = objOne; 
			L1_Tau2 = objTwo;
		    }
		    if (objOne.Pt() < objTwo.Pt()) {
			L1_Tau1 = objTwo;
			L1_Tau2 = objOne;
		    }
		}

		//std::cout << "objOneIsJet: " << objOneIsJet << std::endl;
		//std::cout << "objTwoIsJet: " << objTwoIsJet << std::endl;
		//std::cout << "objOneIsTau: " << objOneIsTau << std::endl;
		//std::cout << "objTwoIsTau: " << objTwoIsTau << std::endl;
	    }
	} // end L1_DoubleJet35_DoubleIsoTau40_MassAnyTwo400_RmvOl if statement 
		
	if (L1_DoubleJet35_IsoTau45_MassAnyTwo400_RmvOl && ccWrtIsoTau45L1JetPrimSize >= 2 && isoTau45PrimSize >= 1) {
	    // we exclude the two tau case for this seed, but allow the two jet case.
	    // To do this, we look for the highestMassPair of just jets and then
	    // the highest mass pair using one tau and one jet. Then we take the larger of the two pairs
	    TLorentzVector tempObjOne, tempObjTwo;
	    std::tie(tempObjOne, tempObjTwo) = highestMassPair(crossCleanedL1PrimJetsWrtIsoTau45, isoTau45L1Primitives, "OneJetOneTau");
	    double tempTwoObjMass = (tempObjOne + tempObjTwo).M();
	    std::tie(objOne, objTwo) = highestMassPair(crossCleanedL1PrimJetsWrtIsoTau45);
	    twoObjMass = (objOne + objTwo).M();

	    if (tempTwoObjMass > twoObjMass) {
		twoObjMass = tempTwoObjMass; objOne = tempObjOne; objTwo = tempObjTwo;
		std::cout << "OneJetOneTau heavier than DiJet" << std::endl; // happens about half the time w Rmv Ol.
	    }

	    if (twoObjMass > 450) {
		passedAnL1 = true;

	    	objOneIsJet = objInContainer(crossCleanedL1PrimJetsWrtIsoTau45, objOne);
	    	objTwoIsJet = objInContainer(crossCleanedL1PrimJetsWrtIsoTau45, objTwo);
	    	objOneIsTau = objInContainer(isoTau45L1Primitives, objOne);
	    	objTwoIsTau = objInContainer(isoTau45L1Primitives, objTwo);

		if (objOneIsJet && !objOneIsTau && !objTwoIsJet && objTwoIsTau) {
		    L1_Jet1 = objOne; L1_Tau1 = objTwo;
		}
		if (!objOneIsJet && objOneIsTau && objTwoIsJet && !objTwoIsTau) {
		    L1_Jet1 = objTwo; L1_Tau1 = objOne;
		}
		if (objOneIsJet && !objOneIsTau && objTwoIsJet && !objTwoIsTau) {
		    if (objOne.Pt() >= objTwo.Pt()) {
			L1_Jet1 = objOne;
			L1_Jet2 = objTwo;
		    }
		    if (objOne.Pt() < objTwo.Pt()) {
			L1_Jet1 = objTwo;
			L1_Jet2 = objOne;
		    }
		    L1_Tau1 = isoTau45L1Primitives.at(0);
		}
		//std::cout << "objOneIsJet: " << objOneIsJet << std::endl;
		//std::cout << "objTwoIsJet: " << objTwoIsJet << std::endl;
		//std::cout << "objOneIsTau: " << objOneIsTau << std::endl;
		//std::cout << "objTwoIsTau: " << objTwoIsTau << std::endl;
	    }
	} // end L1_DoubleJet35_IsoTau45_MassAnyTwo400_RmvOl if statement

	if (L1_Jet35_Tau35_MassJetTau450_IsoTau45_RmvOl && ccWrtTau35L1JetPrimSize >= 1 && tauPrimSize >= 1 && isoTau45PrimSize >= 1) {
	    // not clear if i should check in tau or iso tau container... checking tau for now
	    // check two object mass
	    std::tie(objOne, objTwo) = highestMassPair(crossCleanedL1PrimJetsWrtTau35, tauL1Primitives, "OneJetOneTau");
	    twoObjMass = (objOne + objTwo).M();
	    if (twoObjMass > 450) {
		passedAnL1 = true;

	        objOneIsJet = objInContainer(crossCleanedL1PrimJetsWrtTau35, objOne);
	        objTwoIsJet = objInContainer(crossCleanedL1PrimJetsWrtTau35, objTwo);
	        objOneIsTau = objInContainer(tauL1Primitives, objOne);
	        objTwoIsTau = objInContainer(tauL1Primitives, objTwo);

		if (objOneIsJet && !objOneIsTau && !objTwoIsJet && objTwoIsTau) {
		    L1_Jet1 = objOne; L1_Tau1 = objTwo;
		}
		if (!objOneIsJet && objOneIsTau && objTwoIsJet && !objTwoIsTau) {
		    L1_Jet1 = objTwo; L1_Tau1 = objOne;
		}

		//std::cout << "objOneIsJet: " << objOneIsJet << std::endl;
		//std::cout << "objTwoIsJet: " << objTwoIsJet << std::endl;
		//std::cout << "objOneIsTau: " << objOneIsTau << std::endl;
		//std::cout << "objTwoIsTau: " << objTwoIsTau << std::endl;
	    }
        } // end L1_Jet35_Tau35_MassJetTau450_IsoTau45_RmvOl if statement

	// fill variables
	if (passedAnL1) {
	    if (L1_Jet1.Pt() > 0) {j1_pt = L1_Jet1.Pt(); j1_eta = L1_Jet1.Eta(); j1_phi = L1_Jet1.Phi(); j1_energy = L1_Jet1.Energy();}
	    if (L1_Jet2.Pt() > 0) {j2_pt = L1_Jet2.Pt(); j2_eta = L1_Jet2.Eta(); j2_phi = L1_Jet2.Phi(); j2_energy = L1_Jet2.Energy();}
	    if (L1_Tau1.Pt() > 0) {t1_pt = L1_Tau1.Pt(); t1_eta = L1_Tau1.Eta(); t1_phi = L1_Tau1.Phi(); t1_energy = L1_Tau1.Energy();}
	    if (L1_Tau2.Pt() > 0) {t2_pt = L1_Tau2.Pt(); t2_eta = L1_Tau2.Eta(); t2_phi = L1_Tau2.Phi(); t2_energy = L1_Tau2.Energy();}
	}

        outTree->Fill();
    }// end event loop

    if (L1SeedCaseZeroZero) std::cout << "old VBF but using L1 primitives (seed 00)" << std::endl;
    if (L1SeedCaseZero) std::cout << "new VBF but using L1 primitves (seed 0)" << std::endl;
    if (L1SeedCaseOne) std::cout << "DblJet35_DblIsoTau45_MassAnyTwo450 (seed 1)" << std::endl;
    if (L1SeedCaseTwo) std::cout << "DblJet35_IsoTau45_MassAnyTwo400 (seed 2)" << std::endl;
    if (L1SeedCaseThree) std::cout << "Jet35_Tau35_MassJetTau450_IsoTau45_RmvOl (seed 3)" << std::endl; 

    std::cout << "nEvents: " << nEvents << std::endl;
    std::cout << "Lumi Block Set Size: " << lumis.size() << std::endl;
    std::string outputFileName = outName;
    TFile *fOut = TFile::Open(outputFileName.c_str(),"RECREATE");
    fOut->cd();

    outTree->Write();
    fOut->Close();
    return 0;
}
