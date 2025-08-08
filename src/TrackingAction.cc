#include "TrackingAction.hh"
#include "G4ParticleDefinition.hh"
#include "G4Track.hh"
#include "TTree.h"
#include "RunAction.hh"

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

  fPostParentInfo[trackID] = energy;

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
