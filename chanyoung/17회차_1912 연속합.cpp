#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<queue>

using namespace std;

int n;
vector<long long> number;
long long dp[100001];
long long ans = -1;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int num;
		cin >> num;
		number.push_back(num);
	}
	dp[0] = number[0];
	ans = dp[0];
	for (int i = 1; i < n; i++)
	{
		dp[i] = max(dp[i - 1] + number[i], number[i]);
		ans = max(ans, dp[i]);
	}
	cout << ans;

	return 0;
}