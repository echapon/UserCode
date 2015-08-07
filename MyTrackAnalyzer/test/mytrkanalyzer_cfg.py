import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

# initialize MessageLogger and output report
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.categories.append('Demo')
process.MessageLogger.cerr.INFO = cms.untracked.PSet(
      limit = cms.untracked.int32(-1)
      )
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(200) )

process.source = cms.Source("PoolSource",
      # replace 'myfile.root' with the source file you want to use
      fileNames = cms.untracked.vstring(

         'file:step2.root'
         )
      )

process.demo = cms.EDAnalyzer('MyTrackAnalyzer',
      )

process.TFileService = cms.Service("TFileService",
      fileName = cms.string('histotrk.root')
      )


process.p = cms.Path(process.demo)
