#include <iostream>
#include <cstring>
using namespace std;

int dp[1001];
int box[1001];

int main()
{
	int n;
	cin >> n;	

	for (int i = 1; i <= n; i++) {
		cin >> box[i];
		dp[i] = 1;
	}

	int ans = 1;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < i; j++) {
			if (box[j] < box[i]) dp[i] = max(dp[i], dp[j]+1);
			ans = max(ans, dp[i]);
		}
	}

	cout << ans;

	return 0;
}
