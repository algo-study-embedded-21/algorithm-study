#include <iostream>
using namespace std;

int n, k;
int money[101];
int dp[111111];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		int x;
		cin >> money[i];
	}
/*
* 중복되는 경우의 수가 나와서 X
	dp[0] = 1;
	for (int i = 1; i <= k; i++) {
		for (int j = 1; j <= n; j++) {
			if (i - money[j] < 0) continue;
			dp[i] += dp[i - money[j]];
		}
	}
*/
	// i번째 동전으로 k의 가치를 만드는 경우의 수
	for (int i = 1; i <= n; i++) {
		dp[money[i]] += 1;
		for (int j = money[i] + 1; j <= k; j++) {
			if (j - money[i] < 0) continue;
			dp[j] += dp[j - money[i]];
		}
	}
	cout << dp[k];

	return 0;
}