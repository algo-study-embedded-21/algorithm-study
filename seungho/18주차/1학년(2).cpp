#include <iostream>
using namespace std;

int numbers[101];
long long dp[101][21];

int main()
{
	int N;

	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> numbers[i];
	}
	if(numbers[1] + numbers[2] >= 0 && numbers[1] + numbers[2] <=20) dp[3][numbers[1] + numbers[2]] = 1;
	if(numbers[1] - numbers[2] >= 0 && numbers[1] - numbers[2] <= 20) dp[3][numbers[1] - numbers[2]] = 1;

	for (int i = 4; i <= N; i++) {
		for (int j = 0; j <= 20; j++) {
			int x = j + numbers[i - 1];
			int y = j - numbers[i - 1];
			if(x >=0 && x <=20) dp[i][j] += dp[i - 2][x];
			if (y >= 0 && y <= 20) dp[i][j] += dp[i - 2][y];
		}
	}
	cout << dp[N][numbers[N]];

	return 0;
}
