// Braden Allmond Nov 22nd 2021
// NtupleMaker
// Takes a dataset and makes a tree of branches filled with data
// In this case, our NtupleMaker is for an HLT study,
// so we have branches for multiple HLT filters. 
// Here's a diagram of "triggers" and "filters"
//   Trigger (HLT means High Level Trigger)
// ---------------------------------------------------------------------------
// |L1 Decision| Middle Filter 1| Middle Filter 2| Final Filter| HLT Decision|
// ---------------------------------------------------------------------------
// Some filters/modules are shared between HLT paths,
// meaning sometimes those filters are only triggered
// by one path and sometimes they're triggered by both.
// From one filter's information alone, it's not possible to 
// tell which path the filter was triggered by. If you want to 
// know which filter is triggered by which path, you have to
// daisy-chain the filter decisions for a path explcitly, 
// meaning you check each filter decision in a path before
// the one you care about. If filter in the path before the
// one you care about is passed, then the filter you're looking at
// was triggered in the path you're studying in. That would look
// like this.
//    SomeHLTPath
// -----------------
// |1|1|1|1|0|0|
// -----------------
// Above, we can see that the fourth filter was triggered by
// this path, because each filter before that was triggered
// by this path as well. If we somehow find something like 
// the following in our analysis
//   SomeOtherHLTPath
// -----------------
// |0|0|0|1|0|1|0|0|
// -----------------
// We can safely those filters were not triggered by the path
// we're looking at, and were instead triggered by a different
// path with shared modules. 
//
// Note: I changed all branch names to use exact module names from HLT.
// This seemed more straightforward than coming up with good variable names.
// I'll make a table/sheet of the module names and what they do.
// I'll also update all macros/trigger_trees/and analyzers that are
// affected by this branch name rewriting.
//
// InclusiveVBF = Old VBF = L1_DoubleJet_110_35_DoubleJet35_Mass_Min620
//   it's called inclusive VBF bc a two jet L1 seed includes VBF events with any final lepton state
// VBFPlusTwoTau = New VBF/Proposed VBF = L1_DoubleJet35_Mass_Min420_IsoTau45er2p1_RmvOl
//   includes VBF events with two hadronic taus in final lepton state
// VBFPlusOneTau = same L1 as above
//   includes VBF events with two hadronic taus, one hadronic tau one muon, or one hadronic tau one electron in final state

#include "VBFTau/NtupleMaker/plugins/NtupleMaker.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Common/interface/TriggerNames.h"

#include "DataFormats/Common/interface/TriggerResults.h"

using namespace std; // I think best practice is to include <vector> explicitly at the top of the file

int passDiTau35HLT;
int passDeepDiTau35HLT;
int passInclusiveVBFHLT;
int passVBFPlusTwoTauHLT;
int passVBFPlusOneTauHLT;
int passVBFPlusTwoDeepTauHLT;

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
int		passhltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg;
vector<float>	hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg_pt;
vector<float>	hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg_eta;
vector<float>	hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg_phi;
vector<float>	hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg_energy;

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

//hltHpsDoublePFTau20TrackTightChargedIso
int	passhltHpsDoublePFTau20TrackTightChargedIso;
vector<float>	hltHpsDoublePFTau20TrackTightChargedIso_pt;
vector<float>   hltHpsDoublePFTau20TrackTightChargedIso_eta;
vector<float>   hltHpsDoublePFTau20TrackTightChargedIso_phi;
vector<float>   hltHpsDoublePFTau20TrackTightChargedIso_energy;

//hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon
int	passhltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon;
vector<float>	hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_pt;
vector<float>	hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_eta;
vector<float>	hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_phi;
vector<float>	hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_energy;

//hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20
int	passhltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20;
vector<float>	hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_pt;
vector<float>	hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_eta;
vector<float>	hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_phi;
vector<float>	hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_energy;

//hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20
int	passhltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20;
vector<float> 	hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_pt;
vector<float> 	hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_eta;
vector<float> 	hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_phi;
vector<float>	hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_energy;

//hltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched
int	passhltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched;
vector<float> 	hltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched_pt;
vector<float> 	hltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched_eta;
vector<float> 	hltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched_phi;
vector<float> 	hltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched_energy;

//hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20
int	passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20;
vector<float> 	hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_pt;
vector<float> 	hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_eta;
vector<float> 	hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_phi;
vector<float> 	hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_energy;

//hltHpsSinglePFTau20
int passhltHpsSinglePFTau20;
vector<float>	hltHpsSinglePFTau20_pt;
vector<float>	hltHpsSinglePFTau20_eta;
vector<float>	hltHpsSinglePFTau20_phi;
vector<float>	hltHpsSinglePFTau20_energy;

//hltHpsSinglePFTau20TrackTightChargedIso
int passhltHpsSinglePFTau20TrackTightChargedIso;
vector<float> hltHpsSinglePFTau20TrackTightChargedIso_pt;
vector<float> hltHpsSinglePFTau20TrackTightChargedIso_eta;
vector<float> hltHpsSinglePFTau20TrackTightChargedIso_phi;
vector<float> hltHpsSinglePFTau20TrackTightChargedIso_energy;

//hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon
int passhltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon;
vector<float> hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon_pt;
vector<float> hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon_eta;
vector<float> hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon_phi;
vector<float> hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon_energy;

//hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20
int passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20;
vector<float> hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20_pt;
vector<float> hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20_eta;
vector<float> hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20_phi;
vector<float> hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20_energy;

//branches for VBFPlusTwoDeepTauHLT
int passhltL2VBFIsoTauNNFilter;
vector<float> hltL2VBFIsoTauNNFilter_pt;
vector<float> hltL2VBFIsoTauNNFilter_eta;
vector<float> hltL2VBFIsoTauNNFilter_phi;
vector<float> hltL2VBFIsoTauNNFilter_energy;

int passhltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau;
vector<float> hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_pt;
vector<float> hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_eta;
vector<float> hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_phi;
vector<float> hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_energy;

int passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch;
vector<float> hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_pt;
vector<float> hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_eta;
vector<float> hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_phi;
vector<float> hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_energy;

int passhltHpsL1VBFJetsAndIsoTauHLTDoublePFTauMediumDitauWPDeepTauMatch;
vector<float> hltHpsL1VBFJetsAndIsoTauHLTDoublePFTauMediumDitauWPDeepTauMatch_pt;
vector<float> hltHpsL1VBFJetsAndIsoTauHLTDoublePFTauMediumDitauWPDeepTauMatch_eta;
vector<float> hltHpsL1VBFJetsAndIsoTauHLTDoublePFTauMediumDitauWPDeepTauMatch_phi;
vector<float> hltHpsL1VBFJetsAndIsoTauHLTDoublePFTauMediumDitauWPDeepTauMatch_energy;

int passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched; // match tau
vector<float> hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_pt;
vector<float> hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_eta;
vector<float> hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_phi;
vector<float> hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_energy;

int passhltVBFIsoTauL1TLooseIDPFJetsMatching;
vector<float> hltVBFIsoTauL1TLooseIDPFJetsMatching_pt;
vector<float> hltVBFIsoTauL1TLooseIDPFJetsMatching_eta;
vector<float> hltVBFIsoTauL1TLooseIDPFJetsMatching_phi;
vector<float> hltVBFIsoTauL1TLooseIDPFJetsMatching_energy;

int passhltMatchedVBFIsoTauTwoPFJetsDoubleHpsDeepTauIsoPF25TauOverlapRemoval;
vector<float> hltMatchedVBFIsoTauTwoPFJetsDoubleHpsDeepTauIsoPF25TauOverlapRemoval_pt;
vector<float> hltMatchedVBFIsoTauTwoPFJetsDoubleHpsDeepTauIsoPF25TauOverlapRemoval_eta;
vector<float> hltMatchedVBFIsoTauTwoPFJetsDoubleHpsDeepTauIsoPF25TauOverlapRemoval_phi;
vector<float> hltMatchedVBFIsoTauTwoPFJetsDoubleHpsDeepTauIsoPF25TauOverlapRemoval_energy;

int passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20; // match jets
vector<float> hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_pt;
vector<float> hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_eta;
vector<float> hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_phi;
vector<float> hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_energy;


