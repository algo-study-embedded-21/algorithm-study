#include <iostream>
using namespace std;

int n;
int arr[1000];
int dp[1000];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
		// 초기화 필수. 중간에 작은 상자(1) 나오는 경우 때문
		dp[i] = 1;
	}

	for (int i = 1; i < n; i++) {
		for (int j = i - 1; j >= 0; j--) {
			if (arr[j] < arr[i]) dp[i] = max(dp[i], dp[j] + 1);
		}
	}

	int ans = 0;
	for (int i = 0; i < n; i++) ans = max(ans, dp[i]);
	cout << ans;

	return 0;
}