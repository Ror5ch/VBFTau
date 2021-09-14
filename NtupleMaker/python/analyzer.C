#define analyzer_cxx
#include "analyzer.h"
//#include "smaller_header.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <vector>
#include <array>

float highestMassOfPair(vector<TLorentzVector> jetsRmvOlTaus, vector<TLorentzVector> taus) {
  float mjotjot_ = 0; float tempMjotjot_ = 0;
  vector<TLorentzVector> combined;
  combined.insert(combined.begin(), jetsRmvOlTaus.begin(), jetsRmvOlTaus.end());
  combined.insert(combined.end(), taus.begin(), taus.end());
  int combinedSize = combined.size();
  for (int iObj = 0; iObj < combinedSize; ++iObj) {
    for (int jObj = 0; jObj < combinedSize; ++jObj) {
      if (jObj >= iObj) continue;
      tempMjotjot_ = (combined.at(iObj) + combined.at(jObj)).M();
      if (tempMjotjot_ > mjotjot_) mjotjot_ = tempMjotjot_;
    }
  }
  return mjotjot_;
}

vector<TLorentzVector> crossCleanJets(vector<TLorentzVector> jets, vector<TLorentzVector> taus) {
  if (taus.size() == 0 || jets.size() == 0) {cout << "crossclean function used wrong" << endl;} //throws an error 
  vector<TLorentzVector> crossCleanedJets;
  for (int iTau = 0; iTau < taus.size(); ++iTau) {
    for (int iJet = 0; iJet < jets.size(); ++iJet) {
      if (taus.at(iTau).DeltaR(jets.at(iJet)) > 0.5) crossCleanedJets.push_back(jets.at(iJet));
    }
  }
  return crossCleanedJets;
}

