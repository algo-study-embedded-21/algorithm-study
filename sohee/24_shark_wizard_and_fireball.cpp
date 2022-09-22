#include <iostream>
#include <vector>
using namespace std;

int n, m, k;
int dx[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dy[] = { 0, 1, 1, 1, 0, -1, -1, -1 };

struct ball {
	int m;
	int s;
	int d;
};

int nd[2][4] = {
	{0, 2, 4, 6},
	{1, 3, 5, 7}
};

vector<ball> map[51][51];
vector<pair<int, int>> path;
int cnt[51][51];

int getMass() {
	int val = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (auto b : map[i][j]) {
				val += b.m;
			}
		}
	}
	return val;
}

void after_move() {
	path.clear();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int len = map[i][j].size();
			if (len < 2) continue;
			// 질량, 속력, 방향 계산
			int ma = 0;
			int s = 0;
			// 짝수인 경우 : 1
			// 홀수인 경우 : 0
			int d = map[i][j][0].d % 2 == 0;
			int flag = 0;
			for (int w = 0; w < len; w++) {
				ball now = map[i][j][w];
				ma += now.m;
				s += now.s;
				if (d != (now.d % 2 == 0)) flag = 1;
			}

			ma /= 5;
			s /= len;

			if (ma != 0) {
				for (int w = 0; w < 4; w++) {
					map[i][j].push_back({ ma, s, nd[flag][w] });
				}
			}
			map[i][j].erase(map[i][j].begin(), map[i][j].begin() + len);
		}
	}
}

void move() {
	for (auto p : path) {
		for (int i=0; i<cnt[p.first][p.second]; i++) {
			ball now = map[p.first][p.second][i];
			int nx = (p.first + dx[now.d] * now.s + n) % n;
			int ny = (p.second + dy[now.d] * now.s + n) % n;
			map[nx][ny].push_back({ now.m, now.s, now.d });
		}
		map[p.first][p.second].erase(map[p.first][p.second].begin(), map[p.first][p.second].begin() + cnt[p.first][p.second]);
	}

	after_move();
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> m >> k;
	for (int i = 0; i < m; i++) {
		int x, y, ma, s, d;
		cin >> x >> y >> ma >> s >> d;
		x--;
		y--;
		map[x][y].push_back({ ma, s, d });
	}
	for (int i = 0; i < k; i++) {
		path.clear();

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (map[i][j].size() > 0) {
					path.push_back({ i, j });
				}
				cnt[i][j] = map[i][j].size();
			}
		}

		move();
	}

	cout << getMass();

	return 0;
}
