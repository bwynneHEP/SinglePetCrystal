#ifndef HitPlane_h
#define HitPlane_h 1

#include "G4VSensitiveDetector.hh"

#include <fstream>

class HitPlane : public G4VSensitiveDetector
{
  public:
    HitPlane( const G4String& name, std::string outputFileName );
    ~HitPlane() override;

    G4bool ProcessHits( G4Step* step, G4TouchableHistory* history ) override;

  private:
    std::ofstream m_outputFile;
};

#endif
