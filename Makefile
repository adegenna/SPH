#---------------------------------------

objs_fltest = test_fluid.o fluid.o particle.o
objs_sph = sph.o particle.o fluid.o initialize.o incompinvisc.o  splinekernel.o gaussiankernel.o euler.o output.o

CC = g++ -g -Wall

#--------------------------------------


# not sure what the correct dependencies are.

all: sph test_fluid

sph: $(objs_sph)
	$(CC) -o $@ $^

# to run this the user should have set the environment variable GTEST to
# something equivalent to /usr/src/gtest/include/
test_fluid: $(objs_fltest)
	$(CC) -o $@ $^ -I$(GTEST) -lpthread libgtest.a

clean:
	rm -f *.o
