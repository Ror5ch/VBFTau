// Braden Allmond 04/15/2021

#include "VBFTau/NtupleMaker/plugins/NtupleMaker.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Common/interface/TriggerNames.h"

using namespace std; // I think best practice is to include <vector> explicitly at the top of the file

//int runNumber;
//int lumiBlock;
//int eventNumberID;

bool passDitauTrig_;
vector<bool> passDitauTrig;

bool passOldTrigTight_;
bool passOldTrigMedium_;
bool passOldTrigLoose_;
vector<bool> passOldTrigTight;
vector<bool> passOldTrigMedium;
vector<bool> passOldTrigLoose;

bool passNewTrigTight_;
bool passNewTrigMedium_;
bool passNewTrigLoose_;
vector<bool> passNewTrigTight;
vector<bool> passNewTrigMedium;
vector<bool> passNewTrigLoose;

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
//filter has 3 working points
//hltHpsDoublePFTau20TrackTightChargedIso
int	passhltHpsDoublePFTauTight;
vector<float>	hltHpsDoublePFTauTight_pt;
vector<float>   hltHpsDoublePFTauTight_eta;
vector<float>   hltHpsDoublePFTauTight_phi;
vector<float>   hltHpsDoublePFTauTight_energy;
//hltHpsDoublePFTau20TrackMediumChargedIso
int     passhltHpsDoublePFTauMedium;
vector<float>   hltHpsDoublePFTauMedium_pt;
vector<float>   hltHpsDoublePFTauMedium_eta;
vector<float>   hltHpsDoublePFTauMedium_phi;
vector<float>   hltHpsDoublePFTauMedium_energy;
//hltHpsDoublePFTau20TrackLooseChargedIso
int     passhltHpsDoublePFTauLoose;
vector<float>   hltHpsDoublePFTauLoose_pt;
vector<float>   hltHpsDoublePFTauLoose_eta;
vector<float>   hltHpsDoublePFTauLoose_phi;
vector<float>   hltHpsDoublePFTauLoose_energy;
//
//filter has 3 working points
//hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon
int	passhltHpsDoublePFTauAgainstMuonTight;
vector<float>	hltHpsDoublePFTauAgainstMuonTight_pt;
vector<float>	hltHpsDoublePFTauAgainstMuonTight_eta;
vector<float>	hltHpsDoublePFTauAgainstMuonTight_phi;
vector<float>	hltHpsDoublePFTauAgainstMuonTight_energy;
//hltHpsDoublePFTau20TrackMediumChargedIsoAgainstMuon
int	passhltHpsDoublePFTauAgainstMuonMedium;
vector<float>	hltHpsDoublePFTauAgainstMuonMedium_pt;
vector<float>	hltHpsDoublePFTauAgainstMuonMedium_eta;
vector<float>	hltHpsDoublePFTauAgainstMuonMedium_phi;
vector<float>	hltHpsDoublePFTauAgainstMuonMedium_energy;
//hltHpsDoublePFTau20TrackLooseChargedIsoAgainstMuon
int	passhltHpsDoublePFTauAgainstMuonLoose;
vector<float>	hltHpsDoublePFTauAgainstMuonLoose_pt;
vector<float>	hltHpsDoublePFTauAgainstMuonLoose_eta;
vector<float>	hltHpsDoublePFTauAgainstMuonLoose_phi;
vector<float>	hltHpsDoublePFTauAgainstMuonLoose_energy;
//
//filter has 3 working points
//hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20
int	passhltMatchedVBFTwoTight;
vector<float>	hltMatchedVBFTwoTight_pt;
vector<float>	hltMatchedVBFTwoTight_eta;
vector<float>	hltMatchedVBFTwoTight_phi;
vector<float>	hltMatchedVBFTwoTight_energy;
//hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleMediumChargedIsoPFTauHPS20
int	passhltMatchedVBFTwoMedium;
vector<float>	hltMatchedVBFTwoMedium_pt;
vector<float>	hltMatchedVBFTwoMedium_eta;
vector<float>	hltMatchedVBFTwoMedium_phi;
vector<float>	hltMatchedVBFTwoMedium_energy;
//hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleLooseChargedIsoPFTauHPS20
int	passhltMatchedVBFTwoLoose;
vector<float>	hltMatchedVBFTwoLoose_pt;
vector<float>	hltMatchedVBFTwoLoose_eta;
vector<float>	hltMatchedVBFTwoLoose_phi;
vector<float>	hltMatchedVBFTwoLoose_energy;
//
//filter has 3 working points
//hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20
int	passhltMatchedVBFOneTight;
vector<float> 	hltMatchedVBFOneTight_pt;
vector<float> 	hltMatchedVBFOneTight_eta;
vector<float> 	hltMatchedVBFOneTight_phi;
vector<float>	hltMatchedVBFOneTight_energy;
//hltMatchedVBFOnePFJet2CrossCleanedFromDoubleMediumChargedIsoPFTauHPS20
int	passhltMatchedVBFOneMedium;
vector<float> 	hltMatchedVBFOneMedium_pt;
vector<float> 	hltMatchedVBFOneMedium_eta;
vector<float> 	hltMatchedVBFOneMedium_phi;
vector<float>	hltMatchedVBFOneMedium_energy;
//hltMatchedVBFOnePFJet2CrossCleanedFromDoubleLooseChargedIsoPFTauHPS20
int	passhltMatchedVBFOneLoose;
vector<float> 	hltMatchedVBFOneLoose_pt;
vector<float> 	hltMatchedVBFOneLoose_eta;
vector<float> 	hltMatchedVBFOneLoose_phi;
vector<float>	hltMatchedVBFOneLoose_energy;
//
// filter has 3 working points 
//hltHpsPFTau50TrackPt1TightChargedIsolationL1HLTMatched, renamed from hltHpsDoubleTightIsoAgainstMuonMatch
int	passhltHpsPFTau50Tight;
vector<float> 	hltHpsPFTau50Tight_pt;
vector<float> 	hltHpsPFTau50Tight_eta;
vector<float> 	hltHpsPFTau50Tight_phi;
vector<float> 	hltHpsPFTau50Tight_energy;
//hltHpsPFTau50TrackPt1MediumChargedIsolationL1HLTMatched, renamed from hltHpsDoubleMediumIsoAgainstMuonMatch
int	passhltHpsPFTau50Medium;
vector<float> 	hltHpsPFTau50Medium_pt;
vector<float> 	hltHpsPFTau50Medium_eta;
vector<float> 	hltHpsPFTau50Medium_phi;
vector<float> 	hltHpsPFTau50Medium_energy;
//hltHpsPFTau50TrackPt1LooseChargedIsolationL1HLTMatched, renamed from hltHpsDoubleLooseIsoAgainstMuonMatch
int	passhltHpsPFTau50Loose;
vector<float> 	hltHpsPFTau50Loose_pt;
vector<float> 	hltHpsPFTau50Loose_eta;
vector<float> 	hltHpsPFTau50Loose_phi;
vector<float> 	hltHpsPFTau50Loose_energy;
//
// filter has 3 working points
//hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20
int	passhltMatchedVBFIsoTauTwoTight;
vector<float> 	hltMatchedVBFIsoTauTwoTight_pt;
vector<float> 	hltMatchedVBFIsoTauTwoTight_eta;
vector<float> 	hltMatchedVBFIsoTauTwoTight_phi;
vector<float> 	hltMatchedVBFIsoTauTwoTight_energy;
//hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleMediumChargedIsoPFTauHPS20
int	passhltMatchedVBFIsoTauTwoMedium;
vector<float> 	hltMatchedVBFIsoTauTwoMedium_pt;
vector<float> 	hltMatchedVBFIsoTauTwoMedium_eta;
vector<float> 	hltMatchedVBFIsoTauTwoMedium_phi;
vector<float> 	hltMatchedVBFIsoTauTwoMedium_energy;
//hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleLooseChargedIsoPFTauHPS20
int	passhltMatchedVBFIsoTauTwoLoose;
vector<float> 	hltMatchedVBFIsoTauTwoLoose_pt;
vector<float> 	hltMatchedVBFIsoTauTwoLoose_eta;
vector<float> 	hltMatchedVBFIsoTauTwoLoose_phi;
vector<float> 	hltMatchedVBFIsoTauTwoLoose_energy;

