#include <iostream>
using namespace std;
#include "Prioridad.hh"

int main(){

    Prioridad prio;
    Proceso p;
    p.leer_proceso();
    prio.anadir_proceso(p);

    cout << prio.existe_proceso(12) << endl;

}
