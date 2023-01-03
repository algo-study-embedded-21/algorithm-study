#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<queue>

using namespace std;

int n;
int p[10001]; // p[n] = n�� ���� ī������ ����
int dp[10001]; // dp[n] = n���� ī�带 ��� �ִ���

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 1; i <=n; i++)
	{
		cin >> p[i];
		dp[i] = p[i]; // i������ ī�������� ��� ��츦 �⺻ ����
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