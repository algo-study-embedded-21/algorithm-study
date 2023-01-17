#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int N, S, M;
	int V[51];
	int dp[51];

	cin >> N >> S >> M;

	for (int i = 1; i <= N; i++) {
		cin >> V[i];
	}
	
	dp[0] = S;

	for (int i = 2; i <= N; i++) {
		if (dp[i - 1] + V[i] <= M) dp[i] = dp[i - 1] + V[i];
		else if (dp[i - 1] - V[i] >= 0) dp[i] = max(dp[i], dp[i - 1] + V[i]);
		else if(dp[i-2])
	}

	cout << dp[N];

	return 0;
}
