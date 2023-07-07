// Code by Jorge Buenestado, Runge-Kuta Problem
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

const double G = 6.67e-11;
const double Mt = 5.9736e24;
const double Ml = 0.07349e24;
const double Rt = 6.37816e6;
const double Rl = 1.7374e6;
const double mc = 500000; //masa del cohete
const double TL = 3.844e8; 
const double w = 2.6617e-6;
const double π = 3.14159265;
const double Delta = G*Mt/pow(TL, 3);
const double nu = Ml/Mt;

int main(){
    int i, j, n, frames;
    double  xc, yc, xl, yl, Tt, Ts, rl, ve;
    double   pasos, timer, rpri, dtl, theta, coef;
    double k[5][5], y[5];
    bool decel = true, touchdown = false, choque = false, aterrizaje = false, proximo = true;
    ofstream moonpositions, Hamil;

    cout<<"------------------Start of Program------------------"<<endl<<endl;
    moonpositions.open("moonpositions.txt");
    Hamil.open("Hamiltoniano.txt");
    Tt = 30 ; //tiempo total en días
    Ts = 15; // timestep en segundos
    pasos = (Tt*24*60*60)/(Ts);
    frames = 100;
    timer = 0;
    //reescalado, posiciones iniciales del cohete
    ve = 11236.2;
    ve = ve/TL;
    theta = π/8;
    y[1] = Rt/TL;
    y[2] = π/8;
    y[3] = ve*cos(theta - y[2]);
    y[4] = y[1]*ve*sin(theta - y[2]);
    dtl = 1;
    coef = 0.38591; //coeficiente de deceleración

    for(j = 1; j<5; j++){k[0][j] = 0;}

    for(i = 0; i < pasos; i++){ 

        rl = sqrt(y[1]*y[1] + dtl*dtl - 2*y[1]*dtl*cos(y[2] - w*timer)); // potencial V y Rl
        xl = dtl*cos(w*timer);
        yl = dtl*sin(w*timer);
        if(touchdown == false){
            for(j = 1 ; j<5; j++){
                k[j][1] =  Ts*y[3] + k[j-1][3]/2;
                k[j][2] = Ts*((y[4] + k[j-1][4]/2)/(pow(y[1] + k[j-1][1]/2,2)));
                rpri = sqrt(1 + pow(y[1] + k[j-1][1]/2, 2) - 2*(y[1] + k[j-1][1]/2)*cos(y[2] + k[j-1][2]/2 - w*(timer+Ts/2)));
                k[j][3] = Ts*(pow(y[4] + k[j-1][4]/2,2)/pow((y[1] + k[j-1][1]/2),3) - Delta*(1/(pow((y[1] + k[j-1][1]/2), 2)) + nu*((y[1] + k[j-1][1]/2) - cos(y[2] + k[j-1][2]/2 - w*(timer + Ts/2)))/(pow(rpri, 3))));
                k[j][4] = Ts*((-Delta*nu*(y[1] + k[j-1][1]/2) *sin(y[2] + k[j-1][2]/2 - w*(timer + Ts/2)))/(pow(rpri,3))); 
            }
            for(j = 1; j<5; j++){
                y[j] = y[j] + (k[1][j] + 2*k[2][j]+ 2*k[3][j]+ k[4][j])/6;
            }
            

            xc = y[1]*cos(y[2]);
            yc = y[1]*sin(y[2]);
        }
        if((rl <= 0.006)&&(decel == true)){ //deceleración para entrar en órbita
            y[3] = y[3]*coef;
            y[4]= y[4]*coef;
            decel = false;
        }
        if((0.95*Rl/TL >= rl)&&(touchdown == false)){ //choque con la luna
            touchdown = true;
            choque = true;
             cout<< "Ha impactado contra la luna tras "<< timer/(3600*24) << " días."<<endl;
        }
        if(choque == true){
            xc = xl;
            yc = yl;
        }
        if((0.95*Rt/TL >= y[1])&&(touchdown == false)){ //choque con la tierra
            touchdown = true;
            aterrizaje = true;
            cout<< "Ha impactado contra la Tierra tras "<< timer/(3600*24) << " días."<<endl;
        }
        if(aterrizaje == true){
            xc = 0;
            yc = 0;
        }
        if((i%frames == 0)&&(i>=10)){
            moonpositions<< 0 << "   " << 0 << endl;
            moonpositions<< xl << "   " << yl << endl;
            moonpositions<< xc << "   " << yc << endl<<endl;
            Hamil << pow(mc*TL*y[3],2)/(2*mc) + pow(mc*pow(TL,2)*y[4],2)/(2*mc*pow(TL*y[1],2)) - G*mc*Mt/(TL*y[1]) - G*mc*Ml/Rl-w*(mc*pow(TL,2)*y[4])<<endl;
        } 
        if((y[0] >= 1.2)&&(proximo == true)){
            cout << "El objeto ha salido del campo gravitatorio terrestre/lunar" << endl;
            proximo = false;
        }
        timer += Ts;
    }
    if(touchdown == false){
        cout <<"El objeto sigue orbitando tras " <<Tt << " días."<<endl; 
    }
    moonpositions.close();
    Hamil.close();
    cout<<"-------------------End of Program-------------------"<<endl<<endl;
    return 0;
}