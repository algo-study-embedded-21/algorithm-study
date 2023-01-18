#include <iostream>
using namespace std;

int N, M;
int MAP[1001][1001];
int dp[1001][1001];

int dfs(int i, int j) {
	if (i < 1) return dp[1][j];
	if (j < 1) return dp[i][1];
	if (i == 1 && j == 1) return dp[1][1];

	if (dp[i][j] >= 0) return dp[i][j];
	dp[i][j] = max(dp[i][j], dfs(i - 1, j) + MAP[i][j]);
	dp[i][j] = max(dp[i][j], dfs(i, j - 1) + MAP[i][j]);
	dp[i][j] = max(dp[i][j], dfs(i - 1, j - 1) + MAP[i][j]);

	return dp[i][j];
}

int main() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> MAP[i][j];
			dp[i][j] = -1;
		}
	}

	dp[1][1] = MAP[1][1];
	for (int i = 2; i <= N; i++) {
		dp[i][1] = dp[i - 1][1] + MAP[i][1];
	}
	for (int j = 2; j <= M; j++) {
		dp[1][j] = dp[1][j - 1] + MAP[1][j];
	}

	cout << dfs(N, M);

	return 0;
}
