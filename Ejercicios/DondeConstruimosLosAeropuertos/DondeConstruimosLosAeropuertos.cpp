/*
 * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificación fuera de esas etiquetas no será corregida.
 */

 /*@ <answer>
  *
  * Indicad el nombre completo y usuario del juez de quienes habéis hecho esta solución:
  * Estudiante 1: Pablo Ezquerro Moya DA09
  * Estudiante 2:
  *
  *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

#include "GrafoValorado.h"
#include "PriorityQueue.h"
#include "ConjuntosDisjuntos.h"


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 Para realizar este ejercicio, lo primero que hago es completar un grafo
 valorado en el que los vértices son todos los lugares del país. Las aristas
 son los caminos. No añado todos los caminos ya que si un camino cuesta más
 que un aeropuerto, no quiero que este forme parte del árbol de recubrimiento
 mínimo. El ARM lo calculo utilizando el algoritmo de Kruskal, en el cual
 declaro una variable nueva con el número de aeropuertos necesarios. En un
 principio serán los mismos que vértices tenga el grafo e iran disminuyendo
 segun vaya completandose el ARM.

 COSTE -> O(A log A)
 He ido poniendo los costes del algoritmo en el código

 @ </answer> */

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>

template <typename Valor>
class ARM_Kruskal {
private:
    vector<Arista<Valor> > _ARM;
    Valor coste;
    int aeropuertos;

public:
    ARM_Kruskal(GrafoValorado<Valor> const& g, int costeAeropuerto) : coste(0), aeropuertos(g.V()) { // O(A log A)
        PriorityQueue<Arista<Valor>> pq(g.aristas()); // O(A)
        ConjuntosDisjuntos cjtos(g.V()); // O(V)
        while (!pq.empty()) {
            auto a = pq.top(); pq.pop(); // pop -> O(log A)
            int x = a.uno(), y = a.otro(x);
            if (!cjtos.unidos(x, y)) { // O(lg*V)
                cjtos.unir(x, y); // O(lg*V)
                _ARM.push_back(a); coste += a.valor();
                aeropuertos--;
                if (_ARM.size() == g.V() - 1) break;
            }
        }
        coste += aeropuertos * costeAeropuerto;
    }

    Valor _coste() const {
        return coste;
    }
    int _aeropuertos() const {
        return aeropuertos;
    }
};

bool resuelveCaso() {

    // leemos la entrada
    int N, M, A;
    cin >> N >> M >> A;
    if (!cin)
        return false;

    // leer el resto del caso y resolverlo

    GrafoValorado<int> grafo(N);

    // Se añaden todas las aristas al grafo menos las que cueste más hacer camino que aeropuerto
    for (int i = 0; i < M; i++) {
        int x, y, c;
        cin >> x >> y >> c;
        if (c < A) {
            Arista<int> arista(x - 1, y - 1, c);
            grafo.ponArista(arista);
        }
    }

    ARM_Kruskal<int> ARM(grafo, A);

    cout << ARM._coste() << " " << ARM._aeropuertos() << "\n";

    return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

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
    // system("PAUSE");
#endif
    return 0;
}
