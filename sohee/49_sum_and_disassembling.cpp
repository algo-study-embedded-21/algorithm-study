/*
	N = 5, K = 3
	() + 5 = 5
	() + 4 = 5
	() + 3 = 5
	() + 2 = 5
	() + 1 = 5
	() + 0 = 5
	-> () = dp[2][0] ~ dp[2][5]
*/

#include <iostream>
using namespace std;

int n, k;
// k, n
int dp[201][201];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> k;
	for (int i = 0; i <= n; i++) {
		dp[1][i] = 1;
	}
	for (int i = 0; i <= k; i++) {
		dp[i][0] = 1;
		dp[i][1] = i;
	}

	// dp[k][n] = dp[k-1][0] + ... + dp[k-1][n]
	for (int i = 2; i <= k; i++) {
		for (int j = 2; j <= n; j++) {
			for (int d = 0; d <= j; d++) {
				dp[i][j] += dp[i - 1][d];
				dp[i][j] %= 1000000000;
			}
		}
	}

	cout << dp[k][n];

	return 0;
}