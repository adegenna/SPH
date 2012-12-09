#------------------------------------------------------------------------------

SOURCE =  particle.cc initialize.cc maintest.cc SplineKernel.cc incompinvisc.cc GaussianKernel.cc
MYPROGRAM = maintest

CC = g++ -g -Wall

#------------------------------------------------------------------------------

all: $(MYPROGRAM)

$(MYPROGRAM): $(SOURCE)

	$(CC) $(SOURCE) -o $(MYPROGRAM)


clean:

	rm -f $(MYPROGRAM)
