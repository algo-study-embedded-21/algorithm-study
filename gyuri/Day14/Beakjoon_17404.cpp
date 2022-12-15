#include <iostream>
#define endl '\n'
#define MAX 213456789
using namespace std;

int N;
int cost[1001][3];
int dp[1001][3];
int answer = 213456789;

void Calc() {

	// 첫 번째 집 cost 복사
	for (int i = 0; i < 3; i++) {
		dp[1][i] = cost[1][i];
	}

	for (int i = 2; i <= N; i++) {

		// 이전 집이 빨간색일 때
		dp[i][0] = cost[i][0] + min(dp[i - 1][1], dp[i - 1][2]);
		// 이전 집이 초록색일 때
		dp[i][1] = cost[i][1] + min(dp[i - 1][0], dp[i - 1][2]);
		// 이전 집이 파란색일 때
		dp[i][2] = cost[i][2] + min(dp[i - 1][0], dp[i - 1][1]);
	}

	for (int i = 0; i < 3; i++) {
		answer = min(answer, dp[N][i]);
	}
}

void Init() {

	// MAX 값으로 배열 초기화
	for (int i = 2; i <= N; i++) {
		for (int j = 0; j < 3; j++) {
			dp[i][j] = MAX;
		}
	}
}

void Input() {

	cin >> N;

	for (int i = 1; i <= N; i++) {
		cin >> cost[i][0] >> cost[i][1] >> cost[i][2];
	}

}

void Output() {
	cout << answer;
}

int main() {

	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	Input();
	Init();
	Calc();
	Output();

	return 0;
}