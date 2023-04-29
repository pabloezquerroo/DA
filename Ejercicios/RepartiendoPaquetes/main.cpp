#include <iostream>
#include "DigrafoValorado.h"
#include <queue>
#include "IndexPQ.h"
using namespace std;

template <typename Valor>
class Dijkstra {
private:
    const Valor INF = std::numeric_limits<Valor>::max();
    int origen;
    std::vector<Valor> dist;
    std::vector<AristaDirigida<Valor>> ulti;
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
    
    bool hayCamino(int v) const { return dist[v] != INF; }
    
    Valor distancia(int v) const { return dist[v]; }
    

    deque<Valor> camino(int v) const {
        deque<Valor> cam;
        // recuperamos el camino retrocediendo
        AristaDirigida<Valor> a;
        for (a = ulti[v]; a.desde() != origen; a = ulti[a.desde()])
            cam.push_front(a);
        cam.push_front(a);
        return cam;
    }
};

bool resuelveCaso(){
    int N; cin >> N;
    if (!cin) return false;
    
    DigrafoValorado<int> digrafoIda(N);
    int v, w, val;
    int C; cin >> C;
    for (int i=0; i<C; i++){
        cin >> v >> w >> val;
        digrafoIda.ponArista({v-1, w-1, val});
    }

    int o; cin >> o;
    int P; cin >> P;
    vector<int> dest(P);
    for (int i=0; i<P; i++){
        cin >> dest[i];
    }
    
    Dijkstra<int> dijkIda(digrafoIda, o-1);
    bool llega=true;
    int sum=0;
    for (int i=0; i<P; i++){
        if (dijkIda.hayCamino(dest[i]-1)) sum+=dijkIda.distancia(dest[i]-1);
        else llega = false;
    }
  
    DigrafoValorado<int> digrafoVuelta(N);
    digrafoVuelta=digrafoIda.inverso();
    
    Dijkstra<int> dijkVuelta(digrafoVuelta, o-1);
    for (int i=0; i<P; i++){
        if (dijkVuelta.hayCamino(dest[i]-1)) sum+=dijkVuelta.distancia(dest[i]-1);
        else llega = false;
    }
    
    if (llega){
        cout << sum << "\n";
    }else{
        cout << "Imposible\n";
    }
    
    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}
