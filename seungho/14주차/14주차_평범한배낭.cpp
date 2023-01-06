#include <iostream>
using namespace std;

int N, K;
int items[101][2] = { 0 };
long long dp[101][100000] = { 0 };

int main()
{
	cin >> N >> K;

	for (int i = 1; i <= N; i++) {
		int W, V;
		cin >> items[i][0] >> items[i][1];
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 0; j <= K; j++) {
			if (items[i][0] > j) dp[i][j] = dp[i - 1][j];
			else {
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - items[i][0]] + items[i][1]);
			}
		}
	}

	cout << dp[N][K];

	return 0;
}
