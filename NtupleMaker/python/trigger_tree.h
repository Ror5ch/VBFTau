#ifndef trigger_tree_h
#define trigger_tree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>

class trigger_tree {
public :
    TTree	*fChain;
    Int_t	fCurrent;

    // from HLT
    int runNumber;
    int lumiBlock;
    unsigned long long eventNumberID; // sometimes needs to be int for older samples...

    int nEvents;

    int passDiTau35HLT;
    int passDeepDiTau35HLT;
    int passInclusiveVBFHLT;
    int passVBFPlusTwoTauHLT;
    int passVBFPlusTwoDeepTauHLT;
    int passVBFPlusOneTauHLT;

    int passVBF2DTHLT;
    int passVBF2DTTempLooseHLT;
    int passVBF2DTNoL2NNHLT;
    int passVBF2DTTempLooseNoL2NNHLT;


    // DiTau HLT initial and final branches
    int passhltL1sDoubleTauBigOR;
    std::vector<float>* hltL1sDoubleTauBigOR_pt = nullptr;
    std::vector<float>* hltL1sDoubleTauBigOR_eta = nullptr;
    std::vector<float>* hltL1sDoubleTauBigOR_phi = nullptr;
    std::vector<float>* hltL1sDoubleTauBigOR_energy = nullptr;

    int passhltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg;
    std::vector<float>* hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg_pt = nullptr;
    std::vector<float>* hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg_eta = nullptr;
    std::vector<float>* hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg_phi = nullptr;
    std::vector<float>* hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg_energy = nullptr;

    // Inclusive VBF and VBF Plus Two Tau Branches
    int passhltL1VBFDiJetOR;
    std::vector<float>* hltL1VBFDiJetOR_pt = nullptr;
    std::vector<float>* hltL1VBFDiJetOR_eta = nullptr;
    std::vector<float>* hltL1VBFDiJetOR_phi = nullptr;
    std::vector<float>* hltL1VBFDiJetOR_energy = nullptr;

    int passhltL1VBFDiJetIsoTau;
    std::vector<float>* hltL1VBFDiJetIsoTau_nJets = nullptr;
    std::vector<float>* hltL1VBFDiJetIsoTau_jetPt = nullptr;
    std::vector<float>* hltL1VBFDiJetIsoTau_jetEta = nullptr; 
    std::vector<float>* hltL1VBFDiJetIsoTau_jetPhi = nullptr; 
    std::vector<float>* hltL1VBFDiJetIsoTau_jetEnergy = nullptr; 
    std::vector<float>* hltL1VBFDiJetIsoTau_nTaus = nullptr;
    std::vector<float>* hltL1VBFDiJetIsoTau_tauPt = nullptr;
    std::vector<float>* hltL1VBFDiJetIsoTau_tauEta = nullptr; 
    std::vector<float>* hltL1VBFDiJetIsoTau_tauPhi = nullptr; 
    std::vector<float>* hltL1VBFDiJetIsoTau_tauEnergy = nullptr; 

    int passhltHpsDoublePFTau20;
    std::vector<float>* hltHpsDoublePFTau20_pt = nullptr;
    std::vector<float>* hltHpsDoublePFTau20_eta = nullptr;
    std::vector<float>* hltHpsDoublePFTau20_phi = nullptr;
    std::vector<float>* hltHpsDoublePFTau20_energy = nullptr;

    int passhltHpsDoublePFTau20TrackTightChargedIso;
    std::vector<float>* hltHpsDoublePFTau20TrackTightChargedIso_pt = nullptr;
    std::vector<float>* hltHpsDoublePFTau20TrackTightChargedIso_eta = nullptr;
    std::vector<float>* hltHpsDoublePFTau20TrackTightChargedIso_phi = nullptr;
    std::vector<float>* hltHpsDoublePFTau20TrackTightChargedIso_energy = nullptr;

