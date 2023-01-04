#include <iostream>
using namespace std;

int dp[1001];

int main()
{
	int N;
	cin >> N;
	int P[1001];

	for (int i = 1; i <= N; i++) {
		cin >> P[i];
		dp[i] = P[i];
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= i; j++) {
			dp[i] = max(dp[i], dp[j] + dp[i - j]);
		}
	}

	cout << dp[N];

	return 0;
}
