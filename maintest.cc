#include "Kernel.h"
#include "SplineKernel.h"
#include "particle.h"
#include "initialize.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <string>
#include <iostream>


using namespace std;

double KernelGradMag(double distance,double smoothinglength) {
    //Gaussian Kernel
    double disthat = distance/smoothinglength;
    double rtpi = sqrt(4.*atan(1.));
    double W = exp(-pow(disthat,2))/smoothinglength/rtpi;
    double gradW = 2*disthat/smoothinglength*W; //took out -ve
    return gradW;
}

void KernelGrad(double x1, double y1, double x2, double y2, double smoothinglength, double* K1, double* K2) {
    double rMag = sqrt(pow(x2-x1,2)+pow(y2-y1,2));
    double KMag = KernelGradMag(rMag,smoothinglength);
    //cout <<"rmag = " <<rMag<<endl;
    //cout <<"Kmag = " <<KMag<<endl;
    
    if(rMag =! 0.) {
         *K1 = -(x2-x1)/rMag*KMag;
         *K2 = -(y2-y1)/rMag*KMag;
    }
    else { 
         *K1 = 0.;
         *K2 = 0.;
    }
    
    //cout <<"Kx = " <<*K1<<endl;
    //cout <<"Ky = " <<*K2<<endl;
//    cout <<"address Kx = " <<K1<<endl;
//    cout <<"address Ky = " <<K2<<endl;

}

double InnerProduct2D(double x1, double y1, double x2, double y2) {
    double IP = x1 * x2 + y1 * y2;
//    cout << "x1 = " <<x1<<endl;
//    cout << "x2 = " <<x2<<endl;
//    cout << "y1 = " <<y1<<endl;
//    cout << "y2 = " <<y2<<endl;    
//    cout << "IP = " <<IP<<endl;
   // cout << "IP2 = " << x1 * x2 + y1 * y2 <<endl; 
    return IP;
}

//void ICload

void PrintState(double t, double x, double v) {
    printf("%15.8f", t);
    printf("%15.8f", x);
    printf("%15.8f", v);
    printf("\n");
}

//really hacky, crappy testing

int main() {

    //number of particles
    const int N = 2;
    const double dt = 0.01;
    const double Nsteps = 20;
    
    Particle** particles = new Particle*;
    string input = "input.dat";
    initialize(input,particles);

    //initialize random data
    
    //define initial properties
    double smoothinglength = 5;
    double rho[N];
    double Mass[N];
    double Pressure[N];
//    double Position[N];
//    double Velocity[N];
    
    double x[N];
    double y[N];
    double xdot[N];
    double ydot[N];
    
//    double xTemp[N];
//    double yTemp[N];
//    double xdotTemp[N];
//    double ydotTemp[N];    
    
    double PonRhoSq[N];
    for(int i=0;i<N;i++){
        Mass[i] = 2.;
        rho[i] = 2.;
       // x[i]= i;
       // y[i] = 0.;
        xdot[i]=0.;
        ydot[i]=0.;
       // Velocity[i] = 0.;
    }
    
    x[0] = 0.;
    y[0] = 0.;
    x[1] = 1.;
    y[1] = 0.;

    rho[1]=2.;
    xdot[0]=0.1;
 //   ydot[0]=1.;
    //Mass[1]=1.;
    
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
    double *Kx = new double; 
    double *Ky = new double;  //components of Kernel Gradient
    
//    for(int a=0;a<N;a++){
//        xTemp[a] = x[a];
//    	yTemp[a] = y[a];
//        xdotTemp[a]=xdot[a];
//        ydotTemp[a]=ydot[a];
//    }
    
    FILE* outfile = fopen("output.dat","w");
    //print intial conditions
    for (int i=0;i<N;i++) {
    	fprintf(outfile,"%5d %.5e %.5e %.5e %.5e %.5e %.5e %.5e\n",0,t,x[i],y[i],xdot[i],ydot[i],rho[i],Pressure[i]);
    }
    
    Kernel *myKer;
    myKer = new SplineKernel(smoothinglength);
    
    //new SplineKernel;
    double myW = myKer->W(1,3);
    
    cout <<myW<<endl;
    
    for(int k=1; k <= Nsteps; k++) {
        t +=dt;
        for(int a=0;a<N;a++){
            //reinitialize temporary variables
            drho[a] = 0;
            dxdot[a] = 0;
            dydot[a] = 0;
            PonRhoSq[a] = Pressure[a]/pow(rho[a],2);
            for(int i=0;i<N;i++){
                
            //    cout << "a =" <<a<<endl;
            //   cout << "i =" <<i<<endl;
                
                PonRhoSq[i] = Pressure[i]/pow(rho[i],2);
                //            double distance = abs(ParticleArray[a,1]-ParticleArray[i,1]);
                //        	drho += Mass[i]*(ParticleArray[a,2]-ParticleArray[i,2])*KernelGrad(distance,smoothinglength);
                //double distance = abs(Position[a]-Position[i]); //took out abs
                
               // KernelGrad(x[a],y[a],x[i],y[i],smoothinglength, Kx, Ky);
                Vector ex1 = {1,0};
                Vector ex2 = {1.45,0};
                Vector Kgrad = myKer->gradW(ex1,ex2,smoothinglength);
                
                cout << Kgrad.x << endl;
                
                //drho += Mass[i]*(Velocity[a]-Velocity[i])*KernelGradMag(distance,smoothinglength);
//                cout << "xdot[a]-xdot[i] = " << xdot[a]-xdot[i] <<endl;
//                cout << "Kx = "<<*Kx<<endl;
//                cout << "address Kx = "<<Kx<<endl;
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
            rho[a] += drho[a]*dt; 
            Pressure[a] = B * (pow(rho[a],gamma)-1.);
        
            x[a] += xdot[a] * dt;
            y[a] += ydot[a] * dt;
            xdot[a] += dxdot[a]*dt;
            ydot[a] += dydot[a]*dt;
            
            //x[a] += xdot[a] * dt;
//            y[a] += ydot[a] * dt;
            
            // ParticleArray[a,2] = ParticleArray[a,2]+ du*dt;
        //update velocity
        
        //	for(int a=0;a<N;a++){
        //		//for each particle, calculate change in velocity for a given timestep
        //        for(int i=0;i<N;i++){ //this should be all particles close to particle i
        //        	PonRhoSq[i] = Pressure[i]/pow(rho[i],2);
        //            du += -Mass[i]*(PonRhoSq[i]-PonRhoSq[a])*KernelGrad(distance,smoothinglength);
        //        }
        //        ParticleArray[a,2] += du*dt;
        //    }
            
            //PrintState(t,Position[a],Velocity[a]);
        
        //FILE* outfile = fopen("Output.dat","w");
        fprintf(outfile,"%5d %.5e %.5e %.5e %.5e %.5e %.5e %.5e\n",k,t,x[a],y[a],xdot[a],ydot[a],rho[a],Pressure[a]);
        //fflush(outfile);
        }

       // PrintState(t,x[0],x[1]);
      //  t +=dt;
       // PrintState(t,Velocity[1]);
    }
    
    return 0;
}

//Particle.GetKin(x,y,xdot,ydot)
//Particle.SetKin(x,y,xdot,ydot)
