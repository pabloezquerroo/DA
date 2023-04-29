#include <iostream>
#include "PriorityQueue.h"
#include "GrafoValorado.h"
#include "ConjuntosDisjuntos.h"

using namespace std;

template <typename Valor>
class ARM_Kruskal {
private:
    vector<Arista<Valor>> _ARM;
    Valor coste;
    long long int maxTiempo;
public:
    Valor costeARM() const {
        return coste;
    }
    vector<Arista<Valor>> const& ARM() const {
        return _ARM;
    }
    ARM_Kruskal(GrafoValorado<Valor> const& g) : coste(0), maxTiempo(-1) {
        PriorityQueue<Arista<Valor>> pq(g.aristas());
        ConjuntosDisjuntos cjtos(g.V());
        while (!pq.empty()) {
            auto a = pq.top(); pq.pop();
            int v = a.uno(), w = a.otro(v);
            if (!cjtos.unidos(v,w)) {
                cjtos.unir(v, w);
                _ARM.push_back(a); coste += a.valor();
                if (_ARM.size() == g.V() - 1){
                    maxTiempo = a.valor();
                    break;
                }
            }
        }
    }
    long long int tiempo(){
        return maxTiempo;
    }
};

void resuelveCaso(){
    int N, M;cin >> N >> M;
    int v, w, val;
    
    GrafoValorado<int> g(N);
    for (int i=0; i<M; i++){
        cin >> v >> w >> val;
        g.ponArista({v-1, w-1, val});
    }
    if(N>1){
        ARM_Kruskal<int> arm(g);
        if(arm.tiempo()>-1) cout << arm.tiempo() << "\n";
        else cout << "Imposible\n";
    }else cout << "0\n";
}

int main() {
    int casos; cin>>casos;
    for (int i=0; i<casos; i++){
        resuelveCaso();
    }
    return 0;
}
