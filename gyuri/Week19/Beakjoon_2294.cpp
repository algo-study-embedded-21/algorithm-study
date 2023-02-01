#include <iostream>
#define endl '\n'
#define MAX 213456789

using namespace std;

int n, k;
int coins[101];
int dp[10001];
int cnt, remain;
int result;

// dp[A] = V
// V : A원을 만들기 위한 동전의 최소 개수

void Input() {
    cin >> n >> k;

    for (int i = 0; i < n; i++) {
        cin >> coins[i];
        dp[coins[i]] = 1;
    }
}

void FillDp() {

    for (int i = 0; i <= k; i++) {
        if (dp[i] != 0) continue;
        dp[i] = MAX;
    }

    for (int i = 0; i < n; i++) {
        if (k >= coins[i]) {
            for (int j = coins[i]; j <= k; j++) {
                dp[j] = min(dp[j - coins[i]] + 1, dp[j]);
            }
        }
    }
}

void Output() {

    //for (int i = 0; i <= k; i++) {
    //    cout << dp[i] << " ";
    //}
    //cout << endl;

    result = (dp[k] == MAX) ? -1 : dp[k];
    cout << result;
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