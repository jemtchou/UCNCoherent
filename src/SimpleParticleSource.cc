#include "SimpleParticleSource.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4Neutron.hh"
#include "G4Gamma.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

using namespace std;

SimpleParticleSource::SimpleParticleSource()
: G4VUserPrimaryGeneratorAction()
{
  fParticleGun = new G4ParticleGun(1);
  fParticleGun->SetParticleDefinition(G4Neutron::NeutronDefinition());
  fParticleGun->SetParticleEnergy(1e-9*eV);
  fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,-10.0*cm));
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
}

SimpleParticleSource::~SimpleParticleSource()
{
}

void SimpleParticleSource::GeneratePrimaries(G4Event* evt)
{
  fParticleGun->GeneratePrimaryVertex(evt);
}
