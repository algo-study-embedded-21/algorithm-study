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
	// ���� �� ������ ���� �� �� �ִ� ���� Ȯ��
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
				// �̹� ���� �����ִ� ���� ����
				if (light[map[x][y][i].first][map[x][y][i].second] == 1) continue;
				light[map[x][y][i].first][map[x][y][i].second] = 1;
				// ���� ���� ������ ���
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
		// ���Ӱ� ���� ���� ���� ���ٸ� ���̻� Ȯ������ ����
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