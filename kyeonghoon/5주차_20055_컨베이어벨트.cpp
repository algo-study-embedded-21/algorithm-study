#include<iostream>
#include<queue>
using namespace std;

int n, k;
int a[200], b[100];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> k;
	for (int i = 0; i < 2 * n; i++) {
		cin >> a[i];
	}
	int time = 0;
	int cnt = 0;
	while (cnt < k) {
		//벨트 회전
		int tmp = a[2 * n - 1];
		for (int i = 2 * n - 1; i >= 1; i--) {
			a[i] = a[i - 1];
		}
		a[0] = tmp;
		for (int i = n - 1; i >= 1; i--) {
			b[i] = b[i - 1];
		}
		b[0] = 0;
		//로봇 내리기
		if (b[n - 1] == 1) {
			b[n - 1] = 0;
		}
		//로봇 이동
		for (int i = n - 2; i >= 0; i--) {
			if (b[i] == 1 && b[i + 1] == 0 && a[i + 1] > 0) {
				b[i + 1] = 1;
				b[i] = 0;
				a[i + 1] -= 1;
				if (a[i + 1] == 0) {
					cnt += 1;
				}
			}
			else {
				continue;
			}
		}
		//로봇 내리기
		if (b[n - 1] == 1) {
			b[n - 1] = 0;
		}
		//로봇 올리기
		if (a[0] > 0) {
			b[0] = 1;
			a[0] -= 1;
			if (a[0] == 0) {
				cnt += 1;
			}
		}
		time += 1;
	}
	cout << time;
}
