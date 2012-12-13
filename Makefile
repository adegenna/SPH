#---------------------------------------

objs_fltest = fluid.o particle.o
objs_sph = sph.o fluid.o initialize.o incompinvisc.o euler.o output.o

CC = g++ -g -Wall

#--------------------------------------


# not sure what the correct dependencies are.

all: test_fluid sph

sph: $(objs_sph)
	$(CC) -o $@ $^

test_fluid: $(objs_fltest)
	$(CC) -o test_fluid test_fluid.cc -I/usr/src/gtest/include/ -lpthread libgtest.a

clean:
	rm -f *.o
