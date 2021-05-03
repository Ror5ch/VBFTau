import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('file:root://cms-xrd-global.cern.ch//store/mc/RunIIAutumn18MiniAOD/VBFHToTauTau_M125_13TeV_powheg_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15_ext1-v1/00000/1ACE0760-BF84-3F47-A601-29022E50122E.root')
)
process.CondDB = cms.PSet(
    DBParameters = cms.PSet(
        authenticationPath = cms.untracked.string(''),
        authenticationSystem = cms.untracked.int32(0),
        messageLevel = cms.untracked.int32(0),
        security = cms.untracked.string('')
    ),
    connect = cms.string('')
)

process.CondDBTauConnection = cms.PSet(
    DBParameters = cms.PSet(
        authenticationPath = cms.untracked.string(''),
        authenticationSystem = cms.untracked.int32(0),
        messageLevel = cms.untracked.int32(0),
        security = cms.untracked.string('')
    ),
    connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS')
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(200)
)

process.deepTau2017v2p1 = cms.EDProducer("DeepTauId",
    VSeWP = cms.PSet(
        Loose = cms.string('0.6815435'),
        Medium = cms.string('0.8847544'),
        Tight = cms.string('0.9675541'),
        VLoose = cms.string('0.362813'),
        VTight = cms.string('0.9859251'),
        VVLoose = cms.string('0.1686942'),
        VVTight = cms.string('0.9928449'),
        VVVLoose = cms.string('0.0630386')
    ),
    VSjetWP = cms.PSet(
        Loose = cms.string('0.7848675'),
        Medium = cms.string('0.8834768'),
        Tight = cms.string('0.9308689'),
        VLoose = cms.string('0.5983682'),
        VTight = cms.string('0.9573137'),
        VVLoose = cms.string('0.4249705'),
        VVTight = cms.string('0.9733927'),
        VVVLoose = cms.string('0.2599605')
    ),
    VSmuWP = cms.PSet(
        Loose = cms.string('0.2158633'),
        Medium = cms.string('0.5551894'),
        Tight = cms.string('0.8754835'),
        VLoose = cms.string('0.1058354')
    ),
    debug_level = cms.int32(0),
    disable_dxy_pca = cms.bool(True),
    electrons = cms.InputTag("slimmedElectrons"),
    graph_file = cms.vstring(
        'core:RecoTauTag/TrainingFiles/data/DeepTauId/deepTau_2017v2p6_e6_core.pb', 
        'inner:RecoTauTag/TrainingFiles/data/DeepTauId/deepTau_2017v2p6_e6_inner.pb', 
        'outer:RecoTauTag/TrainingFiles/data/DeepTauId/deepTau_2017v2p6_e6_outer.pb'
    ),
    mem_mapped = cms.bool(True),
    muons = cms.InputTag("slimmedMuons"),
    pfcands = cms.InputTag("packedPFCandidates"),
    rho = cms.InputTag("fixedGridRhoAll"),
    taus = cms.InputTag("slimmedTaus"),
    version = cms.uint32(2),
    vertices = cms.InputTag("offlineSlimmedPrimaryVertices")
)


process.slimmedTausNewID = cms.EDProducer("PATTauIDEmbedder",
    src = cms.InputTag("slimmedTaus"),
    tauIDSources = cms.PSet(
        byDeepTau2017v2p1VSeraw = cms.InputTag("deepTau2017v2p1","VSe"),
        byDeepTau2017v2p1VSjetraw = cms.InputTag("deepTau2017v2p1","VSjet"),
        byDeepTau2017v2p1VSmuraw = cms.InputTag("deepTau2017v2p1","VSmu"),
        byLooseDeepTau2017v2p1VSe = cms.InputTag("deepTau2017v2p1","VSeLoose"),
        byLooseDeepTau2017v2p1VSjet = cms.InputTag("deepTau2017v2p1","VSjetLoose"),
        byLooseDeepTau2017v2p1VSmu = cms.InputTag("deepTau2017v2p1","VSmuLoose"),
        byMediumDeepTau2017v2p1VSe = cms.InputTag("deepTau2017v2p1","VSeMedium"),
        byMediumDeepTau2017v2p1VSjet = cms.InputTag("deepTau2017v2p1","VSjetMedium"),
        byMediumDeepTau2017v2p1VSmu = cms.InputTag("deepTau2017v2p1","VSmuMedium"),
        byTightDeepTau2017v2p1VSe = cms.InputTag("deepTau2017v2p1","VSeTight"),
        byTightDeepTau2017v2p1VSjet = cms.InputTag("deepTau2017v2p1","VSjetTight"),
        byTightDeepTau2017v2p1VSmu = cms.InputTag("deepTau2017v2p1","VSmuTight"),
        byVLooseDeepTau2017v2p1VSe = cms.InputTag("deepTau2017v2p1","VSeVLoose"),
        byVLooseDeepTau2017v2p1VSjet = cms.InputTag("deepTau2017v2p1","VSjetVLoose"),
        byVLooseDeepTau2017v2p1VSmu = cms.InputTag("deepTau2017v2p1","VSmuVLoose"),
        byVTightDeepTau2017v2p1VSe = cms.InputTag("deepTau2017v2p1","VSeVTight"),
        byVTightDeepTau2017v2p1VSjet = cms.InputTag("deepTau2017v2p1","VSjetVTight"),
        byVVLooseDeepTau2017v2p1VSe = cms.InputTag("deepTau2017v2p1","VSeVVLoose"),
        byVVLooseDeepTau2017v2p1VSjet = cms.InputTag("deepTau2017v2p1","VSjetVVLoose"),
        byVVTightDeepTau2017v2p1VSe = cms.InputTag("deepTau2017v2p1","VSeVVTight"),
        byVVTightDeepTau2017v2p1VSjet = cms.InputTag("deepTau2017v2p1","VSjetVVTight"),
        byVVVLooseDeepTau2017v2p1VSe = cms.InputTag("deepTau2017v2p1","VSeVVVLoose"),
        byVVVLooseDeepTau2017v2p1VSjet = cms.InputTag("deepTau2017v2p1","VSjetVVVLoose")
    )
)


