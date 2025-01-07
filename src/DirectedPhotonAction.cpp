#include "DirectedPhotonAction.h"

#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4IonTable.hh"
#include "Randomize.hh"

#include <cmath>

DirectedPhotonAction::DirectedPhotonAction( G4double incidentAngleDegrees )
  : G4VUserPrimaryGeneratorAction()
  , m_angle( incidentAngleDegrees * degree )
{
  G4int nofParticles = 1;
  m_particleGun = new G4ParticleGun( nofParticles );

  // 511 keV photon (default, probably overridden later)
  G4ParticleDefinition * particleDefinition = G4ParticleTable::GetParticleTable()->FindParticle( "gamma" );
  m_particleGun->SetParticleDefinition( particleDefinition );
  m_particleGun->SetParticleEnergy( 511*keV );


  // Set the position and direction such that it always passes through 0, 0, 0 in the downwards y direction
  //m_particleGun->SetParticlePosition( G4ThreeVector( 0.0, 0.0, 0.0 ) ); // in the middle of the detector
  m_particleGun->SetParticlePosition( G4ThreeVector( 0.0, std::sin(m_angle)*20.0*mm, std::cos(m_angle)*20.0*mm ) );
  //m_particleGun->SetParticleMomentumDirection( G4ThreeVector( 0.0, 0.0, 1.0 ) ); // along z axis
  m_particleGun->SetParticleMomentumDirection( G4ThreeVector( 0.0, -std::sin(m_angle), -std::cos(m_angle) ) );
}

DirectedPhotonAction::~DirectedPhotonAction()
{
  delete m_particleGun;
}

// This function is called at the begining of event
void DirectedPhotonAction::GeneratePrimaries( G4Event* anEvent )
{
  // Fire particle
  m_particleGun->GeneratePrimaryVertex( anEvent );
}
