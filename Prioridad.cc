/** @file Prioridad.cc
 @brief Codigo de la clase prioridad
*/

#include "Prioridad.hh"

//Constructoras

Prioridad::Prioridad(){

    colocados = 0;
    rechazados = 0;
    prioProcesos.clear();
    listaProcesos.clear();

}

//Consultoras

bool Prioridad::existe_proceso(const int& etiq){

    map<int,Proceso>::iterator it = prioProcesos.find(etiq);
    if (it != prioProcesos.end()) return true;
    return false;

}

list<Proceso> Prioridad::get_lista() {

    return listaProcesos;
}

void Prioridad::borrar_proceso(int& idp){

    prioProcesos.erase(idp);


}

bool Prioridad::esta_vacia(){

    if (prioProcesos.empty()) return true;
    return false;

}

//Modificadoras

void Prioridad::anadir_proceso(Proceso &p){

    prioProcesos.insert(make_pair(p.get_idp(), p));
    listaProcesos.insert(listaProcesos.end(),p);
}

void Prioridad::colocados_rechazados(int& a, int& b) {
    
    colocados += a;
    rechazados += b;

}

list<Proceso> Prioridad::set_lista(list<Proceso>& l) {

    listaProcesos = l;
    return listaProcesos;
}

//Entrada/Salida

void Prioridad::imprimir_prioridad(){

    for (list<Proceso>::iterator it = listaProcesos.begin(); it != listaProcesos.end(); ++it) {
    
        (*it).imprimir_proceso();

    }
    cout << colocados << ' ' << rechazados << endl;

}


