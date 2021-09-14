//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Sep  4 00:50:31 2021 by ROOT version 6.12/07
// from TChain l1UpgradeTree/L1UpgradeTree/
//////////////////////////////////////////////////////////

#ifndef analyzer_h
#define analyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
//#include "L1Trigger/L1TNtuples/interface/L1AnalysisL1UpgradeDataFormat.h"

class analyzer {
public :
   TTree          *fChain1;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent1; //!current Tree number in a TChain
   TTree          *fChain2;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent2; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.
   UInt_t          run;
   ULong64_t       event;
   UInt_t          lumi;
   UInt_t          bx;
   ULong64_t       orbit;
   ULong64_t       time;
   Int_t           nPV;
   Int_t           nPV_True;
   vector<TString> hlt;
   Double_t        puWeight;

   // List of branches
   TBranch        *b_Event_run;   //!
   TBranch        *b_Event_event;   //!
   TBranch        *b_Event_lumi;   //!
   TBranch        *b_Event_bx;   //!
   TBranch        *b_Event_orbit;   //!
   TBranch        *b_Event_time;   //!
   TBranch        *b_Event_nPV;   //!
   TBranch        *b_Event_nPV_True;   //!
   TBranch        *b_Event_hlt;   //!
   TBranch        *b_Event_puWeight;   //!


   // Declaration of leaf types
 //L1Analysis::L1AnalysisL1UpgradeDataFormat *L1Upgrade;
   UShort_t        nEGs;
   vector<float>   egEt;
   vector<float>   egEta;
   vector<float>   egPhi;
   vector<short>   egIEt;
   vector<short>   egIEta;
   vector<short>   egIPhi;
   vector<short>   egIso;
   vector<short>   egBx;
   vector<short>   egTowerIPhi;
   vector<short>   egTowerIEta;
   vector<short>   egRawEt;
   vector<short>   egIsoEt;
   vector<short>   egFootprintEt;
   vector<short>   egNTT;
   vector<short>   egShape;
   vector<short>   egTowerHoE;
   vector<short>   egHwQual;
   UShort_t        nTaus;
   vector<float>   tauEt;
   vector<float>   tauEta;
   vector<float>   tauPhi;
   vector<short>   tauIEt;
   vector<short>   tauIEta;
   vector<short>   tauIPhi;
   vector<short>   tauIso;
   vector<short>   tauBx;
   vector<short>   tauTowerIPhi;
   vector<short>   tauTowerIEta;
   vector<short>   tauRawEt;
   vector<short>   tauIsoEt;
   vector<short>   tauNTT;
   vector<short>   tauHasEM;
   vector<short>   tauIsMerged;
   vector<short>   tauHwQual;
   UShort_t        nJets;
   vector<float>   jetEt;
   vector<float>   jetEta;
   vector<float>   jetPhi;
   vector<short>   jetIEt;
   vector<short>   jetIEta;
   vector<short>   jetIPhi;
   vector<short>   jetBx;
   vector<short>   jetTowerIPhi;
   vector<short>   jetTowerIEta;
   vector<short>   jetRawEt;
   vector<short>   jetSeedEt;
   vector<short>   jetPUEt;
   vector<short>   jetPUDonutEt0;
   vector<short>   jetPUDonutEt1;
   vector<short>   jetPUDonutEt2;
   vector<short>   jetPUDonutEt3;
   UShort_t        nMuons;
   vector<float>   muonEt;
   vector<float>   muonEta;
   vector<float>   muonPhi;
   vector<float>   muonEtaAtVtx;
   vector<float>   muonPhiAtVtx;
   vector<short>   muonIEt;
   vector<short>   muonIEta;
   vector<short>   muonIPhi;
   vector<short>   muonIEtaAtVtx;
   vector<short>   muonIPhiAtVtx;
   vector<short>   muonIDEta;
   vector<short>   muonIDPhi;
   vector<short>   muonChg;
   vector<unsigned short> muonIso;
   vector<unsigned short> muonQual;
   vector<unsigned short> muonTfMuonIdx;
   vector<short>   muonBx;
   UShort_t        nSums;
   vector<short>   sumType;
   vector<float>   sumEt;
   vector<float>   sumPhi;
   vector<short>   sumIEt;
   vector<short>   sumIPhi;
   vector<float>   sumBx;




