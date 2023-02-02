/*
dp[i] = i번째 칸에 갈 수 있는 최소 점프 횟수
*/

#include <iostream>
using namespace std;

int n;
int arr[1000];
int dp[1111];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 0; i < n; i++)cin >> arr[i];
	for (int i = 1; i < 1111; i++)dp[i] = 2134567890;

	for (int i = 0; i < n; i++) {
		for (int j = 1; j <= arr[i]; j++) {
			dp[i + j] = min(dp[i + j], dp[i] + 1);
		}
	}

	int answer = dp[n - 1];
	if (answer == 2134567890) answer = -1;
	cout << answer;

	return 0;
}