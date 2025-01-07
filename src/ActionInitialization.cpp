#include "ActionInitialization.h"
#include "DirectedPhotonAction.h"
#include "NormalPhotonAction.h"

#include "G4SystemOfUnits.hh"

ActionInitialization::ActionInitialization( std::string sourceName )
  : G4VUserActionInitialization()
  , m_sourceName( sourceName )
{
}

ActionInitialization::~ActionInitialization()
{
}

void ActionInitialization::Build() const
{
  if ( m_sourceName.substr( 0, 11 ) == "PhotonAngle" )
  {
    G4double incidentAngleDegree = strtod( m_sourceName.substr( 11 ).c_str(), nullptr );
    
    this->SetUserAction( new DirectedPhotonAction( incidentAngleDegree ) );
  }
  else if ( m_sourceName.substr( 0, 12 ) == "PhotonOrigin" )
  {
    G4double originZmm = strtod( m_sourceName.substr( 12 ).c_str(), nullptr );
    
    this->SetUserAction( new NormalPhotonAction( originZmm ) );
  }
  else
  {
    std::cerr << "Unrecognised source name: " << m_sourceName << std::endl;
    exit(1);
  }
}
