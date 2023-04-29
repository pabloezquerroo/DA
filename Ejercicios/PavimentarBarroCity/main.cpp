#include <iostream>
#include <queue>
#include "GrafoValorado.h"
#include "ConjuntosDisjuntos.h"
#include "PriorityQueue.h"
using namespace std;

template <typename Valor>
class ARM_Kruskal {
private:
    std::vector<Arista<Valor>> _ARM;
    Valor coste;

public:
    Valor costeARM() const {
        return coste;
    }
    
    vector<Arista<Valor>> const& ARM() const {
        return _ARM;
    }
    
    ARM_Kruskal(GrafoValorado<Valor> const& g) : coste(0) {
        PriorityQueue<Arista<Valor>> pq(g.aristas());
        ConjuntosDisjuntos cjtos(g.V());
        while (!pq.empty()) {
            auto a = pq.top(); pq.pop();
            int v = a.uno(), w = a.otro(v);
            if (!cjtos.unidos(v,w)) {
                cjtos.unir(v, w);
                _ARM.push_back(a); coste += a.valor();
                if (_ARM.size() == g.V() - 1) break;
            }
        }
    }
    
};

bool resuelveCaso(){
    int V, A;
    cin >> V;
    if (!cin)return false;
    
    GrafoValorado<int> g(V);
    int v,w,val;
    cin >> A;
    for (int i=0; i<A; i++){
        cin >> v >> w >> val;
        g.ponArista({v-1,w-1,val});
    }
    ARM_Kruskal<int> arbol(g);
    if (arbol.ARM().size()==V-1){
        cout << "\n" << arbol.costeARM();
    }else{
        cout << "\nImposible";
    }
    
    
    return true;
}

int main(int argc, const char * argv[]) {
    while (resuelveCaso());
    return 0;
}

/*
 5
 7
 1 2 7
 1 3 6
 3 2 1
 1 4 10
 3 4 15
 3 5 3
 4 5 12
 */
