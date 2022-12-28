#include<iostream>
#include<cstring>
using namespace std;

long long dp[100][100], map[100][100], n;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}
	dp[0][0] = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (map[i][j] == 0 || dp[i][j] == 0)continue;
			if (i + map[i][j] < n)dp[i + map[i][j]][j] += dp[i][j];
			if (j + map[i][j] < n)dp[i][j + map[i][j]] += dp[i][j];
		}
	}
	cout << dp[n - 1][n - 1];
}
