#include "particle.h"
#include "initialize.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <string>


using namespace std;

int main() {
//    double* r1 = new double[2]; // Position of P1
//    double* v1 = new double[2]; // Velocity of P1
//    double* r2 = new double[2]; // Position of P2
//    double* v2 = new double[2]; // Velocity of P2
//    
//    double** x_in = new double*[2]; // Pointer to the pointers r1 and r2
//    double** v_in = new double*[2]; // Pointer to the pointers v1 and v2
    
    
    //  double** x = new double*[2]; // Pointer to the pointers r1 and r2
    //  double** v = new double*[2]; // Pointer to the pointers v1 and v2
    
    // **************** Set values ******************
    //
//    double mass; // = 1.0;
//    double visc; // = 2.0;
//    double x1;
//    double x2;
//    double xdot1;
//    double xdot2;
    // **********************************************
    
    // ************** Initialization ****************
    //int N = 2; // Number of particles
    
    
    cout <<"here" <<endl; 
    Particle** particles;
    string input = "input.dat";
    initialize(input,*particles);
    
    //FILE* finput;
//	finput = fopen("input.dat","r");
//    cout <<"here2" <<endl; 
//    float NParticlesf;
//    int NParticles;
//    
//    fscanf(finput,"%f",&NParticlesf);
//    NParticles = int(NParticlesf);
//	Particle** particles = new Particle*[NParticles]; // Pointer to particle pointers
//    double** x = new double*[2]; // Pointer to the pointers r1 and r2
//    double** v = new double*[2]; // Pointer to the pointers v1 and v2
//    cout <<"Nparticles = "<< NParticles <<endl; 
//    
//    
//    for (int i=0;i<NParticles;i++){
//        //fscanf(finput, "%lf %lf %lf %lf %lf %lf",x_in[0],x_in[1],v_in[0],v_in[1],&mass,&visc);
//        fscanf(finput, "%lf %lf %lf %lf %lf %lf",&x1,&x2,&xdot1,&xdot2,&mass,&visc);
//        
//        x[i] = &x1;
//        x[i][1] = x2;
//        v[i] = &xdot1;
//        v[i][1] = xdot2;
//        
//    	particles[i] = new Particle(i+1,x[i],v[i],mass,visc);
//    }
//    fclose(finput);
    
    //for (int i = 0; i < NParticles; i++) {
        //  particles[i] = new Particle(i+1, x[i], v[i], mass, visc);
    //}
    
    
    // *********************************************
    
    // ********* Example Method Usages *************
    double* location1 = new double[2];
    double* location2 = new double[2];
    particles[0]->GetLocation(location1);
    particles[1]->GetLocation(location2);
    
    printf("P1 Location = %e %e \n", location1[0], location1[1]);
    printf("P2 Location = %e %e \n", location2[0], location2[1]);
    
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
