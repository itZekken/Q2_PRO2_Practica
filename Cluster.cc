/** @file Cluster.cc
 @brief Codigo de la clase Cluster
*/

#include "Cluster.hh"

//Constructoras

Cluster::Cluster(){

	busquedaCPU.clear();
    reserva.clear();
	BinTree<string> s;
	pTree = s;

}

//Consultoras

bool Cluster::existe_procesador(const string& p) {

	map<string, CPU>::iterator it = busquedaCPU.find(p);
	if (it != busquedaCPU.end()) return true;
	return false;

}

CPU Cluster::buscar_procesador(const string& p) {

	map<string, CPU>::iterator it = busquedaCPU.find(p);
	return (it->second);
}

bool Cluster::tiene_auxiliares(CPU& cpu) {

	string id = cpu.get_identificador();
	return cpu.buscar_procesador_cluster(pTree, id);

}

BinTree<string> Cluster::get_tree() {

	return pTree;
}

map<string, CPU>Cluster::get_reserva(){

	return reserva;

}

void Cluster::mesProperArrel(string a, string& b, BinTree<string>& bt, int prof, int posEsquerra, string& mesProper, int& profMinima, int& posMinimaEsquerra) {

	if (not bt.empty()){
	
		if ((bt.value() == a or bt.value() == b) and (prof < profMinima or (prof == profMinima and posEsquerra < posMinimaEsquerra))){
			mesProper = bt.value();
			profMinima = prof;
			posMinimaEsquerra = posEsquerra;
		}
		BinTree<string>left = bt.left();
		BinTree<string>right = bt.right();
		mesProperArrel(a, b, left, ++prof, posEsquerra * 2, mesProper, profMinima, posMinimaEsquerra);
		mesProperArrel(a, b, right, ++prof, posEsquerra * 2+1, mesProper, profMinima, posMinimaEsquerra);
	}
}

//Modificadoras

void Cluster::enviar_proceso_procesador(Proceso& process, const string& p) {

	map<string, CPU>::iterator it = busquedaCPU.find(p);
	(it->second).insertar_proceso(process);

}

void Cluster::borrar_proceso(const string& p, int& idp) {

	map<string, CPU>::iterator it = busquedaCPU.find(p); //Buscamos el procesador.
	(it->second).borrar_proceso_procesador(idp);


}

void Cluster::avanzar_tiempo(int t) {

	/*Sería restar una cantidad de tiempo a cada uno de los procesos de todos los procesadores
	* y si se quedan a 0 o negativo eliminarlos? */
	
	for (map<string, CPU>::iterator it = busquedaCPU.begin(); it != busquedaCPU.end(); ++it) {

		(it->second).avanzar_tiempo_procesador(t);

	}
}	

void Cluster::compactar_memoria_procesador(const string& p) {

	map<string, CPU>::iterator it = busquedaCPU.find(p);
	it->second.compactar_memoria();


}

void Cluster::compactar_memoria_cluster() {

	for (map<string, CPU>::iterator it = busquedaCPU.begin(); it != busquedaCPU.end(); ++it) {
		it->second.compactar_memoria();
	}

}
void Cluster::colocar_cluster_arbol(string& p, Cluster& c1) {

	modificar_reserva(c1);
	BinTree<string> b = c1.get_tree();
	colocar_cluster_arbol_2(pTree,p,b);

}

void Cluster::colocar_cluster_arbol_2(BinTree<string>& bt, string& p, BinTree<string>& bt2){

	if (not bt.empty()){
	
		if (bt.value() == p){
			busquedaCPU.erase(p);
			actualizar_mapa(reserva);
			bt = bt2;
			reserva.clear(); //Puede dar problemas?
		}
		else{
		
			BinTree<string> left = bt.left();
			BinTree<string> right = bt.right();
			colocar_cluster_arbol_2(left, p, bt2);
			colocar_cluster_arbol_2(right, p, bt2);
			bt = BinTree<string>(bt.value(), left, right);
		
		}
	
	}

}

