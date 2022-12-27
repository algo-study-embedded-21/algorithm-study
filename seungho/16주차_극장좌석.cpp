#include <iostream>
using namespace std;

// dp[i][0] : i번 자리에 i번이 앉는 경우
// dp[i][1] : i번 자리에 i번이 앉지 않는 경우

long long dp[41][2];

int main()
{
	int N, M;
	int VIP[41] = {0};

	cin >> N >> M;

	for (int i = 1; i <= M; i++) {
		int v;
		cin >> v;
		VIP[v] = 1;
	}
	
	dp[1][0] = 1;
	dp[2][0] = 1;
	dp[2][1] = !(VIP[1] || VIP[2]);

	for (int i = 3; i <= N; i++) {
		dp[i][0] = dp[i - 1][0] + dp[i - 1][1];
		if (VIP[i] || VIP[i-1]) continue;
		dp[i][1] = dp[i - 2][0] + dp[i - 2][1];
	}

	cout << dp[N][0] + dp[N][1];

	return 0;
}
