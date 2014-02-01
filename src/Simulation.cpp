#include <nbody/GlutWrapper.h>
#include <nbody/Shaders.h>
#include <nbody/Window.h>
#include <nbody/Vector3.h>
#include <nbody/SimpleIntegrator.h>
#include <nbody/RK4Integrator.h>
#include <nbody/Simulation.h>

#include <glload/gl_3_0.h>
#include <glload/gll.hpp>
#include <GL/freeglut.h>

#include <iostream>
#include <sstream>
#include <chrono>
#include <stdexcept>
#include <string>
#include <fstream>

namespace nbody {

    // Silly function for generating a unique simulation file run output name
    std::string Simulation::generateName() {
        using std::chrono::system_clock;
        using namespace std::chrono;
        std::tm timeinfo = std::tm();
        timeinfo.tm_year = 114;   // year: 2014
        timeinfo.tm_mon = 0;      // month: january
        timeinfo.tm_mday = 27;     // day: 27th
        std::time_t tt = std::mktime( &timeinfo );

        system_clock::time_point tp = system_clock::from_time_t( tt );
        system_clock::duration d = system_clock::now() - tp;
        std::ostringstream os; os << duration_cast<seconds>( d ).count() << "-sim.txt";
        return os.str();
    }

    void Simulation::loadRun( std::istream &input ) {
        if( _system != nullptr ) {
            throw std::runtime_error( "Tried to attach new system to running simulation!" );
        } else {
            RK4Integrator *integrator = new RK4Integrator();
            _system = new System{input, integrator};
        }
    }

    void Simulation::evolveSystem( int nSteps, float dt ) {
        if( _system != nullptr ) {
            size_t N = _system->nBodies(); 
            size_t bufSize = (4 * N);
            _buf = new float[bufSize];
            for( size_t i = 0; i < N; ++i ) {
                Vector3f position = _system->body( i ).position();
                _buf[4*i] = position.x();
                _buf[4*i+1] = position.y();
                _buf[4*i+2] = position.z();
                _buf[4*i+3] = 1.0f;
            }

            nbody::Shaders shaders;
            shaders.addToVertexList( nBodyShaders::vertex1 );
            shaders.addToFragmentList( nBodyShaders::fragment1 );
            _window = new Window{ "N-Body Simulation", _system, nSteps, dt,
                         nbody::GlutWrapper::NDEBUG}; 
            char ** argv = new char *[1];
            _window->init( 0, argv, 500, 500, &shaders, bufSize, _buf );
            delete [] argv;
            _window->run(); 
        } else {
            throw std::runtime_error( "Tried to evolve simulation with no system!" );
        }
    }

    void Simulation::saveRun() const {
        std::ofstream output{ _name };
        _system->writeState( output );
    }

} // namespace nbody
