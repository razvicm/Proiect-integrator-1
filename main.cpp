#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <stdio.h>
#include <windows.h>
#include <ctime>

using namespace std;
void L(int,int[], int);
void R(int,int[], int);
void G(int,int[], int);

int main()
{
    char codDat[10], denumire[21],raspuns, rasp;
    char codRO[] = "594";
    int codGenerat, nrProduse;
    int S,s1,s2,i;
    fstream cod;
    cod.open( "cod.html", ios::out);
    cod << "<!DOCTYPE html>" << endl;
    cod << "<html>" << endl;
    cod << "<head><style>table, th, td {border: 4px solid black;\
    border-collapse: collapse;}th, td {padding: 5px;}</style></head>"<<endl;
    cod << "<title> Cod de bare </title>" << endl;
    cod << "<body bgcolor=\"LightBlue\">" << endl;
    cod << "<div style=\"text-align:center;\">"<<endl;
    cod << "<table align=\"center\" style=\"width:75%\">"<<endl;

    srand(time(0));
    codGenerat = rand() % 899999999 + 100000000;
    cout << "Introduceti denumirea produsului (max. 20 caractere): ";

    cin.getline(denumire,21);
    //cin.ignore(50,'\n');

    cout<<"Introduceti \"1\" pentru introducerea codului sau alta tasta pentru generarea unui cod aleatoriu: ";
    cin>>raspuns;
    cin.clear();
    cin.ignore(50,'\n');

    if(raspuns=='1'){
    cout << "Introduceti codul produsului (max. 9 cifre, fara spatii): ";
    cin>>codDat;
    cin.clear();
    cin.ignore(50,'\n');


    }
    else{
        cout<<"Se va genera un cod aleatoriu in 5 secunde"<<endl;
        Sleep(1000);
        for(i=4;i>0;i--){
            cout << i <<endl;
            Sleep(1000);
        }
        sprintf(codDat,"%d",codGenerat); //convertire cod generat din int in char
        cout<<"A fost generat codul "<<codDat<<endl;
        }


    char sirSapte[9] = ""; // sirul initial este vid
   int lungime = strlen(codDat);
// Verificare. Numar toate caracterele bune folosind un contor.
    i = 0;
    while(codDat[i] >= '0' && codDat[i] <= '9')
    i++;
    if(i != lungime)
    {
    cout << "Cod eronat: " << codDat << endl;
    return 0;
    }
    if(lungime < 9)
    {
    int j;
    for(j=0; j<9-lungime; j++)
    sirSapte[j] = '7';
    // Limitez sirSapte la dreapta adaugandu-i un caracter '\0'
    sirSapte[j] = '\0';
    }

    char ean13[13]; // 13 caractere, 12+1
    strcpy(ean13, codRO);
    strcat(ean13, sirSapte);
    strcat(ean13, codDat);
    ean13[12]='\0';
    // Verific pana aici
    cout << "Primele 12 caractere sunt : " << ean13 << endl;

    int nean13[13]; // Pentru rezultate
    for(i=0; i<12; i++)
    nean13[i] = ean13[i] - '0';

    s1 = s2 = 0;
    for(i=0; i<12; i=i+2)
    {
    s1 =s1 + nean13[i];
    s2 =s2 + nean13[i+1];
    }
    S = s1 + 3*s2;
    nean13[12] = 10 - S%10; // Cifra de control

    int b[95];
    // Se codifica inceputul: 101
    b[0]=b[2]=1;
    b[1]=0;
    // Se codifica prima parte a codului (6 caractere, nean13[1] la nean13[6];):
    L(nean13[1], b, 3); // Primul, nean13[1]. Se apeleaza functia L
    G(nean13[2], b, 10); // Car. 2, se apeleaza functia G
    G(nean13[3], b, 17); // Car. 3, se apeleaza functia G
    L(nean13[4], b, 24); // Car. 4, se apeleaza functia L
    L(nean13[5], b, 31); // Car. 5, se apeleaza functia L
    G(nean13[6], b, 38); // Car. 6, se apeleaza functia G
    // Se codifica zona de separare din mijloc, 01010:
    b[45]=b[47]=b[49]=0;
    b[46]=b[48]=1;
    // Se codifica partea a doua a codului (nean13[7] la nean13[12]).
    // Pentru toate se apelează funcţia R():
    for(i=0; i<6; i++)
    R(nean13[7+i], b, 50+i*7);

    // Se codifica partea finala a codului, 101:
    b[92] = b[94] = 1;
    b[93] = 0;

    cod << "<br> <br><div style=\"text-align:center;\">\
    <img src=\"http://images.wisegeek.com/fishing-net-with-fish-near-water.jpg\" \
    style=\"width:600px;height:500px;\"> <h2 align=\"center\"> Profesore, profesore... </h2>"<<endl;
    cod << "</body>" << endl;
    cod << "</html>" << endl;
    cod.close();
    Sleep(1000);
    cout<<"Se va genera fisierul cod.html in 5 secunde"<<endl;
    Sleep(1000);
    cout<<"4 secunde"<<endl;
    Sleep(1000);
    for(double j=3;j>0;j-=0.1){
        if(j==0.99999999999999833){
        cout<<"1 secunda"<<endl;
        continue;}
        cout<<j<<" secunde"<<endl;
        Sleep(100);
        }
    cout<<endl<<"A fost generat fisierul cod.html in directorul proiectului integrator"<<endl;
    return 0;
}

