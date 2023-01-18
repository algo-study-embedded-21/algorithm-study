/*
dp[i][j] = i번째 수를 가지고 j라는 수를 만들 수 있는 경우의 수
*/

#include <iostream>
using namespace std;

int n;
int arr[100];
long long dp[100][21];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 0; i < n; i++) cin >> arr[i];
	dp[0][arr[0]] = 1;
	for (int i = 1; i < n - 1; i++) {
		for (int j = 0; j <= 20; j++) {
			if (j + arr[i] <= 20) dp[i][j] += dp[i - 1][j + arr[i]];
			if (j - arr[i] >= 0) dp[i][j] += dp[i - 1][j - arr[i]];
		}
	}

	cout << dp[n - 2][arr[n - 1]];

	return 0;
}