#ifndef _NBODY_SIMULATION_H
#define _NBODY_SIMULATION_H

#include <nbody/Integrator.h>
#include <nbody/SimpleIntegrator.h>
#include <nbody/System.h>
#include <nbody/Window.h>

#include <iosfwd>
#include <string>

namespace nbody {

  class Simulation {
    System *_system;
    std::string _name;
    Window *_window;
    float *_buf; 
    Simulation( const Simulation& sim ) = delete;
    Simulation& operator=( const Simulation& sim ) = delete;
    std::string generateName();
  public:
    Simulation( std::istream &input ) : _system{new System(input, new SimpleIntegrator())}, _name{ generateName() }, _window{ nullptr } , _buf{nullptr} {}
    Simulation() : _system{nullptr}, _name{"Simulation"}, _window{nullptr}, _buf{nullptr} {}
    void evolveSystem( int nSteps, float dt );
    void loadRun( std::istream &input );
    void saveRun() const;
  };

} // namespace nbody

#endif // _NBODY_SIMULATION_H
