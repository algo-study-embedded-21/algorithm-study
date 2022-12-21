#include <iostream>
#define endl '\n'
using namespace std;

int N;
int podo[10001];

void Output(){}

void Input(){

    cin >> N;
    
    for ( int i = 0; i < N; i++ ) {
        cin >> podo[i];
    }
}

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    return 0;
}