/*
	dp[i][0] : i번째 잔을 안마신 경우의 최댓값 
	-> 이전 잔을 마시거나 안마시는 값 중 큰 것
	dp[i][1] : i번째 잔을 마신 경우의 최댓값 
	-> max(2번째 전 잔을 안마시고 1번째 전 잔 마시기 or 1번째 전 잔 안마시기) + 현재 잔
*/

#include <iostream>
using namespace std;

int dp[10000][2];
int arr[10000];
int n;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	dp[0][0] = 0; dp[0][1] = arr[0]; dp[1][0] = arr[0]; dp[1][1] = arr[0] + arr[1];

	for (int i = 2; i < n; i++) {
		dp[i][0] = max(dp[i-1][0], dp[i - 1][1]);
		dp[i][1] = max(dp[i - 2][0] + arr[i - 1], dp[i - 1][0]) + arr[i];
	}

	cout << max(dp[n - 1][0], dp[n - 1][1]);

	return 0;
}