void NtupleMaker::branchesTriggers(TTree* tree){

    tree->Branch("nEvents", &nEvents);

    tree->Branch("passDiTau35HLT", &passDiTau35HLT);
    tree->Branch("passDeepDiTau35HLT", &passDeepDiTau35HLT);


    tree->Branch("passInclusiveVBFHLT", &passInclusiveVBFHLT);    
    
    tree->Branch("passVBFPlusTwoTauHLT", &passVBFPlusTwoTauHLT);
    tree->Branch("passVBFPlusTwoDeepTauHLT", &passVBFPlusTwoDeepTauHLT);

    tree->Branch("passVBFPlusOneTauHLT", &passVBFPlusOneTauHLT);

    tree->Branch("passhltL1sDoubleTauBigOR", &passhltL1sDoubleTauBigOR);
    tree->Branch("hltL1sDoubleTauBigOR_pt", &hltL1sDoubleTauBigOR_pt);
    tree->Branch("hltL1sDoubleTauBigOR_eta", &hltL1sDoubleTauBigOR_eta);
    tree->Branch("hltL1sDoubleTauBigOR_phi", &hltL1sDoubleTauBigOR_phi);
    tree->Branch("hltL1sDoubleTauBigOR_energy", &hltL1sDoubleTauBigOR_energy);

    // don't need the cutflow, so I'm only storing the final filter of DiTau35HLT which is used for HLT-AOD matching purposes
    tree->Branch("passhltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg", &passhltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg);  
    tree->Branch("hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg_pt", &hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg_pt);  
    tree->Branch("hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg_eta", &hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg_eta);  
    tree->Branch("hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg_phi", &hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg_phi);  
    tree->Branch("hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg_energy", &hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg_energy);  

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

    tree->Branch("passhltHpsDoublePFTau20TrackTightChargedIso", &passhltHpsDoublePFTau20TrackTightChargedIso);
    tree->Branch("hltHpsDoublePFTau20TrackTightChargedIso_pt", &hltHpsDoublePFTau20TrackTightChargedIso_pt);
    tree->Branch("hltHpsDoublePFTau20TrackTightChargedIso_eta", &hltHpsDoublePFTau20TrackTightChargedIso_eta);
    tree->Branch("hltHpsDoublePFTau20TrackTightChargedIso_phi", &hltHpsDoublePFTau20TrackTightChargedIso_phi);
    tree->Branch("hltHpsDoublePFTau20TrackTightChargedIso_energy", &hltHpsDoublePFTau20TrackTightChargedIso_energy);

    tree->Branch("passhltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon", &passhltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon);
    tree->Branch("hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_pt", &hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_pt);
    tree->Branch("hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_eta", &hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_eta);
    tree->Branch("hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_phi", &hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_phi);
    tree->Branch("hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_energy", &hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_energy);

    tree->Branch("passhltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20", &passhltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20);
    tree->Branch("hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_pt", &hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_pt);
    tree->Branch("hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_eta", &hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_eta);
    tree->Branch("hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_phi", &hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_phi);
    tree->Branch("hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_energy", &hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_energy);

    tree->Branch("passhltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20", &passhltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20);
    tree->Branch("hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_pt", &hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_pt);
    tree->Branch("hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_eta", &hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_eta);
    tree->Branch("hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_phi", &hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_phi);
    tree->Branch("hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_energy", &hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_energy);

    tree->Branch("passhltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched", &passhltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched);
    tree->Branch("hltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched_pt", &hltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched_pt);
    tree->Branch("hltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched_eta", &hltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched_eta);
    tree->Branch("hltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched_phi", &hltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched_phi);
    tree->Branch("hltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched_energy", &hltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched_energy);

    tree->Branch("passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20", &passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20);
    tree->Branch("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_pt", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_pt);
    tree->Branch("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_eta", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_eta);
    tree->Branch("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_phi", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_phi);
    tree->Branch("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_energy", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_energy);

    tree->Branch("passhltHpsSinglePFTau20", &passhltHpsSinglePFTau20);
    tree->Branch("hltHpsSinglePFTau20_pt", &hltHpsSinglePFTau20_pt);
    tree->Branch("hltHpsSinglePFTau20_eta", &hltHpsSinglePFTau20_eta);
    tree->Branch("hltHpsSinglePFTau20_phi", &hltHpsSinglePFTau20_phi);
    tree->Branch("hltHpsSinglePFTau20_energy", &hltHpsSinglePFTau20_energy);

    tree->Branch("passhltHpsSinglePFTau20TrackTightChargedIso", &passhltHpsSinglePFTau20TrackTightChargedIso);
    tree->Branch("hltHpsSinglePFTau20TrackTightChargedIso_pt", &hltHpsSinglePFTau20TrackTightChargedIso_pt);
    tree->Branch("hltHpsSinglePFTau20TrackTightChargedIso_eta", &hltHpsSinglePFTau20TrackTightChargedIso_eta);
    tree->Branch("hltHpsSinglePFTau20TrackTightChargedIso_phi", &hltHpsSinglePFTau20TrackTightChargedIso_phi);
    tree->Branch("hltHpsSinglePFTau20TrackTightChargedIso_energy", &hltHpsSinglePFTau20TrackTightChargedIso_energy);

    tree->Branch("passhltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon", &passhltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon);
    tree->Branch("hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon_pt", &hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon_pt);
    tree->Branch("hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon_eta", &hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon_eta);
    tree->Branch("hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon_phi", &hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon_phi);
    tree->Branch("hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon_energy", &hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon_energy);

    tree->Branch("passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20", &passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20);
    tree->Branch("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20_pt", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20_pt);
    tree->Branch("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20_eta", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20_eta);
    tree->Branch("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20_phi", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20_phi);
    tree->Branch("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20_energy", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20_energy);

    // VBFPlusTwoDeepTau HLT Modules
    tree->Branch("passhltL2VBFIsoTauNNFilter", &passhltL2VBFIsoTauNNFilter);
    tree->Branch("hltL2VBFIsoTauNNFilter_pt", &hltL2VBFIsoTauNNFilter_pt);
    tree->Branch("hltL2VBFIsoTauNNFilter_eta", &hltL2VBFIsoTauNNFilter_eta);
    tree->Branch("hltL2VBFIsoTauNNFilter_phi", &hltL2VBFIsoTauNNFilter_phi);
    tree->Branch("hltL2VBFIsoTauNNFilter_energy", &hltL2VBFIsoTauNNFilter_energy);

    tree->Branch("passhltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau", &passhltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau);
    tree->Branch("hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_pt", &hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_pt);
    tree->Branch("hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_eta", &hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_eta);
    tree->Branch("hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_phi", &hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_phi);
    tree->Branch("hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_energy", &hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_energy);
    
    tree->Branch("passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch", &passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch);
    tree->Branch("hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_pt", &hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_pt);
    tree->Branch("hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_eta", &hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_eta);
    tree->Branch("hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_phi", &hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_phi);
    tree->Branch("hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_energy", &hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_energy);

    tree->Branch("passhltHpsL1VBFJetsAndIsoTauHLTDoublePFTauMediumDitauWPDeepTauMatch", &passhltHpsL1VBFJetsAndIsoTauHLTDoublePFTauMediumDitauWPDeepTauMatch);
    tree->Branch("hltHpsL1VBFJetsAndIsoTauHLTDoublePFTauMediumDitauWPDeepTauMatch_pt", &hltHpsL1VBFJetsAndIsoTauHLTDoublePFTauMediumDitauWPDeepTauMatch_pt);
    tree->Branch("hltHpsL1VBFJetsAndIsoTauHLTDoublePFTauMediumDitauWPDeepTauMatch_eta", &hltHpsL1VBFJetsAndIsoTauHLTDoublePFTauMediumDitauWPDeepTauMatch_eta);
    tree->Branch("hltHpsL1VBFJetsAndIsoTauHLTDoublePFTauMediumDitauWPDeepTauMatch_phi", &hltHpsL1VBFJetsAndIsoTauHLTDoublePFTauMediumDitauWPDeepTauMatch_phi);
    tree->Branch("hltHpsL1VBFJetsAndIsoTauHLTDoublePFTauMediumDitauWPDeepTauMatch_energy", &hltHpsL1VBFJetsAndIsoTauHLTDoublePFTauMediumDitauWPDeepTauMatch_energy);

    tree->Branch("passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched", &passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched);
    tree->Branch("hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_pt", &hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_pt);
    tree->Branch("hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_eta", &hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_eta);
    tree->Branch("hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_phi", &hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_phi);
    tree->Branch("hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_energy", &hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_energy);

    tree->Branch("passhltVBFIsoTauL1TLooseIDPFJetsMatching", &passhltVBFIsoTauL1TLooseIDPFJetsMatching);
    tree->Branch("hltVBFIsoTauL1TLooseIDPFJetsMatching_pt", &hltVBFIsoTauL1TLooseIDPFJetsMatching_pt);
    tree->Branch("hltVBFIsoTauL1TLooseIDPFJetsMatching_eta", &hltVBFIsoTauL1TLooseIDPFJetsMatching_eta);
    tree->Branch("hltVBFIsoTauL1TLooseIDPFJetsMatching_phi", &hltVBFIsoTauL1TLooseIDPFJetsMatching_phi);
    tree->Branch("hltVBFIsoTauL1TLooseIDPFJetsMatching_energy", &hltVBFIsoTauL1TLooseIDPFJetsMatching_energy);

    tree->Branch("passhltMatchedVBFIsoTauTwoPFJetsDoubleHpsDeepTauIsoPF25TauOverlapRemoval", &passhltMatchedVBFIsoTauTwoPFJetsDoubleHpsDeepTauIsoPF25TauOverlapRemoval);
    tree->Branch("hltMatchedVBFIsoTauTwoPFJetsDoubleHpsDeepTauIsoPF25TauOverlapRemoval_pt", &hltMatchedVBFIsoTauTwoPFJetsDoubleHpsDeepTauIsoPF25TauOverlapRemoval_pt);
    tree->Branch("hltMatchedVBFIsoTauTwoPFJetsDoubleHpsDeepTauIsoPF25TauOverlapRemoval_eta", &hltMatchedVBFIsoTauTwoPFJetsDoubleHpsDeepTauIsoPF25TauOverlapRemoval_eta);
    tree->Branch("hltMatchedVBFIsoTauTwoPFJetsDoubleHpsDeepTauIsoPF25TauOverlapRemoval_phi", &hltMatchedVBFIsoTauTwoPFJetsDoubleHpsDeepTauIsoPF25TauOverlapRemoval_phi);
    tree->Branch("hltMatchedVBFIsoTauTwoPFJetsDoubleHpsDeepTauIsoPF25TauOverlapRemoval_energy", &hltMatchedVBFIsoTauTwoPFJetsDoubleHpsDeepTauIsoPF25TauOverlapRemoval_energy);

    tree->Branch("passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20", &passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20);
    tree->Branch("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_pt", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_pt);
    tree->Branch("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_eta", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_eta);
    tree->Branch("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_phi", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_phi);
    tree->Branch("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_energy", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_energy);
}

