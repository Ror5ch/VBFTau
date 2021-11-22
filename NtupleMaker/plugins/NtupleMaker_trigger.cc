// Braden Allmond Nov 1st 2021

#include "VBFTau/NtupleMaker/plugins/NtupleMaker.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Common/interface/TriggerNames.h"

#include "DataFormats/Common/interface/TriggerResults.h"

using namespace std; // I think best practice is to include <vector> explicitly at the top of the file

int passDiTauTrig;
int passOldTrigTight;
int passNewTrigTight;

float 	pt_;
float 	eta_;
float 	phi_;
float 	energy_;

int	nEvents;
//full trigger filter name is commented above each of its branches
//hltL1sDoubleTauBigOR
int 		passhltL1sDoubleTauBigOR;
vector<float>	hltL1sDoubleTauBigOR_pt;
vector<float>	hltL1sDoubleTauBigOR_eta;
vector<float>	hltL1sDoubleTauBigOR_phi;
vector<float>	hltL1sDoubleTauBigOR_energy;
//hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg
int		passDiTau35HLTFinalFilter;
vector<float>	diTau35HLTFinalFilter_pt;
vector<float>	diTau35HLTFinalFilter_eta;
vector<float>	diTau35HLTFinalFilter_phi;
vector<float>	diTau35HLTFinalFilter_energy;
//hltL1VBFDiJetOR
int	passhltL1VBFDiJetOR;
vector<float>	hltL1VBFDiJetOR_pt;
vector<float>	hltL1VBFDiJetOR_eta;
vector<float>	hltL1VBFDiJetOR_phi;
vector<float>	hltL1VBFDiJetOR_energy;
//hltL1VBFDiJetIsoTau (previously called hltL1NewVBFDiJet) 
int	passhltL1VBFDiJetIsoTau;
vector<int>	hltL1VBFDiJetIsoTau_nJets;
vector<float>	hltL1VBFDiJetIsoTau_jetPt;
vector<float>	hltL1VBFDiJetIsoTau_jetEta;
vector<float>	hltL1VBFDiJetIsoTau_jetPhi;
vector<float>	hltL1VBFDiJetIsoTau_jetEnergy;
vector<int>	hltL1VBFDiJetIsoTau_nTaus;
vector<float>	hltL1VBFDiJetIsoTau_tauPt;
vector<float>	hltL1VBFDiJetIsoTau_tauEta;
vector<float>	hltL1VBFDiJetIsoTau_tauPhi;
vector<float>	hltL1VBFDiJetIsoTau_tauEnergy;
//hltHpsDoublePFTau20
int	passhltHpsDoublePFTau20;
vector<float> 	hltHpsDoublePFTau20_pt;
vector<float> 	hltHpsDoublePFTau20_eta;
vector<float> 	hltHpsDoublePFTau20_phi;
vector<float>	hltHpsDoublePFTau20_energy;
//
//hltHpsDoublePFTau20TrackTightChargedIso
int	passhltHpsDoublePFTauTight;
vector<float>	hltHpsDoublePFTauTight_pt;
vector<float>   hltHpsDoublePFTauTight_eta;
vector<float>   hltHpsDoublePFTauTight_phi;
vector<float>   hltHpsDoublePFTauTight_energy;
//
//hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon
int	passhltHpsDoublePFTauAgainstMuonTight;
vector<float>	hltHpsDoublePFTauAgainstMuonTight_pt;
vector<float>	hltHpsDoublePFTauAgainstMuonTight_eta;
vector<float>	hltHpsDoublePFTauAgainstMuonTight_phi;
vector<float>	hltHpsDoublePFTauAgainstMuonTight_energy;
//
//hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20
int	passhltMatchedVBFTwoTight;
vector<float>	hltMatchedVBFTwoTight_pt;
vector<float>	hltMatchedVBFTwoTight_eta;
vector<float>	hltMatchedVBFTwoTight_phi;
vector<float>	hltMatchedVBFTwoTight_energy;
//
//hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20
int	passhltMatchedVBFOneTight;
vector<float> 	hltMatchedVBFOneTight_pt;
vector<float> 	hltMatchedVBFOneTight_eta;
vector<float> 	hltMatchedVBFOneTight_phi;
vector<float>	hltMatchedVBFOneTight_energy;
//
//hltHpsPFTau50TrackPt1TightChargedIsolationL1HLTMatched, renamed from hltHpsDoubleTightIsoAgainstMuonMatch
int	passhltHpsPFTau50Tight;
vector<float> 	hltHpsPFTau50Tight_pt;
vector<float> 	hltHpsPFTau50Tight_eta;
vector<float> 	hltHpsPFTau50Tight_phi;
vector<float> 	hltHpsPFTau50Tight_energy;
//
//hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20
int	passhltMatchedVBFIsoTauTwoTight;
vector<float> 	hltMatchedVBFIsoTauTwoTight_pt;
vector<float> 	hltMatchedVBFIsoTauTwoTight_eta;
vector<float> 	hltMatchedVBFIsoTauTwoTight_phi;
vector<float> 	hltMatchedVBFIsoTauTwoTight_energy;

