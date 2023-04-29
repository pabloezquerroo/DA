#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#include "DigrafoValorado.h"
#include "IndexPQ.h"

template <typename Valor>
class Dijkstra {
private:
    const Valor INF = numeric_limits<Valor>::max();
    int origen;
    vector<Valor> dist;
    vector<AristaDirigida<Valor>> ulti;
    IndexPQ<Valor> pq;
    
    void relajar(AristaDirigida<Valor> a){
        int v= a.desde(), w=a.hasta();
        if (dist[w] > dist[v] + a.valor()){
            dist[w] = dist[v] + a.valor(); ulti[w] = a;
            pq.update(w, dist[w]);
        }
    }
    
public:
    Dijkstra(DigrafoValorado<Valor> const& g) : origen(0),
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
    Valor distancia(int v) const {  return dist[v]; }
};


bool resuelveCaso(){
    int N;
    cin >> N;
    if (N == 0) return false;
    
    vector<int> tCarga;
    int aux;
    for (int i=0; i<N; i++){
        cin >> aux;
        tCarga.push_back(aux);
    }
        
    int M;
    cin >> M;
    
    DigrafoValorado<int> digrafo(N);
    int x, y, v;
    for (int i=0; i<M; i++){
        cin >> x >> y >> v;
        digrafo.ponArista({x-1, y-1, v+tCarga[x-1]});
    }
    
    Dijkstra<int> dijkstra(digrafo);
    if (dijkstra.hayCamino(N-1)){
        int tiempo=dijkstra.distancia(N-1) + tCarga[N-1];
        cout << tiempo << "\n";
    }else{
        cout << "IMPOSIBLE\n";
    }
    
    return true;
}

int main(){
    while (resuelveCaso());
    return 0;
}
