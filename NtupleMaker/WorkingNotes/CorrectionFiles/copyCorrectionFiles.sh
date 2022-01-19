#!/bin/bash
cp TriggerMenuParser.cc ../../../../L1Trigger/L1TGlobal/plugins/;
cp L1TUtmTriggerMenuESProducer.cc ../../../../L1Trigger/L1TGlobal/plugins/;
cp CorrWithOverlapRemovalCondition.cc ../../../../L1Trigger/L1TGlobal/src/;

echo "TriggerMenuParser.cc diff after copy";
diff TriggerMenuParser.cc ../../../../L1Trigger/L1TGlobal/plugins/; 
echo "L1TUtmTriggerMenuESProducer.cc diff after copy";
diff L1TUtmTriggerMenuESProducer.cc ../../../../L1Trigger/L1TGlobal/plugins/;
echo "CorrWithOverlapRemovalCondition.cc diff after copy";
diff CorrWithOverlapRemovalCondition.cc ../../../../L1Trigger/L1TGlobal/plugins/;

echo "If the diff output is none, copy was successful";
