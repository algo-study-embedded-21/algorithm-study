#include <iostream>
#include <queue>
using namespace std;

int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };
int n;
char map[50][50];
int visited[50][50][4];
int r, c;
struct node {
	int x, y, cnt, dir;
};

struct cmp {
	bool operator() (node a, node b) {
		return a.cnt > b.cnt;
	}
};

int bfs() {
	priority_queue<node, vector<node>, cmp> q;
	q.push({ r, c, 0, 0 });
	q.push({ r, c, 0, 1 });
	q.push({ r, c, 0, 2 });
	q.push({ r, c, 0, 3 });
	for (int i = 0; i < 4; i++) visited[r][c][i] = 1;

	while (!q.empty()) {
		node now = q.top();
		q.pop();

		if (!(r == now.x && c == now.y) && map[now.x][now.y] == '#') return now.cnt;

		for (int i = 0; i < 4; i++) {
			int nx = now.x + dx[i];
			int ny = now.y + dy[i];

			if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
			if (visited[nx][ny][i]) continue;
			if (map[nx][ny] == '*') continue;
			if (map[now.x][now.y] != '!' && now.dir != i) continue;

			// 현재 위치가 ., #, !일 경우 직진 가능
			if (now.dir == i) {
				q.push({ nx, ny, now.cnt, i });
				visited[nx][ny][i] = 1;
			}
			// 현재 위치가 !일 경우 좌, 우 회전 가능
			else {
				q.push({ nx, ny, now.cnt + 1, i });
				visited[nx][ny][i] = 1;
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
			if (map[i][j] == '#') {
				r = i;
				c = j;
			}
		}
	}

	cout << bfs();

	return 0;
}