void Cluster::actualizar_mapa(map<string, CPU>& reserva) {

	busquedaCPU.insert(reserva.begin(), reserva.end()); /*Mete en busquedaCPU todos los elementos de la reserva, es
														decir, del segundo bintree*/
}

void Cluster::modificar_reserva(Cluster& c1) {

	reserva = c1.get_reserva();

}

bool Cluster::enviar_proceso_cluster(Proceso& p) {

	//Acordarse de que no puedo meter dos procesos con el mismo identificador en el mismo procesador.
	//Recorreré todos los procesadores del cluster y lo meteré en el que tenga el hueco más ajustado.
	if (not busquedaCPU.empty()){
		string procesadorDestino;
		int espacioMasAjustado = INT_MAX;
		int aux;
		bool sePuedeColocar = false;
		bool sePuedeColocarProcesador = false;
		for (map<string, CPU>::iterator it = busquedaCPU.begin(); it != busquedaCPU.end(); ++it) {
           // cout << "ESTOY EN EL PROCESADOR " << it->first << endl;
			sePuedeColocarProcesador = false;
			//Mirar si cabe en el procesador. Si cabe, que devuelva el hueco más ajustado.
			
			if (it == busquedaCPU.begin()){	//Si es la primera iteración, que lo guarde como mas ajustado.

				aux = it->second.masAjustado(p);
				//cout << "EL ESPACIO MAS AJUSTADO ES IGUAL A " << aux << endl;
				if (aux != -1) {
					espacioMasAjustado = aux;
					procesadorDestino = it->first;
					sePuedeColocarProcesador = true;
					sePuedeColocar = true;
				}
				//cout << "ES EL PRIMERO" << endl;

			}
			else {
				int nuevoEspacioMasAjustado = it->second.masAjustado(p); //Esto devolverá el hueco mas ajustado dentro del proceso y -1 si no ha podido colocarlo.
				//cout << "NUEVO ESPACIO MAS AJUSTADO ES DE " << nuevoEspacioMasAjustado << endl;
				if (nuevoEspacioMasAjustado != -1) sePuedeColocarProcesador = true; //Si nos ha devuelto el hueco mas ajustado es porque se puede colocar.
				//cout << sePuedeColocarProcesador << endl;
				if (sePuedeColocarProcesador and nuevoEspacioMasAjustado <= espacioMasAjustado) {
					sePuedeColocar = true;
					if (nuevoEspacioMasAjustado < espacioMasAjustado) {
						if (not it->second.existe_proceso(p.get_idp())) {
							espacioMasAjustado = nuevoEspacioMasAjustado;
							procesadorDestino = it->first;
						}
					}
					else { //Cuidado porque los dos procesadores tienen el mismo espacio mas ajustado.
						//Ahora a buscar cuál es el que tiene la mayor memoria disponible al meterlo.
						map<string, CPU>::iterator a = busquedaCPU.find(procesadorDestino); //Busco el primer procesador...
						int espacioAntiguoAv = a->second.get_espacio(); //Espacio disponible del primer procesador.
						int nuevoEspacioAv = it->second.get_espacio(); //Espacio disponible del segundo procesador.
						if (nuevoEspacioAv <= espacioAntiguoAv) {
							if (nuevoEspacioAv > espacioAntiguoAv) {
								if (not it->second.existe_proceso(p.get_idp())) {
									espacioMasAjustado = nuevoEspacioMasAjustado;
									procesadorDestino = it->first;
								}
							}
							else { //Otro empate: los espacios que quedan son iguales. Pillamos el de mas arriba a la izquierda en el arbol.
								//cout << "EMPATE POR ARBOL" << endl;
								//Hare una busqueda por preorden
								string mesProper;
								int profMinima = INT_MAX;
								int posMinimaEsquerra = INT_MAX;
								mesProperArrel(it->first, procesadorDestino, pTree, 0, 0, mesProper, profMinima, posMinimaEsquerra);
								//Esta funcion me pillara el procesador de los dos que esta mas arriba a la izquerda. 
								map<string, CPU>::iterator v = busquedaCPU.find(mesProper);
								if(not v->second.existe_proceso(p.get_idp())) procesadorDestino = mesProper; //El procesador destino sera el mas cercano.
							}
						}
						//Sino significa que el anterior sigue siendo mejor espacio asi que terminado. 
					}
				}
				//Sino significa que no se puede colocar o que el anterior espacio sigue siendo mejor espacio asi que terminado.
			}
			//cout << "EL ESPACIO MAS AJUSTADO POR AHORA ES DE " << espacioMasAjustado << endl;
			//cout << "EL PROCESADOR DESTINO ES: " << procesadorDestino << endl;
		}
		if (not sePuedeColocar) return false; //Significará que no se ha podido insertar en ningún procesador.
		else { /*Habremos encontrado el procesador que tiene el hueco más ajustado, si hay empate el que tiene mas memoria libre,
			   si hay empate el que esta mas cercano a la raiz y si hay otro mas el que esta mas a la izquierda*/
			//cout << "ME VOY A COLOCAR EN EL PROCESADOR " << procesadorDestino << "EN EL HUECO DE TAMAÑO " << espacioMasAjustado << endl;

			map<string, CPU>::iterator buscador = busquedaCPU.find(procesadorDestino); //Busco el procesador destino.
			buscador->second.insertar_proceso(p); //Lo inserto.
			int espacio = p.get_cantidadMemoria();
			buscador->second.restar_espacio_disponible(espacio);
			return true;
		}
	
	}
	return false;

}


