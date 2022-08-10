#include <iostream>
#include <vector>
using namespace std;

int n, b, c;
vector<int> v;
// 100만 시험장에 모두 100만명씩 들어있고, 감독관이 한 명씩밖에 감시를 못한다면
// int의 범위를 벗어날 수 있음
long long cnt;

void getSupervisor(int people) {
	// 총감독관 1명이 감시할 수 있는 사람 제외
	people -= b;
	cnt++;

	// 음수일 경우 거르기
	if (people <= 0) return;

	// 부감독관이 몇 명 필요한지 세기
	cnt += people / c;
	if (people % c > 0) cnt++;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		v.push_back(a);
	}
	cin >> b >> c;

	for (int a : v) {
		getSupervisor(a);
	}
	cout << cnt;

	return 0;
}
