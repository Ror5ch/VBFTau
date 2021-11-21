#define analyzer_cxx
#include <stdio.h>
#include "analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <vector>
#include <array>

float highestMassOfPair(vector<TLorentzVector> jetsRmvOlTaus, vector<TLorentzVector> taus) {
  float mjotjot_ = 0; float tempMjotjot_ = 0;
  int jetSize = jetsRmvOlTaus.size();
  vector<TLorentzVector> combined;
  combined.insert(combined.begin(), jetsRmvOlTaus.begin(), jetsRmvOlTaus.end()); // jetsRmvOlTaus.begin() + 2);//
  combined.insert(combined.end(), taus.begin(), taus.end()); // taus.begin() + 2);
  int combinedSize = combined.size();
  for (int iObj = 0; iObj < combinedSize; ++iObj) {
    for (int jObj = 0; jObj < combinedSize; ++jObj) {
      if (jObj >= iObj) continue;
      //if (iObj >= jetSize && jObj >= jetSize ) continue; // should exclude 2tau case
      tempMjotjot_ = (combined.at(iObj) + combined.at(jObj)).M();
      if (tempMjotjot_ > mjotjot_) mjotjot_ = tempMjotjot_;
    }
  }
  return mjotjot_;
}

vector<TLorentzVector> crossCleanJets(vector<TLorentzVector> jetObjs, vector<TLorentzVector> tauObjs) {
  vector<TLorentzVector> crossCleanedJets;
  int jetObjsSize = jetObjs.size();
  int tauObjsSize = tauObjs.size();
  //cout << jetObjsSize << " jetObjsSize" << endl;
  //cout << tauObjsSize << " tauObjsSize" << endl;
  //int counter = 0;
  if (jetObjsSize >= 2 && tauObjsSize >= 1) {
    for (int iJet = 0; iJet < jetObjsSize; ++iJet) {
      bool jetIsNotTau = true;
      //cout << "iJet: " << iJet << endl;
      //if (counter < 2) { // jet is no longer checked once two matched taus are found
        for (int iTau = 0; iTau < tauObjsSize; ++iTau) {
          float dR = jetObjs.at(iJet).DeltaR(tauObjs.at(iTau));
          //if (dR < 0.5) cout << "\033[0;31m" << dR << "\033[0m" << endl;
          //else {cout << dR << endl;}
          if (dR < 0.2) jetIsNotTau = false;
        }
      //}
      //if (!jetIsNotTau) counter += 1; // if jet matches a tau (or two taus) inc counter
      if (jetIsNotTau) crossCleanedJets.push_back(jetObjs.at(iJet));
    }
  }
  else {crossCleanedJets = jetObjs;}
  //cout << crossCleanedJets.size() << " ccJetsSize" << endl;
/***
      if (counter >= 2 && tauObjsSize >=3 && jetObjsSize >= 3) {

      //if (tauObjsSize >= 3) cout << "\033[0;31m" << "tauObjsSize: " << tauObjsSize << "\033[0m" << endl;
      //else {cout << "tauObjsSize: " << tauObjsSize << endl;}
      //cout << "jetObjsSize: " << jetObjsSize << endl;
      //cout << "ccJetsSize: " << crossCleanedJets.size() << endl;
        if (jetObjsSize - crossCleanedJets.size() == 1) {
          cout << "tauObjsSize: " << tauObjsSize << " jetObjsSize: " << jetObjsSize << " ccJetsSize: " << crossCleanedJets.size() << endl;
          for (int iJet = 0; iJet < jetObjsSize; ++iJet) {
            cout << "iJet: " << iJet << endl;
            for (int iTau = 0; iTau < tauObjsSize; ++iTau) {
              cout << jetObjs.at(iJet).DeltaR(tauObjs.at(iTau)) << endl;
            }
          }
        }


      }
***/

  return crossCleanedJets;
}