    int passhltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon;
    std::vector<float>* hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_pt = nullptr;
    std::vector<float>* hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_eta = nullptr;
    std::vector<float>* hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_phi = nullptr;
    std::vector<float>* hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_energy = nullptr;

    int passhltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20;
    std::vector<float>* hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_pt = nullptr;
    std::vector<float>* hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_eta = nullptr;
    std::vector<float>* hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_phi = nullptr;
    std::vector<float>* hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_energy = nullptr;

    int passhltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20;
    std::vector<float>* hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_pt = nullptr;
    std::vector<float>* hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_eta = nullptr;
    std::vector<float>* hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_phi = nullptr;
    std::vector<float>* hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_energy = nullptr;

    int passhltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched;
    std::vector<float>* hltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched_pt = nullptr;
    std::vector<float>* hltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched_eta = nullptr; 
    std::vector<float>* hltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched_phi = nullptr; 
    std::vector<float>* hltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched_energy = nullptr;

    int passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20;
    std::vector<float>* hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_pt = nullptr;
    std::vector<float>* hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_eta = nullptr;
    std::vector<float>* hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_phi = nullptr;
    std::vector<float>* hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_energy = nullptr;

    // VBF Plus One Tau Branches
    int passhltHpsSinglePFTau20;
    std::vector<float>* hltHpsSinglePFTau20_pt = nullptr;
    std::vector<float>* hltHpsSinglePFTau20_eta = nullptr;
    std::vector<float>* hltHpsSinglePFTau20_phi = nullptr;
    std::vector<float>* hltHpsSinglePFTau20_energy = nullptr;

    int passhltHpsSinglePFTau20TrackTightChargedIso;
    std::vector<float>* hltHpsSinglePFTau20TrackTightChargedIso_pt = nullptr;
    std::vector<float>* hltHpsSinglePFTau20TrackTightChargedIso_eta = nullptr;
    std::vector<float>* hltHpsSinglePFTau20TrackTightChargedIso_phi = nullptr;
    std::vector<float>* hltHpsSinglePFTau20TrackTightChargedIso_energy = nullptr;

    int passhltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon;
    std::vector<float>* hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon_pt = nullptr;
    std::vector<float>* hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon_eta = nullptr;
    std::vector<float>* hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon_phi = nullptr;
    std::vector<float>* hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon_energy = nullptr;

    int passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20;
    std::vector<float>* hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20_pt = nullptr;
    std::vector<float>* hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20_eta = nullptr;
    std::vector<float>* hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20_phi = nullptr;
    std::vector<float>* hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20_energy = nullptr;
    //
    
    // VBF Plus Two Deep Tau Branches
    int passhltL2VBFIsoTauNNFilter;
    std::vector<float>* hltL2VBFIsoTauNNFilter_pt = nullptr;
    std::vector<float>* hltL2VBFIsoTauNNFilter_eta = nullptr;
    std::vector<float>* hltL2VBFIsoTauNNFilter_phi = nullptr;
    std::vector<float>* hltL2VBFIsoTauNNFilter_energy = nullptr;

    //
    int passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch;
    std::vector<float>* hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_pt = nullptr;
    std::vector<float>* hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_eta = nullptr;
    std::vector<float>* hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_phi = nullptr;
    std::vector<float>* hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_energy = nullptr;

    int passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN;
    std::vector<float>* hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_pt = nullptr;
    std::vector<float>* hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_eta = nullptr;
    std::vector<float>* hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_phi = nullptr;
    std::vector<float>* hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_energy = nullptr;

    int passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch;
    std::vector<float>* hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_pt = nullptr;
    std::vector<float>* hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_eta = nullptr;
    std::vector<float>* hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_phi = nullptr;
    std::vector<float>* hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_energy = nullptr;

    int passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN;
    std::vector<float>* hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_pt = nullptr;
    std::vector<float>* hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_eta = nullptr;
    std::vector<float>* hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_phi = nullptr;
    std::vector<float>* hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_energy = nullptr;

