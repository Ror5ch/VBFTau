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

//PFTauCollection Branches
vector<float> hltHpsPFTauProducer_pt;
vector<float> hltHpsPFTauProducer_eta;
vector<float> hltHpsPFTauProducer_phi;

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

    tree->Branch("hltHpsPFTauProducer_pt", &hltHpsPFTauProducer_pt);
    tree->Branch("hltHpsPFTauProducer_eta", &hltHpsPFTauProducer_eta);
    tree->Branch("hltHpsPFTauProducer_phi", &hltHpsPFTauProducer_phi);
}

void NtupleMaker::fillTriggers(const edm::Event& iEvent){

    using namespace edm;

    // clearing vectors at the start of every event 
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

    hltHpsPFTauProducer_pt.clear();
    hltHpsPFTauProducer_eta.clear();
    hltHpsPFTauProducer_phi.clear();

    // getting trigger results and saving to passTrigBranch
    edm::Handle<edm::TriggerResults> triggerResults;
    iEvent.getByToken(triggerResultToken_, triggerResults);
    edm::Handle<trigger::TriggerEvent> triggerEvent;
    iEvent.getByToken(triggerEventToken_, triggerEvent);
    const edm::TriggerNames triggerNames_ = iEvent.triggerNames(*triggerResults);
    std::string pathName="HLT_VBF_DoubleTightChargedIsoPFTauHPS20_Trk1_eta2p1_v1";
    passTrig_ = triggerResults->accept(triggerNames_.triggerIndex(pathName));
    passTrigBranch.push_back(passTrig_);

    // filling PFTauCollection kinematic information
    edm::Handle<vector<reco::PFTau>> PFTauHandle;
    iEvent.getByToken(PFTauCollection_, PFTauHandle);

    for(vector<reco::PFTau>::const_iterator iPFTau = PFTauHandle->begin(); iPFTau != PFTauHandle->end(); ++iPFTau) {
	hltHpsPFTauProducer_pt.push_back(iPFTau->pt());
	hltHpsPFTauProducer_eta.push_back(iPFTau->eta());
	hltHpsPFTauProducer_phi.push_back(iPFTau->phi());
    }

    // filling branches with triggerObjs information
    const trigger::size_type nFilters(triggerEvent->sizeFilters());
    std::string hltHpsDoublePFTau_Tag = "hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon::MYHLT";
    std::string hltMatchedVBFOne_Tag = "hltMatchedVBFOnePFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20::MYHLT";
    std::string hltMatchedVBFTwo_Tag = "hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20::MYHLT";

    for(trigger::size_type iFilter=0; iFilter!=nFilters; ++iFilter){
	std::string filterTag = triggerEvent->filterTag(iFilter).encode();
	trigger::Keys objectKeys = triggerEvent->filterKeys(iFilter);
	const trigger::TriggerObjectCollection& triggerObjects(triggerEvent->getObjects());
	for(trigger::size_type iKey=0; iKey < objectKeys.size(); ++iKey){
	    trigger::size_type objKey = objectKeys.at(iKey);
	    const trigger::TriggerObject& triggerObj(triggerObjects[objKey]);
	    pt_ = triggerObj.pt();
	    eta_ = triggerObj.eta();
	    phi_ = triggerObj.phi();
	// fill hltHpsDoublePFTau branches if match
	    if (filterTag == hltHpsDoublePFTau_Tag && pt_>0){
		hltHpsDoublePFTau_pt.push_back(pt_); 
		hltHpsDoublePFTau_eta.push_back(eta_);
		hltHpsDoublePFTau_phi.push_back(phi_);
	    }
	    else{
		hltHpsDoublePFTau_pt.push_back(-99);
		hltHpsDoublePFTau_eta.push_back(-99);
		hltHpsDoublePFTau_phi.push_back(-99);
	    }
	// fill hltMatchedVBFOne branches if match
            if (filterTag == hltMatchedVBFOne_Tag && pt_>0){
                hltMatchedVBFOne_pt.push_back(pt_);
                hltMatchedVBFOne_eta.push_back(eta_);
                hltMatchedVBFOne_phi.push_back(phi_);
            }
            else{
                hltMatchedVBFOne_pt.push_back(-99);
                hltMatchedVBFOne_eta.push_back(-99);
                hltMatchedVBFOne_phi.push_back(-99);
            }
	// fill hltMatchedVBFTwo branches if match
            if (filterTag == hltMatchedVBFTwo_Tag && pt_>0){
                hltMatchedVBFTwo_pt.push_back(pt_);
                hltMatchedVBFTwo_eta.push_back(eta_);
                hltMatchedVBFTwo_phi.push_back(phi_);
            }
            else{
                hltMatchedVBFTwo_pt.push_back(-99);
                hltMatchedVBFTwo_eta.push_back(-99);
                hltMatchedVBFTwo_phi.push_back(-99);
            }
	} // end loop over trigger object keys
    } // end loop over nfilters
} // end function
