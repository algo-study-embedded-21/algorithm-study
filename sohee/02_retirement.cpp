#include <iostream>
using namespace std;

int n;
int t[16];
int p[16];
int money[17];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();
	
	cin >> n;
	for (int i = 0; i < n; i++) {
		int time, price;
		cin >> time >> price;
		t[i] = time;
		p[i] = price;
	}

	for (int i = 0; i < n; i++) {
		// 마지막 날 보수를 받는다고 생각하고 돈 저장
		// 상담 기간이 퇴사일보다 긴 경우 제외
		if (i + t[i] > n ) continue;
		// 지금 일을 하는 것보다 다른 일을 한 것이 벌이가 더 좋다면 제외
		money[i + t[i]] = max(money[i] + p[i], money[i+t[i]]);
		// 남은 날들 동안 벌 수 있는 최소 금액을 설정
		for (int j = i + t[i] + 1; j <= n; j++) {
			money[j] = max(money[j], money[i + t[i]]);
		}
	}

	cout << money[n];

	return 0;
}