int ManfredLogic(vector<TLorentzVector> jets, vector<TLorentzVector> taus) {
  int tausSize = taus.size();
  int jetsSize = jets.size();

  //cout << "TauSize: " << tausSize << " JetSize: " << jetsSize << endl;
  for (int iTau = 0; iTau < tausSize; ++iTau) {
    for (int iJet = 0; iJet < jetsSize; ++iJet) {
      float dR_iJet = jets.at(iJet).DeltaR(taus.at(iTau));
      if (dR_iJet < 0.2) continue; // if overlapped, go to next jet
      for (int jJet = iJet+1; jJet < jetsSize; ++jJet) {
        //if ( iJet >= jJet ) continue; // don't look at same jet, or repeat combinations
        //cout << "Tau: " << iTau << " Jet1: " << iJet << " Jet2: " << jJet << endl;     
        float dR_jJet = jets.at(jJet).DeltaR(taus.at(iTau));
        if (dR_jJet < 0.2) continue; // if overlapped, go to next jet
        //cout << dR_iJet << " dR_iJet " << dR_jJet << " dR_jJet " << endl; 
        float mjj = (jets.at(iJet) + jets.at(jJet)).M();
        //cout << mjj << " mjj" << endl;
        if (mjj >= 450) return 1;
      }
    }
  }
  return 0;

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

  FILE *out_file = fopen("output.txt", "w");
  if (out_file == NULL) {
    fprintf(out_file, "Error, couldn't open file\n");
    return;
    //exit(-1);
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

  int passTripJets = 0;
  int passTripJetsCount = 0;

  int mjjCuts[6] = {350, 400, 450, 500, 550, 600};
  //jet 35
  int passSeed2_3525All[6] = {0,0,0,0,0,0};
  int passSeed2_3530All[6] = {0,0,0,0,0,0};
  int passSeed2_3532All[6] = {0,0,0,0,0,0};
  int passSeed2_3534All[6] = {0,0,0,0,0,0};
  int passSeed2_3535All[6] = {0,0,0,0,0,0};
  int passSeed2_3536All[6] = {0,0,0,0,0,0};
  int passSeed2_3538All[6] = {0,0,0,0,0,0};
  int passSeed2_3540All[6] = {0,0,0,0,0,0};
  int passSeed2_3542All[6] = {0,0,0,0,0,0};
  int passSeed2_3544All[6] = {0,0,0,0,0,0};
  int passSeed2_3545All[6] = {0,0,0,0,0,0};
  int passSeed2_3546All[6] = {0,0,0,0,0,0};
  int passSeed2_3548All[6] = {0,0,0,0,0,0};
  int passSeed2_3550All[6] = {0,0,0,0,0,0};
  int passSeed2_3555All[6] = {0,0,0,0,0,0};
  int passSeed2_3560All[6] = {0,0,0,0,0,0};
  int passSeed2_3525All_count[6] = {0,0,0,0,0,0};
  int passSeed2_3530All_count[6] = {0,0,0,0,0,0};
  int passSeed2_3532All_count[6] = {0,0,0,0,0,0};
  int passSeed2_3534All_count[6] = {0,0,0,0,0,0};
  int passSeed2_3535All_count[6] = {0,0,0,0,0,0};
  int passSeed2_3536All_count[6] = {0,0,0,0,0,0};
  int passSeed2_3538All_count[6] = {0,0,0,0,0,0};
  int passSeed2_3540All_count[6] = {0,0,0,0,0,0};
  int passSeed2_3542All_count[6] = {0,0,0,0,0,0};
  int passSeed2_3544All_count[6] = {0,0,0,0,0,0};
  int passSeed2_3545All_count[6] = {0,0,0,0,0,0};
  int passSeed2_3546All_count[6] = {0,0,0,0,0,0};
  int passSeed2_3548All_count[6] = {0,0,0,0,0,0};
  int passSeed2_3550All_count[6] = {0,0,0,0,0,0};
  int passSeed2_3555All_count[6] = {0,0,0,0,0,0};
  int passSeed2_3560All_count[6] = {0,0,0,0,0,0};
  //jet 40
  int passSeed2_4025All[6] = {0,0,0,0,0,0};
  int passSeed2_4030All[6] = {0,0,0,0,0,0};
  int passSeed2_4032All[6] = {0,0,0,0,0,0};
  int passSeed2_4034All[6] = {0,0,0,0,0,0};
  int passSeed2_4035All[6] = {0,0,0,0,0,0};
  int passSeed2_4036All[6] = {0,0,0,0,0,0};
  int passSeed2_4038All[6] = {0,0,0,0,0,0};
  int passSeed2_4040All[6] = {0,0,0,0,0,0};
  int passSeed2_4042All[6] = {0,0,0,0,0,0};
  int passSeed2_4044All[6] = {0,0,0,0,0,0};
  int passSeed2_4045All[6] = {0,0,0,0,0,0};
  int passSeed2_4046All[6] = {0,0,0,0,0,0};
  int passSeed2_4048All[6] = {0,0,0,0,0,0};
  int passSeed2_4050All[6] = {0,0,0,0,0,0};
  int passSeed2_4055All[6] = {0,0,0,0,0,0};
  int passSeed2_4060All[6] = {0,0,0,0,0,0};
  int passSeed2_4025All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4030All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4032All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4034All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4035All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4036All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4038All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4040All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4042All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4044All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4045All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4046All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4048All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4050All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4055All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4060All_count[6] = {0,0,0,0,0,0};
  //jet 45
  int passSeed2_4525All[6] = {0,0,0,0,0,0};
  int passSeed2_4530All[6] = {0,0,0,0,0,0};
  int passSeed2_4532All[6] = {0,0,0,0,0,0};
  int passSeed2_4534All[6] = {0,0,0,0,0,0};
  int passSeed2_4535All[6] = {0,0,0,0,0,0};
  int passSeed2_4536All[6] = {0,0,0,0,0,0};
  int passSeed2_4538All[6] = {0,0,0,0,0,0};
  int passSeed2_4540All[6] = {0,0,0,0,0,0};
  int passSeed2_4542All[6] = {0,0,0,0,0,0};
  int passSeed2_4544All[6] = {0,0,0,0,0,0};
  int passSeed2_4545All[6] = {0,0,0,0,0,0};
  int passSeed2_4546All[6] = {0,0,0,0,0,0};
  int passSeed2_4548All[6] = {0,0,0,0,0,0};
  int passSeed2_4550All[6] = {0,0,0,0,0,0};
  int passSeed2_4555All[6] = {0,0,0,0,0,0};
  int passSeed2_4560All[6] = {0,0,0,0,0,0};
  int passSeed2_4525All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4530All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4532All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4534All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4535All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4536All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4538All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4540All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4542All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4544All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4545All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4546All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4548All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4550All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4555All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4560All_count[6] = {0,0,0,0,0,0};
  //jet 50
  int passSeed2_5025All[6] = {0,0,0,0,0,0};
  int passSeed2_5030All[6] = {0,0,0,0,0,0};
  int passSeed2_5032All[6] = {0,0,0,0,0,0};
  int passSeed2_5034All[6] = {0,0,0,0,0,0};
  int passSeed2_5035All[6] = {0,0,0,0,0,0};
  int passSeed2_5036All[6] = {0,0,0,0,0,0};
  int passSeed2_5038All[6] = {0,0,0,0,0,0};
  int passSeed2_5040All[6] = {0,0,0,0,0,0};
  int passSeed2_5042All[6] = {0,0,0,0,0,0};
  int passSeed2_5044All[6] = {0,0,0,0,0,0};
  int passSeed2_5045All[6] = {0,0,0,0,0,0};
  int passSeed2_5046All[6] = {0,0,0,0,0,0};
  int passSeed2_5048All[6] = {0,0,0,0,0,0};
  int passSeed2_5050All[6] = {0,0,0,0,0,0};
  int passSeed2_5055All[6] = {0,0,0,0,0,0};
  int passSeed2_5060All[6] = {0,0,0,0,0,0};
  int passSeed2_5025All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5030All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5032All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5034All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5035All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5036All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5038All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5040All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5042All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5044All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5045All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5046All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5048All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5050All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5055All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5060All_count[6] = {0,0,0,0,0,0};

  //jet 55
  int passSeed2_5525All[6] = {0,0,0,0,0,0};
  int passSeed2_5530All[6] = {0,0,0,0,0,0};
  int passSeed2_5532All[6] = {0,0,0,0,0,0};
  int passSeed2_5534All[6] = {0,0,0,0,0,0};
  int passSeed2_5535All[6] = {0,0,0,0,0,0};
  int passSeed2_5536All[6] = {0,0,0,0,0,0};
  int passSeed2_5538All[6] = {0,0,0,0,0,0};
  int passSeed2_5540All[6] = {0,0,0,0,0,0};
  int passSeed2_5542All[6] = {0,0,0,0,0,0};
  int passSeed2_5544All[6] = {0,0,0,0,0,0};
  int passSeed2_5545All[6] = {0,0,0,0,0,0};
  int passSeed2_5546All[6] = {0,0,0,0,0,0};
  int passSeed2_5548All[6] = {0,0,0,0,0,0};
  int passSeed2_5550All[6] = {0,0,0,0,0,0};
  int passSeed2_5555All[6] = {0,0,0,0,0,0};
  int passSeed2_5560All[6] = {0,0,0,0,0,0};
  int passSeed2_5525All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5530All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5532All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5534All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5535All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5536All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5538All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5540All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5542All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5544All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5545All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5546All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5548All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5550All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5555All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5560All_count[6] = {0,0,0,0,0,0};
  //jet 60
  int passSeed2_6025All[6] = {0,0,0,0,0,0};
  int passSeed2_6030All[6] = {0,0,0,0,0,0};
  int passSeed2_6032All[6] = {0,0,0,0,0,0};
  int passSeed2_6034All[6] = {0,0,0,0,0,0};
  int passSeed2_6035All[6] = {0,0,0,0,0,0};
  int passSeed2_6036All[6] = {0,0,0,0,0,0};
  int passSeed2_6038All[6] = {0,0,0,0,0,0};
  int passSeed2_6040All[6] = {0,0,0,0,0,0};
  int passSeed2_6042All[6] = {0,0,0,0,0,0};
  int passSeed2_6044All[6] = {0,0,0,0,0,0};
  int passSeed2_6045All[6] = {0,0,0,0,0,0};
  int passSeed2_6046All[6] = {0,0,0,0,0,0};
  int passSeed2_6048All[6] = {0,0,0,0,0,0};
  int passSeed2_6050All[6] = {0,0,0,0,0,0};
  int passSeed2_6055All[6] = {0,0,0,0,0,0};
  int passSeed2_6060All[6] = {0,0,0,0,0,0};
  int passSeed2_6025All_count[6] = {0,0,0,0,0,0};
  int passSeed2_6030All_count[6] = {0,0,0,0,0,0};
  int passSeed2_6032All_count[6] = {0,0,0,0,0,0};
  int passSeed2_6034All_count[6] = {0,0,0,0,0,0};
  int passSeed2_6035All_count[6] = {0,0,0,0,0,0};
  int passSeed2_6036All_count[6] = {0,0,0,0,0,0};
  int passSeed2_6038All_count[6] = {0,0,0,0,0,0};
  int passSeed2_6040All_count[6] = {0,0,0,0,0,0};
  int passSeed2_6042All_count[6] = {0,0,0,0,0,0};
  int passSeed2_6044All_count[6] = {0,0,0,0,0,0};
  int passSeed2_6045All_count[6] = {0,0,0,0,0,0};
  int passSeed2_6046All_count[6] = {0,0,0,0,0,0};
  int passSeed2_6048All_count[6] = {0,0,0,0,0,0};
  int passSeed2_6050All_count[6] = {0,0,0,0,0,0};
  int passSeed2_6055All_count[6] = {0,0,0,0,0,0};
  int passSeed2_6060All_count[6] = {0,0,0,0,0,0};
  //
  //
  //extras from after acceptance study
  int passSeed2_3545400All[6] = {0,0,0,0,0,0};
  int passSeed2_3538500All[6] = {0,0,0,0,0,0};
  int passSeed2_4028600All[6] = {0,0,0,0,0,0};
  int passSeed2_4528450All[6] = {0,0,0,0,0,0};
  int passSeed2_4528500All[6] = {0,0,0,0,0,0};
  int passSeed2_4528550All[6] = {0,0,0,0,0,0};
  int passSeed2_5028400All[6] = {0,0,0,0,0,0};
  int passSeed2_5025450All[6] = {0,0,0,0,0,0};

  int passSeed2_3545400All_count[6] = {0,0,0,0,0,0};
  int passSeed2_3538500All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4028600All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4528450All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4528500All_count[6] = {0,0,0,0,0,0};
  int passSeed2_4528550All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5028400All_count[6] = {0,0,0,0,0,0};
  int passSeed2_5025450All_count[6] = {0,0,0,0,0,0};

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

  int orNewVBFTripJets = 0;
  int orDiTauTripJets = 0;
  int orDiTauNewVBFTripJets = 0;

  int passManfredLogic = 0;
  int passManfredLogicCount = 0;
  int orDiTauOldVBFManfredLogic = 0;

  int passSeed2Testing = 0;
  int passSeed2TestingCount = 0;
  int orDiTauOldSeed2Testing = 0;
  int overlapManfredNew = 0;

  // start event loop
  for (Long64_t jentry=0; jentry<nentries1; ++jentry) { // full dataset
  //for (Long64_t jentry=0; jentry<500001; ++jentry) {
  //for (Long64_t jentry=11100000; jentry<11400000; ++jentry) { // full run 323755

    if (jentry%100000 == 0 && jentry != 0) cout << jentry << endl;
    //if (jentry == 50000) return;
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;

    // update both chains of TTree files 
    nb = fChain1->GetEntry(jentry);   nbytes += nb;
    nb = fChain2->GetEntry(jentry);

    // reject events not in selected run number
    // save lumi block info for new blocks (using C std::set)
    eventCount += 1;
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

    passTripJets = 0;
    passManfredLogic = 0;
    passSeed2Testing = 0;
  
    //initialize variations 
    for (int i = 0; i<6; ++i){
      passSeed2_3525All[i] = 0;
      passSeed2_3530All[i] = 0;
      passSeed2_3532All[i] = 0;
      passSeed2_3534All[i] = 0;
      passSeed2_3535All[i] = 0;
      passSeed2_3536All[i] = 0;
      passSeed2_3538All[i] = 0;
      passSeed2_3540All[i] = 0;
      passSeed2_3542All[i] = 0;
      passSeed2_3544All[i] = 0;
      passSeed2_3545All[i] = 0;
      passSeed2_3546All[i] = 0;
      passSeed2_3548All[i] = 0;
      passSeed2_3550All[i] = 0;
      passSeed2_3555All[i] = 0;
      passSeed2_3560All[i] = 0;

      passSeed2_4025All[i] = 0;
      passSeed2_4030All[i] = 0;
      passSeed2_4032All[i] = 0;
      passSeed2_4034All[i] = 0;
      passSeed2_4035All[i] = 0;
      passSeed2_4036All[i] = 0;
      passSeed2_4038All[i] = 0;
      passSeed2_4040All[i] = 0;
      passSeed2_4042All[i] = 0;
      passSeed2_4044All[i] = 0;
      passSeed2_4045All[i] = 0;
      passSeed2_4046All[i] = 0;
      passSeed2_4048All[i] = 0;
      passSeed2_4050All[i] = 0;
      passSeed2_4055All[i] = 0;
      passSeed2_4060All[i] = 0;

      passSeed2_4525All[i] = 0;
      passSeed2_4530All[i] = 0;
      passSeed2_4532All[i] = 0;
      passSeed2_4534All[i] = 0;
      passSeed2_4535All[i] = 0;
      passSeed2_4536All[i] = 0;
      passSeed2_4538All[i] = 0;
      passSeed2_4540All[i] = 0;
      passSeed2_4542All[i] = 0;
      passSeed2_4544All[i] = 0;
      passSeed2_4545All[i] = 0;
      passSeed2_4546All[i] = 0;
      passSeed2_4548All[i] = 0;
      passSeed2_4550All[i] = 0;
      passSeed2_4555All[i] = 0;
      passSeed2_4560All[i] = 0;

      passSeed2_5025All[i] = 0;
      passSeed2_5030All[i] = 0;
      passSeed2_5032All[i] = 0;
      passSeed2_5034All[i] = 0;
      passSeed2_5035All[i] = 0;
      passSeed2_5036All[i] = 0;
      passSeed2_5038All[i] = 0;
      passSeed2_5040All[i] = 0;
      passSeed2_5042All[i] = 0;
      passSeed2_5044All[i] = 0;
      passSeed2_5045All[i] = 0;
      passSeed2_5046All[i] = 0;
      passSeed2_5048All[i] = 0;
      passSeed2_5050All[i] = 0;
      passSeed2_5055All[i] = 0;
      passSeed2_5060All[i] = 0;

      passSeed2_5525All[i] = 0;
      passSeed2_5530All[i] = 0;
      passSeed2_5532All[i] = 0;
      passSeed2_5534All[i] = 0;
      passSeed2_5535All[i] = 0;
      passSeed2_5536All[i] = 0;
      passSeed2_5538All[i] = 0;
      passSeed2_5540All[i] = 0;
      passSeed2_5542All[i] = 0;
      passSeed2_5544All[i] = 0;
      passSeed2_5545All[i] = 0;
      passSeed2_5546All[i] = 0;
      passSeed2_5548All[i] = 0;
      passSeed2_5550All[i] = 0;
      passSeed2_5555All[i] = 0;
      passSeed2_5560All[i] = 0;

      passSeed2_6025All[i] = 0;
      passSeed2_6030All[i] = 0;
      passSeed2_6032All[i] = 0;
      passSeed2_6034All[i] = 0;
      passSeed2_6035All[i] = 0;
      passSeed2_6036All[i] = 0;
      passSeed2_6038All[i] = 0;
      passSeed2_6040All[i] = 0;
      passSeed2_6042All[i] = 0;
      passSeed2_6044All[i] = 0;
      passSeed2_6045All[i] = 0;
      passSeed2_6046All[i] = 0;
      passSeed2_6048All[i] = 0;
      passSeed2_6050All[i] = 0;
      passSeed2_6055All[i] = 0;
      passSeed2_6060All[i] = 0;

      //extra
      passSeed2_3545400All[i] = 0;
      passSeed2_3538500All[i] = 0;
      passSeed2_4028600All[i] = 0;
      passSeed2_4528450All[i] = 0;
      passSeed2_4528500All[i] = 0;
      passSeed2_4528550All[i] = 0;
      passSeed2_5028400All[i] = 0;
      passSeed2_5025450All[i] = 0;

    }

    // build container of taus (two containers are built here at the same time, one is not req. to be isotau)
    // Branch Crossing (Bx) equals zero
    TLorentzVector tempTauIso25;
    vector<TLorentzVector> tauCandsIso25;
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
      if (tauEt_ >= 25 && fabs(tauEta_) <= 2.1 && tauIso[iTau] > 0) {
        tempTauIso25.SetPtEtaPhiM(tauEt_, tauEta_, tauPhi[iTau], 0);
        tauCandsIso25.push_back(tempTauIso25);
      }
    }
    int tauCandsIso25Size = tauCandsIso25.size();
    int tauCands35Size = tauCands35.size();

    vector<TLorentzVector> tauCandsIso28;
    vector<TLorentzVector> tauCandsIso30;
    vector<TLorentzVector> tauCandsIso32;
    vector<TLorentzVector> tauCandsIso34;
    vector<TLorentzVector> tauCandsIso35;
    vector<TLorentzVector> tauCandsIso36;
    vector<TLorentzVector> tauCandsIso38;
    vector<TLorentzVector> tauCandsIso40;
    vector<TLorentzVector> tauCandsIso42;
    vector<TLorentzVector> tauCandsIso44;
    vector<TLorentzVector> tauCandsIso45;
    vector<TLorentzVector> tauCandsIso46;
    vector<TLorentzVector> tauCandsIso48;
    vector<TLorentzVector> tauCandsIso50; 
    vector<TLorentzVector> tauCandsIso55;
    vector<TLorentzVector> tauCandsIso60;
    vector<TLorentzVector> tauCandsIso65;
    float tauPt_;
    TLorentzVector tempTau_;
    for (int iTau = 0; iTau < tauCandsIso25Size; ++iTau) {
      tempTau_ = tauCandsIso25.at(iTau);
      tauPt_ = tempTau_.Pt();
      if (tauPt_ >= 28) tauCandsIso28.push_back(tempTau_);
      if (tauPt_ >= 30) tauCandsIso30.push_back(tempTau_);
      if (tauPt_ >= 32) tauCandsIso32.push_back(tempTau_);
      if (tauPt_ >= 34) tauCandsIso34.push_back(tempTau_);
      if (tauPt_ >= 35) tauCandsIso35.push_back(tempTau_);
      if (tauPt_ >= 36) tauCandsIso36.push_back(tempTau_);
      if (tauPt_ >= 38) tauCandsIso38.push_back(tempTau_);
      if (tauPt_ >= 40) tauCandsIso40.push_back(tempTau_);
      if (tauPt_ >= 42) tauCandsIso42.push_back(tempTau_);
      if (tauPt_ >= 44) tauCandsIso44.push_back(tempTau_);
      if (tauPt_ >= 45) tauCandsIso45.push_back(tempTau_);
      if (tauPt_ >= 46) tauCandsIso46.push_back(tempTau_);
      if (tauPt_ >= 48) tauCandsIso48.push_back(tempTau_);
      if (tauPt_ >= 50) tauCandsIso50.push_back(tempTau_);
      if (tauPt_ >= 55) tauCandsIso55.push_back(tempTau_);
      if (tauPt_ >= 60) tauCandsIso60.push_back(tempTau_);
      if (tauPt_ >= 65) tauCandsIso65.push_back(tempTau_);
    }
    int tauCandsIso28Size = tauCandsIso28.size();
    int tauCandsIso30Size = tauCandsIso30.size();
    int tauCandsIso32Size = tauCandsIso32.size();
    int tauCandsIso34Size = tauCandsIso34.size();
    int tauCandsIso35Size = tauCandsIso35.size();
    int tauCandsIso36Size = tauCandsIso36.size();
    int tauCandsIso38Size = tauCandsIso38.size();
    int tauCandsIso40Size = tauCandsIso40.size();
    int tauCandsIso42Size = tauCandsIso42.size();
    int tauCandsIso44Size = tauCandsIso44.size();
    int tauCandsIso45Size = tauCandsIso45.size();
    int tauCandsIso46Size = tauCandsIso46.size();
    int tauCandsIso48Size = tauCandsIso48.size();
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
    // i want to say Yurii told me one time "nice code is nice, but we really care about results"
    // so this is in the spirit of that sentiment

    // isoTau25
    vector<TLorentzVector> jetCands35RmvOlTauCandsIso25;
    vector<TLorentzVector> jetCands40RmvOlTauCandsIso25;
    vector<TLorentzVector> jetCands45RmvOlTauCandsIso25;
    vector<TLorentzVector> jetCands50RmvOlTauCandsIso25;
    vector<TLorentzVector> jetCands55RmvOlTauCandsIso25;
    vector<TLorentzVector> jetCands60RmvOlTauCandsIso25;
    if (jetCands35Size >= 2) jetCands35RmvOlTauCandsIso25 = crossCleanJets(jetCands35, tauCandsIso25);
    if (jetCands40Size >= 2) jetCands40RmvOlTauCandsIso25 = crossCleanJets(jetCands40, tauCandsIso25);
    if (jetCands45Size >= 2) jetCands45RmvOlTauCandsIso25 = crossCleanJets(jetCands45, tauCandsIso25);
    if (jetCands50Size >= 2) jetCands50RmvOlTauCandsIso25 = crossCleanJets(jetCands50, tauCandsIso25);
    if (jetCands55Size >= 2) jetCands55RmvOlTauCandsIso25 = crossCleanJets(jetCands55, tauCandsIso25);
    if (jetCands60Size >= 2) jetCands60RmvOlTauCandsIso25 = crossCleanJets(jetCands60, tauCandsIso25);
    int jetCands35RmvOlTauCandsIso25Size = jetCands35RmvOlTauCandsIso25.size();
    int jetCands40RmvOlTauCandsIso25Size = jetCands40RmvOlTauCandsIso25.size();
    int jetCands45RmvOlTauCandsIso25Size = jetCands45RmvOlTauCandsIso25.size();
    int jetCands50RmvOlTauCandsIso25Size = jetCands50RmvOlTauCandsIso25.size();
    int jetCands55RmvOlTauCandsIso25Size = jetCands55RmvOlTauCandsIso25.size();
    int jetCands60RmvOlTauCandsIso25Size = jetCands60RmvOlTauCandsIso25.size();

    // isoTau30
    vector<TLorentzVector> jetCands35RmvOlTauCandsIso30;
    vector<TLorentzVector> jetCands40RmvOlTauCandsIso30;
    vector<TLorentzVector> jetCands45RmvOlTauCandsIso30;
    vector<TLorentzVector> jetCands50RmvOlTauCandsIso30;
    vector<TLorentzVector> jetCands55RmvOlTauCandsIso30;
    vector<TLorentzVector> jetCands60RmvOlTauCandsIso30;
    if (jetCands35Size >= 2) jetCands35RmvOlTauCandsIso30 = crossCleanJets(jetCands35, tauCandsIso30);
    if (jetCands40Size >= 2) jetCands40RmvOlTauCandsIso30 = crossCleanJets(jetCands40, tauCandsIso30);
    if (jetCands45Size >= 2) jetCands45RmvOlTauCandsIso30 = crossCleanJets(jetCands45, tauCandsIso30);
    if (jetCands50Size >= 2) jetCands50RmvOlTauCandsIso30 = crossCleanJets(jetCands50, tauCandsIso30);
    if (jetCands55Size >= 2) jetCands55RmvOlTauCandsIso30 = crossCleanJets(jetCands55, tauCandsIso30);
    if (jetCands60Size >= 2) jetCands60RmvOlTauCandsIso30 = crossCleanJets(jetCands60, tauCandsIso30);
    int jetCands35RmvOlTauCandsIso30Size = jetCands35RmvOlTauCandsIso30.size();
    int jetCands40RmvOlTauCandsIso30Size = jetCands40RmvOlTauCandsIso30.size();
    int jetCands45RmvOlTauCandsIso30Size = jetCands45RmvOlTauCandsIso30.size();
    int jetCands50RmvOlTauCandsIso30Size = jetCands50RmvOlTauCandsIso30.size();
    int jetCands55RmvOlTauCandsIso30Size = jetCands55RmvOlTauCandsIso30.size();
    int jetCands60RmvOlTauCandsIso30Size = jetCands60RmvOlTauCandsIso30.size();

    // isoTau32
    vector<TLorentzVector> jetCands35RmvOlTauCandsIso32;
    vector<TLorentzVector> jetCands40RmvOlTauCandsIso32;
    vector<TLorentzVector> jetCands45RmvOlTauCandsIso32;
    vector<TLorentzVector> jetCands50RmvOlTauCandsIso32;
    vector<TLorentzVector> jetCands55RmvOlTauCandsIso32;
    vector<TLorentzVector> jetCands60RmvOlTauCandsIso32;
    if (jetCands35Size >= 2) jetCands35RmvOlTauCandsIso32 = crossCleanJets(jetCands35, tauCandsIso32);
    if (jetCands40Size >= 2) jetCands40RmvOlTauCandsIso32 = crossCleanJets(jetCands40, tauCandsIso32);
    if (jetCands45Size >= 2) jetCands45RmvOlTauCandsIso32 = crossCleanJets(jetCands45, tauCandsIso32);
    if (jetCands50Size >= 2) jetCands50RmvOlTauCandsIso32 = crossCleanJets(jetCands50, tauCandsIso32);
    if (jetCands55Size >= 2) jetCands55RmvOlTauCandsIso32 = crossCleanJets(jetCands55, tauCandsIso32);
    if (jetCands60Size >= 2) jetCands60RmvOlTauCandsIso32 = crossCleanJets(jetCands60, tauCandsIso32);
    int jetCands35RmvOlTauCandsIso32Size = jetCands35RmvOlTauCandsIso32.size();
    int jetCands40RmvOlTauCandsIso32Size = jetCands40RmvOlTauCandsIso32.size();
    int jetCands45RmvOlTauCandsIso32Size = jetCands45RmvOlTauCandsIso32.size();
    int jetCands50RmvOlTauCandsIso32Size = jetCands50RmvOlTauCandsIso32.size();
    int jetCands55RmvOlTauCandsIso32Size = jetCands55RmvOlTauCandsIso32.size();
    int jetCands60RmvOlTauCandsIso32Size = jetCands60RmvOlTauCandsIso32.size();

    // isoTau34
    vector<TLorentzVector> jetCands35RmvOlTauCandsIso34;
    vector<TLorentzVector> jetCands40RmvOlTauCandsIso34;
    vector<TLorentzVector> jetCands45RmvOlTauCandsIso34;
    vector<TLorentzVector> jetCands50RmvOlTauCandsIso34;
    vector<TLorentzVector> jetCands55RmvOlTauCandsIso34;
    vector<TLorentzVector> jetCands60RmvOlTauCandsIso34;
    if (jetCands35Size >= 2) jetCands35RmvOlTauCandsIso34 = crossCleanJets(jetCands35, tauCandsIso34);
    if (jetCands40Size >= 2) jetCands40RmvOlTauCandsIso34 = crossCleanJets(jetCands40, tauCandsIso34);
    if (jetCands45Size >= 2) jetCands45RmvOlTauCandsIso34 = crossCleanJets(jetCands45, tauCandsIso34);
    if (jetCands50Size >= 2) jetCands50RmvOlTauCandsIso34 = crossCleanJets(jetCands50, tauCandsIso34);
    if (jetCands55Size >= 2) jetCands55RmvOlTauCandsIso34 = crossCleanJets(jetCands55, tauCandsIso34);
    if (jetCands60Size >= 2) jetCands60RmvOlTauCandsIso34 = crossCleanJets(jetCands60, tauCandsIso34);
    int jetCands35RmvOlTauCandsIso34Size = jetCands35RmvOlTauCandsIso34.size();
    int jetCands40RmvOlTauCandsIso34Size = jetCands40RmvOlTauCandsIso34.size();
    int jetCands45RmvOlTauCandsIso34Size = jetCands45RmvOlTauCandsIso34.size();
    int jetCands50RmvOlTauCandsIso34Size = jetCands50RmvOlTauCandsIso34.size();
    int jetCands55RmvOlTauCandsIso34Size = jetCands55RmvOlTauCandsIso34.size();
    int jetCands60RmvOlTauCandsIso34Size = jetCands60RmvOlTauCandsIso34.size();


    // isoTau35 
    vector<TLorentzVector> jetCands35RmvOlTauCandsIso35;
    vector<TLorentzVector> jetCands40RmvOlTauCandsIso35;
    vector<TLorentzVector> jetCands45RmvOlTauCandsIso35;
    vector<TLorentzVector> jetCands50RmvOlTauCandsIso35;
    vector<TLorentzVector> jetCands55RmvOlTauCandsIso35;
    vector<TLorentzVector> jetCands60RmvOlTauCandsIso35;
    if (jetCands35Size >= 2) jetCands35RmvOlTauCandsIso35 = crossCleanJets(jetCands35, tauCandsIso35);
    if (jetCands40Size >= 2) jetCands40RmvOlTauCandsIso35 = crossCleanJets(jetCands40, tauCandsIso35);
    if (jetCands45Size >= 2) jetCands45RmvOlTauCandsIso35 = crossCleanJets(jetCands45, tauCandsIso35);
    if (jetCands50Size >= 2) jetCands50RmvOlTauCandsIso35 = crossCleanJets(jetCands50, tauCandsIso35);
    if (jetCands55Size >= 2) jetCands55RmvOlTauCandsIso35 = crossCleanJets(jetCands55, tauCandsIso35);
    if (jetCands60Size >= 2) jetCands60RmvOlTauCandsIso35 = crossCleanJets(jetCands60, tauCandsIso35);
    int jetCands35RmvOlTauCandsIso35Size = jetCands35RmvOlTauCandsIso35.size();
    int jetCands40RmvOlTauCandsIso35Size = jetCands40RmvOlTauCandsIso35.size();
    int jetCands45RmvOlTauCandsIso35Size = jetCands45RmvOlTauCandsIso35.size();
    int jetCands50RmvOlTauCandsIso35Size = jetCands50RmvOlTauCandsIso35.size();
    int jetCands55RmvOlTauCandsIso35Size = jetCands55RmvOlTauCandsIso35.size();
    int jetCands60RmvOlTauCandsIso35Size = jetCands60RmvOlTauCandsIso35.size();

    // isoTau36
    vector<TLorentzVector> jetCands35RmvOlTauCandsIso36;
    vector<TLorentzVector> jetCands40RmvOlTauCandsIso36;
    vector<TLorentzVector> jetCands45RmvOlTauCandsIso36;
    vector<TLorentzVector> jetCands50RmvOlTauCandsIso36;
    vector<TLorentzVector> jetCands55RmvOlTauCandsIso36;
    vector<TLorentzVector> jetCands60RmvOlTauCandsIso36;
    if (jetCands35Size >= 2) jetCands35RmvOlTauCandsIso36 = crossCleanJets(jetCands35, tauCandsIso36);
    if (jetCands40Size >= 2) jetCands40RmvOlTauCandsIso36 = crossCleanJets(jetCands40, tauCandsIso36);
    if (jetCands45Size >= 2) jetCands45RmvOlTauCandsIso36 = crossCleanJets(jetCands45, tauCandsIso36);
    if (jetCands50Size >= 2) jetCands50RmvOlTauCandsIso36 = crossCleanJets(jetCands50, tauCandsIso36);
    if (jetCands55Size >= 2) jetCands55RmvOlTauCandsIso36 = crossCleanJets(jetCands55, tauCandsIso36);
    if (jetCands60Size >= 2) jetCands60RmvOlTauCandsIso36 = crossCleanJets(jetCands60, tauCandsIso36);
    int jetCands35RmvOlTauCandsIso36Size = jetCands35RmvOlTauCandsIso36.size();
    int jetCands40RmvOlTauCandsIso36Size = jetCands40RmvOlTauCandsIso36.size();
    int jetCands45RmvOlTauCandsIso36Size = jetCands45RmvOlTauCandsIso36.size();
    int jetCands50RmvOlTauCandsIso36Size = jetCands50RmvOlTauCandsIso36.size();
    int jetCands55RmvOlTauCandsIso36Size = jetCands55RmvOlTauCandsIso36.size();
    int jetCands60RmvOlTauCandsIso36Size = jetCands60RmvOlTauCandsIso36.size();

    // isoTau38
    vector<TLorentzVector> jetCands35RmvOlTauCandsIso38;
    vector<TLorentzVector> jetCands40RmvOlTauCandsIso38;
    vector<TLorentzVector> jetCands45RmvOlTauCandsIso38;
    vector<TLorentzVector> jetCands50RmvOlTauCandsIso38;
    vector<TLorentzVector> jetCands55RmvOlTauCandsIso38;
    vector<TLorentzVector> jetCands60RmvOlTauCandsIso38;
    if (jetCands35Size >= 2) jetCands35RmvOlTauCandsIso38 = crossCleanJets(jetCands35, tauCandsIso38);
    if (jetCands40Size >= 2) jetCands40RmvOlTauCandsIso38 = crossCleanJets(jetCands40, tauCandsIso38);
    if (jetCands45Size >= 2) jetCands45RmvOlTauCandsIso38 = crossCleanJets(jetCands45, tauCandsIso38);
    if (jetCands50Size >= 2) jetCands50RmvOlTauCandsIso38 = crossCleanJets(jetCands50, tauCandsIso38);
    if (jetCands55Size >= 2) jetCands55RmvOlTauCandsIso38 = crossCleanJets(jetCands55, tauCandsIso38);
    if (jetCands60Size >= 2) jetCands60RmvOlTauCandsIso38 = crossCleanJets(jetCands60, tauCandsIso38);
    int jetCands35RmvOlTauCandsIso38Size = jetCands35RmvOlTauCandsIso38.size();
    int jetCands40RmvOlTauCandsIso38Size = jetCands40RmvOlTauCandsIso38.size();
    int jetCands45RmvOlTauCandsIso38Size = jetCands45RmvOlTauCandsIso38.size();
    int jetCands50RmvOlTauCandsIso38Size = jetCands50RmvOlTauCandsIso38.size();
    int jetCands55RmvOlTauCandsIso38Size = jetCands55RmvOlTauCandsIso38.size();
    int jetCands60RmvOlTauCandsIso38Size = jetCands60RmvOlTauCandsIso38.size();


    // isoTau40
    vector<TLorentzVector> jetCands35RmvOlTauCandsIso40;
    vector<TLorentzVector> jetCands40RmvOlTauCandsIso40;
    vector<TLorentzVector> jetCands45RmvOlTauCandsIso40;
    vector<TLorentzVector> jetCands50RmvOlTauCandsIso40;
    vector<TLorentzVector> jetCands55RmvOlTauCandsIso40;
    vector<TLorentzVector> jetCands60RmvOlTauCandsIso40;
    if (jetCands35Size >= 2) jetCands35RmvOlTauCandsIso40 = crossCleanJets(jetCands35, tauCandsIso40);
    if (jetCands40Size >= 2) jetCands40RmvOlTauCandsIso40 = crossCleanJets(jetCands40, tauCandsIso40);
    if (jetCands45Size >= 2) jetCands45RmvOlTauCandsIso40 = crossCleanJets(jetCands45, tauCandsIso40);
    if (jetCands50Size >= 2) jetCands50RmvOlTauCandsIso40 = crossCleanJets(jetCands50, tauCandsIso40);
    if (jetCands55Size >= 2) jetCands55RmvOlTauCandsIso40 = crossCleanJets(jetCands55, tauCandsIso40);
    if (jetCands60Size >= 2) jetCands60RmvOlTauCandsIso40 = crossCleanJets(jetCands60, tauCandsIso40);
    int jetCands35RmvOlTauCandsIso40Size = jetCands35RmvOlTauCandsIso40.size();
    int jetCands40RmvOlTauCandsIso40Size = jetCands40RmvOlTauCandsIso40.size();
    int jetCands45RmvOlTauCandsIso40Size = jetCands45RmvOlTauCandsIso40.size();
    int jetCands50RmvOlTauCandsIso40Size = jetCands50RmvOlTauCandsIso40.size();
    int jetCands55RmvOlTauCandsIso40Size = jetCands55RmvOlTauCandsIso40.size();
    int jetCands60RmvOlTauCandsIso40Size = jetCands60RmvOlTauCandsIso40.size();

    // isoTau42
    vector<TLorentzVector> jetCands35RmvOlTauCandsIso42;
    vector<TLorentzVector> jetCands40RmvOlTauCandsIso42;
    vector<TLorentzVector> jetCands45RmvOlTauCandsIso42;
    vector<TLorentzVector> jetCands50RmvOlTauCandsIso42;
    vector<TLorentzVector> jetCands55RmvOlTauCandsIso42;
    vector<TLorentzVector> jetCands60RmvOlTauCandsIso42;
    if (jetCands35Size >= 2) jetCands35RmvOlTauCandsIso42 = crossCleanJets(jetCands35, tauCandsIso42);
    if (jetCands40Size >= 2) jetCands40RmvOlTauCandsIso42 = crossCleanJets(jetCands40, tauCandsIso42);
    if (jetCands45Size >= 2) jetCands45RmvOlTauCandsIso42 = crossCleanJets(jetCands45, tauCandsIso42);
    if (jetCands50Size >= 2) jetCands50RmvOlTauCandsIso42 = crossCleanJets(jetCands50, tauCandsIso42);
    if (jetCands55Size >= 2) jetCands55RmvOlTauCandsIso42 = crossCleanJets(jetCands55, tauCandsIso42);
    if (jetCands60Size >= 2) jetCands60RmvOlTauCandsIso42 = crossCleanJets(jetCands60, tauCandsIso42);
    int jetCands35RmvOlTauCandsIso42Size = jetCands35RmvOlTauCandsIso42.size();
    int jetCands40RmvOlTauCandsIso42Size = jetCands40RmvOlTauCandsIso42.size();
    int jetCands45RmvOlTauCandsIso42Size = jetCands45RmvOlTauCandsIso42.size();
    int jetCands50RmvOlTauCandsIso42Size = jetCands50RmvOlTauCandsIso42.size();
    int jetCands55RmvOlTauCandsIso42Size = jetCands55RmvOlTauCandsIso42.size();
    int jetCands60RmvOlTauCandsIso42Size = jetCands60RmvOlTauCandsIso42.size();

    // isoTau44
    vector<TLorentzVector> jetCands35RmvOlTauCandsIso44;
    vector<TLorentzVector> jetCands40RmvOlTauCandsIso44;
    vector<TLorentzVector> jetCands45RmvOlTauCandsIso44;
    vector<TLorentzVector> jetCands50RmvOlTauCandsIso44;
    vector<TLorentzVector> jetCands55RmvOlTauCandsIso44;
    vector<TLorentzVector> jetCands60RmvOlTauCandsIso44;
    if (jetCands35Size >= 2) jetCands35RmvOlTauCandsIso44 = crossCleanJets(jetCands35, tauCandsIso44);
    if (jetCands40Size >= 2) jetCands40RmvOlTauCandsIso44 = crossCleanJets(jetCands40, tauCandsIso44);
    if (jetCands45Size >= 2) jetCands45RmvOlTauCandsIso44 = crossCleanJets(jetCands45, tauCandsIso44);
    if (jetCands50Size >= 2) jetCands50RmvOlTauCandsIso44 = crossCleanJets(jetCands50, tauCandsIso44);
    if (jetCands55Size >= 2) jetCands55RmvOlTauCandsIso44 = crossCleanJets(jetCands55, tauCandsIso44);
    if (jetCands60Size >= 2) jetCands60RmvOlTauCandsIso44 = crossCleanJets(jetCands60, tauCandsIso44);
    int jetCands35RmvOlTauCandsIso44Size = jetCands35RmvOlTauCandsIso44.size();
    int jetCands40RmvOlTauCandsIso44Size = jetCands40RmvOlTauCandsIso44.size();
    int jetCands45RmvOlTauCandsIso44Size = jetCands45RmvOlTauCandsIso44.size();
    int jetCands50RmvOlTauCandsIso44Size = jetCands50RmvOlTauCandsIso44.size();
    int jetCands55RmvOlTauCandsIso44Size = jetCands55RmvOlTauCandsIso44.size();
    int jetCands60RmvOlTauCandsIso44Size = jetCands60RmvOlTauCandsIso44.size();

    // isoTau45
    vector<TLorentzVector> jetCands35RmvOlTauCandsIso45;
    vector<TLorentzVector> jetCands40RmvOlTauCandsIso45;
    vector<TLorentzVector> jetCands45RmvOlTauCandsIso45;
    vector<TLorentzVector> jetCands50RmvOlTauCandsIso45;
    vector<TLorentzVector> jetCands55RmvOlTauCandsIso45;
    vector<TLorentzVector> jetCands60RmvOlTauCandsIso45;
    if (jetCands35Size >= 2) jetCands35RmvOlTauCandsIso45 = crossCleanJets(jetCands35, tauCandsIso45);
    if (jetCands40Size >= 2) jetCands40RmvOlTauCandsIso45 = crossCleanJets(jetCands40, tauCandsIso45);
    if (jetCands45Size >= 2) jetCands45RmvOlTauCandsIso45 = crossCleanJets(jetCands45, tauCandsIso45);
    if (jetCands50Size >= 2) jetCands50RmvOlTauCandsIso45 = crossCleanJets(jetCands50, tauCandsIso45);
    if (jetCands55Size >= 2) jetCands55RmvOlTauCandsIso45 = crossCleanJets(jetCands55, tauCandsIso45);
    if (jetCands60Size >= 2) jetCands60RmvOlTauCandsIso45 = crossCleanJets(jetCands60, tauCandsIso45);
    int jetCands35RmvOlTauCandsIso45Size = jetCands35RmvOlTauCandsIso45.size();
    int jetCands40RmvOlTauCandsIso45Size = jetCands40RmvOlTauCandsIso45.size();
    int jetCands45RmvOlTauCandsIso45Size = jetCands45RmvOlTauCandsIso45.size();
    int jetCands50RmvOlTauCandsIso45Size = jetCands50RmvOlTauCandsIso45.size();
    int jetCands55RmvOlTauCandsIso45Size = jetCands55RmvOlTauCandsIso45.size();
    int jetCands60RmvOlTauCandsIso45Size = jetCands60RmvOlTauCandsIso45.size();

    // isoTau46
    vector<TLorentzVector> jetCands35RmvOlTauCandsIso46;
    vector<TLorentzVector> jetCands40RmvOlTauCandsIso46;
    vector<TLorentzVector> jetCands45RmvOlTauCandsIso46;
    vector<TLorentzVector> jetCands50RmvOlTauCandsIso46;
    vector<TLorentzVector> jetCands55RmvOlTauCandsIso46;
    vector<TLorentzVector> jetCands60RmvOlTauCandsIso46;
    if (jetCands35Size >= 2) jetCands35RmvOlTauCandsIso46 = crossCleanJets(jetCands35, tauCandsIso46);
    if (jetCands40Size >= 2) jetCands40RmvOlTauCandsIso46 = crossCleanJets(jetCands40, tauCandsIso46);
    if (jetCands45Size >= 2) jetCands45RmvOlTauCandsIso46 = crossCleanJets(jetCands45, tauCandsIso46);
    if (jetCands50Size >= 2) jetCands50RmvOlTauCandsIso46 = crossCleanJets(jetCands50, tauCandsIso46);
    if (jetCands55Size >= 2) jetCands55RmvOlTauCandsIso46 = crossCleanJets(jetCands55, tauCandsIso46);
    if (jetCands60Size >= 2) jetCands60RmvOlTauCandsIso46 = crossCleanJets(jetCands60, tauCandsIso46);
    int jetCands35RmvOlTauCandsIso46Size = jetCands35RmvOlTauCandsIso46.size();
    int jetCands40RmvOlTauCandsIso46Size = jetCands40RmvOlTauCandsIso46.size();
    int jetCands45RmvOlTauCandsIso46Size = jetCands45RmvOlTauCandsIso46.size();
    int jetCands50RmvOlTauCandsIso46Size = jetCands50RmvOlTauCandsIso46.size();
    int jetCands55RmvOlTauCandsIso46Size = jetCands55RmvOlTauCandsIso46.size();
    int jetCands60RmvOlTauCandsIso46Size = jetCands60RmvOlTauCandsIso46.size();

    // isoTau48
    vector<TLorentzVector> jetCands35RmvOlTauCandsIso48;
    vector<TLorentzVector> jetCands40RmvOlTauCandsIso48;
    vector<TLorentzVector> jetCands45RmvOlTauCandsIso48;
    vector<TLorentzVector> jetCands50RmvOlTauCandsIso48;
    vector<TLorentzVector> jetCands55RmvOlTauCandsIso48;
    vector<TLorentzVector> jetCands60RmvOlTauCandsIso48;
    if (jetCands35Size >= 2) jetCands35RmvOlTauCandsIso48 = crossCleanJets(jetCands35, tauCandsIso48);
    if (jetCands40Size >= 2) jetCands40RmvOlTauCandsIso48 = crossCleanJets(jetCands40, tauCandsIso48);
    if (jetCands45Size >= 2) jetCands45RmvOlTauCandsIso48 = crossCleanJets(jetCands45, tauCandsIso48);
    if (jetCands50Size >= 2) jetCands50RmvOlTauCandsIso48 = crossCleanJets(jetCands50, tauCandsIso48);
    if (jetCands55Size >= 2) jetCands55RmvOlTauCandsIso48 = crossCleanJets(jetCands55, tauCandsIso48);
    if (jetCands60Size >= 2) jetCands60RmvOlTauCandsIso48 = crossCleanJets(jetCands60, tauCandsIso48);
    int jetCands35RmvOlTauCandsIso48Size = jetCands35RmvOlTauCandsIso48.size();
    int jetCands40RmvOlTauCandsIso48Size = jetCands40RmvOlTauCandsIso48.size();
    int jetCands45RmvOlTauCandsIso48Size = jetCands45RmvOlTauCandsIso48.size();
    int jetCands50RmvOlTauCandsIso48Size = jetCands50RmvOlTauCandsIso48.size();
    int jetCands55RmvOlTauCandsIso48Size = jetCands55RmvOlTauCandsIso48.size();
    int jetCands60RmvOlTauCandsIso48Size = jetCands60RmvOlTauCandsIso48.size();

    // isoTau50
    vector<TLorentzVector> jetCands35RmvOlTauCandsIso50;
    vector<TLorentzVector> jetCands40RmvOlTauCandsIso50;
    vector<TLorentzVector> jetCands45RmvOlTauCandsIso50; 
    vector<TLorentzVector> jetCands50RmvOlTauCandsIso50; 
    vector<TLorentzVector> jetCands55RmvOlTauCandsIso50; 
    vector<TLorentzVector> jetCands60RmvOlTauCandsIso50; 
    if (jetCands35Size >= 2) jetCands35RmvOlTauCandsIso50 = crossCleanJets(jetCands35, tauCandsIso50);
    if (jetCands40Size >= 2) jetCands40RmvOlTauCandsIso50 = crossCleanJets(jetCands40, tauCandsIso50);
    if (jetCands45Size >= 2) jetCands45RmvOlTauCandsIso50 = crossCleanJets(jetCands45, tauCandsIso50);
    if (jetCands50Size >= 2) jetCands50RmvOlTauCandsIso50 = crossCleanJets(jetCands50, tauCandsIso50);
    if (jetCands55Size >= 2) jetCands55RmvOlTauCandsIso50 = crossCleanJets(jetCands55, tauCandsIso50);
    if (jetCands60Size >= 2) jetCands60RmvOlTauCandsIso50 = crossCleanJets(jetCands60, tauCandsIso50);
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
    if (jetCands35Size >= 2) jetCands35RmvOlTauCandsIso55 = crossCleanJets(jetCands35, tauCandsIso55);
    if (jetCands40Size >= 2) jetCands40RmvOlTauCandsIso55 = crossCleanJets(jetCands40, tauCandsIso55);
    if (jetCands45Size >= 2) jetCands45RmvOlTauCandsIso55 = crossCleanJets(jetCands45, tauCandsIso55);
    if (jetCands50Size >= 2) jetCands50RmvOlTauCandsIso55 = crossCleanJets(jetCands50, tauCandsIso55);
    if (jetCands55Size >= 2) jetCands55RmvOlTauCandsIso55 = crossCleanJets(jetCands55, tauCandsIso55);
    if (jetCands60Size >= 2) jetCands60RmvOlTauCandsIso55 = crossCleanJets(jetCands60, tauCandsIso55);
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
    if (jetCands35Size >= 2) jetCands35RmvOlTauCandsIso60 = crossCleanJets(jetCands35, tauCandsIso60);
    if (jetCands40Size >= 2) jetCands40RmvOlTauCandsIso60 = crossCleanJets(jetCands40, tauCandsIso60);
    if (jetCands45Size >= 2) jetCands45RmvOlTauCandsIso60 = crossCleanJets(jetCands45, tauCandsIso60);
    if (jetCands50Size >= 2) jetCands50RmvOlTauCandsIso60 = crossCleanJets(jetCands50, tauCandsIso60);
    if (jetCands55Size >= 2) jetCands55RmvOlTauCandsIso60 = crossCleanJets(jetCands55, tauCandsIso60);
    if (jetCands60Size >= 2) jetCands60RmvOlTauCandsIso60 = crossCleanJets(jetCands60, tauCandsIso60);
    int jetCands35RmvOlTauCandsIso60Size = jetCands35RmvOlTauCandsIso60.size();
    int jetCands40RmvOlTauCandsIso60Size = jetCands40RmvOlTauCandsIso60.size();
    int jetCands45RmvOlTauCandsIso60Size = jetCands45RmvOlTauCandsIso60.size();
    int jetCands50RmvOlTauCandsIso60Size = jetCands50RmvOlTauCandsIso60.size();
    int jetCands55RmvOlTauCandsIso60Size = jetCands55RmvOlTauCandsIso60.size();
    int jetCands60RmvOlTauCandsIso60Size = jetCands60RmvOlTauCandsIso60.size();

    //extras
    //vector<TLorentzVector> jetCands35RmvOlTauCandsIso45;
    //vector<TLorentzVector> jetCands35RmvOlTauCandsIso38;
    vector<TLorentzVector> jetCands40RmvOlTauCandsIso28;
    vector<TLorentzVector> jetCands45RmvOlTauCandsIso28;
    vector<TLorentzVector> jetCands50RmvOlTauCandsIso28;
    //vector<TLorentzVector> jetCands50RmvOlTauCandsIso25;
    if (jetCands40Size >= 2) jetCands40RmvOlTauCandsIso28 = crossCleanJets(jetCands40, tauCandsIso28);
    if (jetCands45Size >= 2) jetCands45RmvOlTauCandsIso28 = crossCleanJets(jetCands45, tauCandsIso28);
    if (jetCands50Size >= 2) jetCands50RmvOlTauCandsIso28 = crossCleanJets(jetCands50, tauCandsIso28);
    int jetCands40RmvOlTauCandsIso28Size = jetCands40RmvOlTauCandsIso28.size();
    int jetCands45RmvOlTauCandsIso28Size = jetCands45RmvOlTauCandsIso28.size();
    int jetCands50RmvOlTauCandsIso28Size = jetCands50RmvOlTauCandsIso28.size();

    // end containers for seed 2 variations
     
    // odd duckling for seed 3
    vector<TLorentzVector> jetCands35RmvOlTauCands35;
    if (jetCands35Size >= 2) jetCands35RmvOlTauCands35 = crossCleanJets(jetCands35, tauCands35);
    int jetCands35RmvOlTauCands35Size = jetCands35RmvOlTauCands35.size();

    //------------------------finished making containers, now checking obj numbers and masses and passing triggers----------------------//
 
    // small counting "study" to see the number of different types of events passing size reqs
    /***
    if ((jetCands35Size + tauCandsIso45Size) >= 3 && tauCandsIso45Size >= 1) {
      int output_value = jetCands35Size*100 + tauCandsIso45Size*10 + jetCands35RmvOlTauCandsIso45Size;
      fprintf(out_file, " %d ", output_value);
    }***/
    

    // ManfredLogic testing
    if (jetCands35Size >= 2 && tauCandsIso45Size >= 1) {
      passManfredLogic = ManfredLogic(jetCands35, tauCandsIso45);
    }

  
    // L1_DoubleIsoTau32er2p1
    if (tauCandsIso32Size >= 2) passDiTau = 1;
    //if (tauCandsIso35Size >= 2) passDiTau = 1;

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

    // L1_TripleJet35_IsoTau45_Mass_Min400 (Note how there is no rmvol) seed idea from Andrew B
    if (jetCands35Size >= 3 && tauCandsIso45Size >= 1) {
      float mjj_threeJets = 0; float tempMjj_ = 0;
      for (int iJet = 0; iJet < jetCands35Size; ++iJet) {
        for (int jJet = 0; jJet < jetCands35Size; ++jJet) {
          if (iJet >= jJet) continue;
          tempMjj_ = (jetCands35.at(iJet) + jetCands35.at(jJet)).M();
          if (tempMjj_ > mjj_threeJets) mjj_threeJets = tempMjj_;
        }
      }
      if (mjj_threeJets >= 400) passTripJets = 1;
    }

  //------------------------------seed 2 varying cuts-----------------------//
  //
  if (tauCandsIso25Size >= 1) {
    if (jetCands35RmvOlTauCandsIso25Size >= 2) setArrayElements(passSeed2_3525All, highestMassOfPair(jetCands35RmvOlTauCandsIso25, tauCandsIso25), mjjCuts);

    if (jetCands40RmvOlTauCandsIso25Size >= 2) setArrayElements(passSeed2_4025All, highestMassOfPair(jetCands40RmvOlTauCandsIso25, tauCandsIso25), mjjCuts);

    if (jetCands45RmvOlTauCandsIso25Size >= 2) setArrayElements(passSeed2_4525All, highestMassOfPair(jetCands45RmvOlTauCandsIso25, tauCandsIso25), mjjCuts);

    if (jetCands50RmvOlTauCandsIso25Size >= 2) setArrayElements(passSeed2_5025All, highestMassOfPair(jetCands50RmvOlTauCandsIso25, tauCandsIso25), mjjCuts);

    if (jetCands55RmvOlTauCandsIso25Size >= 2) setArrayElements(passSeed2_5525All, highestMassOfPair(jetCands55RmvOlTauCandsIso25, tauCandsIso25), mjjCuts);

    if (jetCands60RmvOlTauCandsIso25Size >= 2) setArrayElements(passSeed2_6025All, highestMassOfPair(jetCands60RmvOlTauCandsIso25, tauCandsIso25), mjjCuts);
  }
 
  if (tauCandsIso30Size >= 1) {
    if (jetCands35RmvOlTauCandsIso30Size >= 2) setArrayElements(passSeed2_3530All, highestMassOfPair(jetCands35RmvOlTauCandsIso30, tauCandsIso30), mjjCuts);

    if (jetCands40RmvOlTauCandsIso30Size >= 2) setArrayElements(passSeed2_4030All, highestMassOfPair(jetCands40RmvOlTauCandsIso30, tauCandsIso30), mjjCuts);

    if (jetCands45RmvOlTauCandsIso30Size >= 2) setArrayElements(passSeed2_4530All, highestMassOfPair(jetCands45RmvOlTauCandsIso30, tauCandsIso30), mjjCuts);

    if (jetCands50RmvOlTauCandsIso30Size >= 2) setArrayElements(passSeed2_5030All, highestMassOfPair(jetCands50RmvOlTauCandsIso30, tauCandsIso30), mjjCuts);

    if (jetCands55RmvOlTauCandsIso30Size >= 2) setArrayElements(passSeed2_5530All, highestMassOfPair(jetCands55RmvOlTauCandsIso30, tauCandsIso30), mjjCuts);

    if (jetCands60RmvOlTauCandsIso30Size >= 2) setArrayElements(passSeed2_6030All, highestMassOfPair(jetCands60RmvOlTauCandsIso30, tauCandsIso30), mjjCuts);
  }

  if (tauCandsIso32Size >= 1) {
    if (jetCands35RmvOlTauCandsIso32Size >= 2) setArrayElements(passSeed2_3532All, highestMassOfPair(jetCands35RmvOlTauCandsIso32, tauCandsIso32), mjjCuts);

    if (jetCands40RmvOlTauCandsIso32Size >= 2) setArrayElements(passSeed2_4032All, highestMassOfPair(jetCands40RmvOlTauCandsIso32, tauCandsIso32), mjjCuts);

    if (jetCands45RmvOlTauCandsIso32Size >= 2) setArrayElements(passSeed2_4532All, highestMassOfPair(jetCands45RmvOlTauCandsIso32, tauCandsIso32), mjjCuts);

    if (jetCands50RmvOlTauCandsIso32Size >= 2) setArrayElements(passSeed2_5032All, highestMassOfPair(jetCands50RmvOlTauCandsIso32, tauCandsIso32), mjjCuts);

    if (jetCands55RmvOlTauCandsIso32Size >= 2) setArrayElements(passSeed2_5532All, highestMassOfPair(jetCands55RmvOlTauCandsIso32, tauCandsIso32), mjjCuts);

    if (jetCands60RmvOlTauCandsIso32Size >= 2) setArrayElements(passSeed2_6032All, highestMassOfPair(jetCands60RmvOlTauCandsIso32, tauCandsIso32), mjjCuts);
  }

  if (tauCandsIso34Size >= 1) {
    if (jetCands35RmvOlTauCandsIso34Size >= 2) setArrayElements(passSeed2_3534All, highestMassOfPair(jetCands35RmvOlTauCandsIso34, tauCandsIso34), mjjCuts);

    if (jetCands40RmvOlTauCandsIso34Size >= 2) setArrayElements(passSeed2_4034All, highestMassOfPair(jetCands40RmvOlTauCandsIso34, tauCandsIso34), mjjCuts);

    if (jetCands45RmvOlTauCandsIso34Size >= 2) setArrayElements(passSeed2_4534All, highestMassOfPair(jetCands45RmvOlTauCandsIso34, tauCandsIso34), mjjCuts);

    if (jetCands50RmvOlTauCandsIso34Size >= 2) setArrayElements(passSeed2_5034All, highestMassOfPair(jetCands50RmvOlTauCandsIso34, tauCandsIso34), mjjCuts);

    if (jetCands55RmvOlTauCandsIso34Size >= 2) setArrayElements(passSeed2_5534All, highestMassOfPair(jetCands55RmvOlTauCandsIso34, tauCandsIso34), mjjCuts);

    if (jetCands60RmvOlTauCandsIso34Size >= 2) setArrayElements(passSeed2_6034All, highestMassOfPair(jetCands60RmvOlTauCandsIso34, tauCandsIso34), mjjCuts);
  }

  if (tauCandsIso35Size >= 1) {
    if (jetCands35RmvOlTauCandsIso35Size >= 2) setArrayElements(passSeed2_3535All, highestMassOfPair(jetCands35RmvOlTauCandsIso35, tauCandsIso35), mjjCuts);

    if (jetCands40RmvOlTauCandsIso35Size >= 2) setArrayElements(passSeed2_4035All, highestMassOfPair(jetCands40RmvOlTauCandsIso35, tauCandsIso35), mjjCuts);

    if (jetCands45RmvOlTauCandsIso35Size >= 2) setArrayElements(passSeed2_4535All, highestMassOfPair(jetCands45RmvOlTauCandsIso35, tauCandsIso35), mjjCuts);

    if (jetCands50RmvOlTauCandsIso35Size >= 2) setArrayElements(passSeed2_5035All, highestMassOfPair(jetCands50RmvOlTauCandsIso35, tauCandsIso35), mjjCuts);

    if (jetCands55RmvOlTauCandsIso35Size >= 2) setArrayElements(passSeed2_5535All, highestMassOfPair(jetCands55RmvOlTauCandsIso35, tauCandsIso35), mjjCuts);

    if (jetCands60RmvOlTauCandsIso35Size >= 2) setArrayElements(passSeed2_6035All, highestMassOfPair(jetCands60RmvOlTauCandsIso35, tauCandsIso35), mjjCuts);
  }

  if (tauCandsIso36Size >= 1) {
    if (jetCands35RmvOlTauCandsIso36Size >= 2) setArrayElements(passSeed2_3536All, highestMassOfPair(jetCands35RmvOlTauCandsIso36, tauCandsIso36), mjjCuts);

    if (jetCands40RmvOlTauCandsIso36Size >= 2) setArrayElements(passSeed2_4036All, highestMassOfPair(jetCands40RmvOlTauCandsIso36, tauCandsIso36), mjjCuts);

    if (jetCands45RmvOlTauCandsIso36Size >= 2) setArrayElements(passSeed2_4536All, highestMassOfPair(jetCands45RmvOlTauCandsIso36, tauCandsIso36), mjjCuts);

    if (jetCands50RmvOlTauCandsIso36Size >= 2) setArrayElements(passSeed2_5036All, highestMassOfPair(jetCands50RmvOlTauCandsIso36, tauCandsIso36), mjjCuts);

    if (jetCands55RmvOlTauCandsIso36Size >= 2) setArrayElements(passSeed2_5536All, highestMassOfPair(jetCands55RmvOlTauCandsIso36, tauCandsIso36), mjjCuts);

    if (jetCands60RmvOlTauCandsIso36Size >= 2) setArrayElements(passSeed2_6036All, highestMassOfPair(jetCands60RmvOlTauCandsIso36, tauCandsIso36), mjjCuts);
  }

  if (tauCandsIso38Size >= 1) {
    if (jetCands35RmvOlTauCandsIso38Size >= 2) setArrayElements(passSeed2_3538All, highestMassOfPair(jetCands35RmvOlTauCandsIso38, tauCandsIso38), mjjCuts);

    if (jetCands40RmvOlTauCandsIso38Size >= 2) setArrayElements(passSeed2_4038All, highestMassOfPair(jetCands40RmvOlTauCandsIso38, tauCandsIso38), mjjCuts);

    if (jetCands45RmvOlTauCandsIso38Size >= 2) setArrayElements(passSeed2_4538All, highestMassOfPair(jetCands45RmvOlTauCandsIso38, tauCandsIso38), mjjCuts);

    if (jetCands50RmvOlTauCandsIso38Size >= 2) setArrayElements(passSeed2_5038All, highestMassOfPair(jetCands50RmvOlTauCandsIso38, tauCandsIso38), mjjCuts);

    if (jetCands55RmvOlTauCandsIso38Size >= 2) setArrayElements(passSeed2_5538All, highestMassOfPair(jetCands55RmvOlTauCandsIso38, tauCandsIso38), mjjCuts);

    if (jetCands60RmvOlTauCandsIso38Size >= 2) setArrayElements(passSeed2_6038All, highestMassOfPair(jetCands60RmvOlTauCandsIso38, tauCandsIso38), mjjCuts);
  }

  if (tauCandsIso40Size >= 1) {
    if (jetCands35RmvOlTauCandsIso40Size >= 2) setArrayElements(passSeed2_3540All, highestMassOfPair(jetCands35RmvOlTauCandsIso40, tauCandsIso40), mjjCuts);

    if (jetCands40RmvOlTauCandsIso40Size >= 2) setArrayElements(passSeed2_4040All, highestMassOfPair(jetCands40RmvOlTauCandsIso40, tauCandsIso40), mjjCuts);

    if (jetCands45RmvOlTauCandsIso40Size >= 2) setArrayElements(passSeed2_4540All, highestMassOfPair(jetCands45RmvOlTauCandsIso40, tauCandsIso40), mjjCuts);

    if (jetCands50RmvOlTauCandsIso40Size >= 2) setArrayElements(passSeed2_5040All, highestMassOfPair(jetCands50RmvOlTauCandsIso40, tauCandsIso40), mjjCuts);

    if (jetCands55RmvOlTauCandsIso40Size >= 2) setArrayElements(passSeed2_5540All, highestMassOfPair(jetCands55RmvOlTauCandsIso40, tauCandsIso40), mjjCuts);

    if (jetCands60RmvOlTauCandsIso40Size >= 2) setArrayElements(passSeed2_6040All, highestMassOfPair(jetCands60RmvOlTauCandsIso40, tauCandsIso40), mjjCuts);
  }

  if (tauCandsIso42Size >= 1) {
    if (jetCands35RmvOlTauCandsIso42Size >= 2) setArrayElements(passSeed2_3542All, highestMassOfPair(jetCands35RmvOlTauCandsIso42, tauCandsIso42), mjjCuts);

    if (jetCands40RmvOlTauCandsIso42Size >= 2) setArrayElements(passSeed2_4042All, highestMassOfPair(jetCands40RmvOlTauCandsIso42, tauCandsIso42), mjjCuts);

    if (jetCands45RmvOlTauCandsIso42Size >= 2) setArrayElements(passSeed2_4542All, highestMassOfPair(jetCands45RmvOlTauCandsIso42, tauCandsIso42), mjjCuts);

    if (jetCands50RmvOlTauCandsIso42Size >= 2) setArrayElements(passSeed2_5042All, highestMassOfPair(jetCands50RmvOlTauCandsIso42, tauCandsIso42), mjjCuts);

    if (jetCands55RmvOlTauCandsIso42Size >= 2) setArrayElements(passSeed2_5542All, highestMassOfPair(jetCands55RmvOlTauCandsIso42, tauCandsIso42), mjjCuts);

    if (jetCands60RmvOlTauCandsIso42Size >= 2) setArrayElements(passSeed2_6042All, highestMassOfPair(jetCands60RmvOlTauCandsIso42, tauCandsIso42), mjjCuts);
  }


  if (tauCandsIso44Size >= 1) {
    if (jetCands35RmvOlTauCandsIso44Size >= 2) setArrayElements(passSeed2_3544All, highestMassOfPair(jetCands35RmvOlTauCandsIso44, tauCandsIso44), mjjCuts);

    if (jetCands40RmvOlTauCandsIso44Size >= 2) setArrayElements(passSeed2_4044All, highestMassOfPair(jetCands40RmvOlTauCandsIso44, tauCandsIso44), mjjCuts);

    if (jetCands45RmvOlTauCandsIso44Size >= 2) setArrayElements(passSeed2_4544All, highestMassOfPair(jetCands45RmvOlTauCandsIso44, tauCandsIso44), mjjCuts);

    if (jetCands50RmvOlTauCandsIso44Size >= 2) setArrayElements(passSeed2_5044All, highestMassOfPair(jetCands50RmvOlTauCandsIso44, tauCandsIso44), mjjCuts);

    if (jetCands55RmvOlTauCandsIso44Size >= 2) setArrayElements(passSeed2_5544All, highestMassOfPair(jetCands55RmvOlTauCandsIso44, tauCandsIso44), mjjCuts);

    if (jetCands60RmvOlTauCandsIso44Size >= 2) setArrayElements(passSeed2_6044All, highestMassOfPair(jetCands60RmvOlTauCandsIso44, tauCandsIso44), mjjCuts);
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


  if (tauCandsIso46Size >= 1) {
    if (jetCands35RmvOlTauCandsIso46Size >= 2) setArrayElements(passSeed2_3546All, highestMassOfPair(jetCands35RmvOlTauCandsIso46, tauCandsIso46), mjjCuts);

    if (jetCands40RmvOlTauCandsIso46Size >= 2) setArrayElements(passSeed2_4046All, highestMassOfPair(jetCands40RmvOlTauCandsIso46, tauCandsIso46), mjjCuts);

    if (jetCands45RmvOlTauCandsIso46Size >= 2) setArrayElements(passSeed2_4546All, highestMassOfPair(jetCands45RmvOlTauCandsIso46, tauCandsIso46), mjjCuts);

    if (jetCands50RmvOlTauCandsIso46Size >= 2) setArrayElements(passSeed2_5046All, highestMassOfPair(jetCands50RmvOlTauCandsIso46, tauCandsIso46), mjjCuts);

    if (jetCands55RmvOlTauCandsIso46Size >= 2) setArrayElements(passSeed2_5546All, highestMassOfPair(jetCands55RmvOlTauCandsIso46, tauCandsIso46), mjjCuts);

    if (jetCands60RmvOlTauCandsIso46Size >= 2) setArrayElements(passSeed2_6046All, highestMassOfPair(jetCands60RmvOlTauCandsIso46, tauCandsIso46), mjjCuts);
  }

  if (tauCandsIso48Size >= 1) {
    if (jetCands35RmvOlTauCandsIso48Size >= 2) setArrayElements(passSeed2_3548All, highestMassOfPair(jetCands35RmvOlTauCandsIso48, tauCandsIso48), mjjCuts);

    if (jetCands40RmvOlTauCandsIso48Size >= 2) setArrayElements(passSeed2_4048All, highestMassOfPair(jetCands40RmvOlTauCandsIso48, tauCandsIso48), mjjCuts);

    if (jetCands45RmvOlTauCandsIso48Size >= 2) setArrayElements(passSeed2_4548All, highestMassOfPair(jetCands45RmvOlTauCandsIso48, tauCandsIso48), mjjCuts);

    if (jetCands50RmvOlTauCandsIso48Size >= 2) setArrayElements(passSeed2_5048All, highestMassOfPair(jetCands50RmvOlTauCandsIso48, tauCandsIso48), mjjCuts);

    if (jetCands55RmvOlTauCandsIso48Size >= 2) setArrayElements(passSeed2_5548All, highestMassOfPair(jetCands55RmvOlTauCandsIso48, tauCandsIso48), mjjCuts);

    if (jetCands60RmvOlTauCandsIso48Size >= 2) setArrayElements(passSeed2_6048All, highestMassOfPair(jetCands60RmvOlTauCandsIso48, tauCandsIso48), mjjCuts);
  }


  if (tauCandsIso50Size >= 1) {
    if (jetCands35RmvOlTauCandsIso50Size >= 2) setArrayElements(passSeed2_3550All, highestMassOfPair(jetCands35RmvOlTauCandsIso50, tauCandsIso50), mjjCuts);

    if (jetCands40RmvOlTauCandsIso50Size >= 2) setArrayElements(passSeed2_4050All, highestMassOfPair(jetCands40RmvOlTauCandsIso50, tauCandsIso50), mjjCuts);

    if (jetCands45RmvOlTauCandsIso50Size >= 2) setArrayElements(passSeed2_4550All, highestMassOfPair(jetCands45RmvOlTauCandsIso50, tauCandsIso50), mjjCuts);

    if (jetCands50RmvOlTauCandsIso50Size >= 2) setArrayElements(passSeed2_5050All, highestMassOfPair(jetCands50RmvOlTauCandsIso50, tauCandsIso50), mjjCuts);

    if (jetCands55RmvOlTauCandsIso50Size >= 2) setArrayElements(passSeed2_5550All, highestMassOfPair(jetCands55RmvOlTauCandsIso50, tauCandsIso50), mjjCuts);

    if (jetCands60RmvOlTauCandsIso50Size >= 2) setArrayElements(passSeed2_6050All, highestMassOfPair(jetCands60RmvOlTauCandsIso50, tauCandsIso50), mjjCuts);
  }

  if (tauCandsIso55Size >= 1) {
    if (jetCands35RmvOlTauCandsIso55Size >= 2) setArrayElements(passSeed2_3555All, highestMassOfPair(jetCands35RmvOlTauCandsIso55, tauCandsIso55), mjjCuts);

    if (jetCands40RmvOlTauCandsIso55Size >= 2) setArrayElements(passSeed2_4055All, highestMassOfPair(jetCands40RmvOlTauCandsIso55, tauCandsIso55), mjjCuts);

    if (jetCands45RmvOlTauCandsIso55Size >= 2) setArrayElements(passSeed2_4555All, highestMassOfPair(jetCands45RmvOlTauCandsIso55, tauCandsIso55), mjjCuts);

    if (jetCands50RmvOlTauCandsIso55Size >= 2) setArrayElements(passSeed2_5055All, highestMassOfPair(jetCands50RmvOlTauCandsIso55, tauCandsIso55), mjjCuts);

    if (jetCands55RmvOlTauCandsIso55Size >= 2) setArrayElements(passSeed2_5555All, highestMassOfPair(jetCands55RmvOlTauCandsIso55, tauCandsIso55), mjjCuts);

    if (jetCands60RmvOlTauCandsIso55Size >= 2) setArrayElements(passSeed2_6055All, highestMassOfPair(jetCands60RmvOlTauCandsIso55, tauCandsIso55), mjjCuts);
  }

  if (tauCandsIso60Size >= 1) {
    if (jetCands35RmvOlTauCandsIso60Size >= 2) setArrayElements(passSeed2_3560All, highestMassOfPair(jetCands35RmvOlTauCandsIso60, tauCandsIso60), mjjCuts);

    if (jetCands40RmvOlTauCandsIso60Size >= 2) setArrayElements(passSeed2_4060All, highestMassOfPair(jetCands40RmvOlTauCandsIso60, tauCandsIso60), mjjCuts);

    if (jetCands45RmvOlTauCandsIso60Size >= 2) setArrayElements(passSeed2_4560All, highestMassOfPair(jetCands45RmvOlTauCandsIso60, tauCandsIso60), mjjCuts);

    if (jetCands50RmvOlTauCandsIso60Size >= 2) setArrayElements(passSeed2_5060All, highestMassOfPair(jetCands50RmvOlTauCandsIso60, tauCandsIso60), mjjCuts);

    if (jetCands55RmvOlTauCandsIso60Size >= 2) setArrayElements(passSeed2_5560All, highestMassOfPair(jetCands55RmvOlTauCandsIso60, tauCandsIso60), mjjCuts);

    if (jetCands60RmvOlTauCandsIso60Size >= 2) setArrayElements(passSeed2_6060All, highestMassOfPair(jetCands60RmvOlTauCandsIso60, tauCandsIso60), mjjCuts);
  }

  // extras
  if (tauCandsIso45Size >= 1) {
    if (jetCands35RmvOlTauCandsIso45Size >= 2) setArrayElements(passSeed2_3545400All, highestMassOfPair(jetCands35RmvOlTauCandsIso45, tauCandsIso45), mjjCuts);
  }

  if (tauCandsIso38Size >= 1) {
    if (jetCands35RmvOlTauCandsIso38Size >= 2) setArrayElements(passSeed2_3538500All, highestMassOfPair(jetCands35RmvOlTauCandsIso38, tauCandsIso38), mjjCuts);
  }

  if (tauCandsIso28Size >= 1) {
    if (jetCands40RmvOlTauCandsIso28Size >= 2) setArrayElements(passSeed2_4028600All, highestMassOfPair(jetCands40RmvOlTauCandsIso28, tauCandsIso28), mjjCuts);
    if (jetCands45RmvOlTauCandsIso28Size >= 2) setArrayElements(passSeed2_4528450All, highestMassOfPair(jetCands45RmvOlTauCandsIso28, tauCandsIso28), mjjCuts);
    if (jetCands50RmvOlTauCandsIso28Size >= 2) setArrayElements(passSeed2_5028400All, highestMassOfPair(jetCands50RmvOlTauCandsIso28, tauCandsIso28), mjjCuts);
  }

  if (tauCandsIso25Size >= 1) {
    if (jetCands50RmvOlTauCandsIso25Size >= 2) setArrayElements(passSeed2_5025450All, highestMassOfPair(jetCands50RmvOlTauCandsIso25, tauCandsIso25), mjjCuts);
  }
   

  // counting up events for output

  passDiTauCount += passDiTau;
  passOldCount += passOld;
  passNewCount += passNew;
  passSeed1Count += passSeed1;
  passSeed2Count += passSeed2_3545All[1];
  passSeed3Count += passSeed3;

  // variable for testing/using one specific seed and doing overlap removal by hand in a way that's
  // consistent with overlap removal for New VBF and Manfred Logic
  passSeed2Testing = passSeed2_3545All[2]; //DoubleJet35_IsoTau45_MassAnyTwo450_RmvOl;

  // variations of seed 2
  for (int i = 0; i<6; ++i) {
    if (!passDiTau && !passOld) {
    passSeed2_3525All_count[i] += passSeed2_3525All[i];
    passSeed2_3530All_count[i] += passSeed2_3530All[i];
    passSeed2_3532All_count[i] += passSeed2_3532All[i];
    passSeed2_3534All_count[i] += passSeed2_3534All[i];
    passSeed2_3535All_count[i] += passSeed2_3535All[i];
    passSeed2_3536All_count[i] += passSeed2_3536All[i];
    passSeed2_3538All_count[i] += passSeed2_3538All[i];
    passSeed2_3540All_count[i] += passSeed2_3540All[i];
    passSeed2_3542All_count[i] += passSeed2_3542All[i];
    passSeed2_3544All_count[i] += passSeed2_3544All[i];
    passSeed2_3545All_count[i] += passSeed2_3545All[i];
    passSeed2_3546All_count[i] += passSeed2_3546All[i];
    passSeed2_3548All_count[i] += passSeed2_3548All[i];
    passSeed2_3550All_count[i] += passSeed2_3550All[i];
    passSeed2_3555All_count[i] += passSeed2_3555All[i];
    passSeed2_3560All_count[i] += passSeed2_3560All[i];

    passSeed2_4025All_count[i] += passSeed2_4025All[i];
    passSeed2_4030All_count[i] += passSeed2_4030All[i];
    passSeed2_4032All_count[i] += passSeed2_4032All[i];
    passSeed2_4034All_count[i] += passSeed2_4034All[i];
    passSeed2_4035All_count[i] += passSeed2_4035All[i];
    passSeed2_4036All_count[i] += passSeed2_4036All[i];
    passSeed2_4038All_count[i] += passSeed2_4038All[i];
    passSeed2_4040All_count[i] += passSeed2_4040All[i];
    passSeed2_4042All_count[i] += passSeed2_4042All[i];
    passSeed2_4044All_count[i] += passSeed2_4044All[i];
    passSeed2_4045All_count[i] += passSeed2_4045All[i];
    passSeed2_4046All_count[i] += passSeed2_4046All[i];
    passSeed2_4048All_count[i] += passSeed2_4048All[i];
    passSeed2_4050All_count[i] += passSeed2_4050All[i];
    passSeed2_4055All_count[i] += passSeed2_4055All[i];
    passSeed2_4060All_count[i] += passSeed2_4060All[i];

    passSeed2_4525All_count[i] += passSeed2_4525All[i];
    passSeed2_4530All_count[i] += passSeed2_4530All[i];
    passSeed2_4532All_count[i] += passSeed2_4532All[i];
    passSeed2_4534All_count[i] += passSeed2_4534All[i];
    passSeed2_4535All_count[i] += passSeed2_4535All[i];
    passSeed2_4536All_count[i] += passSeed2_4536All[i];
    passSeed2_4538All_count[i] += passSeed2_4538All[i];
    passSeed2_4540All_count[i] += passSeed2_4540All[i];
    passSeed2_4542All_count[i] += passSeed2_4542All[i];
    passSeed2_4544All_count[i] += passSeed2_4544All[i];
    passSeed2_4545All_count[i] += passSeed2_4545All[i];
    passSeed2_4546All_count[i] += passSeed2_4546All[i];
    passSeed2_4548All_count[i] += passSeed2_4548All[i];
    passSeed2_4550All_count[i] += passSeed2_4550All[i];
    passSeed2_4555All_count[i] += passSeed2_4555All[i];
    passSeed2_4560All_count[i] += passSeed2_4560All[i];

    passSeed2_5025All_count[i] += passSeed2_5025All[i];
    passSeed2_5030All_count[i] += passSeed2_5030All[i];
    passSeed2_5032All_count[i] += passSeed2_5032All[i];
    passSeed2_5034All_count[i] += passSeed2_5034All[i];
    passSeed2_5035All_count[i] += passSeed2_5035All[i];
    passSeed2_5036All_count[i] += passSeed2_5036All[i];
    passSeed2_5038All_count[i] += passSeed2_5038All[i];
    passSeed2_5040All_count[i] += passSeed2_5040All[i];
    passSeed2_5042All_count[i] += passSeed2_5042All[i];
    passSeed2_5044All_count[i] += passSeed2_5044All[i];
    passSeed2_5045All_count[i] += passSeed2_5045All[i];
    passSeed2_5046All_count[i] += passSeed2_5046All[i];
    passSeed2_5048All_count[i] += passSeed2_5048All[i];
    passSeed2_5050All_count[i] += passSeed2_5050All[i];
    passSeed2_5055All_count[i] += passSeed2_5055All[i];
    passSeed2_5060All_count[i] += passSeed2_5060All[i];


    // 55 and 60 jets dont need finer granularity for now
    passSeed2_5525All_count[i] += passSeed2_5525All[i];
    passSeed2_5530All_count[i] += passSeed2_5530All[i];
    passSeed2_5532All_count[i] += passSeed2_5532All[i];
    passSeed2_5534All_count[i] += passSeed2_5534All[i];
    passSeed2_5535All_count[i] += passSeed2_5535All[i];
    passSeed2_5536All_count[i] += passSeed2_5536All[i];
    passSeed2_5538All_count[i] += passSeed2_5538All[i];
    passSeed2_5540All_count[i] += passSeed2_5540All[i];
    passSeed2_5542All_count[i] += passSeed2_5542All[i];
    passSeed2_5544All_count[i] += passSeed2_5544All[i];
    passSeed2_5545All_count[i] += passSeed2_5545All[i];
    passSeed2_5546All_count[i] += passSeed2_5546All[i];
    passSeed2_5548All_count[i] += passSeed2_5548All[i];
    passSeed2_5550All_count[i] += passSeed2_5550All[i];
    passSeed2_5555All_count[i] += passSeed2_5555All[i];
    passSeed2_5560All_count[i] += passSeed2_5560All[i];

    passSeed2_6025All_count[i] += passSeed2_6025All[i];
    passSeed2_6030All_count[i] += passSeed2_6030All[i];
    passSeed2_6032All_count[i] += passSeed2_6032All[i];
    passSeed2_6034All_count[i] += passSeed2_6034All[i];
    passSeed2_6035All_count[i] += passSeed2_6035All[i];
    passSeed2_6036All_count[i] += passSeed2_6036All[i];
    passSeed2_6038All_count[i] += passSeed2_6038All[i];
    passSeed2_6040All_count[i] += passSeed2_6040All[i];
    passSeed2_6042All_count[i] += passSeed2_6042All[i];
    passSeed2_6044All_count[i] += passSeed2_6044All[i];
    passSeed2_6045All_count[i] += passSeed2_6045All[i];
    passSeed2_6046All_count[i] += passSeed2_6046All[i];
    passSeed2_6048All_count[i] += passSeed2_6048All[i];
    passSeed2_6050All_count[i] += passSeed2_6050All[i];
    passSeed2_6055All_count[i] += passSeed2_6055All[i];
    passSeed2_6060All_count[i] += passSeed2_6060All[i];

    // extras
    passSeed2_3545400All_count[i] += passSeed2_3545400All[i];
    passSeed2_3538500All_count[i] += passSeed2_3538500All[i];
    passSeed2_4028600All_count[i] += passSeed2_4028600All[i];
    passSeed2_4528450All_count[i] += passSeed2_4528450All[i];
    passSeed2_5028400All_count[i] += passSeed2_5028400All[i];
    passSeed2_5025450All_count[i] += passSeed2_5025450All[i];

    }

    // two blocks to remove overlap of ditau and old vbf from seed 2 variations to get pure rate
    if (passDiTau || passOld) {
    passSeed2_3525All_count[i] +=1;
    passSeed2_3530All_count[i] +=1;
    passSeed2_3532All_count[i] +=1;
    passSeed2_3534All_count[i] +=1;
    passSeed2_3535All_count[i] +=1;
    passSeed2_3536All_count[i] +=1;
    passSeed2_3538All_count[i] +=1;
    passSeed2_3540All_count[i] +=1;
    passSeed2_3542All_count[i] +=1;
    passSeed2_3544All_count[i] +=1;
    passSeed2_3545All_count[i] +=1;
    passSeed2_3546All_count[i] +=1;
    passSeed2_3548All_count[i] +=1;
    passSeed2_3550All_count[i] +=1;
    passSeed2_3555All_count[i] +=1;
    passSeed2_3560All_count[i] +=1;

    passSeed2_4025All_count[i] +=1;
    passSeed2_4030All_count[i] +=1;
    passSeed2_4032All_count[i] +=1;
    passSeed2_4034All_count[i] +=1;
    passSeed2_4035All_count[i] +=1;
    passSeed2_4036All_count[i] +=1;
    passSeed2_4038All_count[i] +=1;
    passSeed2_4040All_count[i] +=1;
    passSeed2_4042All_count[i] +=1;
    passSeed2_4044All_count[i] +=1;
    passSeed2_4045All_count[i] +=1;
    passSeed2_4046All_count[i] +=1;
    passSeed2_4048All_count[i] +=1;
    passSeed2_4050All_count[i] +=1;
    passSeed2_4055All_count[i] +=1;
    passSeed2_4060All_count[i] +=1;

    passSeed2_4525All_count[i] +=1;
    passSeed2_4530All_count[i] +=1;
    passSeed2_4532All_count[i] +=1;
    passSeed2_4534All_count[i] +=1;
    passSeed2_4535All_count[i] +=1;
    passSeed2_4536All_count[i] +=1;
    passSeed2_4538All_count[i] +=1;
    passSeed2_4540All_count[i] +=1;
    passSeed2_4542All_count[i] +=1;
    passSeed2_4544All_count[i] +=1;
    passSeed2_4545All_count[i] +=1;
    passSeed2_4546All_count[i] +=1;
    passSeed2_4548All_count[i] +=1;
    passSeed2_4550All_count[i] +=1;
    passSeed2_4555All_count[i] +=1;
    passSeed2_4560All_count[i] +=1;

    passSeed2_5025All_count[i] +=1;
    passSeed2_5030All_count[i] +=1;
    passSeed2_5032All_count[i] +=1;
    passSeed2_5034All_count[i] +=1;
    passSeed2_5035All_count[i] +=1;
    passSeed2_5036All_count[i] +=1;
    passSeed2_5038All_count[i] +=1;
    passSeed2_5040All_count[i] +=1;
    passSeed2_5042All_count[i] +=1;
    passSeed2_5044All_count[i] +=1;
    passSeed2_5045All_count[i] +=1;
    passSeed2_5046All_count[i] +=1;
    passSeed2_5048All_count[i] +=1;
    passSeed2_5050All_count[i] +=1;
    passSeed2_5055All_count[i] +=1;
    passSeed2_5060All_count[i] +=1;


    passSeed2_5525All_count[i] +=1;
    passSeed2_5530All_count[i] +=1;
    passSeed2_5532All_count[i] +=1;
    passSeed2_5534All_count[i] +=1;
    passSeed2_5535All_count[i] +=1;
    passSeed2_5536All_count[i] +=1;
    passSeed2_5538All_count[i] +=1;
    passSeed2_5540All_count[i] +=1;
    passSeed2_5542All_count[i] +=1;
    passSeed2_5544All_count[i] +=1;
    passSeed2_5545All_count[i] +=1;
    passSeed2_5546All_count[i] +=1;
    passSeed2_5548All_count[i] +=1;
    passSeed2_5550All_count[i] +=1;
    passSeed2_5555All_count[i] +=1;
    passSeed2_5560All_count[i] +=1;

    passSeed2_6025All_count[i] +=1;
    passSeed2_6030All_count[i] +=1;
    passSeed2_6032All_count[i] +=1;
    passSeed2_6034All_count[i] +=1;
    passSeed2_6035All_count[i] +=1;
    passSeed2_6036All_count[i] +=1;
    passSeed2_6038All_count[i] +=1;
    passSeed2_6040All_count[i] +=1;
    passSeed2_6042All_count[i] +=1;
    passSeed2_6044All_count[i] +=1;
    passSeed2_6045All_count[i] +=1;
    passSeed2_6046All_count[i] +=1;
    passSeed2_6048All_count[i] +=1;
    passSeed2_6050All_count[i] +=1;
    passSeed2_6055All_count[i] +=1;
    passSeed2_6060All_count[i] +=1;
   
    // extras
    passSeed2_3545400All_count[i] += 1;
    passSeed2_3538500All_count[i] += 1;
    passSeed2_4028600All_count[i] += 1;
    passSeed2_4528450All_count[i] += 1;
    passSeed2_5028400All_count[i] += 1;
    passSeed2_5025450All_count[i] += 1;


    } // pass diTau if
  }

  // end variations
  // counting up overlaps (ANDs) and ORs

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

  // additional logics/funny seeds that needed rate testing

  passTripJetsCount += passTripJets;
  orNewVBFTripJets += (passTripJets || passNew);
  orDiTauTripJets += (passTripJets || passDiTau);
  orDiTauNewVBFTripJets += (passTripJets || passNew || passDiTau);

  passManfredLogicCount += passManfredLogic;
  orDiTauOldVBFManfredLogic += (passManfredLogic || passOld || passDiTau);

  passSeed2TestingCount += passSeed2Testing;
  orDiTauOldSeed2Testing += (passSeed2Testing || passOld || passDiTau);

  overlapManfredNew += (passManfredLogic && passNew);

  //olDiTauOldSeed2 += (passDiTau && passOld && passSeed2_3545All[1]);
  //orDiTauOldSeed2 += (passDiTau || passOld || passSeed2_3545All[1]);

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

  cout << Kfactor << '\t' << "Rate factor from eqn Kyungwook gave me" << endl;
  cout << Ofactor << '\t' << "Rate factor from eqn Olivier gave me" << endl;

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

  bool subtractOverlap = true;
  if (subtractOverlap) {
    for (int i = 0; i<6; ++i) {

    passSeed2_3525All_count[i] -= orDiTauOld;
    passSeed2_3530All_count[i] -= orDiTauOld;
    passSeed2_3532All_count[i] -= orDiTauOld;
    passSeed2_3534All_count[i] -= orDiTauOld;
    passSeed2_3535All_count[i] -= orDiTauOld;
    passSeed2_3536All_count[i] -= orDiTauOld;
    passSeed2_3538All_count[i] -= orDiTauOld;
    passSeed2_3540All_count[i] -= orDiTauOld;
    passSeed2_3542All_count[i] -= orDiTauOld;
    passSeed2_3544All_count[i] -= orDiTauOld;
    passSeed2_3545All_count[i] -= orDiTauOld;
    passSeed2_3546All_count[i] -= orDiTauOld;
    passSeed2_3548All_count[i] -= orDiTauOld;
    passSeed2_3550All_count[i] -= orDiTauOld;
    passSeed2_3555All_count[i] -= orDiTauOld;
    passSeed2_3560All_count[i] -= orDiTauOld;

    passSeed2_4025All_count[i] -= orDiTauOld;
    passSeed2_4030All_count[i] -= orDiTauOld;
    passSeed2_4032All_count[i] -= orDiTauOld;
    passSeed2_4034All_count[i] -= orDiTauOld;
    passSeed2_4035All_count[i] -= orDiTauOld;
    passSeed2_4036All_count[i] -= orDiTauOld;
    passSeed2_4038All_count[i] -= orDiTauOld;
    passSeed2_4040All_count[i] -= orDiTauOld;
    passSeed2_4042All_count[i] -= orDiTauOld;
    passSeed2_4044All_count[i] -= orDiTauOld;
    passSeed2_4045All_count[i] -= orDiTauOld;
    passSeed2_4046All_count[i] -= orDiTauOld;
    passSeed2_4048All_count[i] -= orDiTauOld;
    passSeed2_4050All_count[i] -= orDiTauOld;
    passSeed2_4055All_count[i] -= orDiTauOld;
    passSeed2_4060All_count[i] -= orDiTauOld;

    passSeed2_4525All_count[i] -= orDiTauOld;
    passSeed2_4530All_count[i] -= orDiTauOld;
    passSeed2_4532All_count[i] -= orDiTauOld;
    passSeed2_4534All_count[i] -= orDiTauOld;
    passSeed2_4535All_count[i] -= orDiTauOld;
    passSeed2_4536All_count[i] -= orDiTauOld;
    passSeed2_4538All_count[i] -= orDiTauOld;
    passSeed2_4540All_count[i] -= orDiTauOld;
    passSeed2_4542All_count[i] -= orDiTauOld;
    passSeed2_4544All_count[i] -= orDiTauOld;
    passSeed2_4545All_count[i] -= orDiTauOld;
    passSeed2_4546All_count[i] -= orDiTauOld;
    passSeed2_4548All_count[i] -= orDiTauOld;
    passSeed2_4550All_count[i] -= orDiTauOld;
    passSeed2_4555All_count[i] -= orDiTauOld;
    passSeed2_4560All_count[i] -= orDiTauOld;

    passSeed2_5025All_count[i] -= orDiTauOld;
    passSeed2_5030All_count[i] -= orDiTauOld;
    passSeed2_5032All_count[i] -= orDiTauOld;
    passSeed2_5034All_count[i] -= orDiTauOld;
    passSeed2_5035All_count[i] -= orDiTauOld;
    passSeed2_5036All_count[i] -= orDiTauOld;
    passSeed2_5038All_count[i] -= orDiTauOld;
    passSeed2_5040All_count[i] -= orDiTauOld;
    passSeed2_5042All_count[i] -= orDiTauOld;
    passSeed2_5044All_count[i] -= orDiTauOld;
    passSeed2_5045All_count[i] -= orDiTauOld;
    passSeed2_5046All_count[i] -= orDiTauOld;
    passSeed2_5048All_count[i] -= orDiTauOld;
    passSeed2_5050All_count[i] -= orDiTauOld;
    passSeed2_5055All_count[i] -= orDiTauOld;
    passSeed2_5060All_count[i] -= orDiTauOld;


    passSeed2_5525All_count[i] -= orDiTauOld;
    passSeed2_5530All_count[i] -= orDiTauOld;
    passSeed2_5532All_count[i] -= orDiTauOld;
    passSeed2_5534All_count[i] -= orDiTauOld;
    passSeed2_5535All_count[i] -= orDiTauOld;
    passSeed2_5536All_count[i] -= orDiTauOld;
    passSeed2_5538All_count[i] -= orDiTauOld;
    passSeed2_5540All_count[i] -= orDiTauOld;
    passSeed2_5542All_count[i] -= orDiTauOld;
    passSeed2_5544All_count[i] -= orDiTauOld;
    passSeed2_5545All_count[i] -= orDiTauOld;
    passSeed2_5546All_count[i] -= orDiTauOld;
    passSeed2_5548All_count[i] -= orDiTauOld;
    passSeed2_5550All_count[i] -= orDiTauOld;
    passSeed2_5555All_count[i] -= orDiTauOld;
    passSeed2_5560All_count[i] -= orDiTauOld;

    passSeed2_6025All_count[i] -= orDiTauOld;
    passSeed2_6030All_count[i] -= orDiTauOld;
    passSeed2_6032All_count[i] -= orDiTauOld;
    passSeed2_6034All_count[i] -= orDiTauOld;
    passSeed2_6035All_count[i] -= orDiTauOld;
    passSeed2_6036All_count[i] -= orDiTauOld;
    passSeed2_6038All_count[i] -= orDiTauOld;
    passSeed2_6040All_count[i] -= orDiTauOld;
    passSeed2_6042All_count[i] -= orDiTauOld;
    passSeed2_6044All_count[i] -= orDiTauOld;
    passSeed2_6045All_count[i] -= orDiTauOld;
    passSeed2_6046All_count[i] -= orDiTauOld;
    passSeed2_6048All_count[i] -= orDiTauOld;
    passSeed2_6050All_count[i] -= orDiTauOld;
    passSeed2_6055All_count[i] -= orDiTauOld;
    passSeed2_6060All_count[i] -= orDiTauOld;

    passSeed2_3545400All_count[i] -= orDiTauOld;
    passSeed2_3538500All_count[i] -= orDiTauOld;
    passSeed2_4028600All_count[i] -= orDiTauOld;
    passSeed2_4528450All_count[i] -= orDiTauOld;
    passSeed2_5028400All_count[i] -= orDiTauOld;
    passSeed2_5025450All_count[i] -= orDiTauOld;



    }
  }


  cout << "Varying params for Seed 2" << endl;
  cout << "using Et as Pt currently" << endl;
  cout << "JetPt=35, TauPt [25,60], 2MassOnLeft" << endl;
  cout << '\t' << "25" << '\t' 
  << "30" << '\t' 
  << "32" << '\t' 
  << "34" << '\t' 
  << "35" << '\t' 
  << "36" << '\t' 
  << "38" << '\t' 
  << "40" << '\t' 
  << "42" << '\t' 
  << "44" << '\t' 
  << "45" << '\t' 
  << "46" << '\t' 
  << "48" << '\t' 
  << "50" << '\t' 
  << "55" << '\t' 
  << "60" << endl;
  for (int i = 1; i<6; ++i) {
    cout << mjjCuts[i] << '\t'
    << passSeed2_3525All_count[i] << '\t' 
    << passSeed2_3530All_count[i] << '\t' 
    << passSeed2_3532All_count[i] << '\t' 
    << passSeed2_3534All_count[i] << '\t' 
    << passSeed2_3535All_count[i] << '\t' 
    << passSeed2_3536All_count[i] << '\t' 
    << passSeed2_3538All_count[i] << '\t' 
    << passSeed2_3540All_count[i] << '\t' 
    << passSeed2_3542All_count[i] << '\t' 
    << passSeed2_3544All_count[i] << '\t' 
    << passSeed2_3545All_count[i] << '\t' 
    << passSeed2_3546All_count[i] << '\t' 
    << passSeed2_3548All_count[i] << '\t' 
    << passSeed2_3550All_count[i] << '\t' 
    << passSeed2_3555All_count[i] << '\t' 
    << passSeed2_3560All_count[i] << endl;
  }

  cout << "JetPt=40, TauPt [25,60], 2MassOnLeft" << endl;
  cout << '\t' << "25" << '\t' 
  << "30" << '\t' 
  << "32" << '\t' 
  << "34" << '\t' 
  << "35" << '\t' 
  << "36" << '\t' 
  << "38" << '\t' 
  << "40" << '\t' 
  << "42" << '\t' 
  << "44" << '\t' 
  << "45" << '\t' 
  << "46" << '\t' 
  << "48" << '\t' 
  << "50" << '\t' 
  << "55" << '\t' 
  << "60" << endl;
  for (int i = 1; i<6; ++i) {
    cout << mjjCuts[i] << '\t' 
    << passSeed2_4025All_count[i] << '\t' 
    << passSeed2_4030All_count[i] << '\t' 
    << passSeed2_4032All_count[i] << '\t' 
    << passSeed2_4034All_count[i] << '\t' 
    << passSeed2_4035All_count[i] << '\t' 
    << passSeed2_4036All_count[i] << '\t' 
    << passSeed2_4038All_count[i] << '\t' 
    << passSeed2_4040All_count[i] << '\t' 
    << passSeed2_4042All_count[i] << '\t' 
    << passSeed2_4044All_count[i] << '\t' 
    << passSeed2_4045All_count[i] << '\t' 
    << passSeed2_4046All_count[i] << '\t' 
    << passSeed2_4048All_count[i] << '\t' 
    << passSeed2_4050All_count[i] << '\t' 
    << passSeed2_4055All_count[i] << '\t' 
    << passSeed2_4060All_count[i] << endl;
  }

  cout << "JetPt=45, TauPt [25,60], 2MassOnLeft" << endl;
  cout << '\t' << "25" << '\t' 
  << "30" << '\t' 
  << "32" << '\t' 
  << "34" << '\t' 
  << "35" << '\t' 
  << "36" << '\t' 
  << "38" << '\t' 
  << "40" << '\t' 
  << "42" << '\t' 
  << "44" << '\t' 
  << "45" << '\t' 
  << "46" << '\t' 
  << "48" << '\t' 
  << "50" << '\t' 
  << "55" << '\t' 
  << "60" << endl;
  for (int i = 1; i<6; ++i) {
    cout << mjjCuts[i] << '\t'
    << passSeed2_4525All_count[i] << '\t' 
    << passSeed2_4530All_count[i] << '\t' 
    << passSeed2_4532All_count[i] << '\t' 
    << passSeed2_4534All_count[i] << '\t' 
    << passSeed2_4535All_count[i] << '\t' 
    << passSeed2_4536All_count[i] << '\t' 
    << passSeed2_4538All_count[i] << '\t' 
    << passSeed2_4540All_count[i] << '\t' 
    << passSeed2_4542All_count[i] << '\t' 
    << passSeed2_4544All_count[i] << '\t' 
    << passSeed2_4545All_count[i] << '\t' 
    << passSeed2_4546All_count[i] << '\t' 
    << passSeed2_4548All_count[i] << '\t' 
    << passSeed2_4550All_count[i] << '\t' 
    << passSeed2_4555All_count[i] << '\t' 
    << passSeed2_4560All_count[i] << endl;
  }

  cout << "JetPt=50, TauPt [25,60], 2MassOnLeft" << endl;
  cout << '\t' << "25" << '\t' 
  << "30" << '\t' 
  << "32" << '\t' 
  << "34" << '\t' 
  << "35" << '\t' 
  << "36" << '\t' 
  << "38" << '\t' 
  << "40" << '\t' 
  << "42" << '\t' 
  << "44" << '\t' 
  << "45" << '\t' 
  << "46" << '\t' 
  << "48" << '\t' 
  << "50" << '\t' 
  << "55" << '\t' 
  << "60" << endl;
  for (int i = 1; i<6; ++i) {
    cout << mjjCuts[i] << '\t' 
    << passSeed2_5025All_count[i] << '\t' 
    << passSeed2_5030All_count[i] << '\t' 
    << passSeed2_5032All_count[i] << '\t' 
    << passSeed2_5034All_count[i] << '\t' 
    << passSeed2_5035All_count[i] << '\t' 
    << passSeed2_5036All_count[i] << '\t' 
    << passSeed2_5038All_count[i] << '\t' 
    << passSeed2_5040All_count[i] << '\t' 
    << passSeed2_5042All_count[i] << '\t' 
    << passSeed2_5044All_count[i] << '\t' 
    << passSeed2_5045All_count[i] << '\t' 
    << passSeed2_5046All_count[i] << '\t' 
    << passSeed2_5048All_count[i] << '\t' 
    << passSeed2_5050All_count[i] << '\t' 
    << passSeed2_5055All_count[i] << '\t' 
    << passSeed2_5060All_count[i] << endl;
  }
  
  cout << "JetPt=55, TauPt [25,60], 2MassOnLeft" << endl;
  cout << '\t' << "25" << '\t' 
  << "30" << '\t' 
  << "32" << '\t' 
  << "34" << '\t' 
  << "35" << '\t' 
  << "36" << '\t' 
  << "38" << '\t' 
  << "40" << '\t' 
  << "42" << '\t' 
  << "44" << '\t' 
  << "45" << '\t' 
  << "46" << '\t' 
  << "48" << '\t' 
  << "50" << '\t' 
  << "55" << '\t' 
  << "60" << endl;
  for (int i = 1; i<6; ++i) {
    cout << mjjCuts[i] << '\t' 
    << passSeed2_5525All_count[i] << '\t' 
    << passSeed2_5530All_count[i] << '\t' 
    << passSeed2_5532All_count[i] << '\t' 
    << passSeed2_5534All_count[i] << '\t' 
    << passSeed2_5535All_count[i] << '\t' 
    << passSeed2_5536All_count[i] << '\t' 
    << passSeed2_5538All_count[i] << '\t' 
    << passSeed2_5540All_count[i] << '\t' 
    << passSeed2_5542All_count[i] << '\t' 
    << passSeed2_5544All_count[i] << '\t' 
    << passSeed2_5545All_count[i] << '\t' 
    << passSeed2_5546All_count[i] << '\t' 
    << passSeed2_5548All_count[i] << '\t' 
    << passSeed2_5550All_count[i] << '\t' 
    << passSeed2_5555All_count[i] << '\t' 
    << passSeed2_5560All_count[i] << endl;
  }

  cout << "JetPt=60, TauPt [25,60], 2MassOnLeft" << endl;
  cout << '\t' << "25" << '\t' 
  << "30" << '\t' 
  << "32" << '\t' 
  << "34" << '\t' 
  << "35" << '\t' 
  << "36" << '\t' 
  << "38" << '\t' 
  << "40" << '\t' 
  << "42" << '\t' 
  << "44" << '\t' 
  << "45" << '\t' 
  << "46" << '\t' 
  << "48" << '\t' 
  << "50" << '\t' 
  << "55" << '\t' 
  << "60" << endl;
  for (int i = 1; i<6; ++i) {
    cout << mjjCuts[i] << '\t' 
    << passSeed2_6025All_count[i] << '\t' 
    << passSeed2_6030All_count[i] << '\t' 
    << passSeed2_6032All_count[i] << '\t' 
    << passSeed2_6034All_count[i] << '\t' 
    << passSeed2_6035All_count[i] << '\t' 
    << passSeed2_6036All_count[i] << '\t' 
    << passSeed2_6038All_count[i] << '\t' 
    << passSeed2_6040All_count[i] << '\t' 
    << passSeed2_6042All_count[i] << '\t' 
    << passSeed2_6044All_count[i] << '\t' 
    << passSeed2_6045All_count[i] << '\t' 
    << passSeed2_6046All_count[i] << '\t' 
    << passSeed2_6048All_count[i] << '\t' 
    << passSeed2_6050All_count[i] << '\t' 
    << passSeed2_6055All_count[i] << '\t' 
    << passSeed2_6060All_count[i] << endl;
  }
  //extras
  cout << passSeed2_3545400All_count[1] << '\t' << "3545400" << endl;
  cout << passSeed2_3538500All_count[3] << '\t' << "3538500" << endl;
  cout << passSeed2_4028600All_count[5] << '\t' << "4028600" << endl;
  cout << passSeed2_4528450All_count[2] << '\t' << "4528450" << endl;
  cout << passSeed2_4528450All_count[3] << '\t' << "4528500" << endl;
  cout << passSeed2_4528450All_count[4] << '\t' << "4528550" << endl;
  cout << passSeed2_5028400All_count[1] << '\t' << "5028400" << endl;
  cout << passSeed2_5025450All_count[2] << '\t' << "5025450" << endl;

  cout << endl;
  cout << "new hotness" << endl;
  cout << endl;
  cout << passTripJetsCount << " pass TripJet35 etc" << endl;
  cout << orNewVBFTripJets << " pass TripJet35 OR New VBF (except new vbf is still at 450" << endl;
  cout << orDiTauTripJets << " pass TripJets35 OR DiTau (35 should be)" << endl;
  cout << orDiTauNewVBFTripJets << " pass TripJets35 OR DiTau OR New VBF" << endl;

  cout << "comparing 3 rates and pure rates" << endl;
  cout << "Events" << '\t' << "orDiTauOld[SEED]" << '\t' << "Pure Events" << endl;
  int pureManfred = orDiTauOldVBFManfredLogic - orDiTauOld;
  cout << passManfredLogicCount << '\t' << orDiTauOldVBFManfredLogic << '\t' << pureManfred << '\t' << "DoubleJet35_Mass_Min450_IsoTau45_RmvOl_Minimal (Manfred)" << endl;
  int pureNew = orDiTauOldNew - orDiTauOld;
  cout << passNewCount << '\t' << orDiTauOldNew << '\t' << pureNew << '\t' << "DoubleJet35_Mass_Min450_IsoTau45_RmvOl (NewVBF, original)" << endl;
  int pureMassAnyTwo3545450 = orDiTauOldSeed2Testing - orDiTauOld; 
  cout << passSeed2TestingCount << '\t' << orDiTauOldSeed2Testing << '\t' << pureMassAnyTwo3545450 << '\t' << "DoubleJet35_MassAnyTwo450_IsoTau45_RmvOl (MassAnyTwo)" << endl;
  cout << overlapManfredNew << '\t' << "overlap Manfred New" << endl;
}
