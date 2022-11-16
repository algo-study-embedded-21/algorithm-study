#include<iostream>
#include<vector>
using namespace std;

struct gps {
	int x, y;
};

int dx[] = { 0,-1,-1,-1,0,1,1,1 };
int dy[] = { -1,-1,0,1,1,1,0,-1 };
int n, m;
int map[50][50];
int tmp[50][50];
int visited[50][50];
vector<gps> cloud;
vector<gps> n_cloud;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}
	cloud.push_back({ n - 1,0 });
	cloud.push_back({ n - 1,1 });
	cloud.push_back({ n - 2,0 });
	cloud.push_back({ n - 2,1 });
	while (m--) {
		int d, s;
		cin >> d >> s;
		d--;
		//구름이동
		for (auto p : cloud) {
			int nx = (p.x + dx[d] * s) % n;
			int ny = (p.y + dy[d] * s) % n;
			if (nx < 0) {
				nx = n + nx;
			}
			if (ny < 0) {
				ny = n + ny;
			}
			n_cloud.push_back({ nx,ny });
			visited[nx][ny] = 1;
		}
		//구름 비내림
		cloud.clear();
		for (auto p : n_cloud) {
			map[p.x][p.y] += 1;
		}
		//물복사 버그
		for (auto p : n_cloud) {
			int cnt = 0;
			for (int k = 1; k < 8; k += 2) {
				int nx = p.x + dx[k];
				int ny = p.y + dy[k];
				if (nx < 0 || nx >= n || ny < 0 || ny >= n)continue;
				if (map[nx][ny] > 0) {
					cnt += 1;
				}
			}
			tmp[p.x][p.y] += cnt;
		}
		for (auto p : n_cloud) {
			map[p.x][p.y] += tmp[p.x][p.y];
			tmp[p.x][p.y] = 0;
		}
		//구름 생김
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (map[i][j] >= 2 && visited[i][j] == 0) {
					map[i][j] -= 2;
					cloud.push_back({ i,j });
				}
				visited[i][j] = 0;
			}
		}
		n_cloud.clear();
	}
	int sum = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			sum += map[i][j];
		}
	}
	cout << sum;
}
