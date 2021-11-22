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

    int passDiTauTrig;
    int passOldTrigTight;
    int passNewTrigTight;

    int passhltL1VBFDiJetOR;
    std::vector<float>* hltL1VBFDiJetOR_pt = nullptr;
    std::vector<float>* hltL1VBFDiJetOR_eta = nullptr;
    std::vector<float>* hltL1VBFDiJetOR_phi = nullptr;
    std::vector<float>* hltL1VBFDiJetOR_energy = nullptr;

    int passDiTau35HLTFinalFilter;
    std::vector<float>* diTau35HLTFinalFilter_pt = nullptr;
    std::vector<float>* diTau35HLTFinalFilter_eta = nullptr;
    std::vector<float>* diTau35HLTFinalFilter_phi = nullptr;
    std::vector<float>* diTau35HLTFinalFilter_energy = nullptr;

    int passhltL1sDoubleTauBigOR;
    std::vector<float>* hltL1sDoubleTauBigOR_pt = nullptr;
    std::vector<float>* hltL1sDoubleTauBigOR_eta = nullptr;
    std::vector<float>* hltL1sDoubleTauBigOR_phi = nullptr;
    std::vector<float>* hltL1sDoubleTauBigOR_energy = nullptr;

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

    int passhltHpsDoublePFTauTight;
    std::vector<float>* hltHpsDoublePFTauTight_pt = nullptr;
    std::vector<float>* hltHpsDoublePFTauTight_eta = nullptr;
    std::vector<float>* hltHpsDoublePFTauTight_phi = nullptr;
    std::vector<float>* hltHpsDoublePFTauTight_energy = nullptr;

    int passhltHpsDoublePFTauAgainstMuonTight;
    std::vector<float>* hltHpsDoublePFTauAgainstMuonTight_pt = nullptr;
    std::vector<float>* hltHpsDoublePFTauAgainstMuonTight_eta = nullptr;
    std::vector<float>* hltHpsDoublePFTauAgainstMuonTight_phi = nullptr;
    std::vector<float>* hltHpsDoublePFTauAgainstMuonTight_energy = nullptr;

    int passhltMatchedVBFTwoTight;
    std::vector<float>* hltMatchedVBFTwoTight_pt = nullptr;
    std::vector<float>* hltMatchedVBFTwoTight_eta = nullptr;
    std::vector<float>* hltMatchedVBFTwoTight_phi = nullptr;
    std::vector<float>* hltMatchedVBFTwoTight_energy = nullptr;

    int passhltMatchedVBFOneTight;
    std::vector<float>* hltMatchedVBFOneTight_pt = nullptr;
    std::vector<float>* hltMatchedVBFOneTight_eta = nullptr;
    std::vector<float>* hltMatchedVBFOneTight_phi = nullptr;
    std::vector<float>* hltMatchedVBFOneTight_energy = nullptr;

    int passhltHpsPFTau50Tight;
    std::vector<float>* hltHpsPFTau50Tight_pt = nullptr;
    std::vector<float>* hltHpsPFTau50Tight_eta = nullptr; 
    std::vector<float>* hltHpsPFTau50Tight_phi = nullptr; 
    std::vector<float>* hltHpsPFTau50Tight_energy = nullptr;

    int passhltMatchedVBFIsoTauTwoTight;
    std::vector<float>* hltMatchedVBFIsoTauTwoTight_pt = nullptr;
    std::vector<float>* hltMatchedVBFIsoTauTwoTight_eta = nullptr;
    std::vector<float>* hltMatchedVBFIsoTauTwoTight_phi = nullptr;
    std::vector<float>* hltMatchedVBFIsoTauTwoTight_energy = nullptr;
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

    fChain->SetBranchAddress("passDiTauTrig", &passDiTauTrig);
    fChain->SetBranchAddress("passOldTrigTight", &passOldTrigTight);
    fChain->SetBranchAddress("passNewTrigTight", &passNewTrigTight);

    fChain->SetBranchAddress("passDiTau35HLTFinalFilter", &passDiTau35HLTFinalFilter);
    fChain->SetBranchAddress("diTau35HLTFinalFilter_pt", &diTau35HLTFinalFilter_pt);
    fChain->SetBranchAddress("diTau35HLTFinalFilter_eta", &diTau35HLTFinalFilter_eta);
    fChain->SetBranchAddress("diTau35HLTFinalFilter_phi", &diTau35HLTFinalFilter_phi);
    fChain->SetBranchAddress("diTau35HLTFinalFilter_energy", &diTau35HLTFinalFilter_energy);

    fChain->SetBranchAddress("passhltL1VBFDiJetOR", &passhltL1VBFDiJetOR);
    fChain->SetBranchAddress("hltL1VBFDiJetOR_pt", &hltL1VBFDiJetOR_pt);
    fChain->SetBranchAddress("hltL1VBFDiJetOR_eta", &hltL1VBFDiJetOR_eta);
    fChain->SetBranchAddress("hltL1VBFDiJetOR_phi", &hltL1VBFDiJetOR_phi);
    fChain->SetBranchAddress("hltL1VBFDiJetOR_energy", &hltL1VBFDiJetOR_energy);

    fChain->SetBranchAddress("passhltL1sDoubleTauBigOR", &passhltL1sDoubleTauBigOR);
    fChain->SetBranchAddress("hltL1sDoubleTauBigOR_pt", &hltL1sDoubleTauBigOR_pt);
    fChain->SetBranchAddress("hltL1sDoubleTauBigOR_eta", &hltL1sDoubleTauBigOR_eta);
    fChain->SetBranchAddress("hltL1sDoubleTauBigOR_phi", &hltL1sDoubleTauBigOR_phi);
    fChain->SetBranchAddress("hltL1sDoubleTauBigOR_energy", &hltL1sDoubleTauBigOR_energy);

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

    fChain->SetBranchAddress("passhltHpsDoublePFTauTight", &passhltHpsDoublePFTauTight);
    fChain->SetBranchAddress("hltHpsDoublePFTauTight_pt", &hltHpsDoublePFTauTight_pt);
    fChain->SetBranchAddress("hltHpsDoublePFTauTight_eta", &hltHpsDoublePFTauTight_eta);
    fChain->SetBranchAddress("hltHpsDoublePFTauTight_phi", &hltHpsDoublePFTauTight_phi);
    fChain->SetBranchAddress("hltHpsDoublePFTauTight_energy", &hltHpsDoublePFTauTight_energy);

    fChain->SetBranchAddress("passhltHpsDoublePFTauAgainstMuonTight", &passhltHpsDoublePFTauAgainstMuonTight);
    fChain->SetBranchAddress("hltHpsDoublePFTauAgainstMuonTight_pt", &hltHpsDoublePFTauAgainstMuonTight_pt);
    fChain->SetBranchAddress("hltHpsDoublePFTauAgainstMuonTight_eta", &hltHpsDoublePFTauAgainstMuonTight_eta);
    fChain->SetBranchAddress("hltHpsDoublePFTauAgainstMuonTight_phi", &hltHpsDoublePFTauAgainstMuonTight_phi);
    fChain->SetBranchAddress("hltHpsDoublePFTauAgainstMuonTight_energy", &hltHpsDoublePFTauAgainstMuonTight_energy);

    fChain->SetBranchAddress("passhltMatchedVBFTwoTight", &passhltMatchedVBFTwoTight);
    fChain->SetBranchAddress("hltMatchedVBFTwoTight_pt", &hltMatchedVBFTwoTight_pt);
    fChain->SetBranchAddress("hltMatchedVBFTwoTight_eta", &hltMatchedVBFTwoTight_eta);
    fChain->SetBranchAddress("hltMatchedVBFTwoTight_phi", &hltMatchedVBFTwoTight_phi);
    fChain->SetBranchAddress("hltMatchedVBFTwoTight_energy", &hltMatchedVBFTwoTight_energy);

    fChain->SetBranchAddress("passhltMatchedVBFOneTight", &passhltMatchedVBFOneTight);
    fChain->SetBranchAddress("hltMatchedVBFOneTight_pt", &hltMatchedVBFOneTight_pt);
    fChain->SetBranchAddress("hltMatchedVBFOneTight_eta", &hltMatchedVBFOneTight_eta);
    fChain->SetBranchAddress("hltMatchedVBFOneTight_phi", &hltMatchedVBFOneTight_phi);
    fChain->SetBranchAddress("hltMatchedVBFOneTight_energy", &hltMatchedVBFOneTight_energy);

    fChain->SetBranchAddress("passhltHpsPFTau50Tight", &passhltHpsPFTau50Tight);
    fChain->SetBranchAddress("hltHpsPFTau50Tight_pt", &hltHpsPFTau50Tight_pt);
    fChain->SetBranchAddress("hltHpsPFTau50Tight_eta", &hltHpsPFTau50Tight_eta);
    fChain->SetBranchAddress("hltHpsPFTau50Tight_phi", &hltHpsPFTau50Tight_phi);
    fChain->SetBranchAddress("hltHpsPFTau50Tight_energy", &hltHpsPFTau50Tight_energy);

    fChain->SetBranchAddress("passhltMatchedVBFIsoTauTwoTight", &passhltMatchedVBFIsoTauTwoTight);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoTight_pt", &hltMatchedVBFIsoTauTwoTight_pt);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoTight_eta", &hltMatchedVBFIsoTauTwoTight_eta);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoTight_phi", &hltMatchedVBFIsoTauTwoTight_phi);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoTight_energy", &hltMatchedVBFIsoTauTwoTight_energy);

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
