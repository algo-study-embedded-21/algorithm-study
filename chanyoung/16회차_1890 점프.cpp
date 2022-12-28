#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;

int n;
int map[100][100];
long long dp[100][100];

int yy[2] = { 0,1 };
int xx[2] = { 1,0 };

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> map[i][j];
		}
	}
	dp[0][0] = 1;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int jump = map[i][j];
			if (jump == 0) continue;
			if (dp[i][j] == 0)continue;
			for (int d = 0; d < 2; d++)
			{
				int dy = i + yy[d] * jump;
				int dx = j + xx[d] * jump;
				if (dy<0 || dy>n - 1 || dx<0 || dx>n - 1)continue;
				dp[dy][dx] += dp[i][j];
			}
		}
	}
	cout << dp[n - 1][n - 1];
	
	return 0;
}