// the taus/jets are the same objects and therefore have the same information,
// no matter if it's stored by the new or the old trigger
// The difference is the new trigger ends its filter without cutting off 115pt Jets,
// and it has a separate matching branch for taus (or a tau) at 50GeV
// Everything else is the same/shared btwn (HpsTauTracks for example)

void NtupleMaker::branchesTriggers(TTree* tree){

    tree->Branch("nEvents", &nEvents);

    //tree->Branch("runNumber", &runNumber);
    //tree->Branch("lumiBlock", &lumiBlock);
    //tree->Branch("eventNumberID", &eventNumberID);

    tree->Branch("passDitauTrig", &passDitauTrig);

    tree->Branch("passOldTrigTight", &passOldTrigTight);    
    tree->Branch("passOldTrigMedium", &passOldTrigMedium); 
    tree->Branch("passOldTrigLoose", &passOldTrigLoose); 
    
    tree->Branch("passNewTrigTight", &passNewTrigTight);
    tree->Branch("passNewTrigMedium", &passNewTrigMedium);
    tree->Branch("passNewTrigLoose", &passNewTrigLoose);

    tree->Branch("passhltL1sDoubleTauBigOR", &passhltL1sDoubleTauBigOR);
    tree->Branch("hltL1sDoubleTauBigOR_pt", &hltL1sDoubleTauBigOR_pt);
    tree->Branch("hltL1sDoubleTauBigOR_eta", &hltL1sDoubleTauBigOR_eta);
    tree->Branch("hltL1sDoubleTauBigOR_phi", &hltL1sDoubleTauBigOR_phi);
    tree->Branch("hltL1sDoubleTauBigOR_energy", &hltL1sDoubleTauBigOR_energy);

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

    tree->Branch("passhltHpsDoublePFTau20", &passhltHpsDoublePFTau20);
    tree->Branch("hltHpsDoublePFTau20_pt", &hltHpsDoublePFTau20_pt);
    tree->Branch("hltHpsDoublePFTau20_eta", &hltHpsDoublePFTau20_eta);
    tree->Branch("hltHpsDoublePFTau20_phi", &hltHpsDoublePFTau20_phi);
    tree->Branch("hltHpsDoublePFTau20_energy", &hltHpsDoublePFTau20_energy);

    //hltHpsDoublePFTau working points
    tree->Branch("passhltHpsDoublePFTauTight", &passhltHpsDoublePFTauTight);
    tree->Branch("hltHpsDoublePFTauTight_pt", &hltHpsDoublePFTauTight_pt);
    tree->Branch("hltHpsDoublePFTauTight_eta", &hltHpsDoublePFTauTight_eta);
    tree->Branch("hltHpsDoublePFTauTight_phi", &hltHpsDoublePFTauTight_phi);
    tree->Branch("hltHpsDoublePFTauTight_energy", &hltHpsDoublePFTauTight_energy);
    
    tree->Branch("passhltHpsDoublePFTauMedium", &passhltHpsDoublePFTauMedium);
    tree->Branch("hltHpsDoublePFTauMedium_pt", &hltHpsDoublePFTauMedium_pt);
    tree->Branch("hltHpsDoublePFTauMedium_eta", &hltHpsDoublePFTauMedium_eta);
    tree->Branch("hltHpsDoublePFTauMedium_phi", &hltHpsDoublePFTauMedium_phi);
    tree->Branch("hltHpsDoublePFTauMedium_energy", &hltHpsDoublePFTauMedium_energy);
    
    tree->Branch("passhltHpsDoublePFTauLoose", &passhltHpsDoublePFTauLoose);
    tree->Branch("hltHpsDoublePFTauLoose_pt", &hltHpsDoublePFTauLoose_pt);
    tree->Branch("hltHpsDoublePFTauLoose_eta", &hltHpsDoublePFTauLoose_eta);
    tree->Branch("hltHpsDoublePFTauLoose_phi", &hltHpsDoublePFTauLoose_phi);
    tree->Branch("hltHpsDoublePFTauLoose_energy", &hltHpsDoublePFTauLoose_energy);
    //
    //hltHpsDoublePFTauAgainstMuon working points
    tree->Branch("passhltHpsDoublePFTauAgainstMuonTight", &passhltHpsDoublePFTauAgainstMuonTight);
    tree->Branch("hltHpsDoublePFTauAgainstMuonTight_pt", &hltHpsDoublePFTauAgainstMuonTight_pt);
    tree->Branch("hltHpsDoublePFTauAgainstMuonTight_eta", &hltHpsDoublePFTauAgainstMuonTight_eta);
    tree->Branch("hltHpsDoublePFTauAgainstMuonTight_phi", &hltHpsDoublePFTauAgainstMuonTight_phi);
    tree->Branch("hltHpsDoublePFTauAgainstMuonTight_energy", &hltHpsDoublePFTauAgainstMuonTight_energy);

    tree->Branch("passhltHpsDoublePFTauAgainstMuonMedium", &passhltHpsDoublePFTauAgainstMuonMedium);
    tree->Branch("hltHpsDoublePFTauAgainstMuonMedium_pt", &hltHpsDoublePFTauAgainstMuonMedium_pt);
    tree->Branch("hltHpsDoublePFTauAgainstMuonMedium_eta", &hltHpsDoublePFTauAgainstMuonMedium_eta);
    tree->Branch("hltHpsDoublePFTauAgainstMuonMedium_phi", &hltHpsDoublePFTauAgainstMuonMedium_phi);
    tree->Branch("hltHpsDoublePFTauAgainstMuonMedium_energy", &hltHpsDoublePFTauAgainstMuonMedium_energy);

    tree->Branch("passhltHpsDoublePFTauAgainstMuonLoose", &passhltHpsDoublePFTauAgainstMuonLoose);
    tree->Branch("hltHpsDoublePFTauAgainstMuonLoose_pt", &hltHpsDoublePFTauAgainstMuonLoose_pt);
    tree->Branch("hltHpsDoublePFTauAgainstMuonLoose_eta", &hltHpsDoublePFTauAgainstMuonLoose_eta);
    tree->Branch("hltHpsDoublePFTauAgainstMuonLoose_phi", &hltHpsDoublePFTauAgainstMuonLoose_phi);
    tree->Branch("hltHpsDoublePFTauAgainstMuonLoose_energy", &hltHpsDoublePFTauAgainstMuonLoose_energy);
    //
    // hltMatchedVBFTwo working points
    tree->Branch("passhltMatchedVBFTwoTight", &passhltMatchedVBFTwoTight);
    tree->Branch("hltMatchedVBFTwoTight_pt", &hltMatchedVBFTwoTight_pt);
    tree->Branch("hltMatchedVBFTwoTight_eta", &hltMatchedVBFTwoTight_eta);
    tree->Branch("hltMatchedVBFTwoTight_phi", &hltMatchedVBFTwoTight_phi);
    tree->Branch("hltMatchedVBFTwoTight_energy", &hltMatchedVBFTwoTight_energy);

    tree->Branch("passhltMatchedVBFTwoMedium", &passhltMatchedVBFTwoMedium);
    tree->Branch("hltMatchedVBFTwoMedium_pt", &hltMatchedVBFTwoMedium_pt);
    tree->Branch("hltMatchedVBFTwoMedium_eta", &hltMatchedVBFTwoMedium_eta);
    tree->Branch("hltMatchedVBFTwoMedium_phi", &hltMatchedVBFTwoMedium_phi);
    tree->Branch("hltMatchedVBFTwoMedium_energy", &hltMatchedVBFTwoMedium_energy);

    tree->Branch("passhltMatchedVBFTwoLoose", &passhltMatchedVBFTwoLoose);
    tree->Branch("hltMatchedVBFTwoLoose_pt", &hltMatchedVBFTwoLoose_pt);
    tree->Branch("hltMatchedVBFTwoLoose_eta", &hltMatchedVBFTwoLoose_eta);
    tree->Branch("hltMatchedVBFTwoLoose_phi", &hltMatchedVBFTwoLoose_phi);
    tree->Branch("hltMatchedVBFTwoLoose_energy", &hltMatchedVBFTwoLoose_energy);
    //
    //hltMatchedVBFOne working points
    tree->Branch("passhltMatchedVBFOneTight", &passhltMatchedVBFOneTight);
    tree->Branch("hltMatchedVBFOneTight_pt", &hltMatchedVBFOneTight_pt);
    tree->Branch("hltMatchedVBFOneTight_eta", &hltMatchedVBFOneTight_eta);
    tree->Branch("hltMatchedVBFOneTight_phi", &hltMatchedVBFOneTight_phi);
    tree->Branch("hltMatchedVBFOneTight_energy", &hltMatchedVBFOneTight_energy);

    tree->Branch("passhltMatchedVBFOneMedium", &passhltMatchedVBFOneMedium);
    tree->Branch("hltMatchedVBFOneMedium_pt", &hltMatchedVBFOneMedium_pt);
    tree->Branch("hltMatchedVBFOneMedium_eta", &hltMatchedVBFOneMedium_eta);
    tree->Branch("hltMatchedVBFOneMedium_phi", &hltMatchedVBFOneMedium_phi);
    tree->Branch("hltMatchedVBFOneMedium_energy", &hltMatchedVBFOneMedium_energy);

    tree->Branch("passhltMatchedVBFOneLoose", &passhltMatchedVBFOneLoose);
    tree->Branch("hltMatchedVBFOneLoose_pt", &hltMatchedVBFOneLoose_pt);
    tree->Branch("hltMatchedVBFOneLoose_eta", &hltMatchedVBFOneLoose_eta);
    tree->Branch("hltMatchedVBFOneLoose_phi", &hltMatchedVBFOneLoose_phi);
    tree->Branch("hltMatchedVBFOneLoose_energy", &hltMatchedVBFOneLoose_energy);
    //
    //hltHpsPFTau50 working points
    tree->Branch("passhltHpsPFTau50Tight", &passhltHpsPFTau50Tight);
    tree->Branch("hltHpsPFTau50Tight_pt", &hltHpsPFTau50Tight_pt);
    tree->Branch("hltHpsPFTau50Tight_eta", &hltHpsPFTau50Tight_eta);
    tree->Branch("hltHpsPFTau50Tight_phi", &hltHpsPFTau50Tight_phi);
    tree->Branch("hltHpsPFTau50Tight_energy", &hltHpsPFTau50Tight_energy);

    tree->Branch("passhltHpsPFTau50Medium", &passhltHpsPFTau50Medium);
    tree->Branch("hltHpsPFTau50Medium_pt", &hltHpsPFTau50Medium_pt);
    tree->Branch("hltHpsPFTau50Medium_eta", &hltHpsPFTau50Medium_eta);
    tree->Branch("hltHpsPFTau50Medium_phi", &hltHpsPFTau50Medium_phi);
    tree->Branch("hltHpsPFTau50Medium_energy", &hltHpsPFTau50Medium_energy);

    tree->Branch("passhltHpsPFTau50Loose", &passhltHpsPFTau50Loose);
    tree->Branch("hltHpsPFTau50Loose_pt", &hltHpsPFTau50Loose_pt);
    tree->Branch("hltHpsPFTau50Loose_eta", &hltHpsPFTau50Loose_eta);
    tree->Branch("hltHpsPFTau50Loose_phi", &hltHpsPFTau50Loose_phi);
    tree->Branch("hltHpsPFTau50Loose_energy", &hltHpsPFTau50Loose_energy);
    //
    // hltMatchedVBFIsoTauTwo working points
    tree->Branch("passhltMatchedVBFIsoTauTwoTight", &passhltMatchedVBFIsoTauTwoTight);
    tree->Branch("hltMatchedVBFIsoTauTwoTight_pt", &hltMatchedVBFIsoTauTwoTight_pt);
    tree->Branch("hltMatchedVBFIsoTauTwoTight_eta", &hltMatchedVBFIsoTauTwoTight_eta);
    tree->Branch("hltMatchedVBFIsoTauTwoTight_phi", &hltMatchedVBFIsoTauTwoTight_phi);
    tree->Branch("hltMatchedVBFIsoTauTwoTight_energy", &hltMatchedVBFIsoTauTwoTight_energy);

    tree->Branch("passhltMatchedVBFIsoTauTwoMedium", &passhltMatchedVBFIsoTauTwoMedium);
    tree->Branch("hltMatchedVBFIsoTauTwoMedium_pt", &hltMatchedVBFIsoTauTwoMedium_pt);
    tree->Branch("hltMatchedVBFIsoTauTwoMedium_eta", &hltMatchedVBFIsoTauTwoMedium_eta);
    tree->Branch("hltMatchedVBFIsoTauTwoMedium_phi", &hltMatchedVBFIsoTauTwoMedium_phi);
    tree->Branch("hltMatchedVBFIsoTauTwoMedium_energy", &hltMatchedVBFIsoTauTwoMedium_energy);

    tree->Branch("passhltMatchedVBFIsoTauTwoLoose", &passhltMatchedVBFIsoTauTwoLoose);
    tree->Branch("hltMatchedVBFIsoTauTwoLoose_pt", &hltMatchedVBFIsoTauTwoLoose_pt);
    tree->Branch("hltMatchedVBFIsoTauTwoLoose_eta", &hltMatchedVBFIsoTauTwoLoose_eta);
    tree->Branch("hltMatchedVBFIsoTauTwoLoose_phi", &hltMatchedVBFIsoTauTwoLoose_phi);
    tree->Branch("hltMatchedVBFIsoTauTwoLoose_energy", &hltMatchedVBFIsoTauTwoLoose_energy);
}

