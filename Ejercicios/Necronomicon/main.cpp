#include <iostream>
using namespace std;

#include "Digrafo.h"

class Necronomicon{
private:
    
    std::vector<bool> visit; // visit[v] = ¿se ha alcanzado a v en el dfs?
    std::vector<bool> apilado; // apilado[v] = ¿está el vértice v en la pila?
    bool hayciclo;
 
    void dfs(Digrafo const& g, int v) {
        apilado[v] = true;
        visit[v] = true;
        for (int w : g.ady(v)) {
            if (!visit[w]) { // encontrado un nuevo vértice, seguimos
                dfs(g, w);
            } else if (apilado[w]) { // hemos detectado un ciclo
                // se recupera retrocediendo
                hayciclo = true;
            }
        }
        apilado[v] = false;
    }
    
public:
    Necronomicon(Digrafo const& g) : visit(g.V(),false),
    apilado(g.V(),false), hayciclo(false) {
        dfs(g, 0);
    }
            
    int tipoLlegada(int tam) const {
        // 0->NUNCA 1->SIEMPRE 2->A VECES
        if (hayciclo && visit[tam]){        // A VECES
            return 2;
        }else if (!hayciclo && visit[tam]){ // SIEMPRE
            return 1;
        }else{ // !visit[tam]               // NUNCA
            return 0;
        }
    }
};


struct instruccion{
    char tipo;
    int salto;
};

bool resuelveCaso(){
    int L;
    cin >> L;
    if (!cin) return 0;
    
    Digrafo grafo(L+1);
    instruccion ins;
    for (int i=0; i<L; i++){
        cin >> ins.tipo;
        if (ins.tipo=='J'){                 // CASO J
            cin >> ins.salto;
            grafo.ponArista(i, ins.salto-1);
        }else if(ins.tipo=='C'){            // CASO C
            cin >> ins.salto;
            grafo.ponArista(i, ins.salto-1);
            grafo.ponArista(i, i+1);
        }else{                              // CASO A
            grafo.ponArista(i, i+1);
        }
    }
    Necronomicon necro(grafo);
    int llegada = necro.tipoLlegada(L);
    if (llegada==2) cout << "A VECES\n";
    else if (llegada==1) cout << "SIEMPRE\n";
    else cout << "NUNCA\n";
    return true;
}

int main(){
    while(resuelveCaso());
    return 0;
}

/*
 3
 A
 A
 J 1
 
 5
 A
 J 4
 J 5
 C 3
 A
 
 4
 A
 A
 C 2
 A

 */
