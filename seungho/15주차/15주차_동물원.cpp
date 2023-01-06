#include <iostream>
using namespace std;

int N;

long long dp[100000][3];

int main()
{
	cin >> N;

	dp[0][0] = 1;
	dp[0][1] = 1;
	dp[0][2] = 1;

	for (int i = 1; i < N; i++) {
		dp[i][0] = (dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][2]) % 9901;
		dp[i][1] = (dp[i - 1][0] + dp[i - 1][2]) % 9901;
		dp[i][2] = (dp[i - 1][0] + dp[i - 1][1]) % 9901;
	}
	long long ans = 0;

	for (int i = 0; i < 3; i++) {
		ans += dp[N-1][i];
	}

	cout << ans % 9901;

	return 0;
}
