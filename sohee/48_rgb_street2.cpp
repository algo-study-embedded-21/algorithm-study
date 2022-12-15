/*
	dp[i][0] : i��° ������ ������ ���� �ּڰ�
	dp[i][1] : i��° ������ �ʷ��� ���� �ּڰ�
	dp[i][2] : i���� ������ �Ķ��� ���� �ּڰ�
*/
#include <iostream>
using namespace std;

int n;
int dp[1000][3];
int rgb[1000][3];
int ans = 2134567890;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> rgb[i][0] >> rgb[i][1] >> rgb[i][2];
	}

	// 1��° ���� ���� ���� r, g, b ������ Ȯ������ ���
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i == j) {
				dp[0][j] = rgb[0][j];
			}
			else {
				dp[0][j] = 10000;
			}
		}

		for (int j = 1; j < n; j++) {
			dp[j][0] = min(dp[j - 1][1], dp[j - 1][2]) + rgb[j][0];
			dp[j][1] = min(dp[j - 1][0], dp[j - 1][2]) + rgb[j][1];
			dp[j][2] = min(dp[j - 1][0], dp[j - 1][1]) + rgb[j][2];
		}

		int sub_ans = 2134567890;
		for (int j = 0; j < 3; j++) {
			if (i == j) continue;
			sub_ans = min(sub_ans, dp[n - 1][j]);
		}

		ans = min(ans, sub_ans);
	}

	cout << ans;

	return 0;
}