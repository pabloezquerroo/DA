/*
 * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificación fuera de esas etiquetas no será corregida.
 */

 /*@ <answer>
  *
  * Indicad el nombre completo y usuario del juez de quienes habéis hecho esta solución:
  * Estudiante 1: Pablo Ezquerro Moya (DA09)
  * Estudiante 2:
  *
  *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <limits>
using namespace std;


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 El problema lo resuelvo utilizando una estrategia voraz. De modo que asigno 
 a los menores resultados de los rivales, los mayores resultados de los 
 Broncos. De esta manera maximizo la puntuación, ya que los partidos en los 
 que los Broncos meten más puntos serán los que menos puntos reciban.
 Recorro ambos vectores de resultados ya ordenados comparando sus resultados
 y sumando a la variable puntos en el caso de que sea victoria de los Broncos.

 COSTE:
    ordenacionde los vectores O(2 N lon N)
    recorrer vectores para su comprobación O(N)
    Coste total es del orden de O(N)

 Escribe también una demostración que justifique que tu solución encuentra
 siempre soluciones óptimas.

 r[1..N] vector de puntos de los rivales ordenado ascendentemente
 b[1..N] vector de puntos de los Broncos ordenado descendentemente

 Caso 1: b[i] < r[i] => se le suma a la máxima puntuacion 0.
 
 Caso 2: b[i] > r[i] => se le suma a la máxima puntuacion b[i]-r[i].


 @ </answer> */

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>

int maximizarPts(vector<int> r, vector<int> b, int N) {
    int puntos=0;
    
    for (int i = 0; i < N; i++) {
        if (r[i] < b[i]) {
            puntos += (b[i] - r[i]);
        }
    }

    return puntos;
}


bool resuelveCaso() {

    int N;
    cin >> N;  // número de partidos

    if (N == 0)
        return false;

    // leer el resto del caso y resolverlo

    vector<int> r;
    r.resize(N);
    vector<int> b;
    b.resize(N);
    
    for (int i = 0; i < N; i++){
        cin >> r[i];
    }
    for (int i = 0; i < N; i++) {
        cin >> b[i];
    }
    sort(r.begin(), r.end(), less<int>());
    sort(b.begin(), b.end(), greater<int>());

    cout << maximizarPts(r, b, N) <<"\n";
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
