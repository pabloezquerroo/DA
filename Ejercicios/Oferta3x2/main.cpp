#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool resuelveCaso(){
    
    int N; cin >> N;
    if (!cin) return false;
    
    priority_queue<int, vector<int>, less<int>> cola;
    int l, ahorro=0;
    for (int i=0; i<N; i++){
        cin >> l;
        cola.push(l);
    }
    
    for (int i=1; i<=N; i++){
        if(i%3==0){
            ahorro += cola.top();
            cola.pop();
        }
        else{
            cola.pop();
        }
    }
    cout << ahorro << "\n";
    return true;
}

int main(){
    
    while(resuelveCaso());
    
    return 0;
}
