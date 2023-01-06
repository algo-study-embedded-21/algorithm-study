#include <iostream>
using namespace std;

int N, K;
long long dp[201][201] = { 0 };

int main()
{
	cin >> N >> K;

	// dp[n][k] = dp[0][k-1] + dp[1][k-1] + dp[2][k-1] + ... + dp[n][k-1]

	for (int i = 0; i <= N; i++) {
		dp[i][1] = 1;
	}

	for (int i = 0; i <= N; i++) {
		for (int j = 2; j <= K; j++) {
			for (int k = 0; k <= i; k++) {
				dp[i][j] += dp[k][j - 1];
				dp[i][j] %= 1000000000;
			}
		}
	}

	cout << dp[N][K] % 1000000000;

	return 0;
}
