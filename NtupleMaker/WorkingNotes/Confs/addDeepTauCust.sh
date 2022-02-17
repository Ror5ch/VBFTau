#!/bin/bash
FILE=$1

echo "from HLTrigger.Configuration.customizeHLTforPatatrack import customizeHLTforPatatrackTriplets
process = customizeHLTforPatatrackTriplets(process)
process.HLTL2TauTagNNSequence._tasks.add(process.HLTDoLocalPixelTask)
process.HLTL2TauTagNNSequence._tasks.add(process.HLTRecoPixelTracksTask)
process.HLTL2TauTagNNSequence._tasks.add(process.HLTRecopixelvertexingTask)" >> $FILE;

