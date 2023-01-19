#include <iostream>

using namespace std;

int N, result;
int nums[101];
long long dp[101][21];

// dp[A][B] = V
// V : nums�� A��°���� ���� �� B�� ������ ����� ��

void Input() {
	
	cin >> N;

	for (int i = 0; i < N-1; i++) {
		cin >> nums[i];
	}

	cin >> result;
}

void FillDp() {

	dp[0][nums[0]] = 1;

	for (int i = 1; i < N-1; i++) {
		for (int j = 0; j < 21; j++) {
			if (dp[i - 1][j] > 0) { // ������ ����� ������
				if (j - nums[i] >= 0) { // ���� ���� ���� ���� ��� + 1
					dp[i][j - nums[i]] += dp[i - 1][j];
				}
				if (j + nums[i] <= 20) { // ���� ���� ������ ���� ��� + 1
					dp[i][j + nums[i]] += dp[i - 1][j];
				}
			}
		}
	}
}

void Output() {

	cout << dp[N-2][result];
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