   // List of branches
   TBranch        *b_L1Upgrade_nEGs;   //!
   TBranch        *b_L1Upgrade_egEt;   //!
   TBranch        *b_L1Upgrade_egEta;   //!
   TBranch        *b_L1Upgrade_egPhi;   //!
   TBranch        *b_L1Upgrade_egIEt;   //!
   TBranch        *b_L1Upgrade_egIEta;   //!
   TBranch        *b_L1Upgrade_egIPhi;   //!
   TBranch        *b_L1Upgrade_egIso;   //!
   TBranch        *b_L1Upgrade_egBx;   //!
   TBranch        *b_L1Upgrade_egTowerIPhi;   //!
   TBranch        *b_L1Upgrade_egTowerIEta;   //!
   TBranch        *b_L1Upgrade_egRawEt;   //!
   TBranch        *b_L1Upgrade_egIsoEt;   //!
   TBranch        *b_L1Upgrade_egFootprintEt;   //!
   TBranch        *b_L1Upgrade_egNTT;   //!
   TBranch        *b_L1Upgrade_egShape;   //!
   TBranch        *b_L1Upgrade_egTowerHoE;   //!
   TBranch        *b_L1Upgrade_egHwQual;   //!
   TBranch        *b_L1Upgrade_nTaus;   //!
   TBranch        *b_L1Upgrade_tauEt;   //!
   TBranch        *b_L1Upgrade_tauEta;   //!
   TBranch        *b_L1Upgrade_tauPhi;   //!
   TBranch        *b_L1Upgrade_tauIEt;   //!
   TBranch        *b_L1Upgrade_tauIEta;   //!
   TBranch        *b_L1Upgrade_tauIPhi;   //!
   TBranch        *b_L1Upgrade_tauIso;   //!
   TBranch        *b_L1Upgrade_tauBx;   //!
   TBranch        *b_L1Upgrade_tauTowerIPhi;   //!
   TBranch        *b_L1Upgrade_tauTowerIEta;   //!
   TBranch        *b_L1Upgrade_tauRawEt;   //!
   TBranch        *b_L1Upgrade_tauIsoEt;   //!
   TBranch        *b_L1Upgrade_tauNTT;   //!
   TBranch        *b_L1Upgrade_tauHasEM;   //!
   TBranch        *b_L1Upgrade_tauIsMerged;   //!
   TBranch        *b_L1Upgrade_tauHwQual;   //!
   TBranch        *b_L1Upgrade_nJets;   //!
   TBranch        *b_L1Upgrade_jetEt;   //!
   TBranch        *b_L1Upgrade_jetEta;   //!
   TBranch        *b_L1Upgrade_jetPhi;   //!
   TBranch        *b_L1Upgrade_jetIEt;   //!
   TBranch        *b_L1Upgrade_jetIEta;   //!
   TBranch        *b_L1Upgrade_jetIPhi;   //!
   TBranch        *b_L1Upgrade_jetBx;   //!
   TBranch        *b_L1Upgrade_jetTowerIPhi;   //!
   TBranch        *b_L1Upgrade_jetTowerIEta;   //!
   TBranch        *b_L1Upgrade_jetRawEt;   //!
   TBranch        *b_L1Upgrade_jetSeedEt;   //!
   TBranch        *b_L1Upgrade_jetPUEt;   //!
   TBranch        *b_L1Upgrade_jetPUDonutEt0;   //!
   TBranch        *b_L1Upgrade_jetPUDonutEt1;   //!
   TBranch        *b_L1Upgrade_jetPUDonutEt2;   //!
   TBranch        *b_L1Upgrade_jetPUDonutEt3;   //!
   TBranch        *b_L1Upgrade_nMuons;   //!
   TBranch        *b_L1Upgrade_muonEt;   //!
   TBranch        *b_L1Upgrade_muonEta;   //!
   TBranch        *b_L1Upgrade_muonPhi;   //!
   TBranch        *b_L1Upgrade_muonEtaAtVtx;   //!
   TBranch        *b_L1Upgrade_muonPhiAtVtx;   //!
   TBranch        *b_L1Upgrade_muonIEt;   //!
   TBranch        *b_L1Upgrade_muonIEta;   //!
   TBranch        *b_L1Upgrade_muonIPhi;   //!
   TBranch        *b_L1Upgrade_muonIEtaAtVtx;   //!
   TBranch        *b_L1Upgrade_muonIPhiAtVtx;   //!
   TBranch        *b_L1Upgrade_muonIDEta;   //!
   TBranch        *b_L1Upgrade_muonIDPhi;   //!
   TBranch        *b_L1Upgrade_muonChg;   //!
   TBranch        *b_L1Upgrade_muonIso;   //!
   TBranch        *b_L1Upgrade_muonQual;   //!
   TBranch        *b_L1Upgrade_muonTfMuonIdx;   //!
   TBranch        *b_L1Upgrade_muonBx;   //!
   TBranch        *b_L1Upgrade_nSums;   //!
   TBranch        *b_L1Upgrade_sumType;   //!
   TBranch        *b_L1Upgrade_sumEt;   //!
   TBranch        *b_L1Upgrade_sumPhi;   //!
   TBranch        *b_L1Upgrade_sumIEt;   //!
   TBranch        *b_L1Upgrade_sumIPhi;   //!
   TBranch        *b_L1Upgrade_sumBx;   //!

