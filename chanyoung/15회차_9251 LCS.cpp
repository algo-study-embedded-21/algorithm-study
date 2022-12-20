#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;

string st1, st2;
int dp[1001][1001]; // dp[st1][st2]

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> st1 >> st2;
	for (int i = 0; i <= st1.size(); i++)dp[i][0] = 0;
	for (int i = 0; i <= st2.size(); i++)dp[0][i] = 0;
	for (int i = 1; i <= st1.size(); i++)
	{
		for (int j = 1; j <= st2.size(); j++)
		{
			if (st1[i - 1] == st2[j - 1])
			{
				dp[i][j] = dp[i - 1][j - 1] + 1;
			}
			else
			{
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}
	cout << dp[st1.size()][st2.size()];
	
	return 0;
}