/** 
 * \file
 * 
 * \brief Tests for Properties
 */
#include "properties_test.h"

/// tests that Properties initializes properly
TEST (PropertiesTest,checkAllProps){
  Properties props;
  props.x = 1.25;
  props.y = -12.4;
  props.u = -.5;
  props.v = 0.0003;
  props.density = 1.0;
  props.mass = 0.0;
  props.pressure = -2039;
  props.visc = 13;
  EXPECT_FLOAT_EQ(1.25, props.x);
  EXPECT_FLOAT_EQ(-12.4, props.y);
  EXPECT_FLOAT_EQ(-.5, props.u);
  EXPECT_FLOAT_EQ(0.0003, props.v);
  EXPECT_FLOAT_EQ(1.0, props.density);
  EXPECT_FLOAT_EQ(0.0, props.mass);
  EXPECT_FLOAT_EQ(-2039, props.pressure);
  EXPECT_FLOAT_EQ(13, props.visc);
}
