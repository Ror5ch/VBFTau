# VBFTau
If anything goes wrong, try the command 'cmsenv', then repeat whatever step previously failed

# First we need a CMSSW release

`cmsrel CMSSW_10_2_16_UL`

and cd into the 'src' directory
(alternatively: `scram pro -n MyWorkingAreaName CMSSW CMSSW_10_2_16_UL` allows you to name the CMSSW release directory if you like)

# Before downloading this repo, you need to download two other repos which we add two correction files to directly.

First repo,

`git cms-addpkg L1Trigger/L1TGlobal`

Second repo,

`git cms-merge-topic -u cms-tau-pog:CMSSW_10_2_X_tau-pog_DeepTau2017v2p1_nanoAOD`

# Clone this repo. For now it's not on the master branch (FIX)

`git clone -b Braden https://github.com/Ror5ch/VBFTau.git`

Now we add the corrections. First correction,

```
cd VBF/NtupleMaker/corrections

cp CorrWithOverlapRemovalCondition.cc ../../../L1Trigger/L1TGlobal/src
```

this protects against a specific type of crash in L1 overlap removal

Second correction, (still in directory 'VBF/NtupleMaker/corrections')

`cp L1TUtmTriggerMenuESProducer.cc ../../../L1Trigger/L1TGlobal/plugins`

This changes where the L1 xml file is searched for. The necessary xml file should already 
be in the Python directory where you would submit a crab job from. This job is what needs that xml file.

Third correction, (still in directory 'VBF/NtupleMaker/corrections')

`cp L1TUtmTriggerMenuESProducer.cc ../../../L1Trigger/L1TGlobal/plugins`

---remember why we need this

# Finally, go to the top of this project and compile everything

```
cd ~/CMSSW_10_2_16_UL/src

scram b -j 8
```

You should be good to go now!
