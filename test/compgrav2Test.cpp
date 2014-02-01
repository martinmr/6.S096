#include <nbody/Vector3.h>
#include <nbody/Body.h>
#include <nbody/SimpleIntegrator.h>
#include <nbody/System.h>
#include <gtest/gtest.h>


TEST( compgravTest2, ComputeGravity  ) {

  auto simp = new nbody::SimpleIntegrator;

  nbody::System sys( 3, simp );
  // points are at (0,0,0), (1,0,0), and (2,0,0)
  // velocity and acceleration don't matter for force calculation
  for ( size_t i = 0; i < sys.nBodies(); i++ ) {

     Vector3f r{1.0f*i, 0, 0};
     Vector3f v{0, 0, 0};     
     Vector3f a{0, 0, 0}; 

     sys.body(i).position() = r;
     sys.body(i).velocity() = v;
     sys.body(i).force() = a;

     sys.body(i).mass() = 1;
  }

  // Set softening to 0 so it doesn't effect values
  sys.setSoftening(0);

  sys.computeGravitation();

  // acceleration is only in x-direction
  ASSERT_FLOAT_EQ( sys.body(0).force().x() , 1.25f );
  ASSERT_FLOAT_EQ( sys.body(1).force().x() , 0.0f );
  ASSERT_FLOAT_EQ( sys.body(2).force().x() , -1.25f );
}
