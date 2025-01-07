#ifndef DirectedPhotonAction_h
#define DirectedPhotonAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"

// Generate a single particle and fire it into our experiment
class DirectedPhotonAction : public G4VUserPrimaryGeneratorAction
{
  public:
    DirectedPhotonAction( G4double incidentAngleDegrees );
    ~DirectedPhotonAction() override;

    void GeneratePrimaries( G4Event* ) override;

  private:
    G4ParticleGun* m_particleGun;
    G4double m_angle;
};

#endif
