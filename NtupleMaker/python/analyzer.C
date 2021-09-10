#define analyzer_cxx
#include "analyzer.h"
#include "smaller_header.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <vector>

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

  int passDiTauCount = 0;
  int passOldCount = 0;
  int passNewCount = 0;

  int passSeed1Count = 0;
  int passSeed2Count = 0;
  int passSeed3Count = 0;

  int olDiTauSeed1 = 0;
  int olDiTauSeed2 = 0;
  int olDiTauSeed3 = 0;
  int olOldSeed1 = 0;
  int olOldSeed2 = 0;
  int olOldSeed3 = 0;
  int olNewSeed1 = 0;
  int olNewSeed2 = 0;
  int olNewSeed3 = 0;

  // start event loop
  //for (Long64_t jentry=0; jentry<nentries1; ++jentry) { // full dataset
  //for (Long64_t jentry=0; jentry<4000000; ++jentry) {
  for (Long64_t jentry=11100000; jentry<11400000; ++jentry) { // full run 323755

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
    runCount += 1;

    bool restrictLumi = true;
    if (restrictLumi && (lumi < 44 || lumi > 144)) continue;
    lumis.insert(make_pair(run,lumi));

    int passDiTau = 0;
    int passOld = 0;
    int passNew = 0;
    int passSeed1 = 0;
    int passSeed2 = 0;
    int passSeed3 = 0;

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

    
    // make two smaller containers of IsoTaus w higher pt requirement
    vector<TLorentzVector> tauCandsIso40;
    for (int iTau = 0; iTau < tauCandsIso32Size; ++iTau) {
      if (tauCandsIso32.at(iTau).Pt() >= 40) tauCandsIso40.push_back(tauCandsIso32.at(iTau));
    }
    int tauCandsIso40Size = tauCandsIso40.size();
    
    vector<TLorentzVector> tauCandsIso45;
    for (int iTau = 0; iTau < tauCandsIso40Size; ++iTau) {
      if (tauCandsIso40.at(iTau).Pt() >= 45) tauCandsIso45.push_back(tauCandsIso40.at(iTau));
    }
    int tauCandsIso45Size = tauCandsIso45.size();

    // make three cross-cleaned jet containers
    // one wrt 45 isotaus, one wrt 40 isotaus, and one wrt 35 taus
    vector<TLorentzVector> jetCands35RmvOlTauCandsIso40;
    if (tauCandsIso40Size > 0) {
      for (int iTau = 0; iTau < tauCandsIso40Size; ++iTau) {
        for (int iJet = 0; iJet < jetCands35Size; ++iJet) {
          if (tauCandsIso40.at(iTau).DeltaR(jetCands35.at(iJet)) > 0.5) jetCands35RmvOlTauCandsIso40.push_back(jetCands35.at(iJet)); 
        }
      }
    }
    else {jetCands35RmvOlTauCandsIso40 = jetCands35;} // if there aren't any taus, then we don't need to cc. event is rejected later
    int jetCands35RmvOlTauCandsIso40Size = jetCands35RmvOlTauCandsIso40.size();

    vector<TLorentzVector> jetCands35RmvOlTauCandsIso45;
    if (tauCandsIso45Size > 0) {
      for (int iTau = 0; iTau < tauCandsIso45Size; ++iTau) {
        for (int iJet = 0; iJet < jetCands35Size; ++iJet) {
          if (tauCandsIso45.at(iTau).DeltaR(jetCands35.at(iJet)) > 0.5) jetCands35RmvOlTauCandsIso45.push_back(jetCands35.at(iJet)); 
        }
      }
    }
    else {jetCands35RmvOlTauCandsIso45 = jetCands35;} // if there aren't any taus, then we don't need to cc. event is rejected later
    int jetCands35RmvOlTauCandsIso45Size = jetCands35RmvOlTauCandsIso45.size();

    vector<TLorentzVector> jetCands35RmvOlTauCands35;
    if (tauCands35Size > 0) {
      for (int iTau = 0; iTau < tauCands35Size; ++iTau) {
        for (int iJet = 0; iJet < jetCands35Size; ++iJet) {
          if (tauCands35.at(iTau).DeltaR(jetCands35.at(iJet)) > 0.5) jetCands35RmvOlTauCands35.push_back(jetCands35.at(iJet));
        }
      }
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
      if (mjotjot_seed2 >= 400) passSeed2 = 1;
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

  passDiTauCount += passDiTau;
  passOldCount += passOld;
  passNewCount += passNew;
  passSeed1Count += passSeed1;
  passSeed2Count += passSeed2;
  passSeed3Count += passSeed3;

  olDiTauSeed1 += (passDiTau && passSeed1);
  olDiTauSeed2 += (passDiTau && passSeed2);
  olDiTauSeed3 += (passDiTau && passSeed3);

  olOldSeed1 += (passOld && passSeed1);
  olOldSeed2 += (passOld && passSeed2);
  olOldSeed3 += (passOld && passSeed3);

  olNewSeed1 += (passNew && passSeed1);
  olNewSeed2 += (passNew && passSeed2);
  olNewSeed3 += (passNew && passSeed3);

  } // end event loop

  //------------------------------------print results to terminal-----------------------------------//
  //for (auto it = lumis.begin(); it != lumis.end(); ++it) {
  //  cout << it->first << " run " << it->second << " LS " << endl;
  //}
  cout << eventCount << " Events Scanned" << endl;
  cout << runCount << " Events in Selected Run (323755)" << endl;
  cout << lumis.size() << " Lumi Sections in Run" << endl;
  float Kfactor = 17881*40/(lumis.size() * 23.31); // units of Hz
  float Ofactor = 2544 * 11255.6 * (2.0 / 1.849)*(1/float(runCount)); // inst init lumi from report on OMS, used 44 LS lumi from list of init lumis per LS

  cout << "# Pass" << '\t' << "K. Rate" << '\t' << "O. Rate" << endl;
 
  cout << passDiTauCount << '\t' << passDiTauCount*Kfactor << '\t' << passDiTauCount*Ofactor << "  DiTau (L1_DoubleIsoTau32er2p1)" << endl;
  cout << passOldCount << '\t' << passOldCount*Kfactor <<     '\t' << passOldCount*Ofactor << "  old VBF (L1_Jet110_Jet35_Mass_Min620)" << endl;
  cout << passNewCount << '\t' << passNewCount*Kfactor <<     '\t' << passNewCount*Ofactor << "  new VBF (L1_DoubleJet35_IsoTau45_Mjj450_RmvOl)" << endl;

  cout << passSeed1Count << '\t' << passSeed1Count*Kfactor << '\t' << passSeed1Count*Ofactor << "  seed 1 (L1_DoubleJet35_DoubleIsoTau40_MassAnyTwo400_RmvOl)" << endl;
  cout << passSeed2Count << '\t' << passSeed2Count*Kfactor << '\t' << passSeed2Count*Ofactor << "  seed 2 (L1_DoubleJet35_IsoTau45_MassAnyTwo400_RmvOl)" << endl;
  cout << passSeed3Count << '\t' << passSeed3Count*Kfactor << '\t' << passSeed3Count*Ofactor << "  seed 3 (L1_Jet35_Tau35_IsoTau45_MassJetTau450_RmvOl)" << endl; 

  cout << "Overlap with XXX and Seed 1, 2, 3" << endl;
  cout << olDiTauSeed1 << '\t' << olDiTauSeed2 << '\t' << olDiTauSeed3 << '\t' << "DiTau ol" << endl;
  cout << olOldSeed1 << '\t' << olOldSeed2 << '\t' << olOldSeed3 << '\t' << "Old ol" << endl;
  cout << olNewSeed1 << '\t' << olNewSeed2 << '\t' << olNewSeed3 << '\t' << "New ol" << endl;

  cout << "divide number of \"switched files\" by two because we have two TChains" << endl;
}
