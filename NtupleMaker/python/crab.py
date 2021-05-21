#Kyungwook's example crab file

from CRABClient.UserUtilities import config
config = config()

config.General.workArea = 'test'

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'hlt_raw_and_conf.py'
# config.JobType.maxJobRuntimeMin = 120

config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.outLFNDirBase = '/store/user/ballmond' #'/store/user/knam'

config.Data.ignoreLocality = True
config.Site.whitelist = ['T2_US_*']
config.JobType.maxMemoryMB = 4000

config.Site.storageSite = 'T3_US_FNALLPC' #'T3_KR_KNU'

if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand

    config.General.requestName = 'VBFHToTauTau_Raw_and_AOD_full_hlt_w_conf_05052121'
    config.Data.inputDataset = '/VBFHToTauTau_M125_13TeV_powheg_pythia8/RunIISpring18MiniAOD-NZSPU28to70_100X_upgrade2018_realistic_v10-v1/MINIAODSIM'
    config.Data.secondaryInputDataset = '/VBFHToTauTau_M125_13TeV_powheg_pythia8/RunIISpring18DR-NZSPU28to70_100X_upgrade2018_realistic_v10-v1/GEN-SIM-RAW'
    #config.Data.inputDataset = '/VBFHToTauTau_M125_13TeV_powheg_pythia8/RunIISpring18DR-NZSPU28to70_100X_upgrade2018_realistic_v10-v1/GEN-SIM-RAW'
 
    crabCommand('submit', config = config)
