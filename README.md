# VBFTau
If anything goes wrong, try the command 'cmsenv', then repeat whatever step previously failed. Sometimes logging out and logging back in to try a step also works. This happens because if you work in multiple cms-releases you can sometimes unknowingly change some local configuration variable.

# First we need a CMSSW release (currently using CMSSW_11_3_4_patch1, need to move up to CMSSW_12)

`cmsrel CMSSW_10_2_16_UL`

and cd into the 'src' directory
(alternatively: `scram pro -n MyWorkingAreaName CMSSW CMSSW_10_2_16_UL` allows you to name the CMSSW release directory if you like)

# Before downloading this repo, you need to download another repo which we add a correction file to directly.

First repo,

`git cms-addpkg L1Trigger/L1TGlobal`

Second repo, (ONLY NECESSARY FOR RELEASES PRIOR TO CMSSW_11)

`git cms-merge-topic -u cms-tau-pog:CMSSW_10_2_X_tau-pog_DeepTau2017v2p1_nanoAOD`

# Clone this repo. For now it's not on the master branch (FIX)

`git clone -b Braden https://github.com/Ror5ch/VBFTau.git`

Now we add the corrections. First correction,

```
cd VBF/NtupleMaker/corrections

cp CorrWithOverlapRemovalCondition.cc ../../../L1Trigger/L1TGlobal/src
```
this overwrites the L1 overlap removal algorithm with a hotfix made by Kyungwook (basically there's some error that experts are working on and we think the overlap removal algorithm is meant to work as Kyungwook has coded it instead. This will have an official fix sometime soon.)

Second correction, in the file

`L1TUtmTriggerMenuESProducer.cc in L1Trigger/L1TGlobal/plugins`

comment out this line

`edm::FileInPath f1("L1Trigger/L1TGlobal/data/Luminosity/startup/" + L1TriggerMenuFile);`

and replace this line

`m_L1TriggerMenuFile = f1.fullPath();`

with this line

`m_L1TriggerMenuFile = L1TriggerMenuFile;`

This changes where the L1 xml file is searched for. The necessary xml file should already 
be in the Python directory where you would submit a crab job from. This job is what needs that xml file.

# Finally, go to the top of this project and compile everything

```
cd ~/CMSSW_10_2_16_UL/src

scram b -j 8
```

You should be good to go now!

# Making an hlt configuration
Examples of configuration files for CMSSW_10_2_16_UL and CMSSW_11_3_4_patch1 are already available at hltConf_CMSSW10_L1Studies.py and hlt_NewVBF.py, respectively. The CMSSW10 configuration was made primarily to figure out an issue at L1. The CMSSW11 configuration is being used to ensure the fix works and to provide results for HLT efficiency and rate studies. Eventually, we'll need to repeat this for a configuration in CMSSW_12. All the info you need about how to make a new configuration is in the file `hltGetConfiguration.txt` in the `WorkingFiles` directory of this repo. 

# XML menu correction
The L1 seed we're working on, L1_DoubleJet35_Mass_Min450_IsoTau45_RmOvlp, didn't have a tau eta cut applied in its original expression for the L1 emulator (also the dR is 0p2; we've used 0p5 in all our studies)

`mass_inv_orm{JET35,JET35,TAU45[TAU-ISO_0xE]}[MASS_MIN_450,ORMDR_0p2]`

So we just add it by hand. You can download the latest and greatest L1 menu directly from here https://github.com/cms-l1-dpg/L1MenuRun3, under the official directory click "download" and then scp whatever you downloaded to wherever you need it. Alternatively, you could use wget like this

`wget https://raw.githubusercontent.com/cms-l1-dpg/L1MenuRun3/master/official/L1Menu_Collisions2020_v0_1_8/L1Menu_Collisions2020_v0_1_8.xml`

(Hint: wget is easier, just update the command for the most recent L1 menu)

Once you have the menu, the only thing that needs to modified is the expression for L1_DoubleJet35_Mass_Min450_IsoTau45_RmOvlp, like so

`mass_inv_orm{JET35,JET35,TAU45[TAU-ETA_2p13,TAU-ISO_0xE]}[MASS_MIN_450,ORMDR_0p5]`

We've added "TAU-ETA_2p13" next to the tau isolation requirement. This tau eta is a cut, so we need to add a "cut-block" to the xml file as well right after the tau iso cut, like so

```
    <cut>
      <name>TAU-ETA_2p13</name>
      <object>TAU</object>
      <type>ETA</type>
      <minimum>-2.1315000000000000E+00</minimum>
      <maximum>+2.1315000000000000E+00</maximum>
      <data/>
    </cut>
```

We've also changed the dR cone for overlap removal from 0p2 to 0p5, so we need to update the related cut (change the 2's to 5's like so)

```
    <cut>
      <name>ORMDR_0p5</name>
      <object/>
      <type>ORMDR</type>
      <minimum>+0.0000000000000000E+00</minimum>
      <maximum>+5.0000000000000001E-01</maximum>
      <data/>
    </cut>
```


Great, that's all for L1 XML!
