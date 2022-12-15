/*
	dp[i][j] = j��ŭ�� ����, i�������� ������ ����� �ִ밪
	i��° ������ ������, �ȳ��� �� ��� 
	-> dp[i-1][j - stuff[i].first] + stuff[i].second or dp[i-1][j]
*/
#include <iostream>
using namespace std;

int n, k;
int dp[101][100001];
pair<int, int> stuff[101];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		int w, v;
		cin >> w >> v;
		stuff[i] = { w, v };
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= k; j++) {
			if (stuff[i].first > j)
				dp[i][j] = dp[i - 1][j];
			else
				dp[i][j] = max(dp[i - 1][j - stuff[i].first] + stuff[i].second, dp[i - 1][j]);
		}
	}

	cout << dp[n][k];

	return 0;
}