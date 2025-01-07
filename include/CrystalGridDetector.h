#ifndef CrystalGridDetector_h
#define CrystalGridDetector_h 1

#include "G4VPhysicalVolume.hh"
#include "G4SystemOfUnits.hh"

#include <vector>
#include <string>

class CrystalGridDetector
{
  public:
    static G4VPhysicalVolume* Construct( std::string Name, G4LogicalVolume* worldLV, G4int xGrid=5, G4int zGrid=5, std::string Material="LSO" );

  private:
    // Single crystal (square prism)
    static G4double constexpr crystalWidth = 3.2*mm / 2.0; // half because it's measured from middle to face
    static G4double constexpr crystalLength = 20.0*mm / 2.0;
};

#endif
