/*
	dp[i][j] = str1�� i��° ���ڿ� str2�� j��° ���ڸ� ���Ҷ����� ��ġ�� �κм����� ����
	��ġ�� ��� - �������� ���� �� + 1
	��ġ���� ���� ��� - ������ ���� �� �� ū ��
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