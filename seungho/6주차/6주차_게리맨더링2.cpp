#include <iostream>
using namespace std;

int N;
int MAP[21][21];

// 최대최소 인구수 차이 계산
int cntdif(int x, int y, int d1, int d2) {
	int population[6] = { 0 };
	int MAP2[21][21] = { 0 };

	// 5번 선거구 찾기
	for (int tx = x; tx <= x + d2; tx++) {
		int ty = y + (tx - x);
		int ttx = tx;
		int tty = ty;		
		for (int l = x; l <= x + d1; l++) {
			MAP2[ttx][tty] = 5;
			population[5] += MAP[ttx][tty];
			ttx++;
			tty--;
		}
	}

	for (int tx = x+1; tx <= x + d2; tx++) {
		int ty = y + (tx-1 - x);
		int ttx = tx;
		int tty = ty;
		for (int l = x+1; l <= x + d1; l++) {
			MAP2[ttx][tty] = 5;
			population[5] += MAP[ttx][tty];
			ttx++;
			tty--;
		}
	}


	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			// 5번인 경우
			if (MAP2[i][j] == 5) continue;
			// 1번
			else if (i >= 1 && i < (x + d1) && j >= 1 && j <= y) {
				population[1] += MAP[i][j];
			}
			// 2번
			else if (i >= 1 && i <= (x + d2) && j > y && j <= N) {
				population[2] += MAP[i][j];
			}
			// 3번
			else if (i >= (x + d1) && i <= N && j >= 1 && j < (y - d1 + d2)) {
				population[3] += MAP[i][j];
			}
			// 4번
			else {
				population[4] += MAP[i][j];
			}
		}
	}
	int maxpop = -1;
	int minpop = 2134567890;
	for (int i = 1; i <= 5; i++) {
		maxpop = max(maxpop, population[i]);
		minpop = min(minpop, population[i]);
	}
	return (maxpop - minpop);
}

// x,y 에 대해 인구수 차이 최소값 계산
int function(int x, int y) {
	int mindif = 2134567890;
	for (int d1 = 1; d1 <= min(y - 1, N - x); d1++) {
		for (int d2 = 1; d2 <= min(N - y, N - x - d1); d2++) {
			int dif = cntdif(x, y, d1, d2);
			mindif = min(mindif, dif);
		}
	}
	return mindif;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> MAP[i][j];
		}
	}

	int ans = 2134567890;
	// x,y 정해서 구역 나누기
	for (int x = 1; x <= N; x++) {
		for (int y = 1; y <= N; y++) {
			// d1, d2 정하기
			int dif = function(x, y);
			ans = min(ans, dif);
		}
	}

	cout << ans;

	return 0;
}
