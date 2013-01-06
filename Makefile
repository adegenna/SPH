#---------------------------------------

objs_tests = tests.o properties_test.o kvector_test.o particle_test.o fluid_test.o kernel_test.o particle.o fluid.o gaussiankernel.o splinekernel.o
objs_sph = sph.o particle.o fluid.o initialize.o incompinvisc.o splinekernel.o gaussiankernel.o euler.o output.o

CXXFLAGS = -I$(BOOST) -g -c -Wall

# To enable compiler optimizations, run: NDEBUG=1 make
ifdef NDEBUG
	CXXFLAGS = -c -O3 -Wall
    LDFLAGS = -O3
endif

#--------------------------------------


# not sure what the correct dependencies are.

all: sph tests

sph: $(objs_sph)
	$(CXX) -o $@ $^ $(LDFLAGS)

# to run this the user should have set the environment variable GTEST to
# something equivalent to /usr/src/gtest/include/
tests: $(objs_tests)
	$(CXX) -o $@ $^ -I$(GTEST) -lpthread libgtest.a

clean:
	rm -f *.o

cleanout:
	rm -f fluid*dat
