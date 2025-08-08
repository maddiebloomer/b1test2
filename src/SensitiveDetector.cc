#include "SensitiveDetector.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "RunAction.hh"
#include "TTree.h"
#include <iostream>

namespace B1{

  SensitiveDetector::SensitiveDetector(G4String sdtest, RunAction* runAction)
    : G4VSensitiveDetector(sdtest), fRunAction (runAction) {
    // std::cout << "Ping from constructor\n";
  }

SensitiveDetector::~SensitiveDetector(){
  // std::cout << "Ping from destructor\n";
}

G4bool SensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory* history) {
  // std::cout << "Ping!\n";
  G4Track* track = step->GetTrack();

  if (track->GetDefinition()->GetPDGEncoding() != 2212)
  return false;

  G4StepPoint* prePoint = step->GetPreStepPoint();
  G4ThreeVector pos = prePoint->GetPosition();
  G4double ene = prePoint->GetTotalEnergy();
  G4int tid = track->GetTrackID();


  //  std::cout<<pos<<std::endl;

  fRunAction->SetProtonPosition(pos);
  fRunAction->SetProtonEnergy(ene);
  fRunAction->SetTrackID(tid);

  TTree* ptree = fRunAction->GetProtonTree();
  if (ptree) {
    ptree->Fill();
  }

  return true;
}
}
