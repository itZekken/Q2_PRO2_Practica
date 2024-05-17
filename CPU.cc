 /** @file CPU.cc
 @brief Codigo de la clase CPU
*/

#include "CPU.hh"
//Constructoras

CPU::CPU(){

    espacioDisponible = 0;
    identificador = "-1";
    espacioTotal = 0;
    Procesos.clear();
    mapaProcesos.clear();
    bloquesMemoria.clear();

}

CPU::CPU(const int& espacioMemoria, const string& id) {

    espacioDisponible = espacioMemoria;
    espacioTotal = espacioMemoria;
    identificador = id;
    set<int> posicionesEspacio;
    posicionesEspacio.insert({ 0 });
    bloquesMemoria.insert({ espacioMemoria, posicionesEspacio});

}

//Consultoras

    bool CPU::existe_proceso(const int& idp){

        map<int,Proceso>::iterator it = mapaProcesos.find(idp);
        if(it != mapaProcesos.end()) return true;
        return false;

    }

    string CPU::get_identificador() {

        return identificador;

    }

   bool CPU::En_ejecucion(){
        if(not Procesos.empty()) return true;
        return false;

   }

   int CPU::get_espacio() {
   
       return espacioDisponible;

   }

   bool CPU::buscar_procesador_cluster(BinTree<string>& bt, const string& id){
       if (not bt.empty()){
           if (bt.value() == id){
               if (not bt.left().empty() or not bt.right().empty()) return true;
               return false;
           }
           else{
               BinTree<string> left = bt.left();
               BinTree<string> right = bt.right();
               if (buscar_procesador_cluster(left, id)) return true;
               else if (buscar_procesador_cluster(right, id)) return true;
               return false;
               
           }
       }
       return false;

   }

   int CPU::masAjustado(Proceso& p) {
       //Nos devuelve el hueco más ajustado, y -1 si no se puede colocar.
       //cout << espacioDisponible << " << " << p.get_cantidadMemoria() << endl;
       if (espacioDisponible < p.get_cantidadMemoria()) return -1;
       else {
           map<int, set<int>>::iterator s = bloquesMemoria.lower_bound(p.get_cantidadMemoria()); //Busco dónde está el hueco más ajustado
           map<int, Proceso>::iterator it = mapaProcesos.find(p.get_idp());
           if (s != bloquesMemoria.end() and it == mapaProcesos.end()) { //Se ha encontrado un hueco en el que quepa?
               return s->first; //Este será el tamaño del hueco mas ajustado dentro del procesador.
           }
           return -1; //Si no cabe, devolvemos -1.
       }

   }

   //Modificadoras

   void CPU::restar_espacio_disponible(int& x) {
   
       espacioDisponible -= x;
   
   }

   void CPU::insertar_proceso(Proceso& process) {

       //cout << "Estamos en el procesador " << identificador << endl;
      // cout << espacioDisponible << " < " << process.get_cantidadMemoria() << endl;
       if (espacioDisponible < process.get_cantidadMemoria()) cout << "error: no cabe proceso" << endl;
       else{ //Significa que hay espacio, y además uno donde cabe el proceso.

           pair<unsigned int, unsigned int> def;//Parint que guarda posición y el espacio más ajustado.
           def = { -1,-1 };
           map<int, set<int>>::iterator s = bloquesMemoria.lower_bound(process.get_cantidadMemoria());//Busco dónde está el hueco más ajustado
           if (espacioDisponible == espacioTotal) { //El procesador esta vacio

               espacioDisponible -= process.get_cantidadMemoria();
               def.first = 0;
               def.second = espacioTotal;
               Procesos.insert({ 0, process });
               mapaProcesos.insert({ process.get_idp(), process });
               bloquesMemoria.clear();
               bloquesMemoria[espacioTotal - process.get_cantidadMemoria()].insert(process.get_cantidadMemoria());

           }
           else if (s != bloquesMemoria.end()) {

               def.first = *((s->second).begin()); //Posición del hueco, que es la primera posición del set.
               def.second = (s->first); //Espacio que ocupa.

               espacioDisponible -= process.get_cantidadMemoria(); //Resto espacio disponible
               process.set_dirMem(def.first); //Le pongo la posición de memoria donde estaba
               Procesos.insert({ def.first, process });
               mapaProcesos[process.get_idp()] = process;
               //Ahora vamos a borrar el espacio en bloquesMemoria
               int nuevoHueco = (s->first) - process.get_cantidadMemoria(); //Esto sera el espacio del nuevo hueco.
               int posNuevoHueco = def.first + process.get_cantidadMemoria(); //La posición donde estaba el hueco antes + lo que ocupa el proceso.
               //map<int, set<int>>::iterator buscador = bloquesMemoria.find(nuevoHueco);
               bloquesMemoria[nuevoHueco].insert(posNuevoHueco);
               //Ahora tengo que borrar la posición del hueco dentro del map
               s->second.erase(def.first); //Borro del map la posición del hueco de antes.
               if(s->second.empty())s = bloquesMemoria.erase(s); //Borro el hueco anterior

           }
           else  cout << "error: no cabe proceso" << endl;

       }

   }

   void CPU::borrar_proceso_procesador(int& idp) { //Borra en los dos maps un proceso y añade un hueco al bloque de huecos.
       //El problema viene en que si el proceso que borramos es adyacente a uno o mas huecos, hay que juntarlos con el nuevo hueco y hacer uno mas grande.
       //También tenemos que tener en cuenta si estamos al principio o al final del mapaBloques para no acceder a una posición antes del .begin() o una después del .end()

       map<int, Proceso>::iterator it = mapaProcesos.find(idp); //Encuentra en el mapa de busqueda el proceso 99
       int espacioQueOcupa = (it->second).get_cantidadMemoria(); //Espacio que ocupa el proceso.
       espacioDisponible += espacioQueOcupa; //Suma lo que ocupa el proceso a la cantidad de memoria disponible del procesador.
       int dirMem = (it->second).get_dirMemoria(); //Saca la direccion de memoria donde esta almacenado el proceso.
       mapaProcesos.erase(it);
       Procesos.erase(dirMem);

       //Vamos a actualizar el mapa de bloques, borrándolo y haciéndolo de nuevo.

        recalcular_huecos();
    }

   void CPU::compactar_memoria() {
       int x = bloquesMemoria.begin()->first;
       //cout << x << "!=" << espacioTotal << " and " << bloquesMemoria.size() << endl;
       if (bloquesMemoria.size() >= 1 and x != espacioTotal){ //Si hay espacios, es necesario compactar.

           //cout << "hola" << endl;

           //Empezar a recorrer el mapa 'Procesos', hasta el final. 
           //Si hay un hueco, eliminarlo.
           //ajustar la pos. mem del segundo elemento.
           //No tenemos que borrar todos los huecos, solo cuando hay espacios entre procesos y al principio.

           /*Siempre que compactemos memoria, nos va a quedar o un espacio o ninguno. Entonces, simplemente sería
           hacer un clear del mapa de huecos, juntar todos los huecos en procesos, y luego añadir un hueco.*/
           map<int, Proceso>::iterator it = Procesos.begin();
           if (it->first != 0) { //Si hay un espacio al principio...
               Proceso p = it->second; //Hago una copia del proceso
               it = Procesos.erase(it); //Borro el elemento del map
               Procesos.insert({0,p}); //Lo inserto pero esta vez con posición 0.
               //Todo esto lo tengo que hacer porque tengo un map con la posición de memoria como clave, la cual no se puede cambiar.
               it = Procesos.find(0);
           }

           bloquesMemoria.clear();
           int posPrev = 0;
           int tamanoPrev = 0;
           map<int, Proceso>::iterator elemento = Procesos.begin();
           int posFinal;
           if (Procesos.empty()) posFinal = 0;
           else posFinal = elemento->second.get_dirMemoria() + elemento->second.get_cantidadMemoria();
           map<int, Proceso>::iterator it1 = Procesos.begin();
           while (it1 != Procesos.end()) {
               //cout << it1->first << endl;
               if (it1 == Procesos.begin()) {

                   posPrev = it1->first;
                   tamanoPrev = it1->second.get_cantidadMemoria();
               }
               else {
                   //cout << posPrev << "+" << tamanoPrev << "=" << it1->first;
                   if ((posPrev + tamanoPrev) != it1->first) { //Hay un hueco!

                       Proceso p = it1->second; //Creo copia del proceso.
                       it1 = Procesos.erase(it1); //Borro del mapa.
                       Procesos.insert({ posPrev + tamanoPrev,p }); //Lo inserto de nuevo con la posición nueva.
                       it1 = Procesos.find(posPrev + tamanoPrev);
                   }
                   posPrev = it1->first;
                   tamanoPrev = it1->second.get_cantidadMemoria();
                   posFinal = it1->first + it1->second.get_cantidadMemoria();
               }
               if(it1 != Procesos.end()) ++it1;
           }
           if (posFinal != espacioTotal) {

               int espacio = espacioTotal - (posFinal);
               int posicion = (posFinal);
               map<int, set<int>>::iterator it2 = bloquesMemoria.find(espacio); //Busco por espacio en el mapa.
               bloquesMemoria[espacio].insert(posicion);
           }
       
       }
   }

    void CPU::avanzar_tiempo_procesador(const int& t) {
        
        bool f = false;

        //Dos recorridos para los dos mapas del procesador

        map<int, Proceso>::iterator it1 = Procesos.begin();
        map<int, Proceso>::iterator it2;

        while (it1 != Procesos.end()) {
            if ((it1->second).avanzar_tiempo_proceso(t)) {
                espacioDisponible += (it1->second.get_cantidadMemoria());
                it2 = mapaProcesos.find(it1->second.get_idp());
                it1 = Procesos.erase(it1);
                it2 = mapaProcesos.erase(it2);
                f = true;
            }
            else {
                ++it1;
            }
        }
        if (f) recalcular_huecos();
    }


    void CPU::recalcular_huecos() {

        bloquesMemoria.clear();
        int posPrev = 0;
        int tamanoPrev = 0;
        map<int, Proceso>::iterator elemento = Procesos.begin();
        int posFinal;
        if (Procesos.empty()) posFinal = 0;
        else posFinal = elemento->second.get_dirMemoria() + elemento->second.get_cantidadMemoria();


        if (Procesos.empty()) {

            set<int> nuevoSet;
            nuevoSet.insert(0);
            bloquesMemoria.insert({ espacioTotal,nuevoSet });

        }
        else{
            if (Procesos.begin()->first != 0) {

                set<int> nuevoSet;
                nuevoSet.insert(0);
                bloquesMemoria.insert({ Procesos.begin()->first,nuevoSet });
            }

        }
        for (map<int, Proceso>::iterator it1 = Procesos.begin(); it1 != Procesos.end(); ++it1) {
            
                if (it1 == Procesos.begin()) {

                    posPrev = it1->first;
                    tamanoPrev = it1->second.get_cantidadMemoria();
                }
                else {

                    if ((posPrev + tamanoPrev) != it1->first) { //Hay un hueco!

                        int posNuevoHueco = posPrev + tamanoPrev; //Posición del nuevo hueco

                        int tamanoNuevoHueco = it1->first - posNuevoHueco; //Espacio que ocupa el hueco

                        bloquesMemoria[tamanoNuevoHueco].insert(posNuevoHueco);
                    }
                    posPrev = it1->first;
                    tamanoPrev = it1->second.get_cantidadMemoria();
                    posFinal = it1->first + it1->second.get_cantidadMemoria();
                }


        }
        if (posFinal != espacioTotal) {

           int espacio = espacioTotal - (posFinal);
           int posicion = (posFinal);
           map<int, set<int>>::iterator it2 = bloquesMemoria.find(espacio); //Busco por espacio en el mapa.
           if (it2 != bloquesMemoria.end()) (it2->second).insert(posicion); //Si ya existía le ponemos posición
           else {

               set<int> nuevoSet;
               nuevoSet.insert(posicion);
               bloquesMemoria.insert({ espacio,nuevoSet });

           }
        }

    }
        

    //Entrada/Salida

    /*void CPU::leer_procesador() {
    
        cout << "Escribe el identificador: " << endl;
        cin >> identificador;
        cout << "Está en ejecución? 1/0: " << endl;
        cin >> empty();

    }
    */

    void CPU::imprimir_procesos() {


        for (map<int, Proceso>::iterator it = Procesos.begin(); it != Procesos.end(); ++it) {
        
            cout << (it->first) << ' ' << (it->second).get_idp() << ' ' << (it->second).get_cantidadMemoria() << ' ';
            cout << (it->second).get_tiempoEjecutado() << endl;
        }
       

    }
