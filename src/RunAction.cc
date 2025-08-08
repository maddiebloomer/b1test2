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
/// \file B1/src/RunAction.cc
/// \brief Implementation of the B1::RunAction class

#include "RunAction.hh"

#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4AnalysisManager.hh"
#include "G4LogicalVolume.hh"
#include "G4ParticleDefinition.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

namespace B1
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run*)
{
  // inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

  //root test
  fFile = new TFile("b1test2.root", "RECREATE");
  fTree = new TTree("b1test2_tree","B1 Test Tree");
  fTree->Branch("pionPDG", &pionPDG, "pionPDG/I");
  fTree->Branch("parentID", &parentID, "parentID/I");
  fTree->Branch("parentPDG", &parentPDG, "parentPDG/I");
  fTree->Branch("pionX", &pionX, "pionX/D");
  fTree->Branch("pionY", &pionY, "pionY/D");
  fTree->Branch("pionZ", &pionZ, "pionZ/D");
  fTree->Branch("parentEnergy", &parentEnergy, "parentEnergy/D");
  fTree->Branch("pionEnergy", &pionEnergy, "pionEnergy/D");

  //proton position test
  fProtonTree = new TTree("b1test2proton_tree", "B1 Proton Test Tree");
  fProtonTree->Branch("protonX", &protonX, "protonX/D");
  fProtonTree->Branch("protonY", &protonY, "protonY/D");
  fProtonTree->Branch("protonZ", &protonZ, "protonZ/D");
  fProtonTree->Branch("protonEnergy", &protonEnergy, "protonEnergy/D");
  fProtonTree->Branch("trackID", &trackID, "trackID/I");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* run)
{
  fFile->cd();
  fTree->Write();
  fProtonTree->Write();
  fFile->Close();
  delete fFile;

}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}  // namespace B1
