#include <nbody/Body.h>
#include <nbody/constants.h>
#include <nbody/System.h>
#include <nbody/Vector3.h>

#include <fstream>
#include <stdexcept>
#include <iostream>
#include <iomanip>

namespace nbody {
    
    Body& System::body( size_t index ) {
        return _body[index];
    }
    
    Body System::body( size_t index ) const {
        return _body[index];
    }

    size_t System::nBodies() const {
        return _nBodies;
    }
    
    float System::dampingFactor() const {
        return _dampingFactor;
    }

    float System::KineticEnergy() const {
      float K = 0;
      Vector3f v;
      for( size_t i = 0; i < _nBodies; i++ ) {
       // kinE += _body[i].KineticEnergy();
        v = _body[i].velocity();
        K += _body[i].mass() * v.normsq() / 2.0f;
      }
      return K;
    }

    float System::PotentialEnergy() const {
      float U = 0.0f;
      Vector3f r;
      for( size_t i = 0; i < _nBodies - 1; i++ ) {
        for (size_t j = i + 1; j < _nBodies; j++ ) { 
          r = _body[i].position() - _body[j].position();
          U -= NEWTON_G * _body[i].mass() * _body[j].mass()/r.norm();
        }
      }
      return U;
    }
    float System::TotalEnergy() const {
      return KineticEnergy() + PotentialEnergy();
    }

    Vector3f System::Momentum() const {
      auto p = Vector3f( 0.0, 0.0, 0.0 );
      for( size_t i = 0; i < _nBodies; i++ ) {
        p = p + _body[i].mass() * _body[i].velocity();
      }
      return p;
    }

    Vector3f System::AngularMomentum() const {
      auto L = Vector3f( 0.0, 0.0, 0.0 );
      for( size_t i = 0; i < _nBodies; i++ ) {
        L = L + _body[i].mass() * cross( _body[i].position(), _body[i].velocity() );
      }
      return L;
    }

    inline void System::interactBodies( size_t i, size_t j, float softFactor, Vector3f &acc ) const {
        Vector3f r = _body[j].position() - _body[i].position();
        float distance = r.norm() + softFactor;
        float invDist = 1.0f / distance;
        float invDistCubed = cube( invDist );
        acc = acc + NEWTON_G * _body[j].mass() * invDistCubed * r;
    }

    void System::computeGravitation() {
        for( size_t i = 0; i < _nBodies; ++i ) {
            Vector3f acc{ 0.0f, 0.0f, 0.0f };
            for( size_t j = 0; j < _nBodies; ++j ) {
                if( i != j ) {
                    interactBodies( i, j, _softFactor, acc );
                }
            }
            _body[i].force() = acc;
        }
    }

    void System::integrateSystem( float dt ) {
        _integrator.integrateSystem(*this,  dt);
    }

    void System::update( float dt ) {
        computeGravitation();
        integrateSystem( dt );
    }

    void System::readState( std::istream &input ) {
        input >> _nBodies;
        if( _nBodies > MAX_BODIES_RECOMMENDED ) {
            throw std::runtime_error( "Too many input bodies" );
        }
        _body = new Body[_nBodies];
        for( size_t i = 0; i < _nBodies; ++i ) {
            input >> _body[i];
        }
    }

    void System::writeState( std::ostream &output ) const {
        output << _nBodies << "\n";
        for( size_t i = 0; i < _nBodies; ++i ) {
            output << _body[i] << "\n";
        }
    }

} // namespace nbody
