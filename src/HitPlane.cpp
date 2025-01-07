#include "HitPlane.h"

#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"

HitPlane::HitPlane( const G4String& name, std::string outputFileName )
  : G4VSensitiveDetector( name ) // Run the constructor of the parent class
  , m_outputFile( outputFileName )
{
  if (outputFileName.empty()){
    std::cerr << "Output file name cannot be empty" << std::endl;
    exit(1);
  }
  if (!m_outputFile.good()){
    std::cerr << "Failed to open file: " << outputFileName << std::endl;
    exit(1);
  }
}

HitPlane::~HitPlane()
{
}

// Analyse anything that hits the detector
G4bool HitPlane::ProcessHits( G4Step* step, G4TouchableHistory* history )
{
  // Get the type of particle that made this track
  G4Track * track = step->GetTrack();
  std::string particle = track->GetParticleDefinition()->GetParticleName();

  // Output positions
  //if ( step->GetPostStepPoint()->GetPosition().getY() == 10.0*mm ) {
    m_outputFile << particle;
    m_outputFile << " " << step->GetPostStepPoint()->GetPosition().getX();
    m_outputFile << " " << step->GetPostStepPoint()->GetPosition().getY();
    m_outputFile << " " << step->GetPostStepPoint()->GetPosition().getZ();
    m_outputFile << " " << step->GetPostStepPoint()->GetGlobalTime() << std::endl;
  //}
  return true;
}