void analyzer::Loop()
{
  if (fChain1 == 0 || fChain2 == 0 ) {
    cout << "One of your fChains is missing :(" << endl;
    return;
  }

  Long64_t nentries1 = fChain1->GetEntriesFast();
  Long64_t nentries2 = fChain2->GetEntriesFast();

  cout << "These better match" << endl;
  cout << nentries1 << "\t" << nentries2 << endl;

  Long64_t nbytes = 0, nb = 0;

  set<pair<int,int>> lumis;

  int eventCount = 0;
  int runCount = 0;

  int passDiTau = 0;
  int passOld = 0;
  int passNew = 0;
 
  int passSeed1 = 0;
  int passSeed2 = 0;
  int passSeed3 = 0;

  int passDiTauCount = 0;
  int passOldCount = 0;
  int passNewCount = 0;

  int passSeed1Count = 0;
  int passSeed2Count = 0;
  int passSeed3Count = 0;

  int passSeed2_3535350 = 0;
  int passSeed2_3535400 = 0;
  int passSeed2_3535450 = 0;
  int passSeed2_3535500 = 0;
  int passSeed2_3535350_count = 0;
  int passSeed2_3535400_count = 0;
  int passSeed2_3535450_count = 0;
  int passSeed2_3535500_count = 0;

  int passSeed2_3545350 = 0;
  int passSeed2_3545450 = 0;
  int passSeed2_3545500 = 0;
  int passSeed2_3545550 = 0;
  int passSeed2_3545600 = 0;
  int passSeed2_3545350_count = 0;
  int passSeed2_3545450_count = 0;
  int passSeed2_3545500_count = 0;
  int passSeed2_3545550_count = 0;
  int passSeed2_3545600_count = 0;

  int passSeed2_3540350 = 0;
  int passSeed2_3540400 = 0;
  int passSeed2_3540450 = 0;
  int passSeed2_3540500 = 0;
  int passSeed2_3540550 = 0;
  int passSeed2_3540600 = 0;
  int passSeed2_3540350_count = 0;
  int passSeed2_3540400_count = 0;
  int passSeed2_3540450_count = 0;
  int passSeed2_3540500_count = 0;
  int passSeed2_3540550_count = 0;
  int passSeed2_3540600_count = 0;

  int passSeed2_3550350 = 0;
  int passSeed2_3550400 = 0;
  int passSeed2_3550450 = 0;
  int passSeed2_3550500 = 0;
  int passSeed2_3550550 = 0;
  int passSeed2_3550600 = 0;
  int passSeed2_3550350_count = 0;
  int passSeed2_3550400_count = 0;
  int passSeed2_3550450_count = 0;
  int passSeed2_3550500_count = 0;
  int passSeed2_3550550_count = 0;
  int passSeed2_3550600_count = 0;

  int olDiTauSeed1 = 0;
  int olDiTauSeed2 = 0;
  int olDiTauSeed3 = 0;
  int olOldSeed1 = 0;
  int olOldSeed2 = 0;
  int olOldSeed3 = 0;
  int olNewSeed1 = 0;
  int olNewSeed2 = 0;
  int olNewSeed3 = 0;

  int orDiTauSeed1 = 0;
  int orDiTauSeed2 = 0;
  int orDiTauSeed3 = 0;
  int orOldSeed1 = 0;
  int orOldSeed2 = 0;
  int orOldSeed3 = 0;
  int orNewSeed1 = 0;
  int orNewSeed2 = 0;
  int orNewSeed3 = 0;

  // start event loop
  //for (Long64_t jentry=0; jentry<nentries1; ++jentry) { // full dataset
  for (Long64_t jentry=0; jentry<200000; ++jentry) {
  //for (Long64_t jentry=11100000; jentry<11400000; ++jentry) { // full run 323755

    if (jentry%100000 == 0) cout << jentry << endl;
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;

    // update both chains of TTree files 
    nb = fChain1->GetEntry(jentry);   nbytes += nb;
    nb = fChain2->GetEntry(jentry);

    // reject events not in selected run number
    // save lumi block info for new blocks (using C std::set)
    eventCount += 1;
    //bool validRun = (run == 323755 || run == 324237 || run == 324245 || run == 324293);
    //if (!validRun) continue;
    if (run != 323755) continue;

    bool restrictLumi = true;
    if (restrictLumi && (lumi < 44 || lumi >= 144)) continue;
    lumis.insert(make_pair(run,lumi));
    runCount += 1;

    passDiTau = 0;
    passOld = 0;
    passNew = 0;

    passSeed1 = 0;
    passSeed2 = 0;
    passSeed3 = 0;

    passSeed2_3535350 = 0;
    passSeed2_3535400 = 0;
    passSeed2_3535450 = 0;
    passSeed2_3535500 = 0;

    passSeed2_3545350 = 0;
    passSeed2_3545450 = 0;
    passSeed2_3545500 = 0;
    passSeed2_3545550 = 0;
    passSeed2_3545600 = 0;

    passSeed2_3540350 = 0;
    passSeed2_3540400 = 0;
    passSeed2_3540450 = 0;
    passSeed2_3540500 = 0;
    passSeed2_3540550 = 0;
    passSeed2_3540600 = 0;

    passSeed2_3550350 = 0;
    passSeed2_3550400 = 0;
    passSeed2_3550450 = 0;
    passSeed2_3550500 = 0;
    passSeed2_3550550 = 0;
    passSeed2_3550600 = 0;

    // build container of taus (two containers are built here at the same time, one is not req. to be isotau)
    // Branch Crossing (Bx) equals zero
    TLorentzVector tempTauIso32;
    vector<TLorentzVector> tauCandsIso32;
    TLorentzVector tempTau35;
    vector<TLorentzVector> tauCands35;
    for (int iTau = 0; iTau < tauBx.size(); ++iTau) {
      if (tauBx[iTau] != 0) continue;
      float tauEt_ = tauEt[iTau];
      float tauEta_ = tauEta[iTau];
      if (tauEt_ >= 35 && fabs(tauEta_) <= 2.1) {
        tempTau35.SetPtEtaPhiM(tauEt_, tauEta_, tauPhi[iTau], 0);
        tauCands35.push_back(tempTau35);
      }
      if (tauEt_ >= 32 && fabs(tauEta_) <= 2.1 && tauIso[iTau] > 0) {
        tempTauIso32.SetPtEtaPhiM(tauEt_, tauEta_, tauPhi[iTau], 0);
        tauCandsIso32.push_back(tempTauIso32);
      }
    }
    int tauCandsIso32Size = tauCandsIso32.size();
    int tauCands35Size = tauCands35.size();

    vector<TLorentzVector> tauCandsIso35;
    vector<TLorentzVector> tauCandsIso40;
    vector<TLorentzVector> tauCandsIso45;
    vector<TLorentzVector> tauCandsIso50; 
    vector<TLorentzVector> tauCandsIso55;
    vector<TLorentzVector> tauCandsIso60;
    vector<TLorentzVector> tauCandsIso65;
    float tauPt_;
    TLorentzVector tempTau_;
    for (int iTau = 0; iTau < tauCandsIso32Size; ++iTau) {
      tempTau_ = tauCandsIso32.at(iTau);
      tauPt_ = tempTau_.Pt();
      if (tauPt_ >= 35) tauCandsIso35.push_back(tempTau_);
      if (tauPt_ >= 40) tauCandsIso40.push_back(tempTau_);
      if (tauPt_ >= 45) tauCandsIso45.push_back(tempTau_);
      if (tauPt_ >= 50) tauCandsIso50.push_back(tempTau_);
      if (tauPt_ >= 55) tauCandsIso55.push_back(tempTau_);
      if (tauPt_ >= 60) tauCandsIso60.push_back(tempTau_);
      if (tauPt_ >= 65) tauCandsIso65.push_back(tempTau_);
    }
    int tauCandsIso35Size = tauCandsIso35.size();
    int tauCandsIso40Size = tauCandsIso40.size();
    int tauCandsIso45Size = tauCandsIso45.size();
    int tauCandsIso50Size = tauCandsIso50.size();
    int tauCandsIso55Size = tauCandsIso55.size();
    int tauCandsIso60Size = tauCandsIso60.size();
    int tauCandsIso65Size = tauCandsIso65.size();



    // build container of jets
    TLorentzVector tempJet;
    vector<TLorentzVector> jetCands35;
    bool jet110Present = false;
    for (int iJet = 0; iJet < jetBx.size(); ++iJet) {
      if (jetBx[iJet] != 0) continue;

      float jetEt_ = jetEt[iJet];
      float jetEta_ = jetEta[iJet];
      if (jetEt_ >= 110) jet110Present = true; // used for possible 3jet case in old VBF seed
      if (jetEt_ >= 35 && fabs(jetEta_) <= 4.7) {
        tempJet.SetPtEtaPhiM(jetEt_, jetEta_, jetPhi[iJet], 0);
        jetCands35.push_back(tempJet);
      }
    }
    int jetCands35Size = jetCands35.size();
    // every seed needs at least one 35 Et(Pt) jet
    if (jetCands35Size == 0) continue;

    // fill more jet cand containers from loost jet container
    // maybe toggle this with an if statement for testing? i assume this takes a lot of processing time
    vector<TLorentzVector> jetCands40;
    vector<TLorentzVector> jetCands45;
    vector<TLorentzVector> jetCands50;
    vector<TLorentzVector> jetCands55;
    vector<TLorentzVector> jetCands60;
    float jetPt_;
    TLorentzVector tempJet_;
    for (int iJet = 0; iJet < jetCands35Size; ++iJet) {
      tempJet_ = jetCands35.at(iJet);
      jetPt_ = tempJet_.Pt();
      if (jetPt_ >= 40) jetCands40.push_back(tempJet_);
      if (jetPt_ >= 45) jetCands45.push_back(tempJet_);
      if (jetPt_ >= 50) jetCands50.push_back(tempJet_);
      if (jetPt_ >= 55) jetCands55.push_back(tempJet_);
      if (jetPt_ >= 60) jetCands60.push_back(tempJet_);
    }
    int jetCands40Size = jetCands40.size();
    int jetCands45Size = jetCands45.size();
    int jetCands50Size = jetCands50.size();
    int jetCands55Size = jetCands55.size();
    int jetCands60Size = jetCands60.size();

    // what follows is several pages of similar looking code
    // it makes crosscleaned jet containers by hand for different pt cuts of jets and taus
    // i did it this way because i couldn't figure out how to do it a fancier way in a short amount of time
    //
    // isoTau35 
    vector<TLorentzVector> jetCands35RmvOlTauCandsIso35;
    vector<TLorentzVector> jetCands40RmvOlTauCandsIso35;
    vector<TLorentzVector> jetCands45RmvOlTauCandsIso35;
    if (tauCandsIso35Size > 0 ) {
      if (jetCands35Size >= 2) jetCands35RmvOlTauCandsIso35 = crossCleanJets(jetCands35, tauCandsIso35);
      if (jetCands40Size >= 2) jetCands40RmvOlTauCandsIso35 = crossCleanJets(jetCands40, tauCandsIso35);
      if (jetCands45Size >= 2) jetCands45RmvOlTauCandsIso35 = crossCleanJets(jetCands45, tauCandsIso35);
    }
    else {
      jetCands35RmvOlTauCandsIso35 = jetCands35;
      jetCands40RmvOlTauCandsIso35 = jetCands40;
      jetCands45RmvOlTauCandsIso35 = jetCands45;
    }
    int jetCands35RmvOlTauCandsIso35Size = jetCands35RmvOlTauCandsIso35.size();
    int jetCands40RmvOlTauCandsIso35Size = jetCands40RmvOlTauCandsIso35.size();
    int jetCands45RmvOlTauCandsIso35Size = jetCands45RmvOlTauCandsIso35.size();

    // isoTau40
    vector<TLorentzVector> jetCands35RmvOlTauCandsIso40;
    vector<TLorentzVector> jetCands40RmvOlTauCandsIso40;
    vector<TLorentzVector> jetCands45RmvOlTauCandsIso40;
    vector<TLorentzVector> jetCands50RmvOlTauCandsIso40;
    if (tauCandsIso40Size > 0) {
      if (jetCands35Size >= 2) jetCands35RmvOlTauCandsIso40 = crossCleanJets(jetCands35, tauCandsIso40);
      if (jetCands40Size >= 2) jetCands40RmvOlTauCandsIso40 = crossCleanJets(jetCands40, tauCandsIso40);
      if (jetCands45Size >= 2) jetCands45RmvOlTauCandsIso40 = crossCleanJets(jetCands45, tauCandsIso40);
      if (jetCands50Size >= 2) jetCands50RmvOlTauCandsIso40 = crossCleanJets(jetCands50, tauCandsIso40);
    }
    else {
      jetCands35RmvOlTauCandsIso40 = jetCands35;
      jetCands40RmvOlTauCandsIso40 = jetCands40;
      jetCands45RmvOlTauCandsIso40 = jetCands45;
      jetCands50RmvOlTauCandsIso40 = jetCands50;
    }
    int jetCands35RmvOlTauCandsIso40Size = jetCands35RmvOlTauCandsIso40.size();
    int jetCands40RmvOlTauCandsIso40Size = jetCands40RmvOlTauCandsIso40.size();
    int jetCands45RmvOlTauCandsIso40Size = jetCands45RmvOlTauCandsIso40.size();
    int jetCands50RmvOlTauCandsIso40Size = jetCands50RmvOlTauCandsIso40.size();

    // isoTau45
    vector<TLorentzVector> jetCands35RmvOlTauCandsIso45;
    vector<TLorentzVector> jetCands40RmvOlTauCandsIso45;
    vector<TLorentzVector> jetCands45RmvOlTauCandsIso45;
    vector<TLorentzVector> jetCands50RmvOlTauCandsIso45;
    if (tauCandsIso45Size > 0) {
      if (jetCands35Size >= 2) jetCands35RmvOlTauCandsIso45 = crossCleanJets(jetCands35, tauCandsIso45);
      if (jetCands40Size >= 2) jetCands40RmvOlTauCandsIso45 = crossCleanJets(jetCands40, tauCandsIso45);
      if (jetCands45Size >= 2) jetCands45RmvOlTauCandsIso45 = crossCleanJets(jetCands45, tauCandsIso45);
      if (jetCands50Size >= 2) jetCands50RmvOlTauCandsIso45 = crossCleanJets(jetCands50, tauCandsIso45);
    }
    else {
      jetCands35RmvOlTauCandsIso45 = jetCands35;
      jetCands40RmvOlTauCandsIso45 = jetCands40;
      jetCands45RmvOlTauCandsIso45 = jetCands45;
      jetCands50RmvOlTauCandsIso45 = jetCands50;
    }
    int jetCands35RmvOlTauCandsIso45Size = jetCands35RmvOlTauCandsIso45.size();
    int jetCands40RmvOlTauCandsIso45Size = jetCands40RmvOlTauCandsIso45.size();
    int jetCands45RmvOlTauCandsIso45Size = jetCands45RmvOlTauCandsIso45.size();
    int jetCands50RmvOlTauCandsIso45Size = jetCands50RmvOlTauCandsIso45.size();

    // isoTau50
    vector<TLorentzVector> jetCands35RmvOlTauCandsIso50;
    vector<TLorentzVector> jetCands40RmvOlTauCandsIso50;
    vector<TLorentzVector> jetCands45RmvOlTauCandsIso50; 
    vector<TLorentzVector> jetCands50RmvOlTauCandsIso50; 

    if (tauCandsIso50Size > 0) {
      if (jetCands35Size >= 2) jetCands35RmvOlTauCandsIso50 = crossCleanJets(jetCands35, tauCandsIso50);
      if (jetCands40Size >= 2) jetCands40RmvOlTauCandsIso50 = crossCleanJets(jetCands40, tauCandsIso50);
      if (jetCands45Size >= 2) jetCands45RmvOlTauCandsIso50 = crossCleanJets(jetCands45, tauCandsIso50);
      if (jetCands50Size >= 2) jetCands50RmvOlTauCandsIso50 = crossCleanJets(jetCands50, tauCandsIso50);
    }
    else {
      jetCands35RmvOlTauCandsIso50 = jetCands35;
      jetCands40RmvOlTauCandsIso50 = jetCands40;
      jetCands45RmvOlTauCandsIso50 = jetCands45;
      jetCands50RmvOlTauCandsIso50 = jetCands50;
    }
    int jetCands35RmvOlTauCandsIso50Size = jetCands35RmvOlTauCandsIso50.size();
    int jetCands40RmvOlTauCandsIso50Size = jetCands40RmvOlTauCandsIso50.size();
    int jetCands45RmvOlTauCandsIso50Size = jetCands45RmvOlTauCandsIso50.size();
    int jetCands50RmvOlTauCandsIso50Size = jetCands50RmvOlTauCandsIso50.size();


    // odd duckling for seed 3
    vector<TLorentzVector> jetCands35RmvOlTauCands35;
    if (tauCands35Size > 0) {
      if (jetCands35Size >= 2) jetCands35RmvOlTauCands35 = crossCleanJets(jetCands35, tauCands35);
    }
    int jetCands35RmvOlTauCands35Size = jetCands35RmvOlTauCands35.size();

    //------------------------finished making containers, now checking obj numbers and masses and passing triggers----------------------//
   
    // L1_DoubleIsoTau32er2p1
    if (tauCandsIso32Size >= 2) passDiTau = 1;

    // L1_Jet110_Jet35_Mass_Min620 (seed 00)
    // find highest mjj pair of jets
    // jet110Present used for possible 3 jet case in old VBF L1 logic
    if (jetCands35Size >= 2) {
      float mjj_seed00 = 0; float tempMjj = 0;
      for (int iCands = 0; iCands < jetCands35Size; ++iCands) {
        for (int jCands = 0; jCands < jetCands35Size; ++jCands) {
          if (iCands >= jCands) continue;
          // one jet in the event must have Et(Pt) >= 110
          if (jetCands35.at(iCands).Pt() < 110 && jetCands35.at(jCands).Pt() < 110 && !jet110Present) continue;
          tempMjj = (jetCands35.at(iCands) + jetCands35.at(jCands)).M();
          if (tempMjj > mjj_seed00) mjj_seed00 = tempMjj;
        }
      }
      if (mjj_seed00 >= 620) passOld = 1;
    }

    // L1_DoubleJet35_IsoTau45_Mjj450_RmvOl (seed 0)
    // find highest mjj pair of jets from container of crosscleaned jets
    if (jetCands35RmvOlTauCandsIso45Size >= 2 && tauCandsIso45Size >= 1) {
      float mjj_seed0 = 0; float tempMjj = 0;
      for (int iCands = 0; iCands < jetCands35RmvOlTauCandsIso45Size; ++iCands) {
        for (int jCands = 0; jCands < jetCands35RmvOlTauCandsIso45Size; ++jCands) {
          if (iCands >= jCands) continue;
          tempMjj = (jetCands35RmvOlTauCandsIso45.at(iCands) + jetCands35RmvOlTauCandsIso45.at(jCands)).M();
          if (tempMjj > mjj_seed0) mjj_seed0 = tempMjj;
        }
      }
      if (mjj_seed0 >= 450) passNew = 1;
    }

    // L1_DoubleJet35_DoubleIsoTau40_MassAnyTwo400_RmvOl (seed 1)
    if (jetCands35RmvOlTauCandsIso40Size >= 2 && tauCandsIso40Size >= 2) {
      float mjotjot_seed1 = 0; float tempMjotjot = 0; // "jot" as in "jet or tau"
      vector<TLorentzVector> combinedCCJets35TausIso40;
      combinedCCJets35TausIso40.insert(combinedCCJets35TausIso40.begin(), jetCands35RmvOlTauCandsIso40.begin(), jetCands35RmvOlTauCandsIso40.end());
      combinedCCJets35TausIso40.insert(combinedCCJets35TausIso40.end(), tauCandsIso40.begin(), tauCandsIso40.end());
      int combinedCCJets35TausIso40Size = combinedCCJets35TausIso40.size();
      for (int iObj = 0; iObj < combinedCCJets35TausIso40Size; ++iObj) {
        for (int jObj = 0; jObj < combinedCCJets35TausIso40Size; ++jObj) {
          if (jObj >= iObj) continue;
          //overlapped = (combinedContainer.at(iObj).DeltaR(combinedContainer.at(jObj)) < 0.5);
          tempMjotjot = (combinedCCJets35TausIso40.at(iObj) + combinedCCJets35TausIso40.at(jObj)).M();
          if (tempMjotjot > mjotjot_seed1) mjotjot_seed1 = tempMjotjot;
        }
      }
      if (mjotjot_seed1 >= 400) passSeed1 = 1;
    }

    // L1_DoubleJet35_IsoTau45_MassAnyTwo400_RmvOl (seed 2, most like new VBF)
    if (jetCands35RmvOlTauCandsIso45Size >= 2 && tauCandsIso45Size >= 1) {
      float mjotjot_seed2 = 0; float tempMjotjot = 0; // "jot" as in "jet or tau"
      vector<TLorentzVector> combinedCCJets35TausIso45;
      combinedCCJets35TausIso45.insert(combinedCCJets35TausIso45.begin(), jetCands35RmvOlTauCandsIso45.begin(), jetCands35RmvOlTauCandsIso45.end());
      combinedCCJets35TausIso45.insert(combinedCCJets35TausIso45.end(), tauCandsIso45.begin(), tauCandsIso45.end());
      int combinedCCJets35TausIso45Size = combinedCCJets35TausIso45.size();
      for (int iObj = 0; iObj < combinedCCJets35TausIso45Size; ++iObj) {
        for (int jObj = 0; jObj < combinedCCJets35TausIso45Size; ++jObj) {
          if (jObj >= iObj) continue;
          tempMjotjot = (combinedCCJets35TausIso45.at(iObj) + combinedCCJets35TausIso45.at(jObj)).M();
          if (tempMjotjot > mjotjot_seed2) mjotjot_seed2 = tempMjotjot;
        }
      }
//change above to use mass function
      if (mjotjot_seed2 >= 350) passSeed2_3545350 = 1; 
      if (mjotjot_seed2 >= 400) passSeed2 = 1; //passSeed2_3545400
      if (mjotjot_seed2 >= 450) passSeed2_3545450 = 1;
      if (mjotjot_seed2 >= 500) passSeed2_3545500 = 1;
      if (mjotjot_seed2 >= 550) passSeed2_3545550 = 1;
      if (mjotjot_seed2 >= 600) passSeed2_3545600 = 1;
    }

    // L1_Jet35_Tau35_MassJetTau450_IsoTau45_RmvOl (seed 3)
    if (jetCands35Size >= 1 && tauCands35Size >= 1 && tauCandsIso45Size >= 1) {
      float mjt_seed3 = 0; float tempMjt = 0;
      for (int iJet = 0; iJet < jetCands35Size; ++iJet) {
        for (int iTau = 0; iTau < tauCands35Size; ++iTau) {
          tempMjt = (jetCands35.at(iJet) + tauCands35.at(iTau)).M();
          if (tempMjt > mjt_seed3) mjt_seed3 = tempMjt;
        }
      }   
      if (mjt_seed3 >= 450) passSeed3 = 1;
    }
/***
  //------------------------------seed 2 varying cuts-----------------------//
  
  // first, make all the jet containers...
  // second, make all the tau containers...
  // third, cross clean each jet container wrt each tau container
  // fourth, find Mjotjots and cut
  // 
  // jetCands35
  // isoTauCands32
  vector<TLorentzVector> jetCands40;
  vector<TLorentzVector> jetCands45;
  vector<TLorentzVector> jetCands50;
  vector<TLorentzVector> jetCands55;
  vector<TLorentzVector> jetCands60;
  float jetPt_;
  TLorentzVector tempJet_;
  for (int iJet = 0; iJet < jetCands35Size; ++iJet) {
    tempJet_ = jetCands35.at(iJet);
    jetPt_ = tempJet_.Pt();
    if (jetPt_ >= 40) jetCands40.push_back(tempJet_);
    if (jetPt_ >= 45) jetCands45.push_back(tempJet_);
    if (jetPt_ >= 50) jetCands50.push_back(tempJet_);
    if (jetPt_ >= 55) jetCands55.push_back(tempJet_);
    if (jetPt_ >= 60) jetCands60.push_back(tempJet_);
  }
  int jetCands40Size = jetCands40.size();
  int jetCands45Size = jetCands45.size();
  int jetCands50Size = jetCands50.size();
  int jetCands55Size = jetCands55.size();
  int jetCands60Size = jetCands60.size();

  vector<TLorentzVector> tauCandsIso35;
  vector<TLorentzVector> tauCandsIso50; 
  vector<TLorentzVector> tauCandsIso55;
  vector<TLorentzVector> tauCandsIso60;
  vector<TLorentzVector> tauCandsIso65;
  float tauPt_;
  TLorentzVector tempTau_;
  for (int iTau = 0; iTau < tauCandsIso32Size; ++iTau) {
    tempTau_ = tauCandsIso32.at(iTau);
    tauPt_ = tempTau_.Pt();
    if (tauPt_ >= 35) tauCandsIso35.push_back(tempTau_);
    if (tauPt_ >= 50) tauCandsIso50.push_back(tempTau_);
    if (tauPt_ >= 55) tauCandsIso55.push_back(tempTau_);
    if (tauPt_ >= 60) tauCandsIso60.push_back(tempTau_);
    if (tauPt_ >= 65) tauCandsIso65.push_back(tempTau_);
  }
  int tauCandsIso35Size = tauCandsIso35.size();
  int tauCandsIso50Size = tauCandsIso50.size();
  int tauCandsIso55Size = tauCandsIso55.size();
  int tauCandsIso60Size = tauCandsIso60.size();
  int tauCandsIso65Size = tauCandsIso65.size();

  vector<TLorentzVector> jetCands35RmvOlTauCandsIso35;
  vector<TLorentzVector> jetCands40RmvOlTauCandsIso35;
  vector<TLorentzVector> jetCands45RmvOlTauCandsIso35;
  if (tauCandsIso35Size > 0 ) {
    for (int iTau35 = 0; iTau35 < tauCandsIso35Size; ++iTau35) {
      TLorentzVector tempTauIso35_;
      tempTauIso35_ = tauCandsIso35.at(iTau35);
      for (int iJet35 = 0; iJet35 < jetCands35Size; ++iJet35) {
        TLorentzVector tempJet35_;
        tempJet35_ = jetCands35.at(iJet35);
        if (tempTauIso35_.DeltaR(tempJet35_) > 0.5) jetCands35RmvOlTauCandsIso35.push_back(tempJet35_);
      }
      for (int iJet40 = 0; iJet40 < jetCands40Size; ++iJet40) {
        TLorentzVector tempJet40_;
        tempJet40_ = jetCands40.at(iJet40);
        if (tempTauIso35_.DeltaR(tempJet40_) > 0.5) jetCands40RmvOlTauCandsIso35.push_back(tempJet40_);
      }
      for (int iJet45 = 0; iJet45 < jetCands45Size; ++iJet45) {
        TLorentzVector tempJet45_;
        tempJet45_ = jetCands45.at(iJet45);
        if (tempTauIso35_.DeltaR(tempJet45_) > 0.5) jetCands45RmvOlTauCandsIso35.push_back(tempJet45_);
      }
    }
  }
  else {
    jetCands35RmvOlTauCandsIso35 = jetCands35;
    jetCands40RmvOlTauCandsIso35 = jetCands40;
    jetCands45RmvOlTauCandsIso35 = jetCands45;
  }
  int jetCands35RmvOlTauCandsIso35Size = jetCands35RmvOlTauCandsIso35.size();
  int jetCands40RmvOlTauCandsIso35Size = jetCands40RmvOlTauCandsIso35.size();
  int jetCands45RmvOlTauCandsIso35Size = jetCands45RmvOlTauCandsIso35.size();


  vector<TLorentzVector> jetCands40RmvOlTauCandsIso40;
  vector<TLorentzVector> jetCands45RmvOlTauCandsIso40;
  vector<TLorentzVector> jetCands50RmvOlTauCandsIso40;
  if (tauCandsIso40Size > 0) {
    for (int iTau40 = 0; iTau40 < tauCandsIso40Size; ++iTau40) {
      TLorentzVector tempTauIso40_;
      tempTauIso40_ = tauCandsIso40.at(iTau40);
      for (int iJet40 = 0; iJet40 < jetCands40Size; ++iJet40) {
        TLorentzVector tempJet40_;
        tempJet40_ = jetCands40.at(iJet40);
        if (tempTauIso40_.DeltaR(tempJet40_) > 0.5) jetCands40RmvOlTauCandsIso40.push_back(tempJet40_);
      }
      for (int iJet45 = 0; iJet45 < jetCands45Size; ++iJet45) {
        TLorentzVector tempJet45_;
        tempJet45_ = jetCands45.at(iJet45);
        if (tempTauIso40_.DeltaR(tempJet45_) > 0.5) jetCands45RmvOlTauCandsIso40.push_back(tempJet45_);
      }
      for (int iJet50 = 0; iJet50 < jetCands50Size; ++iJet50) {
        TLorentzVector tempJet50_;
        tempJet50_ = jetCands50.at(iJet50);
        if (tempTauIso40_.DeltaR(tempJet50_) > 0.5) jetCands50RmvOlTauCandsIso40.push_back(tempJet50_);
      }    
    }
  }
  else {
    jetCands40RmvOlTauCandsIso40 = jetCands40;
    jetCands45RmvOlTauCandsIso40 = jetCands45;
    jetCands50RmvOlTauCandsIso40 = jetCands50;
  }
  int jetCands40RmvOlTauCandsIso40Size = jetCands40RmvOlTauCandsIso40.size();
  int jetCands45RmvOlTauCandsIso40Size = jetCands45RmvOlTauCandsIso40.size();
  int jetCands50RmvOlTauCandsIso40Size = jetCands50RmvOlTauCandsIso40.size();

  //


  vector<TLorentzVector> jetCands35RmvOlTauCandsIso50;
  vector<TLorentzVector> jetCands40RmvOlTauCandsIso50;
  vector<TLorentzVector> jetCands45RmvOlTauCandsIso50; 
  vector<TLorentzVector> jetCands50RmvOlTauCandsIso50; 

  if (tauCandsIso50Size > 0) {
    if (jetCands35Size >= 2) jetCands35RmvOlTauCandsIso50 = crossCleanJets(jetCands35, tauCandsIso50);
    if (jetCands40Size >= 2) jetCands40RmvOlTauCandsIso50 = crossCleanJets(jetCands40, tauCandsIso50);
    if (jetCands45Size >= 2) jetCands45RmvOlTauCandsIso50 = crossCleanJets(jetCands45, tauCandsIso50);
    if (jetCands50Size >= 2) jetCands50RmvOlTauCandsIso50 = crossCleanJets(jetCands50, tauCandsIso50);
  }
  //else {
  //  jetCands35RmvOlTauCandsIso50 = jetCands35;
  //}
  //
  if (tauCandsIso50Size > 0) {
    // check jet sizes too
    for (int iTau = 0; iTau < tauCandsIso50Size; ++iTau) {
      TLorentzVector tempTauIso50_;
      tempTauIso50_ = tauCandsIso50.at(iTau);
      //for (int iJet35 = 0; iJet35 < jetCands35Size; ++iJet35) {
      //  TLorentzVector tempJet35_;
      //  tempJet35_ = jetCands35.at(iJet35);
      //  if (tempTauIso50_.DeltaR(tempJet35_) > 0.5) jetCands35RmvOlTauCandsIso50.push_back(tempJet35_);
      //}
      for (int iJet40 = 0; iJet40 < jetCands40Size; ++iJet40) {
        TLorentzVector tempJet40_;
        tempJet40_ = jetCands40.at(iJet40);
        if (tempTauIso50_.DeltaR(tempJet40_) > 0.5) jetCands40RmvOlTauCandsIso50.push_back(tempJet40_);
      }
      for (int iJet45 = 0; iJet45 < jetCands45Size; ++iJet45) {
        TLorentzVector tempJet45_;
        tempJet45_ = jetCands45.at(iJet45);
        if (tempTauIso50_.DeltaR(tempJet45_) > 0.5) jetCands45RmvOlTauCandsIso50.push_back(tempJet45_);
      }
      for (int iJet50 = 0; iJet50 < jetCands50Size; ++iJet50) {
        TLorentzVector tempJet50_;
        tempJet50_ = jetCands50.at(iJet50);
        if (tempTauIso50_.DeltaR(tempJet50_) > 0.5) jetCands50RmvOlTauCandsIso50.push_back(tempJet50_);
      }
    }
  }//
  else {
    jetCands35RmvOlTauCandsIso50 = jetCands35;
    jetCands40RmvOlTauCandsIso50 = jetCands40;
    jetCands45RmvOlTauCandsIso50 = jetCands45;
    jetCands50RmvOlTauCandsIso50 = jetCands50;
  }
  int jetCands35RmvOlTauCandsIso50Size = jetCands35RmvOlTauCandsIso50.size();
  int jetCands40RmvOlTauCandsIso50Size = jetCands40RmvOlTauCandsIso50.size();
  int jetCands45RmvOlTauCandsIso50Size = jetCands45RmvOlTauCandsIso50.size();
  int jetCands50RmvOlTauCandsIso50Size = jetCands50RmvOlTauCandsIso50.size();

*/
  if (tauCandsIso35Size >= 1) {
    if (jetCands35RmvOlTauCandsIso35Size >= 2) {
      float mjotjot_3535 = highestMassOfPair(tauCandsIso35, jetCands35RmvOlTauCandsIso35);
      if (mjotjot_3535 >= 350) passSeed2_3535350 = 1;
      if (mjotjot_3535 >= 400) passSeed2_3535400 = 1;
      if (mjotjot_3535 >= 450) passSeed2_3535450 = 1;
      if (mjotjot_3535 >= 500) passSeed2_3535500 = 1;
    }
  }

  if (tauCandsIso40Size >= 1) {
    if (jetCands35RmvOlTauCandsIso40Size >= 2) {
      float mjotjot_3540 = highestMassOfPair(tauCandsIso40, jetCands35RmvOlTauCandsIso40);
      if (mjotjot_3540 >= 350) passSeed2_3540350 = 1;
      if (mjotjot_3540 >= 400) passSeed2_3540400 = 1;
      if (mjotjot_3540 >= 450) passSeed2_3540450 = 1;
      if (mjotjot_3540 >= 500) passSeed2_3540500 = 1;
      if (mjotjot_3540 >= 550) passSeed2_3540550 = 1;
      if (mjotjot_3540 >= 600) passSeed2_3540600 = 1;
    }
  }

  if (tauCandsIso50Size >= 1) {
    if (jetCands35RmvOlTauCandsIso50Size >= 2) {
      float mjotjot_3550 = highestMassOfPair(tauCandsIso50, jetCands35RmvOlTauCandsIso50);
      if (mjotjot_3550 >= 350) passSeed2_3550350 = 1;
      if (mjotjot_3550 >= 400) passSeed2_3550400 = 1;
      if (mjotjot_3550 >= 450) passSeed2_3550450 = 1;
      if (mjotjot_3550 >= 500) passSeed2_3550500 = 1;
      if (mjotjot_3550 >= 550) passSeed2_3550550 = 1;
      if (mjotjot_3550 >= 600) passSeed2_3550600 = 1;
    }
  }


  passDiTauCount += passDiTau;
  passOldCount += passOld;
  passNewCount += passNew;
  passSeed1Count += passSeed1;
  passSeed2Count += passSeed2;
  passSeed3Count += passSeed3;

  // variations of seed 2
  passSeed2_3535350_count += passSeed2_3535350;
  passSeed2_3535400_count += passSeed2_3535400;
  passSeed2_3535450_count += passSeed2_3535450;
  passSeed2_3535500_count += passSeed2_3535500;

  passSeed2_3545350_count += passSeed2_3545350;
  passSeed2_3545450_count += passSeed2_3545450;
  passSeed2_3545500_count += passSeed2_3545500;
  passSeed2_3545550_count += passSeed2_3545550;
  passSeed2_3545600_count += passSeed2_3545600;

  passSeed2_3540350_count += passSeed2_3540350;
  passSeed2_3540400_count += passSeed2_3540400;
  passSeed2_3540450_count += passSeed2_3540450;
  passSeed2_3540500_count += passSeed2_3540500;
  passSeed2_3540550_count += passSeed2_3540550;
  passSeed2_3540600_count += passSeed2_3540600;

  passSeed2_3550350_count += passSeed2_3550350;
  passSeed2_3550400_count += passSeed2_3550400;
  passSeed2_3550450_count += passSeed2_3550450;
  passSeed2_3550500_count += passSeed2_3550500;
  passSeed2_3550550_count += passSeed2_3550550;
  passSeed2_3550600_count += passSeed2_3550600;
  // end variations

  olDiTauSeed1 += (passDiTau && passSeed1);
  olDiTauSeed2 += (passDiTau && passSeed2);
  olDiTauSeed3 += (passDiTau && passSeed3);

  olOldSeed1 += (passOld && passSeed1);
  olOldSeed2 += (passOld && passSeed2);
  olOldSeed3 += (passOld && passSeed3);

  olNewSeed1 += (passNew && passSeed1);
  olNewSeed2 += (passNew && passSeed2);
  olNewSeed3 += (passNew && passSeed3);

  orDiTauSeed1 += (passDiTau || passSeed1);
  orDiTauSeed2 += (passDiTau || passSeed2);
  orDiTauSeed3 += (passDiTau || passSeed3);

  orOldSeed1 += (passOld || passSeed1);
  orOldSeed2 += (passOld || passSeed2);
  orOldSeed3 += (passOld || passSeed3);

  orNewSeed1 += (passNew || passSeed1);
  orNewSeed2 += (passNew || passSeed2);
  orNewSeed3 += (passNew || passSeed3);

  } // end event loop

  //------------------------------------print results to terminal-----------------------------------//
  //for (auto it = lumis.begin(); it != lumis.end(); ++it) {
  //  cout << it->first << " run " << it->second << " LS " << endl;
  //}
  cout << eventCount << " Events Scanned" << endl;
  cout << runCount << " Events in Selected Run (323755)" << endl;
  cout << lumis.size() << " Lumi Sections in Run" << endl;
  float Kfactor = 17881*40*(2.0/1.849)/(lumis.size() * 23.31 * 8); // units of Hz
  float Ofactor = 2544 * 11255.6 * (2.0 / 1.849)*(1/float(runCount)); // inst init lumi from report on OMS, used 44 LS lumi from list of init lumis per LS

  cout << "# Pass" << '\t' << "Eqn 1" << '\t' << "Eqn 2 " << endl;
 
  cout << passDiTauCount << '\t' << passDiTauCount*Kfactor << '\t' << passDiTauCount*Ofactor << '\t' << "DiTau (L1_DoubleIsoTau32er2p1)" << endl;
  cout << passOldCount << '\t' << passOldCount*Kfactor <<     '\t' << passOldCount*Ofactor << '\t' << "old VBF (L1_Jet110_Jet35_Mass_Min620)" << endl;
  cout << passNewCount << '\t' << passNewCount*Kfactor <<     '\t' << passNewCount*Ofactor << '\t' << "new VBF (L1_DoubleJet35_IsoTau45_Mjj450_RmvOl)" << endl;

  cout << passSeed1Count << '\t' << passSeed1Count*Kfactor << '\t' << passSeed1Count*Ofactor << '\t' << "seed 1 (L1_DoubleJet35_DoubleIsoTau40_MassAnyTwo400_RmvOl)" << endl;
  cout << passSeed2Count << '\t' << passSeed2Count*Kfactor << '\t' << passSeed2Count*Ofactor << '\t' << "seed 2 (L1_DoubleJet35_IsoTau45_MassAnyTwo400_RmvOl)" << endl;
  cout << passSeed3Count << '\t' << passSeed3Count*Kfactor << '\t' << passSeed3Count*Ofactor << '\t' << "seed 3 (L1_Jet35_Tau35_IsoTau45_MassJetTau450_RmvOl)" << endl; 

  cout << "Overlap Seed" << '\t' << "1" << '\t' <<  "2" << '\t' << "3" << endl;
  cout << '\t' << '\t' << olDiTauSeed1 << '\t' << olDiTauSeed2 << '\t' << olDiTauSeed3 << '\t' << "DiTau ol" << endl;
  cout << '\t' << '\t' << olOldSeed1 << '\t' << olOldSeed2 << '\t' << olOldSeed3 << '\t' << "Old ol" << endl;
  cout << '\t' << '\t' << olNewSeed1 << '\t' << olNewSeed2 << '\t' << olNewSeed3 << '\t' << "New ol" << endl;

  cout << "OR Seed" << '\t' << '\t' << "1" << '\t' <<  "2" << '\t' << "3" << endl;
  cout << '\t' << '\t' << orDiTauSeed1 << '\t' << orDiTauSeed2 << '\t' << orDiTauSeed3 << '\t' << "DiTau or" << endl;
  cout << '\t' << '\t' << orOldSeed1 << '\t' << orOldSeed2 << '\t' << orOldSeed3 << '\t' << "Old or" << endl;
  cout << '\t' << '\t' << orNewSeed1 << '\t' << orNewSeed2 << '\t' << orNewSeed3 << '\t' << "New or" << endl;


  cout << "divide number of \"switched files\" by two because we have two TChains" << endl;

  cout << "varying parameters for Seed 2" << endl;
  cout << "dbl jet 35, isotau 35" << endl;
  cout << passSeed2_3535350_count << '\t' << "L1_DoubleJet35_IsoTau35_MassAnyTwo350_RmvOl" << endl;
  cout << passSeed2_3535400_count << '\t' << "L1_DoubleJet35_IsoTau35_MassAnyTwo400_RmvOl" << endl;
  cout << passSeed2_3535450_count << '\t' << "L1_DoubleJet35_IsoTau35_MassAnyTwo450_RmvOl" << endl;
  cout << passSeed2_3535500_count << '\t' << "L1_DoubleJet35_IsoTau35_MassAnyTwo500_RmvOl" << endl;
  cout << "dbl jet 35, isotau 40" << endl;
  cout << passSeed2_3540350_count << '\t' << "L1_DoubleJet35_IsoTau40_MassAnyTwo350_RmvOl" << endl;
  cout << passSeed2_3540400_count << '\t' << "L1_DoubleJet35_IsoTau40_MassAnyTwo400_RmvOl" << endl;
  cout << passSeed2_3540450_count << '\t' << "L1_DoubleJet35_IsoTau40_MassAnyTwo450_RmvOl" << endl;
  cout << passSeed2_3540500_count << '\t' << "L1_DoubleJet35_IsoTau40_MassAnyTwo500_RmvOl" << endl;
  cout << passSeed2_3540550_count << '\t' << "L1_DoubleJet35_IsoTau40_MassAnyTwo550_RmvOl" << endl;
  cout << passSeed2_3540600_count << '\t' << "L1_DoubleJet35_IsoTau40_MassAnyTwo600_RmvOl" << endl;
  cout << "dbl jet 35, isotau 45" << endl;
  cout << passSeed2_3545350_count << '\t' << "L1_DoubleJet35_IsoTau45_MassAnyTwo350_RmvOl" << endl;
  cout << passSeed2_3545450_count << '\t' << "L1_DoubleJet35_IsoTau45_MassAnyTwo450_RmvOl" << endl;
  cout << passSeed2_3545500_count << '\t' << "L1_DoubleJet35_IsoTau45_MassAnyTwo500_RmvOl" << endl;
  cout << passSeed2_3545550_count << '\t' << "L1_DoubleJet35_IsoTau45_MassAnyTwo550_RmvOl" << endl;
  cout << passSeed2_3545600_count << '\t' << "L1_DoubleJet35_IsoTau45_MassAnyTwo600_RmvOl" << endl;
  cout << "dbl jet 35, isotau 50" << endl;
  cout << passSeed2_3550350_count << '\t' << "L1_DoubleJet35_IsoTau50_MassAnyTwo350_RmvOl" << endl;
  cout << passSeed2_3550400_count << '\t' << "L1_DoubleJet35_IsoTau50_MassAnyTwo400_RmvOl" << endl;
  cout << passSeed2_3550450_count << '\t' << "L1_DoubleJet35_IsoTau50_MassAnyTwo450_RmvOl" << endl;
  cout << passSeed2_3550500_count << '\t' << "L1_DoubleJet35_IsoTau50_MassAnyTwo500_RmvOl" << endl;
  cout << passSeed2_3550550_count << '\t' << "L1_DoubleJet35_IsoTau50_MassAnyTwo550_RmvOl" << endl;
  cout << passSeed2_3550600_count << '\t' << "L1_DoubleJet35_IsoTau50_MassAnyTwo600_RmvOl" << endl;
}
