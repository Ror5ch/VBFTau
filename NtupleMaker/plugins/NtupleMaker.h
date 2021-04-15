#ifndef Ntuplizer_h
#define Ntuplizer_h

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

// trigger include files
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"

using namespace std;

class NtupleMaker : public edm::one::EDAnalyzer<edm::one::SharedResources> {
    public:
        explicit NtupleMaker(const edm::ParameterSet&);
	~NtupleMaker();

	static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

    private:
	//virtual void beginJob() override;
	virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
	//virtual void endJob() override;
	
	void branchesTriggers(TTree*);
	void fillTriggers(const edm::Event&);

	//-------------member data----------------//
	TTree* tree_; 

	bool need_triggers;

	edm::EDGetTokenT<edm::TriggerResults> triggerResultToken_;
	edm::EDGetTokenT<trigger::TriggerEvent> triggerEventToken_;
};

#endif