    //
    int passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched;
    std::vector<float>* hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_pt = nullptr;
    std::vector<float>* hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_eta = nullptr;
    std::vector<float>* hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_phi = nullptr;
    std::vector<float>* hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_energy = nullptr;

    int passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN;
    std::vector<float>* hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_pt = nullptr;
    std::vector<float>* hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_eta = nullptr;
    std::vector<float>* hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_phi = nullptr;
    std::vector<float>* hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_energy = nullptr;

    int passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched;
    std::vector<float>* hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_pt = nullptr;
    std::vector<float>* hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_eta = nullptr;
    std::vector<float>* hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_phi = nullptr;
    std::vector<float>* hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_energy = nullptr;

    int passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN;
    std::vector<float>* hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_pt = nullptr;
    std::vector<float>* hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_eta = nullptr;
    std::vector<float>* hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_phi = nullptr;
    std::vector<float>* hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_energy = nullptr;

    //
    int passhltRealDijetFilter;
    std::vector<float>* hltRealDijetFilter_pt = nullptr;
    std::vector<float>* hltRealDijetFilter_eta = nullptr;
    std::vector<float>* hltRealDijetFilter_phi = nullptr;
    std::vector<float>* hltRealDijetFilter_energy = nullptr;

    int passhltVBFLooseIDPFDummyFilter;
    std::vector<float>* hltVBFLooseIDPFDummyFilter_pt = nullptr;
    std::vector<float>* hltVBFLooseIDPFDummyFilter_eta = nullptr;
    std::vector<float>* hltVBFLooseIDPFDummyFilter_phi = nullptr;
    std::vector<float>* hltVBFLooseIDPFDummyFilter_energy = nullptr;

    //
    int passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20;
    std::vector<float>* hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_pt = nullptr;
    std::vector<float>* hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_eta = nullptr;
    std::vector<float>* hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_phi = nullptr;
    std::vector<float>* hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_energy = nullptr;

    int passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN;
    std::vector<float>* hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_pt = nullptr;
    std::vector<float>* hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_eta = nullptr;
    std::vector<float>* hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_phi = nullptr;
    std::vector<float>* hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_energy = nullptr;

    int passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20;
    std::vector<float>* hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_pt = nullptr;
    std::vector<float>* hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_eta = nullptr;
    std::vector<float>* hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_phi = nullptr;
    std::vector<float>* hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_energy = nullptr;

    int passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN;
    std::vector<float>* hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_pt = nullptr;
    std::vector<float>* hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_eta = nullptr;
    std::vector<float>* hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_phi = nullptr;
    std::vector<float>* hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_energy = nullptr;

    // end HLT branches

    // from AOD
    // trigger primitives
    std::vector<float>* tauL1PrimitivesPt = nullptr;    
    std::vector<float>* tauL1PrimitivesEta = nullptr;    
    std::vector<float>* tauL1PrimitivesPhi = nullptr;    
    std::vector<float>* tauL1PrimitivesEnergy = nullptr;    
    std::vector<int>* tauL1PrimitivesIso = nullptr;    

    std::vector<float>* jetL1PrimitivesPt = nullptr;    
    std::vector<float>* jetL1PrimitivesEta = nullptr;    
    std::vector<float>* jetL1PrimitivesPhi = nullptr;    
    std::vector<float>* jetL1PrimitivesEnergy = nullptr;    

    std::vector<float>* jetPt = nullptr;
    std::vector<float>* jetEta = nullptr;
    std::vector<float>* jetPhi = nullptr;
    std::vector<float>* jetEn = nullptr;
    std::vector<float>* tauPt = nullptr;
    std::vector<float>* tauEta = nullptr;
    std::vector<float>* tauPhi = nullptr;
    std::vector<float>* tauEnergy = nullptr;

