#ifndef SimpleGeometry_h
#define SimpleGeometry_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;

class SimpleGeometry : public G4VUserDetectorConstruction
{
  public:
    SimpleGeometry();
    virtual ~SimpleGeometry();
  public:
    virtual G4VPhysicalVolume* Construct();
};

#endif

