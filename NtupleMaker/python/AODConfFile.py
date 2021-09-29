import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")
#process = cms.Process(cms.InputTag("TriggerResults","","MYHLT"))

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(500) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        #'file:/afs/cern.ch/user/b/ballmond/private/CMSSW_10_2_16_UL/src/HLTrigger/Configuration/test/addedhltVBF_raw.root'

	#'file:root://cms-xrd-global.cern.ch//store/mc/RunIISpring18DR/VBFHToTauTau_M125_13TeV_powheg_pythia8/GEN-SIM-RAW/NZSPU28to70_100X_upgrade2018_realistic_v10-v1/90000/002188FF-4E2D-E811-9115-FA163EAD427A.root'
    
        #'file:root://cms-xrd-global.cern.ch//store/mc/RunIISpring18MiniAOD/VBFHToTauTau_M125_13TeV_powheg_pythia8/MINIAODSIM/NZSPU28to70_100X_upgrade2018_realistic_v10-v1/90000/021DCAE8-242E-E811-B362-02163E01A0CE.root',
	#'file:root://cms-xrd-global.cern.ch//store/data/Run2018D/EphemeralZeroBias1/MINIAOD/PromptReco-v2/000/320/497/00000/68E2874E-6495-E811-98C2-FA163EE0D32F.root',
	#'file:root://cms-xrd-global.cern.ch//store/data/Run2018D/EphemeralZeroBias8/MINIAOD/PromptReco-v2/000/320/497/00000/C8FEA71E-6695-E811-8D4D-02163E015309.root',

	#'file:root://cms-xrd-global.cern.ch//store/mc/RunIIAutumn18MiniAOD/VBFHToTauTau_M125_13TeV_powheg_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15_ext1-v1/00000/1ACE0760-BF84-3F47-A601-29022E50122E.root'

	#'file:root://cms-xrd-global.cern.ch//store/mc/RunIISpring18DR/VBFHToTauTau_M125_13TeV_powheg_pythia8/GEN-SIM-RAW/NZSPU28to70_100X_upgrade2018_realistic_v10-v1/90000/2850E817-202D-E811-8588-FA163E7C479F.root'

        #'file:root://cms-xrd-global.cern.ch//store/mc/RunIIAutumn18MiniAOD/GluGluHToTauTau_M125_13TeV_powheg_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v2/100000/0367CE5C-D121-5748-93D3-528A4B1DFDA5.root'
	'file:root://cms-xrd-global.cern.ch//store/mc/RunIIAutumn18MiniAOD/VBFHToTauTau_M125_13TeV_powheg_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15_ext1-v1/00000/1ACE0760-BF84-3F47-A601-29022E50122E.root'
    )
    
)
updatedTauName = "slimmedTausNewID" #name of pat::Tau collection with new tau-Ids
import RecoTauTag.RecoTau.tools.runTauIdMVA as tauIdConfig
tauIdEmbedder = tauIdConfig.TauIDEmbedder(process, cms, debug = False,
                    updatedTauName = updatedTauName,
                    toKeep = ["deepTau2017v2p1", #deepTau TauIDs
                               ])
tauIdEmbedder.runTauID()
# Path and EndPath definitions

process.demo = cms.EDAnalyzer('NtupleMaker'
     #, tracks = cms.untracked.InputTag('ctfWithMaterialTracks')
     , triggerResults = cms.untracked.InputTag("TriggerResults","","MYHLT") #change to HLT instead of MYHLT if not rerun 
     , triggerEvent = cms.untracked.InputTag("hltTriggerSummaryAOD","","MYHLT")
     , triggerEventWithRefs = cms.untracked.InputTag("hltTriggerSummaryRAW","","MYHLT")
     #, PFTauCollection = cms.untracked.InputTag("hltHpsPFTauProducer","","MYHLT")
     #, hltHpsTracks = cms.untracked.InputTag("hltHpsPFTauTrack", "","MYHLT")

     , SkipEvent = cms.untracked.vstring('ProductNotFound')

     , fillingTriggers = cms.untracked.bool(False)
     , fillingEventInfo = cms.untracked.bool(True)
     , fillingL1 = cms.untracked.bool(True)
     , fillingTaus = cms.untracked.bool(True)
     , fillingJets = cms.untracked.bool(True)
     , development = cms.untracked.bool(False)
     , doGenParticles = cms.untracked.bool(False)

     , jetTriggerPrimitives = cms.untracked.InputTag("caloStage2Digis", "Jet", "RECO")
     , tauTriggerPrimitives = cms.untracked.InputTag("caloStage2Digis", "Tau", "RECO")

     , genParticleSrc = cms.untracked.InputTag("prunedGenParticles")
     , VtxLabel = cms.untracked.InputTag("offlineSlimmedPrimaryVertices")
     , rhoLabel = cms.untracked.InputTag("fixedGridRhoFastjetAll")
     , tauSrc = cms.untracked.InputTag("slimmedTausNewID")
     , ak4JetSrc = cms.untracked.InputTag("slimmedJets")
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("histoAOD.root"),
    closeFileFast = cms.untracked.bool(True)
)

process.demoPath = cms.EndPath(
        process.rerunMvaIsolationSequence *
        getattr(process,updatedTauName) *
        process.demo
)
