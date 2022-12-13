#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>

using namespace std;

struct color { int r, g, b; };

int n;
vector<color> house;
int ans = 2134567890;

int make(int c) // c = 1 : 첫번째 집을 빨간색 2:초록색 3:파란색
{
	color dp[1001] = { 0 };
	if (c == 0) dp[0] = { house[0].r,10000,10000 };
	else if (c == 1)dp[0] = { 10000,house[0].g,10000 };
	else dp[0] = { 10000,10000,house[0].b };
	for (int i = 1; i < n; i++)
	{
		dp[i].r = min(dp[i - 1].g, dp[i - 1].b) + house[i].r;
		dp[i].g = min(dp[i - 1].r, dp[i - 1].b) + house[i].g;
		dp[i].b = min(dp[i - 1].r, dp[i - 1].g) + house[i].b;
	}
	if (c == 0)dp[n - 1].r = 2134567890;
	else if (c == 1)dp[n - 1].g = 2134567890;
	else dp[n - 1].b = 2134567890;
	return min({ dp[n - 1].r,dp[n - 1].g,dp[n - 1].b });
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int r, g, b;
		cin >> r >> g >> b;
		house.push_back({ r,g,b });
	}
	for (int i = 0; i < 3; i++)
	{
		ans = min(ans, make(i));
	}
	cout << ans;
	return 0;
}