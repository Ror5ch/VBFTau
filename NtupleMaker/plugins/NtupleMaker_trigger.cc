// Braden Allmond 04/15/2021

#include "VBFTau/NtupleMaker/plugins/NtupleMaker.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Common/interface/TriggerNames.h"

using namespace std; // I think best practice is to include <vector> explicitly at the top of the file

bool passTrig_;
bool passNewTrig_;
vector<bool> passTrigBranch;
vector<bool> passNewTrigBranch;

float 	pt_;
float 	eta_;
float 	phi_;
float 	energy_;

// vars associated w old trigger and filters
//full trigger name is
//hltHpsPFTauTrack
vector<float> 	hltHpsPFTauTrack_pt;
vector<float> 	hltHpsPFTauTrack_eta;
vector<float> 	hltHpsPFTauTrack_phi;
vector<float>	hltHpsPFTauTrack_energy;
//hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon
vector<float>	hltHpsDoublePFTau_pt;
vector<float>	hltHpsDoublePFTau_eta;
vector<float>	hltHpsDoublePFTau_phi;
vector<float>	hltHpsDoublePFTau_energy;
//hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20
vector<float> 	hltMatchedVBFOne_pt;
vector<float> 	hltMatchedVBFOne_eta;
vector<float> 	hltMatchedVBFOne_phi;
vector<float>	hltMatchedVBFOne_energy;
//hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20
vector<float>	hltMatchedVBFTwo_pt;
vector<float>	hltMatchedVBFTwo_eta;
vector<float>	hltMatchedVBFTwo_phi;
vector<float>	hltMatchedVBFTwo_energy;

// vars associated w new trigger and filters
// full trigger name is
//hltHpsDoubleTightIsoAgainstMuonMatch (this filter checks L1-HLT matched taus > 50 GeV)
vector<float> hltHpsDoubleAgainstMuon_pt;
vector<float> hltHpsDoubleAgainstMuon_eta;
vector<float> hltHpsDoubleAgainstMuon_phi;
vector<float> hltHpsDoubleAgainstMuon_energy;
//hltMatchedNewVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20
vector<float> hltMatchedNewVBFTwo_pt;
vector<float> hltMatchedNewVBFTwo_eta;
vector<float> hltMatchedNewVBFTwo_phi;
vector<float> hltMatchedNewVBFTwo_energy;

//the taus/jets are the same objects and therefore have the same information,
//no matter if it's stored by the new or the old trigger
//The difference is the new trigger ends its filter without cutting off 115pt Jets,
//and it has a separate matching branch for taus (or a tau) at 50GeV
//Everything else is the same/shared btwn (HpsTauTracks for example)

void NtupleMaker::branchesTriggers(TTree* tree){

    tree->Branch("passTrigBranch", &passTrigBranch);    
    tree->Branch("passNewTrigBranch", &passNewTrigBranch);

    tree->Branch("hltHpsPFTauTrack_pt", &hltHpsPFTauTrack_pt);
    tree->Branch("hltHpsPFTauTrack_eta", &hltHpsPFTauTrack_eta);
    tree->Branch("hltHpsPFTauTrack_phi", &hltHpsPFTauTrack_phi);
    tree->Branch("hltHpsPFTauTrack_energy", &hltHpsPFTauTrack_energy);

    tree->Branch("hltHpsDoublePFTau_pt", &hltHpsDoublePFTau_pt);
    tree->Branch("hltHpsDoublePFTau_eta", &hltHpsDoublePFTau_eta);
    tree->Branch("hltHpsDoublePFTau_phi", &hltHpsDoublePFTau_phi);
    tree->Branch("hltHpsDoublePFTau_energy", &hltHpsDoublePFTau_energy);

    tree->Branch("hltMatchedVBFOne_pt", &hltMatchedVBFOne_pt);
    tree->Branch("hltMatchedVBFOne_eta", &hltMatchedVBFOne_eta);
    tree->Branch("hltMatchedVBFOne_phi", &hltMatchedVBFOne_phi);
    tree->Branch("hltMatchedVBFOne_energy", &hltMatchedVBFOne_energy);

    tree->Branch("hltMatchedVBFTwo_pt", &hltMatchedVBFTwo_pt);
    tree->Branch("hltMatchedVBFTwo_eta", &hltMatchedVBFTwo_eta);
    tree->Branch("hltMatchedVBFTwo_phi", &hltMatchedVBFTwo_phi);
    tree->Branch("hltMatchedVBFTwo_energy", &hltMatchedVBFTwo_energy);

    tree->Branch("hltMatchedNewVBFTwo_pt", &hltMatchedNewVBFTwo_pt);
    tree->Branch("hltMatchedNewVBFTwo_eta", &hltMatchedNewVBFTwo_eta);
    tree->Branch("hltMatchedNewVBFTwo_phi", &hltMatchedNewVBFTwo_phi);
    tree->Branch("hltMatchedNewVBFTwo_energy", &hltMatchedNewVBFTwo_energy);

    tree->Branch("hltHpsDoubleAgainstMuon_pt", &hltHpsDoubleAgainstMuon_pt);
    tree->Branch("hltHpsDoubleAgainstMuon_eta", &hltHpsDoubleAgainstMuon_eta);
    tree->Branch("hltHpsDoubleAgainstMuon_phi", &hltHpsDoubleAgainstMuon_phi);
    tree->Branch("hltHpsDoubleAgainstMuon_energy", &hltHpsDoubleAgainstMuon_energy);
}

