#include <stdlib.h>
#include <iostream>
#include "gtest/gtest.h"

#include "properties.h"
#include "particle.h"
#include "fluid.h"

using namespace std;

TEST (properties,properties){
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

TEST (particle,get_set_props){
  Properties props1;
  Properties props2;
  props1.x = 1.25;
  props1.y = -12.4;
  props1.u = -.5;
  props1.v = 0.0003;
  props1.density = 1.0;
  props1.mass = 0.0;
  props1.pressure = -2039;
  props1.visc = 13;

  int tag = 1;
  int N = 20;

  Particle *part;
  part = new Particle(tag, N, props1);

  // make sure we get the old peroperties properly
  ASSERT_EQ(0,part->get("OLD",props2));
  EXPECT_FLOAT_EQ(props1.x, props2.x);
  EXPECT_FLOAT_EQ(props1.y, props2.y);
  EXPECT_FLOAT_EQ(props1.u, props2.u);
  EXPECT_FLOAT_EQ(props1.v, props2.v);
  EXPECT_FLOAT_EQ(props1.density, props2.density);
  EXPECT_FLOAT_EQ(props1.mass, props2.mass);
  EXPECT_FLOAT_EQ(props1.pressure, props2.pressure);
  EXPECT_FLOAT_EQ(props1.visc, props2.visc);

  // make sure memory isn't all messed up by changing
  // props1 and making sure that doesn't get to part->props
  props1.x = 0;
  props2.x = 0;
  part->get("OLD",props2); // if it worked above, will work here
  EXPECT_FLOAT_EQ(1.25,props2.x);
  
  // now make sure it did change
  ASSERT_EQ(0,part->set("OLD",props1));
  part->get("OLD",props2);
  EXPECT_FLOAT_EQ(props2.x,props1.x);

  delete part;
}

int main(int argc, char** argv){

  cout << "Testing fluid properties: " << endl;

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();

  return 0;
}
