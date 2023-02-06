#include <iostream>
#include <queue>
using namespace std;

int n, m;
char map[250][250];
int visited[250][250];
int ans_sheep, ans_wolf;
int sheep, wolf;
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };

void bfs(int x, int y) {
	queue<pair<int, int>> q;
	q.push({ x, y });
	visited[x][y] = 1;

	while (!q.empty()) {
		pair<int, int> now = q.front();
		q.pop();

		if (map[now.first][now.second] == 'v') wolf++;
		else if (map[now.first][now.second] == 'o') sheep++;

		for (int i = 0; i < 4; i++) {
			int nx = now.first + dx[i];
			int ny = now.second + dy[i];

			if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
			if (visited[nx][ny]) continue;
			if (map[nx][ny] == '#') continue;
			visited[nx][ny] = 1;
			q.push({ nx, ny });
		}
	}
}

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	// init
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}

	// bfs -> 한 구역마다 양, 늑대 수 세기
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] == '#') continue;
			if (visited[i][j]) continue;
			sheep = 0; wolf = 0;
			bfs(i, j);

			if (sheep > wolf) ans_sheep += sheep;
			else ans_wolf += wolf;
		}
	}

	cout << ans_sheep << " " << ans_wolf;

	return 0;
}