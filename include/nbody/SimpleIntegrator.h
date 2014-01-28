#ifndef _NBODY_SIMPLE_INTEGRATOR_H
#define _NBODY_SIMPLE_INTEGRATOR_H

#include <nbody/Integrator.h>
#include <nbody/System.h>

namespace nbody {
    
    class SimpleIntegrator : public Integrator {
    public:
        void integrateSystem( System &s, float dt ) const;
    };

}

#endif //_NBODY_SIMPLE_INTEGRATOR_H

