#include<iostream>
using namespace std;

int n, k;
int v[101], w[101], dp[101][100001]; 
//dp[i][k] : 1번째 물건부터 i번째 물건까지 고려했을 때, 담을 수 있는 최대가치
// 0 0 0 0 0 13 13
// 0 0 0 8 8 13 13
// 0 0 6 8 8 13 14
// 0 0 6 8 12 13 14

int main() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		cin >> w[i] >> v[i];
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= k; j++) {
			if (j - w[i] >= 0) {
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i]] + v[i]);
			}
			else {
				dp[i][j] = dp[i - 1][j];
			}
		}
	}
	cout << dp[n][k] << '\n';
	return 0;
}
