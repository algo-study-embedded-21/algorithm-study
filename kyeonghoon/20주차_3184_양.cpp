#include<iostream>
#include<queue>
#include<tuple>
using namespace std;

char map[250][250];
int n, m, visited[250][250], oo, vv;
int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (visited[i][j])continue;
			if (map[i][j] == 'v' || map[i][j] == 'o') {
				visited[i][j] = 1;
				queue<pair<int, int>> q;
				int xx = 0, yy = 0;
				if (map[i][j] == 'v') {
					xx = 1;
				}
				else {
					yy = 1;
				}
				q.push({ i,j });
				while (!q.empty()) {
					int x, y;
					tie(x, y) = q.front(); q.pop();
					for (int k = 0; k < 4; k++) {
						int nx = x + dx[k];
						int ny = y + dy[k];
						if (nx < 0 || nx >= n || ny < 0 || ny >= m)continue;
						if (visited[nx][ny])continue;
						if (map[nx][ny] != '#') {
							visited[nx][ny] = 1;
							if (map[nx][ny] == 'v') {
								xx += 1;
							}
							else if (map[nx][ny] == 'o') {
								yy += 1;
							}
							q.push({ nx,ny });
						}
					}
				}
				//cout << yy << " " << xx << '\n';
				if (xx >= yy) {
					vv += xx;
				}
				else {
					oo += yy;
				}
			}
		}
	}
	cout << oo << " " << vv;
}
