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

void setArrayElements(int array[], float value, const int cutoffs[]) {
  int arraySize = 6; // not pretty
  for (int i = 0; i < arraySize; ++i) { if (value >= cutoffs[i]) array[i] = 1; }
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

  int mjjCuts[6] = {350, 400, 450, 500, 550, 600};
  //jet 35
  int passSeed2_3535All[6] = {0,0,0,0,0,0};
  int passSeed2_3540All[6] = {0,0,0,0,0,0};
  int passSeed2_3545All[6] = {0,0,0,0,0,0};
  int passSeed2_3550All[6] = {0,0,0,0,0,0};
  int passSeed2_3555All[6] = {0,0,0,0,0,0};
  int passSeed2_3560All[6] = {0,0,0,0,0,0};
  int passSeed2_3535All_count[6] = {0,0,0,0,0,0};
  int passSeed2_3540All_count[6] = {0,0,0,0,0,0};
  int passSeed2_3545All_count[6] = {0,0,0,0,0,0};
  int passSeed2_3550All_count[6] = {0,0,0,0,0,0};
  int passSeed2_3555All_count[6] = {0,0,0,0,0,0};
  int passSeed2_3560All_count[6] = {0,0,0,0,0,0};
  //jet 40
  int passSeed2_4035All[6] = {0,0,0,0,0,0};
  int passSeed2_4040All[6] = {0,0,0,0,0,0};
  int passSeed2_4045All[6] = {0,0,0,0,0,0};
  int passSeed2_4050All[6] = {0,0,0,0,0,0};
  int passSeed2_4055All[6] = {0,0,0,0,0,0};
  int passSeed2_4060All[6] = {0,0,0,0,0,0};
  int passSeed2_4035All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4040All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4045All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4050All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4055All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4060All_count[6] = {0,0,0,0,0,0};
  //jet 45
  int passSeed2_4535All[6] = {0,0,0,0,0,0};
  int passSeed2_4540All[6] = {0,0,0,0,0,0};
  int passSeed2_4545All[6] = {0,0,0,0,0,0};
  int passSeed2_4550All[6] = {0,0,0,0,0,0};
  int passSeed2_4555All[6] = {0,0,0,0,0,0};
  int passSeed2_4560All[6] = {0,0,0,0,0,0};
  int passSeed2_4535All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4540All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4545All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4550All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4555All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4560All_count[6] = {0,0,0,0,0,0};
  //jet 50
  int passSeed2_5035All[6] = {0,0,0,0,0,0};
  int passSeed2_5040All[6] = {0,0,0,0,0,0};
  int passSeed2_5045All[6] = {0,0,0,0,0,0};
  int passSeed2_5050All[6] = {0,0,0,0,0,0};
  int passSeed2_5055All[6] = {0,0,0,0,0,0};
  int passSeed2_5060All[6] = {0,0,0,0,0,0};
  int passSeed2_5035All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5040All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5045All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5050All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5055All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5060All_count[6] = {0,0,0,0,0,0};
  //jet 55
  int passSeed2_5535All[6] = {0,0,0,0,0,0};
  int passSeed2_5540All[6] = {0,0,0,0,0,0};
  int passSeed2_5545All[6] = {0,0,0,0,0,0};
  int passSeed2_5550All[6] = {0,0,0,0,0,0};
  int passSeed2_5555All[6] = {0,0,0,0,0,0};
  int passSeed2_5560All[6] = {0,0,0,0,0,0};
  int passSeed2_5535All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5540All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5545All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5550All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5555All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5560All_count[6] = {0,0,0,0,0,0};
  //jet 60
  int passSeed2_6035All[6] = {0,0,0,0,0,0};
  int passSeed2_6040All[6] = {0,0,0,0,0,0};
  int passSeed2_6045All[6] = {0,0,0,0,0,0};
  int passSeed2_6050All[6] = {0,0,0,0,0,0};
  int passSeed2_6055All[6] = {0,0,0,0,0,0};
  int passSeed2_6060All[6] = {0,0,0,0,0,0};
  int passSeed2_6035All_count[6] = {0,0,0,0,0,0};
  int passSeed2_6040All_count[6] = {0,0,0,0,0,0};
  int passSeed2_6045All_count[6] = {0,0,0,0,0,0};
  int passSeed2_6050All_count[6] = {0,0,0,0,0,0};
  int passSeed2_6055All_count[6] = {0,0,0,0,0,0};
  int passSeed2_6060All_count[6] = {0,0,0,0,0,0};
  //

  int olDiTauSeed1 = 0;
  int olDiTauSeed2 = 0;
  int olDiTauSeed3 = 0;
  int olOldSeed1 = 0;
  int olOldSeed2 = 0;
  int olOldSeed3 = 0;
  int olNewSeed1 = 0;
  int olNewSeed2 = 0;
  int olNewSeed3 = 0;
  int olDiTauOldSeed1 = 0;
  int olDiTauOldSeed2 = 0;
  int olDiTauOldSeed3 = 0;
  int olDiTauNewSeed1 = 0;
  int olDiTauNewSeed2 = 0;
  int olDiTauNewSeed3 = 0;
  int olOldNewSeed1 = 0;
  int olOldNewSeed2 = 0;
  int olOldNewSeed3 = 0;
  int olDiTauOld = 0;
  int olDiTauNew = 0;
  int olOldNew = 0;
  int olDiTauOldNew = 0;

  int orDiTauSeed1 = 0;
  int orDiTauSeed2 = 0;
  int orDiTauSeed3 = 0;
  int orOldSeed1 = 0;
  int orOldSeed2 = 0;
  int orOldSeed3 = 0;
  int orNewSeed1 = 0;
  int orNewSeed2 = 0;
  int orNewSeed3 = 0;
  int orDiTauOldSeed1 = 0;
  int orDiTauOldSeed2 = 0;
  int orDiTauOldSeed3 = 0;
  int orDiTauNewSeed1 = 0;
  int orDiTauNewSeed2 = 0;
  int orDiTauNewSeed3 = 0;
  int orOldNewSeed1 = 0;
  int orOldNewSeed2 = 0;
  int orOldNewSeed3 = 0;
  int orDiTauOld = 0;
  int orDiTauNew = 0;
  int orOldNew = 0;
  int orDiTauOldNew = 0;


  // start event loop
  for (Long64_t jentry=0; jentry<nentries1; ++jentry) { // full dataset
  //for (Long64_t jentry=0; jentry<200000; ++jentry) {
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
   
    for (int i = 0; i<6; ++i){
      passSeed2_3535All[i] = 0;
      passSeed2_3540All[i] = 0;
      passSeed2_3545All[i] = 0;
      passSeed2_3550All[i] = 0;
      passSeed2_3555All[i] = 0;
      passSeed2_3560All[i] = 0;

      passSeed2_4035All[i] = 0;
      passSeed2_4040All[i] = 0;
      passSeed2_4045All[i] = 0;
      passSeed2_4050All[i] = 0;
      passSeed2_4055All[i] = 0;
      passSeed2_4060All[i] = 0;

      passSeed2_4535All[i] = 0;
      passSeed2_4540All[i] = 0;
      passSeed2_4545All[i] = 0;
      passSeed2_4550All[i] = 0;
      passSeed2_4555All[i] = 0;
      passSeed2_4560All[i] = 0;

      passSeed2_5035All[i] = 0;
      passSeed2_5040All[i] = 0;
      passSeed2_5045All[i] = 0;
      passSeed2_5050All[i] = 0;
      passSeed2_5055All[i] = 0;
      passSeed2_5060All[i] = 0;

      passSeed2_5535All[i] = 0;
      passSeed2_5540All[i] = 0;
      passSeed2_5545All[i] = 0;
      passSeed2_5550All[i] = 0;
      passSeed2_5555All[i] = 0;
      passSeed2_5560All[i] = 0;

      passSeed2_6035All[i] = 0;
      passSeed2_6040All[i] = 0;
      passSeed2_6045All[i] = 0;
      passSeed2_6050All[i] = 0;
      passSeed2_6055All[i] = 0;
      passSeed2_6060All[i] = 0;

    }

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
    vector<TLorentzVector> jetCands50RmvOlTauCandsIso35;
    vector<TLorentzVector> jetCands55RmvOlTauCandsIso35;
    vector<TLorentzVector> jetCands60RmvOlTauCandsIso35;
    if (tauCandsIso35Size > 0 ) {
      if (jetCands35Size >= 2) jetCands35RmvOlTauCandsIso35 = crossCleanJets(jetCands35, tauCandsIso35);
      if (jetCands40Size >= 2) jetCands40RmvOlTauCandsIso35 = crossCleanJets(jetCands40, tauCandsIso35);
      if (jetCands45Size >= 2) jetCands45RmvOlTauCandsIso35 = crossCleanJets(jetCands45, tauCandsIso35);
      if (jetCands50Size >= 2) jetCands50RmvOlTauCandsIso35 = crossCleanJets(jetCands50, tauCandsIso35);
      if (jetCands55Size >= 2) jetCands55RmvOlTauCandsIso35 = crossCleanJets(jetCands55, tauCandsIso35);
      if (jetCands60Size >= 2) jetCands60RmvOlTauCandsIso35 = crossCleanJets(jetCands60, tauCandsIso35);
    }
    else {
      jetCands35RmvOlTauCandsIso35 = jetCands35;
      jetCands40RmvOlTauCandsIso35 = jetCands40;
      jetCands45RmvOlTauCandsIso35 = jetCands45;
      jetCands50RmvOlTauCandsIso35 = jetCands50;
      jetCands55RmvOlTauCandsIso35 = jetCands55;
      jetCands60RmvOlTauCandsIso35 = jetCands60;
    }
    int jetCands35RmvOlTauCandsIso35Size = jetCands35RmvOlTauCandsIso35.size();
    int jetCands40RmvOlTauCandsIso35Size = jetCands40RmvOlTauCandsIso35.size();
    int jetCands45RmvOlTauCandsIso35Size = jetCands45RmvOlTauCandsIso35.size();
    int jetCands50RmvOlTauCandsIso35Size = jetCands50RmvOlTauCandsIso35.size();
    int jetCands55RmvOlTauCandsIso35Size = jetCands55RmvOlTauCandsIso35.size();
    int jetCands60RmvOlTauCandsIso35Size = jetCands60RmvOlTauCandsIso35.size();

    // isoTau40
    vector<TLorentzVector> jetCands35RmvOlTauCandsIso40;
    vector<TLorentzVector> jetCands40RmvOlTauCandsIso40;
    vector<TLorentzVector> jetCands45RmvOlTauCandsIso40;
    vector<TLorentzVector> jetCands50RmvOlTauCandsIso40;
    vector<TLorentzVector> jetCands55RmvOlTauCandsIso40;
    vector<TLorentzVector> jetCands60RmvOlTauCandsIso40;
    if (tauCandsIso40Size > 0) {
      if (jetCands35Size >= 2) jetCands35RmvOlTauCandsIso40 = crossCleanJets(jetCands35, tauCandsIso40);
      if (jetCands40Size >= 2) jetCands40RmvOlTauCandsIso40 = crossCleanJets(jetCands40, tauCandsIso40);
      if (jetCands45Size >= 2) jetCands45RmvOlTauCandsIso40 = crossCleanJets(jetCands45, tauCandsIso40);
      if (jetCands50Size >= 2) jetCands50RmvOlTauCandsIso40 = crossCleanJets(jetCands50, tauCandsIso40);
      if (jetCands55Size >= 2) jetCands55RmvOlTauCandsIso40 = crossCleanJets(jetCands55, tauCandsIso40);
      if (jetCands60Size >= 2) jetCands60RmvOlTauCandsIso40 = crossCleanJets(jetCands60, tauCandsIso40);
    }
    else {
      jetCands35RmvOlTauCandsIso40 = jetCands35;
      jetCands40RmvOlTauCandsIso40 = jetCands40;
      jetCands45RmvOlTauCandsIso40 = jetCands45;
      jetCands50RmvOlTauCandsIso40 = jetCands50;
      jetCands55RmvOlTauCandsIso40 = jetCands55;
      jetCands60RmvOlTauCandsIso40 = jetCands60;
    }
    int jetCands35RmvOlTauCandsIso40Size = jetCands35RmvOlTauCandsIso40.size();
    int jetCands40RmvOlTauCandsIso40Size = jetCands40RmvOlTauCandsIso40.size();
    int jetCands45RmvOlTauCandsIso40Size = jetCands45RmvOlTauCandsIso40.size();
    int jetCands50RmvOlTauCandsIso40Size = jetCands50RmvOlTauCandsIso40.size();
    int jetCands55RmvOlTauCandsIso40Size = jetCands55RmvOlTauCandsIso40.size();
    int jetCands60RmvOlTauCandsIso40Size = jetCands60RmvOlTauCandsIso40.size();

    // isoTau45
    vector<TLorentzVector> jetCands35RmvOlTauCandsIso45;
    vector<TLorentzVector> jetCands40RmvOlTauCandsIso45;
    vector<TLorentzVector> jetCands45RmvOlTauCandsIso45;
    vector<TLorentzVector> jetCands50RmvOlTauCandsIso45;
    vector<TLorentzVector> jetCands55RmvOlTauCandsIso45;
    vector<TLorentzVector> jetCands60RmvOlTauCandsIso45;
    if (tauCandsIso45Size > 0) {
      if (jetCands35Size >= 2) jetCands35RmvOlTauCandsIso45 = crossCleanJets(jetCands35, tauCandsIso45);
      if (jetCands40Size >= 2) jetCands40RmvOlTauCandsIso45 = crossCleanJets(jetCands40, tauCandsIso45);
      if (jetCands45Size >= 2) jetCands45RmvOlTauCandsIso45 = crossCleanJets(jetCands45, tauCandsIso45);
      if (jetCands50Size >= 2) jetCands50RmvOlTauCandsIso45 = crossCleanJets(jetCands50, tauCandsIso45);
      if (jetCands55Size >= 2) jetCands55RmvOlTauCandsIso45 = crossCleanJets(jetCands55, tauCandsIso45);
      if (jetCands60Size >= 2) jetCands60RmvOlTauCandsIso45 = crossCleanJets(jetCands60, tauCandsIso45);
    }
    else {
      jetCands35RmvOlTauCandsIso45 = jetCands35;
      jetCands40RmvOlTauCandsIso45 = jetCands40;
      jetCands45RmvOlTauCandsIso45 = jetCands45;
      jetCands50RmvOlTauCandsIso45 = jetCands50;
      jetCands55RmvOlTauCandsIso45 = jetCands55;
      jetCands60RmvOlTauCandsIso45 = jetCands60;
    }
    int jetCands35RmvOlTauCandsIso45Size = jetCands35RmvOlTauCandsIso45.size();
    int jetCands40RmvOlTauCandsIso45Size = jetCands40RmvOlTauCandsIso45.size();
    int jetCands45RmvOlTauCandsIso45Size = jetCands45RmvOlTauCandsIso45.size();
    int jetCands50RmvOlTauCandsIso45Size = jetCands50RmvOlTauCandsIso45.size();
    int jetCands55RmvOlTauCandsIso45Size = jetCands55RmvOlTauCandsIso45.size();
    int jetCands60RmvOlTauCandsIso45Size = jetCands60RmvOlTauCandsIso45.size();

    // isoTau50
    vector<TLorentzVector> jetCands35RmvOlTauCandsIso50;
    vector<TLorentzVector> jetCands40RmvOlTauCandsIso50;
    vector<TLorentzVector> jetCands45RmvOlTauCandsIso50; 
    vector<TLorentzVector> jetCands50RmvOlTauCandsIso50; 
    vector<TLorentzVector> jetCands55RmvOlTauCandsIso50; 
    vector<TLorentzVector> jetCands60RmvOlTauCandsIso50; 
    if (tauCandsIso50Size > 0) {
      if (jetCands35Size >= 2) jetCands35RmvOlTauCandsIso50 = crossCleanJets(jetCands35, tauCandsIso50);
      if (jetCands40Size >= 2) jetCands40RmvOlTauCandsIso50 = crossCleanJets(jetCands40, tauCandsIso50);
      if (jetCands45Size >= 2) jetCands45RmvOlTauCandsIso50 = crossCleanJets(jetCands45, tauCandsIso50);
      if (jetCands50Size >= 2) jetCands50RmvOlTauCandsIso50 = crossCleanJets(jetCands50, tauCandsIso50);
      if (jetCands55Size >= 2) jetCands55RmvOlTauCandsIso50 = crossCleanJets(jetCands55, tauCandsIso50);
      if (jetCands60Size >= 2) jetCands60RmvOlTauCandsIso50 = crossCleanJets(jetCands60, tauCandsIso50);
    }
    else {
      jetCands35RmvOlTauCandsIso50 = jetCands35;
      jetCands40RmvOlTauCandsIso50 = jetCands40;
      jetCands45RmvOlTauCandsIso50 = jetCands45;
      jetCands50RmvOlTauCandsIso50 = jetCands50;
      jetCands55RmvOlTauCandsIso50 = jetCands55;
      jetCands60RmvOlTauCandsIso50 = jetCands60;
    }
    int jetCands35RmvOlTauCandsIso50Size = jetCands35RmvOlTauCandsIso50.size();
    int jetCands40RmvOlTauCandsIso50Size = jetCands40RmvOlTauCandsIso50.size();
    int jetCands45RmvOlTauCandsIso50Size = jetCands45RmvOlTauCandsIso50.size();
    int jetCands50RmvOlTauCandsIso50Size = jetCands50RmvOlTauCandsIso50.size();
    int jetCands55RmvOlTauCandsIso50Size = jetCands55RmvOlTauCandsIso50.size();
    int jetCands60RmvOlTauCandsIso50Size = jetCands60RmvOlTauCandsIso50.size();

    // isoTau55
    vector<TLorentzVector> jetCands35RmvOlTauCandsIso55;
    vector<TLorentzVector> jetCands40RmvOlTauCandsIso55;
    vector<TLorentzVector> jetCands45RmvOlTauCandsIso55; 
    vector<TLorentzVector> jetCands50RmvOlTauCandsIso55; 
    vector<TLorentzVector> jetCands55RmvOlTauCandsIso55; 
    vector<TLorentzVector> jetCands60RmvOlTauCandsIso55; 
    if (tauCandsIso55Size > 0) {
      if (jetCands35Size >= 2) jetCands35RmvOlTauCandsIso55 = crossCleanJets(jetCands35, tauCandsIso55);
      if (jetCands40Size >= 2) jetCands40RmvOlTauCandsIso55 = crossCleanJets(jetCands40, tauCandsIso55);
      if (jetCands45Size >= 2) jetCands45RmvOlTauCandsIso55 = crossCleanJets(jetCands45, tauCandsIso55);
      if (jetCands50Size >= 2) jetCands50RmvOlTauCandsIso55 = crossCleanJets(jetCands50, tauCandsIso55);
      if (jetCands55Size >= 2) jetCands55RmvOlTauCandsIso55 = crossCleanJets(jetCands55, tauCandsIso55);
      if (jetCands60Size >= 2) jetCands60RmvOlTauCandsIso55 = crossCleanJets(jetCands60, tauCandsIso55);
    }
    else {
      jetCands35RmvOlTauCandsIso55 = jetCands35;
      jetCands40RmvOlTauCandsIso55 = jetCands40;
      jetCands45RmvOlTauCandsIso55 = jetCands45;
      jetCands50RmvOlTauCandsIso55 = jetCands50;
      jetCands55RmvOlTauCandsIso55 = jetCands55;
      jetCands60RmvOlTauCandsIso55 = jetCands60;
    }
    int jetCands35RmvOlTauCandsIso55Size = jetCands35RmvOlTauCandsIso55.size();
    int jetCands40RmvOlTauCandsIso55Size = jetCands40RmvOlTauCandsIso55.size();
    int jetCands45RmvOlTauCandsIso55Size = jetCands45RmvOlTauCandsIso55.size();
    int jetCands50RmvOlTauCandsIso55Size = jetCands50RmvOlTauCandsIso55.size();
    int jetCands55RmvOlTauCandsIso55Size = jetCands55RmvOlTauCandsIso55.size();
    int jetCands60RmvOlTauCandsIso55Size = jetCands60RmvOlTauCandsIso55.size();

    // isoTau60
    vector<TLorentzVector> jetCands35RmvOlTauCandsIso60;
    vector<TLorentzVector> jetCands40RmvOlTauCandsIso60;
    vector<TLorentzVector> jetCands45RmvOlTauCandsIso60; 
    vector<TLorentzVector> jetCands50RmvOlTauCandsIso60; 
    vector<TLorentzVector> jetCands55RmvOlTauCandsIso60; 
    vector<TLorentzVector> jetCands60RmvOlTauCandsIso60; 
    if (tauCandsIso60Size > 0) {
      if (jetCands35Size >= 2) jetCands35RmvOlTauCandsIso60 = crossCleanJets(jetCands35, tauCandsIso60);
      if (jetCands40Size >= 2) jetCands40RmvOlTauCandsIso60 = crossCleanJets(jetCands40, tauCandsIso60);
      if (jetCands45Size >= 2) jetCands45RmvOlTauCandsIso60 = crossCleanJets(jetCands45, tauCandsIso60);
      if (jetCands50Size >= 2) jetCands50RmvOlTauCandsIso60 = crossCleanJets(jetCands50, tauCandsIso60);
      if (jetCands55Size >= 2) jetCands55RmvOlTauCandsIso60 = crossCleanJets(jetCands55, tauCandsIso60);
      if (jetCands60Size >= 2) jetCands60RmvOlTauCandsIso60 = crossCleanJets(jetCands60, tauCandsIso60);
    }
    else {
      jetCands35RmvOlTauCandsIso60 = jetCands35;
      jetCands40RmvOlTauCandsIso60 = jetCands40;
      jetCands45RmvOlTauCandsIso60 = jetCands45;
      jetCands50RmvOlTauCandsIso60 = jetCands50;
      jetCands55RmvOlTauCandsIso60 = jetCands55;
      jetCands60RmvOlTauCandsIso60 = jetCands60;
    }
    int jetCands35RmvOlTauCandsIso60Size = jetCands35RmvOlTauCandsIso60.size();
    int jetCands40RmvOlTauCandsIso60Size = jetCands40RmvOlTauCandsIso60.size();
    int jetCands45RmvOlTauCandsIso60Size = jetCands45RmvOlTauCandsIso60.size();
    int jetCands50RmvOlTauCandsIso60Size = jetCands50RmvOlTauCandsIso60.size();
    int jetCands55RmvOlTauCandsIso60Size = jetCands55RmvOlTauCandsIso60.size();
    int jetCands60RmvOlTauCandsIso60Size = jetCands60RmvOlTauCandsIso60.size();

    // end containers for seed 2 variations

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
      float mjotjot_seed1 = highestMassOfPair(jetCands35RmvOlTauCandsIso40, tauCandsIso40);
      if (mjotjot_seed1 >= 400) passSeed1 = 1;
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

  //------------------------------seed 2 varying cuts-----------------------//
  //
  if (tauCandsIso35Size >= 1) {
    if (jetCands35RmvOlTauCandsIso35Size >= 2) setArrayElements(passSeed2_3535All, highestMassOfPair(jetCands35RmvOlTauCandsIso35, tauCandsIso35), mjjCuts);

    if (jetCands40RmvOlTauCandsIso35Size >= 2) setArrayElements(passSeed2_4035All, highestMassOfPair(jetCands40RmvOlTauCandsIso35, tauCandsIso35), mjjCuts);

    if (jetCands45RmvOlTauCandsIso35Size >= 2) setArrayElements(passSeed2_4535All, highestMassOfPair(jetCands45RmvOlTauCandsIso35, tauCandsIso35), mjjCuts);

    if (jetCands50RmvOlTauCandsIso35Size >= 2) setArrayElements(passSeed2_5035All, highestMassOfPair(jetCands50RmvOlTauCandsIso35, tauCandsIso35), mjjCuts);

    if (jetCands55RmvOlTauCandsIso35Size >= 2) setArrayElements(passSeed2_5535All, highestMassOfPair(jetCands55RmvOlTauCandsIso35, tauCandsIso35), mjjCuts);

    if (jetCands60RmvOlTauCandsIso35Size >= 2) setArrayElements(passSeed2_6035All, highestMassOfPair(jetCands60RmvOlTauCandsIso35, tauCandsIso35), mjjCuts);
  }

  if (tauCandsIso40Size >= 1) {
    if (jetCands35RmvOlTauCandsIso40Size >= 2) setArrayElements(passSeed2_3540All, highestMassOfPair(jetCands35RmvOlTauCandsIso40, tauCandsIso40), mjjCuts);

    if (jetCands40RmvOlTauCandsIso40Size >= 2) setArrayElements(passSeed2_4040All, highestMassOfPair(jetCands40RmvOlTauCandsIso40, tauCandsIso40), mjjCuts);

    if (jetCands45RmvOlTauCandsIso40Size >= 2) setArrayElements(passSeed2_4540All, highestMassOfPair(jetCands45RmvOlTauCandsIso40, tauCandsIso40), mjjCuts);

    if (jetCands50RmvOlTauCandsIso40Size >= 2) setArrayElements(passSeed2_5040All, highestMassOfPair(jetCands50RmvOlTauCandsIso40, tauCandsIso40), mjjCuts);

    if (jetCands55RmvOlTauCandsIso40Size >= 2) setArrayElements(passSeed2_5540All, highestMassOfPair(jetCands55RmvOlTauCandsIso40, tauCandsIso40), mjjCuts);

    if (jetCands60RmvOlTauCandsIso40Size >= 2) setArrayElements(passSeed2_6040All, highestMassOfPair(jetCands60RmvOlTauCandsIso40, tauCandsIso40), mjjCuts);
  }

  if (tauCandsIso45Size >= 1) {
    // original seed 2 at 400 cut
    if (jetCands35RmvOlTauCandsIso45Size >= 2) setArrayElements(passSeed2_3545All, highestMassOfPair(jetCands35RmvOlTauCandsIso45, tauCandsIso45), mjjCuts);

    if (jetCands40RmvOlTauCandsIso45Size >= 2) setArrayElements(passSeed2_4045All, highestMassOfPair(jetCands40RmvOlTauCandsIso45, tauCandsIso45), mjjCuts);

    if (jetCands45RmvOlTauCandsIso45Size >= 2) setArrayElements(passSeed2_4545All, highestMassOfPair(jetCands45RmvOlTauCandsIso45, tauCandsIso45), mjjCuts);

    if (jetCands50RmvOlTauCandsIso45Size >= 2) setArrayElements(passSeed2_5045All, highestMassOfPair(jetCands50RmvOlTauCandsIso45, tauCandsIso45), mjjCuts);

    if (jetCands55RmvOlTauCandsIso45Size >= 2) setArrayElements(passSeed2_5545All, highestMassOfPair(jetCands55RmvOlTauCandsIso45, tauCandsIso45), mjjCuts);

    if (jetCands60RmvOlTauCandsIso45Size >= 2) setArrayElements(passSeed2_6045All, highestMassOfPair(jetCands60RmvOlTauCandsIso45, tauCandsIso45), mjjCuts);
  }

  if (tauCandsIso50Size >= 1) {
    // original seed 2 at 400 cut
    if (jetCands35RmvOlTauCandsIso50Size >= 2) setArrayElements(passSeed2_3550All, highestMassOfPair(jetCands35RmvOlTauCandsIso50, tauCandsIso50), mjjCuts);

    if (jetCands40RmvOlTauCandsIso50Size >= 2) setArrayElements(passSeed2_4050All, highestMassOfPair(jetCands40RmvOlTauCandsIso50, tauCandsIso50), mjjCuts);

    if (jetCands45RmvOlTauCandsIso50Size >= 2) setArrayElements(passSeed2_4550All, highestMassOfPair(jetCands45RmvOlTauCandsIso50, tauCandsIso50), mjjCuts);

    if (jetCands50RmvOlTauCandsIso50Size >= 2) setArrayElements(passSeed2_5050All, highestMassOfPair(jetCands50RmvOlTauCandsIso50, tauCandsIso50), mjjCuts);

    if (jetCands55RmvOlTauCandsIso50Size >= 2) setArrayElements(passSeed2_5550All, highestMassOfPair(jetCands55RmvOlTauCandsIso50, tauCandsIso50), mjjCuts);

    if (jetCands60RmvOlTauCandsIso50Size >= 2) setArrayElements(passSeed2_6050All, highestMassOfPair(jetCands60RmvOlTauCandsIso50, tauCandsIso50), mjjCuts);
  }

  if (tauCandsIso55Size >= 1) {
    // original seed 2 at 400 cut
    if (jetCands35RmvOlTauCandsIso55Size >= 2) setArrayElements(passSeed2_3555All, highestMassOfPair(jetCands35RmvOlTauCandsIso55, tauCandsIso55), mjjCuts);

    if (jetCands40RmvOlTauCandsIso55Size >= 2) setArrayElements(passSeed2_4055All, highestMassOfPair(jetCands40RmvOlTauCandsIso55, tauCandsIso55), mjjCuts);

    if (jetCands45RmvOlTauCandsIso55Size >= 2) setArrayElements(passSeed2_4555All, highestMassOfPair(jetCands45RmvOlTauCandsIso55, tauCandsIso55), mjjCuts);

    if (jetCands50RmvOlTauCandsIso55Size >= 2) setArrayElements(passSeed2_5055All, highestMassOfPair(jetCands50RmvOlTauCandsIso55, tauCandsIso55), mjjCuts);

    if (jetCands55RmvOlTauCandsIso55Size >= 2) setArrayElements(passSeed2_5555All, highestMassOfPair(jetCands55RmvOlTauCandsIso55, tauCandsIso55), mjjCuts);

    if (jetCands60RmvOlTauCandsIso55Size >= 2) setArrayElements(passSeed2_6055All, highestMassOfPair(jetCands60RmvOlTauCandsIso55, tauCandsIso55), mjjCuts);
  }

  if (tauCandsIso60Size >= 1) {
    // original seed 2 at 400 cut
    if (jetCands35RmvOlTauCandsIso60Size >= 2) setArrayElements(passSeed2_3560All, highestMassOfPair(jetCands35RmvOlTauCandsIso60, tauCandsIso60), mjjCuts);

    if (jetCands40RmvOlTauCandsIso60Size >= 2) setArrayElements(passSeed2_4060All, highestMassOfPair(jetCands40RmvOlTauCandsIso60, tauCandsIso60), mjjCuts);

    if (jetCands45RmvOlTauCandsIso60Size >= 2) setArrayElements(passSeed2_4560All, highestMassOfPair(jetCands45RmvOlTauCandsIso60, tauCandsIso60), mjjCuts);

    if (jetCands50RmvOlTauCandsIso60Size >= 2) setArrayElements(passSeed2_5060All, highestMassOfPair(jetCands50RmvOlTauCandsIso60, tauCandsIso60), mjjCuts);

    if (jetCands55RmvOlTauCandsIso60Size >= 2) setArrayElements(passSeed2_5560All, highestMassOfPair(jetCands55RmvOlTauCandsIso60, tauCandsIso60), mjjCuts);

    if (jetCands60RmvOlTauCandsIso60Size >= 2) setArrayElements(passSeed2_6060All, highestMassOfPair(jetCands60RmvOlTauCandsIso60, tauCandsIso60), mjjCuts);
  }

  passDiTauCount += passDiTau;
  passOldCount += passOld;
  passNewCount += passNew;
  passSeed1Count += passSeed1;
  passSeed2Count += passSeed2_3545All[1];
  passSeed3Count += passSeed3;

  // variations of seed 2
  for (int i = 0; i<6; ++i) {
    passSeed2_3535All_count[i] += passSeed2_3535All[i];
    passSeed2_3540All_count[i] += passSeed2_3540All[i];
    passSeed2_3545All_count[i] += passSeed2_3545All[i];
    passSeed2_3550All_count[i] += passSeed2_3550All[i];
    passSeed2_3555All_count[i] += passSeed2_3555All[i];
    passSeed2_3560All_count[i] += passSeed2_3560All[i];

    passSeed2_4035All_count[i] += passSeed2_4035All[i];
    passSeed2_4040All_count[i] += passSeed2_4040All[i];
    passSeed2_4045All_count[i] += passSeed2_4045All[i];
    passSeed2_4050All_count[i] += passSeed2_4050All[i];
    passSeed2_4055All_count[i] += passSeed2_4055All[i];
    passSeed2_4060All_count[i] += passSeed2_4060All[i];

    passSeed2_4535All_count[i] += passSeed2_4535All[i];
    passSeed2_4540All_count[i] += passSeed2_4540All[i];
    passSeed2_4545All_count[i] += passSeed2_4545All[i];
    passSeed2_4550All_count[i] += passSeed2_4550All[i];
    passSeed2_4555All_count[i] += passSeed2_4555All[i];
    passSeed2_4560All_count[i] += passSeed2_4560All[i];

    passSeed2_5035All_count[i] += passSeed2_5035All[i];
    passSeed2_5040All_count[i] += passSeed2_5040All[i];
    passSeed2_5045All_count[i] += passSeed2_5045All[i];
    passSeed2_5050All_count[i] += passSeed2_5050All[i];
    passSeed2_5055All_count[i] += passSeed2_5055All[i];
    passSeed2_5060All_count[i] += passSeed2_5060All[i];

    passSeed2_5535All_count[i] += passSeed2_5535All[i];
    passSeed2_5540All_count[i] += passSeed2_5540All[i];
    passSeed2_5545All_count[i] += passSeed2_5545All[i];
    passSeed2_5550All_count[i] += passSeed2_5550All[i];
    passSeed2_5555All_count[i] += passSeed2_5555All[i];
    passSeed2_5560All_count[i] += passSeed2_5560All[i];

    passSeed2_6035All_count[i] += passSeed2_6035All[i];
    passSeed2_6040All_count[i] += passSeed2_6040All[i];
    passSeed2_6045All_count[i] += passSeed2_6045All[i];
    passSeed2_6050All_count[i] += passSeed2_6050All[i];
    passSeed2_6055All_count[i] += passSeed2_6055All[i];
    passSeed2_6060All_count[i] += passSeed2_6060All[i];

  }

  // end variations

  olDiTauSeed1 += (passDiTau && passSeed1);
  olDiTauSeed2 += (passDiTau && passSeed2_3545All[1]);
  olDiTauSeed3 += (passDiTau && passSeed3);

  olOldSeed1 += (passOld && passSeed1);
  olOldSeed2 += (passOld && passSeed2_3545All[1]);
  olOldSeed3 += (passOld && passSeed3);

  olNewSeed1 += (passNew && passSeed1);
  olNewSeed2 += (passNew && passSeed2_3545All[1]);
  olNewSeed3 += (passNew && passSeed3);

  olDiTauOld += (passOld && passDiTau);
  olDiTauNew += (passOld && passDiTau);
  olOldNew += (passOld && passNew);

  olDiTauOldSeed1 += (passDiTau && passOld && passSeed1);
  olDiTauOldSeed2 += (passDiTau && passOld && passSeed2_3545All[1]);
  olDiTauOldSeed3 += (passDiTau && passOld && passSeed3);

  olDiTauNewSeed1 += (passDiTau && passNew && passSeed1);
  olDiTauNewSeed2 += (passDiTau && passNew && passSeed2_3545All[1]);
  olDiTauNewSeed3 += (passDiTau && passNew && passSeed3);

  olOldNewSeed1 += (passOld && passNew && passSeed1);
  olOldNewSeed2 += (passOld && passNew && passSeed2_3545All[1]);
  olOldNewSeed3 += (passOld && passNew && passSeed3);

  olDiTauOldNew += (passDiTau && passOld && passNew);

  orDiTauSeed1 += (passDiTau || passSeed1);
  orDiTauSeed2 += (passDiTau || passSeed2_3545All[1]);
  orDiTauSeed3 += (passDiTau || passSeed3);

  orOldSeed1 += (passOld || passSeed1);
  orOldSeed2 += (passOld || passSeed2_3545All[1]);
  orOldSeed3 += (passOld || passSeed3);

  orNewSeed1 += (passNew || passSeed1);
  orNewSeed2 += (passNew || passSeed2_3545All[1]);
  orNewSeed3 += (passNew || passSeed3);

  orDiTauOld += (passDiTau || passOld);
  orDiTauNew += (passDiTau || passNew);
  orOldNew += (passOld || passNew);

  orDiTauOldSeed1 += (passDiTau || passOld || passSeed1);
  orDiTauOldSeed2 += (passDiTau || passOld || passSeed2_3545All[1]);
  orDiTauOldSeed3 += (passDiTau || passOld || passSeed3);

  orDiTauNewSeed1 += (passDiTau || passNew || passSeed1);
  orDiTauNewSeed2 += (passDiTau || passNew || passSeed2_3545All[1]);
  orDiTauNewSeed3 += (passDiTau || passNew || passSeed3);

  orOldNewSeed1 += (passOld || passNew || passSeed1);
  orOldNewSeed2 += (passOld || passNew || passSeed2_3545All[1]);
  orOldNewSeed3 += (passOld || passNew || passSeed3);

  orDiTauOldNew += (passDiTau || passOld || passNew);

  } // end event loop

  //float lumiSum = 0;
  //float firstLumi = 0;
  //------------------------------------print results to terminal-----------------------------------//
  //for (auto it = lumis.begin(); it != lumis.end(); ++it) {
  //  cout << it->first << " run " << it->second << " LS " << endl;
  //  lumiSum += it->second;
  //  if (it == lumis.begin()) firstLumi = it->second;
  //}
  cout << eventCount << " Events Scanned" << endl;
  cout << runCount << " Events in Selected Run (323755)" << endl;
  cout << lumis.size() << " Lumi Sections in Run" << endl;
  //cout << firstLumi << '\t' << "firstLumi" << '\t' << lumiSum << '\t' << "lumiSum" << endl;
  cout << "from OMS, lumi at LS = 44 is 1.849E34 and drops by 4\% after 100 LS (at 143 it is 1.775E34)" << endl;
  cout << "this makes the avg lumi = 1.812E34, which is what is used as the denom. lumi in the scaling" << endl;
  float Kfactor = 17881 * 40 * (2.0 / 1.812) / (lumis.size() * 23.31 * 8); // units of Hz
  float Ofactor = 2544 * 11255.6 * (2.0 / 1.812) * (1 / float(runCount)); // inst init lumi from report on OMS, used 44 LS lumi from list of init lumis per LS

  cout << "# Pass" << '\t' << "Eqn 1" << '\t' << "Eqn 2 " << endl;
 
  cout << passDiTauCount << '\t' << passDiTauCount*Kfactor << '\t' << passDiTauCount*Ofactor << '\t' << "DiTau (L1_DoubleIsoTau32er2p1)" << endl;
  cout << passOldCount << '\t' << passOldCount*Kfactor <<     '\t' << passOldCount*Ofactor << '\t' << "old VBF (L1_Jet110_Jet35_Mass_Min620)" << endl;
  cout << passNewCount << '\t' << passNewCount*Kfactor <<     '\t' << passNewCount*Ofactor << '\t' << "new VBF (L1_DoubleJet35_IsoTau45_Mjj450_RmvOl)" << endl;

  cout << passSeed1Count << '\t' << passSeed1Count*Kfactor << '\t' << passSeed1Count*Ofactor << '\t' << "seed 1 (L1_DoubleJet35_DoubleIsoTau40_MassAnyTwo400_RmvOl)" << endl;
  cout << passSeed2Count << '\t' << passSeed2Count*Kfactor << '\t' << passSeed2Count*Ofactor << '\t' << "seed 2 (L1_DoubleJet35_IsoTau45_MassAnyTwo400_RmvOl)" << endl;
  cout << passSeed3Count << '\t' << passSeed3Count*Kfactor << '\t' << passSeed3Count*Ofactor << '\t' << "seed 3 (L1_Jet35_Tau35_IsoTau45_MassJetTau450_RmvOl)" << endl; 

  cout << "1" << '\t' <<  "2" << '\t' << "3" << "seed: overlap w trig" << endl;
  cout << olDiTauSeed1 << '\t' << olDiTauSeed2 << '\t' << olDiTauSeed3 << '\t' << "DiTau AND" << endl;
  cout << olOldSeed1 << '\t' << olOldSeed2 << '\t' << olOldSeed3 << '\t' << "Old AND" << endl;
  cout << olNewSeed1 << '\t' << olNewSeed2 << '\t' << olNewSeed3 << '\t' << "New AND" << endl;

  cout << "1" << '\t' <<  "2" << '\t' << "3" << "seed: OR w trig" << endl;
  cout << orDiTauSeed1 << '\t' << orDiTauSeed2 << '\t' << orDiTauSeed3 << '\t' << "DiTau OR" << endl;
  cout << orOldSeed1 << '\t' << orOldSeed2 << '\t' << orOldSeed3 << '\t' << "Old OR" << endl;
  cout << orNewSeed1 << '\t' << orNewSeed2 << '\t' << orNewSeed3 << '\t' << "New OR" << endl;

  cout << "1" << '\t' << "2" << '\t' << "3" << '\t' << "three trig Overlap" << endl;
  cout << olDiTauOldSeed1 << '\t' << olDiTauOldSeed2 << '\t' << olDiTauNewSeed2 << '\t' << "DiTau AND Old AND" << endl;
  cout << olDiTauNewSeed1 << '\t' << olDiTauNewSeed2 << '\t' << olDiTauNewSeed2 << '\t' << "DiTau AND New AND" << endl;
  cout << olOldNewSeed1 << '\t' << olOldNewSeed2 << '\t' << olOldNewSeed2 << '\t' << "Old AND New AND" << endl;

  cout << "1" << '\t' << "2" << '\t' << "3" << '\t' << "three trig OR" << endl;
  cout << orDiTauOldSeed1 << '\t' << orDiTauOldSeed2 << '\t' << orDiTauNewSeed2 << '\t' << "DiTau OR Old OR" << endl;
  cout << orDiTauNewSeed1 << '\t' << orDiTauNewSeed2 << '\t' << orDiTauNewSeed2 << '\t' << "DiTau OR New OR" << endl;
  cout << orOldNewSeed1 << '\t' << orOldNewSeed2 << '\t' << orOldNewSeed2 << '\t' << "Old OR New OR" << endl;

  cout << "special interest ANDs/ORs" << endl;
  cout << olDiTauOld << '\t' << "DiTau AND Old" << endl;
  cout << olDiTauNew << '\t' << "DiTau AND New" << endl;
  cout << olOldNew << '\t' << "Old AND New" << endl;

  cout << orDiTauOld << '\t' << "DiTau OR Old" << endl;
  cout << orDiTauNew << '\t' << "DiTau OR New" << endl;
  cout << orOldNew << '\t' << "Old OR New" << endl;

  cout << olDiTauOldNew << '\t' << "DiTau AND Old AND New" << endl;
  cout << orDiTauOldNew << '\t' << "DiTau OR Old OR New" << endl;


  cout << "Varying params for Seed 2" << endl;
  cout << "xxxx number is jet pt then tau pt (using Et as Pt currently)" << endl;
  cout << "3535" << '\t' << "3540" << '\t' << "3545" << '\t' << "3550" << '\t' << "3555" << '\t' << "3560" << endl;
  for (int i = 0; i<6; ++i) {
    cout << passSeed2_3535All_count[i] << '\t' << passSeed2_3540All_count[i] << '\t' \
    << passSeed2_3545All_count[i] << '\t' << passSeed2_3550All_count[i] << '\t' \
    << passSeed2_3555All_count[i] << '\t' << passSeed2_3560All_count[i] << '\t' << "mjj cut " << mjjCuts[i] << endl;
  }

  cout << "4035" << '\t' << "4040" << '\t' << "4045" << '\t' << "4050" << '\t' << "4055" << '\t' << "4060" << endl;
  for (int i = 0; i<6; ++i) {
    cout << passSeed2_4035All_count[i] << '\t' << passSeed2_4040All_count[i] << '\t' \
    << passSeed2_4045All_count[i] << '\t' << passSeed2_4050All_count[i] << '\t' \
    << passSeed2_4055All_count[i] << '\t' << passSeed2_4060All_count[i] << '\t' << "mjj cut " << mjjCuts[i] << endl;
  }

  cout << "4535" << '\t' << "4540" << '\t' << "4545" << '\t' << "4550" << '\t' << "4555" << '\t' << "4560" << endl;
  for (int i = 0; i<6; ++i) {
    cout << passSeed2_4535All_count[i] << '\t' << passSeed2_4540All_count[i] << '\t' \
    << passSeed2_4545All_count[i] << '\t' << passSeed2_4550All_count[i] << '\t' \
    << passSeed2_4555All_count[i] << '\t' << passSeed2_4560All_count[i] << '\t' << "mjj cut " << mjjCuts[i] << endl;
  }

  cout << "5035" << '\t' << "5040" << '\t' << "5045" << '\t' << "5050" << '\t' << "5055" << '\t' << "5060" << endl;
  for (int i = 0; i<6; ++i) {
    cout << passSeed2_5035All_count[i] << '\t' << passSeed2_5040All_count[i] << '\t' \
    << passSeed2_5045All_count[i] << '\t' << passSeed2_5050All_count[i] << '\t' \
    << passSeed2_5055All_count[i] << '\t' << passSeed2_5060All_count[i] << '\t' << "mjj cut " << mjjCuts[i] << endl;
  }

  cout << "5535" << '\t' << "5540" << '\t' << "5545" << '\t' << "5550" << '\t' << "5555" << '\t' << "5560" << endl;
  for (int i = 0; i<6; ++i) {
    cout << passSeed2_5535All_count[i] << '\t' << passSeed2_5540All_count[i] << '\t' \
    << passSeed2_5545All_count[i] << '\t' << passSeed2_5550All_count[i] << '\t' \
    << passSeed2_5555All_count[i] << '\t' << passSeed2_5560All_count[i] << '\t' << "mjj cut " << mjjCuts[i] << endl;
  }

  cout << "6035" << '\t' << "6040" << '\t' << "6045" << '\t' << "6050" << '\t' << "6055" << '\t' << "6060" << endl;
  for (int i = 0; i<6; ++i) {
    cout << passSeed2_6035All_count[i] << '\t' << passSeed2_6040All_count[i] << '\t' \
    << passSeed2_6045All_count[i] << '\t' << passSeed2_6050All_count[i] << '\t' \
    << passSeed2_6055All_count[i] << '\t' << passSeed2_6060All_count[i] << '\t' << "mjj cut " << mjjCuts[i] << endl;
  }

}
