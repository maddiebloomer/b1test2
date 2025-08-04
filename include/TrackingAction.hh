
#ifndef TrackingAction_h
#define TrackingAction_h 1

#include "G4UserTrackingAction.hh"
#include <map>


namespace B1
{
  class RunAction;

  
class TrackingAction : public G4UserTrackingAction
{
public:
  TrackingAction(RunAction* runAction);
  ~TrackingAction() override = default;

  void PreUserTrackingAction(const G4Track*) override;
  void PostUserTrackingAction(const G4Track*) override;

private:
  RunAction* fRunAction;
  //int fParentID{-1};
  std::map<int, int> fParentInfo;
  std::map<int, double> fPostParentInfo;
};

}

#endif
