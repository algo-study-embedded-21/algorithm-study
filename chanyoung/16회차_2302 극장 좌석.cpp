#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;

int n, m;
vector<int> vip;
int dp[41];

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		int a;
		cin >> a;
		vip.push_back(a);
	}
	dp[0] = 1;
	dp[1] = 1;
	dp[2] = 2;
	for (int i = 3; i <= n; i++)
	{
		dp[i] = dp[i - 1] + dp[i - 2]; // i�� i-1�� �ڸ��� �ٲ��� �ʴ� ����� �� + �ٲٴ� ����� ��
	}
	int before = 0;
	long long ans = 1;
	for (int i = 0; i < m; i++)
	{
		int now = vip[i];
		ans *= dp[now - before - 1];
		before = now;
	}
	ans *= dp[n - before];
	cout << ans;

	return 0;
}