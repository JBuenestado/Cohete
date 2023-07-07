// Code by Jorge Buenestado, Runge-Kuta Problem
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

const double G = 6.67e-11;
const double Mt = 5.9736e24;
const double Rt = 6.37816e6;
const double Ml = 0.07349e24;
const double Rl = 1.7374e6;
const double mc = 200000; //masa del cohete
const double TL = 3.844e8; 
const double w = 2.6617e-6;
const double π = 3.14159265;
const double Delta = G*Mt/pow(TL, 3);
 const double nu = Ml/Mt;


int main(){
    int i, j, n, frames;
    double  xc, yc, xl, yl, Tt, Ts;
    double   pasos, timer, rl, ve, rpri, dtl, theta, coef;
    double k[5][5];
    bool decel = true, touchdown = true, choque = false;
    ofstream moonpositions;

    cout<<"------------------Start of Program------------------"<<endl<<endl;
    moonpositions.open("moonpositions.txt");
    Tt = 100 ; //tiempo total en días
    Ts = 10; // timestep en segundos
    pasos = (Tt*24*60*60)/(Ts);
    frames = 500;
    timer = 0;

    //reescalado, posiciones iniciales del cohete
    ve = 11236.6;
    ve = ve/TL;
    theta = π/8;
    k[0][1] = Rt/TL;
    k[0][2] = π/8;
    k[0][3] = ve*cos(theta - k[0][2]);
    k[0][4] = k[0][1]*ve*sin(theta - k[0][2]);
    dtl = 1;
    coef = 0.38591; //coeficiente de deceleración

    for(i = 0; i < pasos; i++){ 
        rl = sqrt(k[0][1]*k[0][1] + dtl*dtl - 2*k[0][1]*dtl*cos(k[0][2] - w*timer)); // potencial V y Rl
 
        k[1][1] = Ts*k[0][3];
        k[1][2] = Ts*k[0][4]/(pow(k[0][1],2));
        rpri = sqrt(1 + pow(k[0][1], 2) - 2*k[0][1]*cos(k[0][2] - w*timer));
        k[1][3] = Ts*(pow(k[0][4],2)/pow(k[0][1],3) - Delta*( 1/pow(k[0][1], 2) + nu*(k[0][1]-cos(k[0][2] - w*timer))/(pow(rpri, 3))));
        k[1][4] = Ts*((-Delta*nu*k[0][1]*sin(k[0][2] - w*timer))/(pow(rpri,3))); 

        for(j = 2; j<5; j++){
            k[j][1] =  Ts*k[0][3] + k[j-1][3]/2;
            k[j][2] = Ts*((k[0][4] + k[j-1][4]/2)/(pow(k[0][1] + k[j-1][1]/2,2)));
            rpri = sqrt(1 + pow(k[0][1] + k[j-1][1]/2, 2) - 2*(k[0][1] + k[j-1][1]/2)*cos(k[0][2] + k[j-1][2]/2 - w*(timer+Ts/2)));
            k[j][3] = Ts*(pow(k[0][4] + k[j-1][4]/2,2)/pow((k[0][1] + k[j-1][1]/2),3) - Delta*(1/(pow((k[0][1] + k[j-1][1]/2), 2)) + nu*((k[0][1] + k[j-1][1]/2) - cos(k[0][2] + k[j-1][2]/2 - w*(timer + Ts/2)))/(pow(rpri, 3))));
            k[j][4] = Ts*((-Delta*nu*(k[0][1] + k[j-1][1]/2) *sin(k[0][2] + k[j-1][2]/2 - w*(timer + Ts/2)))/(pow(rpri,3))); 
        }

        for(j = 1; j<5; j++){
            k[0][j] = k[0][j] + (k[1][j] + 2*k[2][j]+ 2*k[3][j]+ k[4][j])/6;
        }
        
        xl = dtl*cos(w*timer);
        yl = dtl*sin(w*timer);
        xc = k[0][1]*cos(k[0][2]);
        yc = k[0][1]*sin(k[0][2]);

        if((rl <= 0.006)&&(decel == true)){
            k[0][3] = k[0][3]*coef;
            k[0][4]= k[0][4]*coef;
            decel = false;
        }
        if((0.9*Rl/TL >= rl)&&(touchdown == true)){
            k[0][3] =0;
            k[0][4]= 0;
            touchdown = false;
            choque = true;
        }
        if(choque == true){
            xc = xl;
            yc = yl;
        }
    
        if((i%frames == 0)&&(i>=10)){
            moonpositions<< 0 << "   " << 0 << endl;
            moonpositions<< xl << "   " << yl << endl;
            moonpositions<< xc << "   " << yc << endl<<endl;
        } 
        timer += Ts;
    }
    moonpositions.close();
    cout<<"-------------------End of Program-------------------"<<endl<<endl;
    return 0;
}