#include<iostream>

using namespace std;

int n;
int dp[100000];

int make(int num)
{
	if (dp[num] == 0)
	{
		//  n번째 줄을 비우는경우 [ n-2까지의 경우의수 * n-1번째 줄을 채우는 경우의 수(=3) ]
		//  n번째 줄을 채우는 경우 [ 왼쪽,오른쪽 (=2) * (n-1번째 경우의수 - n번째에 채워진칸에 반대되는 칸이 채워진 경우의 수)]
		dp[num] = (3 * make(num - 2) + 2 * (make(num - 1) - make(num - 2))) % 9901; 
		return dp[num];
	}
	else return dp[num];
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	dp[0] = 3;
	dp[1] = 7;

	cout << make(n - 1);

	return 0;
}