#ifndef trigger_tree_h
#define trigger_tree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class trigger_tree {
public :
    TTree	*fChain;
    Int_t	fCurrent;

    Float_t	hltMatchedVBFTwo_eta;

    TBranch	*b_hltMatchedVBFTwo_eta;

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
    fChain->SetBranchAddress("hltMatchedVBFTwo_eta", &hltMatchedVBFTwo_eta, &b_hltMatchedVBFTwo_eta);
}

#endif
