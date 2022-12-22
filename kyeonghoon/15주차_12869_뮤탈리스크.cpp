#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

int dp[61][61][61]; // scv의 체력이 a,b,c 일 때 최소로 박살낼 수 있는 횟수
int scv[3], n;

int dfs(int a, int b, int c) {
	if (a < 0)return dfs(0, b, c);
	if (b < 0)return dfs(a, 0, c);
	if (c < 0)return dfs(a, b, 0);
	if (a == 0 && b == 0 && c == 0)return 0;
	if (dp[a][b][c] != -1)return dp[a][b][c];
	dp[a][b][c] = 1e9;
	dp[a][b][c] = min(dfs(a - 9, b - 3, c - 1) + 1, dp[a][b][c]);
	dp[a][b][c] = min(dfs(a - 9, b - 1, c - 3) + 1, dp[a][b][c]);
	dp[a][b][c] = min(dfs(a - 3, b - 9, c - 1) + 1, dp[a][b][c]);
	dp[a][b][c] = min(dfs(a - 3, b - 1, c - 9) + 1, dp[a][b][c]);
	dp[a][b][c] = min(dfs(a - 1, b - 3, c - 9) + 1, dp[a][b][c]);
	dp[a][b][c] = min(dfs(a - 1, b - 9, c - 3) + 1, dp[a][b][c]);

	return dp[a][b][c];
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> scv[i];
	}
	memset(dp, -1, sizeof(dp));
	cout << dfs(scv[0], scv[1], scv[2]);
}
