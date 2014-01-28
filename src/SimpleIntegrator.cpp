#include <nbody/SimpleIntegrator.h>
#include <nbody/System.h>
#include <nbody/Vector3.h>

namespace nbody {

    void SimpleIntegrator::integrateSystem( System &s, float dt ) const{
        Vector3f r, v, a;
        for( size_t i = 0; i < s.nBodies(); ++i ) {
            r = s.body(i).position();
            v = s.body(i).velocity();
            a = s.body(i).force();

            v = v + ( a * dt );
            v = v * s.dampingFactor();
            r = r + v * dt;

            s.body(i).position() = r;
            s.body(i).velocity() = v;
        }
    }

} //namespace nbody
