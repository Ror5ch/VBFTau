// -*- C++ -*-
//
// Package:    VBFTau/NtupleMaker
// Class:      NtupleMaker
//
/**\class NtupleMaker NtupleMaker.cc VBFTau/NtupleMaker/plugins/NtupleMaker.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Kyungwook Nam
//         Created:  Wed, 31 Mar 2021 12:16:11 GMT
//
//


// system include files
#include <memory>
#include <vector>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h" 

#include "TTree.h"

//added from other file for trigger names (?)
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h" //might be old/deprecated, other script written in 2017
#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "DataFormats/Common/interface/TriggerResults.h"
//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<>
// This will improve performance in multithreaded jobs.


using reco::TrackCollection;

class NtupleMaker : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit NtupleMaker(const edm::ParameterSet&);
      ~NtupleMaker();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
      // tracks
      //edm::EDGetTokenT<TrackCollection> tracksToken_;  //used to select what tracks to read from configuration file
      TTree* tree_;

      static constexpr int MAX_SIZE = 1000;

      //int ntracks_;
      //int track_charge_[MAX_SIZE];
      // hlt
      edm::EDGetTokenT<edm::TriggerResults>   triggerResultToken_;
      edm::EDGetTokenT<trigger::TriggerEvent> triggerEventToken_;
      std::vector<bool> * triggeredBranch_;
      bool triggered_;

      float pt_;
      float eta_;
      float phi_;
      std::vector<float> * ptT1_; //doing this for three different triggers
      std::vector<float> * etaT1_;
      std::vector<float> * phiT1_;
      std::vector<float> * ptT2_;
      std::vector<float> * etaT2_;
      std::vector<float> * phiT2_;
      std::vector<float> * ptT3_;
      std::vector<float> * etaT3_;
      std::vector<float> * phiT3_;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
NtupleMaker::NtupleMaker(const edm::ParameterSet& iConfig):
    //tracksToken_(consumes<TrackCollection>(iConfig.getUntrackedParameter<edm::InputTag>("tracks"))),
    triggerResultToken_(consumes<edm::TriggerResults>(iConfig.getUntrackedParameter<edm::InputTag>("triggerResults"))),
    triggerEventToken_(consumes<trigger::TriggerEvent>(iConfig.getUntrackedParameter<edm::InputTag>("triggerEvent"))),
//"tracks" as a string isn't defined previously so I think it refers to the tracks variable defined in the config file,
//accordingly, we define a trigger result variable 
//remember to ask Kyungwook
    triggeredBranch_{new std::vector<bool>()},
    ptT1_{new std::vector<float>()},
    etaT1_{new std::vector<float>()},
    phiT1_{new std::vector<float>()},
    ptT2_{new std::vector<float>()},
    etaT2_{new std::vector<float>()},
    phiT2_{new std::vector<float>()},
    ptT3_{new std::vector<float>()},
    etaT3_{new std::vector<float>()},
    phiT3_{new std::vector<float>()}
{
       //now do what ever initialization is needed
}


NtupleMaker::~NtupleMaker()
{

    // do anything here that needs to be done at desctruction time
    // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void NtupleMaker::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
	// hlt
    edm::Handle<TriggerResults> triggerResults;
    iEvent.getByToken(triggerResultToken_, triggerResults);
    edm::Handle<trigger::TriggerEvent> triggerEvent; //instantiation
    iEvent.getByToken(triggerEventToken_, triggerEvent); //assignment
    const edm::TriggerNames triggerNames_ = iEvent.triggerNames(*triggerResults); //from online tutorial
    std::string pathName="HLT_VBF_DoubleTightChargedIsoPFTauHPS20_Trk1_eta2p1_v1";
    triggered_ = triggerResults->accept(triggerNames_.triggerIndex(pathName));
    triggeredBranch_->push_back(triggered_);


    const trigger::size_type nFilters(triggerEvent->sizeFilters());
    std::string firstTag = "hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon::MYHLT";
    std::string secondTag = "hltMatchedVBFOnePFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20::MYHLT";
    std::string thirdTag = "hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20::MYHLT";

    ptT1_->clear();
    etaT1_->clear();
    phiT1_->clear();
    ptT2_->clear();
    etaT2_->clear();
    phiT2_->clear();
    ptT3_->clear();
    etaT3_->clear();
    phiT3_->clear();
    for (trigger::size_type iFilter=0; iFilter!=nFilters; ++iFilter){
        std::string filterTag = triggerEvent->filterTag(iFilter).encode();
        trigger::Keys objectKeys = triggerEvent->filterKeys(iFilter);
	const trigger::TriggerObjectCollection& triggerObjects(triggerEvent->getObjects());
	for(trigger::size_type iKey=0; iKey < objectKeys.size(); ++iKey){
	    trigger::size_type objKey = objectKeys.at(iKey);
	    const trigger::TriggerObject& triggerObj(triggerObjects[objKey]);
	    pt_ = triggerObj.pt();
	    eta_ = triggerObj.eta();
	    phi_ = triggerObj.phi();
	    if (filterTag == firstTag && pt_ > 0){
		ptT1_->push_back(pt_);
		etaT1_->push_back(eta_);
		phiT1_->push_back(phi_);
	    }
	    else{
		ptT1_->push_back(-9999);
		etaT1_->push_back(-9999);
		phiT1_->push_back(-9999);
	    }
	    if (filterTag == secondTag && pt_ > 0){
		ptT2_->push_back(pt_);
		etaT2_->push_back(eta_);
		phiT2_->push_back(phi_);
	    }
	    else{
		ptT2_->push_back(-9999);
		etaT2_->push_back(-9999);
		phiT2_->push_back(-9999);
	    }
	    if (filterTag == thirdTag && pt_ > 0){
		ptT3_->push_back(pt_);
		etaT3_->push_back(eta_);
		phiT3_->push_back(phi_);
	    }
	    else{
		ptT3_->push_back(-9999);
		etaT3_->push_back(-9999);
		phiT3_->push_back(-9999);
	    }
	}
    }

    //std::string filter1("hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon");
//implementation from https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideHLTAnalysis
//    trigger::size_type filterIndex = triggerEvent->filterIndex(edm::InputTag(filterName,"","MYHLT")); 
//    if(filterIndex < triggerEvent->sizeFilters()){ 
//        const trigger::Keys& triggerKeys = triggerEvent->filterKeys(filterIndex); 
//        const trigger::TriggerObjectCollection & trigObjColl(triggerEvent->getObjects());
        //now loop on the trigger objects passing filter
//        for(trigger::Keys::const_iterator keyIt=triggerKeys.begin(); keyIt!=triggerKeys.end(); ++keyIt){ 
//            const trigger::TriggerObject& obj = trigObjColl[*keyIt];
            //do what you want with the trigger objects, you have
            //eta,phi,pt,mass,p,px,py,pz,et,energy accessors
//            pt_ = obj.pt();
//	    std::cout << pt_ << std::endl;
//	    ptBranch_->push_back(pt_);
//        }
                                          
//    }//end filter size check

    tree_->Fill();
}


// ------------ method called once each job just before starting event loop  ------------
void NtupleMaker::beginJob()
{
    edm::Service<TFileService> fs;
    tree_ = fs->make<TTree>("vbf", "vbf");
    //tree_->Branch("ntracks_", &ntracks_);
    //tree_->Branch("track_charge_", track_charge_, "track_charge_[ntracks_]/I");
    tree_->Branch("triggeredBranch_", &triggeredBranch_);
    tree_->Branch("ptT1_", &ptT1_);
    tree_->Branch("etaT1_", &etaT1_);
    tree_->Branch("phiT1_", &phiT1_);
    tree_->Branch("ptT2_", &ptT2_);
    tree_->Branch("etaT2_", &etaT2_);
    tree_->Branch("phiT2_", &phiT2_);
    tree_->Branch("ptT3_", &ptT3_);
    tree_->Branch("etaT3_", &etaT3_);
    tree_->Branch("phiT3_", &phiT3_);
}

// ------------ method called once each job just after ending the event loop  ------------
void NtupleMaker::endJob()
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void NtupleMaker::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
    //The following says we do not know what parameters are allowed so do no validation
    // Please change this to state exactly what you do use, even if it is no parameters
    edm::ParameterSetDescription desc;
    desc.setUnknown();
    descriptions.addDefault(desc);

    //Specify that only 'tracks' is allowed
    //To use, remove the default given above and uncomment below
    //edm::ParameterSetDescription desc;
    //desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
    //descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(NtupleMaker);
