#include "particle.h"
#include "initialize.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <string>


using namespace std;

int main() {
    
    // ************** Initialization ****************

    Particle** particles = new Particle*;
    string input = "input.dat";
    initialize(input,particles);
    
    // *********************************************
    
    // ********* Example Method Usages *************
    double* location1 = new double[2];
    double* location2 = new double[2];
    cout <<"here8" <<endl;
    
    particles[0]->GetLocation(location1);
    cout <<"here8a" <<endl;
    
    particles[1]->GetLocation(location2);
    cout <<"here9" <<endl;
    printf("P1 Location = %e %e \n", location1[0], location1[1]);
    printf("P2 Location = %e %e \n", location2[0], location2[1]);
    cout <<"here10" <<endl;
    double dist = particles[0]->Distance(location2);  // Get distance to p2
    printf("Distance = %e \n", dist);
    
    double* velocity1 = new double[2];
    double* velocity2 = new double[2];
    particles[0]->GetVelocity(velocity1);
    particles[1]->GetVelocity(velocity2);
    printf("P1 Velocity = %e %e \n", velocity1[0], velocity1[1]);
    printf("P2 Velocity = %e %e \n", velocity2[0], velocity2[1]);
    
    //delete r1; delete r2; delete v1; delete v2;
    delete location1; delete location2; delete velocity1; delete velocity2;
    delete particles;
    // *********************************************
    
    return 0;
}