   // YM modified constructor
   analyzer();
   virtual ~analyzer();
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   // YM modified initialization
   virtual void     Init(TTree *tree1, TTree* tree2);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef analyzer_cxx
analyzer::analyzer() 
{
  //YM first chain with upgrade info
      TChain * chain1 = new TChain("l1UpgradeTree/L1UpgradeTree","");

      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_1.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_10.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_11.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_12.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_13.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_14.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_15.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_16.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_17.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_18.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_19.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_2.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_20.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_21.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_22.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_23.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_24.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_25.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_26.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_27.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_28.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_29.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_3.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_30.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_31.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_32.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_33.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_34.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_35.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_36.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_37.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_38.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_39.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_4.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_40.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_41.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_42.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_43.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_44.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_45.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_5.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_6.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_7.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_8.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_9.root");
  
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/2_EphemeralZeroBias6/L1Ntuple.root");

      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_1.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_10.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_11.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_12.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_13.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_14.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_15.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_16.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_17.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_18.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_19.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_2.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_20.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_21.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_22.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_23.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_24.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_25.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_26.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_27.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_28.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_29.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_3.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_30.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_31.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_32.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_33.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_34.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_35.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_36.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_37.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_38.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_39.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_4.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_40.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_41.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_42.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_43.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_44.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_45.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_5.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_6.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_7.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_8.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_9.root");
 
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_1.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_10.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_11.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_12.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_13.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_14.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_15.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_16.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_17.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_18.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_19.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_2.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_20.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_21.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_22.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_23.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_24.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_25.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_26.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_27.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_28.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_29.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_3.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_30.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_31.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_32.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_33.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_34.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_35.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_36.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_37.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_38.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_39.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_4.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_40.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_41.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_42.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_43.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_44.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_45.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_5.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_6.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_7.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_8.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_9.root");

      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_1.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_10.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_11.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_12.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_13.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_14.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_15.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_16.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_17.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_18.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_19.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_2.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_20.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_21.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_22.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_23.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_24.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_25.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_26.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_27.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_28.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_29.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_3.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_30.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_31.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_32.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_33.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_34.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_35.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_36.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_37.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_38.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_39.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_4.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_40.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_41.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_42.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_43.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_44.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_45.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_5.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_6.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_7.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_8.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_9.root");

      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_1.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_10.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_11.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_12.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_13.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_14.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_15.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_16.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_17.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_18.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_19.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_2.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_20.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_21.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_22.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_23.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_24.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_25.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_26.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_27.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_28.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_29.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_3.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_30.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_31.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_32.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_33.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_34.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_35.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_36.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_37.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_38.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_39.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_4.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_40.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_41.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_42.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_43.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_44.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_45.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_5.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_6.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_7.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_8.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_9.root");

      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_1.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_10.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_11.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_12.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_13.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_14.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_15.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_16.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_17.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_18.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_19.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_2.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_20.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_21.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_22.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_23.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_24.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_25.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_26.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_27.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_28.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_29.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_3.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_30.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_31.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_32.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_33.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_34.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_35.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_36.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_37.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_38.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_39.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_4.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_40.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_41.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_42.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_43.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_44.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_45.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_5.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_6.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_7.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_8.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_9.root");

      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_1.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_10.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_11.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_12.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_13.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_14.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_15.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_16.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_17.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_18.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_19.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_2.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_20.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_21.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_22.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_23.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_24.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_25.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_26.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_27.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_28.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_29.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_3.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_30.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_31.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_32.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_33.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_34.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_35.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_36.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_37.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_38.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_39.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_4.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_40.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_41.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_42.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_43.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_44.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_45.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_5.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_6.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_7.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_8.root");
      chain1->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_9.root");

      //chain1->Add("/eos/cms/store/group/dpg_trigger/comm_trigger/L1Trigger/stempl/CRAB/EphemeralZeroBias8/zb_Nov2020-v2/201119_174913/0000/L1Ntuple_9.root");
      TTree* tree1 = chain1;

  //YM first chain with event info
      TChain * chain2 = new TChain("l1EventTree/L1EventTree","");

      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_1.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_10.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_11.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_12.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_13.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_14.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_15.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_16.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_17.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_18.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_19.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_2.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_20.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_21.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_22.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_23.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_24.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_25.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_26.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_27.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_28.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_29.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_3.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_30.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_31.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_32.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_33.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_34.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_35.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_36.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_37.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_38.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_39.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_4.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_40.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_41.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_42.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_43.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_44.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_45.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_5.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_6.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_7.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_8.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/1_EphemeralZeroBias8/L1Ntuple_9.root");

      chain2->Add("/eos/user/j/jleonhol/HH/run323755/2_EphemeralZeroBias6/L1Ntuple.root");

      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_1.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_10.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_11.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_12.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_13.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_14.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_15.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_16.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_17.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_18.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_19.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_2.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_20.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_21.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_22.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_23.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_24.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_25.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_26.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_27.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_28.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_29.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_3.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_30.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_31.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_32.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_33.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_34.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_35.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_36.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_37.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_38.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_39.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_4.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_40.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_41.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_42.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_43.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_44.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_45.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_5.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_6.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_7.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_8.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/3_EphemeralZeroBias1/L1Ntuple_9.root");

      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_1.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_10.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_11.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_12.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_13.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_14.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_15.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_16.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_17.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_18.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_19.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_2.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_20.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_21.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_22.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_23.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_24.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_25.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_26.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_27.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_28.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_29.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_3.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_30.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_31.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_32.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_33.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_34.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_35.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_36.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_37.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_38.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_39.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_4.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_40.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_41.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_42.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_43.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_44.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_45.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_5.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_6.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_7.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_8.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/4_EphemeralZeroBias3/L1Ntuple_9.root");

      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_1.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_10.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_11.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_12.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_13.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_14.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_15.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_16.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_17.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_18.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_19.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_2.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_20.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_21.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_22.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_23.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_24.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_25.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_26.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_27.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_28.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_29.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_3.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_30.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_31.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_32.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_33.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_34.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_35.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_36.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_37.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_38.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_39.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_4.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_40.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_41.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_42.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_43.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_44.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_45.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_5.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_6.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_7.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_8.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/5_EphemeralZeroBias5/L1Ntuple_9.root");

      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_1.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_10.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_11.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_12.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_13.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_14.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_15.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_16.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_17.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_18.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_19.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_2.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_20.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_21.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_22.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_23.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_24.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_25.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_26.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_27.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_28.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_29.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_3.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_30.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_31.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_32.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_33.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_34.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_35.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_36.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_37.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_38.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_39.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_4.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_40.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_41.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_42.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_43.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_44.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_45.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_5.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_6.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_7.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_8.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/6_EphemeralZeroBias7/L1Ntuple_9.root");

      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_1.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_10.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_11.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_12.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_13.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_14.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_15.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_16.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_17.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_18.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_19.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_2.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_20.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_21.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_22.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_23.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_24.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_25.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_26.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_27.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_28.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_29.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_3.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_30.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_31.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_32.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_33.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_34.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_35.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_36.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_37.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_38.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_39.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_4.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_40.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_41.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_42.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_43.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_44.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_45.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_5.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_6.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_7.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_8.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/7_EphemeralZeroBias4/L1Ntuple_9.root");

      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_1.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_10.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_11.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_12.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_13.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_14.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_15.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_16.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_17.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_18.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_19.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_2.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_20.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_21.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_22.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_23.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_24.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_25.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_26.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_27.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_28.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_29.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_3.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_30.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_31.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_32.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_33.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_34.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_35.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_36.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_37.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_38.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_39.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_4.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_40.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_41.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_42.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_43.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_44.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_45.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_5.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_6.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_7.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_8.root");
      chain2->Add("/eos/user/j/jleonhol/HH/run323755/8_EphemeralZeroBias2/L1Ntuple_9.root");


      //chain2->Add("/eos/cms/store/group/dpg_trigger/comm_trigger/L1Trigger/stempl/CRAB/EphemeralZeroBias8/zb_Nov2020-v2/201119_174913/0000/L1Ntuple_9.root");

      TTree* tree2 = chain2;
      
      // YM calling initialization with two trees
      Init(tree1, tree2);
}

analyzer::~analyzer()
{
  // YM slightly modified destructor due to 2 chains
   if (fChain1) delete fChain1->GetCurrentFile();
   if (fChain2) delete fChain2->GetCurrentFile();
   return;
}

Int_t analyzer::GetEntry(Long64_t entry)
{
  if (!fChain1 || !fChain2 ) return 0;
  fChain1->GetEntry(entry);
  fChain2->GetEntry(entry);
  return 1;
}

Long64_t analyzer::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain1) return -5;
   Long64_t centry = fChain1->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain1->GetTreeNumber() != fCurrent1) {
      fCurrent1 = fChain1->GetTreeNumber();
      Notify();
   }
   centry = fChain2->LoadTree(entry);
   if (centry < 0 ) return centry;
   if (fChain2->GetTreeNumber() != fCurrent2) {
     fCurrent2 = fChain2->GetTreeNumber();
     Notify();
   }
   return centry;
}

