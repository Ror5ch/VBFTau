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
    std::vector<int>* nEvents = nullptr;

    std::vector<bool>* passOldTrigTight = nullptr;
    std::vector<bool>* passOldTrigMedium = nullptr;
    std::vector<bool>* passOldTrigLoose = nullptr;
    std::vector<bool>* passNewTrigTight = nullptr;
    std::vector<bool>* passNewTrigMedium = nullptr;
    std::vector<bool>* passNewTrigLoose = nullptr;

    std::vector<int>* passhltL1VBFDiJetOR = nullptr;
    std::vector<float>* hltL1VBFDiJetOR_pt = nullptr;
    std::vector<float>* hltL1VBFDiJetOR_eta = nullptr;
    std::vector<float>* hltL1VBFDiJetOR_phi = nullptr;
    std::vector<float>* hltL1VBFDiJetOR_energy = nullptr;

    std::vector<int>* passhltL1VBFDiJetIsoTau = nullptr;
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

    std::vector<int>* passhltHpsPFTauTrack = nullptr;
    std::vector<float>* hltHpsPFTauTrack_pt = nullptr;
    std::vector<float>* hltHpsPFTauTrack_eta = nullptr;
    std::vector<float>* hltHpsPFTauTrack_phi = nullptr;
    std::vector<float>* hltHpsPFTauTrack_energy = nullptr;

    // multiple working points
    std::vector<int>* passhltHpsDoublePFTauTight = nullptr;
    std::vector<float>* hltHpsDoublePFTauTight_pt = nullptr;
    std::vector<float>* hltHpsDoublePFTauTight_eta = nullptr;
    std::vector<float>* hltHpsDoublePFTauTight_phi = nullptr;
    std::vector<float>* hltHpsDoublePFTauTight_energy = nullptr;
    std::vector<int>* passhltHpsDoublePFTauMedium = nullptr;
    std::vector<float>* hltHpsDoublePFTauMedium_pt = nullptr;
    std::vector<float>* hltHpsDoublePFTauMedium_eta = nullptr;
    std::vector<float>* hltHpsDoublePFTauMedium_phi = nullptr;
    std::vector<float>* hltHpsDoublePFTauMedium_energy = nullptr;
    std::vector<int>* passhltHpsDoublePFTauLoose = nullptr;
    std::vector<float>* hltHpsDoublePFTauLoose_pt = nullptr;
    std::vector<float>* hltHpsDoublePFTauLoose_eta = nullptr;
    std::vector<float>* hltHpsDoublePFTauLoose_phi = nullptr;
    std::vector<float>* hltHpsDoublePFTauLoose_energy = nullptr;

    // multiple working points
    std::vector<int>* passhltHpsDoublePFTauAgainstMuonTight = nullptr;
    std::vector<float>* hltHpsDoublePFTauAgainstMuonTight_pt = nullptr;
    std::vector<float>* hltHpsDoublePFTauAgainstMuonTight_eta = nullptr;
    std::vector<float>* hltHpsDoublePFTauAgainstMuonTight_phi = nullptr;
    std::vector<float>* hltHpsDoublePFTauAgainstMuonTight_energy = nullptr;
    std::vector<int>* passhltHpsDoublePFTauAgainstMuonMedium = nullptr;
    std::vector<float>* hltHpsDoublePFTauAgainstMuonMedium_pt = nullptr;
    std::vector<float>* hltHpsDoublePFTauAgainstMuonMedium_eta = nullptr;
    std::vector<float>* hltHpsDoublePFTauAgainstMuonMedium_phi = nullptr;
    std::vector<float>* hltHpsDoublePFTauAgainstMuonMedium_energy = nullptr;
    std::vector<int>* passhltHpsDoublePFTauAgainstMuonLoose = nullptr;
    std::vector<float>* hltHpsDoublePFTauAgainstMuonLoose_pt = nullptr;
    std::vector<float>* hltHpsDoublePFTauAgainstMuonLoose_eta = nullptr;
    std::vector<float>* hltHpsDoublePFTauAgainstMuonLoose_phi = nullptr;
    std::vector<float>* hltHpsDoublePFTauAgainstMuonLoose_energy = nullptr;

    // multiple working points
    std::vector<int>* passhltHpsPFTau50Tight = nullptr;
    std::vector<float>* hltHpsPFTau50Tight_pt = nullptr;
    std::vector<float>* hltHpsPFTau50Tight_eta = nullptr; 
    std::vector<float>* hltHpsPFTau50Tight_phi = nullptr; 
    std::vector<float>* hltHpsPFTau50Tight_energy = nullptr;
    std::vector<int>* passhltHpsPFTau50Medium = nullptr;
    std::vector<float>* hltHpsPFTau50Medium_pt = nullptr;
    std::vector<float>* hltHpsPFTau50Medium_eta = nullptr; 
    std::vector<float>* hltHpsPFTau50Medium_phi = nullptr; 
    std::vector<float>* hltHpsPFTau50Medium_energy = nullptr; 
    std::vector<int>* passhltHpsPFTau50Loose = nullptr;
    std::vector<float>* hltHpsPFTau50Loose_pt = nullptr;
    std::vector<float>* hltHpsPFTau50Loose_eta = nullptr; 
    std::vector<float>* hltHpsPFTau50Loose_phi = nullptr; 
    std::vector<float>* hltHpsPFTau50Loose_energy = nullptr; 

    // multiple working points
    std::vector<int>* passhltMatchedVBFOneTight = nullptr;
    std::vector<float>* hltMatchedVBFOneTight_pt = nullptr;
    std::vector<float>* hltMatchedVBFOneTight_eta = nullptr;
    std::vector<float>* hltMatchedVBFOneTight_phi = nullptr;
    std::vector<float>* hltMatchedVBFOneTight_energy = nullptr;
    std::vector<int>* passhltMatchedVBFOneMedium = nullptr;
    std::vector<float>* hltMatchedVBFOneMedium_pt = nullptr;
    std::vector<float>* hltMatchedVBFOneMedium_eta = nullptr;
    std::vector<float>* hltMatchedVBFOneMedium_phi = nullptr;
    std::vector<float>* hltMatchedVBFOneMedium_energy = nullptr;
    std::vector<int>* passhltMatchedVBFOneLoose = nullptr;
    std::vector<float>* hltMatchedVBFOneLoose_pt = nullptr;
    std::vector<float>* hltMatchedVBFOneLoose_eta = nullptr;
    std::vector<float>* hltMatchedVBFOneLoose_phi = nullptr;
    std::vector<float>* hltMatchedVBFOneLoose_energy = nullptr;

    // multiple working points
    std::vector<int>* passhltMatchedVBFTwoTight = nullptr;
    std::vector<float>* hltMatchedVBFTwoTight_pt = nullptr;
    std::vector<float>* hltMatchedVBFTwoTight_eta = nullptr;
    std::vector<float>* hltMatchedVBFTwoTight_phi = nullptr;
    std::vector<float>* hltMatchedVBFTwoTight_energy = nullptr;
    std::vector<int>* passhltMatchedVBFTwoMedium = nullptr;
    std::vector<float>* hltMatchedVBFTwoMedium_pt = nullptr;
    std::vector<float>* hltMatchedVBFTwoMedium_eta = nullptr;
    std::vector<float>* hltMatchedVBFTwoMedium_phi = nullptr;
    std::vector<float>* hltMatchedVBFTwoMedium_energy = nullptr;
    std::vector<int>* passhltMatchedVBFTwoLoose = nullptr;
    std::vector<float>* hltMatchedVBFTwoLoose_pt = nullptr;
    std::vector<float>* hltMatchedVBFTwoLoose_eta = nullptr;
    std::vector<float>* hltMatchedVBFTwoLoose_phi = nullptr;
    std::vector<float>* hltMatchedVBFTwoLoose_energy = nullptr;

    // multiple working points
    std::vector<int>* passhltMatchedVBFIsoTauTwoTight = nullptr;
    std::vector<float>* hltMatchedVBFIsoTauTwoTight_pt = nullptr;
    std::vector<float>* hltMatchedVBFIsoTauTwoTight_eta = nullptr;
    std::vector<float>* hltMatchedVBFIsoTauTwoTight_phi = nullptr;
    std::vector<float>* hltMatchedVBFIsoTauTwoTight_energy = nullptr;
    std::vector<int>* passhltMatchedVBFIsoTauTwoMedium = nullptr;
    std::vector<float>* hltMatchedVBFIsoTauTwoMedium_pt = nullptr;
    std::vector<float>* hltMatchedVBFIsoTauTwoMedium_eta = nullptr;
    std::vector<float>* hltMatchedVBFIsoTauTwoMedium_phi = nullptr;
    std::vector<float>* hltMatchedVBFIsoTauTwoMedium_energy = nullptr;
    std::vector<int>* passhltMatchedVBFIsoTauTwoLoose = nullptr;
    std::vector<float>* hltMatchedVBFIsoTauTwoLoose_pt = nullptr;
    std::vector<float>* hltMatchedVBFIsoTauTwoLoose_eta = nullptr;
    std::vector<float>* hltMatchedVBFIsoTauTwoLoose_phi = nullptr;
    std::vector<float>* hltMatchedVBFIsoTauTwoLoose_energy = nullptr;
    // end HLT branches

    // from AOD
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
    fChain->SetBranchAddres("nEvents", &nEvents);

    fChain->SetBranchAddress("passOldTrigTight", &passOldTrigTight);
    fChain->SetBranchAddress("passOldTrigMedium", &passOldTrigMedium);
    fChain->SetBranchAddress("passOldTrigLoose", &passOldTrigLoose);
    fChain->SetBranchAddress("passNewTrigTight", &passNewTrigTight);
    fChain->SetBranchAddress("passNewTrigMedium", &passNewTrigMedium);
    fChain->SetBranchAddress("passNewTrigLoose", &passNewTrigLoose);

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

    fChain->SetBranchAddress("passhltHpsPFTauTrack", &passhltHpsPFTauTrack);
    fChain->SetBranchAddress("hltHpsPFTauTrack_pt", &hltHpsPFTauTrack_pt);
    fChain->SetBranchAddress("hltHpsPFTauTrack_eta", &hltHpsPFTauTrack_eta);
    fChain->SetBranchAddress("hltHpsPFTauTrack_phi", &hltHpsPFTauTrack_phi);
    fChain->SetBranchAddress("hltHpsPFTauTrack_energy", &hltHpsPFTauTrack_energy);

    // multiple working points
    fChain->SetBranchAddress("passhltHpsDoublePFTauTight", &passhltHpsDoublePFTauTight);
    fChain->SetBranchAddress("hltHpsDoublePFTauTight_pt", &hltHpsDoublePFTauTight_pt);
    fChain->SetBranchAddress("hltHpsDoublePFTauTight_eta", &hltHpsDoublePFTauTight_eta);
    fChain->SetBranchAddress("hltHpsDoublePFTauTight_phi", &hltHpsDoublePFTauTight_phi);
    fChain->SetBranchAddress("hltHpsDoublePFTauTight_energy", &hltHpsDoublePFTauTight_energy);
    fChain->SetBranchAddress("passhltHpsDoublePFTauMedium", &passhltHpsDoublePFTauMedium);
    fChain->SetBranchAddress("hltHpsDoublePFTauMedium_pt", &hltHpsDoublePFTauMedium_pt);
    fChain->SetBranchAddress("hltHpsDoublePFTauMedium_eta", &hltHpsDoublePFTauMedium_eta);
    fChain->SetBranchAddress("hltHpsDoublePFTauMedium_phi", &hltHpsDoublePFTauMedium_phi);
    fChain->SetBranchAddress("hltHpsDoublePFTauMedium_energy", &hltHpsDoublePFTauMedium_energy);
    fChain->SetBranchAddress("passhltHpsDoublePFTauLoose", &passhltHpsDoublePFTauLoose);
    fChain->SetBranchAddress("hltHpsDoublePFTauLoose_pt", &hltHpsDoublePFTauLoose_pt);
    fChain->SetBranchAddress("hltHpsDoublePFTauLoose_eta", &hltHpsDoublePFTauLoose_eta);
    fChain->SetBranchAddress("hltHpsDoublePFTauLoose_phi", &hltHpsDoublePFTauLoose_phi);
    fChain->SetBranchAddress("hltHpsDoublePFTauLoose_energy", &hltHpsDoublePFTauLoose_energy);

    // multiple working points
    fChain->SetBranchAddress("passhltHpsDoublePFTauAgainstMuonTight", &passhltHpsDoublePFTauAgainstMuonTight);
    fChain->SetBranchAddress("hltHpsDoublePFTauAgainstMuonTight_pt", &hltHpsDoublePFTauAgainstMuonTight_pt);
    fChain->SetBranchAddress("hltHpsDoublePFTauAgainstMuonTight_eta", &hltHpsDoublePFTauAgainstMuonTight_eta);
    fChain->SetBranchAddress("hltHpsDoublePFTauAgainstMuonTight_phi", &hltHpsDoublePFTauAgainstMuonTight_phi);
    fChain->SetBranchAddress("hltHpsDoublePFTauAgainstMuonTight_energy", &hltHpsDoublePFTauAgainstMuonTight_energy);
    fChain->SetBranchAddress("passhltHpsDoublePFTauAgainstMuonMedium", &passhltHpsDoublePFTauAgainstMuonMedium);
    fChain->SetBranchAddress("hltHpsDoublePFTauAgainstMuonMedium_pt", &hltHpsDoublePFTauAgainstMuonMedium_pt);
    fChain->SetBranchAddress("hltHpsDoublePFTauAgainstMuonMedium_eta", &hltHpsDoublePFTauAgainstMuonMedium_eta);
    fChain->SetBranchAddress("hltHpsDoublePFTauAgainstMuonMedium_phi", &hltHpsDoublePFTauAgainstMuonMedium_phi);
    fChain->SetBranchAddress("hltHpsDoublePFTauAgainstMuonMedium_energy", &hltHpsDoublePFTauAgainstMuonMedium_energy);
    fChain->SetBranchAddress("passhltHpsDoublePFTauAgainstMuonLoose", &passhltHpsDoublePFTauAgainstMuonLoose);
    fChain->SetBranchAddress("hltHpsDoublePFTauAgainstMuonLoose_pt", &hltHpsDoublePFTauAgainstMuonLoose_pt);
    fChain->SetBranchAddress("hltHpsDoublePFTauAgainstMuonLoose_eta", &hltHpsDoublePFTauAgainstMuonLoose_eta);
    fChain->SetBranchAddress("hltHpsDoublePFTauAgainstMuonLoose_phi", &hltHpsDoublePFTauAgainstMuonLoose_phi);
    fChain->SetBranchAddress("hltHpsDoublePFTauAgainstMuonLoose_energy", &hltHpsDoublePFTauAgainstMuonLoose_energy);

    // multiple working points
    fChain->SetBranchAddress("passhltHpsPFTau50Tight", &passhltHpsPFTau50Tight);
    fChain->SetBranchAddress("hltHpsPFTau50Tight_pt", &hltHpsPFTau50Tight_pt);
    fChain->SetBranchAddress("hltHpsPFTau50Tight_eta", &hltHpsPFTau50Tight_eta);
    fChain->SetBranchAddress("hltHpsPFTau50Tight_phi", &hltHpsPFTau50Tight_phi);
    fChain->SetBranchAddress("hltHpsPFTau50Tight_energy", &hltHpsPFTau50Tight_energy);
    fChain->SetBranchAddress("passhltHpsPFTau50Medium", &passhltHpsPFTau50Medium);
    fChain->SetBranchAddress("hltHpsPFTau50Medium_pt", &hltHpsPFTau50Medium_pt);
    fChain->SetBranchAddress("hltHpsPFTau50Medium_eta", &hltHpsPFTau50Medium_eta);
    fChain->SetBranchAddress("hltHpsPFTau50Medium_phi", &hltHpsPFTau50Medium_phi);
    fChain->SetBranchAddress("hltHpsPFTau50Medium_energy", &hltHpsPFTau50Medium_energy);
    fChain->SetBranchAddress("passhltHpsPFTau50Loose", &passhltHpsPFTau50Loose);
    fChain->SetBranchAddress("hltHpsPFTau50Loose_pt", &hltHpsPFTau50Loose_pt);
    fChain->SetBranchAddress("hltHpsPFTau50Loose_eta", &hltHpsPFTau50Loose_eta);
    fChain->SetBranchAddress("hltHpsPFTau50Loose_phi", &hltHpsPFTau50Loose_phi);
    fChain->SetBranchAddress("hltHpsPFTau50Loose_energy", &hltHpsPFTau50Loose_energy);

    // multiple working points
    fChain->SetBranchAddress("passhltMatchedVBFOneTight", &passhltMatchedVBFOneTight);
    fChain->SetBranchAddress("hltMatchedVBFOneTight_pt", &hltMatchedVBFOneTight_pt);
    fChain->SetBranchAddress("hltMatchedVBFOneTight_eta", &hltMatchedVBFOneTight_eta);
    fChain->SetBranchAddress("hltMatchedVBFOneTight_phi", &hltMatchedVBFOneTight_phi);
    fChain->SetBranchAddress("hltMatchedVBFOneTight_energy", &hltMatchedVBFOneTight_energy);
    fChain->SetBranchAddress("passhltMatchedVBFOneMedium", &passhltMatchedVBFOneMedium);
    fChain->SetBranchAddress("hltMatchedVBFOneMedium_pt", &hltMatchedVBFOneMedium_pt);
    fChain->SetBranchAddress("hltMatchedVBFOneMedium_eta", &hltMatchedVBFOneMedium_eta);
    fChain->SetBranchAddress("hltMatchedVBFOneMedium_phi", &hltMatchedVBFOneMedium_phi);
    fChain->SetBranchAddress("hltMatchedVBFOneMedium_energy", &hltMatchedVBFOneMedium_energy);
    fChain->SetBranchAddress("passhltMatchedVBFOneLoose", &passhltMatchedVBFOneLoose);
    fChain->SetBranchAddress("hltMatchedVBFOneLoose_pt", &hltMatchedVBFOneLoose_pt);
    fChain->SetBranchAddress("hltMatchedVBFOneLoose_eta", &hltMatchedVBFOneLoose_eta);
    fChain->SetBranchAddress("hltMatchedVBFOneLoose_phi", &hltMatchedVBFOneLoose_phi);
    fChain->SetBranchAddress("hltMatchedVBFOneLoose_energy", &hltMatchedVBFOneLoose_energy);

    // multiple working points
    fChain->SetBranchAddress("passhltMatchedVBFTwoTight", &passhltMatchedVBFTwoTight);
    fChain->SetBranchAddress("hltMatchedVBFTwoTight_pt", &hltMatchedVBFTwoTight_pt);
    fChain->SetBranchAddress("hltMatchedVBFTwoTight_eta", &hltMatchedVBFTwoTight_eta);
    fChain->SetBranchAddress("hltMatchedVBFTwoTight_phi", &hltMatchedVBFTwoTight_phi);
    fChain->SetBranchAddress("hltMatchedVBFTwoTight_energy", &hltMatchedVBFTwoTight_energy);
    fChain->SetBranchAddress("passhltMatchedVBFTwoMedium", &passhltMatchedVBFTwoMedium);
    fChain->SetBranchAddress("hltMatchedVBFTwoMedium_pt", &hltMatchedVBFTwoMedium_pt);
    fChain->SetBranchAddress("hltMatchedVBFTwoMedium_eta", &hltMatchedVBFTwoMedium_eta);
    fChain->SetBranchAddress("hltMatchedVBFTwoMedium_phi", &hltMatchedVBFTwoMedium_phi);
    fChain->SetBranchAddress("hltMatchedVBFTwoMedium_energy", &hltMatchedVBFTwoMedium_energy);
    fChain->SetBranchAddress("passhltMatchedVBFTwoLoose", &passhltMatchedVBFTwoLoose);
    fChain->SetBranchAddress("hltMatchedVBFTwoLoose_pt", &hltMatchedVBFTwoLoose_pt);
    fChain->SetBranchAddress("hltMatchedVBFTwoLoose_eta", &hltMatchedVBFTwoLoose_eta);
    fChain->SetBranchAddress("hltMatchedVBFTwoLoose_phi", &hltMatchedVBFTwoLoose_phi);
    fChain->SetBranchAddress("hltMatchedVBFTwoLoose_energy", &hltMatchedVBFTwoLoose_energy);

    // multiple working points
    fChain->SetBranchAddress("passhltMatchedVBFIsoTauTwoTight", &passhltMatchedVBFIsoTauTwoTight);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoTight_pt", &hltMatchedVBFIsoTauTwoTight_pt);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoTight_eta", &hltMatchedVBFIsoTauTwoTight_eta);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoTight_phi", &hltMatchedVBFIsoTauTwoTight_phi);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoTight_energy", &hltMatchedVBFIsoTauTwoTight_energy);
    fChain->SetBranchAddress("passhltMatchedVBFIsoTauTwoMedium", &passhltMatchedVBFIsoTauTwoMedium);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoMedium_pt", &hltMatchedVBFIsoTauTwoMedium_pt);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoMedium_eta", &hltMatchedVBFIsoTauTwoMedium_eta);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoMedium_phi", &hltMatchedVBFIsoTauTwoMedium_phi);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoMedium_energy", &hltMatchedVBFIsoTauTwoMedium_energy);
    fChain->SetBranchAddress("passhltMatchedVBFIsoTauTwoLoose", &passhltMatchedVBFIsoTauTwoLoose);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoLoose_pt", &hltMatchedVBFIsoTauTwoLoose_pt);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoLoose_eta", &hltMatchedVBFIsoTauTwoLoose_eta);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoLoose_phi", &hltMatchedVBFIsoTauTwoLoose_phi);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoLoose_energy", &hltMatchedVBFIsoTauTwoLoose_energy);
    // end HLT

    // from AOD
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
