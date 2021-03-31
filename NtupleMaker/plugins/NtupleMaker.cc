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
      edm::EDGetTokenT<TrackCollection> tracksToken_;  //used to select what tracks to read from configuration file
      TTree* tree_;

      static constexpr int MAX_SIZE = 1000;

      int ntracks_;
      int track_charge_[MAX_SIZE];
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
    tracksToken_(consumes<TrackCollection>(iConfig.getUntrackedParameter<edm::InputTag>("tracks")))

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

    edm::Handle<TrackCollection> tracks;
    iEvent.getByToken(tracksToken_, tracks);

    ntracks_ = tracks->size();

    auto i = 0;
    for (const auto& track : *tracks)
    {
      track_charge_[i++] = track.charge();
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
    //ParameterSetDescription desc;
    //desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
    //descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(NtupleMaker);
