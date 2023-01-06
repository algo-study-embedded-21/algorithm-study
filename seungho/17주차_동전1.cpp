#include <iostream>
using namespace std;

int coins[101];
long long dp[10001];

int main()
{
	int n, k;
	cin >> n >> k;

	for (int i = 1; i <= n; i++) {
		cin >> coins[i];
	}
	
	dp[0] = 1;
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= k; j++) {
			if(j-coins[i] >= 0) dp[j] += dp[j - coins[i]];
		}
	}
	cout << dp[k];
	return 0;
}
