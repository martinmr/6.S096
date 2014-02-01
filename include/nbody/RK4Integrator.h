#ifndef _NBODY_RK4_INTEGRATOR_H
#define _NBODY_RK4_INTEGRATOR_H

#include <nbody/Integrator.h>
#include <nbody/System.h>
typedef System* SystemPtr;

namespace nbody {
    /* Runge-Kutta method of solving differential equation:
     * \dot{y} = f(t, y), y(t_0) = y_0.
     * For time step h > 0 we find:
     * y_{n+1} = y_n + 1/6 * ( k_1 + 2*k_2 + 2*k_3 + k_4 )
     * t_{n+1} = t_n + h, where increments k_i (i = 1, 2, 3, 4) are
     * k_1 = f( t_n, y_n);
     * k_2 = f( t_n + 1/2 * h, y_n + h/2 * k_1 );
     * k_3 = f( t_n + 1/2 * h, y_n + h/2 * k_2 );
     * k_4 = f( t_n + h, y_n + h *k_3 ).
     * For more information: http://en.wikipedia.org/wiki/Runge-Kutta_methods`
     * For nbody system y = { pos[j], vel[j] }, f = { vel[j], acc[j] }.
    */
    class RK4Integrator : public Integrator {
    public:
        void integrateSystem( System &s, float dt );
        System* compute_k1( System &s, float dt );
        System* compute_k2( System &s, System *k1, float dt );
        System* compute_k3( System &s, System *k2, float dt );
        System* compute_k4( System &s, System *k3, float dt );
    };

}

#endif //_NBODY_RK4_INTEGRATOR_H

