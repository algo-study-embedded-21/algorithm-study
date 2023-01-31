/*
dp[i][j] = i번째 동전으로 j값을 만드는데 드는 최소 횟수
dp[i][j] = 1 or min(dp[i-1][j], dp[i][j - money[i]] + 1)
*/

#include <iostream>
using namespace std;

int n, k;
int money[100];
int dp[100][10001];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> k;
	for (int i = 0; i < n; i++) cin >> money[i];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= k; j++) {
			dp[i][j] = 2134567890;
		}
	}

	for (int i = 0; i <= k; i++) {
		if (i % money[0] == 0) dp[0][i] = i / money[0];
	}

	for (int i = 0; i <= k; i++) {
		for (int j = 1; j < n; j++) {
			if (money[j] == i) dp[j][i] = 1;
			else if (money[j] < i) {
				dp[j][i] = min(dp[j - 1][i], dp[j][i - money[j]] + 1);
			}
			else {
				dp[j][i] = dp[j - 1][i];
			}
		}
	}

	int answer = 2134567890;
	for (int i = 0; i < n; i++) {
		if (answer > dp[i][k]) answer = dp[i][k];
	}

	if (answer == 2134567890) answer = -1;
	cout << answer;

	return 0;
}