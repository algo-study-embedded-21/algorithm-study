/*
	dp[i] = dp[i-1] + dp[i-2]
	i��° �ڸ��� �ٲ��� �ʴ� ��� = dp[i-1]�� ����
	i��° �ڸ��� i-1��° �ڸ��� �ٲ� ��� = dp[i-2]�� ����
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

	// 0�� �߰��� �������� �� ��
	for (int i = 1; i <= m; i++) {
		if (dp[vip[i] - vip[i - 1] - 1] == 0) continue;
		ans *= dp[vip[i] - vip[i - 1] - 1];
	}
	if(dp[n - vip[m]] != 0)
		ans *= dp[n - vip[m]];

	cout << ans;

	return 0;
}