process.demo = cms.EDAnalyzer("NtupleMaker",
    SkipEvent = cms.untracked.vstring('ProductNotFound'),
    VtxLabel = cms.untracked.InputTag("offlineSlimmedPrimaryVertices"),
    ak4JetSrc = cms.untracked.InputTag("slimmedJets"),
    development = cms.untracked.bool(False),
    doGenParticles = cms.untracked.bool(False),
    genParticleSrc = cms.untracked.InputTag("prunedGenParticles"),
    needJets = cms.untracked.bool(True),
    needTaus = cms.untracked.bool(True),
    needTriggers = cms.untracked.bool(False),
    rhoLabel = cms.untracked.InputTag("fixedGridRhoFastjetAll"),
    tauSrc = cms.untracked.InputTag("slimmedTausNewID"),
    triggerEvent = cms.untracked.InputTag("hltTriggerSummaryAOD","","MYHLT"),
    triggerResults = cms.untracked.InputTag("TriggerResults","","MYHLT")
)


process.MessageLogger = cms.Service("MessageLogger",
    FrameworkJobReport = cms.untracked.PSet(
        FwkJob = cms.untracked.PSet(
            limit = cms.untracked.int32(10000000),
            optionalPSet = cms.untracked.bool(True)
        ),
        default = cms.untracked.PSet(
            limit = cms.untracked.int32(0)
        ),
        optionalPSet = cms.untracked.bool(True)
    ),
    categories = cms.untracked.vstring(
        'FwkJob', 
        'FwkReport', 
        'FwkSummary', 
        'Root_NoDictionary'
    ),
    cerr = cms.untracked.PSet(
        FwkJob = cms.untracked.PSet(
            limit = cms.untracked.int32(0),
            optionalPSet = cms.untracked.bool(True)
        ),
        FwkReport = cms.untracked.PSet(
            limit = cms.untracked.int32(10000000),
            optionalPSet = cms.untracked.bool(True),
            reportEvery = cms.untracked.int32(1)
        ),
        FwkSummary = cms.untracked.PSet(
            limit = cms.untracked.int32(10000000),
            optionalPSet = cms.untracked.bool(True),
            reportEvery = cms.untracked.int32(1)
        ),
        INFO = cms.untracked.PSet(
            limit = cms.untracked.int32(0)
        ),
        Root_NoDictionary = cms.untracked.PSet(
            limit = cms.untracked.int32(0),
            optionalPSet = cms.untracked.bool(True)
        ),
        default = cms.untracked.PSet(
            limit = cms.untracked.int32(10000000)
        ),
        noTimeStamps = cms.untracked.bool(False),
        optionalPSet = cms.untracked.bool(True),
        threshold = cms.untracked.string('INFO')
    ),
    cerr_stats = cms.untracked.PSet(
        optionalPSet = cms.untracked.bool(True),
        output = cms.untracked.string('cerr'),
        threshold = cms.untracked.string('WARNING')
    ),
    cout = cms.untracked.PSet(
        placeholder = cms.untracked.bool(True)
    ),
    debugModules = cms.untracked.vstring(),
    debugs = cms.untracked.PSet(
        placeholder = cms.untracked.bool(True)
    ),
    default = cms.untracked.PSet(

    ),
    destinations = cms.untracked.vstring(
        'warnings', 
        'errors', 
        'infos', 
        'debugs', 
        'cout', 
        'cerr'
    ),
    errors = cms.untracked.PSet(
        placeholder = cms.untracked.bool(True)
    ),
    fwkJobReports = cms.untracked.vstring('FrameworkJobReport'),
    infos = cms.untracked.PSet(
        Root_NoDictionary = cms.untracked.PSet(
            limit = cms.untracked.int32(0),
            optionalPSet = cms.untracked.bool(True)
        ),
        optionalPSet = cms.untracked.bool(True),
        placeholder = cms.untracked.bool(True)
    ),
    statistics = cms.untracked.vstring('cerr_stats'),
    suppressDebug = cms.untracked.vstring(),
    suppressInfo = cms.untracked.vstring(),
    suppressWarning = cms.untracked.vstring(),
    warnings = cms.untracked.PSet(
        placeholder = cms.untracked.bool(True)
    )
)


