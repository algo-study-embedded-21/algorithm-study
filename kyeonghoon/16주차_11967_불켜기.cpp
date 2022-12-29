#include<iostream>
#include<queue>
#include<tuple>
using namespace std;

int n, m, light[101][101],visited[101][101], ans;
vector<pair<int, int>> map[101][101];
queue<pair<int, int>> q;
int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	freopen("input.txt", "r", stdin);
	for (int i = 0; i < m; i++) {
		int x, y, a, b;
		cin >> x >> y >> a >> b;
		map[x][y].push_back({ a,b });
	}
	q.push({ 1,1 });
	visited[1][1] = 1;
	light[1][1] = 1;
	while (1) {
		bool ok = false;
		queue<pair<int, int>> tmp;
		while (!q.empty()) {
			int x, y;
			tie(x, y) = q.front(); q.pop();
			if (light[x][y] == 0)continue;
			for (int i = 0; i < map[x][y].size(); i++) {
				light[map[x][y][i].first][map[x][y][i].second] = 1;
			}
			for (int k = 0; k < 4; k++) {
				int nx = x + dx[k];
				int ny = y + dy[k];
				if (nx<1 || nx>n || ny<1 || ny>n)continue;
				if (visited[nx][ny] == 1)continue;
				visited[nx][ny] = 1;
				if (light[nx][ny] == 1) {
					ok = true;
					q.push({ nx,ny });
				}
				else {
					tmp.push({ nx,ny });
				}
			}
		}
		q = tmp;
		if (!ok)break;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (light[i][j])ans += 1;
		}
	}
	cout << ans;
}
