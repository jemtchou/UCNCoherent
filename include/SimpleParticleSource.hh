#ifndef SimpleParticleSource_h
#define SimpleParticleSource_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

#include <map>

class G4ParticleGun;
class G4Event;

class SimpleParticleSource : public G4VUserPrimaryGeneratorAction
{
public:
  SimpleParticleSource();    
  virtual ~SimpleParticleSource();

  // method from the base class
  virtual void GeneratePrimaries(G4Event*);         
  
private:

  G4ParticleGun*  fParticleGun;
};

#endif


