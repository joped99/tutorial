#include <iostream>
#include <fstream>
#include <math.h>

#define MAX 65536 // maximum loop length

using namespace std;

class pend{
    public:
    //creating variables
        double theta[MAX];
        double omega[MAX];
        double t[MAX];
        double dt;
        double g;
        double l;
        double q;
        double Fd;
        double btheta;
        double bomega;
        double omegad;

        string fileName;

        void init(){ // getting all data from user
            cout << "Initial angle (rad): ";
            cin >> btheta;
            cout << endl << "Initial angular velocity (rad/s): ";
            cin >> bomega;
            cout << endl << "Pendulum length (m): ";
            cin >> l;
            cout << endl << "Damping coefficient (rad/s^2): ";
            cin >> q;
            cout << endl << "Driving force (strange unit): ";
            cin >> Fd;
            cout << endl << "Driving frequency (rad/s): ";
            cin >> omegad;
            cout << endl << "Time step (s): ";
            cin >> dt;
            cout << endl << "Filename to save under: ";
            cin >> fileName;
            t[0]=0.0;
            theta[0]=btheta;
            omega[0]=bomega;
            g=9.811;
        }

        // initialization without user input (besides filename)
        void hardInit(){
            theta[0]=0.2;
            omega[0]=0.0;
            l=9.8;
            q=0.5;
            Fd=1.2;
            omegad=2.0/3.0;
            dt=0.1;
            cout << endl << "Filename to save under: ";
            cin >> fileName;
            t[0]=0.0;
            g=9.811;
        }

        // angular acceleration function
        double alpha(double angle, double vel, double tim){
            return -1*sin(angle)*g/l - q*vel + Fd*sin(omegad*tim);
        }

        // running angular motion in Runge-Kutta 4
        void run(){
            double pi2=2.* M_PI;
            for(int i=1; i<MAX; i++){
                double k1w=dt*alpha(theta[i-1],omega[i-1],t[i-1]);
                double k1t=dt*omega[i-1];
                double k2w=dt*alpha(theta[i-1]+0.5*k1t,omega[i-1]+0.5*k1w,t[i-1]+0.5*dt);
                double k2t=dt*(omega[i-1]+0.5*k2w);
                double k3w=dt*alpha(theta[i-1]+0.5*k2t,omega[i-1]+0.5*k2w,t[i-1]+0.5*dt);
                double k3t=dt*(omega[i-1]+0.5*k3w);
                double k4w=dt*alpha(theta[i-1]+k3t,omega[i-1]+k3w,t[i-1]+dt);
                double k4t=dt*(omega[i-1]+k4w);
                // adding to array
                omega[i]=omega[i-1]+(k1w+2.0*k2w+2.0*k3w+k4w)/6.0;
                theta[i]=theta[i-1]+(k1t+2.0*k2t+2.0*k3t+k4t)/6.0;
                // if angle is beyond pi in either direction, loop around
                if(theta[i]>M_PI){
                    theta[i]-=pi2;
                }
                if(theta[i]<-M_PI){
                    theta[i]+=pi2;
                }
                // advancing time
                t[i]=t[i-1]+dt;
            }
        }

        // write angle and time to file
        void angleSave(){
            string angleFile = fileName + "Theta.txt";
            ofstream fout(angleFile); // opening file
            if (fout.fail()){ // checking if file can be opened and warning user
                cout << "FAILED TO WRITE TO FILE" << endl;
                return;
            }
            for(int i=0; i<MAX; i++){ // looping through data to write to file
                fout << t[i] << " " << theta[i] << endl;
            }
            fout.close(); // closing file and notifying user
            cout << "Data successfully written to " << angleFile << endl;
            return;
        }

        // write velocity and time to file
        void omegaSave(){
            string speedFile = fileName + "Omega.txt";
            ofstream fout(speedFile); // opening file
            if (fout.fail()){ // checking if file can be opened and warning user
                cout << "FAILED TO WRITE TO FILE" << endl;
                return;
            }
            for(int i=0; i<MAX; i++){ // looping through data to write to file
                fout << t[i] << " " << omega[i] << endl;
            }
            fout.close(); // closing file and notifying user
            cout << "Data successfully written to " << speedFile << endl;
            return;
        }

        // saving a Poincare section to a file, with a given phase shift
        void poincareSave(double phaseShift, string name){
            string poincare = fileName + name + "Pcr.txt";
            ofstream fout(poincare); // opening file
            if (fout.fail()){ // checking if file can be opened and warning user
                cout << "FAILED TO WRITE TO FILE" << endl;
                return;
            }
            // saving data only at frequency of driving force
            double phase = 2.0*3.1415926/omegad;
            for(int i=0; i<MAX; i++){ // looping through data to write to file
                bool check = ((fmod(t[i]-phaseShift,phase)) <= dt);
                if(check){
                    fout << theta[i] << " " << omega[i] << endl;
                }
            }
            fout.close(); // closing file and notifying user
            cout << "Data successfully written to " << poincare << endl;
            return;
        }
};

int main(){
    // Hello world
    cout << "Hello World" << endl;

    // variables, loops, if/else, functions, classes, file i/o
    pend swing;

    // swing.init();
    swing.hardInit();
    swing.run();
    
    // saving Poincare data for different phases
    swing.poincareSave(0,"0");
    swing.poincareSave(M_PI/2.0,"pi2");
    swing.poincareSave(M_PI/4.0,"pi4");
    return 0;
}