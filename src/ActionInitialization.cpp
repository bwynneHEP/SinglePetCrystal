#include "ActionInitialization.h"
#include "DirectedPhotonAction.h"

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
  if ( m_sourceName.substr( 0, 6 ) == "Photon" )
  {
    G4double incidentAngleDegree = strtod( m_sourceName.substr( 6 ).c_str(), nullptr );
    
    this->SetUserAction( new DirectedPhotonAction( incidentAngleDegree ) );
  }
  else
  {
    std::cerr << "Unrecognised source name: " << m_sourceName << std::endl;
    exit(1);
  }
}
