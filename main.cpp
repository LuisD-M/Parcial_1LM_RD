#include <iostream>

using namespace std;

int Public();
void imprimir(int **matriz);

int main()
{
    int opcion=1, tiempo=0, repeticiones=0;

    int **matriz = new int*[8];                       //Se reserva la matriz de 8X8 en memoria dinamica;
    for(int i=0; i<8; i++) matriz[i] = new int[8];


    while(opcion!=0){
        opcion = Public();

        if(opcion==1){
            cout<<"Ingrese el tiempo de encendido - apagado: "; cin>>tiempo;
            cout<<"Ingrese el numero de repeticiones que quiere: "; cin>>repeticiones;
            cout<<endl;

        }

        if(opcion==2){
            cout<<"Ingrese el tiempo de espera: "; cin>>tiempo;
            cout<<endl;

        }

        if(opcion==3){
            cout<<"Opcion 3"<<endl;

        }

        cout<<endl;

    }
    cout<<"El menu finalizo"<<endl;

    for (int i=0; i<8; i++) delete[] matriz[i];                         //Libera la memoria de las filas.
    delete[] matriz;                                                    //Libera la memoria del puntero.
}


int Public(){
    int opcion=10;
    char opcion1;

    cout<<"--------- Menu de opciones ----------"<<endl;
    cout<<"1. Verificar el funcionamiento de los leds."<<endl;
    cout<<"2. Imagen de prueba ingresada por el usuario."<<endl;
    cout<<"3. Mostrar los patrones de prueba 1-4."<<endl;
    cout<<"0. Para finalizar."<<endl;
    cout<<endl;

    while((opcion<0) || (opcion>3)){
        cout<<"Ingrese la opcion que desea: "; cin>>opcion1;
        opcion = (int)opcion1 - 48;
    }
    return opcion;
}

void imprimir(int **matriz){
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++) cout<<matriz[i][j]<<" ";

        cout<<endl;
    }
}
