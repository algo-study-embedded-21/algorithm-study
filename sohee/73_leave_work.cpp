#include <iostream>
using namespace std;

int n;
int dp[1500001];
int t[1500000];
int p[1500000];

void findDays1() {
	for (int i = n - 1; i >= 0; i--) {
		int finish = i + t[i];
		// 범위를 벗어나는 경우 일 안함
		if (finish > n) dp[i] = dp[i + 1];
		// 일 안한다 vs 한다
		else dp[i] = max(dp[i + 1], dp[finish] + p[i]);
	}

	cout << dp[0];
}

void findDays2() {
	int result = 0;
	for (int i = 0; i < n; i++) {
		int finish = i + t[i];
		// i번째 날 일 한다
		if (finish <= n) {
			dp[finish] = max(dp[finish], dp[i] + p[i]);
			result = dp[finish];
		}
		// i번째 날 일 안한다
		dp[i + 1] = max(dp[i], dp[i + 1]);
	}

	cout << dp[n];
}

int main() {
	ios_base::sync_with_stdio;
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 0; i < n; i++) cin >> t[i] >> p[i];

	findDays2();

	return 0;
}