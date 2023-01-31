#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> number;
long long dp[100][21]; // dp[n-1][i] = n 번째 수까지 연산하여 i를 만들수 있는 경우의 수
int result; // 마지막에 도출해야 하는 수

int cal(int a, int b, int d)
{
	if (d == 0) return a + b;
	else if (d == 1)return a - b;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 0; i < n-1; i++) // 마지막 수 전까지만 벡터에 받기
	{
		int a;
		cin >> a;
		number.push_back(a);
	}
	cin >> result; // 마지막 수 받기
	dp[0][number[0]] = 1; // 첫번째 수는 연산 없이 세팅
	for (int i = 1; i < n - 1; i++) // 주어진 순서대로 연산
	{
		for (int j = 0; j < 21; j++) // 0~20중
		{
			if (dp[i - 1][j] > 0) // i-1 번까지 연산에서 j가 가능한 수라면
			{
				for (int d = 0; d < 2; d++)
				{
					int calnum = cal(j, number[i], d); //i번째 수와 연산
					if (calnum > 20 || calnum < 0)continue; // 주어진 범위 넘으면 무시
					dp[i][calnum] += dp[i-1][j]; // 가능한 경우의수 합
				}
			}
		}
	}
	cout << dp[n - 2][result]; // n-1개의 수를 연산해서 마지막수가 가능한 경우의 수

	return 0;
}
