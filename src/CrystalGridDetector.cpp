#include "CrystalGridDetector.h"
#include "CrystalMaterial.h"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"


G4VPhysicalVolume* CrystalGridDetector::Construct( std::string Name, G4LogicalVolume* worldLV,
                                                   G4int xGrid, G4int zGrid, std::string Material )
{
  G4Material* crystal = CrystalMaterial::GetCrystalMaterial(Material, "Siemens");
 
  std::cout << "Selected detector material: " << crystal->GetName() << std::endl;

  G4double x = crystalWidth;
  G4double y = crystalLength;
  G4double z = crystalWidth;
  G4int const totalCrystals = xGrid * zGrid;

  // make a grid
  G4double xPosition = -x * xGrid;
  G4double yPosition = -y;
  for ( int xIndex = 0; xIndex < xGrid; xIndex++ )
  {
    xPosition += x;
    G4double zPosition = -z * zGrid;
    for ( int zIndex = 0; zIndex < zGrid; zIndex++ )
    {
      zPosition += z;

      std::string crystalName = Name + "." + std::to_string( xIndex ) + "." + std::to_string( zIndex );

      // DETECTOR: the solid shape
      G4Box* detectorS = new G4Box(
          crystalName,
          x,
          y,
          z );

      // DETECTOR: Logical volume (how to treat it)
      G4LogicalVolume* detectorLV = new G4LogicalVolume(
          detectorS,         // its solid
          crystal,           // its material
          crystalName,              // its name
          0, 0, 0 );         // Modifiers we don't use

      G4VisAttributes* vis = new G4VisAttributes();
      vis->SetColor( 0.0, G4double( rand() % totalCrystals ) / G4double( totalCrystals ), 0.0, 0.2 );
      detectorLV->SetVisAttributes( vis );

      // DETECTOR: Physical volume (where is it)
      /*G4VPhysicalVolume* detectorPV =*/ new G4PVPlacement(
          0,               // no rotation
          G4ThreeVector(xPosition, yPosition, zPosition), // in the centre
          detectorLV,      // its logical volume
          crystalName,            // its name
          worldLV,         // its mother volume
          false,           // no boolean operations
          0,               // copy number
          true );          // checking overlaps


      zPosition += z;
    }
    xPosition += x;
  }

  // HITS: a perfect photodetector
  G4Box* hitsS = new G4Box(
                 "HitPlane",         // its name
                 (x*xGrid),
                 1*mm,
                 (z*zGrid) );   // its size (in half-lengths)

  // HITS: Logical volume (how to treat it)
  G4LogicalVolume* hitsLV = new G4LogicalVolume(
                 hitsS,          // its solid
                 crystal,             // its material
                 "HitPlane" );       // its name

  G4VisAttributes* vis = new G4VisAttributes();
  vis->SetColor( 1.0, 0.0, 0.0, 1.0 );
  hitsLV->SetVisAttributes( vis );
  
  // HITS: Physical volume (where is it)
  /*G4VPhysicalVolume* hitsPV =*/ new G4PVPlacement(
                 0,               // no rotation
                 G4ThreeVector(0.0, -(2*y + 1*mm), 0.0), // below crystals
                 hitsLV,         // its logical volume
                 "HitPlane",         // its name
                 worldLV,         // its mother volume
                 false,           // no boolean operations
                 0,               // copy number
                 true );          // checking overlaps


  return nullptr;
}
