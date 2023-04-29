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
#include <limits>
using namespace std;

#include "DigrafoValorado.h"
#include "IndexPQ.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 Para este problema, como hay que buscar el camino mínimo desde muchas celdas a una,
 genero el grafo inverso. Esto me permite tener el camino minimo desde la salida hasta
 todos las celdas desde donde salen ratones. De esta manera puedo contar todos los
 caminos que tienen un coste menor que el máximo que nos dan utilizando el vector dist.

 COSTES:
 El coste de insertar todas las aristas en el grafo en O(P) 
 El algoritmo de dijkstra tiene un coste de O(A log V) siendo A el número de aristas(caminos)
 y V el número de vértices(celdas).
 El coste de consultar las distancias a la salida es O(V) siendo v el número de vertices(celdas)

 Por lo tanto el coste total del problema es del orden de O(A log V + V + P)


 @ </answer> */

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>


template <typename Valor>
class Dijkstra {
private:
    const Valor INF = numeric_limits<Valor>::max();
    int origen;
    vector<Valor> dist;
    vector<AristaDirigida<Valor>> ulti;
    IndexPQ<Valor> pq;

    void relajar(AristaDirigida<Valor> a) {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor(); ulti[w] = a;
            pq.update(w, dist[w]);
        }
    }

public:
    Dijkstra(DigrafoValorado<Valor> const& g, int orig) : origen(orig),
        dist(g.V(), INF), ulti(g.V()), pq(g.V()) {
        dist[origen] = 0;
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }

    int numRatones(int t) { //t es el tiempo en el que se para el cronómetro
        int num = 0;
        for (int i = 0; i < dist.size(); i++) {
            if (dist[i] <= t) num++;
        }
        return num - 1;
    }

    bool hayCamino(int v) const { return dist[v] != INF; }
    Valor distancia(int v) const { return dist[v]; }
};

bool resuelveCaso() {

    // leemos la entrada
    int N, S, T, P;
    cin >> N >> S >> T >> P;

    if (!cin)
        return false;

    // leer el resto del caso y resolverlo

    DigrafoValorado<int> digrafo(N);
    int a, b, t;
    for (int i = 0; i < P; i++) {
        cin >> a >> b >> t;
        digrafo.ponArista({ b - 1, a - 1, t }); //grafo inverso
    }

    Dijkstra<int> dijkstra(digrafo, S - 1);
    cout << dijkstra.numRatones(T) << "\n";

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
