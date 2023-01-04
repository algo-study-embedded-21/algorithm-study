#include <iostream>
using namespace std;

int n;
int money[1001];
int dp[1001];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 1; i <= n; i++) cin >> money[i];
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			if (i - j < 0) continue;
			dp[i] = max(dp[i], dp[i - j] + money[j]);
		}
	}

	cout << dp[n];

	return 0;
}