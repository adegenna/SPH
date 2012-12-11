#include "Kernel.h"
#include "Fluid.h"
#include "SplineKernel.h"
#include "GaussianKernel.h"
#include "particle.h"
#include "initialize.h"
#include "incompinvisc.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <string>
#include <iostream>


using namespace std;

double InnerProduct2D(double x1, double y1, double x2, double y2) {
    double IP = x1 * x2 + y1 * y2;
    return IP;
}

void PrintState(double t, double x, double v) {
    printf("%15.8f", t);
    printf("%15.8f", x);
    printf("%15.8f", v);
    printf("\n");
}

//really hacky testing

int main() {

    //number of particles
    //const int N = 2;
    const double dt = 0.01;
    const double Nsteps = 20;
    
    Particle** particles = new Particle*;
    string input = "input.dat";
    
    int N;  //Number of Particles
    
    initialize(input,particles,N);
    //initialize random data
    
    //cout <<N<<endl;
    
    //define initial properties
    double smoothinglength = 1;
    double rho[N];
    double Mass[N];
    double Pressure[N];
    
    double x[N];
    double y[N];
    double xdot[N];
    double ydot[N];
    
    double PonRhoSq[N];
    Properties properties;
    
    for(int i=0;i<N;i++){
        particles[i]->Get("OLD",properties);
        Mass[i] = 2.;
        rho[i] = 2.;
        xdot[i]=0.;
        ydot[i]=0.;
    }
    
    x[0] = 0.;
    y[0] = 0.;
    x[1] = 1.;
    y[1] = 0.;

    rho[1]=2.;
    xdot[0]=0.1;
    
    double B = 100;
    double gamma = 7;
    
    //use typical eqn of state for liquids
    for(int i=0;i<N;i++){ 
    	Pressure[i] = B * (pow(rho[i],gamma)-1.);
    }
    //update every timestep
    double drho[N];
    //double du;
    double dxdot[N],dydot[N];
    //double uold;
    double t = 0;
    FILE* outfile = fopen("output.dat","w");
    //print intial conditions
    for (int i=0;i<N;i++) {
    	fprintf(outfile,"%5d %.5e %.5e %.5e %.5e %.5e %.5e %.5e\n",0,t,x[i],y[i],xdot[i],ydot[i],rho[i],Pressure[i]);
    }
    
    Kernel *myKer;
    //myKer = new SplineKernel(smoothinglength);
    myKer = new GaussianKernel(smoothinglength);
    
    Physics *myPhysics;
    myPhysics = new IncompInvisc();
    Integrator *integrator = new Euler(dt, *myPhysics);
    //Properties PartProps;
    
    
    for(int k=1; k <= Nsteps; k++) {
        t +=dt;
        //myFluid->update(particles,myKer);
        
        for(int a=0;a<N;a++){
            //reinitialize temporary variables
            drho[a] = 0;
            dxdot[a] = 0;
            dydot[a] = 0;
            PonRhoSq[a] = Pressure[a]/pow(rho[a],2);
            Vector xa = {x[a],y[a]};
            
            myPhysics->advance(particles[a],myKer);
           // myFluid->update(particles[a]);
            particles[a]->Get("OLD",properties);
            
            
            
            cout <<"x[a] = " << properties.x <<endl;
            cout <<"y[a] = " << properties.y <<endl;
            cout <<"u[a] = " << properties.u <<endl;
            cout <<"v[a] = " << properties.v <<endl;
            
            
            for(int i=0;i<N;i++){
                
            //    cout << "a =" <<a<<endl;
            //   cout << "i =" <<i<<endl;
                
                PonRhoSq[i] = Pressure[i]/pow(rho[i],2);
                Vector xi = {x[i],y[i]};
                Vector Kgrad = myKer->gradW(xa,xi);
                
                //cout << Kgrad.x << endl;
                drho[a] += Mass[i] * InnerProduct2D(xdot[a]-xdot[i],ydot[a]-ydot[i],Kgrad.x,Kgrad.y);  //,*Kx,*Ky);
                //du += Mass[i] * (PonRhoSq[i]-PonRhoSq[a])*KernelGradMag(distance,smoothinglength);
                dxdot[a] += -Mass[i] * (PonRhoSq[i]+PonRhoSq[a]) * Kgrad.x;//(*Kx);
                dydot[a] += -Mass[i] * (PonRhoSq[i]+PonRhoSq[a]) * Kgrad.y;//(*Ky);
                
            //    cout << a <<"    "  <<Kx<< "   " << Ky <<endl;
            }
            
            
        }
        //update all positions, velocities, densities, pressures etc.
        // should be set velocity
        for(int a=0;a<N;a++){
            myFluid->update(particles[a]);
            rho[a] += drho[a]*dt; 
            Pressure[a] = B * (pow(rho[a],gamma)-1.);
        
            x[a] += xdot[a] * dt;
            y[a] += ydot[a] * dt;
            xdot[a] += dxdot[a]*dt;
            ydot[a] += dydot[a]*dt;
            
        fprintf(outfile,"%5d %.5e %.5e %.5e %.5e %.5e %.5e %.5e\n",k,t,x[a],y[a],xdot[a],ydot[a],rho[a],Pressure[a]);
        //fflush(outfile);
        }
    }
    
    return 0;
}
