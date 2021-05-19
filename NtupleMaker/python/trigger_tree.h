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

    std::vector<float>* hltHpsDoublePFTau_pt = nullptr;
    std::vector<float>* hltHpsDoublePFTau_eta = nullptr;
    std::vector<float>* hltHpsDoublePFTau_phi = nullptr;
    std::vector<float>* hltHpsDoublePFTau_energy = nullptr;
    std::vector<float>* hltMatchedVBFOne_pt = nullptr;
    std::vector<float>* hltMatchedVBFOne_eta = nullptr;
    std::vector<float>* hltMatchedVBFOne_phi = nullptr;
    std::vector<float>* hltMatchedVBFOne_energy = nullptr;
    std::vector<float>*	hltMatchedVBFTwo_pt = nullptr;
    std::vector<float>* hltMatchedVBFTwo_eta = nullptr;
    std::vector<float>* hltMatchedVBFTwo_phi = nullptr;
    std::vector<float>* hltMatchedVBFTwo_energy = nullptr;

    std::vector<float>* jetPt = nullptr;
    std::vector<float>* jetEta = nullptr;
    std::vector<float>* jetPhi = nullptr;
    std::vector<float>* jetEn = nullptr;
    std::vector<float>* tauPt = nullptr;
    std::vector<float>* tauEta = nullptr;
    std::vector<float>* tauPhi = nullptr;
    std::vector<float>* tauEnergy = nullptr;
    int 	nTau;

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
    fChain->SetBranchAddress("hltHpsDoublePFTau_pt", &hltHpsDoublePFTau_pt);
    fChain->SetBranchAddress("hltHpsDoublePFTau_eta", &hltHpsDoublePFTau_eta);
    fChain->SetBranchAddress("hltHpsDoublePFTau_phi", &hltHpsDoublePFTau_phi);
    fChain->SetBranchAddress("hltHpsDoublePFTau_energy", &hltHpsDoublePFTau_energy);
    fChain->SetBranchAddress("hltMatchedVBFOne_pt", &hltMatchedVBFOne_pt);
    fChain->SetBranchAddress("hltMatchedVBFOne_eta", &hltMatchedVBFOne_eta);
    fChain->SetBranchAddress("hltMatchedVBFOne_phi", &hltMatchedVBFOne_phi);
    fChain->SetBranchAddress("hltMatchedVBFOne_energy", &hltMatchedVBFOne_energy);
    fChain->SetBranchAddress("hltMatchedVBFTwo_pt", &hltMatchedVBFTwo_pt);
    fChain->SetBranchAddress("hltMatchedVBFTwo_eta", &hltMatchedVBFTwo_eta);
    fChain->SetBranchAddress("hltMatchedVBFTwo_phi", &hltMatchedVBFTwo_phi);
    fChain->SetBranchAddress("hltMatchedVBFTwo_energy", &hltMatchedVBFTwo_energy);

    fChain->SetBranchAddress("jetPt", &jetPt);
    fChain->SetBranchAddress("jetEta", &jetEta);
    fChain->SetBranchAddress("jetPhi", &jetPhi);
    fChain->SetBranchAddress("jetEn", &jetEn);
    fChain->SetBranchAddress("tauPt", &tauPt);
    fChain->SetBranchAddress("tauEta", &tauEta);
    fChain->SetBranchAddress("tauPhi", &tauPhi);
    fChain->SetBranchAddress("tauEnergy", &tauEnergy);
    fChain->SetBranchAddress("nTau", &nTau);
}

#endif
