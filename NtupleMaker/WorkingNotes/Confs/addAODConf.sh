#!/bin/bash
FILE=$1

echo "
updatedTauName = \"slimmedTausNewID\" #name of pat::Tau collection with new tau-Ids
import RecoTauTag.RecoTau.tools.runTauIdMVA as tauIdConfig
tauIdEmbedder = tauIdConfig.TauIDEmbedder(process, cms, #debug = False,
                    updatedTauName = updatedTauName,
                    toKeep = [\"deepTau2017v2p1\", #deepTau TauIDs
                               ])
tauIdEmbedder.runTauID()
# Path and EndPath definitions

process.demo = cms.EDAnalyzer('NtupleMaker'
     #, tracks = cms.untracked.InputTag('ctfWithMaterialTracks')
     , triggerResults = cms.untracked.InputTag(\"TriggerResults\",\"\",\"MYOTHERHLT\") #change to HLT instead of MYOTHERHLT if not rerun 
     , triggerEvent = cms.untracked.InputTag(\"hltTriggerSummaryAOD\",\"\",\"MYOTHERHLT\")
     , triggerEventWithRefs = cms.untracked.InputTag(\"hltTriggerSummaryRAW\",\"\",\"MYOTHERHLT\")
     #, PFTauCollection = cms.untracked.InputTag(\"hltHpsPFTauProducer\",\"\",\"MYOTHERHLT\")
     #, hltHpsTracks = cms.untracked.InputTag(\"hltHpsPFTauTrack\",\"\",\"MYOTHERHLT\")

     , SkipEvent = cms.untracked.vstring('ProductNotFound')

     , fillingTriggers = cms.untracked.bool(True) # can run on data/GEN-SIM-DIGI-RAW
     , fillingEventInfo = cms.untracked.bool(True) # can run on data/GEN-SIM-DIGI-RAW/MINIAODSIM
     , fillingL1 = cms.untracked.bool(False)        # can run on MINIAODSIM
     , fillingTaus = cms.untracked.bool(False)      # can run on MINIAODSIM
     , fillingJets = cms.untracked.bool(False)      # can run on MINIAODSIM
     , development = cms.untracked.bool(False)     # left in to play nice with NtupleMaker
     , doGenParticles = cms.untracked.bool(False)  # left in to play nice with NtupleMaker

     , jetTriggerPrimitives = cms.untracked.InputTag(\"caloStage2Digis\", \"Jet\", \"RECO\")
     , tauTriggerPrimitives = cms.untracked.InputTag(\"caloStage2Digis\", \"Tau\", \"RECO\")

     , genParticleSrc = cms.untracked.InputTag(\"prunedGenParticles\")
     , VtxLabel = cms.untracked.InputTag(\"offlineSlimmedPrimaryVertices\")
     , rhoLabel = cms.untracked.InputTag(\"fixedGridRhoFastjetAll\")
     , tauSrc = cms.untracked.InputTag(\"slimmedTausNewID\")
     , ak4JetSrc = cms.untracked.InputTag(\"slimmedJets\")
)

process.TFileService = cms.Service(\"TFileService\",
    fileName = cms.string(\"histo.root\"),
    closeFileFast = cms.untracked.bool(True)
)

process.demoPath = cms.EndPath(
#        process.rerunMvaIsolationSequence * # comment out if not running on MINIAODSIM
#        getattr(process,updatedTauName) *   # comment out if not running on MINIAODSIM
        process.demo
)
process.schedule_().append(process.demoPath)" >> $FILE;
