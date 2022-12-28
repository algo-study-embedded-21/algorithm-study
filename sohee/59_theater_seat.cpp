/*
	dp[i] = dp[i-1] + dp[i-2]
	i번째 자리가 바뀌지 않는 경우 = dp[i-1]과 같음
	i번째 자리와 i-1번째 자리가 바뀐 경우 = dp[i-2]와 같음
*/
#include <iostream>
using namespace std;

int n, m;
int dp[41];
int vip[41];
int ans = 1;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> m;
	for (int i = 1; i <= m; i++) cin >> vip[i];

	dp[1] = 1;
	dp[2] = 2;
	for (int i = 3; i <= n; i++) dp[i] = dp[i - 1] + dp[i - 2];

	// 0이 중간에 곱해지면 안 됨
	for (int i = 1; i <= m; i++) {
		if (dp[vip[i] - vip[i - 1] - 1] == 0) continue;
		ans *= dp[vip[i] - vip[i - 1] - 1];
	}
	if(dp[n - vip[m]] != 0)
		ans *= dp[n - vip[m]];

	cout << ans;

	return 0;
}