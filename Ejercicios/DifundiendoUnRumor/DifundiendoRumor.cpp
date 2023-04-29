/*
 * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificación fuera de esas etiquetas no será corregida.
 */

 /*@ <answer>
  *
  * Indicad el nombre completo y usuario del juez de quienes habéis hecho esta solución:
  * Estudiante 1: Pablo Ezquerro Moya - DA09
  * Estudiante 2:
  *
  *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include <queue>
#include <vector>
#include "Grafo.h"
using namespace std;


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

Para resolver el problema recorro todas las componentes conexas quedandome con la que tiene menor coste
e ir sumando asi los menores costes de todas estas componentes.

 Costes ->   resuelveCaso() -> O(N + M)
             Recorrido en profundidad -> O(N + M)
             El coste total del problema esta en el orden de O(N+M) siendo N el numero de personas
             y M las relaciones entre ellas.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>

class Rumor {
private:
    int costeAbs;
    vector<bool> visit;
    int dfs(Grafo const& G, int v, const vector<int> &C) {
        visit[v] = true;
        int coste = C[v];
        for (int w : G.ady(v))
            if (!visit[w]) {
                coste = min(dfs(G, w, C), coste);
            }
        return coste;
    }

public:
    Rumor(Grafo const& G, const vector<int> &C) : visit(G.V(), false), costeAbs(0) {
        for (int v = 0; v < G.V(); ++v) {
            if (!visit[v]) { 
                costeAbs += dfs(G, v, C);
            }
        }
    }

    int costeA() const {
        return costeAbs;
    }
};



bool resuelveCaso() {

    // leemos la entrada
    int N, M;
    cin >> N >> M;

    if (!cin)
        return false;

    // leer el resto del caso y resolverlo
    int auxA, auxB;
    int costeAbsoluto=0;
    vector<int> C;
    for (int i = 0; i < N; i++) {
        cin >> auxA;
        C.push_back(auxA);
    }

    Grafo grafo(N);
    for (int i = 0; i < M; i++) {
        cin >> auxA >> auxB;
        grafo.ponArista(auxA-1, auxB-1);
    }
    //PROGRAMAR SALIDA
    Rumor rumor(grafo, C);
    cout << rumor.costeA() << "\n";

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
