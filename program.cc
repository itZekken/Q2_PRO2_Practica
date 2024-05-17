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
            cout << '#' << comando << endl;
            Cluster b;
            c = b;
            c.leer_procesadores(c);
        }

        //////////////////////////////OPERATION//////////////////////////////
        else if(comando == "modificar_cluster" or comando == "mc"){
            string p;
            Cluster c1;
            cin >> p;
            c1.leer_procesadores(c1);
            cout << '#' << comando << ' ' << p << endl;
            if(c.existe_procesador(p)){
                CPU cpu = c.buscar_procesador(p);
                if(not cpu.En_ejecucion()){
                    if (not c.tiene_auxiliares(cpu)) {
                        c.colocar_cluster_arbol(p, c1);
                    } 
                    else cout << "error: procesador con auxiliares" << endl;
                }
                else cout << "error: procesador con procesos" << endl;
                
            }
            else cout << "error: no existe procesador" << endl;
        }

        //////////////////////////////OPERATION//////////////////////////////
        else if (comando == "alta_prioridad" or comando == "ap"){
            string prio;
            cin >> prio;
            cout << '#' << comando << ' ' << prio << endl;
            if(ade.existe_prioridad(prio)){
                cout << "error: ya existe prioridad" << endl;
            }
            else ade.anadir_prioridad(prio);
        }

        //////////////////////////////OPERATION//////////////////////////////
        else if (comando == "baja_prioridad" or comando == "bp"){
            string prio;
            cin >> prio;
            cout << '#' << comando << ' ' << prio << endl;
            if (not ade.existe_prioridad(prio)) cout << "error: no existe prioridad" << endl;
            else if (ade.procesos_pendientes(prio)) cout << "error: prioridad con procesos" << endl;
            else ade.borrar_prioridad(prio);
        }

        //////////////////////////////OPERATION//////////////////////////////
        else if (comando == "alta_proceso_espera" or comando == "ape"){
            
            string prio;
            cin >> prio;
            Proceso process;
            process.leer_proceso();
            int idp = process.get_idp();
            cout << '#' << comando << ' ' << prio << ' ' << idp << endl;
            if(not ade.existe_prioridad(prio)) cout << "error: no existe prioridad" << endl;
            else if (ade.existe_proceso(idp, prio)) cout << "error: ya existe proceso" << endl;
            else ade.anadir_proceso(process, prio);
        }

        //////////////////////////////OPERATION//////////////////////////////
        else if (comando == "alta_proceso_procesador" or comando == "app"){
            string p;
            cin >> p;
            Proceso process;
            process.leer_proceso();
            string prio;
            cout << '#' << comando << ' ' << p << ' ' << process.get_idp() << endl;
            int res = c.alta_proceso_procesador(process, p,c); //Esto lo que hará es, buscar en el cluster el procesador con el identificador p y luego buscar si está el proceso
            if (res == 1) {
                c.enviar_proceso_procesador(process, p);
            } 
            else if (res == 2) cout << "error: ya existe proceso" << endl;
            else if (res == 3) cout << "error: no existe procesador" << endl;

        }

        //////////////////////////////OPERATION//////////////////////////////
        else if (comando == "baja_proceso_procesador" or comando == "bpp"){
            string p;
            int idp;
            cin >> p >> idp;
            cout << '#' << comando << ' ' << p << ' ' << idp << endl;
            int res = c.baja_proceso_procesador(idp, p,c); //Esto lo que hará es, buscar en el cluster si existe el procesador en el cluster, y si tiene un proceso con el identificador idp.
            if (res == 1) cout << "error: no existe proceso" << endl;
            else if (res == 2) cout << "error: no existe procesador" << endl;
            else if (res == 3) c.borrar_proceso(p, idp);

        }

        //////////////////////////////OPERATION//////////////////////////////
        else if (comando == "enviar_procesos_cluster" or comando == "epc"){
            int n;
            cin >> n;
            cout << '#' << comando << ' ' << n << endl;
            ade.enviar_procesos(n, c);
        }

        //////////////////////////////OPERATION//////////////////////////////
        else if (comando == "avanzar_tiempo" or comando == "at"){
            int t;
            cin >> t;
            cout << '#' << comando << ' ' << t << endl;
            c.avanzar_tiempo(t);    
        }

        //////////////////////////////OPERATION//////////////////////////////
        else if (comando == "imprimir_prioridad" or comando == "ipri"){
            string prio;
            cin >> prio;
            cout << '#' << comando << ' ' << prio << endl;
            if (not ade.existe_prioridad(prio)) cout << "error: no existe prioridad" << endl;
            else{
                ade.imprimir_prio(prio);
            }
        }

        //////////////////////////////OPERATION//////////////////////////////
        else if (comando == "imprimir_area_espera" or comando == "iae"){
            cout << "#" << comando << endl;
            ade.imprimir();
        }

        //////////////////////////////OPERATION//////////////////////////////
        else if (comando == "imprimir_procesador" or comando == "ipro"){
            string p;
            cin >> p;
            cout << "#" << comando << ' ' << p << endl;
            if (not c.existe_procesador(p)) cout << "error: no existe procesador" << endl;
            else{
                c.imprimir_procesador(p);
            }
        }

        //////////////////////////////OPERATION//////////////////////////////
        else if (comando == "imprimir_procesadores_cluster" or comando == "ipc"){
            cout << '#' << comando << endl;
            c.imprimir_procesadores();
        }

        //////////////////////////////OPERATION//////////////////////////////
        else if (comando == "imprimir_estructura_cluster" or comando == "iec"){
            cout << "#" << comando << endl;
            c.imprimir_estructura(c);
        }

        //////////////////////////////OPERATION//////////////////////////////
        else if (comando == "compactar_memoria_procesador" or comando == "cmp"){
            string p;
            cin >> p;
            cout << "#" << comando << ' ' << p << endl;
            if (not c.existe_procesador(p)) cout << "error: no existe procesador" << endl;
            else c.compactar_memoria_procesador(p);
        }
        

        //////////////////////////////OPERATION//////////////////////////////
        else if (comando == "compactar_memoria_cluster" or comando == "cmc"){
            cout << "#" << comando << endl;
             c.compactar_memoria_cluster();
        }
        
        cin >> comando;
    }
}
