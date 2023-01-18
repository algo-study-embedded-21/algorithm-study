#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int N, S, M;
	int V[51];
	int dp[51][1001];

	cin >> N >> S >> M;

	for (int i = 1; i <= N; i++) {
		cin >> V[i];
	}
	
	dp[0][S] = 1;
        if(S+V[1]<=M) dp[1][S+V[1]] = 1;
        if(S-V[1]>=0) dp[1][S-V[1]] = 1;

	for (int i = 2; i <= N; i++) {
            {
                for(int j=0;j<=M;j++){
                    if(dp[i-1][j]){
                        if(j + V[i] <= M) dp[i][j+V[i]] = 1;
                        if(j - V[i] >= 0) dp[i][j-V[i]] = 1;
                    }
                }
		if (dp[i - 1] + V[i] <= M) dp[i] = dp[i - 1] + V[i];
		else if (dp[i - 1] - V[i] >= 0) dp[i] = max(dp[i], dp[i - 1] + V[i]);
		else if(dp[i-2])
	}

	cout << dp[N];

	return 0;
}
