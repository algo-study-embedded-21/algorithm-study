#include <iostream>
#define endl '\n'
using namespace std;

int N;
int dp[10001];

void Output(){}

void Input(){

    cin >> N;

    for ( int i = 0; i < N; i++ ) {
        cin >> dp[i];
    }
}

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    Input();

    return 0;
}
