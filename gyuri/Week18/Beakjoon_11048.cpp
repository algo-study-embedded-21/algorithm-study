#include <iostream>

using namespace std;

int N, M;
int arr[1001][1001];
int dp[1001][1001];

// dp[A][B] = V
// V : 좌표 AB까지 왔을 때 최대 사탕 개수

void Input() {
	
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> arr[i][j];
		}
	}
}

void FillDp() {

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			dp[i][j] = max(max(dp[i][j - 1], dp[i - 1][j]), dp[i - 1][j - 1]) + arr[i-1][j-1];
		}
	}
}

void Output() {

	cout << dp[N][M];
}

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	Input();
	FillDp();
	Output();

	return 0;
}