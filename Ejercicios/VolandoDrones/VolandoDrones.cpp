#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool resuelveCaso() {
	int N; cin >> N;
	if (!cin) return false;

	int A, B;
	cin >> A >> B;
	
	int aux;
	priority_queue<int, vector<int>> colaA; //potencia 9V
	for (int i = 0; i < A; i++) {
		cin >> aux;
		colaA.push(aux);
	}
	priority_queue<int, vector<int>> colaB;
	for (int i = 0; i < B; i++) { //potencia 1,5V
		cin >> aux;
		colaB.push(aux);
	}

	int suma=0;
	vector<int> colaAaux;
	vector<int> colaBaux;

	while (!colaA.empty() && !colaB.empty()) {
		for (int i = 0; i < N; i++) {
			if (!colaA.empty() && !colaB.empty()) {
				if (colaA.top() > colaB.top()) {
					suma += colaB.top();
					colaAaux.push_back(colaA.top() - colaB.top());
					colaB.pop();
					colaA.pop();
				}
				else {
					suma += colaA.top();
					colaBaux.push_back(colaB.top() - colaA.top());
					colaA.pop();
					colaB.pop();
				}
			}
		}
		for (int i = colaAaux.size()-1; i >= 0; i--) {
			colaA.push(colaAaux[i]);
		}
		for (int i = colaBaux.size() - 1; i >= 0; i--) {
			colaB.push(colaBaux[i]);
		}
		colaAaux.clear();
		colaBaux.clear();
		if (suma>0) cout << suma << " ";
		suma = 0;
	}

	return true;
}

int main() {

	while (resuelveCaso());

	return 0;
}