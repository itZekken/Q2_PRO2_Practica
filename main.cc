#include "Area_de_espera.hh"
#ifndef NO_DIAGRAM
#include <iostream>
using namespace std;
#endif


int main(){

    Cluster c;
    c.leer_procesadores(c);
    Area_de_espera ade;
    ade.leer_Area();
    string comando;
    cin >> comando;
    while(comando != "fin"){

        //////////////////////////////OPERATION//////////////////////////////
        if(comando == "configurar_cluster" or comando == "cc"){
            c.leer_procesadores(c);
        }

        //////////////////////////////OPERATION//////////////////////////////
        else if(comando == "modificar_cluster" or comando == "mc"){
            string p;

            if(c.existe_procesador(p)){
                CPU cpu; //Buscar en el bintree el procesador
                if(not cpu.En_ejecucion()){
                }
                else cout << "Error: el procesador no se ha encontrado, tiene procesos en ejecución o tiene procesadores auxiliares." << endl;
            }
            else cout << "Error: el procesador no se ha encontrado, tiene procesos en ejecución o tiene procesadores auxiliares." << endl;
        }

        //////////////////////////////OPERATION//////////////////////////////
        else if (comando == "alta_prioridad" or comando == "ap"){
            string prio;
            cin >> prio;
            if(ade.existe_prioridad(prio)){
                cout << "Error: ya existe en el área de espera una prioridad con el mismo identificador." << endl;
            }
            else ade.anadir_prioridad(prio); //Quizás hacer una función que busque la prioridad prio?
        }

        //////////////////////////////OPERATION//////////////////////////////
        else if (comando == "baja_prioridad" or comando == "bp"){
            string prio;
            cin >> prio;
            if (not ade.existe_prioridad(prio)) cout << "Error: no existe la prioridad en el área de espera." << endl;
            else if (ade.procesos_pendientes()) cout << "Error: el área de espera tiene procesos pendientes." << endl;
            else ade.borrar_prioridad(prio); //Quizás hacer una función que busque la prioridad prio?
        }

        //////////////////////////////OPERATION//////////////////////////////
        else if (comando == "alta_proceso_espera" or comando == "ape"){
            
            Proceso process;
            process.leer_proceso();
            int idp = process.get_idp();
            string prio;
            if(not ade.existe_prioridad(prio)) cout << "Error: no existe la prioridad." << endl;
            else if (ade.existe_proceso(idp, prio)) cout << "Error: ya existe un proceso con ese identificador y prioridad." << endl;
            else ade.anadir_proceso(process, prio); //Quizás hacer una función que busque la prioridad prio?
        }

        //////////////////////////////OPERATION//////////////////////////////
        else if (comando == "alta_proceso_procesador" or comando == "app"){
            string p;
            Proceso process;
            process.leer_proceso();
            string prio;
            int res = c.alta_proceso_procesador(process, p,c); //Esto lo que hará es, buscar en el cluster el procesador con el identificador p y luego buscar si está el proceso
            if (res == 1) cout << "Error: No hay espacio para colocar el proceso en el procesador." << endl;
            else if (res == 2) cout << "Error: Ya hay un proceso con el mismo identificador en el procesador." << endl;
            else if (res == 3) cout << "Error: No existe el procesador en el cluster. " << endl;
            else c.enviar_proceso_procesador(process,p);
        }

        //////////////////////////////OPERATION//////////////////////////////
        else if (comando == "baja_proceso_procesador" or comando == "bpp"){
            string p;
            int idp;
            cin >> p >> idp;
            int res = c.baja_proceso_procesador(idp, p,c); //Esto lo que hará es, buscar en el cluster si existe el procesador en el cluster, y si tiene un proceso con el identificador idp.
            if (res == 1) cout << "Error: No existe el proceso en el procesador." << endl;
            else if (res == 2) cout << "Error: No existe el procesador en el cluster." << endl;
            else c.borrar_proceso(p, idp, c);
        }

        //////////////////////////////OPERATION//////////////////////////////
        else if (comando == "enviar_procesos_cluster" or comando == "epc"){
            int n;
            cin >> n; 
            ade.enviar_procesos(n, c);
        }

        //////////////////////////////OPERATION//////////////////////////////
        else if (comando == "avanzar_tiempo" or comando == "at"){
            int t;
            cin >> t;
            c.avanzar_tiempo(t);    
        }

        //////////////////////////////OPERATION//////////////////////////////
        else if (comando == "imprimir_prioridad" or comando == "ipri"){
            string prio;
            cin >> prio;
            if (not ade.existe_prioridad(prio)) cout << "Error: no existe una prioridad en el área de espera con la etiqueta seleccionada" << endl;
            else{
                ade.imprimir_prioridad(prio);
            }
        }

        //////////////////////////////OPERATION//////////////////////////////
        else if (comando == "imprimir_area_espera" or comando == "iae"){
            ade.imprimir();
        }

        //////////////////////////////OPERATION//////////////////////////////
        else if (comando == "imprimir_procesador" or comando == "ipro"){
            string p;
            if (not c.existe_procesador(p)) cout << "Error: no existe un procesador con ese identificador en el cluster" << endl;
            else{
                c.imprimir_procesador(p);
            }
        }

        //////////////////////////////OPERATION//////////////////////////////
        else if (comando == "imprimir_procesadores_cluster" or comando == "ipc"){
            c.imprimir_procesadores();
        }

        //////////////////////////////OPERATION//////////////////////////////
        else if (comando == "imprimir_estructura_cluster" or comando == "iec"){
            cout << "#" << comando << endl;
            c.imprimir_estructura();
        }

        //////////////////////////////OPERATION//////////////////////////////
        else if (comando == "compactar_memoria_procesador" or comando == "cmp"){
            string p;
            if (not c.existe_procesador(p)) cout << "Error: no existe un procesador con ese identificador en el cluster" << endl;
            else c.compactar_memoria_procesador(p);
        }

        //////////////////////////////OPERATION//////////////////////////////
        else if (comando == "compactar_memoria_cluster" or comando == "cmc"){
            
             c.compactar_memoria_cluster();
            //Con la función de antes, compactar la memoria de cada uno de los procesadores paso a paso.
        }
        cin >> comando;
    }
}