void L(int valoare, int bin[], int poz)
    {
    switch(valoare)
    {
    case 0: // 0001101
    bin[poz]=bin[poz+1]=bin[poz+2]=bin[poz+5]=0;
    bin[poz+3]=bin[poz+4]=bin[poz+6]=1;
    break;
    case 1: // 0011001
    bin[poz]=bin[poz+1]=bin[poz+4]=bin[poz+5]=0;
    bin[poz+2]=bin[poz+3]=bin[poz+6]=1;
    break;
    case 2: // 0010011
    bin[poz]=bin[poz+1]=bin[poz+3]=bin[poz+4]=0;
    bin[poz+2]=bin[poz+5]=bin[poz+6]=1;
    break;
    case 3: // 0111101
    bin[poz]=bin[poz+5]=0;
    bin[poz+1]=bin[poz+2]=bin[poz+3]=bin[poz+4]=bin[poz+6]=1;
    break;
    case 4: // 0100011
    bin[poz]=bin[poz+2]=bin[poz+3]=bin[poz+4]=0;
    bin[poz+1]=bin[poz+5]=bin[poz+6]=1;
    break;
    case 5: // 0110001
    bin[poz]=bin[poz+3]=bin[poz+4]=bin[poz+5]=0;
    bin[poz+1]=bin[poz+2]=bin[poz+6]=1;
    break;
    case 6: // 0101111
    bin[poz]=bin[poz+2]=0;
    bin[poz+1]=bin[poz+3]=bin[poz+4]=bin[poz+5]=bin[poz+6]=1;
    break;
    case 7: // 0111011
    bin[poz]=bin[poz+2]=0;
    bin[poz+1]=bin[poz+4]=bin[poz+3]=bin[poz+5]=bin[poz+6]=1;
    break;
    case 8: // 0110111
    bin[poz]=bin[poz+3]=0;
    bin[poz+1]=bin[poz+2]=bin[poz+4]=bin[poz+5]=bin[poz+6]=1;
    break;
    case 9: // 0001011
    bin[poz]=bin[poz+1]=bin[poz+2]=bin[poz+4]=0;
    bin[poz+3]=bin[poz+5]=bin[poz+6]=1;
    break;
    }
}
void G(int valoare, int bin[], int poz)
    {
    switch(valoare)
    {
    case 0: // 0001101
    bin[poz]=bin[poz+4]=bin[poz+3]=0;
    bin[poz+1]=bin[poz+2]=bin[poz+5]=bin[poz+6]=1;
    break;
    case 1: // 0011001
    bin[poz]=bin[poz+3]=bin[poz+4]=0;
    bin[poz+1]=bin[poz+2]=bin[poz+5]=bin[poz+6]=1;
    break;
    case 2: // 0010011
    bin[poz]=bin[poz+1]=bin[poz+4]=0;
    bin[poz+2]=bin[poz+3]=bin[poz+5]=bin[poz+6]=1;
    break;
    case 3: // 0111101
    bin[poz]=bin[poz+6]=bin[poz+3]=bin[poz+4]=bin[poz+5]=0;
    bin[poz+1]=bin[poz+2]=1;
    break;
    case 4: // 0100011
    bin[poz]=bin[poz+1]=bin[poz+5]=0;
    bin[poz+2]=bin[poz+3]=bin[poz+4]=bin[poz+6]=1;
    break;
    case 5: // 0110001
    bin[poz]=bin[poz+4]=bin[poz+5]=0;
    bin[poz+1]=bin[poz+2]=bin[poz+3]=bin[poz+6]=1;
    break;
    case 6: // 0101111
    bin[poz]=bin[poz+1]=bin[poz+2]=bin[poz+3]=bin[poz+5]=0;
    bin[poz+4]=bin[poz+6]=1;
    break;
    case 7: // 0111011
    bin[poz]=bin[poz+1]=bin[poz+3]=bin[poz+4]=bin[poz+5]=0;
    bin[poz+2]=bin[poz+6]=1;
    break;
    case 8: // 0110111
    bin[poz]=bin[poz+1]=bin[poz+2]=bin[poz+4]=bin[poz+5]=0;
    bin[poz+3]=bin[poz+6]=1;
    break;
    case 9: // 0001011
    bin[poz]=bin[poz+1]=bin[poz+3]=0;
    bin[poz+2]=bin[poz+4]=bin[poz+5]=bin[poz+6]=1;
    break;
    }
}

