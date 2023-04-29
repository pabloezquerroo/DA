#include <iostream>
#include "vector"
using namespace std;
using Mapa = vector<string>;

class Ovejas {
private:
    int F, C; // tamaño del mapa
    vector<vector<bool>> visit; // visit[i][j] = se ha visitado el píxel <i,j>?
    int num; // número de ovejas blancas
    
    bool correcta(int i, int j) const {
        return 0 <= i && i < F && 0 <= j && j < C;
    }
    
    const vector<pair<int,int>> dirs = {{1,0},{0,1},{-1,0},{0,-1}, };
       
    void dfs(Mapa const& M, int i, int j) {
        visit[i][j] = true;
        for (auto d : dirs) {
            int ni = i + d.first, nj = j + d.second;
            if (correcta(ni,nj) && M[ni][nj] == '.' && !visit[ni][nj]) {
                dfs(M, ni, nj);
            }
        }
    }
    
public:
    Ovejas(Mapa const& M) : F(M.size()), C(M[0].size()),
                            visit(F, vector<bool>(C, false)), num(0) {
        for (int i = 0; i < F; ++i) {
            for (int j = 0; j < C; ++j) {
                if (!visit[i][j] && M[i][j] == '.') { // se recorre una nueva mancha
                    ++num;
                    dfs(M, i, j);
                }
            }
        }
    }
        
        int numero() const { return num-1; }
        
};


bool resuelveCaso() { // O(F*C)
    int C, F;
    cin >> C >> F; // número de filas y columnas
    if (!cin) return false;
    
    Mapa mapa(F);
    
    // leemos la imagen
    for (string & linea : mapa)
        cin >> linea;
    
    // la analizamos
    Ovejas ov(mapa);
    cout << ov.numero() << '\n';
    return true;
}

int main(int argc, const char * argv[]) {
    while (resuelveCaso());
    return 0;
}
