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
      edm::EDGetTokenT<TrackCollection> tracksToken_;  //used to select what tracks to read from configuration file
      TTree* tree_;

      static constexpr int MAX_SIZE = 1000;

      int ntracks_;
      int track_charge_[MAX_SIZE];
      // hlt
      //edm::InputTag triggerResultTag_;
      edm::EDGetTokenT<edm::TriggerResults>   triggerResultToken_; // might not need the second edm on this line
      //edm::InputTag triggerSummTag_;
      edm::EDGetTokenT<trigger::TriggerEvent> triggerEventToken_;
      bool triggered_;
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
    tracksToken_(consumes<TrackCollection>(iConfig.getUntrackedParameter<edm::InputTag>("tracks"))), //this comma may not need to be here?
    triggerResultToken_(consumes<TriggerResults>(iConfig.getUntrackedParameter<edm::InputTag>("triggerResults"))), //consumes is a cpp memory thing
    triggerEventToken_(consumes<trigger::TriggerEvent>(iConfig.getUntrackedParameter<edm::InputTag>("triggerEvent")))
//"tracks" as a string isn't defined previously so I think it refers to the tracks variable defined in the config file,
//accordingly, we define a trigger result variable (?)
//looks like the case when comparing to other code but remember to ask Kyungwook
//what the other script does in two lines Kyungwook does in one, that's why we're all tokens and no tags here  
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
   using namespace edm; //isn't this line redundant?

	// tracks
    edm::Handle<TrackCollection> tracks;
    iEvent.getByToken(tracksToken_, tracks);

    ntracks_ = tracks->size();

    auto i = 0;
    for (const auto& track : *tracks)
    {
      track_charge_[i++] = track.charge();
    }
	// hlt
    edm::Handle<TriggerResults> triggerResults;
    iEvent.getByToken(triggerResultToken_, triggerResults); //adding trigger event may be necessary? edm::Handle<trigger::TriggerEvent> triggerEvent;
    edm::Handle<trigger::TriggerEvent> triggerEvent; //instantiation
    iEvent.getByToken(triggerEventToken_, triggerEvent); //assignment
    edm::TriggerNames triggerNames_ = iEvent.triggerNames(*triggerResults);

    // copying the meat of the function from the other file
    triggered_ = false;
    for (unsigned int itrig = 0; itrig < triggerNames.size(); ++itrig)
    {
     LogDebug ("triggers") << triggerNames.triggerName(itrig) ; //is this native cpp? doesn't seem to be related to edm... may need to comment out
     if (triggerResults->accept(itrig))
     {
      std::string pathName = triggerNames.triggerName(itrig); //triggerName must be a method of triggerNames ?
      if ( pathName.find("HLT_VBF") != std::string::npos )
      {
       iEvent_.hlt.triggers.push_back(pathName);
       triggered_ = true;
      }
     }
    }
    tree_->Fill();
}


// ------------ method called once each job just before starting event loop  ------------
void NtupleMaker::beginJob()
{
    edm::Service<TFileService> fs;
    tree_ = fs->make<TTree>("vbf", "vbf");
    tree_->Branch("ntracks_", &ntracks_);
    tree_->Branch("track_charge_", track_charge_, "track_charge_[ntracks_]/I");
    tree_->Branch("HLT_triggered", triggered_, "triggered/B");
}

// ------------ method called once each job just after ending the event loop  ------------
void NtupleMaker::endJob()
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void NtupleMaker::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
    //The following says we do not know what parameters are allowed so do no validation
    // Please change this to state exactly what you do use, even if it is no parameters
    //edm::ParameterSetDescription desc;
    //desc.setUnknown();
    //descriptions.addDefault(desc);

    //Specify that only 'tracks' is allowed
    //To use, remove the default given above and uncomment below
    edm::ParameterSetDescription desc;
    desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
    descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(NtupleMaker);
