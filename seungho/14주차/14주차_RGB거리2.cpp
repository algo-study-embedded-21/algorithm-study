#include <iostream>
using namespace std;

int N;
int cost[1000][3];

int main()
{
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> cost[i][j];
		}
	}

	int ans = 2134567890;

	// 첫번째 집 c
	for (int c = 0; c < 3; c++) {
		int dp[1000][3];
		for (int i = 0; i < 3; i++) {
			dp[0][i] = cost[0][i];
		}
		for (int i = 0; i < 3; i++) {
			if (i == c) {
				dp[1][i] = 2134567890;
				continue;
			}
			dp[1][i] = dp[0][c] + cost[1][i];
		}

		for (int i = 2; i < N; i++) {
			dp[i][0] = min(dp[i - 1][1], dp[i - 1][2]) + cost[i][0];
			dp[i][1] = min(dp[i - 1][0], dp[i - 1][2]) + cost[i][1];
			dp[i][2] = min(dp[i - 1][0], dp[i - 1][1]) + cost[i][2];
		}
		for (int i = 0; i < 3; i++) {
			if (i == c) continue;
			ans = min(ans, dp[N - 1][i]);
		}
	}

	cout << ans;

	return 0;
}