// the taus/jets are the same objects and therefore have the same information,
// no matter if it's stored by the new or the old trigger
// The difference is the new trigger ends its filter without cutting off 115pt Jets,
// and it has a separate matching branch for taus (or a tau) at 50GeV
// Everything else is the same/shared btwn (HpsTauTracks for example)

void NtupleMaker::branchesTriggers(TTree* tree){

    tree->Branch("nEvents", &nEvents);

    tree->Branch("passDiTauTrig", &passDiTauTrig);

    tree->Branch("passOldTrigTight", &passOldTrigTight);    
    
    tree->Branch("passNewTrigTight", &passNewTrigTight);

    tree->Branch("passhltL1sDoubleTauBigOR", &passhltL1sDoubleTauBigOR);
    tree->Branch("hltL1sDoubleTauBigOR_pt", &hltL1sDoubleTauBigOR_pt);
    tree->Branch("hltL1sDoubleTauBigOR_eta", &hltL1sDoubleTauBigOR_eta);
    tree->Branch("hltL1sDoubleTauBigOR_phi", &hltL1sDoubleTauBigOR_phi);
    tree->Branch("hltL1sDoubleTauBigOR_energy", &hltL1sDoubleTauBigOR_energy);

    // hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg
    // don't need the cutflow, so I'm only storing the final filter which is used for HLT-AOD matching purposes
    tree->Branch("passDiTau35HLTFinalFilter", &passDiTau35HLTFinalFilter);  
    tree->Branch("diTau35HLTFinalFilter_pt", &diTau35HLTFinalFilter_pt);  
    tree->Branch("diTau35HLTFinalFilter_eta", &diTau35HLTFinalFilter_eta);  
    tree->Branch("diTau35HLTFinalFilter_phi", &diTau35HLTFinalFilter_phi);  
    tree->Branch("diTau35HLTFinalFilter_energy", &diTau35HLTFinalFilter_energy);  

    tree->Branch("passhltL1VBFDiJetOR", &passhltL1VBFDiJetOR);
    tree->Branch("hltL1VBFDiJetOR_pt", &hltL1VBFDiJetOR_pt);
    tree->Branch("hltL1VBFDiJetOR_eta", &hltL1VBFDiJetOR_eta);
    tree->Branch("hltL1VBFDiJetOR_phi", &hltL1VBFDiJetOR_phi);
    tree->Branch("hltL1VBFDiJetOR_energy", &hltL1VBFDiJetOR_energy);

    tree->Branch("passhltL1VBFDiJetIsoTau", &passhltL1VBFDiJetIsoTau);
    tree->Branch("hltL1VBFDiJetIsoTau_nJets", &hltL1VBFDiJetIsoTau_nJets);
    tree->Branch("hltL1VBFDiJetIsoTau_jetPt", &hltL1VBFDiJetIsoTau_jetPt);
    tree->Branch("hltL1VBFDiJetIsoTau_jetEta", &hltL1VBFDiJetIsoTau_jetEta);
    tree->Branch("hltL1VBFDiJetIsoTau_jetPhi", &hltL1VBFDiJetIsoTau_jetPhi);
    tree->Branch("hltL1VBFDiJetIsoTau_jetEnergy", &hltL1VBFDiJetIsoTau_jetEnergy);
    tree->Branch("hltL1VBFDiJetIsoTau_nTaus", &hltL1VBFDiJetIsoTau_nTaus);
    tree->Branch("hltL1VBFDiJetIsoTau_tauPt", &hltL1VBFDiJetIsoTau_tauPt);
    tree->Branch("hltL1VBFDiJetIsoTau_tauEta", &hltL1VBFDiJetIsoTau_tauEta);
    tree->Branch("hltL1VBFDiJetIsoTau_tauPhi", &hltL1VBFDiJetIsoTau_tauPhi);
    tree->Branch("hltL1VBFDiJetIsoTau_tauEnergy", &hltL1VBFDiJetIsoTau_tauEnergy);

    //hltHpsDoublePFTau20
    tree->Branch("passhltHpsDoublePFTau20", &passhltHpsDoublePFTau20);
    tree->Branch("hltHpsDoublePFTau20_pt", &hltHpsDoublePFTau20_pt);
    tree->Branch("hltHpsDoublePFTau20_eta", &hltHpsDoublePFTau20_eta);
    tree->Branch("hltHpsDoublePFTau20_phi", &hltHpsDoublePFTau20_phi);
    tree->Branch("hltHpsDoublePFTau20_energy", &hltHpsDoublePFTau20_energy);
    //hltHpsDoublePFTau20TrackTightChargedIso
    tree->Branch("passhltHpsDoublePFTauTight", &passhltHpsDoublePFTauTight);
    tree->Branch("hltHpsDoublePFTauTight_pt", &hltHpsDoublePFTauTight_pt);
    tree->Branch("hltHpsDoublePFTauTight_eta", &hltHpsDoublePFTauTight_eta);
    tree->Branch("hltHpsDoublePFTauTight_phi", &hltHpsDoublePFTauTight_phi);
    tree->Branch("hltHpsDoublePFTauTight_energy", &hltHpsDoublePFTauTight_energy);
    //hltHpsDoublePFTauAgainstMuon 
    tree->Branch("passhltHpsDoublePFTauAgainstMuonTight", &passhltHpsDoublePFTauAgainstMuonTight);
    tree->Branch("hltHpsDoublePFTauAgainstMuonTight_pt", &hltHpsDoublePFTauAgainstMuonTight_pt);
    tree->Branch("hltHpsDoublePFTauAgainstMuonTight_eta", &hltHpsDoublePFTauAgainstMuonTight_eta);
    tree->Branch("hltHpsDoublePFTauAgainstMuonTight_phi", &hltHpsDoublePFTauAgainstMuonTight_phi);
    tree->Branch("hltHpsDoublePFTauAgainstMuonTight_energy", &hltHpsDoublePFTauAgainstMuonTight_energy);
    // hltMatchedVBFTwo 
    tree->Branch("passhltMatchedVBFTwoTight", &passhltMatchedVBFTwoTight);
    tree->Branch("hltMatchedVBFTwoTight_pt", &hltMatchedVBFTwoTight_pt);
    tree->Branch("hltMatchedVBFTwoTight_eta", &hltMatchedVBFTwoTight_eta);
    tree->Branch("hltMatchedVBFTwoTight_phi", &hltMatchedVBFTwoTight_phi);
    tree->Branch("hltMatchedVBFTwoTight_energy", &hltMatchedVBFTwoTight_energy);
    //hltMatchedVBFOne 
    tree->Branch("passhltMatchedVBFOneTight", &passhltMatchedVBFOneTight);
    tree->Branch("hltMatchedVBFOneTight_pt", &hltMatchedVBFOneTight_pt);
    tree->Branch("hltMatchedVBFOneTight_eta", &hltMatchedVBFOneTight_eta);
    tree->Branch("hltMatchedVBFOneTight_phi", &hltMatchedVBFOneTight_phi);
    tree->Branch("hltMatchedVBFOneTight_energy", &hltMatchedVBFOneTight_energy);
    //hltHpsPFTau50 
    tree->Branch("passhltHpsPFTau50Tight", &passhltHpsPFTau50Tight);
    tree->Branch("hltHpsPFTau50Tight_pt", &hltHpsPFTau50Tight_pt);
    tree->Branch("hltHpsPFTau50Tight_eta", &hltHpsPFTau50Tight_eta);
    tree->Branch("hltHpsPFTau50Tight_phi", &hltHpsPFTau50Tight_phi);
    tree->Branch("hltHpsPFTau50Tight_energy", &hltHpsPFTau50Tight_energy);
    // hltMatchedVBFIsoTauTwo 
    tree->Branch("passhltMatchedVBFIsoTauTwoTight", &passhltMatchedVBFIsoTauTwoTight);
    tree->Branch("hltMatchedVBFIsoTauTwoTight_pt", &hltMatchedVBFIsoTauTwoTight_pt);
    tree->Branch("hltMatchedVBFIsoTauTwoTight_eta", &hltMatchedVBFIsoTauTwoTight_eta);
    tree->Branch("hltMatchedVBFIsoTauTwoTight_phi", &hltMatchedVBFIsoTauTwoTight_phi);
    tree->Branch("hltMatchedVBFIsoTauTwoTight_energy", &hltMatchedVBFIsoTauTwoTight_energy);
}

