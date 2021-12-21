#!/bin/bash
COUNT=0
while read line
  do 
    if [ $COUNT -lt 500 ]
    then
      echo "$line"
      ((COUNT++))
    else
      :
    fi
done < $1
  
