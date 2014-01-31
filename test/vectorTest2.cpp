#include <nbody/Vector3.h>
#include <gtest/gtest.h>

TEST( vectorTest2, scalarmultiplication ) {
  auto v = Vector3f{ 1, 2, 3 };
  auto f = 2.0f;

  auto a = v * f;
  auto b = f * v;

  ASSERT_FLOAT_EQ( a.x() , 2.0f );
  ASSERT_FLOAT_EQ( a.y() , 4.0f );
  ASSERT_FLOAT_EQ( a.z() , 6.0f );

  ASSERT_FLOAT_EQ( b.x() , 2.0f );
  ASSERT_FLOAT_EQ( b.y() , 4.0f );
  ASSERT_FLOAT_EQ( b.z() , 6.0f );
}

TEST( vectorTest2, scalardivision ) {
  auto v = Vector3f{ 1, 2, 3 };
  auto f = 2.0f;

  auto a = v / f;

  ASSERT_FLOAT_EQ( a.x() , 0.5f );
  ASSERT_FLOAT_EQ( a.y() , 1.0f );
  ASSERT_FLOAT_EQ( a.z() , 1.5f );
}

TEST( vectorTest2, norm ) {
  auto v = Vector3f{ 1, 2, 3 };

  ASSERT_FLOAT_EQ( v.normsq() , 14.0f );
  ASSERT_FLOAT_EQ( v.norm() , sqrt(14.0f) ); 
}

TEST( vectorTest2, addition ) {
  auto a = Vector3f{ 1, 2, 3 };
  auto b = Vector3f{ 4, 5, 6 };
  auto c = a + b;

  ASSERT_FLOAT_EQ( c.x() , 5.0f );
  ASSERT_FLOAT_EQ( c.y() , 7.0f );
  ASSERT_FLOAT_EQ( c.z() , 9.0f );
}

TEST( vectorTest2, subtraction ) {
  auto a = Vector3f{ 1, 2, 3 };
  auto b = Vector3f{ 4, 5, 6 };
  auto c = a - b;

  ASSERT_FLOAT_EQ( c.x() , -3.0f );
  ASSERT_FLOAT_EQ( c.y() , -3.0f );
  ASSERT_FLOAT_EQ( c.z() , -3.0f );
}
