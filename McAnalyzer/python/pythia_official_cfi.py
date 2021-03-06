import FWCore.ParameterSet.Config as cms

from Configuration.Generator.PythiaUESettings_cfi import *

generator = cms.EDFilter("Pythia6GeneratorFilter",
    pythiaHepMCVerbosity = cms.untracked.bool(False),
    maxEventsToPrint = cms.untracked.int32(0),
    pythiaPylistVerbosity = cms.untracked.int32(1),
    filterEfficiency = cms.untracked.double(1.0),
    crossSection = cms.untracked.double(71260000000.),
    comEnergy = cms.double(7000.0),
    PythiaParameters = cms.PSet(
        pythiaUESettingsBlock,
        processParameters = cms.vstring('MSEL=0         ! User defined processes', 
                                        'MSUB(11)=1     ! Min bias process', 
                                        'MSUB(12)=1     ! Min bias process', 
                                        'MSUB(13)=1     ! Min bias process', 
                                        'MSUB(28)=1     ! Min bias process', 
                                        'MSUB(53)=1     ! Min bias process', 
                                        'MSUB(68)=1     ! Min bias process', 
                                        'MSUB(92)=1     ! Min bias process, single diffractive', 
                                        'MSUB(93)=1     ! Min bias process, single diffractive', 
                                        'MSUB(94)=1     ! Min bias process, double diffractive', 
                                        'MSUB(95)=1     ! Min bias process',
                                        'CKIN(3)=6.    ! ptMin'),
        # This is a vector of ParameterSet names to be read, in this order
        parameterSets = cms.vstring('pythiaUESettings', 
            'processParameters')
    )
)

