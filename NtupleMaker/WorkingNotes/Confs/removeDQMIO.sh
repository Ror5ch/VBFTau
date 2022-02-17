#!/bin/bash
FILE=$1

# use sed to remove lines referring to timing and multithreading 
# in place, match /pattern/ and delete(d) the next five lines (,+5)

sed -i -e '/# enable TrigReport, TimeReport and MultiThreading/,+5d' $FILE;
sed -i -e '/# load the DQMStore and DQMRootOutputModule/,+8d' $FILE;
