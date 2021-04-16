// Braden Allmond 04/15/2021

#include "VBFTau/NtupleMaker/plugins/NtupleMaker.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Common/interface/TriggerNames.h"

using namespace std; // I think best practice is to include <vector> explicitly at the top of the file

bool passTrig_;
vector<bool> passTrigBranch;

float 	pt_;
float 	eta_;
float 	phi_;

//full trigger is
//hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon
vector<float>	hltHpsDoublePFTau_pt;
vector<float>	hltHpsDoublePFTau_eta;
vector<float>	hltHpsDoublePFTau_phi;
//hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20
vector<float> 	hltMatchedVBFOne_pt;
vector<float> 	hltMatchedVBFOne_eta;
vector<float> 	hltMatchedVBFOne_phi;
//hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20
vector<float>	hltMatchedVBFTwo_pt;
vector<float>	hltMatchedVBFTwo_eta;
vector<float>	hltMatchedVBFTwo_phi;

void NtupleMaker::branchesTriggers(TTree* tree){

    tree->Branch("passTrigBranch", &passTrigBranch);    

    tree->Branch("hltHpsDoublePFTau_pt", &hltHpsDoublePFTau_pt);
    tree->Branch("hltHpsDoublePFTau_eta", &hltHpsDoublePFTau_eta);
    tree->Branch("hltHpsDoublePFTau_phi", &hltHpsDoublePFTau_phi);

    tree->Branch("hltMatchedVBFOne_pt", &hltMatchedVBFOne_pt);
    tree->Branch("hltMatchedVBFOne_eta", &hltMatchedVBFOne_eta);
    tree->Branch("hltMatchedVBFOne_phi", &hltMatchedVBFOne_phi);

    tree->Branch("hltMatchedVBFTwo_pt", &hltMatchedVBFTwo_pt);
    tree->Branch("hltMatchedVBFTwo_eta", &hltMatchedVBFTwo_eta);
    tree->Branch("hltMatchedVBFTwo_phi", &hltMatchedVBFTwo_phi);
}

void NtupleMaker::fillTriggers(const edm::Event& iEvent){

    //using namespace edm; 
    passTrigBranch.clear();

    hltHpsDoublePFTau_pt.clear();
    hltHpsDoublePFTau_eta.clear();
    hltHpsDoublePFTau_phi.clear();
    hltMatchedVBFOne_pt.clear();
    hltMatchedVBFOne_eta.clear();
    hltMatchedVBFOne_phi.clear();
    hltMatchedVBFTwo_pt.clear();
    hltMatchedVBFTwo_eta.clear();
    hltMatchedVBFTwo_phi.clear();

    edm::Handle<edm::TriggerResults> triggerResults;
    iEvent.getByToken(triggerResultToken_, triggerResults);
    edm::Handle<trigger::TriggerEvent> triggerEvent;
    iEvent.getByToken(triggerEventToken_, triggerEvent);
    const edm::TriggerNames triggerNames_ = iEvent.triggerNames(*triggerResults);
    std::string pathName="HLT_VBF_DoubleTightChargedIsoPFTauHPS20_Trk1_eta2p1_v1";
    passTrig_ = triggerResults->accept(triggerNames_.triggerIndex(pathName));
    std::cout << "passTrig: " << passTrig_ << std::endl;
    passTrigBranch.push_back(passTrig_);

}
