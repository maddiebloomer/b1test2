#ifndef SensitiveDetector_h
#define SensitiveDetector_h 1

#include "G4VSensitiveDetector.hh"
class G4Step;
//class G4HCofThisEvent;
class G4TouchableHistory;

namespace B1{

  class RunAction;
  
class  SensitiveDetector : public G4VSensitiveDetector {
public:
  SensitiveDetector(G4String sdtest, RunAction*runAction);
  virtual ~SensitiveDetector();

  virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history) override;

private:
  RunAction* fRunAction;
};
}

#endif