process.TFileService = cms.Service("TFileService",
    closeFileFast = cms.untracked.bool(True),
    fileName = cms.string('histo.root')
)


process.loadRecoTauTagMVAsFromPrepDB = cms.ESSource("PoolDBESSource",
    DBParameters = cms.PSet(
        authenticationPath = cms.untracked.string(''),
        authenticationSystem = cms.untracked.int32(0),
        messageLevel = cms.untracked.int32(0),
        security = cms.untracked.string('')
    ),
    DumpStat = cms.untracked.bool(False),
    ReconnectEachRun = cms.untracked.bool(False),
    RefreshAlways = cms.untracked.bool(False),
    RefreshEachRun = cms.untracked.bool(False),
    RefreshOpenIOVs = cms.untracked.bool(False),
    connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS'),
    globaltag = cms.string(''),
    pfnPostfix = cms.untracked.string(''),
    pfnPrefix = cms.untracked.string(''),
    snapshotTime = cms.string(''),
    toGet = cms.VPSet( (
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAoldDMwoLTv1'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAoldDMwoLTv1')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAoldDMwoLTv1_WPEff50'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAoldDMwoLTv1_WPEff50')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAoldDMwoLTv1_WPEff70'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAoldDMwoLTv1_WPEff70')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAoldDMwoLTv1_WPEff60'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAoldDMwoLTv1_WPEff60')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAoldDMwoLTv1_WPEff80'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAoldDMwoLTv1_WPEff80')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAoldDMwoLTv1_WPEff40'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAoldDMwoLTv1_WPEff40')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAoldDMwoLTv1_WPEff90'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAoldDMwoLTv1_WPEff90')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAoldDMwoLTv1_mvaOutput_normalization'),
            record = cms.string('PhysicsTFormulaPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAoldDMwoLTv1_mvaOutput_normalization')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAnewDMwLTv1'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAnewDMwLTv1')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAnewDMwLTv1_WPEff50'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAnewDMwLTv1_WPEff50')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAnewDMwLTv1_WPEff70'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAnewDMwLTv1_WPEff70')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAnewDMwLTv1_WPEff60'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAnewDMwLTv1_WPEff60')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAnewDMwLTv1_WPEff80'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAnewDMwLTv1_WPEff80')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAnewDMwLTv1_WPEff40'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAnewDMwLTv1_WPEff40')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAnewDMwLTv1_WPEff90'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAnewDMwLTv1_WPEff90')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAnewDMwLTv1_mvaOutput_normalization'),
            record = cms.string('PhysicsTFormulaPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAnewDMwLTv1_mvaOutput_normalization')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAoldDMwLTv1'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAoldDMwLTv1')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAoldDMwLTv1_WPEff50'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAoldDMwLTv1_WPEff50')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAoldDMwLTv1_WPEff70'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAoldDMwLTv1_WPEff70')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAoldDMwLTv1_WPEff60'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAoldDMwLTv1_WPEff60')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAoldDMwLTv1_WPEff80'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAoldDMwLTv1_WPEff80')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAoldDMwLTv1_WPEff40'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAoldDMwLTv1_WPEff40')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAoldDMwLTv1_WPEff90'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAoldDMwLTv1_WPEff90')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAoldDMwLTv1_mvaOutput_normalization'),
            record = cms.string('PhysicsTFormulaPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAoldDMwLTv1_mvaOutput_normalization')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAnewDMwoLTv1'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAnewDMwoLTv1')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAnewDMwoLTv1_WPEff50'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAnewDMwoLTv1_WPEff50')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAnewDMwoLTv1_WPEff70'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAnewDMwoLTv1_WPEff70')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAnewDMwoLTv1_WPEff60'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAnewDMwoLTv1_WPEff60')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAnewDMwoLTv1_WPEff80'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAnewDMwoLTv1_WPEff80')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAnewDMwoLTv1_WPEff40'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAnewDMwoLTv1_WPEff40')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAnewDMwoLTv1_WPEff90'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAnewDMwoLTv1_WPEff90')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAnewDMwoLTv1_mvaOutput_normalization'),
            record = cms.string('PhysicsTFormulaPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAnewDMwoLTv1_mvaOutput_normalization')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVADBoldDMwLTv1'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_tauIdMVADBoldDMwLTv1')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVADBoldDMwLTv1_WPEff50'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVADBoldDMwLTv1_WPEff50')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVADBoldDMwLTv1_WPEff70'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVADBoldDMwLTv1_WPEff70')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVADBoldDMwLTv1_WPEff60'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVADBoldDMwLTv1_WPEff60')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVADBoldDMwLTv1_WPEff80'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVADBoldDMwLTv1_WPEff80')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVADBoldDMwLTv1_WPEff40'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVADBoldDMwLTv1_WPEff40')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVADBoldDMwLTv1_WPEff90'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVADBoldDMwLTv1_WPEff90')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVADBoldDMwLTv1_mvaOutput_normalization'),
            record = cms.string('PhysicsTFormulaPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVADBoldDMwLTv1_mvaOutput_normalization')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVADBnewDMwLTv1'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_tauIdMVADBnewDMwLTv1')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVADBnewDMwLTv1_WPEff50'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVADBnewDMwLTv1_WPEff50')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVADBnewDMwLTv1_WPEff70'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVADBnewDMwLTv1_WPEff70')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVADBnewDMwLTv1_WPEff60'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVADBnewDMwLTv1_WPEff60')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVADBnewDMwLTv1_WPEff80'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVADBnewDMwLTv1_WPEff80')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVADBnewDMwLTv1_WPEff40'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVADBnewDMwLTv1_WPEff40')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVADBnewDMwLTv1_WPEff90'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVADBnewDMwLTv1_WPEff90')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVADBnewDMwLTv1_mvaOutput_normalization'),
            record = cms.string('PhysicsTFormulaPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVADBnewDMwLTv1_mvaOutput_normalization')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAPWoldDMwLTv1'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAPWoldDMwLTv1')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAPWoldDMwLTv1_WPEff50'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAPWoldDMwLTv1_WPEff50')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAPWoldDMwLTv1_WPEff70'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAPWoldDMwLTv1_WPEff70')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAPWoldDMwLTv1_WPEff60'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAPWoldDMwLTv1_WPEff60')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAPWoldDMwLTv1_WPEff80'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAPWoldDMwLTv1_WPEff80')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAPWoldDMwLTv1_WPEff40'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAPWoldDMwLTv1_WPEff40')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAPWoldDMwLTv1_WPEff90'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAPWoldDMwLTv1_WPEff90')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAPWoldDMwLTv1_mvaOutput_normalization'),
            record = cms.string('PhysicsTFormulaPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAPWoldDMwLTv1_mvaOutput_normalization')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAPWnewDMwLTv1'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAPWnewDMwLTv1')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAPWnewDMwLTv1_WPEff50'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAPWnewDMwLTv1_WPEff50')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAPWnewDMwLTv1_WPEff70'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAPWnewDMwLTv1_WPEff70')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAPWnewDMwLTv1_WPEff60'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAPWnewDMwLTv1_WPEff60')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAPWnewDMwLTv1_WPEff80'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAPWnewDMwLTv1_WPEff80')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAPWnewDMwLTv1_WPEff40'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAPWnewDMwLTv1_WPEff40')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAPWnewDMwLTv1_WPEff90'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAPWnewDMwLTv1_WPEff90')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAPWnewDMwLTv1_mvaOutput_normalization'),
            record = cms.string('PhysicsTFormulaPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAPWnewDMwLTv1_mvaOutput_normalization')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAPWdR03oldDMwLTv1'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAPWdR03oldDMwLTv1')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAPWdR03oldDMwLTv1_WPEff50'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAPWdR03oldDMwLTv1_WPEff50')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAPWdR03oldDMwLTv1_WPEff70'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAPWdR03oldDMwLTv1_WPEff70')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAPWdR03oldDMwLTv1_WPEff60'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAPWdR03oldDMwLTv1_WPEff60')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAPWdR03oldDMwLTv1_WPEff80'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAPWdR03oldDMwLTv1_WPEff80')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAPWdR03oldDMwLTv1_WPEff40'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAPWdR03oldDMwLTv1_WPEff40')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAPWdR03oldDMwLTv1_WPEff90'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAPWdR03oldDMwLTv1_WPEff90')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAPWdR03oldDMwLTv1_mvaOutput_normalization'),
            record = cms.string('PhysicsTFormulaPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAPWdR03oldDMwLTv1_mvaOutput_normalization')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVADBdR03oldDMwLTv1'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_tauIdMVADBdR03oldDMwLTv1')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVADBdR03oldDMwLTv1_WPEff50'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVADBdR03oldDMwLTv1_WPEff50')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVADBdR03oldDMwLTv1_WPEff70'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVADBdR03oldDMwLTv1_WPEff70')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVADBdR03oldDMwLTv1_WPEff60'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVADBdR03oldDMwLTv1_WPEff60')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVADBdR03oldDMwLTv1_WPEff80'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVADBdR03oldDMwLTv1_WPEff80')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVADBdR03oldDMwLTv1_WPEff40'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVADBdR03oldDMwLTv1_WPEff40')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVADBdR03oldDMwLTv1_WPEff90'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVADBdR03oldDMwLTv1_WPEff90')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVADBdR03oldDMwLTv1_mvaOutput_normalization'),
            record = cms.string('PhysicsTFormulaPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVADBdR03oldDMwLTv1_mvaOutput_normalization')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBnewDMwLT2016v1'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBnewDMwLT2016v1')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBnewDMwLT2016v1_WPEff50'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBnewDMwLT2016v1_WPEff50')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBnewDMwLT2016v1_WPEff70'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBnewDMwLT2016v1_WPEff70')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBnewDMwLT2016v1_WPEff60'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBnewDMwLT2016v1_WPEff60')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBnewDMwLT2016v1_WPEff80'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBnewDMwLT2016v1_WPEff80')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBnewDMwLT2016v1_WPEff40'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBnewDMwLT2016v1_WPEff40')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBnewDMwLT2016v1_WPEff90'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBnewDMwLT2016v1_WPEff90')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBnewDMwLT2016v1_mvaOutput_normalization'),
            record = cms.string('PhysicsTFormulaPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBnewDMwLT2016v1_mvaOutput_normalization')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2016v1'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2016v1')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2016v1_WPEff50'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2016v1_WPEff50')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2016v1_WPEff70'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2016v1_WPEff70')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2016v1_WPEff60'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2016v1_WPEff60')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2016v1_WPEff80'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2016v1_WPEff80')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2016v1_WPEff40'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2016v1_WPEff40')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2016v1_WPEff90'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2016v1_WPEff90')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2016v1_mvaOutput_normalization'),
            record = cms.string('PhysicsTFormulaPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2016v1_mvaOutput_normalization')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v1'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v1')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v1_WPEff50'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v1_WPEff50')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v1_WPEff70'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v1_WPEff70')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v1_WPEff60'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v1_WPEff60')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v1_WPEff80'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v1_WPEff80')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v1_WPEff95'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v1_WPEff95')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v1_WPEff40'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v1_WPEff40')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v1_WPEff90'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v1_WPEff90')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v1_mvaOutput_normalization'),
            record = cms.string('PhysicsTFormulaPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v1_mvaOutput_normalization')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBoldDMdR0p3wLT2017v2'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBoldDMdR0p3wLT2017v2')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBoldDMdR0p3wLT2017v2_WPEff50'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBoldDMdR0p3wLT2017v2_WPEff50')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBoldDMdR0p3wLT2017v2_WPEff70'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBoldDMdR0p3wLT2017v2_WPEff70')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBoldDMdR0p3wLT2017v2_WPEff60'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBoldDMdR0p3wLT2017v2_WPEff60')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBoldDMdR0p3wLT2017v2_WPEff80'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBoldDMdR0p3wLT2017v2_WPEff80')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBoldDMdR0p3wLT2017v2_WPEff95'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBoldDMdR0p3wLT2017v2_WPEff95')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBoldDMdR0p3wLT2017v2_WPEff40'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBoldDMdR0p3wLT2017v2_WPEff40')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBoldDMdR0p3wLT2017v2_WPEff90'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBoldDMdR0p3wLT2017v2_WPEff90')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBoldDMdR0p3wLT2017v2_mvaOutput_normalization'),
            record = cms.string('PhysicsTFormulaPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBoldDMdR0p3wLT2017v2_mvaOutput_normalization')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBnewDMwLT2017v2'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBnewDMwLT2017v2')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBnewDMwLT2017v2_WPEff50'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBnewDMwLT2017v2_WPEff50')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBnewDMwLT2017v2_WPEff70'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBnewDMwLT2017v2_WPEff70')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBnewDMwLT2017v2_WPEff60'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBnewDMwLT2017v2_WPEff60')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBnewDMwLT2017v2_WPEff80'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBnewDMwLT2017v2_WPEff80')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBnewDMwLT2017v2_WPEff95'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBnewDMwLT2017v2_WPEff95')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBnewDMwLT2017v2_WPEff40'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBnewDMwLT2017v2_WPEff40')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBnewDMwLT2017v2_WPEff90'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBnewDMwLT2017v2_WPEff90')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBnewDMwLT2017v2_mvaOutput_normalization'),
            record = cms.string('PhysicsTFormulaPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBnewDMwLT2017v2_mvaOutput_normalization')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v2'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v2')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v2_WPEff50'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v2_WPEff50')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v2_WPEff70'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v2_WPEff70')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v2_WPEff60'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v2_WPEff60')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v2_WPEff80'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v2_WPEff80')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v2_WPEff95'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v2_WPEff95')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v2_WPEff40'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v2_WPEff40')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v2_WPEff90'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v2_WPEff90')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v2_mvaOutput_normalization'),
            record = cms.string('PhysicsTFormulaPayloadRcd'),
            tag = cms.string('RecoTauTag_tauIdMVAIsoDBoldDMwLT2017v2_mvaOutput_normalization')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwGSF_EC'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwGSF_EC')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwGSF_EC_WPeff99'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwGSF_EC_WPeff99')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwGSF_EC_WPeff96'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwGSF_EC_WPeff96')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwGSF_EC_WPeff91'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwGSF_EC_WPeff91')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwGSF_EC_WPeff85'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwGSF_EC_WPeff85')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwGSF_EC_WPeff79'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwGSF_EC_WPeff79')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwoGSF_EC'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwoGSF_EC')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwoGSF_EC_WPeff99'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwoGSF_EC_WPeff99')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwoGSF_EC_WPeff96'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwoGSF_EC_WPeff96')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwoGSF_EC_WPeff91'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwoGSF_EC_WPeff91')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwoGSF_EC_WPeff85'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwoGSF_EC_WPeff85')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwoGSF_EC_WPeff79'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwoGSF_EC_WPeff79')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwGSF_EC'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwGSF_EC')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwGSF_EC_WPeff99'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwGSF_EC_WPeff99')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwGSF_EC_WPeff96'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwGSF_EC_WPeff96')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwGSF_EC_WPeff91'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwGSF_EC_WPeff91')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwGSF_EC_WPeff85'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwGSF_EC_WPeff85')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwGSF_EC_WPeff79'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwGSF_EC_WPeff79')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwoGSF_EC'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwoGSF_EC')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwoGSF_EC_WPeff99'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwoGSF_EC_WPeff99')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwoGSF_EC_WPeff96'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwoGSF_EC_WPeff96')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwoGSF_EC_WPeff91'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwoGSF_EC_WPeff91')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwoGSF_EC_WPeff85'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwoGSF_EC_WPeff85')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwoGSF_EC_WPeff79'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwoGSF_EC_WPeff79')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwGSF_EC'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwGSF_EC')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwGSF_EC_WPeff99'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwGSF_EC_WPeff99')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwGSF_EC_WPeff96'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwGSF_EC_WPeff96')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwGSF_EC_WPeff91'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwGSF_EC_WPeff91')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwGSF_EC_WPeff85'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwGSF_EC_WPeff85')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwGSF_EC_WPeff79'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwGSF_EC_WPeff79')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwoGSF_EC'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwoGSF_EC')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwoGSF_EC_WPeff99'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwoGSF_EC_WPeff99')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwoGSF_EC_WPeff96'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwoGSF_EC_WPeff96')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwoGSF_EC_WPeff91'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwoGSF_EC_WPeff91')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwoGSF_EC_WPeff85'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwoGSF_EC_WPeff85')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwoGSF_EC_WPeff79'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwoGSF_EC_WPeff79')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwGSF_BL'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwGSF_BL')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwGSF_BL_WPeff99'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwGSF_BL_WPeff99')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwGSF_BL_WPeff96'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwGSF_BL_WPeff96')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwGSF_BL_WPeff91'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwGSF_BL_WPeff91')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwGSF_BL_WPeff85'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwGSF_BL_WPeff85')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwGSF_BL_WPeff79'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwGSF_BL_WPeff79')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwoGSF_BL'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwoGSF_BL')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwoGSF_BL_WPeff99'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwoGSF_BL_WPeff99')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwoGSF_BL_WPeff96'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwoGSF_BL_WPeff96')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwoGSF_BL_WPeff91'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwoGSF_BL_WPeff91')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwoGSF_BL_WPeff85'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwoGSF_BL_WPeff85')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwoGSF_BL_WPeff79'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwoGSF_BL_WPeff79')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwGSF_BL'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwGSF_BL')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwGSF_BL_WPeff99'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwGSF_BL_WPeff99')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwGSF_BL_WPeff96'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwGSF_BL_WPeff96')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwGSF_BL_WPeff91'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwGSF_BL_WPeff91')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwGSF_BL_WPeff85'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwGSF_BL_WPeff85')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwGSF_BL_WPeff79'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwGSF_BL_WPeff79')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwoGSF_BL'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwoGSF_BL')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwoGSF_BL_WPeff99'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwoGSF_BL_WPeff99')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwoGSF_BL_WPeff96'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwoGSF_BL_WPeff96')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwoGSF_BL_WPeff91'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwoGSF_BL_WPeff91')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwoGSF_BL_WPeff85'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwoGSF_BL_WPeff85')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwoGSF_BL_WPeff79'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_wGwoGSF_BL_WPeff79')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwGSF_BL'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwGSF_BL')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwGSF_BL_WPeff99'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwGSF_BL_WPeff99')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwGSF_BL_WPeff96'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwGSF_BL_WPeff96')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwGSF_BL_WPeff91'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwGSF_BL_WPeff91')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwGSF_BL_WPeff85'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwGSF_BL_WPeff85')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwGSF_BL_WPeff79'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwGSF_BL_WPeff79')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwoGSF_BL'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwoGSF_BL')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwoGSF_BL_WPeff99'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwoGSF_BL_WPeff99')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwoGSF_BL_WPeff96'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwoGSF_BL_WPeff96')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwoGSF_BL_WPeff91'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwoGSF_BL_WPeff91')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwoGSF_BL_WPeff85'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwoGSF_BL_WPeff85')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwoGSF_BL_WPeff79'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_woGwoGSF_BL_WPeff79')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwGSF_BL'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwGSF_BL')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwGSF_BL_WPeff99'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwGSF_BL_WPeff99')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwGSF_BL_WPeff96'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwGSF_BL_WPeff96')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwGSF_BL_WPeff91'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwGSF_BL_WPeff91')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwGSF_BL_WPeff85'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwGSF_BL_WPeff85')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwGSF_BL_WPeff79'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwGSF_BL_WPeff79')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwoGSF_BL'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwoGSF_BL')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwoGSF_BL_WPeff99'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwoGSF_BL_WPeff99')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwoGSF_BL_WPeff96'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwoGSF_BL_WPeff96')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwoGSF_BL_WPeff91'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwoGSF_BL_WPeff91')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwoGSF_BL_WPeff85'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwoGSF_BL_WPeff85')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwoGSF_BL_WPeff79'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_wGwoGSF_BL_WPeff79')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwGSF_EC'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwGSF_EC')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwGSF_EC_WPeff99'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwGSF_EC_WPeff99')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwGSF_EC_WPeff96'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwGSF_EC_WPeff96')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwGSF_EC_WPeff91'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwGSF_EC_WPeff91')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwGSF_EC_WPeff85'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwGSF_EC_WPeff85')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwGSF_EC_WPeff79'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwGSF_EC_WPeff79')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwoGSF_EC'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwoGSF_EC')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwoGSF_EC_WPeff99'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwoGSF_EC_WPeff99')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwoGSF_EC_WPeff96'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwoGSF_EC_WPeff96')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwoGSF_EC_WPeff91'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwoGSF_EC_WPeff91')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwoGSF_EC_WPeff85'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwoGSF_EC_WPeff85')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwoGSF_EC_WPeff79'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA5v1_gbr_NoEleMatch_woGwoGSF_EC_WPeff79')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_wGwGSF_EC'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_wGwGSF_EC')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_wGwGSF_EC_WPEff99'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_wGwGSF_EC_WPEff99')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_wGwGSF_EC_WPEff96'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_wGwGSF_EC_WPEff96')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_wGwGSF_EC_WPEff91'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_wGwGSF_EC_WPEff91')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_wGwGSF_EC_WPEff85'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_wGwGSF_EC_WPEff85')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_wGwGSF_EC_WPEff79'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_wGwGSF_EC_WPEff79')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_woGwoGSF_BL'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_woGwoGSF_BL')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_woGwoGSF_BL_WPEff99'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_woGwoGSF_BL_WPEff99')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_woGwoGSF_BL_WPEff96'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_woGwoGSF_BL_WPEff96')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_woGwoGSF_BL_WPEff91'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_woGwoGSF_BL_WPEff91')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_woGwoGSF_BL_WPEff85'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_woGwoGSF_BL_WPEff85')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_woGwoGSF_BL_WPEff79'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_woGwoGSF_BL_WPEff79')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_woGwGSF_EC'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_woGwGSF_EC')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_woGwGSF_EC_WPEff99'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_woGwGSF_EC_WPEff99')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_woGwGSF_EC_WPEff96'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_woGwGSF_EC_WPEff96')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_woGwGSF_EC_WPEff91'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_woGwGSF_EC_WPEff91')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_woGwGSF_EC_WPEff85'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_woGwGSF_EC_WPEff85')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_woGwGSF_EC_WPEff79'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_woGwGSF_EC_WPEff79')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_wGwoGSF_BL'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_wGwoGSF_BL')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_wGwoGSF_BL_WPEff99'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_wGwoGSF_BL_WPEff99')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_wGwoGSF_BL_WPEff96'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_wGwoGSF_BL_WPEff96')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_wGwoGSF_BL_WPEff91'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_wGwoGSF_BL_WPEff91')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_wGwoGSF_BL_WPEff85'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_wGwoGSF_BL_WPEff85')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_wGwoGSF_BL_WPEff79'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_wGwoGSF_BL_WPEff79')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_woGwGSF_BL'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_woGwGSF_BL')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_woGwGSF_BL_WPEff99'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_woGwGSF_BL_WPEff99')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_woGwGSF_BL_WPEff96'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_woGwGSF_BL_WPEff96')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_woGwGSF_BL_WPEff91'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_woGwGSF_BL_WPEff91')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_woGwGSF_BL_WPEff85'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_woGwGSF_BL_WPEff85')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_woGwGSF_BL_WPEff79'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_woGwGSF_BL_WPEff79')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_wGwGSF_BL'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_wGwGSF_BL')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_wGwGSF_BL_WPEff99'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_wGwGSF_BL_WPEff99')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_wGwGSF_BL_WPEff96'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_wGwGSF_BL_WPEff96')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_wGwGSF_BL_WPEff91'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_wGwGSF_BL_WPEff91')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_wGwGSF_BL_WPEff85'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_wGwGSF_BL_WPEff85')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_wGwGSF_BL_WPEff79'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_wGwGSF_BL_WPEff79')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_wGwoGSF_EC'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_wGwoGSF_EC')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_wGwoGSF_EC_WPEff99'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_wGwoGSF_EC_WPEff99')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_wGwoGSF_EC_WPEff96'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_wGwoGSF_EC_WPEff96')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_wGwoGSF_EC_WPEff91'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_wGwoGSF_EC_WPEff91')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_wGwoGSF_EC_WPEff85'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_wGwoGSF_EC_WPEff85')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_wGwoGSF_EC_WPEff79'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_wGwoGSF_EC_WPEff79')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_woGwoGSF_EC'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_woGwoGSF_EC')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_woGwoGSF_EC_WPEff99'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_woGwoGSF_EC_WPEff99')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_woGwoGSF_EC_WPEff96'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_woGwoGSF_EC_WPEff96')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_woGwoGSF_EC_WPEff91'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_woGwoGSF_EC_WPEff91')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_woGwoGSF_EC_WPEff85'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_woGwoGSF_EC_WPEff85')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_woGwoGSF_EC_WPEff79'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v1_gbr_NoEleMatch_woGwoGSF_EC_WPEff79')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_wGwGSF_EC'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_wGwGSF_EC')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_wGwGSF_EC_WPeff98'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_wGwGSF_EC_WPeff98')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_wGwGSF_EC_WPeff90'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_wGwGSF_EC_WPeff90')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_wGwGSF_EC_WPeff80'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_wGwGSF_EC_WPeff80')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_wGwGSF_EC_WPeff70'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_wGwGSF_EC_WPeff70')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_wGwGSF_EC_WPeff60'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_wGwGSF_EC_WPeff60')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_woGwoGSF_BL'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_woGwoGSF_BL')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_woGwoGSF_BL_WPeff98'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_woGwoGSF_BL_WPeff98')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_woGwoGSF_BL_WPeff90'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_woGwoGSF_BL_WPeff90')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_woGwoGSF_BL_WPeff80'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_woGwoGSF_BL_WPeff80')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_woGwoGSF_BL_WPeff70'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_woGwoGSF_BL_WPeff70')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_woGwoGSF_BL_WPeff60'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_woGwoGSF_BL_WPeff60')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_woGwGSF_EC'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_woGwGSF_EC')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_woGwGSF_EC_WPeff98'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_woGwGSF_EC_WPeff98')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_woGwGSF_EC_WPeff90'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_woGwGSF_EC_WPeff90')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_woGwGSF_EC_WPeff80'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_woGwGSF_EC_WPeff80')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_woGwGSF_EC_WPeff70'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_woGwGSF_EC_WPeff70')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_woGwGSF_EC_WPeff60'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_woGwGSF_EC_WPeff60')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_wGwoGSF_BL'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_wGwoGSF_BL')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_wGwoGSF_BL_WPeff98'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_wGwoGSF_BL_WPeff98')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_wGwoGSF_BL_WPeff90'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_wGwoGSF_BL_WPeff90')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_wGwoGSF_BL_WPeff80'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_wGwoGSF_BL_WPeff80')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_wGwoGSF_BL_WPeff70'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_wGwoGSF_BL_WPeff70')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_wGwoGSF_BL_WPeff60'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_wGwoGSF_BL_WPeff60')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_woGwGSF_BL'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_woGwGSF_BL')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_woGwGSF_BL_WPeff98'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_woGwGSF_BL_WPeff98')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_woGwGSF_BL_WPeff90'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_woGwGSF_BL_WPeff90')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_woGwGSF_BL_WPeff80'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_woGwGSF_BL_WPeff80')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_woGwGSF_BL_WPeff70'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_woGwGSF_BL_WPeff70')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_woGwGSF_BL_WPeff60'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_woGwGSF_BL_WPeff60')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_wGwGSF_BL'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_wGwGSF_BL')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_wGwGSF_BL_WPeff98'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_wGwGSF_BL_WPeff98')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_wGwGSF_BL_WPeff90'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_wGwGSF_BL_WPeff90')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_wGwGSF_BL_WPeff80'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_wGwGSF_BL_WPeff80')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_wGwGSF_BL_WPeff70'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_wGwGSF_BL_WPeff70')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_wGwGSF_BL_WPeff60'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_wGwGSF_BL_WPeff60')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_wGwoGSF_EC'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_wGwoGSF_EC')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_wGwoGSF_EC_WPeff98'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_wGwoGSF_EC_WPeff98')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_wGwoGSF_EC_WPeff90'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_wGwoGSF_EC_WPeff90')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_wGwoGSF_EC_WPeff80'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_wGwoGSF_EC_WPeff80')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_wGwoGSF_EC_WPeff70'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_wGwoGSF_EC_WPeff70')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_wGwoGSF_EC_WPeff60'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_wGwoGSF_EC_WPeff60')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_woGwoGSF_EC'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_woGwoGSF_EC')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_woGwoGSF_EC_WPeff98'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_woGwoGSF_EC_WPeff98')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_woGwoGSF_EC_WPeff90'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_woGwoGSF_EC_WPeff90')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_woGwoGSF_EC_WPeff80'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_woGwoGSF_EC_WPeff80')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_woGwoGSF_EC_WPeff70'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_woGwoGSF_EC_WPeff70')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_woGwoGSF_EC_WPeff60'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_antiElectronMVA6v3_noeveto_gbr_NoEleMatch_woGwoGSF_EC_WPeff60')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_againstMuonMVAv1'),
            record = cms.string('GBRWrapperRcd'),
            tag = cms.string('RecoTauTag_againstMuonMVAv1')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_againstMuonMVAv1_WPeff99_5'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_againstMuonMVAv1_WPeff99_5')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_againstMuonMVAv1_WPeff99_0'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_againstMuonMVAv1_WPeff99_0')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_againstMuonMVAv1_WPeff98_0'),
            record = cms.string('PhysicsTGraphPayloadRcd'),
            tag = cms.string('RecoTauTag_againstMuonMVAv1_WPeff98_0')
        ), 
        cms.PSet(
            label = cms.untracked.string('RecoTauTag_againstMuonMVAv1_mvaOutput_normalization'),
            record = cms.string('PhysicsTFormulaPayloadRcd'),
            tag = cms.string('RecoTauTag_againstMuonMVAv1_mvaOutput_normalization')
        )
     ) )
)


process.rerunMvaIsolationTask = cms.Task(process.deepTau2017v2p1)


process.rerunMvaIsolationSequence = cms.Sequence(process.deepTau2017v2p1)


process.p = cms.Path(process.rerunMvaIsolationSequence+process.slimmedTausNewID+process.demo)


