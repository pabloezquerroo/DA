#include <iostream>
using namespace std;

#include <queue>

typedef struct {
	bool periodica;
	int ini, fin, per;
}tTarea;

struct Comparator {
	bool operator()(tTarea const& a, tTarea const& b) {
		return b.ini < a.ini;
	}
};

bool resuelveCaso() {
	int N;
	cin >> N;
	if (!cin)return false;
	
	priority_queue<tTarea, vector<tTarea>, Comparator> cola;
	int M, T;
	cin >> M >> T;

	int ini, fin, per;
	for (int i = 0; i < N; i++) {
		cin >> ini >> fin;
		cola.push({ false, ini, fin, 0 });
	}
	for (int i = 0; i < M; i++) {
		cin >> ini >> fin >> per;
		cola.push({ true, ini, fin, per });
	}

	bool conflicto = false;
	while (!cola.empty() && !conflicto && cola.top().ini<T) {
		tTarea aux = cola.top();
		cola.pop();
		if (aux.fin > cola.top().ini && cola.top().ini < T) {
			conflicto = true;
		}
		else {
			if (aux.periodica) {
				cola.push({ true, aux.ini + aux.per, aux.fin + aux.per, aux.per });
			}
		}
	}
	if (conflicto) cout << "SI\n";
	else cout << "NO\n";

	return true;
}

int main() {

	while (resuelveCaso());

	return 0;
}