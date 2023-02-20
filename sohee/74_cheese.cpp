/*
visited[i] = i시간에 사라지는 치즈 or i시간에 다녀간 자리 -> 개수 세기 (cnt)
n * m - cnt -> 남은 치즈 카운트
i시간, cnt개
*/

#include <iostream>
#include <queue>
using namespace std;

int n, m;
int map[100][100];
int visited[100][100];
int cheese;
int now_cheese;
int t;
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };

void bfs() {
	queue<pair<int, int>> q;
	q.push({ 0, 0 });

	while (!q.empty()) {
		pair<int, int> now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = now.first + dx[i];
			int ny = now.second + dy[i];

			if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
			if (visited[nx][ny] >= t) continue;
			if (map[nx][ny] == 1) {
				now_cheese++;
				map[nx][ny] = 0;
			}
			else {
				q.push({ nx, ny });
			}

			visited[nx][ny] = t;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
			if (map[i][j] == 0) cheese++;
		}
	}

	while (n * m - cheese > 0) {
		t++;
		now_cheese = 0;
		bfs();
		cheese += now_cheese;
	}

	cout << t << '\n' << now_cheese;

	return 0;
}