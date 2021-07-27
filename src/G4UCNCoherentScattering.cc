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
///////////////////////////////////////////////////////////////////////
// UCN Coherent Scattering Class Implementation
///////////////////////////////////////////////////////////////////////
//
// File:        G4UCNCoherentScattering.cc
// Description: G4VDiscreteProcess -- CoherentScattering of UCNs
// Version:     1.0
// Created:     2014-05-12
// Author:      Peter Gumplinger
//              adopted from Geant4UCN by Peter Fierlinger (7.9.04) and
//              Marcin Kuzniak (21.4.06)
//              Calculate "elastic scattering" inside materials
// Updated:
//
// mail:        gum@triumf.ca
//
///////////////////////////////////////////////////////////////////////

#include "G4UCNProcessSubType.hh"

#include "G4UCNCoherentScattering.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

int fUCNCoherentScattering = 45;

/////////////////////////
// Class Implementation
/////////////////////////

        //////////////
        // Operators
        //////////////
 
        // G4UCNCoherentScattering::operator=(const G4UCNCoherentScattering &right)
        // {
        // }

        /////////////////
        // Constructors
        /////////////////

G4UCNCoherentScattering::G4UCNCoherentScattering(const G4String& processName,
                                           G4ProcessType type)
                    : G4VDiscreteProcess(processName, type)
{
  if (verboseLevel>0) G4cout << GetProcessName() << " is created " << G4endl;

  SetProcessSubType(fUCNCoherentScattering);
}

// G4UCNCoherentScattering::G4UCNCoherentScattering(const G4UCNCoherentScattering &right)
// {
// }

        ////////////////
        // Destructors
        ////////////////

G4UCNCoherentScattering::~G4UCNCoherentScattering(){}

        ////////////
        // Methods
        ////////////

// PostStepDoIt
// ------------

G4VParticleChange*
G4UCNCoherentScattering::PostStepDoIt(const G4Track& aTrack, const G4Step& aStep)
{
  aParticleChange.Initialize(aTrack);

  if ( verboseLevel > 0 ) G4cout << "UCNCoherentSCATTER at: "
     << aTrack.GetProperTime()/s << "s, "
     << aTrack.GetGlobalTime()/s << "s. "
     << ", after track length " << aTrack.GetTrackLength()/cm << "cm, "
           << "in volume "
           << aStep.GetPostStepPoint()->GetPhysicalVolume()->GetName()
           << G4endl;

  G4ThreeVector scattered = Scatter();
      
  aParticleChange.ProposeMomentumDirection(-scattered);

  return G4VDiscreteProcess::PostStepDoIt(aTrack, aStep);
}

// GetMeanFreePath
// ---------------

G4double G4UCNCoherentScattering::GetMeanFreePath(const G4Track& aTrack,
                                               G4double ,
                                               G4ForceCondition*)
{
  G4double AttenuationLength = DBL_MAX;

  const G4Material* aMaterial = aTrack.GetMaterial();
  G4MaterialPropertiesTable* aMaterialPropertiesTable =
                                     aMaterial->GetMaterialPropertiesTable();

  G4double crossect = 0.0;
  if (aMaterialPropertiesTable) {
     G4cout << "Energy: " << aTrack.GetKineticEnergy()/eV << G4endl;
     G4MaterialPropertyVector* crossvector = aMaterialPropertiesTable->GetProperty("COHCS");
     if (crossvector){
         crossect = crossvector->Value(aTrack.GetKineticEnergy());

         G4cout << "FOUND CROSS-SECTION COHCS: " << crossect << G4endl;
     }
//     if(crossect == 0.0)
//       G4cout << "No UCN CoherentScattering length specified" << G4endl;
  }
  else G4cout << aMaterial->GetName() << " No UCN Coherent Scattering cross-section specified" << G4endl;

// CHECK CALCULATIONS AND PUT YOUR MODEL HERE!!
  if (crossect) {

    // Calculate a UCN CoherentScattering length for this cross section

    G4double density = aMaterial->GetTotNbOfAtomsPerVolume();

    crossect *= barn;
  
    // attenuation length in mm
    AttenuationLength = 1./density/crossect; 
  }

  return AttenuationLength;
}

G4ThreeVector G4UCNCoherentScattering::Scatter()
{

  G4cout << "SCATTER: Put your code here!" << G4endl;

  G4ThreeVector final(0.,0.,1.);

  // Make a simple uniform distribution in 4 pi
  // apply scattering, calculate angle phi, theta

  G4double theta = std::acos(2*G4UniformRand()-1);
  G4double phi = G4UniformRand() * 2 * pi;

  final.rotateY(theta);
  final.rotateZ(phi);
  final = final.unit();

  return final;
}
