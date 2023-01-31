#include <iostream>
using namespace std;

int main()
{
	int N;
	cin >> N;

	int MAP[1001];
	int dp[1001] = { 0 };

	for (int i = 1; i <= N; i++) {
		cin >> MAP[i];
		if (i == 1) continue;
		dp[i] = 2134567890;
	}
	for (int i = 2; i <= N; i++) {
		for (int j = 1; j < i; j++) {
			if (j + MAP[j] >= i) {
				dp[i] = min(dp[i], dp[j] + 1);
			}
		}
	}
	if (dp[N] == 2134567890) cout << -1;
	else cout << dp[N];

	return 0;
}
