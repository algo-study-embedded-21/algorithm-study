#include <iostream>
using namespace std;

long long dp[101][101];

int main()
{
	int MAP[101][101];
	int N;
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> MAP[i][j];
		}
	}
	
	dp[1][1] = 1;

	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			for (int i = 1; i < y; i++) {
				if(MAP[i][x] == y-i) dp[y][x] += dp[i][x];
			}
			for (int j = 1; j < x; j++) {
				if (MAP[y][j] == x - j) dp[y][x] += dp[y][j];
			}
		}
	}

	cout << dp[N][N];

	return 0;
}
