#include <iostream>
#include <vector>
#define endl '\n'

using namespace std;

int n;
int arr[100001];
int dp[100001]; // index: 수열 인덱스, value: 최대 합
int answer = 213456789;

void Input() {

    cin >> n;

    for ( int i = 0; i < n; i++ ) {
        cin >> arr[i];
    }
}

void FillDp() {

    dp[0] = 0;

    for ( int i = 1; i < n; i++) {
        // 이전까지의 최대합이 양수이고, 현재의 값을 더한 최대합이 양수이면 계속 더해줌
        if ( dp[i-1] > 0 && dp[i] + dp[i-1] > 0) {
            dp[i] += dp[i-1];
        }

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
    Output();
    return 0;
}
