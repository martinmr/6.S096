#include <nbody/Vector3.h>
#include <nbody/Body.h>
#include <nbody/SimpleIntegrator.h>
#include <nbody/System.h>
#include <gtest/gtest.h>

// This unit test examines how System::update calls the functions ComputationGravation and SimpleIntegrator
TEST( updateTest, iteration  ) {

  auto simp = new nbody::SimpleIntegrator;

  nbody::System sys( 2, simp );

  for ( size_t i = 0; i < sys.nBodies(); i++ ) {

     Vector3f r{0.0f, i*3.0f, i*4.0f};
     Vector3f v{1, 1, 1};     
     Vector3f a{0, 0, 0}; 

     sys.body(i).position() = r;
     sys.body(i).velocity() = v;
     sys.body(i).force() = a;

     sys.body(i).mass() = 1;
  }

  sys.setSoftening(0);

  sys.update( 1.0f );

  auto r1 = sys.body(0).position();
  auto v1 = sys.body(0).velocity();
  auto r2 = sys.body(1).position();
  auto v2 = sys.body(1).velocity();


  ASSERT_FLOAT_EQ( r1.x() , 1.0f );
  ASSERT_FLOAT_EQ( r1.y() , 1.024f );
  ASSERT_FLOAT_EQ( r1.z() , 1.032f ); 

  ASSERT_FLOAT_EQ( v1.x() , 1.0f );
  ASSERT_FLOAT_EQ( v1.y() , 1.024f );
  ASSERT_FLOAT_EQ( v1.z() , 1.032f ); 

  ASSERT_FLOAT_EQ( r2.x() , 1.0f );
  ASSERT_FLOAT_EQ( r2.y() , 3.976f );
  ASSERT_FLOAT_EQ( r2.z() , 4.968f ); 

  ASSERT_FLOAT_EQ( v2.x() , 1.0f );
  ASSERT_FLOAT_EQ( v2.y() , 0.976f );
  ASSERT_FLOAT_EQ( v2.z() , 0.968f );
}
