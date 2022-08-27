#include<iostream>
#include<queue>
using namespace std;

int r_x, r_y, r_dir;

int dx[] = { -1,0,1,0 };
int dy[] = { 0,1,0,-1 };

int a[50][50];
int visited[50][50];

int n, m;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	cin >> r_x >> r_y >> r_dir;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> a[i][j];
		}
	}
	//현재 위치 청소
	visited[r_x][r_y] = 1;
	while (true) {
		bool ok = false;
		//왼쪽방향으로 차례로 탐색
		for (int k = 1; k <= 4; k++) {
			int nx = r_x + dx[(r_dir - k + 4) % 4];
			int ny = r_y + dy[(r_dir - k + 4) % 4];
			if (nx < 0 || nx >= n || ny < 0 || ny >= m)continue;
			if (visited[nx][ny] == 1)continue;
			if (a[nx][ny] == 1)continue;
			visited[nx][ny] = 1;
			r_x = nx; r_y = ny; r_dir = (r_dir - k + 4) % 4;
			ok = true;
			break;
		}
		//4방향 모두 청소 && 벽
		if (!ok) {
			int nx = r_x + dx[(r_dir + 2) % 4];
			int ny = r_y + dy[(r_dir + 2) % 4];
			if (nx < 0 || nx >= n || ny < 0 || ny >= m || a[nx][ny] == 1) {
				break;
			}
			r_x = nx;
			r_y = ny;
		}
	}
	int ans = 0;
	//청소한 곳 탐색
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (visited[i][j] == 1) {
				ans += 1;
			}
		}
	}
	cout << ans;
}
