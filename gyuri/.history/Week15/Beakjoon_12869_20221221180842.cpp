#include <iostream>
#define endl '\n'
using namespace std;

int N;
int podo[10002];
int dp[10001];

void Output() {
    cout << dp[i];
}

void FillDp() {

    dp[1] = podo[1];

    dp[2] = podo[1] + podo[2];

    for ( int i = 3; i <= N; i++ ) {
        dp[i] = max(dp[i-1], max(dp[i-2] + podo[i], dp[i-3] + podo[i-1] + podo[i]));
    }
}

void Input() {

    cin >> N;

    for ( int i = 1; i <= N; i++ ) {
        cin >> podo[i];
    }
}

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    Input();

    return 0;
}
