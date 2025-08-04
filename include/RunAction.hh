//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file B1/include/RunAction.hh
/// \brief Definition of the B1::RunAction class

#ifndef B1RunAction_h
#define B1RunAction_h 1

#include "G4UserRunAction.hh"
#include "TFile.h"
#include "TTree.h"
#include "G4ThreeVector.hh"


class G4Run;

namespace B1
{


class RunAction : public G4UserRunAction
{
  public:
    RunAction();
    ~RunAction() override = default;

    void BeginOfRunAction(const G4Run*) override;
    void EndOfRunAction(const G4Run*) override;

    void SetPionPDG(int pionpdg) { pionPDG = pionpdg; }
    void SetParentID(int id) { parentID = id; }
    void SetParentPDG(int pdg) { parentPDG = pdg; }
  //  void SetGrandparentID(int gid) { gparentID = gid; }
  //  void SetGrandparentPDG(int gpdg) { gparentPDG = gpdg;}
  // void SetGreatGrandparentID(int ggid) { ggparentID = ggid; }
  //  void SetGreatGrandparentPDG(int ggpdg) { ggparentPDG = ggpdg; }

  
    void SetPionPosition(G4ThreeVector pos) {
      pionPosition = pos;
      pionX = pos.x();
      pionY = pos.y();
      pionZ = pos.z();
    }
    void SetParentEnergy(G4double ene) { parentEnergy = ene; }
    void SetPionEnergy(G4double pionene) {pionEnergy = pionene; }

    TFile* GetRootFile() const {return fFile;}
    TTree* GetTree() const{return fTree;}

  //proton position test
    void SetProtonPosition(G4ThreeVector ppos) {
      protonPosition = ppos;
      protonX = ppos.x();
      protonY = ppos.y();
      protonZ = ppos.z();
    }

    TTree* GetProtonTree() const {return fProtonTree;}

  private:
    TFile* fFile;
    TTree* fTree;
    int pionPDG;
    int parentID;
    int parentPDG;
  //  int gparentID;
  //int gparentPDG;
  // int ggparentID;
  // int ggparentPDG;
    G4ThreeVector pionPosition;
    double pionX;
    double pionY;
    double pionZ;
    G4double parentEnergy;
    G4double pionEnergy;

    //proton position test
    TTree* fProtonTree;
    G4ThreeVector protonPosition;
    double protonX;
    double protonY;
    double protonZ;
};

}  // namespace B1

#endif
