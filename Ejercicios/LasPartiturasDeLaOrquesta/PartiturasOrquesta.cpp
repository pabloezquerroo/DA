/*
 * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificación fuera de esas etiquetas no será corregida.
 */

 /*@ <answer>
  *
  * Indicad el nombre completo y usuario del juez de quienes habéis hecho esta solución:
  * Estudiante 1: Pablo Ezquerro Moya -> DA09
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

Mi solucion se basa en el uso de una cola de prioridad y una estructura que almacena la informacion de un instrumento, es decir, 
el número ed musicos que lo tocan y el numero de partituras paa dicho instrumento. En la cola de prioridad decimos que el intrumento más
prioritario es aquel cuya division entre los músicos y las partituras es mayor. Cuando disponemos de una nueva partitura extraemos el 
instrumento más prioritario, le añadimos una partitura, y lo volvemos a insertar en su posición.

COSTES -> push y pop tienen coste O(log N)
          top tiene coste O(1)
          En esta implementación tenemos dos bucles:
                1º: Hacemos push N veces -> O(N log N)
                2º: Hacemos top, pop y push P-N veces. P-N lo llamaré M -> O(M log N)
          El coste total del algoritmo es  O(N log N) +  O(M log N)


 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>

typedef struct {
    int musicos;
    int partituras;
}tInstrumento;

struct Comparator{
    bool operator()(tInstrumento const& a, tInstrumento const& b) {
        int divB, divA;
        if (b.musicos % b.partituras != 0) {
            divB = (b.musicos / b.partituras) + 1;
        }
        else {
            divB = b.musicos / b.partituras;
        }
        if (a.musicos % a.partituras != 0) {
            divA = (a.musicos / a.partituras) + 1;
        }
        else {
            divA = a.musicos / a.partituras;
        }
        return divB>divA;
    }
};


bool resuelveCaso() {

    // leemos la entrada
    int P, N;
    cin >> P >> N;

    if (!cin)
        return false;

    // leer el resto del caso y resolverlo


    priority_queue<tInstrumento, vector<tInstrumento>, Comparator> cola;
    int m; //musicos por instrumento
    for (int i = 0; i < N; i++) {
        cin >> m;
        cola.push({ m, 1 });
    }

    int partiturasRestantes = P - N;
    for (int i = partiturasRestantes; i > 0; i--) {
        tInstrumento aux = cola.top();
        cola.pop();
        aux.partituras++;
        cola.push(aux);
    }

    tInstrumento sol = cola.top();

    if (sol.musicos % sol.partituras == 0) {
        cout << sol.musicos / sol.partituras << "\n";
    }
    else {
        cout << (sol.musicos / sol.partituras)+1 << "\n";
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
