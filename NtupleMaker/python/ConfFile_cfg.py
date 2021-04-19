import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")
#process = cms.Process(cms.InputTag("TriggerResults","","MYHLT"))

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        #'file:/afs/cern.ch/user/b/ballmond/private/CMSSW_10_1_11_patch1/src/HLTrigger/Configuration/test/raw_addedhltVBF.root'
    
	'file:root://cms-xrd-global.cern.ch//store/mc/RunIIAutumn18MiniAOD/VBFHToTauTau_M125_13TeV_powheg_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15_ext1-v1/00000/1ACE0760-BF84-3F47-A601-29022E50122E.root'
    )
    
)

process.demo = cms.EDAnalyzer('NtupleMaker'
     #, tracks = cms.untracked.InputTag('ctfWithMaterialTracks')
     , triggerResults = cms.untracked.InputTag("TriggerResults","","MYHLT")
     , triggerEvent = cms.untracked.InputTag("hltTriggerSummaryAOD","","MYHLT")

     , SkipEvent = cms.untracked.vstring('ProductNotFound')

     , needTriggers = cms.untracked.bool(False)
     , needTaus = cms.untracked.bool(True)
     , needJets = cms.untracked.bool(True)
     , development = cms.untracked.bool(False)
     , doGenParticles = cms.untracked.bool(False)

     , genParticleSrc = cms.untracked.InputTag("prunedGenParticles")
     , VtxLabel = cms.untracked.InputTag("offlineSlimmedPrimaryVertices")
     , rhoLabel = cms.untracked.InputTag("fixedGridRhoFastjetAll")
     , tauSrc = cms.untracked.InputTag("slimmedTaus")
     , ak4JetSrc = cms.untracked.InputTag("slimmedJets")
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("histo.root"),
    closeFileFast = cms.untracked.bool(True)
)


process.p = cms.Path(process.demo)
