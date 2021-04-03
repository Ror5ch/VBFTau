import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:/afs/cern.ch/user/b/ballmond/private/CMSSW_10_1_11_patch1/src/HLTrigger/Configuration/test/addedhltVBF.root'
    )
)

process.demo = cms.EDAnalyzer('NtupleMaker'
     , tracks = cms.untracked.InputTag('ctfWithMaterialTracks')
)


process.p = cms.Path(process.demo)
