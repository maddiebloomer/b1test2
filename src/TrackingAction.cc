#include "TrackingAction.hh"
#include "G4ParticleDefinition.hh"
#include "G4Track.hh"
#include "TTree.h"
#include "RunAction.hh"
#include "G4VProcess.hh"
#include "G4TrackingManager.hh"
#include <iostream>

namespace B1
{

  TrackingAction::TrackingAction(RunAction* runAction)
    : fRunAction (runAction) {} //, fParentID(-1) {}


void TrackingAction::PreUserTrackingAction(const G4Track* track)
{
  const G4ParticleDefinition* particle = track->GetDefinition();
  int trackID = track->GetTrackID();
  int pdgID = track->GetDefinition()->GetPDGEncoding();
  // int parentTrackID = track->GetParentID();




  fParentInfo[trackID] = pdgID;
  //fHistory

  if (particle->GetPDGEncoding() == 211 || particle->GetPDGEncoding() ==-211) {
    int pionPDG  = particle->GetPDGEncoding();
    fRunAction->SetPionPDG(pionPDG);

    int parentID = track->GetParentID();
    fRunAction->SetParentID(parentID);

    int parentPDG = fParentInfo[parentID];
    fRunAction->SetParentPDG(parentPDG);

    G4ThreeVector pionPosition = track->GetPosition();
    fRunAction->SetPionPosition(pionPosition);

    G4double pionEnergy = track->GetTotalEnergy();
    fRunAction->SetPionEnergy(pionEnergy);

    std::cout << "Creator process: " << track->GetCreatorProcess()->GetProcessName() << std::endl;

    

    // TTree* tree = fRunAction->GetTree();
    // if (tree) {
    //	tree->Fill();
    //  }
  }
}

void TrackingAction::PostUserTrackingAction(const G4Track* track)
{
  int trackID = track->GetTrackID();
  G4double energy = track->GetTotalEnergy();
  int pdgID = track->GetDefinition()->GetPDGEncoding();
  G4String creatorProcess = "primary";
  if (track->GetCreatorProcess()){
    creatorProcess = track->GetCreatorProcess()->GetProcessName();
  }

  fPostParentInfo[trackID] = energy;

   auto secondaries = fpTrackingManager->GimmeSecondaries();
   if (secondaries) {
     bool pion = false;
     for (const auto* sec : *secondaries ){
       const G4ParticleDefinition* def = sec->GetParticleDefinition();
       int pdg = def->GetPDGEncoding();
       if (pdg ==211 || pdg == -211) {
	 pion = true;
	 break;
       }

     }
     if (pion) {
       std::cout << "Particle: " << track->GetParticleDefinition()->GetParticleName() << " (" <<  pdgID << ")" << std::endl;
       std::cout << "Parent track ID: " << track->GetParentID()  << std::endl;
       // std::cout << "Creator process: " << creatorProcess << std::endl;
      std::cout << "Other secondaries:" << std::endl;
        for (auto sec : *secondaries) {
	  std::cout << "\t" << sec->GetDefinition()->GetParticleName()  << " (" << sec->GetDefinition()->GetPDGEncoding() << ", " << sec->GetPosition() << ", " << sec->GetKineticEnergy() <<  ")" << std::endl;
	}
     }

  if (pdgID == 211 || pdgID == -211) {
    int parentID = track->GetParentID();
    G4double parentEnergy = fPostParentInfo[parentID];
    fRunAction->SetParentEnergy(parentEnergy);

    TTree* tree = fRunAction->GetTree();
      if (tree) {
	tree->Fill();
      }

   
    }
  }

}
}
