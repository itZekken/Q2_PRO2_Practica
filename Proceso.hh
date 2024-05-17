/** @file Proceso.hh
 @brief Especificación de la clase Proceso
*/
#ifndef _PROCESO_HH_
#define _PROCESO_HH_

#ifndef NO_DIAGRAM
#include <iostream>
using namespace std;
#endif

/** @class Proceso
 @brief Representa un proceso.
 Este proceso puede ser ejecutado en uno de los procesadores del cluster o puede estar en pausa en el área de espera.
 Tiene un identificador único.
*/

class Proceso{

private:

    int idp; //Identificador de proceso
    int cantidadMemoria;
    int tiempoEjecutado;
    int posicionMemoria;
   
public:

    //Constructoras

     /** @brief Constructora por defecto
         \pre: <em>cierto</em>
         \post: Crea un proceso vacío.
     */
    Proceso();

    //Consultoras

    /** @brief Consulta el identificador.
        \pre <em>cierto</em>
        \post Devuelve el identificador idp del proceso.
    */
    int get_idp();

    /** @brief Consulta el tiempo ejecutado.
        \pre <em>cierto</em>
        \post Devuelve el tiempo de ejecución.
    */
    int get_tiempoEjecutado();

    /** @brief Consulta la cantidad de memoria.
        \pre <em>cierto</em>
        \post Devuelve la cantidad de memoria que ocupa el proceso.
    */
    int get_cantidadMemoria();

    /** @brief Consulta la direccion de memoria.
        \pre <em>cierto</em>
        \post Devuelve la direccion de memoria donde esta colocado el proceso en el procesador.
    */
    int get_dirMemoria();

    //Modificadoras

    /** @brief Establece la posición de memoria como parámetro privado.
        \pre <em>Dado una direccion de memoria x</em>
        \post El parametro de la direccion de memoria del procesador ha sido actualizado.
    */
    void set_dirMem(const int& x);

    /** @brief Avanza el tiempo en el proceso.
        \pre <em>Dadas t unidades de tiempo a avanzar</em>
        \post Avanza el tiempo en el proceso y si es <= 0 el devuelve true. De lo contrario devuelve false.
    */
    bool avanzar_tiempo_proceso(const int& t);
    
    //Entrada/Salida

    /** @brief Lee un proceso.
        \pre <em>cierto</em>
        \post Lee un proceso y sus parámetros.
    */
    void leer_proceso();

    /** @brief Imprime los parámetros de un proceso.
        \pre <em>cierto</em>
        \post Imprime los parámetros del proceso.
    */
    void imprimir_proceso();

};
#endif
