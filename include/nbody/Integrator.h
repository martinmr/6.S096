#ifndef _NBODY_INTEGRATOR_H
#define _NBODY_INTEGRATOR_H

#include <nbody/Vector3.h>

namespace nbody {
    
    class System;

    class Integrator {
        Integrator( const System &s ) = delete;
        Integrator& operator=( const System &sys ) = delete;
    public:
        Integrator() {}
        virtual ~Integrator() {}
        virtual void integrateSystem( System &s, float dt ) const { (void)s; (void)dt; } 
    };

} //namespace nbody

#endif // _NBODY_INTEGRATOR_H
