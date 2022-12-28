#include<iostream>
using namespace std;

int n, box[1000], dp[1000], ans;

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> box[i];
	}
	for (int i = 0; i < n; i++) {
		dp[i] = 1;
		for (int j = 0; j < i; j++) {
			if (box[j] < box[i] && dp[i] < dp[j] + 1) {
				dp[i] = dp[j] + 1;
			}
		}
		ans = max(dp[i], ans);
	}
	cout << ans;
}
