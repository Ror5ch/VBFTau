# doesn't work when testing on lxplus
# instructions from this twiki at the bottom
# https://twiki.cern.ch/twiki/bin/view/CMSPublic/CRAB3FAQ#Doing_lumi_mask_arithmetics
from WMCore.DataStructs.LumiList import LumiList

originalLumiList1 = LumiList(filename='normtag_PHYSICS.json')
originalLumiList2 = LumiList(filename='dummyAllLumi.json')
newLumiList = originalLumiList1 & originalLumiList2
newLumiList.writeJSON('my_new_lumi_mask.json')
