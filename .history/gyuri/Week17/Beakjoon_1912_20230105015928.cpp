#include <iostream>
#include <vector>
#define endl '\n'

using namespace std;

int n;
int dp[100001]; // index: 수열 인덱스, value: 최대 합

void Input() {

    cin >> n;

    for ( int i = 0; i < n; i++ ) {
        cin >> dp[i];
    }
}

void FillDp() {

    int answer = dp[0];

    for ( int i = 1; i < n; i++) {
        // 이전까지의 최대합이 음수이면 넘김
        if ( dp[i-1] < 0 ) continue;
        // 이전 최대합에 현재 값을 더했을 때 음수이면 넘김
        if ( dp[i-1] + dp[i] ) continue;
        
        dp[i] += dp[i-1];
        answer = max(answer, dp[i]);
    }
}

void Output() {

    cout << answer;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    Input();
    FillDp();
    Output();
    return 0;
}
