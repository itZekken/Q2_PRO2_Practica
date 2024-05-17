#ifndef _Prioridad_HH
#define _Prioridad_HH

#include "Proceso.hh"
#ifndef NO_DIAGRAM
#include <iostream>
#include <list>
#include <map>
using namespace std;
#endif

/** @class Prioridad
 @brief Representa una prioridad dentro del area de espera.
 Esta prioridad tiene una etiqueta que indica su orden, y cada prioridad contiene una lista de procesos pendientes.
*/

class Prioridad{

private:
    int colocados;
    int rechazados;
    map<int, Proceso> prioProcesos; //Id, Proceso
    list<Proceso> listaProcesos; //Lista de procesos ordenados por orden cronológico.

public:

    /** @brief Constructora por defecto
        \pre: <em>cierto</em>
        \post: Crea una prioridad vacía.
    */
    Prioridad();

    //Consultoras

     /** @brief Lee un proceso.
         \pre <em>Dado un identificador de proceso etiq</em>
         \post Devuelve true/false dependiendo si el proceso con la etiqueta etiq está en esta prioridad.
    */
    bool existe_proceso(const int& etiq);

    /** @brief Devuelve la lista de procesos de la prioridad.
        \pre <em>Dado un identificador de proceso etiq</em>
        \post Devuelve la lista de procesos de la prioridad.
   */
    list<Proceso> get_lista();

  /** @brief ***
        \pre <em>***</em>
        \post ***
   */
    void borrar_proceso(int& idp);


    /** @brief Dada una prioridad.
      \pre <em>cierto</em>
      \post Devuelve true/false dependiendo si la prioridad está vacía.
    */
    bool esta_vacia();

    //Modificadoras

    /** @brief Añade un proceso a una prioridad.
         \pre <em>Dado un proceso p con sus parámetros</em>
         \post Inserta el proceso en la prioridad.
    */
    void anadir_proceso(Proceso& p);

    /** @brief Establece los procesos colocados y rechazados.
        \pre <em>Dado un proceso p con sus parámetros</em>
        \post Los procesos colocados y rechazados han sido actualizados.
    */
    void colocados_rechazados(int& a, int& b);

    /** @brief Cambia la lista del parametro privado por una nueva.
        \pre <em>Dada una lista</em>
        \post La lista de procesos ha sido actualizada.
    */
    list<Proceso> set_lista(list<Proceso>& l);

    //Entrada/Salida

    /** @brief Imprime una prioridad
         \pre <em>Dada una prioridad prio</em>
         \post Imprime la prioridad prio con todos sus procesos pendientes.
    */
    void imprimir_prioridad();

};
#endif