void NtupleMaker::fillTriggers(const edm::Event& iEvent){

    using namespace edm;

    // clearing vectors and initializing flags at the start of every event 
    nEvents = 0;

    // pass trig as in pass final hlt decision
    passDiTauTrig = 0; // DiTau35 HLT
    passOldTrigTight = 0; // "Old" is Inclusive VBF HLT, the one we can compare to but didn't make ourselves
    passNewTrigTight = 0; // "New" is VBF + 2 Tau HLT, adding VBF + 1 Tau HLT now

    // DiTau 32 L1 branches (there's a big OR with multiple DiTaus, but 32 is the lowest)
    passhltL1sDoubleTauBigOR = 0;
    hltL1sDoubleTauBigOR_pt.clear();
    hltL1sDoubleTauBigOR_eta.clear();
    hltL1sDoubleTauBigOR_phi.clear();
    hltL1sDoubleTauBigOR_energy.clear();

    passDiTau35HLTFinalFilter = 0;
    diTau35HLTFinalFilter_pt.clear();
    diTau35HLTFinalFilter_eta.clear();
    diTau35HLTFinalFilter_phi.clear();
    diTau35HLTFinalFilter_energy.clear();

    // Inclusive VBF L1 branches
    passhltL1VBFDiJetOR = 0;
    hltL1VBFDiJetOR_pt.clear();
    hltL1VBFDiJetOR_eta.clear();
    hltL1VBFDiJetOR_phi.clear();
    hltL1VBFDiJetOR_energy.clear();

    // Propose/New L1 branches
    passhltL1VBFDiJetIsoTau = 0;
    hltL1VBFDiJetIsoTau_nJets.clear();
    hltL1VBFDiJetIsoTau_jetPt.clear();
    hltL1VBFDiJetIsoTau_jetEta.clear();
    hltL1VBFDiJetIsoTau_jetPhi.clear();
    hltL1VBFDiJetIsoTau_jetEnergy.clear();
    hltL1VBFDiJetIsoTau_nTaus.clear();
    hltL1VBFDiJetIsoTau_tauPt.clear();
    hltL1VBFDiJetIsoTau_tauEta.clear();
    hltL1VBFDiJetIsoTau_tauPhi.clear();
    hltL1VBFDiJetIsoTau_tauEnergy.clear();

    // hltHpsDoubelPFTau20
    passhltHpsDoublePFTau20 = 0;
    hltHpsDoublePFTau20_pt.clear();
    hltHpsDoublePFTau20_eta.clear();
    hltHpsDoublePFTau20_phi.clear();
    hltHpsDoublePFTau20_energy.clear();

    // hltHpsDoublePFTau20TrackTightChargedIso
    passhltHpsDoublePFTauTight = 0;
    hltHpsDoublePFTauTight_pt.clear();
    hltHpsDoublePFTauTight_eta.clear();
    hltHpsDoublePFTauTight_phi.clear();
    hltHpsDoublePFTauTight_energy.clear();

    // hltHpsDoublePFTauAgainstMuon 
    passhltHpsDoublePFTauAgainstMuonTight = 0;
    hltHpsDoublePFTauAgainstMuonTight_pt.clear();
    hltHpsDoublePFTauAgainstMuonTight_eta.clear();
    hltHpsDoublePFTauAgainstMuonTight_phi.clear();
    hltHpsDoublePFTauAgainstMuonTight_energy.clear();

    // hltMatchedVBFTwo 
    passhltMatchedVBFTwoTight = 0;
    hltMatchedVBFTwoTight_pt.clear();
    hltMatchedVBFTwoTight_eta.clear();
    hltMatchedVBFTwoTight_phi.clear();
    hltMatchedVBFTwoTight_energy.clear();

    // hltMatchedVBFOne 
    passhltMatchedVBFOneTight = 0;
    hltMatchedVBFOneTight_pt.clear();
    hltMatchedVBFOneTight_eta.clear();
    hltMatchedVBFOneTight_phi.clear();
    hltMatchedVBFOneTight_energy.clear();

    // hltHpsPFTau50 
    passhltHpsPFTau50Tight = 0;
    hltHpsPFTau50Tight_pt.clear();
    hltHpsPFTau50Tight_eta.clear();
    hltHpsPFTau50Tight_phi.clear();
    hltHpsPFTau50Tight_energy.clear();

    // hltMatchedVBFIsoTauTwo 
    passhltMatchedVBFIsoTauTwoTight = 0;
    hltMatchedVBFIsoTauTwoTight_pt.clear();
    hltMatchedVBFIsoTauTwoTight_eta.clear();
    hltMatchedVBFIsoTauTwoTight_phi.clear();
    hltMatchedVBFIsoTauTwoTight_energy.clear();

    // getting trigger results, following this page
    // https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideHLTAnalysis
    edm::Handle<edm::TriggerResults> triggerResults;
    iEvent.getByToken(triggerResultToken_, triggerResults);
    edm::Handle<trigger::TriggerEvent> triggerEvent;
    iEvent.getByToken(triggerEventToken_, triggerEvent);
    const edm::TriggerNames triggerNames_ = iEvent.triggerNames(*triggerResults);

    // saving trigger results to respective branches
    //std::string pathNameDiTauTrig = "HLT_DoubleTightChargedIsoPFTauHPS40_Trk1_eta2p1_Reg_v1"; // previously used DiTau HLT
    std::string pathNameDiTauTrig = "HLT_DoubleTightChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_v1";
    passDiTauTrig = triggerResults->accept(triggerNames_.triggerIndex(pathNameDiTauTrig));
    // using DiTau35 HLT

    // Inclusive VBF HLT
    std::string pathNameOldTrigTight = "HLT_VBF_DoubleTightChargedIsoPFTauHPS20_Trk1_eta2p1_v1";
    passOldTrigTight = triggerResults->accept(triggerNames_.triggerIndex(pathNameOldTrigTight));

    // VBF + 2 Tau HLT
    std::string pathNameNewTrigTight = "HLT_VBF_TightChargedIsoPFTauHPS50_PFTauHPS20_Trk1_eta2p1_v1";
    passNewTrigTight = triggerResults->accept(triggerNames_.triggerIndex(pathNameNewTrigTight));

    // filling branches with triggerObjs information, hltL1VBFDiJetIsoTau object info filled separately since it's a weird L1

    // getting trigger refs for hltL1VBFDiJetIsoTau filter's tau/jet splitting
    edm::Handle<trigger::TriggerEventWithRefs> triggerEventWithRefsHandle_;
    iEvent.getByToken(triggerEventWithRefsToken_, triggerEventWithRefsHandle_);
    const unsigned int filterIndex(triggerEventWithRefsHandle_->filterIndex(InputTag("hltL1VBFDiJetIsoTau", "", "MYHLT")));
		//making jet object and filling vector
    l1t::JetVectorRef jetCandRefVec;
    trigger::Vids jvids;
    triggerEventWithRefsHandle_->getObjects(filterIndex, jvids, jetCandRefVec);
		//making tau object and filling vector
    l1t::TauVectorRef tauCandRefVec;
    trigger::Vids tvids;
    triggerEventWithRefsHandle_->getObjects(filterIndex, tvids, tauCandRefVec);

    const unsigned int nJets(jvids.size());
    if (nJets > 0) {
        //std::cout << "   Jets: " << nJets << std::endl;
        hltL1VBFDiJetIsoTau_nJets.push_back(nJets);
        for (unsigned int i = 0; i != nJets; ++i) {
            //std::cout << i << " " << jvids[i] << " " << jetCandRefVec[i]->pt() << endl;
	    hltL1VBFDiJetIsoTau_jetPt.push_back(jetCandRefVec[i]->pt());
	    hltL1VBFDiJetIsoTau_jetEta.push_back(jetCandRefVec[i]->eta());
   	    hltL1VBFDiJetIsoTau_jetPhi.push_back(jetCandRefVec[i]->phi());
   	    hltL1VBFDiJetIsoTau_jetEnergy.push_back(jetCandRefVec[i]->energy());
        }
    }

    const unsigned int nTaus(tvids.size());
    if (nTaus > 0) {
	//std::cout << "   Taus: " << nTaus << std::endl;
	hltL1VBFDiJetIsoTau_nTaus.push_back(nTaus);
	for (unsigned int i = 0; i != nTaus; ++i) {
	    //std::cout << i << " " << tvids[i] << " " << tauCandRefVec[i]->pt() << endl;
	    hltL1VBFDiJetIsoTau_tauPt.push_back(tauCandRefVec[i]->pt());
	    hltL1VBFDiJetIsoTau_tauEta.push_back(tauCandRefVec[i]->eta());
   	    hltL1VBFDiJetIsoTau_tauPhi.push_back(tauCandRefVec[i]->phi());
   	    hltL1VBFDiJetIsoTau_tauEnergy.push_back(tauCandRefVec[i]->energy());
	}
    }
    //filling the rest, as well as passFilter branches
    const trigger::size_type nFilters(triggerEvent->sizeFilters());
    std::string hltL1sDoubleTauBigOR_Tag = "hltL1sDoubleTauBigOR::MYHLT"; // ditau L1
    std::string hltL1VBFDiJetOR_Tag = "hltL1VBFDiJetOR::MYHLT";		  // inclusive L1
    std::string hltL1VBFDiJetIsoTau_Tag = "hltL1VBFDiJetIsoTau::MYHLT";	  // proposed L1

    std::string hltHpsDoublePFTau20_Tag = "hltHpsDoublePFTau20::MYHLT";
    std::string hltHpsDoublePFTauTight_Tag = "hltHpsDoublePFTau20TrackTightChargedIso::MYHLT";
    std::string hltHpsDoublePFTauAgainstMuonTight_Tag = "hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon::MYHLT";
    std::string hltMatchedVBFTwoTight_Tag = "hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20::MYHLT";
    std::string hltMatchedVBFOneTight_Tag = "hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20::MYHLT";
    std::string hltHpsPFTau50Tight_Tag = "hltHpsPFTau50TrackPt1TightChargedIsolationL1HLTMatched::MYHLT";
    std::string hltMatchedVBFIsoTauTwoTight_Tag = "hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20::MYHLT";

    std::string diTau35HLTFinalFilter_Tag = "hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg::MYHLT";

    // accepted filters per event
    for(trigger::size_type iFilter=0; iFilter!=nFilters; ++iFilter) {
	std::string filterTag = triggerEvent->filterTag(iFilter).encode();
	trigger::Keys objectKeys = triggerEvent->filterKeys(iFilter);

	const trigger::TriggerObjectCollection& triggerObjects(triggerEvent->getObjects());
	// fill "pass filter" branches
	int nObjKeys = objectKeys.size();
	if (filterTag == hltL1VBFDiJetOR_Tag && nObjKeys >= 0) nEvents = 1; // accept pass or fail condition to fill nEvents
	if (filterTag == hltL1sDoubleTauBigOR_Tag && nObjKeys >= 2) passhltL1sDoubleTauBigOR = 1;
	if (filterTag == hltL1VBFDiJetOR_Tag && nObjKeys >= 2) passhltL1VBFDiJetOR = 1;
	if (filterTag == hltL1VBFDiJetIsoTau_Tag && hltL1VBFDiJetIsoTau_tauPt.size() >= 1
						 && hltL1VBFDiJetIsoTau_jetPt.size() >= 2) passhltL1VBFDiJetIsoTau = 1;

	// hltHpsDoublePFTau20 filter to be replaced by hltHpsDoublePFTau filter
	if (filterTag == hltHpsDoublePFTau20_Tag && nObjKeys >= 2) passhltHpsDoublePFTau20 = 1; 
	// hltHpsDoublePFTau20TrackTightChargedIso
	if (filterTag == hltHpsDoublePFTauTight_Tag && nObjKeys >= 2) passhltHpsDoublePFTauTight = 1;
	// hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon
	if (filterTag == hltHpsDoublePFTauAgainstMuonTight_Tag && nObjKeys >= 2) passhltHpsDoublePFTauAgainstMuonTight = 1;
	// hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20
	if (filterTag == hltMatchedVBFTwoTight_Tag && nObjKeys >= 2) passhltMatchedVBFTwoTight = 1;
	// hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20
	if (filterTag == hltMatchedVBFOneTight_Tag && nObjKeys >= 1) passhltMatchedVBFOneTight = 1;
	// hltHpsPFTau50TrackPt1TightChargedIsolationL1HLTMatched
	if (filterTag == hltHpsPFTau50Tight_Tag && nObjKeys >= 1) passhltHpsPFTau50Tight = 1;
	// hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20
	if (filterTag == hltMatchedVBFIsoTauTwoTight_Tag && nObjKeys >= 2) passhltMatchedVBFIsoTauTwoTight = 1;
        // hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg
        if (filterTag == diTau35HLTFinalFilter_Tag && nObjKeys >= 2) passDiTau35HLTFinalFilter = 1;

// should change to only filling kinematic branches if the flag for passing the filter is set to true as well
      
	//loop over trigger objects and store their kinematics to the proper filter branches
	for(trigger::size_type iKey=0; iKey < nObjKeys; ++iKey){
	    trigger::size_type objKey = objectKeys.at(iKey);
	    const trigger::TriggerObject& triggerObj(triggerObjects[objKey]);
	    pt_ = triggerObj.pt();
	    eta_ = triggerObj.eta();
	    phi_ = triggerObj.phi();
	    energy_ = triggerObj.energy();
	// fill ditau trig and old trig L1 branches (new trig L1 branches filled separately because it has two types of objects)
	    if (filterTag == hltL1sDoubleTauBigOR_Tag && passhltL1sDoubleTauBigOR && pt_>0) {
		hltL1sDoubleTauBigOR_pt.push_back(pt_);
		hltL1sDoubleTauBigOR_eta.push_back(eta_);
		hltL1sDoubleTauBigOR_phi.push_back(phi_);
		hltL1sDoubleTauBigOR_energy.push_back(energy_);
	    }
	    if (filterTag == hltL1VBFDiJetOR_Tag && passhltL1VBFDiJetOR && pt_>0) {
		hltL1VBFDiJetOR_pt.push_back(pt_);
		hltL1VBFDiJetOR_eta.push_back(eta_);
		hltL1VBFDiJetOR_phi.push_back(phi_);
		hltL1VBFDiJetOR_energy.push_back(energy_);
	    }
	// fill hltHpsDoublePFTau20 branches if match
	    if (filterTag == hltHpsDoublePFTau20_Tag && passhltHpsDoublePFTau20 && pt_>0) {
		hltHpsDoublePFTau20_pt.push_back(pt_);
		hltHpsDoublePFTau20_eta.push_back(eta_);
		hltHpsDoublePFTau20_phi.push_back(phi_);
		hltHpsDoublePFTau20_energy.push_back(energy_);
	    }
	// fill hltHpsDoublePFTauTight branches if match
	    if (filterTag == hltHpsDoublePFTauTight_Tag && passhltHpsDoublePFTauTight && pt_>0) {
		hltHpsDoublePFTauTight_pt.push_back(pt_); 
		hltHpsDoublePFTauTight_eta.push_back(eta_);
		hltHpsDoublePFTauTight_phi.push_back(phi_);
		hltHpsDoublePFTauTight_energy.push_back(energy_);
	    }
	// fill hltHpsDoublePFTauAgainstMuonTight branches if match
	    if (filterTag == hltHpsDoublePFTauAgainstMuonTight_Tag && passhltHpsDoublePFTauAgainstMuonTight && pt_>0) {
		hltHpsDoublePFTauAgainstMuonTight_pt.push_back(pt_); 
		hltHpsDoublePFTauAgainstMuonTight_eta.push_back(eta_);
		hltHpsDoublePFTauAgainstMuonTight_phi.push_back(phi_);
		hltHpsDoublePFTauAgainstMuonTight_energy.push_back(energy_);
	    }
	// fill hltMatchedVBFTwoTight branches if match
            if (filterTag == hltMatchedVBFTwoTight_Tag && passhltMatchedVBFTwoTight && pt_>0) {
                hltMatchedVBFTwoTight_pt.push_back(pt_);
                hltMatchedVBFTwoTight_eta.push_back(eta_);
                hltMatchedVBFTwoTight_phi.push_back(phi_);
		hltMatchedVBFTwoTight_energy.push_back(energy_);
            }
	// fill hltMatchedVBFOneTight branches if match
            if (filterTag == hltMatchedVBFOneTight_Tag && passhltMatchedVBFOneTight && pt_>0) {
                hltMatchedVBFOneTight_pt.push_back(pt_);
                hltMatchedVBFOneTight_eta.push_back(eta_);
                hltMatchedVBFOneTight_phi.push_back(phi_);
		hltMatchedVBFOneTight_energy.push_back(energy_);
            }
	// fill hltHpsPFTau50Tight branches if match
	    if (filterTag == hltHpsPFTau50Tight_Tag && passhltHpsPFTau50Tight && pt_>0) {
		hltHpsPFTau50Tight_pt.push_back(pt_);
		hltHpsPFTau50Tight_eta.push_back(eta_);
		hltHpsPFTau50Tight_phi.push_back(phi_);
		hltHpsPFTau50Tight_energy.push_back(energy_);
	    }
	// fill hltMatchedVBFIsoTauTwoTight branches if match
	    if (filterTag == hltMatchedVBFIsoTauTwoTight_Tag && passhltMatchedVBFIsoTauTwoTight && pt_>0) {
		hltMatchedVBFIsoTauTwoTight_pt.push_back(pt_);
 		hltMatchedVBFIsoTauTwoTight_eta.push_back(eta_);
		hltMatchedVBFIsoTauTwoTight_phi.push_back(phi_);
		hltMatchedVBFIsoTauTwoTight_energy.push_back(energy_);
	    }
        // fill diTau35HLTFinalFilter branches if match
            if (filterTag == diTau35HLTFinalFilter_Tag && passDiTau35HLTFinalFilter && pt_>0) {
                diTau35HLTFinalFilter_pt.push_back(pt_);
                diTau35HLTFinalFilter_eta.push_back(eta_);
                diTau35HLTFinalFilter_phi.push_back(phi_);
                diTau35HLTFinalFilter_energy.push_back(energy_);
            }
	} // end loop over trigger object keys
    } // end loop over nfilters
} // end function
