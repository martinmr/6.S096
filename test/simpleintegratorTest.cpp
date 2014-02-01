#include <nbody/Vector3.h>
#include <nbody/Body.h>
#include <nbody/SimpleIntegrator.h>
#include <nbody/System.h>
#include <nbody/Integrator.h>
#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <nbody/Simulation.h>

TEST( simpleintegratorTest, integratesystem  ) {

  std::ifstream input{ "test/test-file.txt" };

  auto simp = new nbody::SimpleIntegrator;

  nbody::System sys( input, simp );

  ASSERT_FLOAT_EQ( sys.body(0).position().x() , 1.0f );
  ASSERT_FLOAT_EQ( sys.body(0).velocity().x() , 1.0f );

  sys.integrateSystem( 1.0 );

  ASSERT_EQ( sys.nBodies() , 1u );  
  ASSERT_FLOAT_EQ( sys.dampingFactor() , 1.0f );  

  auto r = sys.body(0).position();
  auto v = sys.body(0).velocity();

  ASSERT_FLOAT_EQ( v.x() , 2.0f );
  ASSERT_FLOAT_EQ( v.y() , 11.0f );
  ASSERT_FLOAT_EQ( v.z() , 101.0f ); 

  ASSERT_FLOAT_EQ( r.x() , 3.0f );
  ASSERT_FLOAT_EQ( r.y() , 13.0f );
  ASSERT_FLOAT_EQ( r.z() , 104.0f ); 

  delete simp;
}
