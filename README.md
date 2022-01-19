#Updated for CMSSW_12_3_0_pre2
Fresh start.
`cmsrel CMSSW_12_3_0_pre2` or `scram pro -n MyCMSSW_12_3_0_pre2 CMSSW CMSSW_12_3_0_pre2`
`cd CMSSW_12_3_0_pre2/src`

`git cms-addpkg L1Trigger/L1TGlobal`
`git cms-addpkg HLTrigger/Configuration`
`git cms-addpkg RecoTauTag/HLTProducers`

`git clone -b Braden https://github.com/Ror5ch/VBFTau.git`

Now run this script to put some updated files in place.
Technically I should be pulling these from a git commit or library.
`cd NtupleMaker/WorkingFiles/CorrectionFiles`
`copyCorrectionFiles.sh`

Finally, build everything.
`cd ../`
`scram b -j 8`

#Timing
If you need to run timing and customize it, download this repo
`git clone --recursive https://gitlab.cern.ch/cms-tsg/steam/timing.git`
