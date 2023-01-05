#include <iostream>
#include <vector>
#define endl '\n'

using namespace std;

int n;
int arr[100001];
int dp[100001]; // index: 수열 인덱스, value: 최대 합
int answer;

void Input() {

    cin >> n;

    for ( int i = 0; i < n; i++ ) {
        cin >> arr[i];
    }
}

void FillDp() {

    answer = arr[0];
    dp[0] = arr[0];

    for ( int i = 1; i < n; i++) {
        dp[i] = max(dp[i-1] + dp[i], dp[i]);
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
