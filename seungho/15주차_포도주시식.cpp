#include <iostream>
using namespace std;

int wine[10002];
int dp[10002][3];

int main()
{
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		cin >> wine[i];
	}

	dp[1][0] = wine[1];
	dp[1][1] = wine[1];
	dp[2][0] = wine[2];
	dp[2][1] = wine[1] + wine[2];
	dp[2][2] = wine[1];

	for (int i = 2; i <= n+1; i++) {
		dp[i][0] = max(dp[i - 2][0], dp[i - 2][1]) + wine[i];
		dp[i][1] = dp[i - 2][2] + wine[i-1] + wine[i];
		dp[i][2] = max(max(dp[i - 1][0], dp[i - 1][1]), dp[i - 1][2]);
	}

	int a = 2;
	cout << dp[n + 1][2];

	return 0;
}
