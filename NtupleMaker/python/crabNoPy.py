#stripped down crab submit file...

from CRABClient.UserUtilities import config
config = config()

config.General.workArea = 'test'

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'hltDummy_AllUnprescaledL1s.py'

config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.outLFNDirBase = '/store/user/ballmond' #'/store/user/knam'

config.Data.ignoreLocality = True
config.Site.whitelist = ['T1_US_FNAL', 'T2_FR_GRIF_LLR', 'T2_HU_Budapest', 'T3_US_FNALLPC']
config.JobType.maxJobRuntimeMin = 2000
config.JobType.maxMemoryMB = 4000
#config.JobType.inputFiles = ['L1Menu_Collisions2022_v0_1_1_2Jet1TauEtaRestrictionAddition.xml']
config.JobType.inputFiles = ['L1Menu_Collisions2022_v0_1_1_modified_updated_Nov30.xml']

#config.Data.runRange = '321755,323725,323755,323790,323841,323940,323976,323978,324021,324077,324201,324237,324245,324293,324315,324420,324747,324785,324835,324897,324970,324980,324997,325022,325057,325097-325099'
config.Data.runRange = '323755'

config.Site.storageSite = 'T3_US_FNALLPC'

#for i in range(1,9): 
config.General.requestName = 'EZB1_UnprescaledL1Repack'
config.Data.inputDataset = '/EphemeralZeroBias1/Run2018D-v1/RAW'
    
    # newest ggH
#config.Data.inputDataset = '/GluGluHToTauTau_M-125_TuneCP5_14TeV-powheg-pythia8/Run3Winter21DRMiniAOD-FlatPU30to80FEVT_112X_mcRun3_2021_realistic_v16-v1/MINIAODSIM'
#config.Data.secondaryInputDataset = '/GluGluHToTauTau_M-125_TuneCP5_14TeV-powheg-pythia8/Run3Winter21DRMiniAOD-FlatPU30to80FEVT_112X_mcRun3_2021_realistic_v16-v1/GEN-SIM-DIGI-RAW'
    # newest VBF
#config.Data.inputDataset = '/VBFHToTauTau_M125_TuneCP5_14TeV-powheg-pythia8/Run3Winter21DRMiniAOD-FlatPU30to80FEVT_112X_mcRun3_2021_realistic_v16-v1/MINIAODSIM'
#config.Data.secondaryInputDataset = '/VBFHToTauTau_M125_TuneCP5_14TeV-powheg-pythia8/Run3Winter21DRMiniAOD-FlatPU30to80FEVT_112X_mcRun3_2021_realistic_v16-v1/GEN-SIM-DIGI-RAW'
