#include <iostream>
#define endl '\n'
using namespace std;

int N;
int podo[10002];
int dp[10001];

void Output() {
    cout << dp[N];
}

void FillDp() {

    dp[1] = podo[1];
    dp[2] = podo[1] + podo[2];

    for ( int i = 3; i <= N; i++ ) {
        // 현재 잔을 안마실 때, i-1잔을 안마실 때, i-2잔을 안마실 때
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
    FillDp();
    Output();

    return 0;
}
