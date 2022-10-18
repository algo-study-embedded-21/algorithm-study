#include<iostream>
#include<queue>
#include<tuple>
using namespace std;

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

int map[8][8];
int n, m, ans;

int bfs() {
	int copy[8][8];
	queue<pair<int, int>> q;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			copy[i][j] = map[i][j];
			if (map[i][j] == 2) {
				q.push({ i,j });
			}
		}
	}
	while (!q.empty()) {
		int x, y;
		tie(x, y) = q.front(); q.pop();
		for (int k = 0; k < 4; k ++) {
			int nx = x + dx[k];
			int ny = y + dy[k];
			if (nx < 0 || nx >= n || ny < 0 || ny >= m)continue;
			if (copy[nx][ny] != 0)continue;
			copy[nx][ny] = 2;
			q.push({ nx,ny });
		}
	}
	int aa = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (copy[i][j] == 0)aa++;
		}
	}
	return aa;
}

void dfs(int sx, int sy, int lev) {
	if (lev == 3) {
		int tmp = bfs();
		ans = max(ans, tmp);
		return;
	}
	for (int i = sx; i < n; i++) {
		for (int j = sy; j < m; j++) {
			if (map[i][j] == 1 || map[i][j] == 2)continue;
			map[i][j] = 1;
			dfs(i, j, lev + 1);
			map[i][j] = 0;
		}
		sy = 0;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}
	dfs(0, 0, 0);
	cout << ans;
}
