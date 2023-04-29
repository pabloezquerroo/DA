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
using namespace std;

#include "Matriz.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 Escribe en particular la especificación y definición de la recurrencia
 en la que te has basado para resolver el problema por programación dinámica.


 i = festivales
 j = presupuesto

 Mi solución está hecha de manera muy similar al problema de la mochila de la 
 semana 11. Creo una matriz en la cual voy almacenando los grupos a los que puede
 asistir en función del presupuesto que disponga. Para saber si en una casilla
 podemos añadir los grupos del festival i, consulto el precio para ver si es asumible.
 Si es así, entonces examino cual es la mejor de las dos opciones posibles mediante recursión que son 
 las siguientes:
 RECURSION 1:
    Descartar el festival i y probar con los demas;
    elegirGrupos(festivales, i - 1, j, matrizGrupos)
 RECURSION 2:
    Ir al festival i, y por consiguiente restarle al presupuesto su precio y
    añadir el número de grupos;
    elegirGrupos(festivales, i - 1, j - festivales[i - 1].precio, matrizGrupos) + festivales[i - 1].grupos)
 
 En el caso de que el precio no sea asumible se da otro caso de recursion;
 RECURSION 3:
    Descartar el festival i;
    elegirGrupos(festivales, i-1 , j, matrizGrupos)

Casos básicos:
elegirGrupos(0,j) = 0   0<=j<=P
elegirGrupos(i,0) = 0   0<=i<=N

LLamada inicial: elegirGrupos(N,P)

 @ </answer> */

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>

typedef struct {
    int grupos;
    int precio;
}festival;

int elegirGrupos(vector<festival> const& festivales, int i, int j, Matriz<int>& matrizGrupos) {
    if (matrizGrupos[i][j] != -1)
        return matrizGrupos[i][j];
    if (i == 0 || j == 0) matrizGrupos[i][j] = 0;
    else if (festivales[i - 1].precio>j)
        matrizGrupos[i][j] = elegirGrupos(festivales, i-1 , j, matrizGrupos);
    else
        matrizGrupos[i][j] = max(elegirGrupos(festivales, i - 1, j, matrizGrupos),
            elegirGrupos(festivales, i - 1, j - festivales[i - 1].precio, matrizGrupos)
            + festivales[i - 1].grupos);

    return matrizGrupos[i][j];
}

bool resuelveCaso() {

    int P, N;
    cin >> P >> N;  // presupuesto y número de festivales

    if (!cin)
        return false;

    // leer el resto del caso y resolverlo

    Matriz<int> matrizGrupos(N + 1, P + 1, -1);
    vector<festival> festivales(N);

    for (int i = 0; i < N; i++) {
        cin >> festivales[i].grupos >> festivales[i].precio;
    }

    elegirGrupos(festivales, N, P, matrizGrupos);

    cout << matrizGrupos[N][P] << "\n";

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
