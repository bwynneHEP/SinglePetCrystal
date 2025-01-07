#include "DetectorConstruction.h"
#include "CrystalGridDetector.h"
#include "HitPlane.h"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4NistManager.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4AutoDelete.hh"
#include "G4GeometryManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"

G4ThreadLocal
G4GlobalMagFieldMessenger* DetectorConstruction::m_magneticFieldMessenger = 0;

DetectorConstruction::DetectorConstruction( std::string detector, std::string outputFileName, std::string material )
  : G4VUserDetectorConstruction()
  , m_detector( detector )
  , m_outputFileName( outputFileName )
  , m_material( material )
{
}

DetectorConstruction::~DetectorConstruction()
{
}

// Here we define the actual experiment that we want to perform
G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Materials
  // http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Appendix/materialNames.html
  G4NistManager* nistManager = G4NistManager::Instance();
  G4Material* air = nistManager->FindOrBuildMaterial( "G4_AIR" );

  // Definitions of Solids, Logical Volumes, Physical Volumes
  //G4double const worldAxial = 1.5*m;
  //G4double const worldTrans = 1.0*m;
  G4double const worldAxial = 10.0*cm;
  G4double const worldTrans = 10.0*cm;

  // WORLD: Solid (cube)
  G4GeometryManager::GetInstance()->SetWorldMaximumExtent( worldAxial );
  G4Box* worldS = new G4Box(
                 "World",         // its name
                 worldTrans,
                 worldTrans,
                 worldAxial );   // its size (in half-lengths)

  // WORLD: Logical volume (how to treat it)
  G4LogicalVolume* worldLV = new G4LogicalVolume(
                 worldS,          // its solid
                 air,             // its material
                 "World" );       // its name

  // WORLD: Physical volume (where is it)
  // Must place the World Physical volume unrotated at (0,0,0).
  G4VPhysicalVolume* worldPV = new G4PVPlacement(
                 0,               // no rotation
                 G4ThreeVector(0.0, 0.0, 0.0), // in the centre
                 worldLV,         // its logical volume
                 "World",         // its name
                 0,               // its mother volume
                 false,           // no boolean operations
                 0,               // copy number
                 true );          // checking overlaps

  // DETECTOR: separate class
  if ( m_detector.substr( 0, 4 ) == "Grid" )
  {
    CrystalGridDetector::Construct( "Detector", worldLV );
  }
  else
  {
    std::cerr << "Unrecognised detector name: " << m_detector << std::endl;
    exit(1);
  }

  // DETECTOR: Warn if there's an overlap, but it's very slow (N^2 I think)
  //if ( detectorPV->CheckOverlaps() ) std::cerr << "WARNING: your simulated objects overlap" << std::endl;

  // Always return the physical world
  return worldPV;
}

// Set up the magnetic field
void DetectorConstruction::ConstructSDandField()
{
  // Create global magnetic field messenger.
  // Uniform magnetic field is then created automatically if
  // the field value is not zero.
  G4ThreeVector fieldValue = G4ThreeVector();
  m_magneticFieldMessenger = new G4GlobalMagFieldMessenger( fieldValue );

  // Register the field messenger for deleting
  G4AutoDelete::Register( m_magneticFieldMessenger );

  HitPlane * hitPlane = new HitPlane( "HitPlane", m_outputFileName );
  G4SDManager::GetSDMpointer()->AddNewDetector( hitPlane );
  this->SetSensitiveDetector( "HitPlane", hitPlane );
}
