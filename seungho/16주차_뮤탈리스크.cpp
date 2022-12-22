#include <iostream>
#include <cstring>
using namespace std;

int N;
int SCV[3] = { 0 };
int dp[61][61][61];

int dfs(int x, int y, int z) {
	if (x < 0) return dfs(0, y, z);
	if (y < 0) return dfs(x, 0, z);
	if (z < 0) return dfs(x, y, 0);

	if (x == 0 && y == 0 && z == 0) return 0;

	if (dp[x][y][z] != -1) return dp[x][y][z];

	dp[x][y][z] = 2134567890;
	dp[x][y][z] = min(dp[x][y][z], dfs(x - 9, y - 3, z - 1) + 1);
	dp[x][y][z] = min(dp[x][y][z], dfs(x - 9, y - 1, z - 3) + 1);
	dp[x][y][z] = min(dp[x][y][z], dfs(x - 3, y - 9, z - 1) + 1);
	dp[x][y][z] = min(dp[x][y][z], dfs(x - 3, y - 1, z - 9) + 1);
	dp[x][y][z] = min(dp[x][y][z], dfs(x - 1, y - 3, z - 9) + 1);
	dp[x][y][z] = min(dp[x][y][z], dfs(x - 1, y - 9, z - 3) + 1);
	return dp[x][y][z];
}

int main()
{
	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> SCV[i];
	}

	memset(dp, -1, sizeof(dp));

	cout << dfs(SCV[0], SCV[1], SCV[2]);

	return 0;
}
