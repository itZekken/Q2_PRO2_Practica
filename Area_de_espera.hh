/** @file Area_de_espera.hh
 @brief Especificación de la clase Area_de_espera
*/
#ifndef _AREA_DE_ESPERA_HH_
#define _AREA_DE_ESPERA_HH_

#include "Cluster.hh"
#include "Prioridad.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include <list>
#include <map>
using namespace std;
#endif

/** @class Area_de_espera
 @brief Representa un área en la que hay procesos pendientes preparados para entrar al cluster y ser ejecutados.
 Éste área ordena los procesos pendientes por prioridades, representadas por una etiqueta. 
 A menor nombre, mayor prioridad.
*/

class Area_de_espera{

private:

    map<string, Prioridad> Prioridades; //Así, el map se ordena por el string (la etiqueta) y luego en el value tenemos las prioridades. 

public:
    //Constructoras

    /** @brief Constructora por defecto
        \pre: <em>cierto</em>
        \post: Crea un área de espera vacía
    */
    Area_de_espera();

    //Consultoras

    /** @brief Nos dice si existe una prioridad en el área de espera
        \pre <em>Dado un identificador de prioridad prio</em>
        \post Devuelve cierto o falso dependiendo si existe una prioridad con identificador prio en el área de espera.
        \coste Logaritmico
    */
    bool existe_prioridad(const string& prio);
    
    /** @brief Nos dice si existe un proceso en el área de espera
        \pre <em>Dado un identificador de prioridad prio y un identificador de proceso idpr</em>
        \post Devuelve cierto o falso dependiendo si existe un proceso con identificador idp en el area de espera.
        \coste Logaritmico
    */
    bool existe_proceso(const int& idp, const string& prio);

    /** @brief Nos dice si existen procesos pendientes en una prioridad en concreto.
        \pre <em>Dado un identificador de prioridad prio</em>
        \post Devuelve cierto o falso dependiendo si existen procesos pendientes en la prioridad prio.
        \coste Logaritmico
    */
    bool procesos_pendientes(const string& prio);

    //Modificadoras

     /** @brief Añade una prioridad nueva.
        \pre <em>Dado un identificador de prioridad prio</em>
        \post Añade una prioridad nueva al área de espera con la etiqueta prio.
        \coste Constante
     */
    void anadir_prioridad(const string& prio);

    /** @brief Añade un proceso nuevo.
        \pre <em>Dado un identificador de prioridad prio y un proceso process</em>
        \post Añade un proceso process al área de espera en la prioridad prio.
        \coste Logaritmico
    */
    void anadir_proceso(Proceso& process, const string& prio);

    /** @brief Borra una prioridad.
        \pre <em>Dado un identificador de prioridad prio</em>
        \post Borra la prioridad con identificador prio del el área de espera.
        \coste Logaritmico
    */
    void borrar_prioridad(string& prio);

    /** @brief Envía n procesos al cluster
       \pre <em>Dado un entero n y un cluster c</em>
       \post Envía n procesos al cluster c.
       \coste Lineal
    */
    void enviar_procesos(int& n, Cluster& c);

    //Entrada/Salida

    /** @brief Lee el área de espera.
       \pre <em>cierto</em>
       \post Lee las prioridades del area de espera.
       \coste Lineal
    */
    void leer_Area();

    /** @brief Imprime la prioridad prio.
        \pre <em>Dado un identificador de prioridad prio</em>
        \post Imprime todos los procesos pendientes de la prioridad prio. Además, escribe
         el número de procesos de la prioridad colocados en el clúster por la operación
         enviar_procesos_a_cluster y el número de rechazos.
         \coste Constante
    */
    void imprimir_prio(const string& prio);

    /** @brief Imprime el área de espera al completo.
        \pre <em>cierto</em>
        \post Imprime todas las prioridades y los procesos pendientes del área de espera por orden creciente de prioridad
        y cronologico para los procesos.
        \coste Lineal
    */
    void imprimir();

};
#endif
