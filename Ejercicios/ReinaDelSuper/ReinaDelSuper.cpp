/*
 * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificación fuera de esas etiquetas no será corregida.
 */

 /*@ <answer>
  *
  * Indicad el nombre completo y usuario del juez de quienes habéis hecho esta solución:
  * Estudiante 1: Pablo Ezquerro Moya
  * Estudiante 2:
  *
  *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include <queue>
using namespace std;


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

Mi solucion la he pensado usando una estructura por caja en la que se guardara el tiempo que va a estar ocupada
y su numero correspondiente. El orden en la cola sera de menor tiempo de espera a mayor tiempo de espera, sin
importar el numero de caja. Cuando todas las cajas estan usadas entonces se expulsara de la cola la mas prioritaria,
es decir, la q tenia menor tiempo de espera. Y se insertara la sieguiente con su tiempo de espera mas la espera
espulsada.

COSTES-> push y pop tienen coste O(log N)
         top tiene coste O(1)
         el bucle se recorre N veces siendo N el numero de clientes que hay en la fila por lo tanto
         el coste del bucle sera O(N * log N)
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>

typedef struct {
    int nCaja;            
    int tiempo;            
}tCaja;

struct Comparator {
    bool operator()(tCaja const& a, tCaja const& b) {
        return b.tiempo < a.tiempo || ((a.tiempo == b.tiempo) && (b.nCaja < a.nCaja));
    }
};

bool resuelveCaso() {

    // leemos la entrada
    int N, C;
    cin >> N >> C;
    if (N == 0)
        return false;

    // leer el resto del caso y resolverlo
    priority_queue<tCaja, vector<tCaja>, Comparator> cola;
    tCaja aux;
    int t, cajaSiguiente=1;
    for (int i = 0; i < C; i++) {
        cin >> t;
        if (cajaSiguiente <= N) {
            aux.nCaja = cajaSiguiente;
            aux.tiempo = t;
            cola.push(aux); 
            cajaSiguiente++;
        }
        else {
            tCaja saliente= cola.top();
            cola.pop();
            tCaja entrante = { saliente.nCaja, saliente.tiempo + t };
            cola.push(entrante);
        }
    }

    if (cajaSiguiente <= N) {                   
        cout << cajaSiguiente << '\n';
    }
    else {
        cout << cola.top().nCaja << '\n';
    }

    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    // Resolvemos
    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}