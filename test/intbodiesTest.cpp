#include <nbody/Vector3.h>
#include <nbody/Body.h>
#include <nbody/SimpleIntegrator.h>
#include <nbody/System.h>
#include <gtest/gtest.h>


TEST( intbodiesTest, InteractBodies  ) {

  auto simp = new nbody::SimpleIntegrator;

  nbody::System sys( 2, simp );

  for ( size_t i = 0; i < sys.nBodies(); i++ ) {

     Vector3f r{0.0f, i*3.0f, i*4.0f};
     Vector3f v{0, 0, 0};     
     Vector3f a{0, 0, 0}; 

     sys.body(i).position() = r;
     sys.body(i).velocity() = v;
     sys.body(i).force() = a;

     sys.body(i).mass() = 1;
  }

  Vector3f acc{ 0.0f, 0.0f, 0.0f };

  sys.interactBodies( 0, 1, 0, acc);

  ASSERT_FLOAT_EQ( acc.x() , 0.0f );
  ASSERT_FLOAT_EQ( acc.y() , 0.024f );
  ASSERT_FLOAT_EQ( acc.z() , 0.032f ); 

}
