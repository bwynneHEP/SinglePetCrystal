#ifndef ActionInitialization_h
#define ActionInitialization_h 1

#include "DecayTimeFinderAction.h"

#include "G4VUserActionInitialization.hh"

// This class is a very simple template that just tells Geant where to look for our custom code
class ActionInitialization : public G4VUserActionInitialization
{
  public:
    ActionInitialization( std::string sourceName );
    ~ActionInitialization() override;

    void Build() const override;

  private:
    std::string m_sourceName;
};

#endif

