#include<iostream>
#include<cstring>
using namespace std;

int xx = -1, yy = -1, x2 = -1, y2 = -1;
int r, c, t;

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

int map[50][50];
int n_map[50][50];

void move() {
	for (int x = 0; x < r; x++) {
		for (int y = 0; y < c; y++) {
			if (map[x][y] == 0 || map[x][y] == -1)continue;
			int val = map[x][y] / 5;
			int cnt = 0;
			for (int k = 0; k < 4; k++) {
				int nx = x + dx[k];
				int ny = y + dy[k];
				if (nx < 0 || nx >= r || ny < 0 || ny >= c)continue;
				if (map[nx][ny] == -1)continue;
				n_map[nx][ny] += val;
				cnt += 1;
			}
			n_map[x][y] += (map[x][y] - val * cnt);
		}
	}
	n_map[xx][yy] = -1;
	n_map[x2][y2] = -1;
	memcpy(map, n_map, sizeof(n_map));
	memset(n_map, 0, sizeof(n_map));
	
}

void air() {
	//상
	for (int i = xx - 1; i >= 1; i--) {
		map[i][0] = map[i - 1][0];
	}
	for (int i = 0; i < c - 1; i++) {
		map[0][i] = map[0][i + 1];
	}
	for (int i = 0; i < xx; i++) {
		map[i][c - 1] = map[i + 1][c - 1];
	}
	for (int i = c - 1; i >= 2; i--) {
		map[xx][i] = map[xx][i - 1];
	}
	map[xx][1] = 0;
	//하
	for (int i = x2 + 1; i < r - 1; i++) {
		map[i][0] = map[i + 1][0];
	}
	for (int i = 0; i < c - 1; i++) {
		map[r-1][i] = map[r-1][i + 1];
	}
	for (int i = r - 1; i > x2; i--) {
		map[i][c - 1] = map[i - 1][c - 1];
	}
	for (int i = c - 1; i >= 2; i--) {
		map[x2][i] = map[x2][i - 1];
	}
	map[x2][1] = 0;
}

int ans() {
	int sum = 0;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (map[i][j] == -1)continue;
			sum += map[i][j];
		}
	}
	return sum;
}

void input() {
	cin >> r >> c >> t;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cin >> map[i][j];
			if (map[i][j] == -1) {
				if (xx == -1) {
					xx = i;
					yy = j;
				}
				else {
					x2 = i;
					y2 = j;
				}
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	input();
	for (int i = 0; i < t; i++) {
		move();
		air();
	}
	cout << ans();
}
