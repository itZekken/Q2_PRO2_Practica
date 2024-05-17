/** @file Area_de_espera.cc
 @brief Codigo de la clase Area_de_espera
*/

#include "Area_de_espera.hh"

//Constructoras

Area_de_espera::Area_de_espera(){
    Prioridades.clear();

}

//Consultoras

bool Area_de_espera::existe_prioridad(const string& prio) {

	map<string, Prioridad>::iterator it = Prioridades.find(prio);
	if (it == Prioridades.end()) return false;
	return true;

}

bool Area_de_espera::existe_proceso(const int& idp, const string& prio){

	map<string, Prioridad>::iterator it = Prioridades.find(prio);
	if ((it -> second).existe_proceso(idp)) return true;
	return false;

}

bool Area_de_espera::procesos_pendientes(const string& prio){

	map<string, Prioridad>::iterator it = Prioridades.find(prio);
	if (not (it -> second).esta_vacia()) return true;
	return false;


}

//Modificadoras

void Area_de_espera::anadir_prioridad(const string& prio){

	Prioridad priority;
	Prioridades.insert(make_pair(prio, priority));

}

void Area_de_espera::anadir_proceso(Proceso& process, const string& prio){

	map<string, Prioridad>::iterator it = Prioridades.find(prio);
	(it->second).anadir_proceso(process);

}

void Area_de_espera::borrar_prioridad(string& prio){

	Prioridades.erase(prio);

}


void Area_de_espera::enviar_procesos(int& n, Cluster& c){

	int i = 0; //Voy a hacer un contador para los procesos que se van enviando.
	map<string, Prioridad>::iterator it = Prioridades.begin(); //Por cada prioridad por orden...
	while (i < n and it != Prioridades.end()) { //Recorro todas las prioridades.

		int colocados = 0; 
		int rechazados = 0;

		/*Lo que voy a hacer es sacar la medida de la lista. De esta manera, al recorrer la lista, si uno 
		de los procesos queda rechazado y se tiene que volver a recolocar en la lista, no entraríamos en 
		un bucle infinito. Sacando la memoria de la lista solo recorrere la lista una vez.*/
		list<Proceso>listaProceso = it->second.get_lista(); //Saco la lista de procesos de la prioridad que quiero.
		int size = listaProceso.size(); //Medida de la lista.
		list<Proceso>::iterator it1 = listaProceso.begin(); //Iterador que recorre la lista.
		int j = 0; //Este será el contador de procesos que se han enviado en esta iteración.
		while(j < size and n > i){ //Recorro los procesos de la lista por orden cronológico.
			//(*it1).imprimir_proceso();
			bool f = c.enviar_proceso_cluster(*it1); //Esta funcion podria ser un booleano...

			if (f) { //Si se ha podido enviar el proceso...
				++colocados; //Se ha colocado uno nuevo
				//Por lo tanto, hay que eliminarlo de su prioridad correspondiente.
				++i;
			}
			else {
				++rechazados; //Se ha rechazado uno nuevo.
				listaProceso.push_back(*it1); //Añado el mismo proceso al final de la lista
			}
            int idp = it1->get_idp();
			it1 = listaProceso.erase(it1); //Borro el proceso que no hemos insertado.
            it->second.borrar_proceso(idp); //También lo borro de mi mapa de prioridades
			++j;
		}
		(it->second).colocados_rechazados(colocados,rechazados); //Actualiza los colocados y rechazados en la prioridad
		(it->second).set_lista(listaProceso); //Le cambio la lista por la que hemos modificado.
		//cout << "LA I ES IGUAL A " << i << " < " << n << "EN LA PRIORIDAD " << it->first << endl;
		++it;

	}


}

//Entrada/Salida

void Area_de_espera::leer_Area() {

	int x; 
	cin >> x; 
	for (int i = 1; i <= x; ++i) {
	
		Prioridad p;
		string s;  
		cin >> s;
		Prioridades.insert(make_pair(s, p));

	}

}

void Area_de_espera::imprimir_prio(const string& prio) {

	map<string, Prioridad>::iterator it = Prioridades.find(prio);
	(it->second).imprimir_prioridad();

}

void Area_de_espera::imprimir() {

	for (map<string, Prioridad>::iterator it = Prioridades.begin(); it != Prioridades.end(); ++it) {
		cout << (it->first) << endl;
		(it->second).imprimir_prioridad();

	}

}