void NtupleMaker::fillTriggers(const edm::Event& iEvent){

    using namespace edm;

    // clearing vectors and initializing flags at the start of every event 
    nEvents = 0;

    passDiTau35HLT = 0;
    passDeepDiTau35HLT = 0;
    passInclusiveVBFHLT = 0; 
    passVBFPlusTwoTauHLT = 0;
    passVBFPlusTwoDeepTauHLT = 0;
    passVBFPlusOneTauHLT = 0;

    // DiTau 32 L1 branches (there's a big OR with multiple DiTaus, but 32 is the lowest)
    passhltL1sDoubleTauBigOR = 0;
    hltL1sDoubleTauBigOR_pt.clear();
    hltL1sDoubleTauBigOR_eta.clear();
    hltL1sDoubleTauBigOR_phi.clear();
    hltL1sDoubleTauBigOR_energy.clear();

    passhltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg = 0;
    hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg_pt.clear();
    hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg_eta.clear();
    hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg_phi.clear();
    hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg_energy.clear();

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

    passhltHpsDoublePFTau20TrackTightChargedIso = 0;
    hltHpsDoublePFTau20TrackTightChargedIso_pt.clear();
    hltHpsDoublePFTau20TrackTightChargedIso_eta.clear();
    hltHpsDoublePFTau20TrackTightChargedIso_phi.clear();
    hltHpsDoublePFTau20TrackTightChargedIso_energy.clear();

    passhltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon = 0;
    hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_pt.clear();
    hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_eta.clear();
    hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_phi.clear();
    hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_energy.clear();

    passhltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20 = 0;
    hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_pt.clear();
    hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_eta.clear();
    hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_phi.clear();
    hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_energy.clear();

    passhltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20 = 0;
    hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_pt.clear();
    hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_eta.clear();
    hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_phi.clear();
    hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_energy.clear();

    passhltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched = 0;
    hltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched_pt.clear();
    hltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched_eta.clear();
    hltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched_phi.clear();
    hltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched_energy.clear();

    passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20 = 0;
    hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_pt.clear();
    hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_eta.clear();
    hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_phi.clear();
    hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_energy.clear();

    passhltHpsSinglePFTau20 = 0;
    hltHpsSinglePFTau20_pt.clear();
    hltHpsSinglePFTau20_eta.clear();
    hltHpsSinglePFTau20_phi.clear();
    hltHpsSinglePFTau20_energy.clear();

    passhltHpsSinglePFTau20TrackTightChargedIso = 0;
    hltHpsSinglePFTau20TrackTightChargedIso_pt.clear();
    hltHpsSinglePFTau20TrackTightChargedIso_eta.clear();
    hltHpsSinglePFTau20TrackTightChargedIso_phi.clear();
    hltHpsSinglePFTau20TrackTightChargedIso_energy.clear();

    passhltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon = 0;
    hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon_pt.clear();
    hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon_eta.clear();
    hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon_phi.clear();
    hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon_energy.clear();

    passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20 = 0;
    hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20_pt.clear();
    hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20_eta.clear();
    hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20_phi.clear();
    hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20_energy.clear();

    passhltL2VBFIsoTauNNFilter = 0;
    hltL2VBFIsoTauNNFilter_pt.clear();
    hltL2VBFIsoTauNNFilter_eta.clear();
    hltL2VBFIsoTauNNFilter_phi.clear();
    hltL2VBFIsoTauNNFilter_energy.clear();

    passhltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau = 0;
    hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_pt.clear();
    hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_eta.clear();
    hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_phi.clear();
    hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_energy.clear();

    passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch = 0;
    hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_pt.clear();
    hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_eta.clear();
    hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_phi.clear();
    hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_energy.clear();

    passhltHpsL1VBFJetsAndIsoTauHLTDoublePFTauMediumDitauWPDeepTauMatch = 0;
    hltHpsL1VBFJetsAndIsoTauHLTDoublePFTauMediumDitauWPDeepTauMatch_pt.clear();
    hltHpsL1VBFJetsAndIsoTauHLTDoublePFTauMediumDitauWPDeepTauMatch_eta.clear();
    hltHpsL1VBFJetsAndIsoTauHLTDoublePFTauMediumDitauWPDeepTauMatch_phi.clear();
    hltHpsL1VBFJetsAndIsoTauHLTDoublePFTauMediumDitauWPDeepTauMatch_energy.clear();

    passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched = 0;
    hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_pt.clear();
    hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_eta.clear();
    hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_phi.clear();
    hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_energy.clear();

    passhltVBFIsoTauL1TLooseIDPFJetsMatching = 0;
    hltVBFIsoTauL1TLooseIDPFJetsMatching_pt.clear();
    hltVBFIsoTauL1TLooseIDPFJetsMatching_eta.clear();
    hltVBFIsoTauL1TLooseIDPFJetsMatching_phi.clear();
    hltVBFIsoTauL1TLooseIDPFJetsMatching_energy.clear();

    passhltMatchedVBFIsoTauTwoPFJetsDoubleHpsDeepTauIsoPF25TauOverlapRemoval = 0;
    hltMatchedVBFIsoTauTwoPFJetsDoubleHpsDeepTauIsoPF25TauOverlapRemoval_pt.clear();
    hltMatchedVBFIsoTauTwoPFJetsDoubleHpsDeepTauIsoPF25TauOverlapRemoval_eta.clear();
    hltMatchedVBFIsoTauTwoPFJetsDoubleHpsDeepTauIsoPF25TauOverlapRemoval_phi.clear();
    hltMatchedVBFIsoTauTwoPFJetsDoubleHpsDeepTauIsoPF25TauOverlapRemoval_energy.clear();

    passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20 = 0;
    hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_pt.clear();
    hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_eta.clear();
    hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_phi.clear();
    hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_energy.clear();

    // getting trigger results, following this page
    // https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideHLTAnalysis
    edm::Handle<edm::TriggerResults> triggerResults;
    iEvent.getByToken(triggerResultToken_, triggerResults);
    edm::Handle<trigger::TriggerEvent> triggerEvent;
    iEvent.getByToken(triggerEventToken_, triggerEvent);
    const edm::TriggerNames triggerNames_ = iEvent.triggerNames(*triggerResults);

    // saving trigger results to respective branches
    // DiTau35 HLT
    std::string pathNameDiTauTrig = "HLT_DoubleTightChargedIsoPFTauHPS35_Trk1_eta2p1_v1";
    passDiTau35HLT = triggerResults->accept(triggerNames_.triggerIndex(pathNameDiTauTrig));

    // DeepDiTau35 HLT
    std::string pathNameDeepDiTauTrig = "HLT_DoubleMediumDeepTauIsoPFTauHPS35_L2NN_eta2p1_v1";
    passDeepDiTau35HLT = triggerResults->accept(triggerNames_.triggerIndex(pathNameDeepDiTauTrig));

    // Inclusive VBF HLT
    std::string pathNameInclusiveVBF = "HLT_VBF_DoubleTightChargedIsoPFTauHPS20_Trk1_eta2p1_v1";
    passInclusiveVBFHLT = triggerResults->accept(triggerNames_.triggerIndex(pathNameInclusiveVBF));

    // VBF Plus Two Tau HLT
    std::string pathNameVBFPlusTwoTau = "HLT_VBF_TightChargedIsoPFTauHPS45_PFTauHPS20_Trk1_eta2p1_v1";
    passVBFPlusTwoTauHLT = triggerResults->accept(triggerNames_.triggerIndex(pathNameVBFPlusTwoTau));

    // VBF Plus Two Deep Tau HLT
    std::string pathNameVBFPlusTwoDeepTau = "HLT_VBF_DeepTau_ModifiedTightChargedIsoPFTauHPS45_PFTauHPS20_Trk1_eta2p1_v1";
    passVBFPlusTwoDeepTauHLT = triggerResults->accept(triggerNames_.triggerIndex(pathNameVBFPlusTwoDeepTau));

    // VBF Plus One Tau HLT
    std::string pathNameVBFPlusOneTau = "HLT_VBF_TightChargedIsoPFTauHPS45_Trk1_eta2p1_v1";
    passVBFPlusOneTauHLT = triggerResults->accept(triggerNames_.triggerIndex(pathNameVBFPlusOneTau));

    // filling branches with triggerObjs information, hltL1VBFDiJetIsoTau object info filled separately since it's a weird L1

    // getting trigger refs for hltL1VBFDiJetIsoTau filter's tau/jet splitting
    edm::Handle<trigger::TriggerEventWithRefs> triggerEventWithRefsHandle_;
    iEvent.getByToken(triggerEventWithRefsToken_, triggerEventWithRefsHandle_);
    const unsigned int filterIndex(triggerEventWithRefsHandle_->filterIndex(InputTag("hltL1VBFDiJetIsoTau", "", "MYOTHERHLT")));
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
        hltL1VBFDiJetIsoTau_nJets.push_back(nJets);
        for (unsigned int i = 0; i != nJets; ++i) {
	    hltL1VBFDiJetIsoTau_jetPt.push_back(jetCandRefVec[i]->pt());
	    hltL1VBFDiJetIsoTau_jetEta.push_back(jetCandRefVec[i]->eta());
   	    hltL1VBFDiJetIsoTau_jetPhi.push_back(jetCandRefVec[i]->phi());
   	    hltL1VBFDiJetIsoTau_jetEnergy.push_back(jetCandRefVec[i]->energy());
        }
    }

    const unsigned int nTaus(tvids.size());
    if (nTaus > 0) {
	hltL1VBFDiJetIsoTau_nTaus.push_back(nTaus);
	for (unsigned int i = 0; i != nTaus; ++i) {
	    hltL1VBFDiJetIsoTau_tauPt.push_back(tauCandRefVec[i]->pt());
	    hltL1VBFDiJetIsoTau_tauEta.push_back(tauCandRefVec[i]->eta());
   	    hltL1VBFDiJetIsoTau_tauPhi.push_back(tauCandRefVec[i]->phi());
   	    hltL1VBFDiJetIsoTau_tauEnergy.push_back(tauCandRefVec[i]->energy());
	}
    }

    // make strings to identify filter names
    const trigger::size_type nFilters(triggerEvent->sizeFilters());
    std::string hltL1sDoubleTauBigOR_Tag = "hltL1sDoubleTauBigOR::MYOTHERHLT"; // ditau L1
    std::string hltL1VBFDiJetOR_Tag = "hltL1VBFDiJetOR::MYOTHERHLT";		  // inclusive L1
    std::string hltL1VBFDiJetIsoTau_Tag = "hltL1VBFDiJetIsoTau::MYOTHERHLT";	  // proposed L1

    std::string hltHpsDoublePFTau20_Tag = "hltHpsDoublePFTau20::MYOTHERHLT";
    std::string hltHpsDoublePFTau20TrackTightChargedIso_Tag = "hltHpsDoublePFTau20TrackTightChargedIso::MYOTHERHLT";
    std::string hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_Tag = "hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon::MYOTHERHLT";
    std::string hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_Tag = "hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20::MYOTHERHLT";
    std::string hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_Tag = "hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20::MYOTHERHLT";
    std::string hltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched_Tag = "hltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched::MYOTHERHLT";
    std::string hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_Tag = "hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20::MYOTHERHLT";

    std::string hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg_Tag = "hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg::MYOTHERHLT";

    std::string hltHpsSinglePFTau20_Tag = "hltHpsSinglePFTau20::MYOTHERHLT";
    std::string hltHpsSinglePFTau20TrackTightChargedIso_Tag = "hltHpsSinglePFTau20TrackTightChargedIso::MYOTHERHLT";
    std::string hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon_Tag = "hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon::MYOTHERHLT";
    std::string hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20_Tag = "hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20::MYOTHERHLT";

    std::string hltL2VBFIsoTauNNFilter_Tag = "hltL2VBFIsoTauNNFilter::MYOTHERHLT";
    std::string hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_Tag = "hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau::MYOTHERHLT";
    std::string hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_Tag = "hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch::MYOTHERHLT";
    std::string hltHpsL1VBFJetsAndIsoTauHLTDoublePFTauMediumDitauWPDeepTauMatch_Tag = "hltHpsL1VBFJetsAndIsoTauHLTDoublePFTauMediumDitauWPDeepTauMatch::MYOTHERHLT";
    std::string hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_Tag = "hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched::MYOTHERHLT";
    std::string hltVBFIsoTauL1TLooseIDPFJetsMatching_Tag = "hltVBFIsoTauL1TLooseIDPFJetsMatching::MYOTHERHLT";
    std::string hltMatchedVBFIsoTauTwoPFJetsDoubleHpsDeepTauIsoPF25TauOverlapRemoval_Tag = "hltMatchedVBFIsoTauTwoPFJetsDoubleHpsDeepTauIsoPF25TauOverlapRemoval::MYOTHERHLT";
    std::string hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_Tag = "hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20::MYOTHERHLT";

    // accepted filters per event
    for(trigger::size_type iFilter=0; iFilter!=nFilters; ++iFilter) {
	std::string filterTag = triggerEvent->filterTag(iFilter).encode();
	trigger::Keys objectKeys = triggerEvent->filterKeys(iFilter);

	const trigger::TriggerObjectCollection& triggerObjects(triggerEvent->getObjects());
	// fill "pass filter" branches
	int nObjKeys = objectKeys.size();
	if (filterTag == hltL1VBFDiJetOR_Tag && nObjKeys >= 0) nEvents = 1; // accept pass or fail condition to fill nEvents

        // L1s
	if (filterTag == hltL1sDoubleTauBigOR_Tag && nObjKeys >= 2) passhltL1sDoubleTauBigOR = 1;
	if (filterTag == hltL1VBFDiJetOR_Tag && nObjKeys >= 2) passhltL1VBFDiJetOR = 1;
	if (filterTag == hltL1VBFDiJetIsoTau_Tag && hltL1VBFDiJetIsoTau_tauPt.size() >= 1
						 && hltL1VBFDiJetIsoTau_jetPt.size() >= 2) passhltL1VBFDiJetIsoTau = 1;

        // Inclusive/VBFPlusTwoTau Modules
	if (filterTag == hltHpsDoublePFTau20_Tag && nObjKeys >= 2) passhltHpsDoublePFTau20 = 1; 
	if (filterTag == hltHpsDoublePFTau20TrackTightChargedIso_Tag && nObjKeys >= 2) passhltHpsDoublePFTau20TrackTightChargedIso = 1;
	if (filterTag == hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_Tag && nObjKeys >= 2) passhltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon = 1;
	if (filterTag == hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_Tag && nObjKeys >= 2) passhltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20 = 1;
	if (filterTag == hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_Tag && nObjKeys >= 1) passhltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20 = 1;
	if (filterTag == hltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched_Tag && nObjKeys >= 1) passhltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched = 1;
	if (filterTag == hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_Tag && nObjKeys >= 2) passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20 = 1;

        // VBFPlusTwoDeepTau Modules
        if (filterTag == hltL2VBFIsoTauNNFilter_Tag && nObjKeys >= 1) passhltL2VBFIsoTauNNFilter = 1;
        if (filterTag == hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_Tag && nObjKeys >= 2) passhltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau = 1;
        if (filterTag == hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_Tag && nObjKeys >= 2) passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch = 1;
        if (filterTag == hltHpsL1VBFJetsAndIsoTauHLTDoublePFTauMediumDitauWPDeepTauMatch_Tag && nObjKeys >= 2) passhltHpsL1VBFJetsAndIsoTauHLTDoublePFTauMediumDitauWPDeepTauMatch = 1;
        if (filterTag == hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_Tag && nObjKeys >= 1) passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched = 1;
        if (filterTag == hltVBFIsoTauL1TLooseIDPFJetsMatching_Tag && nObjKeys >= 2) passhltVBFIsoTauL1TLooseIDPFJetsMatching = 1;
        if (filterTag == hltMatchedVBFIsoTauTwoPFJetsDoubleHpsDeepTauIsoPF25TauOverlapRemoval_Tag && nObjKeys >= 2) passhltMatchedVBFIsoTauTwoPFJetsDoubleHpsDeepTauIsoPF25TauOverlapRemoval = 1;
        if (filterTag == hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_Tag && nObjKeys >= 2) passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20 = 1;

        // VBFPlusOneTau Modules
        if (filterTag == hltHpsSinglePFTau20_Tag && nObjKeys >= 1) passhltHpsSinglePFTau20 = 1;
        if (filterTag == hltHpsSinglePFTau20TrackTightChargedIso_Tag && nObjKeys >= 1) passhltHpsSinglePFTau20TrackTightChargedIso = 1;
        if (filterTag == hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon_Tag && nObjKeys >= 1) passhltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon = 1;
        if (filterTag == hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20_Tag && nObjKeys >= 2) passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20 = 1;


        // DiTau35HLT Final Filter
        if (filterTag == hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg_Tag && nObjKeys >= 2) passhltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg = 1;

	//loop over trigger objects and store their kinematics to the proper filter branches
	for(trigger::size_type iKey=0; iKey < nObjKeys; ++iKey){
	    trigger::size_type objKey = objectKeys.at(iKey);
	    const trigger::TriggerObject& triggerObj(triggerObjects[objKey]);
	    pt_ = triggerObj.pt();
	    eta_ = triggerObj.eta();
	    phi_ = triggerObj.phi();
	    energy_ = triggerObj.energy();
	// fill ditau and inclusive L1 branches (proposed L1 branches filled separately because it has two types of objects)
	    if (filterTag == hltL1sDoubleTauBigOR_Tag 
                  && passhltL1sDoubleTauBigOR && pt_>0) {
		hltL1sDoubleTauBigOR_pt.push_back(pt_);
		hltL1sDoubleTauBigOR_eta.push_back(eta_);
		hltL1sDoubleTauBigOR_phi.push_back(phi_);
		hltL1sDoubleTauBigOR_energy.push_back(energy_);
	    }
	    if (filterTag == hltL1VBFDiJetOR_Tag 
                  && passhltL1VBFDiJetOR && pt_>0) {
		hltL1VBFDiJetOR_pt.push_back(pt_);
		hltL1VBFDiJetOR_eta.push_back(eta_);
		hltL1VBFDiJetOR_phi.push_back(phi_);
		hltL1VBFDiJetOR_energy.push_back(energy_);
	    }
	// fill hltHpsDoublePFTau20 branches if match
	    if (filterTag == hltHpsDoublePFTau20_Tag 
                  && passhltHpsDoublePFTau20 && pt_>0) {
		hltHpsDoublePFTau20_pt.push_back(pt_);
		hltHpsDoublePFTau20_eta.push_back(eta_);
		hltHpsDoublePFTau20_phi.push_back(phi_);
		hltHpsDoublePFTau20_energy.push_back(energy_);
	    }
	// fill hltHpsDoublePFTau20TrackTightChargedIso branches if match
	    if (filterTag == hltHpsDoublePFTau20TrackTightChargedIso_Tag 
                  && passhltHpsDoublePFTau20TrackTightChargedIso && pt_>0) {
		hltHpsDoublePFTau20TrackTightChargedIso_pt.push_back(pt_); 
		hltHpsDoublePFTau20TrackTightChargedIso_eta.push_back(eta_);
		hltHpsDoublePFTau20TrackTightChargedIso_phi.push_back(phi_);
		hltHpsDoublePFTau20TrackTightChargedIso_energy.push_back(energy_);
	    }
	// fill hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon branches if match
	    if (filterTag == hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_Tag 
                  && passhltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon && pt_>0) {
		hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_pt.push_back(pt_); 
		hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_eta.push_back(eta_);
		hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_phi.push_back(phi_);
		hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_energy.push_back(energy_);
	    }
	// fill hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20 branches if match
            if (filterTag == hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_Tag 
                  && passhltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20 && pt_>0) {
                hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_pt.push_back(pt_);
                hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_eta.push_back(eta_);
                hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_phi.push_back(phi_);
		hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_energy.push_back(energy_);
            }
	// fill hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20 branches if match
            if (filterTag == hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_Tag 
                  && passhltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20 && pt_>0) {
                hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_pt.push_back(pt_);
                hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_eta.push_back(eta_);
                hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_phi.push_back(phi_);
		hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_energy.push_back(energy_);
            }
	// fill hltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched branches if match
	    if (filterTag == hltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched_Tag 
                  && passhltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched && pt_>0) {
		hltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched_pt.push_back(pt_);
		hltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched_eta.push_back(eta_);
		hltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched_phi.push_back(phi_);
		hltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched_energy.push_back(energy_);
	    }
	// fill hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20 branches if match
	    if (filterTag == hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_Tag 
                  && passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20 && pt_>0) {
		hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_pt.push_back(pt_);
 		hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_eta.push_back(eta_);
		hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_phi.push_back(phi_);
		hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_energy.push_back(energy_);
	    }
        // fill hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg branches if match
            if (filterTag == hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg_Tag 
                  && passhltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg && pt_>0) {
                hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg_pt.push_back(pt_);
                hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg_eta.push_back(eta_);
                hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg_phi.push_back(phi_);
                hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg_energy.push_back(energy_);
            }
        // fill hltHpsSinglePFTau20 branches if match
            if (filterTag == hltHpsSinglePFTau20_Tag
                 && passhltHpsSinglePFTau20 && pt_>0) {
               hltHpsSinglePFTau20_pt.push_back(pt_);
               hltHpsSinglePFTau20_eta.push_back(eta_);
               hltHpsSinglePFTau20_phi.push_back(phi_);
               hltHpsSinglePFTau20_energy.push_back(energy_);
            }
        // fill hltHpsSinglePFTau20TrackTightChargedIso branches if match
            if (filterTag == hltHpsSinglePFTau20TrackTightChargedIso_Tag
                 && passhltHpsSinglePFTau20TrackTightChargedIso && pt_>0) {
               hltHpsSinglePFTau20TrackTightChargedIso_pt.push_back(pt_);
               hltHpsSinglePFTau20TrackTightChargedIso_eta.push_back(eta_);
               hltHpsSinglePFTau20TrackTightChargedIso_phi.push_back(phi_);
               hltHpsSinglePFTau20TrackTightChargedIso_energy.push_back(energy_);
            }
        // fill hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon branches if match
            if (filterTag == hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon_Tag 
                 && passhltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon && pt_>0) {
               hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon_pt.push_back(pt_);
               hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon_eta.push_back(eta_);
               hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon_phi.push_back(phi_);
               hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon_energy.push_back(energy_);
            } 
        // fill hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20 if match
            if (filterTag == hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20_Tag
                 && passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20 && pt_>0) {
               hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20_pt.push_back(pt_);
               hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20_eta.push_back(eta_);
               hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20_phi.push_back(phi_);
               hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20_energy.push_back(energy_);
            }        
        // fill hltL2VBFIsoTauNNFilter if match
            if (filterTag == hltL2VBFIsoTauNNFilter_Tag
                 && passhltL2VBFIsoTauNNFilter && pt_>0) {
               hltL2VBFIsoTauNNFilter_pt.push_back(pt_);
               hltL2VBFIsoTauNNFilter_eta.push_back(eta_);
               hltL2VBFIsoTauNNFilter_phi.push_back(phi_);
               hltL2VBFIsoTauNNFilter_energy.push_back(energy_);
            }
        // fill hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau if match
            if (filterTag == hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_Tag
                 && passhltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau && pt_>0) {
               hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_pt.push_back(pt_);
               hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_eta.push_back(eta_);
               hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_phi.push_back(phi_);
               hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_energy.push_back(energy_);
            }
        // fill hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch if match
            if (filterTag == hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_Tag
                 && passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch && pt_>0) {
               hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_pt.push_back(pt_);
               hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_eta.push_back(eta_);
               hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_phi.push_back(phi_);
               hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_energy.push_back(energy_);
            }
        // fill hltHpsL1VBFJetsAndIsoTauHLTDoublePFTauMediumDitauWPDeepTauMatch if match
            if (filterTag == hltHpsL1VBFJetsAndIsoTauHLTDoublePFTauMediumDitauWPDeepTauMatch_Tag
                 && passhltHpsL1VBFJetsAndIsoTauHLTDoublePFTauMediumDitauWPDeepTauMatch && pt_>0) {
               hltHpsL1VBFJetsAndIsoTauHLTDoublePFTauMediumDitauWPDeepTauMatch_pt.push_back(pt_);
               hltHpsL1VBFJetsAndIsoTauHLTDoublePFTauMediumDitauWPDeepTauMatch_eta.push_back(eta_);
               hltHpsL1VBFJetsAndIsoTauHLTDoublePFTauMediumDitauWPDeepTauMatch_phi.push_back(phi_);
               hltHpsL1VBFJetsAndIsoTauHLTDoublePFTauMediumDitauWPDeepTauMatch_energy.push_back(energy_);
            }
        // fill hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched if match
            if (filterTag == hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_Tag
                 && passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched && pt_>0) {
               hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_pt.push_back(pt_);
               hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_eta.push_back(eta_);
               hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_phi.push_back(phi_);
               hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_energy.push_back(energy_);
            }
        // fill hltVBFIsoTauL1TLooseIDPFJetsMatching if match
            if (filterTag == hltVBFIsoTauL1TLooseIDPFJetsMatching_Tag
                 && passhltVBFIsoTauL1TLooseIDPFJetsMatching && pt_>0) {
               hltVBFIsoTauL1TLooseIDPFJetsMatching_pt.push_back(pt_);
               hltVBFIsoTauL1TLooseIDPFJetsMatching_eta.push_back(eta_);
               hltVBFIsoTauL1TLooseIDPFJetsMatching_phi.push_back(phi_);
               hltVBFIsoTauL1TLooseIDPFJetsMatching_energy.push_back(energy_);
            }
        // fill hltMatchedVBFIsoTauTwoPFJetsDoubleHpsDeepTauIsoPF25TauOverlapRemoval if match
            if (filterTag == hltMatchedVBFIsoTauTwoPFJetsDoubleHpsDeepTauIsoPF25TauOverlapRemoval_Tag
                 && passhltMatchedVBFIsoTauTwoPFJetsDoubleHpsDeepTauIsoPF25TauOverlapRemoval && pt_>0) {
               hltMatchedVBFIsoTauTwoPFJetsDoubleHpsDeepTauIsoPF25TauOverlapRemoval_pt.push_back(pt_);
               hltMatchedVBFIsoTauTwoPFJetsDoubleHpsDeepTauIsoPF25TauOverlapRemoval_eta.push_back(eta_);
               hltMatchedVBFIsoTauTwoPFJetsDoubleHpsDeepTauIsoPF25TauOverlapRemoval_phi.push_back(phi_);
               hltMatchedVBFIsoTauTwoPFJetsDoubleHpsDeepTauIsoPF25TauOverlapRemoval_energy.push_back(energy_);
            }
        // fill hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20 if match
            if (filterTag == hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_Tag
                 && passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20 && pt_>0) {
               hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_pt.push_back(pt_);
               hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_eta.push_back(eta_);
               hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_phi.push_back(phi_);
               hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_energy.push_back(energy_);
            }

	} // end loop over trigger object keys
    } // end loop over nfilters
} // end function
