#---------------------------------------

objs_tests = tests.o properties_test.o kvector_test.o particle_test.o fluid_test.o kernel_test.o particle.o fluid.o gaussiankernel.o splinekernel.o
objs_sph = sph.o particle.o fluid.o initialize.o incompinvisc.o splinekernel.o gaussiankernel.o euler.o output.o

CC = g++ -g -Wall

#--------------------------------------


# not sure what the correct dependencies are.

all: sph tests

sph: $(objs_sph)
	$(CC) -o $@ $^

# to run this the user should have set the environment variable GTEST to
# something equivalent to /usr/src/gtest/include/
tests: $(objs_tests)
	$(CC) -o $@ $^ -I$(GTEST) -lpthread libgtest.a

clean:
	rm -f *.o
