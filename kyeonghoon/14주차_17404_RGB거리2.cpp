#include<iostream>
using namespace std;

int n, home[1001][3], dp[1001][3], cost=1e9;

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> home[i][0] >> home[i][1] >> home[i][2];
	}
	//1번 집의 색깔을 고르는 경우의수 세 가지
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			//색깔고름 
			if (i == j) {
				dp[1][j] = home[1][j];
			}
			//색깔이 바뀔 때마다 dp 전부 초기화
			else {
				dp[1][j] = 1e9;
			}
		}
		//2번 집부터 n번 집까지 최소비용 dp에 저장
		for (int j = 2; j <= n; j++) {
			dp[j][0] = home[j][0] + min(dp[j - 1][1], dp[j - 1][2]);
			dp[j][1] = home[j][1] + min(dp[j - 1][0], dp[j - 1][2]);
			dp[j][2] = home[j][2] + min(dp[j - 1][0], dp[j - 1][1]);
		}
		//n번 집까지 최소비용 dp 중 1번 집과 겹치지 않는 선에서 cost갱신
		for (int j = 0; j < 3; j++) {
			if (i != j)cost = min(cost, dp[n][j]);
		}
	}
	cout << cost;
}
