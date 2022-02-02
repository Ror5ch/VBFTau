#!/bin/bash
FIRST=1
while read line
  do 
    if [ $FIRST == 1 ]
    then
      echo -n "$line"
      FIRST=2
    else
      echo -n ",$line"
    fi
done < EZB3Jaime.txt
