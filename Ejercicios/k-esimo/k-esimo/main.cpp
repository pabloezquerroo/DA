#include <iostream>
using namespace std;

#include "TreeSet_AVL.h"

bool resuelveCaso(){
    int nValor;
    cin >> nValor;
    if (nValor==0)return false;
    long long int valor, nk ,k;
    Set<long long int> arbol;
    for (int i =0; i<nValor; i++){
        cin >> valor;
        arbol.insert(valor);
    }
    cin >> nk;
    for (int i=0; i<nk; i++){
        cin >> k;
        try{
            long long int elem = arbol.kesimo(k);
            cout<<elem<<"\n";
        }catch(exception){
            cout << "??\n";
        }
    }
    cout << "---\n";

    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}
    
