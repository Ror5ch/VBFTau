#include "VBFTau/NtupleMaker/plugins/NtupleMaker.h"

//using namespace std;

NtupleMaker::NtupleMaker(const edm::ParameterSet& iConfig) :
    need_triggers(iConfig.getUntrackedParameter<bool>("needTriggers")),
    need_taus(iConfig.getUntrackedParameter<bool>("needTaus")),
    need_jets(iConfig.getUntrackedParameter<bool>("needJets")),

    development_(iConfig.getUntrackedParameter<bool>("development")),
    doGenParticles_(iConfig.getUntrackedParameter<bool>("doGenParticles")),
    genParticlesCollection_(consumes<vector<reco::GenParticle>>(iConfig.getUntrackedParameter<edm::InputTag>("genParticleSrc"))),
    tauCollection_(consumes<vector<pat::Tau>>(iConfig.getUntrackedParameter<edm::InputTag>("tauSrc"))),
    //PFTauCollection_(consumes<vector<reco::PFTau>>(iConfig.getUntrackedParameter<edm::InputTag>("PFTauCollection"))),
    vtxLabel_(consumes<reco::VertexCollection>(iConfig.getUntrackedParameter<edm::InputTag>("VtxLabel"))),
    rhoLabel_(consumes<double>(iConfig.getUntrackedParameter<edm::InputTag>("rhoLabel"))),
    jetsAK4Label_(consumes<edm::View<pat::Jet>>(iConfig.getUntrackedParameter<edm::InputTag>("ak4JetSrc"))),

    triggerResultToken_(consumes<edm::TriggerResults>(iConfig.getUntrackedParameter<edm::InputTag>("triggerResults"))),
    triggerEventToken_(consumes<trigger::TriggerEvent>(iConfig.getUntrackedParameter<edm::InputTag>("triggerEvent"))),

    triggerEventWithRefsToken_(consumes<trigger::TriggerEventWithRefs>(iConfig.getUntrackedParameter<edm::InputTag>("triggerEventWithRefs")))

{

    edm::Service<TFileService> fs;
    tree_ = fs->make<TTree>("vbf", "vbf");

    if(need_triggers) branchesTriggers(tree_);
    if(need_taus) branchesTaus(tree_);
    if(need_jets) branchesJets(tree_);
}

NtupleMaker::~NtupleMaker(){
//destructor
}

int runNumber;
int lumiBlock;
int eventNumberID;

void NtupleMaker::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    //using namespace edm;
    if(doGenParticles_){
        jetResolution_   = JME::JetResolution::get(iSetup, "AK4PFchs_pt");
        jetResolutionSF_ = JME::JetResolutionScaleFactor::get(iSetup, "AK4PFchs");
        //AK8jetResolution_   = JME::JetResolution::get(es, "AK8PFchs_pt");
        //AK8jetResolutionSF_ = JME::JetResolutionScaleFactor::get(es, "AK8PFchs");
    }

    if(need_triggers) fillTriggers(iEvent);
    if(need_taus) fillTaus(iEvent);
    if(need_jets) fillJets(iEvent, iSetup);


    tree_->Branch("runNumber", &runNumber);
    tree_->Branch("lumiBlock", &lumiBlock);
    tree_->Branch("eventNumberID", &eventNumberID);

    runNumber = iEvent.id().run();
    lumiBlock = iEvent.id().luminosityBlock();
    eventNumberID = iEvent.id().event();

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