void NtupleMaker::fillTriggers(const edm::Event& iEvent){

    using namespace edm;

    // clearing vectors at the start of every event 
    passTrigBranch.clear(); 
    passNewTrigBranch.clear();

    hltHpsPFTauTrack_pt.clear();
    hltHpsPFTauTrack_eta.clear();
    hltHpsPFTauTrack_phi.clear();
    hltHpsPFTauTrack_energy.clear();
    hltHpsDoublePFTau_pt.clear();
    hltHpsDoublePFTau_eta.clear();
    hltHpsDoublePFTau_phi.clear();
    hltHpsDoublePFTau_energy.clear();
    hltMatchedVBFOne_pt.clear();
    hltMatchedVBFOne_eta.clear();
    hltMatchedVBFOne_phi.clear();
    hltMatchedVBFOne_energy.clear();
    hltMatchedVBFTwo_pt.clear();
    hltMatchedVBFTwo_eta.clear();
    hltMatchedVBFTwo_phi.clear();
    hltMatchedVBFTwo_energy.clear();

    hltMatchedNewVBFTwo_pt.clear();
    hltMatchedNewVBFTwo_eta.clear();
    hltMatchedNewVBFTwo_phi.clear();
    hltMatchedNewVBFTwo_energy.clear();
    hltHpsDoubleAgainstMuon_pt.clear();
    hltHpsDoubleAgainstMuon_eta.clear();
    hltHpsDoubleAgainstMuon_phi.clear();
    hltHpsDoubleAgainstMuon_energy.clear();
    
    // getting trigger results and saving to passTrigBranch
    edm::Handle<edm::TriggerResults> triggerResults;
    iEvent.getByToken(triggerResultToken_, triggerResults);
    edm::Handle<trigger::TriggerEvent> triggerEvent;
    iEvent.getByToken(triggerEventToken_, triggerEvent);
    const edm::TriggerNames triggerNames_ = iEvent.triggerNames(*triggerResults);
    std::string pathNameTrig="HLT_VBF_DoubleTightChargedIsoPFTauHPS20_Trk1_eta2p1_v1";
    std::string pathNameNewTrig="HLT_NewVBF_DoubleTightChargedIsoPFTauHPS20_Trk1_eta2p1_v1";
    passTrig_ = triggerResults->accept(triggerNames_.triggerIndex(pathNameTrig));
    passNewTrig_ = triggerResults->accept(triggerNames_.triggerIndex(pathNameNewTrig));
    passTrigBranch.push_back(passTrig_);
    passNewTrigBranch.push_back(passNewTrig_);

    // filling branches with triggerObjs information
    const trigger::size_type nFilters(triggerEvent->sizeFilters());
    std::string hltHpsPFTauTrack_Tag = "hltHpsPFTauTrack::MYHLT";
    std::string hltHpsDoublePFTau_Tag = "hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon::MYHLT";
    std::string hltMatchedVBFOne_Tag = "hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20::MYHLT";
    std::string hltMatchedVBFTwo_Tag = "hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20::MYHLT";
    std::string hltMatchedNewVBFTwo_Tag = "hltMatchedNewVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20::MYHLT";
    std::string hltHpsDoubleAgainstMuon_Tag = "hltHpsDoubleTightIsoAgainstMuonMatch::MYHLT";

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
	    energy_ = triggerObj.energy();
	// fill hltHpsPFTauTrack branches if match
	    if (filterTag == hltHpsPFTauTrack_Tag && pt_>0){
		hltHpsPFTauTrack_pt.push_back(pt_);
		hltHpsPFTauTrack_eta.push_back(eta_);
		hltHpsPFTauTrack_phi.push_back(phi_);
		hltHpsPFTauTrack_energy.push_back(energy_);
	    }
	// fill hltHpsDoublePFTau branches if match
	    if (filterTag == hltHpsDoublePFTau_Tag && pt_>0){
		hltHpsDoublePFTau_pt.push_back(pt_); 
		hltHpsDoublePFTau_eta.push_back(eta_);
		hltHpsDoublePFTau_phi.push_back(phi_);
		hltHpsDoublePFTau_energy.push_back(energy_);
	    }
	// fill hltMatchedVBFOne branches if match
            if (filterTag == hltMatchedVBFOne_Tag && pt_>0){
                hltMatchedVBFOne_pt.push_back(pt_);
                hltMatchedVBFOne_eta.push_back(eta_);
                hltMatchedVBFOne_phi.push_back(phi_);
		hltMatchedVBFOne_energy.push_back(energy_);
            }
	// fill hltMatchedVBFTwo branches if match
            if (filterTag == hltMatchedVBFTwo_Tag && pt_>0){
                hltMatchedVBFTwo_pt.push_back(pt_);
                hltMatchedVBFTwo_eta.push_back(eta_);
                hltMatchedVBFTwo_phi.push_back(phi_);
		hltMatchedVBFTwo_energy.push_back(energy_);
            }
	// fill hltMatchedVBFNewTwo branches if match
	    if (filterTag == hltMatchedNewVBFTwo_Tag && pt_>0){
		hltMatchedNewVBFTwo_pt.push_back(pt_);
 		hltMatchedNewVBFTwo_eta.push_back(eta_);
		hltMatchedNewVBFTwo_phi.push_back(phi_);
		hltMatchedNewVBFTwo_energy.push_back(energy_);
	    }
	// fill hltHpsDoubleAgainstMuon branches if match
	    if (filterTag == hltHpsDoubleAgainstMuon_Tag && pt_>0){
		hltHpsDoubleAgainstMuon_pt.push_back(pt_);
		hltHpsDoubleAgainstMuon_eta.push_back(eta_);
		hltHpsDoubleAgainstMuon_phi.push_back(phi_);
		hltHpsDoubleAgainstMuon_energy.push_back(energy_);
	    }
	} // end loop over trigger object keys
    } // end loop over nfilters
} // end function
