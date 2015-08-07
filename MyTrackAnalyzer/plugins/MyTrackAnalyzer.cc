// -*- C++ -*-
//
// Package:    MyTrackAnalyzer/MyTrackAnalyzer
// Class:      MyTrackAnalyzer
// 
/**\class MyTrackAnalyzer MyTrackAnalyzer.cc MyTrackAnalyzer/MyTrackAnalyzer/plugins/MyTrackAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Emilien Chapon
//         Created:  Fri, 07 Aug 2015 08:14:23 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"
#include "TH2.h"
//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

// number of track algorithm types
#define NTRKALGO reco::TrackBase::TrackAlgorithm::algoSize

class MyTrackAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit MyTrackAnalyzer(const edm::ParameterSet&);
      ~MyTrackAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
      TH1F *hAlgo;
      TH1F *hOrigAlgo;
      TH2F *hAlgoHist;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
MyTrackAnalyzer::MyTrackAnalyzer(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
   // usesResource("TFileService");

   edm::Service<TFileService> fs;
   hAlgo = fs->make<TH1F>("trk algo","trk algo",NTRKALGO,0,NTRKALGO);
   hOrigAlgo = fs->make<TH1F>("original trk algo","original trk algo",NTRKALGO,0,NTRKALGO);
   hAlgoHist = fs->make<TH2F>("trk algo history","trk algo history",NTRKALGO,0,NTRKALGO,NTRKALGO,0,NTRKALGO);
}


MyTrackAnalyzer::~MyTrackAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
MyTrackAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;


   Handle<reco::TrackCollection> tracks;
   iEvent.getByLabel("hiGeneralTracks", tracks); 

   for (reco::TrackCollection::const_iterator itrk = tracks->begin();
         itrk != tracks->end();
         ++itrk)
   {
      int thealgo = itrk->algo();
      hAlgo->Fill(thealgo);
      hOrigAlgo->Fill(itrk->originalAlgo());
      reco::TrackBase::AlgoMask themask = itrk->algoMask();
      for (int i=0; i<NTRKALGO; i++)
         if (themask[i])
            hAlgoHist->Fill(thealgo,i);
   }

}


// ------------ method called once each job just before starting event loop  ------------
void 
MyTrackAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
MyTrackAnalyzer::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
MyTrackAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(MyTrackAnalyzer);
