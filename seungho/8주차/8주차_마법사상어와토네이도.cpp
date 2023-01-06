#include <iostream>
using namespace std;

int N;
int MAP[500][500];
int MAP2[500][500] = { 0 };
int y, x;
int ans;
int flag = 1;

int diry[9] = {-2, -1, -1, -1, 0, 1, 1, 1, 2};
int dirx[9] = { 0, -1, 0, 1, -2, -1, 0, 1, 0};
int dirs[9] = { 2, 10, 7, 1, 5, 10, 7, 1, 2 };

void move(int n) {
	for (int i = 0; i < n; i++) {
		if (x - 1 < 0) {
			flag = 0;
			return;
		}
		x--;
		// 모래 이동
		int stotal = MAP[y][x];
		for (int d = 0; d < 9; d++) {
			int ny = y + diry[d];
			int nx = x + dirx[d];
			int ns = stotal * dirs[d] / 100;   // 이동되는 모래 양
			MAP[y][x] -= ns;
			// 범위를 벗어나면 답에 추가
			if (ny < 0 || nx < 0 || ny >= N || nx >= N) {
				ans += ns;
			}
			else {
				MAP[ny][nx] += ns;
			}
		}
		if (x - 1 < 0) {
			ans += MAP[y][x];
		}
		else {
			MAP[y][x - 1] += MAP[y][x];
		}
		MAP[y][x] = 0;
	}

}

void turn() {
	// 현재 맵 복사
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			MAP2[i][j] = MAP[i][j];
		}
	}
	
	// 맵 시계방향 회전
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			MAP[j][N-1-i] = MAP2[i][j];
		}
	}

	// 현재 토네이도 위치 회전
	int temp = x;
	x = N - 1 - y;
	y = temp;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
		}
	}

	// 초기 위치
	y = N / 2;
	x = N / 2;

	// 왼쪽으로 i칸 이동 -> 맵 시계방향 회전 -> 왼쪽으로 i칸 이동 -> 맵 시계방향 회전-> i++
	// 이동하려는 위치가 맵 밖으로 나가려하면 break

	int i = 1;
	while (1) {
		move(i);
		if (flag == 0) break;
		turn();

		move(i);
		if (flag == 0) break;
		turn();
		i++;
	}

	cout << ans;

	return 0;
}
