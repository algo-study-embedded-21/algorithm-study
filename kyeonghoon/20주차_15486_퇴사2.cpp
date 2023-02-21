#include<iostream>
using namespace std;

int n, t[1500001],p[1500001], dp[1500001];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> t[i] >> p[i];
	}
	for (int i = n; i >= 1; i--) {
		if (i + t[i] > n + 1) {
			dp[i] = dp[i + 1];
		}
		else {
			dp[i] = max(dp[i + 1], p[i] + dp[i + t[i]]);
		}
	}
	cout << dp[1];
}
