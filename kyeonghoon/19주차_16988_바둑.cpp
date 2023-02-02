#include<iostream>
#include<queue>
#include<tuple>
#include<cstring>
using namespace std;

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };
int n, m, ans, map[21][21];

void bfs() {
	int sum = 0;
	int visited[21][21] = { 0 };
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] == 2 && !visited[i][j]) {
				bool flag = true;
				queue<pair<int, int>> q;
				q.push({ i,j });
				visited[i][j] = 1;
				int cur = 0;
				while (!q.empty()) {
					int x, y;
					tie(x, y) = q.front(); q.pop();
					cur += 1;
					for (int k = 0; k < 4; k++) {
						int nx = x + dx[k];
						int ny = y + dy[k];
						if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
							if (map[nx][ny] == 0) {
								flag = false;
							}
							else if (map[nx][ny] == 2 && !visited[nx][ny]) {
								q.push({ nx,ny });
								visited[nx][ny] = 1;
							}
						}
					}
				}
				if (flag)sum += cur;
			}
		}
	}
	if (sum > ans)ans = sum;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}
	for (int x1 = 0; x1 < n; x1++) {
		for (int y1 = 0; y1 < m; y1++) {
			if (map[x1][y1] != 0)continue;
			for (int x2 = 0; x2 < n; x2++) {
				for (int y2 = 0; y2 < m; y2++) {
					if (x1 == x2 && y1 == y2)continue;
					if (map[x2][y2] != 0)continue;
					map[x1][y1] = 1;
					map[x2][y2] = 1;
					bfs();
					map[x1][y1] = 0;
					map[x2][y2] = 0;
				}
			}
		}
	}
	cout << ans;
}