void NtupleMaker::fillTriggers(const edm::Event& iEvent){

    using namespace edm;

    // clearing vectors at the start of every event 
    nEvents = 0;

    //runNumber = iEvent.id().run();
    //lumiBlock = iEvent.id().luminosityBlock();
    //eventNumberID = iEvent.id().event();

    passDitauTrig.clear();

    passOldTrigTight.clear(); 
    passOldTrigMedium.clear(); 
    passOldTrigLoose.clear(); 

    passNewTrigTight.clear();
    passNewTrigMedium.clear();
    passNewTrigLoose.clear();

    passhltL1sDoubleTauBigOR = 0;
    hltL1sDoubleTauBigOR_pt.clear();
    hltL1sDoubleTauBigOR_eta.clear();
    hltL1sDoubleTauBigOR_phi.clear();
    hltL1sDoubleTauBigOR_energy.clear();

    passhltL1VBFDiJetOR = 0;
    hltL1VBFDiJetOR_pt.clear();
    hltL1VBFDiJetOR_eta.clear();
    hltL1VBFDiJetOR_phi.clear();
    hltL1VBFDiJetOR_energy.clear();

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

    passhltHpsDoublePFTau20 = 0;
    hltHpsDoublePFTau20_pt.clear();
    hltHpsDoublePFTau20_eta.clear();
    hltHpsDoublePFTau20_phi.clear();
    hltHpsDoublePFTau20_energy.clear();

    // hltHpsDoublePFTau working points
    passhltHpsDoublePFTauTight = 0;
    hltHpsDoublePFTauTight_pt.clear();
    hltHpsDoublePFTauTight_eta.clear();
    hltHpsDoublePFTauTight_phi.clear();
    hltHpsDoublePFTauTight_energy.clear();

    passhltHpsDoublePFTauMedium = 0;
    hltHpsDoublePFTauMedium_pt.clear();
    hltHpsDoublePFTauMedium_eta.clear();
    hltHpsDoublePFTauMedium_phi.clear();
    hltHpsDoublePFTauMedium_energy.clear();

    passhltHpsDoublePFTauLoose = 0;
    hltHpsDoublePFTauLoose_pt.clear();
    hltHpsDoublePFTauLoose_eta.clear();
    hltHpsDoublePFTauLoose_phi.clear();
    hltHpsDoublePFTauLoose_energy.clear();

    // hltHpsDoublePFTauAgainstMuon working points
    passhltHpsDoublePFTauAgainstMuonTight = 0;
    hltHpsDoublePFTauAgainstMuonTight_pt.clear();
    hltHpsDoublePFTauAgainstMuonTight_eta.clear();
    hltHpsDoublePFTauAgainstMuonTight_phi.clear();
    hltHpsDoublePFTauAgainstMuonTight_energy.clear();

    passhltHpsDoublePFTauAgainstMuonMedium = 0;
    hltHpsDoublePFTauAgainstMuonMedium_pt.clear();
    hltHpsDoublePFTauAgainstMuonMedium_eta.clear();
    hltHpsDoublePFTauAgainstMuonMedium_phi.clear();
    hltHpsDoublePFTauAgainstMuonMedium_energy.clear();

    passhltHpsDoublePFTauAgainstMuonLoose = 0;
    hltHpsDoublePFTauAgainstMuonLoose_pt.clear();
    hltHpsDoublePFTauAgainstMuonLoose_eta.clear();
    hltHpsDoublePFTauAgainstMuonLoose_phi.clear();
    hltHpsDoublePFTauAgainstMuonLoose_energy.clear();

    //
    // hltMatchedVBFTwo working points
    passhltMatchedVBFTwoTight = 0;
    hltMatchedVBFTwoTight_pt.clear();
    hltMatchedVBFTwoTight_eta.clear();
    hltMatchedVBFTwoTight_phi.clear();
    hltMatchedVBFTwoTight_energy.clear();

    passhltMatchedVBFTwoMedium = 0;
    hltMatchedVBFTwoMedium_pt.clear();
    hltMatchedVBFTwoMedium_eta.clear();
    hltMatchedVBFTwoMedium_phi.clear();
    hltMatchedVBFTwoMedium_energy.clear();

    passhltMatchedVBFTwoLoose = 0;
    hltMatchedVBFTwoLoose_pt.clear();
    hltMatchedVBFTwoLoose_eta.clear();
    hltMatchedVBFTwoLoose_phi.clear();
    hltMatchedVBFTwoLoose_energy.clear();

    // 
    // hltMatchedVBFOne working points
    passhltMatchedVBFOneTight = 0;
    hltMatchedVBFOneTight_pt.clear();
    hltMatchedVBFOneTight_eta.clear();
    hltMatchedVBFOneTight_phi.clear();
    hltMatchedVBFOneTight_energy.clear();

    passhltMatchedVBFOneMedium = 0;
    hltMatchedVBFOneMedium_pt.clear();
    hltMatchedVBFOneMedium_eta.clear();
    hltMatchedVBFOneMedium_phi.clear();
    hltMatchedVBFOneMedium_energy.clear();
    
    passhltMatchedVBFOneLoose = 0;
    hltMatchedVBFOneLoose_pt.clear();
    hltMatchedVBFOneLoose_eta.clear();
    hltMatchedVBFOneLoose_phi.clear();
    hltMatchedVBFOneLoose_energy.clear(); 

    //
    // hltHpsPFTau50 working points
    passhltHpsPFTau50Tight = 0;
    hltHpsPFTau50Tight_pt.clear();
    hltHpsPFTau50Tight_eta.clear();
    hltHpsPFTau50Tight_phi.clear();
    hltHpsPFTau50Tight_energy.clear();

    passhltHpsPFTau50Medium = 0;
    hltHpsPFTau50Medium_pt.clear();
    hltHpsPFTau50Medium_eta.clear();
    hltHpsPFTau50Medium_phi.clear();
    hltHpsPFTau50Medium_energy.clear();
    
    passhltHpsPFTau50Loose = 0;
    hltHpsPFTau50Loose_pt.clear();
    hltHpsPFTau50Loose_eta.clear();
    hltHpsPFTau50Loose_phi.clear();
    hltHpsPFTau50Loose_energy.clear();

    //
    // hltMatchedVBFIsoTauTwo working points
    passhltMatchedVBFIsoTauTwoTight = 0;
    hltMatchedVBFIsoTauTwoTight_pt.clear();
    hltMatchedVBFIsoTauTwoTight_eta.clear();
    hltMatchedVBFIsoTauTwoTight_phi.clear();
    hltMatchedVBFIsoTauTwoTight_energy.clear();

    passhltMatchedVBFIsoTauTwoMedium = 0;
    hltMatchedVBFIsoTauTwoMedium_pt.clear();
    hltMatchedVBFIsoTauTwoMedium_eta.clear();
    hltMatchedVBFIsoTauTwoMedium_phi.clear();
    hltMatchedVBFIsoTauTwoMedium_energy.clear();

    passhltMatchedVBFIsoTauTwoLoose = 0;
    hltMatchedVBFIsoTauTwoLoose_pt.clear();
    hltMatchedVBFIsoTauTwoLoose_eta.clear();
    hltMatchedVBFIsoTauTwoLoose_phi.clear();
    hltMatchedVBFIsoTauTwoLoose_energy.clear();

    // getting trigger results, following this page
    // https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideHLTAnalysis
    edm::Handle<edm::TriggerResults> triggerResults;
    iEvent.getByToken(triggerResultToken_, triggerResults);
    edm::Handle<trigger::TriggerEvent> triggerEvent;
    iEvent.getByToken(triggerEventToken_, triggerEvent);
    const edm::TriggerNames triggerNames_ = iEvent.triggerNames(*triggerResults);

/***
    // saving trigger results to respective branches
    // just one ditau trigger
    std::string pathNameDitauTrig = "HLT_DoubleTightChargedIsoPFTauHPS40_Trk1_eta2p1_Reg_v1";
    passDitauTrig_ = triggerResults->accept(triggerNames_.triggerIndex(pathNameDitauTrig));
    passDitauTrig.push_back(passDitauTrig_);

    // for the VBF triggers, there are two triggers with three working points each
    std::string pathNameOldTrigTight = "HLT_VBF_DoubleTightChargedIsoPFTauHPS20_Trk1_eta2p1_v1";
    passOldTrigTight_ = triggerResults->accept(triggerNames_.triggerIndex(pathNameOldTrigTight));
    passOldTrigTight.push_back(passOldTrigTight_);
   
    std::string pathNameOldTrigMedium = "HLT_VBF_DoubleMediumChargedIsoPFTauHPS20_Trk1_eta2p1_v1";
    passOldTrigMedium_ = triggerResults->accept(triggerNames_.triggerIndex(pathNameOldTrigMedium));
    passOldTrigMedium.push_back(passOldTrigMedium_);

    std::string pathNameOldTrigLoose = "HLT_VBF_DoubleLooseChargedIsoPFTauHPS20_Trk1_eta2p1_v1";
    passOldTrigLoose_ = triggerResults->accept(triggerNames_.triggerIndex(pathNameOldTrigLoose));
    passOldTrigLoose.push_back(passOldTrigLoose_);

    std::string pathNameNewTrigTight = "HLT_VBF_TightChargedIsoPFTauHPS50_PFTauHPS20_Trk1_eta2p1_v1";
    passNewTrigTight_ = triggerResults->accept(triggerNames_.triggerIndex(pathNameNewTrigTight));
    passNewTrigTight.push_back(passNewTrigTight_);

    std::string pathNameNewTrigMedium = "HLT_VBF_MediumChargedIsoPFTauHPS50_PFTauHPS20_Trk1_eta2p1_v1";
    passNewTrigMedium_ = triggerResults->accept(triggerNames_.triggerIndex(pathNameNewTrigMedium));
    passNewTrigMedium.push_back(passNewTrigMedium_);

    std::string pathNameNewTrigLoose = "HLT_VBF_LooseChargedIsoPFTauHPS50_PFTauHPS20_Trk1_eta2p1_v1";
    passNewTrigLoose_ = triggerResults->accept(triggerNames_.triggerIndex(pathNameNewTrigLoose));
    passNewTrigLoose.push_back(passNewTrigLoose_);
***/

    // filling branches with triggerObjs information, hltL1VBFDiJetIsoTau object info filled separately since it's a weird trigger

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
    std::string hltL1sDoubleTauBigOR_Tag = "hltL1sDoubleTauBigOR::MYHLT"; // ditau trigger
    std::string hltL1VBFDiJetOR_Tag = "hltL1VBFDiJetOR::MYHLT";		  // old trigger
    std::string hltL1VBFDiJetIsoTau_Tag = "hltL1VBFDiJetIsoTau::MYHLT";	  // new trigger
    std::string hltHpsDoublePFTau20_Tag = "hltHpsDoublePFTau20::MYHLT";
    // hltHpsDoublePFTau working points
    std::string hltHpsDoublePFTauTight_Tag = "hltHpsDoublePFTau20TrackTightChargedIso::MYHLT";
    std::string hltHpsDoublePFTauMedium_Tag = "hltHpsDoublePFTau20TrackMediumChargedIso::MYHLT";
    std::string hltHpsDoublePFTauLoose_Tag = "hltHpsDoublePFTau20TrackLooseChargedIso::MYHLT";
    // 
    // hltHpsDoublePFTauAgainstMuon working points
    std::string hltHpsDoublePFTauAgainstMuonTight_Tag = "hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon::MYHLT";
    std::string hltHpsDoublePFTauAgainstMuonMedium_Tag = "hltHpsDoublePFTau20TrackMediumChargedIsoAgainstMuon::MYHLT";
    std::string hltHpsDoublePFTauAgainstMuonLoose_Tag = "hltHpsDoublePFTau20TrackLooseChargedIsoAgainstMuon::MYHLT";
    //
    // hltMatchedVBFTwo working points
    std::string hltMatchedVBFTwoTight_Tag = "hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20::MYHLT";
    std::string hltMatchedVBFTwoMedium_Tag = "hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleMediumChargedIsoPFTauHPS20::MYHLT";
    std::string hltMatchedVBFTwoLoose_Tag = "hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleLooseChargedIsoPFTauHPS20::MYHLT";
    //
    // hltMatchedVBFOne working points
    std::string hltMatchedVBFOneTight_Tag = "hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20::MYHLT";
    std::string hltMatchedVBFOneMedium_Tag = "hltMatchedVBFOnePFJet2CrossCleanedFromDoubleMediumChargedIsoPFTauHPS20::MYHLT";
    std::string hltMatchedVBFOneLoose_Tag = "hltMatchedVBFOnePFJet2CrossCleanedFromDoubleLooseChargedIsoPFTauHPS20::MYHLT";
    //
    //hltHpsPFTau50 working points, renamed from hltHpsDoubleTightIsoAgainstMuonMatch
    std::string hltHpsPFTau50Tight_Tag = "hltHpsPFTau50TrackPt1TightChargedIsolationL1HLTMatched::MYHLT";
    std::string hltHpsPFTau50Medium_Tag = "hltHpsPFTau50TrackPt1MediumChargedIsolationL1HLTMatched::MYHLT";
    std::string hltHpsPFTau50Loose_Tag = "hltHpsPFTau50TrackPt1LooseChargedIsolationL1HLTMatched::MYHLT";
    //
    // hltMatchedVBFIsoTauTwo working points
    std::string hltMatchedVBFIsoTauTwoTight_Tag = "hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20::MYHLT";
    std::string hltMatchedVBFIsoTauTwoMedium_Tag = "hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleMediumChargedIsoPFTauHPS20::MYHLT";
    std::string hltMatchedVBFIsoTauTwoLoose_Tag = "hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleLooseChargedIsoPFTauHPS20::MYHLT";

    // accepted filters per event
    for(trigger::size_type iFilter=0; iFilter!=nFilters; ++iFilter){
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
/***
	// hltHpsDoublePFTau20 filter to be replaced by hltHpsDoublePFTau filter
	if (filterTag == hltHpsDoublePFTau20_Tag && nObjKeys >= 2) passhltHpsDoublePFTau20 = 1; 
	// hltHpsDoublePFTau working points
	if (filterTag == hltHpsDoublePFTauTight_Tag && nObjKeys >= 2) passhltHpsDoublePFTauTight = 1;
	if (filterTag == hltHpsDoublePFTauMedium_Tag && nObjKeys >= 2) passhltHpsDoublePFTauMedium = 1;
	if (filterTag == hltHpsDoublePFTauLoose_Tag && nObjKeys >= 2) passhltHpsDoublePFTauLoose = 1;
	//	
	// hltHpsDoublePFTauAgainstMuon working points 
	if (filterTag == hltHpsDoublePFTauAgainstMuonTight_Tag && nObjKeys >= 2) passhltHpsDoublePFTauAgainstMuonTight = 1;
	if (filterTag == hltHpsDoublePFTauAgainstMuonMedium_Tag && nObjKeys >= 2) passhltHpsDoublePFTauAgainstMuonMedium = 1;
	if (filterTag == hltHpsDoublePFTauAgainstMuonLoose_Tag && nObjKeys >= 2) passhltHpsDoublePFTauAgainstMuonLoose = 1;
	//
	// hltMatchedVBFTwo working points
	if (filterTag == hltMatchedVBFTwoTight_Tag && nObjKeys >= 2) passhltMatchedVBFTwoTight = 1;
	if (filterTag == hltMatchedVBFTwoMedium_Tag && nObjKeys >= 2) passhltMatchedVBFTwoMedium = 1;
	if (filterTag == hltMatchedVBFTwoLoose_Tag && nObjKeys >= 2) passhltMatchedVBFTwoLoose = 1;
	//
	// hltMatchedVBFOne working points
	if (filterTag == hltMatchedVBFOneTight_Tag && nObjKeys >= 1) passhltMatchedVBFOneTight = 1;
	if (filterTag == hltMatchedVBFOneMedium_Tag && nObjKeys >= 1) passhltMatchedVBFOneMedium = 1;
	if (filterTag == hltMatchedVBFOneLoose_Tag && nObjKeys >= 1) passhltMatchedVBFOneLoose = 1;
	//
	// hltHpsPFTau50 working points
	if (filterTag == hltHpsPFTau50Tight_Tag && nObjKeys >= 1) passhltHpsPFTau50Tight = 1;
	if (filterTag == hltHpsPFTau50Medium_Tag && nObjKeys >= 1) passhltHpsPFTau50Medium = 1;
	if (filterTag == hltHpsPFTau50Loose_Tag && nObjKeys >= 1) passhltHpsPFTau50Loose = 1;
	//
	// hltMatchedVBFIsoTauTwo working points
	if (filterTag == hltMatchedVBFIsoTauTwoTight_Tag && nObjKeys >= 2) passhltMatchedVBFIsoTauTwoTight = 1;
	if (filterTag == hltMatchedVBFIsoTauTwoMedium_Tag && nObjKeys >= 2) passhltMatchedVBFIsoTauTwoMedium = 1;
	if (filterTag == hltMatchedVBFIsoTauTwoLoose_Tag && nObjKeys >= 2) passhltMatchedVBFIsoTauTwoLoose = 1;
***/

	//loop over trigger objects and store their kinematics to the proper filter branches
	for(trigger::size_type iKey=0; iKey < nObjKeys; ++iKey){
	    trigger::size_type objKey = objectKeys.at(iKey);
	    const trigger::TriggerObject& triggerObj(triggerObjects[objKey]);
	    pt_ = triggerObj.pt();
	    eta_ = triggerObj.eta();
	    phi_ = triggerObj.phi();
	    energy_ = triggerObj.energy();
	// fill ditau trig and old trig L1 branches (new trig L1 branches filled separately because it has two types of objects...)
	    if (filterTag == hltL1sDoubleTauBigOR_Tag && pt_>0){
		hltL1sDoubleTauBigOR_pt.push_back(pt_);
		hltL1sDoubleTauBigOR_eta.push_back(eta_);
		hltL1sDoubleTauBigOR_phi.push_back(phi_);
		hltL1sDoubleTauBigOR_energy.push_back(energy_);
	    }
	    if (filterTag == hltL1VBFDiJetOR_Tag && pt_>0){
		hltL1VBFDiJetOR_pt.push_back(pt_);
		hltL1VBFDiJetOR_eta.push_back(eta_);
		hltL1VBFDiJetOR_phi.push_back(phi_);
		hltL1VBFDiJetOR_energy.push_back(energy_);
	    }
/***
	// fill hltHpsDoublePFTau20 branches if match
	    if (filterTag == hltHpsDoublePFTau20_Tag && pt_>0){
		hltHpsDoublePFTau20_pt.push_back(pt_);
		hltHpsDoublePFTau20_eta.push_back(eta_);
		hltHpsDoublePFTau20_phi.push_back(phi_);
		hltHpsDoublePFTau20_energy.push_back(energy_);
	    }
	// hltHpsDoublePFTaIsoCharge working points
	// fill hltHpsDoublePFTauTight branches if match
	    if (filterTag == hltHpsDoublePFTauTight_Tag && pt_>0){
		hltHpsDoublePFTauTight_pt.push_back(pt_); 
		hltHpsDoublePFTauTight_eta.push_back(eta_);
		hltHpsDoublePFTauTight_phi.push_back(phi_);
		hltHpsDoublePFTauTight_energy.push_back(energy_);
	    }
	// fill hltHpsDoublePFTauMedium branches if match
	    if (filterTag == hltHpsDoublePFTauMedium_Tag && pt_>0){
		hltHpsDoublePFTauMedium_pt.push_back(pt_); 
		hltHpsDoublePFTauMedium_eta.push_back(eta_);
		hltHpsDoublePFTauMedium_phi.push_back(phi_);
		hltHpsDoublePFTauMedium_energy.push_back(energy_);
	    }
	// fill hltHpsDoublePFTauLoose branches if match
	    if (filterTag == hltHpsDoublePFTauLoose_Tag && pt_>0){
		hltHpsDoublePFTauLoose_pt.push_back(pt_); 
		hltHpsDoublePFTauLoose_eta.push_back(eta_);
		hltHpsDoublePFTauLoose_phi.push_back(phi_);
		hltHpsDoublePFTauLoose_energy.push_back(energy_);
	    }
	////
	// hltHpsDoublePFTauAgainstMuon working points
	// fill hltHpsDoublePFTauAgainstMuonTight branches if match
	    if (filterTag == hltHpsDoublePFTauAgainstMuonTight_Tag && pt_>0){
		hltHpsDoublePFTauAgainstMuonTight_pt.push_back(pt_); 
		hltHpsDoublePFTauAgainstMuonTight_eta.push_back(eta_);
		hltHpsDoublePFTauAgainstMuonTight_phi.push_back(phi_);
		hltHpsDoublePFTauAgainstMuonTight_energy.push_back(energy_);
	    }
	// fill hltHpsDoublePFTauAgainstMuonMedium branches if match
	    if (filterTag == hltHpsDoublePFTauAgainstMuonMedium_Tag && pt_>0){
		hltHpsDoublePFTauAgainstMuonMedium_pt.push_back(pt_); 
		hltHpsDoublePFTauAgainstMuonMedium_eta.push_back(eta_);
		hltHpsDoublePFTauAgainstMuonMedium_phi.push_back(phi_);
		hltHpsDoublePFTauAgainstMuonMedium_energy.push_back(energy_);
	    }
	// fill hltHpsDoublePFTauAgainstMuonLoose branches if match
	    if (filterTag == hltHpsDoublePFTauAgainstMuonLoose_Tag && pt_>0){
		hltHpsDoublePFTauAgainstMuonLoose_pt.push_back(pt_); 
		hltHpsDoublePFTauAgainstMuonLoose_eta.push_back(eta_);
		hltHpsDoublePFTauAgainstMuonLoose_phi.push_back(phi_);
		hltHpsDoublePFTauAgainstMuonLoose_energy.push_back(energy_);
	    }
	////
	// hltMatchedVBFTwo working points
	// fill hltMatchedVBFTwoTight branches if match
            if (filterTag == hltMatchedVBFTwoTight_Tag && pt_>0){
                hltMatchedVBFTwoTight_pt.push_back(pt_);
                hltMatchedVBFTwoTight_eta.push_back(eta_);
                hltMatchedVBFTwoTight_phi.push_back(phi_);
		hltMatchedVBFTwoTight_energy.push_back(energy_);
            }
	// fill hltMatchedVBFTwoMedium branches if match
            if (filterTag == hltMatchedVBFTwoMedium_Tag && pt_>0){
                hltMatchedVBFTwoMedium_pt.push_back(pt_);
                hltMatchedVBFTwoMedium_eta.push_back(eta_);
                hltMatchedVBFTwoMedium_phi.push_back(phi_);
		hltMatchedVBFTwoMedium_energy.push_back(energy_);
            }
	// fill hltMatchedVBFTwoLoose branches if match
            if (filterTag == hltMatchedVBFTwoLoose_Tag && pt_>0){
                hltMatchedVBFTwoLoose_pt.push_back(pt_);
                hltMatchedVBFTwoLoose_eta.push_back(eta_);
                hltMatchedVBFTwoLoose_phi.push_back(phi_);
		hltMatchedVBFTwoLoose_energy.push_back(energy_);
            }
	////
	// hltMatchedVBFOne working points
	// fill hltMatchedVBFOneTight branches if match
            if (filterTag == hltMatchedVBFOneTight_Tag && pt_>0){
                hltMatchedVBFOneTight_pt.push_back(pt_);
                hltMatchedVBFOneTight_eta.push_back(eta_);
                hltMatchedVBFOneTight_phi.push_back(phi_);
		hltMatchedVBFOneTight_energy.push_back(energy_);
            }
	// fill hltMatchedVBFOneMedium branches if match
            if (filterTag == hltMatchedVBFOneMedium_Tag && pt_>0){
                hltMatchedVBFOneMedium_pt.push_back(pt_);
                hltMatchedVBFOneMedium_eta.push_back(eta_);
                hltMatchedVBFOneMedium_phi.push_back(phi_);
		hltMatchedVBFOneMedium_energy.push_back(energy_);
            }
	// fill hltMatchedVBFOneLoose branches if match
            if (filterTag == hltMatchedVBFOneLoose_Tag && pt_>0){
                hltMatchedVBFOneLoose_pt.push_back(pt_);
                hltMatchedVBFOneLoose_eta.push_back(eta_);
                hltMatchedVBFOneLoose_phi.push_back(phi_);
		hltMatchedVBFOneLoose_energy.push_back(energy_);
            }
	////
	// fill hltHpsPFTau50Tight branches if match
	    if (filterTag == hltHpsPFTau50Tight_Tag && pt_>0){
		hltHpsPFTau50Tight_pt.push_back(pt_);
		hltHpsPFTau50Tight_eta.push_back(eta_);
		hltHpsPFTau50Tight_phi.push_back(phi_);
		hltHpsPFTau50Tight_energy.push_back(energy_);
	    }
	// fill hltHpsPFTau50Medium branches if match
	    if (filterTag == hltHpsPFTau50Medium_Tag && pt_>0){
		hltHpsPFTau50Medium_pt.push_back(pt_);
		hltHpsPFTau50Medium_eta.push_back(eta_);
		hltHpsPFTau50Medium_phi.push_back(phi_);
		hltHpsPFTau50Medium_energy.push_back(energy_);
	    }
	// fill hltHpsPFTau50Loose branches if match
	    if (filterTag == hltHpsPFTau50Loose_Tag && pt_>0){
		hltHpsPFTau50Loose_pt.push_back(pt_);
		hltHpsPFTau50Loose_eta.push_back(eta_);
		hltHpsPFTau50Loose_phi.push_back(phi_);
		hltHpsPFTau50Loose_energy.push_back(energy_);
	    }
	////
	//
	// hltMatchedVBFIsoTauTwo working points
	// fill hltMatchedVBFIsoTauTwoTight branches if match
	    if (filterTag == hltMatchedVBFIsoTauTwoTight_Tag && pt_>0){
		hltMatchedVBFIsoTauTwoTight_pt.push_back(pt_);
 		hltMatchedVBFIsoTauTwoTight_eta.push_back(eta_);
		hltMatchedVBFIsoTauTwoTight_phi.push_back(phi_);
		hltMatchedVBFIsoTauTwoTight_energy.push_back(energy_);
	    }
	// fill hltMatchedVBFIsoTauTwoMedium branches if match
	    if (filterTag == hltMatchedVBFIsoTauTwoMedium_Tag && pt_>0){
		hltMatchedVBFIsoTauTwoMedium_pt.push_back(pt_);
 		hltMatchedVBFIsoTauTwoMedium_eta.push_back(eta_);
		hltMatchedVBFIsoTauTwoMedium_phi.push_back(phi_);
		hltMatchedVBFIsoTauTwoMedium_energy.push_back(energy_);
	    }
	// fill hltMatchedVBFIsoTauTwoLoose branches if match
	    if (filterTag == hltMatchedVBFIsoTauTwoLoose_Tag && pt_>0){
		hltMatchedVBFIsoTauTwoLoose_pt.push_back(pt_);
 		hltMatchedVBFIsoTauTwoLoose_eta.push_back(eta_);
		hltMatchedVBFIsoTauTwoLoose_phi.push_back(phi_);
		hltMatchedVBFIsoTauTwoLoose_energy.push_back(energy_);
	    }
		***/
	} // end loop over trigger object keys
    } // end loop over nfilters
} // end function
