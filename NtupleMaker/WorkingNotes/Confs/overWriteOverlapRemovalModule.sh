#!/bin/sh
FILE=$1

#https://unix.stackexchange.com/questions/303644/how-can-i-use-sed-or-ex-to-replace-a-block-multi-line-code-with-new-block-of-t
#sed -i '/marker1/,/marker2/c\
#New text 1\
#New text 2' filename

sed -i "/process.hltMatchedVBFIsoTauTwoPFJetsDoubleHpsDeepTauIsoPF25TauOverlapRemoval = cms./,/^)/c\
process.hltMatchedVBFIsoTauTwoPFJetsDoubleHpsDeepTauIsoPF25TauOverlapRemoval = cms.EDProducer( \"PFJetsTauCorrelationCondition\",\
\n    PFJetSrc = cms.InputTag( 'hltVBFIsoTauL1TLooseIDPFJetsMatching','TwoJets' ),\
\n    TauSrc = cms.InputTag( \"hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch\" ),\
\n    extraTauPtCut = cms.double( 45 ),\
\n    mjjMin = cms.double( 500 ),\
\n    Min_dR = cms.double( 0.5 )\
\n)" $FILE;

sed -i "/process.hltMatchedVBFIsoTauTwoPFJetsDoubleHpsDeepTauIsoPF25TauOverlapRemovalNoL2NN = cms./,/^)/c\
process.hltMatchedVBFIsoTauTwoPFJetsDoubleHpsDeepTauIsoPF25TauOverlapRemovalNoL2NN = cms.EDProducer( \"PFJetsTauCorrelationCondition\",\
\n    PFJetSrc = cms.InputTag( 'hltVBFIsoTauL1TLooseIDPFJetsMatching','TwoJets' ),\
\n    TauSrc = cms.InputTag( \"hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN\" ),\
\n    extraTauPtCut = cms.double( 45 ),\
\n    mjjMin = cms.double( 500 ),\
\n    Min_dR = cms.double( 0.5 )\
\n)" $FILE;

sed -i "/process.hltMatchedVBFIsoTauTwoPFJetsDoubleHpsTempLooseDeepTauIsoPF25TauOverlapRemoval = cms./,/^)/c\
process.hltMatchedVBFIsoTauTwoPFJetsDoubleHpsTempLooseDeepTauIsoPF25TauOverlapRemoval = cms.EDProducer( \"PFJetsTauCorrelationCondition\",\
\n    PFJetSrc = cms.InputTag( 'hltVBFIsoTauL1TLooseIDPFJetsMatching','TwoJets' ),\
\n    TauSrc = cms.InputTag( \"hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch\" ),\
\n    extraTauPtCut = cms.double( 45 ),\
\n    mjjMin = cms.double( 500 ),\
\n    Min_dR = cms.double( 0.5 )\
\n)" $FILE;

sed -i "/process.hltMatchedVBFIsoTauTwoPFJetsDoubleHpsTempLooseDeepTauIsoPF25TauOverlapRemovalNoL2NN = cms./,/^)/c\
process.hltMatchedVBFIsoTauTwoPFJetsDoubleHpsTempLooseDeepTauIsoPF25TauOverlapRemovalNoL2NN = cms.EDProducer( \"PFJetsTauCorrelationCondition\",\
\n    PFJetSrc = cms.InputTag( 'hltVBFIsoTauL1TLooseIDPFJetsMatching','TwoJets' ),\
\n    TauSrc = cms.InputTag( \"hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN\" ),\
\n    extraTauPtCut = cms.double( 45 ),\
\n    mjjMin = cms.double( 500 ),\
\n    Min_dR = cms.double( 0.5 )\
\n)" $FILE;
