#include <iostream>

using namespace std;

int n, k;
int coin[100];
int dp[100001];

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> k;
	for (int i = 0; i < n; i++)
	{
		cin >> coin[i];
	}
	for (int i = 0; i < n; i++)
	{
		int now = coin[i];
		dp[now] += 1;
		for (int j = 1; j <= k; j++)
		{
			if (j - now <= 0)continue;
			dp[j] += dp[j - now];
		}
	}
	cout << dp[k];

	return 0;
}