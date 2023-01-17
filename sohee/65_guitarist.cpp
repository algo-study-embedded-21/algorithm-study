/*
dp[i][j] = i번째 볼륨을 조절해서 j값을 만들 수 있는지 확인
*/

#include <iostream>
using namespace std;

int n, s, m;
int arr[50];
int dp[50][1001];
int answer = -1;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> s >> m;
	for (int i = 0; i < n; i++) cin >> arr[i];

	if (s + arr[0] >= 0 && s + arr[0] <= m) dp[0][s + arr[0]] = 1;
	if (s - arr[0] >= 0 && s - arr[0] <= m) dp[0][s - arr[0]] = 1;
	for (int i = 1; i < n; i++) {
		for (int j = 0; j <= m; j++) {
			if (!dp[i - 1][j]) continue;
			if (j + arr[i] >= 0 && j + arr[i] <= m) dp[i][j + arr[i]] = 1;
			if (j - arr[i] >= 0 && j - arr[i] <= m) dp[i][j - arr[i]] = 1;
		}
	}

	for (int i = 0; i <= m; i++) if (dp[n - 1][i] > 0) answer = i;
	cout << answer;

	return 0;
}
