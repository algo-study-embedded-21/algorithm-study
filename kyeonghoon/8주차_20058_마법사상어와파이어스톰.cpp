//0:42
#include<iostream>
#include<queue>
#include<cstring>
#include<tuple>
using namespace std;

int n, q, l, ans1, ans2;
int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };
int map[64][64];
int visited[64][64];

void ice(int xx[64][64]) {
	int yy[64][64] = { 0 };
	int len = (1 << n);
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			if (map[i][j] == 0)continue;
			int cnt = 0;
			for (int k = 0; k < 4; k++) {
				int nx = i + dx[k];
				int ny = j + dy[k];
				if (nx < 0 || nx >= len || ny < 0 || ny >= len)continue;
				if (map[nx][ny] > 0) {
					cnt += 1;
				}
			}
			if (cnt < 3) {
				yy[i][j] = 1;
			}
		}
	}
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			if (yy[i][j] == 1) {
				xx[i][j] -= 1;
			}
		}
	}
}

void clock(int x, int y, int size) {
	int tmp[64][64] = { 0 };
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			tmp[i][j] = map[x + i][y + j];
		}
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			map[x + i][y + j] = tmp[size - j - 1][i];
		}
	}
}

void go(int size) {
	int len = (1 << size);
	for (int i = 0; i < (1 << n); i += len) {
		for (int j = 0; j < (1 << n); j += len) {
			clock(i, j, len);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> q;
	for (int i = 0; i < (1 << n); i++) {
		for (int j = 0; j < (1 << n); j++) {
			cin >> map[i][j];
		}
	}
	while (q--) {
		cin >> l;
		go(l);
		ice(map);
	}
	for (int i = 0; i < (1 << n); i++) {
		for (int j = 0; j < (1 << n); j++) {
			ans1 += map[i][j];
			if (map[i][j] == 0 || visited[i][j] == 1)continue;
			visited[i][j] = 1;
			int cnt = 1;
			queue<pair<int, int>> q;
			q.push({ i,j });
			while (!q.empty()) {
				int x, y;
				tie(x, y) = q.front(); q.pop();
				for (int k = 0; k < 4; k++) {
					int nx = x + dx[k];
					int ny = y + dy[k];
					if (nx < 0 || nx >= (1 << n) || ny < 0 || ny >= (1 << n))continue;
					if (visited[nx][ny])continue;
					if (map[nx][ny] == 0)continue;
					visited[nx][ny] = 1;
					cnt += 1;
					q.push({ nx,ny });
				}
			}
			ans2 = max(ans2, cnt);
		}
	}
	cout << ans1 << '\n';
	cout << ans2;
}
