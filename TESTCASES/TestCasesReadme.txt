This folder contains input and output files for some simple test simulations. Sample usage is as follows:

# Dam break, then flow over a triangular obstruction:
# Output file given in ExampleOutputs/dambreakoutput.dat

sph TESTCASES/ExampleInputs/box12p5_12p5fluid.dat TESTCASES/ExampleInputs/Damwithobstructionboundary.dat 100 0.001 euler spline

# sphere falling on an inclined plane:
# Output file given in ExampleOutputs/sphereoninclineoutput.dat

sph TESTCASES/ExampleInputs/sphere10_10.dat TESTCASES/ExampleInputs/InclinedBoundary_m1_c4.dat 100 0.001 euler spline

# two fluids of different densities mixing
# Output file given in ExampleOutputs/twofluidsmixingoutput.dat

sph TESTCASES/ExampleInputs/spheresdifferentdensities.dat TESTCASES/ExampleInputs/Box23by20.dat 100 0.001 euler spline

A sample Matlab script to visualize the output (fluid.dat by default) file is in the ExampleOutput folder
