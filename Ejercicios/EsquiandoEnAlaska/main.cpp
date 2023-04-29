#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
using namespace std;

bool resuelveCaso(){
    int N; cin >> N;
    if (N==0)return false;

    priority_queue<int, vector<int>, greater<int>> alturas;
    priority_queue<int, vector<int>, greater<int>> esqui;
    int aux;
    for (int i=0; i<N; i++){
        cin >> aux;
        alturas.push(aux);
    }
    for (int i=0; i<N; i++){
        cin >> aux;
        esqui.push(aux);
    }

    int suma = 0;
    for (int i=0; i<N; i++){
        suma+=abs(alturas.top() - esqui.top());
        alturas.pop();
        esqui.pop();
    }

    cout << suma << "\n";
    return true;
}

int main() {
    while(resuelveCaso());
    return 0;
}
