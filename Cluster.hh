/** @file Cluster.hh
 @brief Especificación de la clase Cluster
*/
#ifndef _CLUSTER_HH_
#define _CLUSTER_HH_

#include "CPU.hh"
#include "BinTree.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include <map>
#include <climits>
using namespace std;    
#endif

/** @class Cluster
 @brief Representa un bloque con un conjunto de procesadores en forma de árbol.
 Cada procesador puede tener dos, uno o cero procesadores sucesores, también
 llamados auxiliares. Todo clúster ha de tener como mínimo un procesador, pudiendo ser éste incluso otro cluster.
 Tiene un identificador único.
*/

class Cluster{

private:

    BinTree<string> pTree; 
    string id; 
    map<string, CPU> busquedaCPU;
    map<string, CPU> reserva;

public:

    //Constructoras

    /** @brief Constructora por defecto
        \pre: <em>cierto</em>
        \post: Crea un cluster vacío
    */
    Cluster();

    //Consultoras

    /** @brief Nos muestra si existe un procesador.
        \pre <em>Dado un identificador de procesador p</em>
        \post Devuelve true o false dependiendo de si existe un procesador en el cluster con identificador p.
    */
    bool existe_procesador(const string& p);

    /** @brief Busca un procesador en el cluster y lo devuelve.
        \pre <em>Dado un identificador de proceso p</em>
        \post Busca el procesador con identificador p en el cluster.
    */
    CPU buscar_procesador(const string& p);

    /** @brief Comprueba que el procesador tenga hijos o no.
        \pre <em>cierto</em>
        \post Devuelve true o false dependiendo si el procesador tiene hijos o no.
    */
    bool tiene_auxiliares(CPU& cpu);

    /** @brief Devuelve el árbol de procesadores de un árbol
        \pre <em>cierto</em>
        \post Devuelve el árbol de procesadores de un árbol.
    */
    BinTree<string> get_tree();

    /** @brief Devuelve el map guardado como reserva.
        \pre <em>cierto</em>
        \post Devuelve el map guardado como reserva.
    */
    map<string, CPU> get_reserva();

    /** @brief ***.
        \pre <em>***</em>
        \post ***.
    */
    void mesProperArrel(string a, string& b, BinTree<string>& bt, int prof, int posEsquerra, string& mesProper, int& profMinima, int& posMinimaEsquerra);

    // Modificadores
    
    /** @brief Envia un proceso a un procesador del cluster
        \pre <em>Dado un proceso process y un identificador de procesador p</em>
        \post Envía un proceso process al procesador con identificador p
    */
    void enviar_proceso_procesador(Proceso& process, const string& p);
  
    /** @brief Borra un proceso
        \pre <em>Dado un identificador de procesador p y un identificador de proceso idp</em>
        \post Borra el proceso con identificador idp del procesador con identificador idp del cluster
    */
    void borrar_proceso(const string& p, int& idp);

    /** @brief Avanza unidades de tiempo los procesadores.
        \pre <em>Dado un entero t</em>
        \post  Avanza t unidades de tiempo los procesadores y se eliminan todos los procesos activos
        que hayan acabado en ese intervalo de tiempo.
    */
    void avanzar_tiempo(int t);

    /** @brief Compacta la memoria de un procesador con identificador 'p'.
        \pre <em>Dado un identificador de procesador p</em>
        \post Se mueven todos los procesos hacia el principio de
        la memoria del procesador p, sin dejar huecos, sin solaparse y respetando el orden inicial.
    */
    void compactar_memoria_procesador(const string& p);

    /** @brief Compacta la memoria del cluster.
        \pre <em>cierto</em>
        \post En todos los procesadores del cluster se ha compactado la memoria tal como hace la función compactar_memoria_procesador.
    */
    void compactar_memoria_cluster();

    /** @brief Coloca el cluster nuevo en el árbol.
        \pre <em>cierto</em>
        \post Coloca el cluster nuevo en el árbol.
    */
    void colocar_cluster_arbol(string& p, Cluster& c1);

    /** @brief Coloca un cluster en el lugar de un procesador
        \pre <em>Dado un identificador de procesador t</em>
        \post Coloca un cluster nuevo en el lugar del procesador con identificador p.
    */
    void colocar_cluster_arbol_2(BinTree<string>& bt, string& p, BinTree<string>& bt2);

    /** @brief Mete los procesadores del arbol en el mapa de procesadores.
        \pre <em>Dado un arbol con procesadores t</em>
        \post Mete los procesadores del arbol en el mapa de procesadores del cluster.
    */
    void actualizar_mapa(map<string,CPU>& reserva);

    /** @brief Mueve la reserva del cluster del parametro al cluster actual.
        \pre <em>Dado un cluster</em>
        \post Mueve la reserva del cluster dado al cluster actual.
    */
    void modificar_reserva(Cluster& c1);

    /** @brief Envia un proceso al cluster.
        \pre <em>Dado un entero n y un cluster c</em>
        \post Envia un proceso al cluster. Si se ha podido insertar, devuelve true, y de lo contrario, false.
    */
    bool enviar_proceso_cluster(Proceso& p);

    //Entrada/Salida

    /** @brief Indica los erorres que puede haber al colocar un proceso en un procesador del cluster.
        \pre <em>Dado un proceso process, un identificador de procesador p y un cluster c</em>
        \post Devuelve un entero entre 0 y 3 según si existe el procesador en el cluster o no,
        si hay un proceso con el mismo identificador, si no hay espacio para colocar el proceso o ninguna de las anteriores.
    */
    int alta_proceso_procesador(Proceso& process, const string& p, Cluster& c);
  
    /** @brief Indica los erorres que puede haber al eliminar un proceso de un procesador del cluster.
        \pre <em>Dado un identificador de proceso idp, un identificador de procesador p y un cluster c</em>
        \post Devuelve un entero entre 0 y 2 según si existe el procesador en el cluster o no,
        si hay un proceso con el mismo identificador o ninguna de las anteriores.
    */
    int baja_proceso_procesador(int& idp, const string& p, Cluster& c);

    /** @brief Lee los procesadores del cluster.
        \pre <em>Dado un cluster c</em>
        \post Lee la estructura de los procesadores del cluster.
    */
    void leer_procesadores(Cluster& c);

    /** @brief Lee el arbol binario.
         \pre <em>Dado un arbol binario s y un conjunto de procesadores m</em>
        \post Lee el arbol binario de procesadores en forma de string y los almacena en el conjunto m.
    */
    void leer_arbol(BinTree<string>& s, map<string, CPU>& m);

    /** @brief Lee el mapa de procesadores.
         \pre <em>Dado un identificador de procesador p</em>
         \post Imprime el procesador p y sus procesos almacenados.
    */
    void imprimir_procesador(const string& p);
    
    /** @brief Imprime todos los procesadores del cluster.
        \pre <em>cierto</em>
        \post Imprime todos los procesadores del cluster. 
    */
    void imprimir_procesadores();

    /** @brief Imprime la estructura del cluster.
        \pre <em>Dado un cluster c </em>
        \post Llama a la función recursiva imprimir_arbol que escribe la estructura del cluster c.
    */
    void imprimir_estructura(Cluster &c); 

    /** @brief Imprime la estructura del árbol del cluster.
        \pre <em>Dado un arbol binario bt</em>
        \post Imprime todos los procesadores del cluster según la estructura del arbol binario bt que forman.
    */
    void imprimir_arbol(const BinTree<string>& bt);

   

};
#endif
