/** @file CPU.hh
 @brief Especificación de la clase CPU
*/
#ifndef _CPU_HH_
#define _CPU_HH_

#include "Proceso.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <set>
#include "BinTree.hh"
using namespace std;
#endif

/** @class CPU
 @brief Representa un procesador, que está en el cluster.
 Los procesadores ejecutan los que les llegan directamente o desde el área de espera.
 Cada procesador dispone de una cantidad de memoria limitada para almacenar diversos procesos.
 Tiene un identificador único.
*/

class CPU{

private:

    string identificador;
    int espacioDisponible; //Espacio disponible. Se resta cuando coloco un proceso, y se suma cuando un proceso termina.
    int espacioTotal; //Espacio total de la memoria.
    map<int,Proceso> Procesos; //Posición, proceso. Para definir la memoria y la posición de cada proceso.
    map<int,Proceso> mapaProcesos; //ID, proceso. Para la busqueda.
    map<int, set<int>> bloquesMemoria; //Tamaño hueco, posiciones del hueco.


public:

    //Constructoras
        
    /** @brief Constructora por defecto
        \pre: <em>cierto</em>
        \post: Crea un procesador con su memoria vacía
    */
    CPU();

    /** @brief Constructora
         \pre: <em>Dado el espacio de memoria espacioMemoria que le queremos asignar al procesador</em>
         \post: Crea un procesador con una memoria.
    */
    CPU(const int& espacioMemoria, const string& id);

    //Consultoras

    /** @brief Consulta la existencia de un proceso en el procesador.
        \pre <em>cierto</em>
        \post Devuelve true/false dependiendo si existe el procesador o no.
    */
    bool existe_proceso(const int& idp);

    /** @brief Consulta el identificador del procesador.
        \pre <em>Dado un procesador en el parametro implicito </em>
        \post Devuelve el identificador del procesador en el que se ejecuta la función.
    */
    string get_identificador();

    /** @brief Comprueba si el procesador tiene procesos activos
        \pre <em>cierto</em>
        \post Devuelve cierto o falso dependiendo si el procesador tiene procesos activos o no.
    */
    bool En_ejecucion();

    /** @brief Consulta el espacio que le queda al procesador.
        \pre <em>cierto</em>
        \post Devuelve el espacio que le queda al procesador en forma de posiciones.
    */
    int get_espacio();

    /** @brief Busca un procesador en el árbol binario del cluster
        \pre <em>cierto</em>
        \post Devuelve el identificador del procesador buscado.
    */
    bool buscar_procesador_cluster(BinTree<string>& bt, const string& id);

    /** @brief Busca el espacio mas ajustado del procesador.
        \pre <em>cierto</em>
        \post Devuelve el hueco más ajustado dentro del proceso y si no se puede colocar, devuelve -1.
    */
    int masAjustado(Proceso& p);


    //Modificadoras

     /** @brief ***
        \pre <em>***</em>
        \post ***
    */
    void restar_espacio_disponible(int& x);

    /** @brief Inserta un proceso en la memoria del procesador
        \pre <em>Dado un proceso process</em>
        \post Inserta un proceso process en la memoria del procesador.
    */
    void insertar_proceso(Proceso& process);

    /** @brief Elimina un proceso de la memoria del procesador
        \pre <em>Dado un identificador de proceso idp</em>
        \post Elimina un proceso idp de la memoria del procesador.
    */
    void borrar_proceso_procesador(int& idp);

    /** @brief Compacta la memoria del procesador
        \pre <em>cierto</em>
        \post Se mueven todos los procesos hacia el principio de
        la memoria del procesador, sin dejar huecos, sin solaparse y respetando el orden inicial.
    */
    void compactar_memoria();

    /** @brief Avanza el tiempo de todos los procesos del procesador.
         \pre <em>Dado un entero t</em>
         \post Todos los procesos del procesador serán avanzados t unidades de tiempo.
    */
    void avanzar_tiempo_procesador(const int& t);


    /** @brief Recalcula los huecos al eliminar un proceso.
        \pre <em>Dado un entero t</em>
        \post Recalcula los huecos al eliminar un proceso.
    */
    void recalcular_huecos();

    //Entrada/Salida

     /** @brief Lee los datos de un procesador.
       \pre: <em>cierto</em>
       \post: Lee los parámetros del procesador.
     */
    void leer_procesador();

    /** @brief Imprime los procesos del procesador.
        \pre <em>cierto</em>
        \post Imprime los procesos almacenados en la memoria del procesador.
    */
    void imprimir_procesos();

};
#endif
