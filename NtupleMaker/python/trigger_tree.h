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
    std::vector<float>* hltMatchedVBFOne_pt = nullptr;
    std::vector<float>* hltMatchedVBFOne_eta = nullptr;
    std::vector<float>* hltMatchedVBFOne_phi = nullptr;
    std::vector<float>* hltMatchedVBFOne_energy = nullptr;
    std::vector<float>*	hltMatchedVBFTwo_pt = nullptr;
    std::vector<float>* hltMatchedVBFTwo_eta = nullptr;
    std::vector<float>* hltMatchedVBFTwo_phi = nullptr;
    std::vector<float>* hltMatchedVBFTwo_energy = nullptr;

    //TBranch	*b_hltMatchedVBFTwo_eta;

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
    fChain->SetBranchAddress("hltMatchedVBFOne_pt", &hltMatchedVBFOne_pt);
    fChain->SetBranchAddress("hltMatchedVBFOne_eta", &hltMatchedVBFOne_eta);
    fChain->SetBranchAddress("hltMatchedVBFOne_phi", &hltMatchedVBFOne_phi);
    fChain->SetBranchAddress("hltMatchedVBFOne_energy", &hltMatchedVBFOne_energy);
    fChain->SetBranchAddress("hltMatchedVBFTwo_pt", &hltMatchedVBFTwo_pt);
    fChain->SetBranchAddress("hltMatchedVBFTwo_eta", &hltMatchedVBFTwo_eta);
    fChain->SetBranchAddress("hltMatchedVBFTwo_phi", &hltMatchedVBFTwo_phi);
    fChain->SetBranchAddress("hltMatchedVBFTwo_energy", &hltMatchedVBFTwo_energy);
}

#endif
