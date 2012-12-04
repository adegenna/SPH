#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <string>
#include <iostream>


using namespace std;

double KernelGradMag(double distance,double smoothinglength) {
    //Gaussian Kernel
    double q = distance/smoothinglength;
    double rtpi = sqrt(4.*atan(1.));
    double W = exp(-pow(q,2)/pow(smoothinglength,2))/rtpi;
    double gradW = 2*q/smoothinglength; //took out -ve
    return gradW;
}

void KernelGrad(double x1, double y1, double x2, double y2, double smoothinglength, double Kx, double Ky) {
    double rMag = sqrt(pow(x2-x1,2)+pow(y2-y1,2));
    double KMag = KernelGradMag(rMag,smoothinglength);
    cout <<"rmag = " <<rMag<<endl;
    cout <<"Kmag = " <<KMag<<endl;
    
    if(rMag =! 0.) {
         Kx = (x2-x1)/rMag*KMag;
         Ky = (y2-y1)/rMag*KMag;
    }
    else { 
         Kx = 0.;
         Ky = 0.;
    }

}

double InnerProduct2D(double x1, double y1, double x2, double y2) {
    double IP = x1*x2 + y1*y2;
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
    const int N = 4;
    //int Ndata = 4;
    
    
    const double dt = 0.01;
    const double Nsteps = 10;
    
    
   // double ParticleArray[N][Ndata];

    
    //initialize random data
    
//    for (int a=0;a<N;a++){
//        for (int j=0;j<Ndata;j++){
//    	//	ParticleArray[a,j] = 1.;//cos((a+0.5)*j);
//        }
//    }
    
    //define initial properties
    double smoothinglength = 1;
    double rho[N];
    double Mass[N];
    double Pressure[N];
    double Position[N];
    double Velocity[N];
    
    double x[N];
    double y[N];
    double xdot[N];
    double ydot[N];
    
    
    double PonRhoSq[N];
    for(int i=0;i<N;i++){
        Mass[i] = 2.;
        rho[i] = 2.;
       // x[i]= i;
       // y[i] = 0.;
        xdot[i]=0.;
        ydot[i]=0.;
        Velocity[i] = 0.;
    }
    
    x[0] = 0.;
    y[0] = 0.;
    x[1] = 1.;
    y[1] = 0.;
    x[2] = 0.;
    y[2] = 1.;
    x[3] = 1.;
    y[3] = 1.;
    
    
    //Position[1]=2.;
    rho[1]=2.;
    xdot[0]=1.;
    ydot[0]=1.;
    //Mass[1]=1.;
    
    double B = 100;
    double gamma = 7;
    
    //use typical eqn of state for liquids
    for(int i=0;i<N;i++){ 
    	Pressure[i] = B * (pow(rho[i],gamma)-1.);
    }
    
    //update every timestep
    double drho;
    //double du;
    double dxdot,dydot;
    //double uold;
    double t = 0;
    double Kx, Ky; //components of Kernel Gradient
    
    FILE* outfile = fopen("output.dat","w");
    for (int i=0;i<N;i++) {
    	fprintf(outfile,"%5d %.5e %.5e %.5e %.5e %.5e %.5e %.5e\n",0,t,x[i],y[i],xdot[i],ydot[i],rho[i],Pressure[i]);
    }
    
    for(int k=1; k <= Nsteps; k++) {
        t +=dt;
        for(int a=0;a<N;a++){
            
            PonRhoSq[a] = Pressure[a]/pow(rho[a],2);
            for(int i=0;i<N;i++){
                PonRhoSq[i] = Pressure[i]/pow(rho[i],2);
                //            double distance = abs(ParticleArray[a,1]-ParticleArray[i,1]);
                //        	drho += Mass[i]*(ParticleArray[a,2]-ParticleArray[i,2])*KernelGrad(distance,smoothinglength);
                //double distance = abs(Position[a]-Position[i]); //took out abs
                
                KernelGrad(x[a],x[i],y[a],y[i],smoothinglength,Kx,Ky);
                //drho += Mass[i]*(Velocity[a]-Velocity[i])*KernelGradMag(distance,smoothinglength);
                
                drho += Mass[i] * InnerProduct2D(xdot[a]-xdot[i],ydot[a]-ydot[i],Kx,Ky);
                //du += Mass[i] * (PonRhoSq[i]-PonRhoSq[a])*KernelGradMag(distance,smoothinglength);
                dxdot += -Mass[i] * (PonRhoSq[i]+PonRhoSq[a])*Kx;
                dydot += -Mass[i] * (PonRhoSq[i]+PonRhoSq[a])*Ky;
                
            //    cout << a <<"    "  <<Kx<< "   " << Ky <<endl;
            }
            rho[a] += drho*dt; 
            Pressure[a] = B * (pow(rho[a],gamma)-1.);
        
            xdot[a] += dxdot*dt;
            ydot[a] += dydot*dt;
            
            x[a] += xdot[a] * dt;
            y[a] += ydot[a] * dt;
            
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
