/*
	dp[i][0] : i��° ���� �ȸ��� ����� �ִ� 
	-> ���� ���� ���ðų� �ȸ��ô� �� �� ū ��
	dp[i][1] : i��° ���� ���� ����� �ִ� 
	-> max(2��° �� ���� �ȸ��ð� 1��° �� �� ���ñ� or 1��° �� �� �ȸ��ñ�) + ���� ��
*/

#include <iostream>
using namespace std;

int dp[10000][2];
int arr[10000];
int n;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	dp[0][0] = 0; dp[0][1] = arr[0]; dp[1][0] = arr[0]; dp[1][1] = arr[0] + arr[1];

	for (int i = 2; i < n; i++) {
		dp[i][0] = max(dp[i-1][0], dp[i - 1][1]);
		dp[i][1] = max(dp[i - 2][0] + arr[i - 1], dp[i - 1][0]) + arr[i];
	}

	cout << max(dp[n - 1][0], dp[n - 1][1]);

	return 0;
}