/*
	dp[i][j] = str1의 i번째 문자와 str2의 j번째 문자를 비교할때까지 일치한 부분수열의 길이
	일치할 경우 - 이전까지 비교한 값 + 1
	일치하지 않을 경우 - 이전에 비교한 값 중 큰 값
*/

#include <iostream>
#include <string>
using namespace std;

string str1, str2;
int dp[1001][1001];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> str1 >> str2;
	int len1 = str1.size();
	int len2 = str2.size();

	for (int i = 0; i < len1; i++) {
		for (int j = 0; j < len2; j++) {
			if (str1[i] == str2[j]) {
				dp[i + 1][j + 1] = dp[i][j] + 1;
			}else{
				dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
			}
		}
	}

	cout << dp[len1][len2];

	return 0;
}