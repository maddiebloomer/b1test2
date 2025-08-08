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
/// \file B1/include/DetectorConstruction.hh
/// \brief Definition of the B1::DetectorConstruction class

//what do these things do?
#ifndef B1DetectorConstruction_h
#define B1DetectorConstruction_h 1



#include "G4VUserDetectorConstruction.hh"

//Header files have all of the classes that are going to get used in the .cc files?
class G4VPhysicalVolume;
class G4LogicalVolume;

//How does namespace work/what exactly does it do?
namespace B1
{

  class RunAction;
  
  
/// Detector construction class to define materials and geometry.

//This is creating a specific instance of an existing virtual class, and everything that happens inside the brackets is presumably defined by whatever that virtual class requires?
class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction(RunAction* runAction);
    ~DetectorConstruction() override = default;

    G4VPhysicalVolume* Construct() override;

    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

    void  ConstructSDandField() override;

private:
  RunAction* fRunAction;

  protected:
    G4LogicalVolume* fScoringVolume = nullptr;
};
}

#endif
