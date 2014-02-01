#include <nbody/Vector3.h>
#include <nbody/Body.h>
#include <gtest/gtest.h>


TEST( bodyTest, values  ) {

  auto r = Vector3f{ 1, 2, 3 };
  auto v = Vector3f{ 10, 20, 30 };
  auto a = Vector3f{ 0, 5, 10 };
  auto m = 1.0f;

 
  nbody::Body b(r, v, a, m);

  ASSERT_FLOAT_EQ( b.position().x() , r.x() );
  ASSERT_FLOAT_EQ( b.position().y() , r.y() );
  ASSERT_FLOAT_EQ( b.position().z() , r.z() );

  ASSERT_FLOAT_EQ( b.velocity().x() , v.x() );
  ASSERT_FLOAT_EQ( b.velocity().y() , v.y() );
  ASSERT_FLOAT_EQ( b.velocity().z() , v.z() );

  ASSERT_FLOAT_EQ( b.force().x() , a.x() );
  ASSERT_FLOAT_EQ( b.force().y() , a.y() );
  ASSERT_FLOAT_EQ( b.force().z() , a.z() );

  ASSERT_FLOAT_EQ( b.mass() , m );
}
