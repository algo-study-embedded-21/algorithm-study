#include<iostream>
#include<vector>

using namespace std;

struct cup { int zero,one, two; }; // 연속으로 선택한 컵수

int n;
vector<int> wine;
cup dp[10000];

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int a;
		cin >> a;
		wine.push_back(a);
	}
	dp[0].one = wine[0];
	dp[1].zero = dp[0].one;
	dp[1].one = wine[1];
	dp[1].two = dp[0].one + wine[1];
	for (int i = 2; i < n; i++)
	{
		// 이번 컵을 선택하지 않는 경우
		dp[i].zero = max(dp[i-1].zero,max(dp[i - 1].one, dp[i - 1].two));
		// 이전번에 컵을 선택하지 않았고 이번 컵을 선택하는 경우
		dp[i].one = max(max(dp[i - 2].one, dp[i - 2].two), dp[i - 1].zero) + wine[i];
		// 이전번 컵과 이번 컵 모두를 선택한 경우
		dp[i].two = dp[i - 1].one + wine[i];
	}
	cout << max(max(dp[n - 1].one, dp[n - 1].two), dp[n - 1].zero);
	return 0;
}