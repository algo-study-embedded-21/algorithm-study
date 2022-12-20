#include<iostream>
#include<vector>

using namespace std;

struct cup { int zero,one, two; }; // �������� ������ �ż�

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
		// �̹� ���� �������� �ʴ� ���
		dp[i].zero = max(dp[i-1].zero,max(dp[i - 1].one, dp[i - 1].two));
		// �������� ���� �������� �ʾҰ� �̹� ���� �����ϴ� ���
		dp[i].one = max(max(dp[i - 2].one, dp[i - 2].two), dp[i - 1].zero) + wine[i];
		// ������ �Ű� �̹� �� ��θ� ������ ���
		dp[i].two = dp[i - 1].one + wine[i];
	}
	cout << max(max(dp[n - 1].one, dp[n - 1].two), dp[n - 1].zero);
	return 0;
}