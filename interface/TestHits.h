#ifndef TESTHITS_H
#define TESTHITS_H


// -*- C++ -*-
//
// Package:    TestHits
// Class:      TestHits
// 
/**\class TestHits TestHits.cc RecoTracker/TestHits/src/TestHits.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Giuseppe Cerati
//         Created:  Tue Feb 13 17:29:10 CET 2007
// $Id$
//
//
#include <memory>
#include <vector>
#include <string>
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "SimTracker/TrackerHitAssociation/interface/TrackerHitAssociator.h"
#include "MagneticField/Engine/interface/MagneticField.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h" 
#include "TrackingTools/Records/interface/TrackingComponentsRecord.h" 
#include "TrackingTools/Records/interface/TransientRecHitRecord.h" 
#include "TrackingTools/PatternTools/interface/TrajectoryStateUpdator.h"
#include "Geometry/CommonDetUnit/interface/TrackingGeometry.h"
#include "DataFormats/TrackCandidate/interface/TrackCandidateCollection.h"
#include "TrackingTools/GeomPropagators/interface/Propagator.h"
#include "TrackingTools/TransientTrackingRecHit/interface/TransientTrackingRecHitBuilder.h"
#include "RecoTracker/TransientTrackingRecHit/interface/TkTransientTrackingRecHitBuilder.h"
#include <sstream>
#include <TFile.h>
#include <TH1F.h>

class TestHits : public edm::EDAnalyzer {
public:
  explicit TestHits(const edm::ParameterSet&);
  ~TestHits();

private:
  virtual void beginJob(const edm::EventSetup&) ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  const edm::ParameterSet conf_;
  TrackerHitAssociator * hitAssociator;

  double mineta, maxeta;

  std::string propagatorName;
  std::string builderName;
  std::string srcName;
  std::string updatorName;
  edm::ESHandle<TrackerGeometry> theG;
  edm::ESHandle<MagneticField> theMF;
  edm::ESHandle<Propagator> thePropagator;
  edm::ESHandle<TransientTrackingRecHitBuilder> theBuilder;
  edm::ESHandle<TrajectoryStateUpdator> theUpdator;
  edm::Handle<TrackCandidateCollection> theTCCollection;

  TFile* file;
  std::stringstream title;
  std::map<std::string,TH1F*> hPullGP_X_ts;
  std::map<std::string,TH1F*> hPullGP_Y_ts;
  std::map<std::string,TH1F*> hPullGP_Z_ts;
  std::map<std::string,TH1F*> hPullGM_X_ts;
  std::map<std::string,TH1F*> hPullGM_Y_ts;
  std::map<std::string,TH1F*> hPullGM_Z_ts;
  std::map<std::string,TH1F*> hPullGP_X_rs;
  std::map<std::string,TH1F*> hPullGP_Y_rs;
  std::map<std::string,TH1F*> hPullGP_Z_rs;
  std::map<std::string,TH1F*> hPullGP_X_tr;
  std::map<std::string,TH1F*> hPullGP_Y_tr;
  std::map<std::string,TH1F*> hPullGP_Z_tr;

  std::map<std::string,TH1F*> hPullGP_X_ts_mono;
  std::map<std::string,TH1F*> hPullGP_Y_ts_mono;
  std::map<std::string,TH1F*> hPullGP_Z_ts_mono;
  std::map<std::string,TH1F*> hPullGM_X_ts_mono;
  std::map<std::string,TH1F*> hPullGM_Y_ts_mono;
  std::map<std::string,TH1F*> hPullGM_Z_ts_mono;
  std::map<std::string,TH1F*> hPullGP_X_rs_mono;
  std::map<std::string,TH1F*> hPullGP_Y_rs_mono;
  std::map<std::string,TH1F*> hPullGP_Z_rs_mono;
  std::map<std::string,TH1F*> hPullGP_X_tr_mono;
  std::map<std::string,TH1F*> hPullGP_Y_tr_mono;
  std::map<std::string,TH1F*> hPullGP_Z_tr_mono;

  std::map<std::string,TH1F*> hPullGP_X_ts_stereo;
  std::map<std::string,TH1F*> hPullGP_Y_ts_stereo;
  std::map<std::string,TH1F*> hPullGP_Z_ts_stereo;
  std::map<std::string,TH1F*> hPullGM_X_ts_stereo;
  std::map<std::string,TH1F*> hPullGM_Y_ts_stereo;
  std::map<std::string,TH1F*> hPullGM_Z_ts_stereo;
  std::map<std::string,TH1F*> hPullGP_X_rs_stereo;
  std::map<std::string,TH1F*> hPullGP_Y_rs_stereo;
  std::map<std::string,TH1F*> hPullGP_Z_rs_stereo;
  std::map<std::string,TH1F*> hPullGP_X_tr_stereo;
  std::map<std::string,TH1F*> hPullGP_Y_tr_stereo;
  std::map<std::string,TH1F*> hPullGP_Z_tr_stereo;
};

#endif
