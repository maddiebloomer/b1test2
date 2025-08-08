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
// * use  in  resulting  scientific  publications,  and indicqate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file B1/src/DetectorConstruction.cc
/// \brief Implementation of the B1::DetectorConstruction class

#include "DetectorConstruction.hh"

#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Trd.hh"

#include "SensitiveDetector.hh"
#include "G4SDManager.hh"
#include "RunAction.hh"
#include "G4RunManager.hh"

namespace B1
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//this is defining the parameters of that specific instance from the header file? And this is saying from that instance pull the method construct?

  DetectorConstruction::DetectorConstruction(RunAction* runAction)
    : G4VUserDetectorConstruction(), fRunAction(runAction){}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();


  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //
  // World
  //
  G4double world_radius = 100*m;
  G4double world_inner_radius = 0.0 ;
  G4double world_phi_i = 0.0 ;
  G4double world_phi_f = CLHEP::twopi ;
  G4double world_theta_i = 0.0 ;
  G4double world_theta_f = CLHEP::pi ;
  
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic");

  auto solid_world = new G4Sphere("world", world_inner_radius, world_radius, world_phi_i, world_phi_f, world_theta_i, world_theta_f) ;

  auto logic_world = new G4LogicalVolume(solid_world,  // its solid
                                        world_mat,  // its material
                                        "world");  // its name

  auto phys_world = new G4PVPlacement(nullptr,  // no rotation
                                     G4ThreeVector(),  // at (0,0,0)
                                     logic_world,  // its logical volume
                                     "world",  // its name
                                     nullptr,  // its mother  volume
                                     false,  // no boolean operation
                                     0,  // copy number
                                     checkOverlaps);  // overlaps checking

 

  //
  // cylinder
  //
  G4Material* cylinder_mat = nist->FindOrBuildMaterial("G4_Ni");
  G4ThreeVector pos1 = G4ThreeVector(0, 0, 8*cm);

  G4double inner_radius = 0.0 ;
  G4double outer_radius = 3.0*mm ;
  G4double half_length = 8.0*cm ;
  G4double angle_i = 0.0 ;
  G4double angle_f = CLHEP::twopi ;
  
  
  auto solid_cylinder = new G4Tubs("cylinder", inner_radius, outer_radius, half_length, angle_i, angle_f);

  auto logic_cylinder = new G4LogicalVolume(solid_cylinder,  // its solid
                                         cylinder_mat,  // its material
                                         "cylinder");  // its name

  new G4PVPlacement(nullptr,  // no rotation
                    pos1,  // at position
                    logic_cylinder,  // its logical volume
                    "cylinder",  // its name
                    logic_world,  // its mother  volume
                    false,  // no boolean operation
                    0,  // copy number
                    checkOverlaps);  // overlaps checking


  // detector
  G4Material* detector_mat = nist->FindOrBuildMaterial("G4_Galactic");
  G4ThreeVector detector_pos = G4ThreeVector(0, 0, 16.05*cm);

  G4double d_inner_r = 0.0 ;
  G4double d_outer_r = 5.0*cm;
  G4double d_half_length = 0.5*mm;
  G4double d_angle_i = 0.0 ;
  G4double d_angle_f = CLHEP::twopi ;

  auto solid_detector = new  G4Tubs("detector", d_inner_r, d_outer_r, d_half_length, d_angle_i, d_angle_f);

  auto logic_detector = new G4LogicalVolume(solid_detector, detector_mat, "detector");

  new G4PVPlacement(nullptr, detector_pos, logic_detector, "detector", logic_world, false, 0, checkOverlaps);

  // sensitive detector
  // G4SDManager* sdManager = G4SDManager::GetSDMpointer();
  // SensitiveDetector* sdtest = new SensitiveDetector("/sdtest", fRunAction);
  // sdManager->AddNewDetector(sdtest);
  // logic_detector->SetSensitiveDetector(sdtest);
  // sdManager->Activate("sdtest", true);


  // Set cylinder  as scoring volume
  //
  fScoringVolume = logic_cylinder;

  //
  // always return the physical World
  //
  return phys_world;
}

  void DetectorConstruction::ConstructSDandField() {
    G4SDManager* sdManager = G4SDManager::GetSDMpointer();
    SensitiveDetector* sdtest = new SensitiveDetector("/sdtest", fRunAction);
    sdManager->AddNewDetector(sdtest);
    SetSensitiveDetector("detector", sdtest);
  }
}
