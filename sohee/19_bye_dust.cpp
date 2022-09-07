#include <iostream>
using namespace std;

int r, c, t;
int map[51][51];
int cleaner_x[2];
int cleaner_y[2];
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };

void diffusion() {
	// map을 한 번에 갱신시켜야하므로 새로운 배열에 변경될 값 저장
	int dust[51][51] = { 0 };

	// 확산
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (map[i][j] <= 0) continue;

			for (int k = 0; k < 4; k++) {
				int nx = i + dx[k];
				int ny = j + dy[k];

				if (nx < 0 || nx >= r || ny < 0 || ny >= c) continue;
				if (map[nx][ny] == -1) continue;
				
				dust[nx][ny] += map[i][j] / 5;
				dust[i][j] -= map[i][j] / 5;
			}
		}
	}
	// 확산이 끝난 후 map 갱신
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			map[i][j] += dust[i][j];
		}
	}
}

// 위쪽 공기청정기 방향대로 움직이기
void clean_up() {
	int x = cleaner_x[0] - 1;
	int y = cleaner_y[0];

	while (x > 0) {
		map[x][y] = map[x - 1][y];
		x--;
	}
	while (y < c - 1) {
		map[x][y] = map[x][y + 1];
		y++;
	}
	while (x < cleaner_x[0]) {
		map[x][y] = map[x + 1][y];
		x++;
	}
	while (y > 0) {
		map[x][y] = map[x][y - 1];
		y--;
	}
	map[cleaner_x[0]][cleaner_y[0] + 1] = 0;
}

// 아래쪽 공기청정기 방향대로 움직이기
void clean_botton() {
	int x = cleaner_x[1] + 1;
	int y = cleaner_y[1];

	while (x < r - 1) {
		map[x][y] = map[x + 1][y];
		x++;
	}
	while (y < c - 1) {
		map[x][y] = map[x][y + 1];
		y++;
	}
	while (x > cleaner_x[1]) {
		map[x][y] = map[x - 1][y];
		x--;
	}
	while (y > 0) {
		map[x][y] = map[x][y - 1];
		y--;
	}
	map[cleaner_x[1]][cleaner_y[1] + 1] = 0;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> r >> c >> t;

	int index = 0;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cin >> map[i][j];
			if (map[i][j] == -1) {
				cleaner_x[index] = i;
				cleaner_y[index++] = j;
			}
		}
	}

	int time = 0;
	while (time < t) {
		diffusion();
		clean_up();
		clean_botton();

		time++;
	}

	int dust = 0;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (map[i][j] < 0) continue;
			dust += map[i][j];
		}
	}

	cout << dust;

	return 0;
}