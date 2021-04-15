#include "VBFTau/NtupleMaker/plugins/NtupleMaker.h"

//using namespace std;

NtupleMaker::NtupleMaker(const edm::ParameterSet& iConfig) :
    need_triggers(iConfig.getUntrackedParameter<bool>("needTriggers")),
    triggerResultToken_(consumes<edm::TriggerResults>(iConfig.getUntrackedParameter<edm::InputTag>("triggerResults"))),
    triggerEventToken_(consumes<trigger::TriggerEvent>(iConfig.getUntrackedParameter<edm::InputTag>("triggerEvent")))
{

    edm::Service<TFileService> fs;
    tree_ = fs->make<TTree>("vbf", "vbf");

    if(need_triggers) branchesTriggers(tree_);
}

NtupleMaker::~NtupleMaker(){
//destructor
}

void NtupleMaker::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    //using namespace edm;
    if(need_triggers) fillTriggers(iEvent);

    tree_->Fill();
}

void NtupleMaker::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
    edm::ParameterSetDescription desc;
    desc.setUnknown();
    descriptions.addDefault(desc);
}

DEFINE_FWK_MODULE(NtupleMaker);
