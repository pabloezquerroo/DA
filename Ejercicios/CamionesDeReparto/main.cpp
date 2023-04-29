#include <iostream>
using namespace std;

#include "GrafoValorado.h"

struct consulta{
    int origen, destino, anchura;
};

class Camino{
private:
    
    std::vector<bool> visit; // visit[v] = ¿hay camino dirigido de s a v?
    bool camino;
    
    // visita los nodos alcanzables desde v respetando el umbral
    void dfs(GrafoValorado<int> const& G, int o, int d, int umbral) { //camino a true cuando llegue a d
        visit[o] = true;
        if (o==d) camino=true;
        for (auto a : G.ady(o)) {
            if (a.valor() >= umbral) {
                int w = a.otro(o);
                if (!visit[w])
                    dfs(G, w, d, umbral);
            }
        }
    }
    
public:
    
    Camino(GrafoValorado<int> const& g, consulta c) : visit(g.V(), false), camino(false) {
        dfs(g, c.origen-1, c.destino-1, c.anchura);
    }
    
    bool hayCamino(){
        return camino;;
    }
    
};

bool resuelveCaso(){
    int V;
    cin >> V;
    if (!cin) return 0;
    
    GrafoValorado<int> grafo(V);
    int E, v, w, valor;
    cin>>E;
    for(int i=0; i<E; i++){
        cin >> v >> w >> valor;
        Arista<int> arista(v-1, w-1, valor);
        grafo.ponArista(arista);
    }
    
    
    
    consulta c;
    int K;
    cin >> K;
    for (int i=0; i<K; i++){
        cin >> c.origen >> c.destino >> c.anchura;
        Camino cam(grafo, c);
        if (cam.hayCamino()) cout << "SI\n";
        else cout << "NO\n";
    }
    
    return true;
}

int main(){
    while (resuelveCaso());
    return 0;
}