//Entrada/Salida

int Cluster::alta_proceso_procesador(Proceso& process, const string& p, Cluster& c) {

	if (not c.existe_procesador(p)) return 3;
	else {
		map<string, CPU>::iterator it = busquedaCPU.find(p); //Busca el procesador
		int idp = process.get_idp();
		if ((it->second).existe_proceso(idp)) return 2;
		else return 1;
	
	}

}

int Cluster::baja_proceso_procesador(int& idp, const string& p, Cluster& c) {


	if (not c.existe_procesador(p)) return 2;
	else {
		map<string, CPU>::iterator it = busquedaCPU.find(p); //Busca el procesador en el cluster.
		if (not (it->second).existe_proceso(idp)) return 1; //Si no existe el proceso dentro del procesador.
		else return 3;
	}

}

void Cluster::leer_procesadores(Cluster& c){

	leer_arbol(c.pTree, c.busquedaCPU);

}

void Cluster::leer_arbol(BinTree<string>& s, map<string, CPU>& m){
	
	string a; 
	cin >> a;
	if (a != "*") {

		int x; 
		cin >> x;
		CPU procesador(x,a);
		reserva.insert({ a, procesador });
		m[a] = procesador;
		BinTree<string> b;
		BinTree<string> c;
		leer_arbol(b, m);
		leer_arbol(c, m);
		s = BinTree<string>(a, b, c);
	
	}

}

void Cluster::imprimir_procesador(const string& p) {

	map<string, CPU>::iterator it = busquedaCPU.find(p);
	(it->second).imprimir_procesos();

}

void Cluster::imprimir_procesadores() {

	for (map<string, CPU>::iterator it = busquedaCPU.begin(); it != busquedaCPU.end(); ++it) {
	
		cout << (it->first) << endl;
		(it->second).imprimir_procesos();


	}
}

void Cluster::imprimir_estructura(Cluster& c) {

	c.imprimir_arbol(c.pTree);
	cout << endl;

}

void Cluster::imprimir_arbol(const BinTree<string>& bt) {

	if (not bt.empty()){

		cout << "(" << bt.value();
		imprimir_arbol(bt.left());
		imprimir_arbol(bt.right());
		cout << ')';
		return;
	}
	cout << ' ';

}
