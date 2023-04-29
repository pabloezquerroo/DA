#include <iostream>
#include <queue>
#include "Digrafo.h"

using namespace std;

class Sumidero {
public:
	Sumidero(Digrafo const& g) : vSumidero(-1) {
		buscaSumidero(g);
	}
	int verticeSumidero() const {
		return vSumidero;
	}
private:
	int vSumidero;
	void buscaSumidero(Digrafo const& g) {
		Digrafo gInv = g.inverso();
		int i = 0;
		while (i < gInv.V() && vSumidero == -1) {
			if (gInv.ady(i).size() == gInv.V() - 1 && g.ady(i).size() == 0) vSumidero = i;
			i++;
		}
	}
};

bool resuelveCaso() {
	int V; cin >> V;
	if (!cin) return false;

	int A; cin >> A;
	Digrafo digrafo(V);
	int v, w;
	for (int i = 0; i < A; i++){
		cin >> v >> w;
		digrafo.ponArista(v, w);
	}

	Sumidero s(digrafo);
	if (s.verticeSumidero() != -1) cout << "SI " << s.verticeSumidero() << "\n";
	else cout << "NO\n";
	
	return true;
}


int main(){

	while (resuelveCaso());

	return 0;
}
