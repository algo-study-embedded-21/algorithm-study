#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>

using namespace std;

int n, k;
long long dp[201][201];

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> k;
	
	for (int i = 0; i <= n; i++)
	{
		dp[1][i] = 1;
	}
	for (int i = 1; i <= k; i++)
	{
		dp[i][0] = 1;
	}

	for (int i = 2; i <= k; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			for (int a = 0; a <= j; a++)
			{
				dp[i][j] += dp[i - 1][a];
			}
			dp[i][j] %= 1000000000;
		}
	}
	cout << dp[k][n];
	return 0;
}