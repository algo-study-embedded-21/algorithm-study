//  k/n   1  2  3  4  5  6
//   1    1  1  1  1  1  1
//   2    2  3  4  5  6  7
//   3    3  6  10 15 21 28
//   4    4  10 20 35 56 84
//
//

#include<iostream>
using namespace std;

long long dp[201][201], n, k;

int main() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		dp[i][1] = 1;
		dp[1][i] = i;
	}
	for (int i = 2; i <= n; i++) {
		for (int j = 2; j <= k; j++) {
			dp[i][j] = (dp[i][j - 1] + dp[i - 1][j])%1000000000;
		}
	}
	cout << dp[n][k];
}
