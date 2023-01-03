#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<queue>

using namespace std;

int n;
int p[10001]; // p[n] = n개 구성 카드팩의 가격
int dp[10001]; // dp[n] = n개의 카드를 사는 최대비용

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 1; i <=n; i++)
	{
		cin >> p[i];
		dp[i] = p[i]; // i개구성 카드팩으로 사는 경우를 기본 세팅
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j < i; j++)
		{
			dp[i] = max(dp[i], dp[i - j] + dp[j]);
		}
	}
	cout << dp[n];

	return 0;
}