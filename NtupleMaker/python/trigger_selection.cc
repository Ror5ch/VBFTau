#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <utility> 	//?
#include <map> 		//?
#include <string>
//#include <vector>

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

// example running on wisc server: ./trigger_selection.exe /hdfs/store/user/ballmond/merged_trigger_05092020/merged.root ./output.root

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
    int j1_loc; //jet1 location, either position 0 or 1 in the vector of jets
    int j2_loc; //other intermediate variables
    int t1_loc;
    int t2_loc;
    int vecSizeVBFOne;
    int vecSizeVBFTwo;
    int vecSizeHpsTau;
    
    float j1_pt; // branch variables (eta, phi, energy are necessary for mjj calculation)
    float j1_eta;
    float j1_phi;
    float j1_energy;
    float j2_pt;
    float j2_eta;
    float j2_phi;
    float j2_energy;
    float t1_pt;
    float t1_eta;
    float t1_phi;
    float t1_energy;
    float t2_pt;
    float t2_eta;
    float t2_phi;
    float t2_energy;
    float mjj;
    
    int vecSizeAODJet;
    int vecSizeAODTau;

    float j1_pt_A; //A is for MiniAOD
    float j1_eta_A;
    float j1_phi_A;
    float j1_energy_A;
    float j2_pt_A;
    float j2_eta_A;
    float j2_phi_A;
    float j2_energy_A;
    float t1_pt_A;
    float t1_eta_A;
    float t1_phi_A;
    float t1_energy_A;
    float t2_pt_A;
    float t2_eta_A;
    float t2_phi_A;
    float t2_energy_A;
    float mjj_A;

    float dRj1;
    float dRj2;
    float dRt1;
    float dRt2;

    int passSel;
    int passTrig;
    int passNewTrig;
    int passSelAndTrig;
    int passSelAndNewTrig;
    int matched;

    std::vector<TLorentzVector> jetCandidates;
    float mjjCandidatePair;

    std::vector<std::pair<int,int>> jetCandsLocs; //jet candidate locations

    std::vector<float> dRj1_vec;
    std::vector<float> dRj2_vec;
    std::vector<float> dRjSum;

    outTree->Branch("j1_pt", &j1_pt);
    outTree->Branch("j2_pt", &j2_pt);
    outTree->Branch("j1_eta", &j1_eta);
    outTree->Branch("j2_eta", &j2_eta);
    outTree->Branch("j1_phi", &j1_phi);
    outTree->Branch("j2_phi", &j2_phi);
    outTree->Branch("t1_pt", &t1_pt);
    outTree->Branch("t2_pt", &t2_pt);
    outTree->Branch("t1_eta", &t1_eta);
    outTree->Branch("t2_eta", &t2_eta);
    outTree->Branch("t1_phi", &t1_phi);
    outTree->Branch("t2_phi", &t2_phi);
    outTree->Branch("mjj", &mjj);

    outTree->Branch("j1_pt_A", &j1_pt_A);
    outTree->Branch("j2_pt_A", &j2_pt_A);
    outTree->Branch("j1_eta_A", &j1_eta_A);
    outTree->Branch("j2_eta_A", &j2_eta_A);
    outTree->Branch("j1_phi_A", &j1_phi_A);
    outTree->Branch("j2_phi_A", &j2_phi_A);
    outTree->Branch("t1_pt_A", &t1_pt_A);
    outTree->Branch("t2_pt_A", &t2_pt_A);
    outTree->Branch("t1_eta_A", &t1_eta_A);
    outTree->Branch("t2_eta_A", &t2_eta_A);
    outTree->Branch("t1_phi_A", &t1_phi_A);
    outTree->Branch("t2_phi_A", &t2_phi_A);
    outTree->Branch("mjj_A", &mjj_A);

    outTree->Branch("dRj1", &dRj1);
    outTree->Branch("dRj2", &dRj2);
    outTree->Branch("dRt1", &dRt1);
    outTree->Branch("dRt2", &dRt2);

    outTree->Branch("passSel", &passSel);
    outTree->Branch("passTrig", &passTrig);
    outTree->Branch("passNewTrig", &passNewTrig);
    outTree->Branch("passSelAndTrig", &passSelAndTrig);
    outTree->Branch("passSelAndNewTrig", &passSelAndNewTrig);
    outTree->Branch("matched", &matched);

    TH1F *h_cutflow = new TH1F("","",9,0,9);

    // Event Loop
    for (int iEntry = 0; iEntry < inTree->GetEntries(); iEntry++) {
	inTree->GetEntry(iEntry);
	if (iEntry % 1000 == 0) { std::cout << std::to_string(iEntry) << std::endl;}
	
	passSel = 0; //ints standing in as booleans
	passTrig = 0;//to tell if an event passed selection, trigger, etc.
	passSelAndTrig = 0;
	matched = 0;

	jetCandidates.clear(); //all for matching jets later
	jetCandsLocs.clear();
	dRj1_vec.clear();
	dRj2_vec.clear();
	dRjSum.clear();

	//tau selection:
	//2 taus
	//pt > 25 for both
	//fabs(eta) < 2.1 for both
	
	//fill cutflow before any selection
	h_cutflow->Fill(0.0,1.0);

	vecSizeAODTau = inTree->tauPt->size();
	if (vecSizeAODTau <= 1) continue;

	h_cutflow->Fill(1.0,1.0);

	t1_pt_A = inTree->tauPt->at(0);
	t2_pt_A = inTree->tauPt->at(1);
	if (t1_pt_A < 25 || t2_pt_A < 25) continue;

	h_cutflow->Fill(2.0,1.0);

	t1_eta_A = inTree->tauEta->at(0);
	t2_eta_A = inTree->tauEta->at(1);
	if (fabs(t1_eta_A) > 2.1 || fabs(t2_eta_A) > 2.1) continue;

	TLorentzVector tau1_A, tau2_A;
	t1_phi_A = inTree->tauPhi->at(0);
	t2_phi_A = inTree->tauPhi->at(1);
	tau1_A.SetPtEtaPhiE(t1_pt_A, t1_eta_A, t1_phi_A, inTree->tauEnergy->at(0));
	tau2_A.SetPtEtaPhiE(t2_pt_A, t2_eta_A, t2_phi_A, inTree->tauEnergy->at(1));

	h_cutflow->Fill(3.0,1.0);

	//jet selection:
	//2 jets
	//leading pt > 120, subleading > 45
	//fabs(eta) < 4.7 for both
	vecSizeAODJet = inTree->jetPt->size();
	if (vecSizeAODJet <= 1) continue;
	
	h_cutflow->Fill(4.0,1.0);

	if (inTree->jetPt->at(0) < 120) continue;
	if (inTree->jetPt->at(1) < 45) continue;

	h_cutflow->Fill(5.0,1.0);

	if (fabs(inTree->jetEta->at(0)) > 4.7 || fabs(inTree->jetEta->at(1) > 4.7)) continue;

	h_cutflow->Fill(6.0,1.0);

	//put all the jets that passed cuts up to here into a vector of jetCandidates
	//from jetCandidates, we remove taus (possibly) and make dijet pairs to cut on dijet mass
	for (int iJet = 0; iJet < vecSizeAODJet; iJet++){
	    //cuts above only applied to first and second jet in list
	    //these cuts make it so that a list of 11 jets, of which some have pt < 45,
	    //aren't filled into the jet candidates.
	    if (inTree->jetPt->at(iJet) < 45) continue;
	    if (fabs(inTree->jetEta->at(iJet) > 4.7)) continue;
	    TLorentzVector jetCand1;
	    jetCand1.SetPtEtaPhiE(inTree->jetPt->at(iJet), inTree->jetEta->at(iJet), inTree->jetPhi->at(iJet), inTree->jetEn->at(iJet));
	    jetCandidates.push_back(jetCand1);
	}

	//if I need to remove taus from the jets, this is where I should do that.

	for (int iCand = 0; iCand < jetCandidates.size(); iCand++){
	    for (int jCand = 0; jCand < jetCandidates.size(); jCand++){
		if (iCand >= jCand) continue;

		// makes sure one jet has pt > 120 and the other has pt > 45
		if ((jetCandidates.at(iCand).Pt()>120 && jetCandidates.at(jCand).Pt()>45) || \
		    (jetCandidates.at(iCand).Pt()>45 && jetCandidates.at(jCand).Pt()>120)) continue;
		//if ((jetCandidates.at(iCand).Pt() + jetCandidates.at(jCand).Pt()) < 165) continue;

		mjjCandidatePair = (jetCandidates.at(iCand) + jetCandidates.at(jCand)).M();
		if (mjjCandidatePair < 700) continue;

		jetCandsLocs.push_back(std::make_pair(iCand,jCand));
	    }
	}
	h_cutflow->Fill(7.0,1.0); //prev 2 for loops serv as the mjj cut
	//here should I define j1_pt_A and other kinematic variables? if I don't, 
	//those branches are never filled. If I define them after matching, then some
	//events could be excluding, making our efficiency value inaccurate..
	
	// if there isn't a viable dijet system, skip the event
	if (jetCandidates.size() < 2) continue;
	
	h_cutflow->Fill(8.0,1.0);

	j1_pt_A = jetCandidates.at(0).Pt();
	j1_eta_A = jetCandidates.at(0).Eta();
	j1_phi_A = jetCandidates.at(0).Phi();
	j1_energy_A = jetCandidates.at(0).Energy();
	j2_pt_A = jetCandidates.at(1).Pt();
	j2_eta_A = jetCandidates.at(1).Eta();
	j2_phi_A = jetCandidates.at(1).Phi();
	j2_energy_A = jetCandidates.at(1).Energy();
	mjj_A = (jetCandidates.at(0) + jetCandidates.at(1)).M();
	

	passSel = 1; //any event that makes it here has passed AOD selection
		//next is to check if the event passed the trigger AND if it can be matched to AOD
	
	vecSizeHpsTau = inTree->hltHpsDoublePFTau_pt->size();
	vecSizeVBFOne = inTree->hltMatchedVBFOne_pt->size();
	vecSizeVBFTwo = inTree->hltMatchedVBFTwo_pt->size(); 

	// fill trigger info for taus if it's available
	if (vecSizeHpsTau == 2){
	
	    t1_pt = inTree->hltHpsDoublePFTau_pt->at(0);
	    t2_pt = inTree->hltHpsDoublePFTau_pt->at(1);
	    t1_loc = 0;
	    t2_loc = 1;

	    if (t2_pt > t1_pt){
		t1_pt = inTree->hltHpsDoublePFTau_pt->at(1);
		t2_pt = inTree->hltHpsDoublePFTau_pt->at(0);
	     	t1_loc = 1;
	     	t2_loc = 0;
	    }

	    t1_eta = inTree->hltHpsDoublePFTau_eta->at(t1_loc);
	    t1_phi = inTree->hltHpsDoublePFTau_phi->at(t1_loc);
	    t1_energy = inTree->hltHpsDoublePFTau_energy->at(t1_loc);
	    t2_eta = inTree->hltHpsDoublePFTau_eta->at(t2_loc);
	    t2_phi = inTree->hltHpsDoublePFTau_phi->at(t2_loc);
	    t2_energy = inTree->hltHpsDoublePFTau_energy->at(t2_loc);

	    TLorentzVector tau1, tau2; //cut on tau dR immediately after here or later? when do we cut on dR?
	    tau1.SetPtEtaPhiE(t1_pt, t1_eta, t1_phi, t1_energy);
	    tau2.SetPtEtaPhiE(t2_pt, t2_eta, t2_phi, t2_energy);
	   
	    dRt1 = tau1.DeltaR(tau1_A);
	    dRt2 = tau2.DeltaR(tau2_A);
	}

	// fill trigger info for jets if its available
	// if there are 2 jets, make the greater pt jet j1_pt
	if (vecSizeVBFOne == 2){
	     j1_pt = inTree->hltMatchedVBFOne_pt->at(0);
	     j1_loc = 0;
	     j2_pt = inTree->hltMatchedVBFOne_pt->at(1);
	     j2_loc = 1;
	     if (j2_pt > j1_pt){
	     	j1_pt = inTree->hltMatchedVBFOne_pt->at(1);
		j1_loc = 1;
	     	j2_pt = inTree->hltMatchedVBFOne_pt->at(0);
		j2_loc = 0;
	     }
	     j1_eta = inTree->hltMatchedVBFOne_eta->at(j1_loc);
	     j2_eta = inTree->hltMatchedVBFOne_eta->at(j2_loc);
	     j1_phi = inTree->hltMatchedVBFOne_phi->at(j1_loc);
	     j2_phi = inTree->hltMatchedVBFOne_phi->at(j2_loc);
	     j1_energy = inTree->hltMatchedVBFOne_energy->at(j1_loc);
	     j2_energy = inTree->hltMatchedVBFOne_energy->at(j2_loc);
	}
	// if there's 1 jet in VBFOne filter, make it the leading one. Subleading is in prior filter, VBFTwo.
	if (vecSizeVBFOne == 1){
	     j1_pt = inTree->hltMatchedVBFOne_pt->at(0);
	     j1_loc = 0;
	     j2_pt = inTree->hltMatchedVBFTwo_pt->at(0);
	     j2_loc = 0; 
	     if (j1_pt == j2_pt) {
		j2_pt = inTree->hltMatchedVBFTwo_pt->at(1);
		j2_loc = 1;
	     }
	     j1_eta = inTree->hltMatchedVBFOne_eta->at(j1_loc);
	     j2_eta = inTree->hltMatchedVBFTwo_eta->at(j2_loc);
	     j1_phi = inTree->hltMatchedVBFOne_phi->at(j1_loc);
	     j2_phi = inTree->hltMatchedVBFTwo_phi->at(j2_loc);
	     j1_energy = inTree->hltMatchedVBFOne_energy->at(j1_loc);
	     j2_energy = inTree->hltMatchedVBFTwo_energy->at(j2_loc);
	}

	//if either of the if statements before triggered, then we have a dijet system from the trigger
	TLorentzVector jet1, jet2;
	if (vecSizeVBFOne == 1 || vecSizeVBFOne == 2){
	    jet1.SetPtEtaPhiE(j1_pt,j1_eta,j1_phi,j1_energy);
	    jet2.SetPtEtaPhiE(j2_pt,j2_eta,j2_phi,j2_energy);
	    mjj = (jet1 + jet2).M();
	}

	//now try to match to MiniAOD object if the event passed the trigger

	passTrig = inTree->passTrigBranch->at(0);
	//passNewTrig = inTree->passNewTrigBranch->front(); //uncomment when new trigger dataset is available
	//should I have a seperate script for the new trigger?

	//if (passSel == 1 && passTrig == 1) passSelAndTrig = 1;
	//if (passSel == 1 && passNewTrig == 1) passSelAndNewTrig = 1;
	
	if (passTrig){
	    
	    for (std::vector<std::pair<int,int>>::iterator it = jetCandsLocs.begin(); it != jetCandsLocs.end(); ++it){
	    	dRj1 = jet1.DeltaR(jetCandidates.at(it->first));
		dRj1_vec.push_back(dRj1);
	    	dRj2 = jet2.DeltaR(jetCandidates.at(it->second));
		dRj2_vec.push_back(dRj2);
		dRjSum.push_back(dRj1+dRj2);
	    }//end for loop, fills possible dRj1s and dRj2s to vectors that are checked in the next for loop below
	
	    if (dRj1_vec.size() != 0 && dRj2_vec.size() != 0){
		int dRjSum_ = 999;
		for (int n = 0; n < dRjSum.size(); n++){
		    if (dRjSum[n] < dRjSum_){
			dRjSum_ = dRjSum[n];
			dRj1 = dRj1_vec.at(n);
			dRj2 = dRj2_vec.at(n);
		    }//end inner if, finds min dR for both jets
		}//end for loop, finds min dR for both jets
	    }//end if, checks if vectors containing possible dRs are non-zero 	
	}//end if, sets dRj1 and 2



	outTree->Fill();
    } // end event loop

    std::string outputFileName = outName;
    TFile *fOut = TFile::Open(outputFileName.c_str(),"RECREATE");
    fOut->cd();
    h_cutflow->SetName("Cutflow");
    h_cutflow->Write();
    outTree->Write();
    fOut->Close();
    return 0;
}
