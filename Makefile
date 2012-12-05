#------------------------------------------------------------------------------

SOURCE = TEST_PARTICLE.cc particle.cc
MYPROGRAM = test_particle

CC = g++ -g -Wall

#------------------------------------------------------------------------------

all: $(MYPROGRAM)

$(MYPROGRAM): $(SOURCE)

	$(CC) $(SOURCE) -o $(MYPROGRAM)

clean:

	rm -f $(MYPROGRAM)