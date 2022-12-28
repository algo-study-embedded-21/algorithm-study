#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;

int n;
int box[1000];
int dp[1000];

int maxIN = -1;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> box[i];
		dp[i] = 1;
	}
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (box[j] < box[i])
			{
				dp[i] = max(dp[i], dp[j] + 1);
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		maxIN = max(maxIN, dp[i]);
	}
	cout << maxIN;
	
	return 0;
}