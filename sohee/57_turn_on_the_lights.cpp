#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int n, m;
vector<pair<int, int>> map[100][100];
int light[100][100];
int visited[100][100];
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };
int cnt;

void bfs() {
	light[0][0] = 1;
	int idx = 1;
	// 불을 켤 때마다 새로 갈 수 있는 곳을 확인
	while (1) {
		queue < pair<int, int>> q;
		q.push({ 0, 0 });
		visited[0][0] = idx;
		int flag = 0;

		while (!q.empty()) {
			pair<int, int> now = q.front();
			q.pop();

			int x = now.first;
			int y = now.second;
			int len = map[x][y].size();
			for (int i = 0; i < len; i++) {
				// 이미 불이 켜져있는 경우는 제외
				if (light[map[x][y][i].first][map[x][y][i].second] == 1) continue;
				light[map[x][y][i].first][map[x][y][i].second] = 1;
				// 새로 불을 밝히는 경우
				cnt++;
				flag = 1;
			}

			for (int i = 0; i < 4; i++) {
				int nx = x + dx[i];
				int ny = y + dy[i];

				if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
				if (visited[nx][ny] == idx) continue;
				if (!light[nx][ny]) continue;
				visited[nx][ny] = idx;
				q.push({ nx, ny });
			}
		}
		idx++;
		// 새롭게 불이 켜진 곳이 없다면 더이상 확인하지 않음
		if (!flag) break;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int x, y, a, b;
		cin >> x >> y >> a >> b;
		map[x - 1][y - 1].push_back({ a - 1, b - 1 });
	}

	bfs();
	cout << cnt + 1;

	return 0;
}