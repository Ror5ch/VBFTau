#define analyzer_cxx
#include "analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void analyzer::Loop()
{
  if (fChain1 == 0 || fChain2 == 0 ) {
    cout << "Santa Mozzarella!" << endl;
    return;
  }

  Long64_t nentries1 = fChain1->GetEntriesFast();
  Long64_t nentries2 = fChain2->GetEntriesFast();

  cout << nentries1 << "\t" << nentries2 << endl;

  Long64_t nbytes = 0, nb = 0;

  set<int> lumis;

  int count = 0;
  int count2 = 0;
  int passDiTau = 0;
  int tauCount = 0;

  for (Long64_t jentry=11100000; jentry<11400001; ++jentry) {

    if (jentry%100000 == 0) cout << jentry << endl;
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;

    nb = fChain1->GetEntry(jentry);   nbytes += nb;
    nb = fChain2->GetEntry(jentry);

    count += 1;
    if (run != 323755) continue;
    lumis.insert(lumi);
    count2 += 1;

    tauCount = 0;
    for (int iTau = 0; iTau < tauBx.size(); ++iTau) {
      if (tauBx[iTau] != 0) continue;
      if (tauIso[iTau] < 1) continue;
      if (tauEt[iTau] < 32) continue;
      if (abs(tauEta[iTau]) > 2.1) continue;
      tauCount += 1;
      //if (tauCount != 0) cout << "Et, Eta, Bx, Iso: " << '\t' << tauEt[iTau] << '\t' << tauEta[iTau] << '\t' << tauBx[iTau] << '\t' << tauIso[iTau] << endl;
    }
    if (tauCount >= 2) passDiTau += 1;

    for (int iJet = 0; iJet < jetBx.size(); ++iJet) {
      if (jetBx[iJet] != 0) continue;
      cout << jetBx[iJet] << " jetBx" << endl;
    }

    //will need, tauBx, tauIso, tauEt, tauPhi, tauEta
    //also need, jetBx, jetEt, jetPhi, jetEta
    //finally, just need "run" and "lumiBlock"
    //there is neither jet nor tau energy. how will we calculate object mass?
  }
  cout << count << " Events Scanned" << endl;
  cout << count2 << " Events in Selected Run Number (323755)" << endl;
  cout << passDiTau << " Events passing selection " << endl;
  cout << lumis.size() << " lumi set size" << endl;
}
