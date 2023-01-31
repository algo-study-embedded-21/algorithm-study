/*
dp[i][j] = i, j번째 칸에서 얻을 수 있는 최대 사탕 수
dp[i-1][j], dp[i][j-1], dp[i-1][j-1] 중 최대값 + map[i][j]
*/

#include <iostream>
using namespace std;

int n, m;
int map[1000][1000];
long long dp[1000][1000];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}
	dp[0][0] = map[0][0];
	for (int i = 1; i < n; i++) {
		dp[i][0] = dp[i - 1][0] + map[i][0];
	}

	for (int i = 1; i < m; i++) {
		dp[0][i] = dp[0][i - 1] + map[0][i];
	}

	for (int i = 1; i < n; i++) {
		for (int j = 1; j < m; j++) {
			dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
			dp[i][j] = max(dp[i][j], dp[i - 1][j - 1]);
			dp[i][j] += map[i][j];
		}
	}

	cout << dp[n - 1][m - 1];

	return 0;
}