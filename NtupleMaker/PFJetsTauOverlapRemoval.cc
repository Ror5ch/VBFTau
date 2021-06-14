#include "RecoTauTag/HLTProducers/interface/PFJetsTauOverlapRemoval.h"
#include "Math/GenVector/VectorUtil.h"
#include "DataFormats/HLTReco/interface/TriggerTypeDefs.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "DataFormats/TauReco/interface/PFTau.h"
#include "DataFormats/Math/interface/deltaR.h"

//
// class declaration
//
PFJetsTauOverlapRemoval::PFJetsTauOverlapRemoval(const edm::ParameterSet& iConfig):
  tauSrc_    ( consumes<trigger::TriggerFilterObjectWithRefs>(iConfig.getParameter<edm::InputTag>("TauSrc"      ) ) ),
  pfJetSrc_  ( consumes<reco::PFJetCollection>(iConfig.getParameter<edm::InputTag>("PFJetSrc") ) ),
  matchingR2_ ( iConfig.getParameter<double>("Min_dR")*iConfig.getParameter<double>("Min_dR") )
{  
  produces<reco::PFJetCollection>();
}
PFJetsTauOverlapRemoval::~PFJetsTauOverlapRemoval(){ }

void PFJetsTauOverlapRemoval::produce(edm::StreamID iSId, edm::Event& iEvent, const edm::EventSetup& iES) const
{
  std::unique_ptr<reco::PFJetCollection> cleanedPFJets(new reco::PFJetCollection);
    
  edm::Handle<trigger::TriggerFilterObjectWithRefs> tauJets;
  iEvent.getByToken(tauSrc_, tauJets);
  
  edm::Handle<reco::PFJetCollection> PFJets;
  iEvent.getByToken(pfJetSrc_,PFJets);
                
  trigger::VRpftau taus; 
  tauJets->getObjects(trigger::TriggerTau,taus);

  if(PFJets->size() > 1){
    for(unsigned int iJet = 0; iJet < PFJets->size(); iJet++){  
      bool isMatched = false;  
      const reco::PFJet &  myPFJet = (*PFJets)[iJet];
      //std::cout << "myPFJet.pt() " << myPFJet.pt() << std::endl;
      //std::cout << "myPFJet.eta() " << myPFJet.eta() << std::endl;
      //std::cout << "myPFJet.phi() " << myPFJet.phi() << std::endl;
      //std::cout << "myPFJet.energy() " << myPFJet.energy() << std::endl;
      for(unsigned int iTau = 0; iTau < taus.size(); iTau++){  
	//std::cout << "iJet: " << iJet << " iTau: " << iTau << std::endl;
	//std::cout << "myTau.pt() " << taus[iTau]->pt() << std::endl;
	//std::cout << "myTau.eta() " << taus[iTau]->eta() << std::endl;
	//std::cout << "myTau.phi() " << taus[iTau]->phi() << std::endl;
	//std::cout << "myTau.energy() " << taus[iTau]->energy() << std::endl;
        if(reco::deltaR2(taus[iTau]->p4(), myPFJet.p4()) < matchingR2_){
	  std::cout << "MATCHED in overlap" << std::endl;
	  //std::cout << "MATCHED " << "jet pt: " << myPFJet.pt() << " tau pt: " << taus[iTau]->pt() << std::endl;
	  //std::cout << "MATCHED " << "jet eta: " << myPFJet.eta() << " tau eta: " << taus[iTau]->eta() << std::endl;
	  //std::cout << "MATCHED " << "jet phi: " << myPFJet.phi() << " tau phi: " << taus[iTau]->phi() << std::endl;
	  //std::cout << "MATCHED " << "jet energy: " << myPFJet.energy() << " tau energy: " << taus[iTau]->energy() << std::endl;
	  //std::cout << "MATCHED deltaR2: " << reco::deltaR2(taus[iTau]->p4(), myPFJet.p4()) << std::endl;
          isMatched = true;
          break;
        }
      }
      if(isMatched == false) cleanedPFJets->push_back(myPFJet);
    }
  }
  iEvent.put(std::move(cleanedPFJets));
}

void PFJetsTauOverlapRemoval::fillDescriptions(edm::ConfigurationDescriptions& descriptions) 
{
  edm::ParameterSetDescription desc;
  desc.add<edm::InputTag>("PFJetSrc", edm::InputTag("hltAK4PFJetsCorrected"))->setComment("Input collection of PFJets"    );
  desc.add<edm::InputTag>("TauSrc", edm::InputTag("hltSinglePFTau20TrackPt1LooseChargedIsolationReg"))->setComment("Input collection of PFTaus that have passed ID and isolation requirements");
  desc.add<double>       ("Min_dR",0.5)->setComment("Minimum dR outside of which PFJets will be saved");
  descriptions.setComment("This module produces a collection of PFJets that are cross-cleaned with respect to PFTaus passing a HLT filter.");
  descriptions.add       ("PFJetsTauOverlapRemoval",desc);
}
