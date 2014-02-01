#include <nbody/RK4Integrator.h>
#include <nbody/SimpleIntegrator.h>
#include <nbody/System.h>
#include <nbody/Vector3.h>
#include <cmath>

namespace nbody {
  /* Runge-Kutta method of solving differential equation:
   * \dot{y} = f(t, y), y(t_0) = y_0.
   * For time step h > 0 we find:
   * y_{n+1} = y_n + 1/6 * dt *( k_1 + 2*k_2 + 2*k_3 + k_4 )
   * t_{n+1} = t_n + dt, where increments k_i (i = 1, 2, 3, 4) are
   * k_1 = f( t_n, y_n);
   * k_2 = f( t_n + 1/2 * dt, y_n + dt/2 * k_1 );
   * k_3 = f( t_n + 1/2 * dt, y_n + dt/2 * k_2 );
   * k_4 = f( t_n + dt, y_n + dt * k_3 ).
   * For nbody system y = { pos[j], vel[j] }, f = { vel[j], acc[j] }.
   */
  System* RK4Integrator::compute_k1( System &s, float dt ) {
    Vector3f rs, vs, v, a;
    SimpleIntegrator *si = new SimpleIntegrator();
    System *k1 = new System( s.nBodies(), si );
    // computing k_1 * dt/2
    for( size_t i = 0; i < s.nBodies(); ++i ) {
      rs = s.body(i).position();
      vs = s.body(i).velocity();
      v = vs;
      a = s.body(i).force();

      k1->body(i).position() = rs + ( v * dt / 2.0f );
      k1->body(i).velocity() = ( vs + a * dt / 2.0f ) * ( ( float ) sqrt( s.dampingFactor() ) );
    }
    k1->computeGravitation();
    return k1;
  }

  System* RK4Integrator::compute_k2( System &s, System *k1, float dt ) {
    Vector3f rs, vs, v, a;
    SimpleIntegrator *si = new SimpleIntegrator();
    System *k2 = new System( s.nBodies(), si );
    // computing k_2 * dt/2
    for( size_t i = 0; i < s.nBodies(); ++i ) {
      rs = s.body(i).position();
      vs = s.body(i).velocity();
      v = k1->body(i).velocity();
      a = k1->body(i).force();

      k2->body(i).position() = rs + ( v * dt / 2.0f );
      k2->body(i).velocity() = ( vs + a * dt / 2.0f ) * ( ( float ) sqrt( s.dampingFactor() ) );
    }
    k2->computeGravitation();
    return k2;
  }

  System* RK4Integrator::compute_k3( System &s, System *k2, float dt ) {
    Vector3f rs, vs, v, a;
    SimpleIntegrator *si = new SimpleIntegrator();
    System *k3 = new System( s.nBodies(), si );
    // computing k_3 * dt
    for( size_t i = 0; i < s.nBodies(); ++i ) {
      rs = s.body(i).position();
      vs = s.body(i).velocity();
      v = k2->body(i).velocity();
      a = k2->body(i).force();

      k3->body(i).position() = rs + ( v * dt );
      k3->body(i).velocity() = ( vs + a * dt ) * ( (float)  s.dampingFactor() );
    }
    k3->computeGravitation();
    return k3;
  }


  System* RK4Integrator::compute_k4( System &s, System *k3, float dt ) {
    Vector3f rs, vs, v, a;
    SimpleIntegrator *si = new SimpleIntegrator();
    System *k4 = new System( s.nBodies(), si );
    // computing k_4 * dt
    for( size_t i = 0; i < s.nBodies(); ++i ) {
      rs = s.body(i).position();
      vs = s.body(i).velocity();
      v = k3->body(i).velocity();
      a = k3->body(i).force();

      k4->body(i).position() = rs + ( v * dt );
      k4->body(i).velocity() = ( vs + a * dt ) * s.dampingFactor();
    }
    return k4;
  }

  void RK4Integrator::integrateSystem( System &s, float dt ) {
    Vector3f dr, dv;
    // compute increments
    System *k1 = compute_k1( s, dt );
    System *k2 = compute_k2( s, k1, dt );
    System *k3 = compute_k3( s, k2, dt ); 
    System *k4 = compute_k4( s, k3, dt );
    // compute positions and velocities
    for( size_t i = 0; i < s.nBodies(); ++i ) {
      dr =  2.0f * ( k1->body(i).position() - s.body(i).position() ) +
            2.0f * 2.0f * ( k2->body(i).position() - s.body(i).position() ) +
            2.0f * ( k3->body(i).position() - s.body(i).position() ) +
            ( k4->body(i).position() - s.body(i).position() );  

      dv =  2.0f * ( k1->body(i).velocity() - s.body(i).velocity() ) +
            2.0f * 2.0f * ( k2->body(i).velocity() - s.body(i).velocity() ) +
            2.0f * ( k3->body(i).velocity() - s.body(i).velocity() ) +
            ( k4->body(i).velocity() - s.body(i).velocity() );

      s.body(i).position() =  s.body(i).position() + dr / 6.0f;
      s.body(i).velocity() = s.body(i).velocity() + dv / 6.0f;
    }
    delete k1;
    delete k2;
    delete k3;
    delete k4;
  }

} //namespace nbody
