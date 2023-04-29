#include <iostream>
using namespace std;

#include <queue>


typedef struct {
	string nombre;
	int gravedad, orden;
}tEvento;

struct Comparator {
	bool operator()(tEvento const& a, tEvento const& b) {
		return a.gravedad < b.gravedad || (a.gravedad == b.gravedad && a.orden > b.orden);
	}
};

bool resuelveCaso() {
	int n;
	cin >> n;
	if (n <= 0) return false;
	priority_queue<tEvento, vector<tEvento>, Comparator> cola;
	string tipo, nombre;
	int gravedad;
	for (int i = 0; i < n; i++) {
		cin >> tipo;
		if (tipo == "I") {
			cin >> nombre >> gravedad;
			cola.push({nombre, gravedad, i});
		}
		else {
			cout << cola.top().nombre << "\n";
			cola.pop();
		}
	}
	cout << "---\n";
	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}