    std::vector<float>* jetID = nullptr;
    std::vector<float>* tauByVVVLooseDeepTau2017v2p1VSe = nullptr;
    std::vector<float>* tauByTightDeepTau2017v2p1VSmu = nullptr;
    std::vector<float>* tauByVLooseDeepTau2017v2p1VSmu = nullptr;
    std::vector<float>* tauByMediumDeepTau2017v2p1VSjet = nullptr;
    std::vector<float>* tauByVVVLooseDeepTau2017v2p1VSjet = nullptr;
    // end AOD branches
    //int 	nTau;

    trigger_tree(TTree *tree=0);
    virtual ~trigger_tree();
    virtual void	Init(TTree *tree);
    virtual Int_t	GetEntry(Long64_t entry);
    virtual Long64_t	GetEntries();
    TTree* GetTree();
};

trigger_tree::trigger_tree(TTree *tree) : fChain(0)
{
    Init(tree);
}

trigger_tree::~trigger_tree()
{

}

Int_t trigger_tree::GetEntry(Long64_t entry)
{
    if (!fChain) return 0;
    return fChain->GetEntry(entry);
}

Long64_t trigger_tree::GetEntries()
{
    return fChain->GetEntries();
}

TTree* trigger_tree::GetTree()
{
    return fChain;
}