void R(int valoare, int bin[], int poz)
    {
    switch(valoare)
    {
    case 0: // 0001101
    bin[poz+3]=bin[poz+4]=bin[poz+6]=0;
    bin[poz]=bin[poz+1]=bin[poz+2]=bin[poz+5]=1;
    break;
    case 1: // 0011001
    bin[poz+2]=bin[poz+1]=bin[poz+6]=0;
    bin[poz]=bin[poz+3]=bin[poz+4]=bin[poz+5]=1;
    break;
    case 2: // 0010011
    bin[poz+2]=bin[poz+5]=bin[poz+6]=0;
    bin[poz]=bin[poz+1]=bin[poz+3]=bin[poz+4]=1;
    break;
    case 3: // 0111101
    bin[poz+1]=bin[poz+2]=bin[poz+3]=bin[poz+4]=bin[poz+6]=0;
    bin[poz]=bin[poz+5]=1;
    break;
    case 4: // 0100011
    bin[poz+1]=bin[poz+5]=bin[poz+6]=0;
    bin[poz]=bin[poz+2]=bin[poz+3]=bin[poz+4]=1;
    break;
    case 5: // 0110001
    bin[poz+1]=bin[poz+2]=bin[poz+6]=0;
    bin[poz]=bin[poz+3]=bin[poz+4]=bin[poz+5]=1;
    break;
    case 6: // 0101111
    bin[poz+1]=bin[poz+3]=bin[poz+4]=bin[poz+5]=bin[poz+6]=0;
    bin[poz]=bin[poz+2]=1;
    break;
    case 7: // 0111011
    bin[poz+1]=bin[poz+2]=bin[poz+3]=bin[poz+5]=bin[poz+6]=0;
    bin[poz]=bin[poz+4]=1;
    break;
    case 8: // 0110111
    bin[poz+1]=bin[poz+2]=bin[poz+4]=bin[poz+5]=bin[poz+6]=0;
    bin[poz]=bin[poz+3]=1;
    break;
    case 9: // 0001011
    bin[poz+3]=bin[poz+5]=bin[poz+6]=0;
    bin[poz]=bin[poz+1]=bin[poz+2]=bin[poz+4]=1;
    break;
    }
}
