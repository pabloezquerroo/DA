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
#include <string>
using namespace std;

#include "Matriz.h"


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución (tanto en
 tiempo como en espacio), en función del tamaño del problema.

 Escribe en particular la especificación y definición de la recurrencia
 en la que te has basado para resolver el problema por programación dinámica.

 Este problema lo resuelvo mediante memoria dinámica. Creo una matriz en la
 cual la fila representa la primera palabra y la columna la segunda. En ella
 voy almacenando el tamaño de la subsecuencia mas larga posible para i letras
 de la palabra X con j letras de la palabra Y.
 Así sabemos que en la ultima posicion de la matriz estará el maximo tamaño.
 Para reconstruir la palabra es rehacer los pasos:
 Si las letras coinciden se añaden a la solucion y se sube una casilla
 de la matriz en diagonal. Si no coinciden las letras entonces iremos arriba
 o a la izquierda en funcion a donde el tamaño se igual(con preferencia de ir arriba
 tal y como esta codificado).

 En mi caso lo he resuelto sin recurrencia con unb coste en espacio y tiempo de O(X.size() * Y.size())



 @ </answer> */

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>

string subsecuencia(string X, string Y) {
    int sizeX = X.size(), sizeY = Y.size();
    Matriz<int> matriz(sizeX + 1, sizeY + 1, 0);
    for (int i = 1; i <= sizeX; i++) {
        for (int j = 1; j <= sizeY; j++) {
            if (X[i - 1] == Y[j - 1]) {
                matriz[i][j] = matriz[i - 1][j - 1] + 1;
            }
            else {
                matriz[i][j] = max(matriz[i - 1][j], matriz[i][j - 1]);
            }
        }
    }
    int tamSubsecuencia = matriz[sizeX][sizeY];
    string subsecuencia="";
    while (tamSubsecuencia > 0) {
        if (X[sizeX - 1] == Y[sizeY - 1]) {
            subsecuencia += X[sizeX - 1];
            tamSubsecuencia--;
            sizeX--;
            sizeY--;

        }
        else {
            if (matriz[sizeX][sizeY] == matriz[sizeX][sizeY - 1]) {
                sizeY--;
            }
            else {
                sizeX--;
            }
        }
    }
    reverse(subsecuencia.begin(), subsecuencia.end());
    return subsecuencia;
}

bool resuelveCaso() {

    // leemos la entrada
    string X, Y;
    cin >> X >> Y;

    if (!cin)
        return false;


    // resolver el caso

    cout << subsecuencia(X, Y) << "\n";


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
