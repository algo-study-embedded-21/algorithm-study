#include <iostream>
using namespace std;

int main()
{
	int n, k;
	int dp[10001] = { 0 };
	int coins[101] = { 0 };
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		cin >> coins[i];
		if(coins[i]<=k) dp[coins[i]] = 1;
	}
	for (int i = 1; i <= k; i++) {
		for (int j = 1; j <= n; j++) {
			if (i - coins[j] > 0 && dp[i-coins[j]]>0) {
				if (dp[i] == 0) dp[i] = dp[i - coins[j]] + 1;
				dp[i] = min(dp[i],dp[i - coins[j]] + 1);
			}
		}
	}
	if (dp[k] == 0) {
		cout << -1;
		return 0;
	}
	cout << dp[k];
	return 0;
}