void trigger_tree::Init(TTree *tree)
{
    if (!tree) return;
    fChain = tree;
    fCurrent = -1;

    // from HLT
    fChain->SetBranchAddress("runNumber", &runNumber);
    fChain->SetBranchAddress("lumiBlock", &lumiBlock);
    fChain->SetBranchAddress("eventNumberID", &eventNumberID);
    fChain->SetBranchAddress("nEvents", &nEvents);

    fChain->SetBranchAddress("passDiTau35HLT", &passDiTau35HLT);
    fChain->SetBranchAddress("passDeepDiTau35HLT", &passDeepDiTau35HLT);
    fChain->SetBranchAddress("passInclusiveVBFHLT", &passInclusiveVBFHLT);
    fChain->SetBranchAddress("passVBFPlusTwoTauHLT", &passVBFPlusTwoTauHLT);
    fChain->SetBranchAddress("passVBFPlusTwoDeepTauHLT", &passVBFPlusTwoDeepTauHLT);
    fChain->SetBranchAddress("passVBFPlusOneTauHLT", &passVBFPlusOneTauHLT);

    fChain->SetBranchAddress("passVBF2DTHLT", &passVBF2DTHLT);
    fChain->SetBranchAddress("passVBF2DTTempLooseHLT", &passVBF2DTTempLooseHLT);
    fChain->SetBranchAddress("passVBF2DTNoL2NNHLT", &passVBF2DTNoL2NNHLT);
    fChain->SetBranchAddress("passVBF2DTTempLooseNoL2NNHLT", &passVBF2DTTempLooseNoL2NNHLT);

    // DiTau HLT initial and final branches
    fChain->SetBranchAddress("passhltL1sDoubleTauBigOR", &passhltL1sDoubleTauBigOR);
    fChain->SetBranchAddress("hltL1sDoubleTauBigOR_pt", &hltL1sDoubleTauBigOR_pt);
    fChain->SetBranchAddress("hltL1sDoubleTauBigOR_eta", &hltL1sDoubleTauBigOR_eta);
    fChain->SetBranchAddress("hltL1sDoubleTauBigOR_phi", &hltL1sDoubleTauBigOR_phi);
    fChain->SetBranchAddress("hltL1sDoubleTauBigOR_energy", &hltL1sDoubleTauBigOR_energy);

    fChain->SetBranchAddress("passhltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg", &passhltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg);
    fChain->SetBranchAddress("hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg_pt", &hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg_pt);
    fChain->SetBranchAddress("hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg_eta", &hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg_eta);
    fChain->SetBranchAddress("hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg_phi", &hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg_phi);
    fChain->SetBranchAddress("hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg_energy", &hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg_energy);

    // Inclusive VBF and VBF Plus Two Tau Branches
    fChain->SetBranchAddress("passhltL1VBFDiJetOR", &passhltL1VBFDiJetOR);
    fChain->SetBranchAddress("hltL1VBFDiJetOR_pt", &hltL1VBFDiJetOR_pt);
    fChain->SetBranchAddress("hltL1VBFDiJetOR_eta", &hltL1VBFDiJetOR_eta);
    fChain->SetBranchAddress("hltL1VBFDiJetOR_phi", &hltL1VBFDiJetOR_phi);
    fChain->SetBranchAddress("hltL1VBFDiJetOR_energy", &hltL1VBFDiJetOR_energy);

    fChain->SetBranchAddress("passhltL1VBFDiJetIsoTau", &passhltL1VBFDiJetIsoTau);
    fChain->SetBranchAddress("hltL1VBFDiJetIsoTau_nJets", &hltL1VBFDiJetIsoTau_nJets);
    fChain->SetBranchAddress("hltL1VBFDiJetIsoTau_jetPt", &hltL1VBFDiJetIsoTau_jetPt);
    fChain->SetBranchAddress("hltL1VBFDiJetIsoTau_jetEta", &hltL1VBFDiJetIsoTau_jetEta);
    fChain->SetBranchAddress("hltL1VBFDiJetIsoTau_jetPhi", &hltL1VBFDiJetIsoTau_jetPhi);
    fChain->SetBranchAddress("hltL1VBFDiJetIsoTau_jetEnergy", &hltL1VBFDiJetIsoTau_jetEnergy);
    fChain->SetBranchAddress("hltL1VBFDiJetIsoTau_nTaus", &hltL1VBFDiJetIsoTau_nTaus);
    fChain->SetBranchAddress("hltL1VBFDiJetIsoTau_tauPt", &hltL1VBFDiJetIsoTau_tauPt);
    fChain->SetBranchAddress("hltL1VBFDiJetIsoTau_tauEta", &hltL1VBFDiJetIsoTau_tauEta);
    fChain->SetBranchAddress("hltL1VBFDiJetIsoTau_tauPhi", &hltL1VBFDiJetIsoTau_tauPhi);
    fChain->SetBranchAddress("hltL1VBFDiJetIsoTau_tauEnergy", &hltL1VBFDiJetIsoTau_tauEnergy);

    fChain->SetBranchAddress("passhltHpsDoublePFTau20", &passhltHpsDoublePFTau20);
    fChain->SetBranchAddress("hltHpsDoublePFTau20_pt", &hltHpsDoublePFTau20_pt);
    fChain->SetBranchAddress("hltHpsDoublePFTau20_eta", &hltHpsDoublePFTau20_eta);
    fChain->SetBranchAddress("hltHpsDoublePFTau20_phi", &hltHpsDoublePFTau20_phi);
    fChain->SetBranchAddress("hltHpsDoublePFTau20_energy", &hltHpsDoublePFTau20_energy);

    fChain->SetBranchAddress("passhltHpsDoublePFTau20TrackTightChargedIso", &passhltHpsDoublePFTau20TrackTightChargedIso);
    fChain->SetBranchAddress("hltHpsDoublePFTau20TrackTightChargedIso_pt", &hltHpsDoublePFTau20TrackTightChargedIso_pt);
    fChain->SetBranchAddress("hltHpsDoublePFTau20TrackTightChargedIso_eta", &hltHpsDoublePFTau20TrackTightChargedIso_eta);
    fChain->SetBranchAddress("hltHpsDoublePFTau20TrackTightChargedIso_phi", &hltHpsDoublePFTau20TrackTightChargedIso_phi);
    fChain->SetBranchAddress("hltHpsDoublePFTau20TrackTightChargedIso_energy", &hltHpsDoublePFTau20TrackTightChargedIso_energy);

    fChain->SetBranchAddress("passhltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon", &passhltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon);
    fChain->SetBranchAddress("hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_pt", &hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_pt);
    fChain->SetBranchAddress("hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_eta", &hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_eta);
    fChain->SetBranchAddress("hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_phi", &hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_phi);
    fChain->SetBranchAddress("hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_energy", &hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_energy);

    fChain->SetBranchAddress("passhltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20", &passhltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20);
    fChain->SetBranchAddress("hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_pt", &hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_pt);
    fChain->SetBranchAddress("hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_eta", &hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_eta);
    fChain->SetBranchAddress("hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_phi", &hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_phi);
    fChain->SetBranchAddress("hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_energy", &hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_energy);

    fChain->SetBranchAddress("passhltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20", &passhltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20);
    fChain->SetBranchAddress("hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_pt", &hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_pt);
    fChain->SetBranchAddress("hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_eta", &hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_eta);
    fChain->SetBranchAddress("hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_phi", &hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_phi);
    fChain->SetBranchAddress("hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_energy", &hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_energy);

    fChain->SetBranchAddress("passhltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched", &passhltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched);
    fChain->SetBranchAddress("hltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched_pt", &hltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched_pt);
    fChain->SetBranchAddress("hltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched_eta", &hltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched_eta);
    fChain->SetBranchAddress("hltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched_phi", &hltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched_phi);
    fChain->SetBranchAddress("hltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched_energy", &hltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched_energy);

    fChain->SetBranchAddress("passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20", &passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_pt", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_pt);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_eta", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_eta);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_phi", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_phi);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_energy", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_energy);

    // VBF Plus One Tau Branches
    fChain->SetBranchAddress("passhltHpsSinglePFTau20", &passhltHpsSinglePFTau20);
    fChain->SetBranchAddress("hltHpsSinglePFTau20_pt", &hltHpsSinglePFTau20_pt);
    fChain->SetBranchAddress("hltHpsSinglePFTau20_eta", &hltHpsSinglePFTau20_eta);
    fChain->SetBranchAddress("hltHpsSinglePFTau20_phi", &hltHpsSinglePFTau20_phi);
    fChain->SetBranchAddress("hltHpsSinglePFTau20_energy", &hltHpsSinglePFTau20_energy);

    fChain->SetBranchAddress("passhltHpsSinglePFTau20TrackTightChargedIso", &passhltHpsSinglePFTau20TrackTightChargedIso);
    fChain->SetBranchAddress("hltHpsSinglePFTau20TrackTightChargedIso_pt", &hltHpsSinglePFTau20TrackTightChargedIso_pt);
    fChain->SetBranchAddress("hltHpsSinglePFTau20TrackTightChargedIso_eta", &hltHpsSinglePFTau20TrackTightChargedIso_eta);
    fChain->SetBranchAddress("hltHpsSinglePFTau20TrackTightChargedIso_phi", &hltHpsSinglePFTau20TrackTightChargedIso_phi);
    fChain->SetBranchAddress("hltHpsSinglePFTau20TrackTightChargedIso_energy", &hltHpsSinglePFTau20TrackTightChargedIso_energy);

    fChain->SetBranchAddress("passhltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon", &passhltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon);
    fChain->SetBranchAddress("hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon_pt", &hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon_pt);
    fChain->SetBranchAddress("hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon_eta", &hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon_eta);
    fChain->SetBranchAddress("hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon_phi", &hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon_phi);
    fChain->SetBranchAddress("hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon_energy", &hltHpsSinglePFTau20TrackTightChargedIsoAgainstMuon_energy);

    fChain->SetBranchAddress("passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20", &passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20_pt", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20_pt);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20_eta", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20_eta);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20_phi", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20_phi);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20_energy", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromSingleTightChargedIsoPFTauHPS20_energy);

    // VBF Plus Two Deep Tau Branches
    fChain->SetBranchAddress("passhltL2VBFIsoTauNNFilter", &passhltL2VBFIsoTauNNFilter);
    fChain->SetBranchAddress("hltL2VBFIsoTauNNFilter_pt", &hltL2VBFIsoTauNNFilter_pt);
    fChain->SetBranchAddress("hltL2VBFIsoTauNNFilter_eta", &hltL2VBFIsoTauNNFilter_eta);
    fChain->SetBranchAddress("hltL2VBFIsoTauNNFilter_phi", &hltL2VBFIsoTauNNFilter_phi);
    fChain->SetBranchAddress("hltL2VBFIsoTauNNFilter_energy", &hltL2VBFIsoTauNNFilter_energy);

    //
    fChain->SetBranchAddress("passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch", &passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch);
    fChain->SetBranchAddress("hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_pt", &hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_pt);
    fChain->SetBranchAddress("hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_eta", &hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_eta);
    fChain->SetBranchAddress("hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_phi", &hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_phi);
    fChain->SetBranchAddress("hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_energy", &hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_energy);

    fChain->SetBranchAddress("passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN", &passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN);
    fChain->SetBranchAddress("hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_pt", &hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_pt);
    fChain->SetBranchAddress("hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_eta", &hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_eta);
    fChain->SetBranchAddress("hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_phi", &hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_phi);
    fChain->SetBranchAddress("hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_energy", &hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_energy);

    fChain->SetBranchAddress("passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch", &passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch);
    fChain->SetBranchAddress("hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_pt", &hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_pt);
    fChain->SetBranchAddress("hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_eta", &hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_eta);
    fChain->SetBranchAddress("hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_phi", &hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_phi);
    fChain->SetBranchAddress("hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_energy", &hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_energy);

    fChain->SetBranchAddress("passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN", &passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN);
    fChain->SetBranchAddress("hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_pt", &hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_pt);
    fChain->SetBranchAddress("hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_eta", &hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_eta);
    fChain->SetBranchAddress("hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_phi", &hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_phi);
    fChain->SetBranchAddress("hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_energy", &hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_energy);

    //
    fChain->SetBranchAddress("passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched", &passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched);
    fChain->SetBranchAddress("hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_pt", &hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_pt);
    fChain->SetBranchAddress("hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_eta", &hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_eta);
    fChain->SetBranchAddress("hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_phi", &hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_phi);
    fChain->SetBranchAddress("hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_energy", &hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_energy);

    fChain->SetBranchAddress("passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN", &passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN);
    fChain->SetBranchAddress("hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_pt", &hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_pt);
    fChain->SetBranchAddress("hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_eta", &hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_eta);
    fChain->SetBranchAddress("hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_phi", &hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_phi);
    fChain->SetBranchAddress("hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_energy", &hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_energy);

    fChain->SetBranchAddress("passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched", &passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched);
    fChain->SetBranchAddress("hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_pt", &hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_pt);
    fChain->SetBranchAddress("hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_eta", &hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_eta);
    fChain->SetBranchAddress("hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_phi", &hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_phi);
    fChain->SetBranchAddress("hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_energy", &hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_energy);

    fChain->SetBranchAddress("passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN", &passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN);
    fChain->SetBranchAddress("hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_pt", &hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_pt);
    fChain->SetBranchAddress("hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_eta", &hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_eta);
    fChain->SetBranchAddress("hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_phi", &hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_phi);
    fChain->SetBranchAddress("hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_energy", &hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_energy);

    //
    fChain->SetBranchAddress("passhltRealDijetFilter", &passhltRealDijetFilter);
    fChain->SetBranchAddress("hltRealDijetFilter_pt", &hltRealDijetFilter_pt);
    fChain->SetBranchAddress("hltRealDijetFilter_eta", &hltRealDijetFilter_eta);
    fChain->SetBranchAddress("hltRealDijetFilter_phi", &hltRealDijetFilter_phi);
    fChain->SetBranchAddress("hltRealDijetFilter_energy", &hltRealDijetFilter_energy);

    fChain->SetBranchAddress("passhltVBFLooseIDPFDummyFilter", &passhltVBFLooseIDPFDummyFilter);
    fChain->SetBranchAddress("hltVBFLooseIDPFDummyFilter_pt", &hltVBFLooseIDPFDummyFilter_pt);
    fChain->SetBranchAddress("hltVBFLooseIDPFDummyFilter_eta", &hltVBFLooseIDPFDummyFilter_eta);
    fChain->SetBranchAddress("hltVBFLooseIDPFDummyFilter_phi", &hltVBFLooseIDPFDummyFilter_phi);
    fChain->SetBranchAddress("hltVBFLooseIDPFDummyFilter_energy", &hltVBFLooseIDPFDummyFilter_energy);

    //
    fChain->SetBranchAddress("passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20", &passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_pt", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_pt);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_eta", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_eta);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_phi", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_phi);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_energy", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_energy);

    fChain->SetBranchAddress("passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN", &passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_pt", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_pt);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_eta", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_eta);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_phi", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_phi);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_energy", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_energy);


    fChain->SetBranchAddress("passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20", &passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_pt", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_pt);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_eta", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_eta);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_phi", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_phi);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_energy", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_energy);

    fChain->SetBranchAddress("passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN", &passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_pt", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_pt);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_eta", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_eta);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_phi", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_phi);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_energy", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_energy);


    // from AOD
    // trigger primitives
    fChain->SetBranchAddress("tauL1PrimitivesPt", &tauL1PrimitivesPt);
    fChain->SetBranchAddress("tauL1PrimitivesEta", &tauL1PrimitivesEta);
    fChain->SetBranchAddress("tauL1PrimitivesPhi", &tauL1PrimitivesPhi);
    fChain->SetBranchAddress("tauL1PrimitivesEnergy", &tauL1PrimitivesEnergy);
    fChain->SetBranchAddress("tauL1PrimitivesIso", &tauL1PrimitivesIso);

    fChain->SetBranchAddress("jetL1PrimitivesPt", &jetL1PrimitivesPt);
    fChain->SetBranchAddress("jetL1PrimitivesEta", &jetL1PrimitivesEta);
    fChain->SetBranchAddress("jetL1PrimitivesPhi", &jetL1PrimitivesPhi);
    fChain->SetBranchAddress("jetL1PrimitivesEnergy", &jetL1PrimitivesEnergy);

    fChain->SetBranchAddress("jetPt", &jetPt);
    fChain->SetBranchAddress("jetEta", &jetEta);
    fChain->SetBranchAddress("jetPhi", &jetPhi);
    fChain->SetBranchAddress("jetEn", &jetEn);
    fChain->SetBranchAddress("tauPt", &tauPt);
    fChain->SetBranchAddress("tauEta", &tauEta);
    fChain->SetBranchAddress("tauPhi", &tauPhi);
    fChain->SetBranchAddress("tauEnergy", &tauEnergy);
    
    fChain->SetBranchAddress("jetID", &jetID);
    fChain->SetBranchAddress("tauByVVVLooseDeepTau2017v2p1VSe", &tauByVVVLooseDeepTau2017v2p1VSe);
    fChain->SetBranchAddress("tauByTightDeepTau2017v2p1VSmu", &tauByTightDeepTau2017v2p1VSmu);
    fChain->SetBranchAddress("tauByVLooseDeepTau2017v2p1VSmu", &tauByVLooseDeepTau2017v2p1VSmu);
    fChain->SetBranchAddress("tauByVVVLooseDeepTau2017v2p1VSjet", &tauByVVVLooseDeepTau2017v2p1VSjet);
    fChain->SetBranchAddress("tauByMediumDeepTau2017v2p1VSjet", &tauByMediumDeepTau2017v2p1VSjet);
    // end AOD
}

#endif
