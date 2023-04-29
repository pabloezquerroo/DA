#include <iostream>
#include <vector>
#include <queue>
using namespace std;


bool resuelveCaso(){
    int N;
    cin >> N;
    if (!cin || N==0){
        return false;
    }
    
    long long int s, gorras = 0;
    priority_queue<long long int, vector<long long int>, greater<long long int>> cola, cola_aux; //Más pequeños mas prioritarios
    vector<int> v;
    for (int i=0; i<N; i++){
        cin >> s;
        cola.push(s);
    }
    long long int e1, e2;
    while(cola.size()>=2){
        e1= cola.top(); cola.pop();
        e2= cola.top(); cola.pop();
        cola.push(e1+e2);
        gorras+= e1+e2;
    }
    cout << gorras << "\n";
    return true;
}

int main(int argc, const char * argv[]) {
    while (resuelveCaso());
    return 0;
}

