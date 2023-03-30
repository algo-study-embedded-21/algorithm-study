#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int main()
{
	long long N, K;
	cin >> N >> K;

	long long num = K;
	long long m = 0;
	long long cnt = 0;
	while (true) {
		if (num - pow(10, m) * 9 * (m + 1) <= 0) break;
		num -= pow(10, m) * 9 * (m + 1);
		cnt += pow(10, m) * 9;
		if (cnt > N) {
			cout << -1;
			return 0;
		}
		m++;
	}
	m++;
	cnt += num / m;
	if (cnt > N || (cnt == N && num % m != 0)) {
		cout << -1;
		return 0;
	}
	if (num % m == 0) {
		cout << cnt % 10;
		return 0;
	}
	cout << to_string(cnt + 1)[num % m - 1];

	return 0;
}
