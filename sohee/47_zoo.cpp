/*
	0 : (o, x)
	1 : (x, o)
	2 : (x, x)
	dp[i][0] 
	= 2 * i행에 (o, x)로 사자를 둘 수 있는 경우의 수
	= dp[i - 1][1] + dp[i - 1][2];
*/
#include <iostream>
using namespace std;

int n;
int dp[100000][3];

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	dp[0][0] = 1; dp[0][1] = 1; dp[0][2] = 1;

	for (int i = 1; i < n; i++) {
		dp[i][0] = (dp[i - 1][1] + dp[i - 1][2]) % 9901;
		dp[i][1] = (dp[i - 1][0] + dp[i - 1][2]) % 9901;
		dp[i][2] = (dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][2]) % 9901;
	}
	
	cout << (dp[n-1][0] + dp[n-1][1] + dp[n-1][2]) % 9901;

	return 0;
}