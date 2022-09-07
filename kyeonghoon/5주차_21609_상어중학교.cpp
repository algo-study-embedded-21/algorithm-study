#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring>
#include<tuple>
#include<vector>
using namespace std;

int n, m, ans;
int map[20][20];
int visited[20][20];

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

struct Edge {
	int cnt, zero, x, y;
};

bool cmp(Edge a, Edge b) {
	if (a.cnt > b.cnt)return true;
	if (a.cnt < b.cnt)return false;
	if (a.zero > b.zero)return true;
	if (a.zero < b.zero)return false;
	if (a.x > b.x)return true;
	if (a.x < b.x)return false;
	if (a.y > b.y)return true;
	if (a.y < b.y)return false;
	return false;
}

void input() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}
}

void gravity() {
	for (int i = 0; i < n; i++) {
		for (int j = n - 2; j >= 0; j--) {
			for (int k = j; k < n; k++) {
				if (map[k][i] == -1)continue;
				if (map[k + 1][i] == 6) {
					map[k + 1][i] = map[k][i];
					map[k][i] = 6;
				}
			}
		}
	}
}

void turn_left() {
	int n_map[20][20] = { 0 };
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			n_map[i][j] = map[j][n - i - 1];
		}
	}
	memcpy(map, n_map, sizeof(n_map));
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	input();
	bool ok = true;
	while (ok) {
		ok = false;
		vector<Edge> v;
		int num = 1;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (visited[i][j])continue;
				if (map[i][j] == -1 || map[i][j] == 0 || map[i][j] == 6)continue;
				queue<pair<int, int>> q;
				q.push({ i,j });
				visited[i][j] = num;
				int cnt = 1;
				int zero = 0;
				while (!q.empty()) {
					int x, y;
					tie(x, y) = q.front(); q.pop();
					for (int k = 0; k < 4; k++) {
						int nx = x + dx[k];
						int ny = y + dy[k];
						if (nx < 0 || nx >= n || ny < 0 || ny >= n)continue;
						if (visited[nx][ny])continue;
						if (map[nx][ny] == -1)continue;
						if (map[nx][ny] == 0 || map[nx][ny] == map[i][j]) {
							ok = true;
							visited[nx][ny] = num;
							cnt += 1;
							if (map[nx][ny] == 0) {
								zero += 1;
							}
							q.push({ nx,ny });
						}
					}
				}

				v.push_back({ cnt,zero,i,j });
				num += 1;
				for (int x = 0; x < n; x++) {
					for (int y = 0; y < n; y++) {
						if (map[x][y] == 0) {
							visited[x][y] = 0;
						}
					}
				}
			}
		}
		if (v.size() == 0)break;
		sort(v.begin(), v.end(), cmp);
		int lev = visited[v[0].x][v[0].y];
		if (v[0].cnt > 1) {
			ans += v[0].cnt * v[0].cnt;
		}
		memset(visited, 0, sizeof(visited));
		queue<pair<int, int>> q;
		q.push({ v[0].x,v[0].y });
		visited[v[0].x][v[0].y] = 1;
		//cout << v.size() << '\n';
		//cout << ans << '\n';
		while (!q.empty()) {
			int x, y;
			tie(x, y) = q.front(); q.pop();
			for (int k = 0; k < 4; k++) {
				int nx = x + dx[k];
				int ny = y + dy[k];
				if (nx < 0 || nx >= n || ny < 0 || ny >= n)continue;
				if (visited[nx][ny])continue;
				if (map[nx][ny] == -1)continue;
				if (map[nx][ny] == map[v[0].x][v[0].y] || map[nx][ny] == 0) {
					visited[nx][ny] = 1;
					q.push({ nx,ny });
				}
			}
		}
		for (int x = 0; x < n; x++) {
			for (int y = 0; y < n; y++) {
				if (visited[x][y] == 1) {
					map[x][y] = 6;
				}
			}
		}
		memset(visited, 0, sizeof(visited));
		v.clear();
		gravity();
		turn_left();
		gravity();
	}
	cout << ans;
}
