#Kyungwook's example crab file

import sys

from CRABClient.UserUtilities import config
config = config()

config.General.workArea = 'test'

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'ditau_and_vbf.py'
# config.JobType.maxJobRuntimeMin = 120

config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.outLFNDirBase = '/store/user/ballmond' #'/store/user/knam'

config.Data.ignoreLocality = True
#config.Site.whitelist = ['T2_US_*', 'T2_RU_JINR', 'T1_RU_JINR']
#config.Site.whitelist = ['T3_US_FNALLPC']
config.Site.whitelist = ['T2_US_*']
#config.Site.ignoreGlobalBlacklist = True
config.JobType.maxJobRuntimeMin = 2000
config.JobType.maxMemoryMB = 4000
#config.JobType.numCores = 4
config.JobType.inputFiles = ['L1Menu_Collisions2018_v1_0_0-d1_fixed.xml']

config.Site.storageSite = 'T3_US_FNALLPC' #'T3_KR_KNU'

if __name__ == '__main__':

    print("Submission checks...")
    print("Have you compiled your plugins recently?")
    yesno1 = raw_input('y/n? ')
    print("Have you added/compiled the 2 correction files?")
    yesno2 = raw_input('y/n? ')
    print("Have you added the fixed xml file to the crab submission?")
    yesno3 = raw_input('y/n? ')
    print("Are all variables in your conffile set to true?")
    yesno4 = raw_input('y/n? ')
    print("Did you remove the OR conditions on L1 old trigger in hlt paths?")
    yesno5 = raw_input('y/n? ')
    print("Did you add the L1 ditau trigger?")
    yesno6 = raw_input('y/n? ')
    print("Did you remove the OR conditions on L1 ditau trigger in hlt paths?")
    yesno7 = raw_input('y/n? ')
    print("Did you reduce the leading tau cut to 45 in your hlt menu?")
    yesno8 = raw_input('y/n? ')

    if (yesno1 == 'n' or yesno2 == 'n' or yesno3 == 'n' or yesno4 == 'n' or yesno5 == 'n' or yesno6 == 'n' or yesno7 == 'n' or yesno8 == 'n'\
	or yesno1 == '' or yesno2 == '' or yesno3 == '' or yesno4 == '' or yesno5 == '' or yesno6 == '' or yesno7 == '' or yesno8 == ''):
	print("Well, go fix that!")
	sys.exit()

    print("Remember to check your branches/run selection code as soon as one job is finished!!!")

    from CRABAPI.RawCommand import crabCommand

    config.General.requestName = 'VBFHToTauTau_DitauAndVBF_4520Tau_CorrectedEta'
    config.Data.inputDataset = '/VBFHToTauTau_M125_13TeV_powheg_pythia8/RunIISpring18MiniAOD-NZSPU28to70_100X_upgrade2018_realistic_v10-v1/MINIAODSIM'
    config.Data.secondaryInputDataset = '/VBFHToTauTau_M125_13TeV_powheg_pythia8/RunIISpring18DR-NZSPU28to70_100X_upgrade2018_realistic_v10-v1/GEN-SIM-RAW'
    #config.Data.inputDataset = '/VBFHToTauTau_M125_13TeV_powheg_pythia8/RunIISpring18DR-NZSPU28to70_100X_upgrade2018_realistic_v10-v1/GEN-SIM-RAW'
 
    crabCommand('submit', config = config)
