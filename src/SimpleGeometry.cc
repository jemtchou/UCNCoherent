#include "SimpleGeometry.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

using namespace CLHEP;

SimpleGeometry::SimpleGeometry()
: G4VUserDetectorConstruction()
{ }

SimpleGeometry::~SimpleGeometry()
{ }

G4VPhysicalVolume* SimpleGeometry::Construct()
{  
  G4bool checkOverlaps = true;

  G4NistManager* nist = G4NistManager::Instance();
  G4Material* Carbon = nist->FindOrBuildMaterial("G4_C");
  G4Material* Vacuum = nist->FindOrBuildMaterial("G4_Galactic");

  std::vector<G4double> neutronEnergy = {
1e-10 * eV, 2e-10 * eV, 5e-10 * eV, 1e-9 * eV, 2e-9 * eV, 1e-8*eV
};


  std::vector<G4double> CoherentSc = {
  1343.5, 1344, 13445, 1345, 13455, 1.33
  };

  G4MaterialPropertiesTable* carbon_table = new G4MaterialPropertiesTable();
  carbon_table->AddProperty("COHCS", neutronEnergy, CoherentSc) ->SetSpline(true);
  Carbon->SetMaterialPropertiesTable(carbon_table);

  // World
  G4Box* world = new G4Box("World", 50*cm, 50*cm, 50*cm);
  G4LogicalVolume* worldlv =                         
    new G4LogicalVolume(world, Vacuum, "World");  
  
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0, G4ThreeVector(),
                      worldlv, "World",
                      0, false, 0, checkOverlaps);

  // Carbon plate
  G4Box* plate = new G4Box("CarbonPlate", 10*cm, 10*cm, 5*cm);
  G4LogicalVolume* platelv =                         
    new G4LogicalVolume(plate, Carbon, "CarbonPlate");  

  new G4PVPlacement(0, G4ThreeVector(0.,0.,0.),
                      platelv, "CarbonPlate",
                      worldlv, false, 0, checkOverlaps);

  return physWorld;
}
