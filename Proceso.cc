/** @file Proceso.cc
 @brief Codigo de la clase proceso
*/
#include "Proceso.hh"

//Constructoras

Proceso::Proceso(){
    idp = 0;
    cantidadMemoria = 0;
    tiempoEjecutado = 0;
    posicionMemoria = 0;

}

//Consultoras

int Proceso::get_tiempoEjecutado(){

    return tiempoEjecutado;

}

int Proceso::get_cantidadMemoria(){

    return cantidadMemoria;

}

int Proceso::get_idp() {

    return idp;

}

int Proceso::get_dirMemoria() {

    return posicionMemoria;
}

//Modificadoras

void Proceso::set_dirMem(const int& x) {

    posicionMemoria = x;

}


bool Proceso::avanzar_tiempo_proceso(const int& t) {

    tiempoEjecutado -= t;
    if (tiempoEjecutado <= 0) return true;
    return false;

}

//Entrada/Salida

void Proceso::leer_proceso(){

    cin >> idp;
    cin >> cantidadMemoria;
    cin >> tiempoEjecutado;

}

void Proceso::imprimir_proceso(){

    cout << idp << ' ' << cantidadMemoria << ' ' << tiempoEjecutado << endl;

}