void analyzer::Init(TTree *tree1, TTree *tree2)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree1 || !tree2) return;
   fChain1 = tree1;
   fCurrent1 = -1;
   fChain1->SetMakeClass(1);

   fChain1->SetBranchAddress("nEGs", &nEGs, &b_L1Upgrade_nEGs);
   fChain1->SetBranchAddress("egEt", &egEt, &b_L1Upgrade_egEt);
   fChain1->SetBranchAddress("egEta", &egEta, &b_L1Upgrade_egEta);
   fChain1->SetBranchAddress("egPhi", &egPhi, &b_L1Upgrade_egPhi);
   fChain1->SetBranchAddress("egIEt", &egIEt, &b_L1Upgrade_egIEt);
   fChain1->SetBranchAddress("egIEta", &egIEta, &b_L1Upgrade_egIEta);
   fChain1->SetBranchAddress("egIPhi", &egIPhi, &b_L1Upgrade_egIPhi);
   fChain1->SetBranchAddress("egIso", &egIso, &b_L1Upgrade_egIso);
   fChain1->SetBranchAddress("egBx", &egBx, &b_L1Upgrade_egBx);
   fChain1->SetBranchAddress("egTowerIPhi", &egTowerIPhi, &b_L1Upgrade_egTowerIPhi);
   fChain1->SetBranchAddress("egTowerIEta", &egTowerIEta, &b_L1Upgrade_egTowerIEta);
   fChain1->SetBranchAddress("egRawEt", &egRawEt, &b_L1Upgrade_egRawEt);
   fChain1->SetBranchAddress("egIsoEt", &egIsoEt, &b_L1Upgrade_egIsoEt);
   fChain1->SetBranchAddress("egFootprintEt", &egFootprintEt, &b_L1Upgrade_egFootprintEt);
   fChain1->SetBranchAddress("egNTT", &egNTT, &b_L1Upgrade_egNTT);
   fChain1->SetBranchAddress("egShape", &egShape, &b_L1Upgrade_egShape);
   fChain1->SetBranchAddress("egTowerHoE", &egTowerHoE, &b_L1Upgrade_egTowerHoE);
   fChain1->SetBranchAddress("egHwQual", &egHwQual, &b_L1Upgrade_egHwQual);
   fChain1->SetBranchAddress("nTaus", &nTaus, &b_L1Upgrade_nTaus);
   fChain1->SetBranchAddress("tauEt", &tauEt, &b_L1Upgrade_tauEt);
   fChain1->SetBranchAddress("tauEta", &tauEta, &b_L1Upgrade_tauEta);
   fChain1->SetBranchAddress("tauPhi", &tauPhi, &b_L1Upgrade_tauPhi);
   fChain1->SetBranchAddress("tauIEt", &tauIEt, &b_L1Upgrade_tauIEt);
   fChain1->SetBranchAddress("tauIEta", &tauIEta, &b_L1Upgrade_tauIEta);
   fChain1->SetBranchAddress("tauIPhi", &tauIPhi, &b_L1Upgrade_tauIPhi);
   fChain1->SetBranchAddress("tauIso", &tauIso, &b_L1Upgrade_tauIso);
   fChain1->SetBranchAddress("tauBx", &tauBx, &b_L1Upgrade_tauBx);
   fChain1->SetBranchAddress("tauTowerIPhi", &tauTowerIPhi, &b_L1Upgrade_tauTowerIPhi);
   fChain1->SetBranchAddress("tauTowerIEta", &tauTowerIEta, &b_L1Upgrade_tauTowerIEta);
   fChain1->SetBranchAddress("tauRawEt", &tauRawEt, &b_L1Upgrade_tauRawEt);
   fChain1->SetBranchAddress("tauIsoEt", &tauIsoEt, &b_L1Upgrade_tauIsoEt);
   fChain1->SetBranchAddress("tauNTT", &tauNTT, &b_L1Upgrade_tauNTT);
   fChain1->SetBranchAddress("tauHasEM", &tauHasEM, &b_L1Upgrade_tauHasEM);
   fChain1->SetBranchAddress("tauIsMerged", &tauIsMerged, &b_L1Upgrade_tauIsMerged);
   fChain1->SetBranchAddress("tauHwQual", &tauHwQual, &b_L1Upgrade_tauHwQual);
   fChain1->SetBranchAddress("nJets", &nJets, &b_L1Upgrade_nJets);
   fChain1->SetBranchAddress("jetEt", &jetEt, &b_L1Upgrade_jetEt);
   fChain1->SetBranchAddress("jetEta", &jetEta, &b_L1Upgrade_jetEta);
   fChain1->SetBranchAddress("jetPhi", &jetPhi, &b_L1Upgrade_jetPhi);
   fChain1->SetBranchAddress("jetIEt", &jetIEt, &b_L1Upgrade_jetIEt);
   fChain1->SetBranchAddress("jetIEta", &jetIEta, &b_L1Upgrade_jetIEta);
   fChain1->SetBranchAddress("jetIPhi", &jetIPhi, &b_L1Upgrade_jetIPhi);
   fChain1->SetBranchAddress("jetBx", &jetBx, &b_L1Upgrade_jetBx);
   fChain1->SetBranchAddress("jetTowerIPhi", &jetTowerIPhi, &b_L1Upgrade_jetTowerIPhi);
   fChain1->SetBranchAddress("jetTowerIEta", &jetTowerIEta, &b_L1Upgrade_jetTowerIEta);
   fChain1->SetBranchAddress("jetRawEt", &jetRawEt, &b_L1Upgrade_jetRawEt);
   fChain1->SetBranchAddress("jetSeedEt", &jetSeedEt, &b_L1Upgrade_jetSeedEt);
   fChain1->SetBranchAddress("jetPUEt", &jetPUEt, &b_L1Upgrade_jetPUEt);
   fChain1->SetBranchAddress("jetPUDonutEt0", &jetPUDonutEt0, &b_L1Upgrade_jetPUDonutEt0);
   fChain1->SetBranchAddress("jetPUDonutEt1", &jetPUDonutEt1, &b_L1Upgrade_jetPUDonutEt1);
   fChain1->SetBranchAddress("jetPUDonutEt2", &jetPUDonutEt2, &b_L1Upgrade_jetPUDonutEt2);
   fChain1->SetBranchAddress("jetPUDonutEt3", &jetPUDonutEt3, &b_L1Upgrade_jetPUDonutEt3);
   fChain1->SetBranchAddress("nMuons", &nMuons, &b_L1Upgrade_nMuons);
   fChain1->SetBranchAddress("muonEt", &muonEt, &b_L1Upgrade_muonEt);
   fChain1->SetBranchAddress("muonEta", &muonEta, &b_L1Upgrade_muonEta);
   fChain1->SetBranchAddress("muonPhi", &muonPhi, &b_L1Upgrade_muonPhi);
   fChain1->SetBranchAddress("muonEtaAtVtx", &muonEtaAtVtx, &b_L1Upgrade_muonEtaAtVtx);
   fChain1->SetBranchAddress("muonPhiAtVtx", &muonPhiAtVtx, &b_L1Upgrade_muonPhiAtVtx);
   fChain1->SetBranchAddress("muonIEt", &muonIEt, &b_L1Upgrade_muonIEt);
   fChain1->SetBranchAddress("muonIEta", &muonIEta, &b_L1Upgrade_muonIEta);
   fChain1->SetBranchAddress("muonIPhi", &muonIPhi, &b_L1Upgrade_muonIPhi);
   fChain1->SetBranchAddress("muonIEtaAtVtx", &muonIEtaAtVtx, &b_L1Upgrade_muonIEtaAtVtx);
   fChain1->SetBranchAddress("muonIPhiAtVtx", &muonIPhiAtVtx, &b_L1Upgrade_muonIPhiAtVtx);
   fChain1->SetBranchAddress("muonIDEta", &muonIDEta, &b_L1Upgrade_muonIDEta);
   fChain1->SetBranchAddress("muonIDPhi", &muonIDPhi, &b_L1Upgrade_muonIDPhi);
   fChain1->SetBranchAddress("muonChg", &muonChg, &b_L1Upgrade_muonChg);
   fChain1->SetBranchAddress("muonIso", &muonIso, &b_L1Upgrade_muonIso);
   fChain1->SetBranchAddress("muonQual", &muonQual, &b_L1Upgrade_muonQual);
   fChain1->SetBranchAddress("muonTfMuonIdx", &muonTfMuonIdx, &b_L1Upgrade_muonTfMuonIdx);
   fChain1->SetBranchAddress("muonBx", &muonBx, &b_L1Upgrade_muonBx);
   fChain1->SetBranchAddress("nSums", &nSums, &b_L1Upgrade_nSums);
   fChain1->SetBranchAddress("sumType", &sumType, &b_L1Upgrade_sumType);
   fChain1->SetBranchAddress("sumEt", &sumEt, &b_L1Upgrade_sumEt);
   fChain1->SetBranchAddress("sumPhi", &sumPhi, &b_L1Upgrade_sumPhi);
   fChain1->SetBranchAddress("sumIEt", &sumIEt, &b_L1Upgrade_sumIEt);
   fChain1->SetBranchAddress("sumIPhi", &sumIPhi, &b_L1Upgrade_sumIPhi);
   fChain1->SetBranchAddress("sumBx", &sumBx, &b_L1Upgrade_sumBx);

   //YM second tree
   fChain2 = tree2;
   fChain2->SetMakeClass(2);
   fCurrent2 = -1;

   fChain2->SetBranchAddress("run", &run, &b_Event_run);
   fChain2->SetBranchAddress("event", &event, &b_Event_event);
   fChain2->SetBranchAddress("lumi", &lumi, &b_Event_lumi);
   fChain2->SetBranchAddress("bx", &bx, &b_Event_bx);
   fChain2->SetBranchAddress("orbit", &orbit, &b_Event_orbit);
   fChain2->SetBranchAddress("time", &time, &b_Event_time);
   fChain2->SetBranchAddress("nPV", &nPV, &b_Event_nPV);
   fChain2->SetBranchAddress("nPV_True", &nPV_True, &b_Event_nPV_True);
   fChain2->SetBranchAddress("hlt", &hlt, &b_Event_hlt);
   fChain2->SetBranchAddress("puWeight", &puWeight, &b_Event_puWeight);

   Notify();
}

Bool_t analyzer::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   cout << "switched file" << endl;
   return kTRUE;
}

void analyzer::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain1) return;
   fChain1->Show(entry);
}

#endif
