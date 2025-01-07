#ifndef NormalPhotonAction_h
#define NormalPhotonAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"

// Generate a single particle and fire it into our experiment
class NormalPhotonAction : public G4VUserPrimaryGeneratorAction
{
  public:
    NormalPhotonAction( G4double originZmm );
    ~NormalPhotonAction() override;

    void GeneratePrimaries( G4Event* ) override;

  private:
    G4ParticleGun* m_particleGun;
    G4double m_origin;
};

#endif
