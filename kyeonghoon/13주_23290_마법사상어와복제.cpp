#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

int dx[] = { 0,-1,-1,-1,0,1,1,1 };
int dy[] = { -1,-1,0,1,1,1,0,-1 };
int s_dx[] = { -1,0,1,0 };
int s_dy[] = { 0,-1,0,1 };
int M, S, s_x, s_y;

struct Edge {
	int x, y, dir;
};

vector<Edge> fish[4][4], n_fish[4][4];
int smell[4][4], visited[4][4];
int max_sum;
int dir[3] = { -1,-1,-1 }, s_dir[3]; //상어의 이동경로

void magic() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			n_fish[i][j] = fish[i][j];
		}
	}
}

void move_fish() {
	vector<Edge> tmp[4][4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (fish[i][j].size() == 0)continue;
			for (auto p : fish[i][j]) {
				int ndir = p.dir;
				bool ok = false;
				for (int k = 0; k < 8; k++) {
					int nx = p.x + dx[ndir];
					int ny = p.y + dy[ndir];
					if (nx < 0 || nx >= 4 || ny < 0 || ny >= 4) {
						ndir = (ndir + 7) % 8;
						continue;
					}
					if (nx == s_x && ny == s_y) {
						ndir = (ndir + 7) % 8;
						continue;
					}
					if (smell[nx][ny]) {
						ndir = (ndir + 7) % 8;
						continue;
					}
					tmp[nx][ny].push_back({ nx,ny,ndir });
					ok = true;
					break;
				}
				if (!ok) {
					tmp[i][j].push_back(p);
				}
			}
			fish[i][j].clear();
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			fish[i][j] = tmp[i][j];
		}
	}
}

void move_shark(int x, int y, int lev) {
	if (lev == 3) {
		int visited[4][4] = { 0 };
		int sum = 0;
		int nx = s_x, ny = s_y;
		for (int i = 0; i < 3; i++) {
			nx += s_dx[dir[i]];
			ny += s_dy[dir[i]];
			if (visited[nx][ny] == 0) {
				visited[nx][ny] = 1;
				sum += fish[nx][ny].size();
			}
		}
		if (max_sum < sum) {
			max_sum = sum;
			for (int i = 0; i < 3; i++) {
				s_dir[i] = dir[i];
			}
		}
		return;
	}
	for (int k = 0; k < 4; k++) {
		int nx = x + s_dx[k];
		int ny = y + s_dy[k];
		if (nx < 0 || nx >= 4 || ny < 0 || ny >= 4)continue;
		dir[lev] = k;
		move_shark(nx, ny, lev + 1);
		dir[lev] = -1;
	}
}

void remove_fish(int tt) {
	for (int i = 0; i < 3; i++) {
		s_x += s_dx[s_dir[i]];
		s_y += s_dy[s_dir[i]];
		if (fish[s_x][s_y].size() != 0) {
			fish[s_x][s_y].clear();
			smell[s_x][s_y] = tt + 2;
		}
	}
	max_sum = -1;
	for (int i = 0; i < 3; i++) {
		s_dir[i] = -1;
		dir[i] = -1;
	}
}

void remove_smell(int tt) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (smell[i][j] == tt) {
				smell[i][j] = 0;
			}
		}
	}
}

void complete() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (n_fish[i][j].size() == 0)continue;
			for (auto p : n_fish[i][j]) {
				fish[i][j].push_back(p);
			}
			n_fish[i][j].clear();
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> M >> S;
	for (int i = 0; i < M; i++) {
		int x, y, dir;
		cin >> x >> y >> dir;
		x -= 1, y -= 1, dir -= 1;
		fish[x][y].push_back({ x,y,dir });
	}
	cin >> s_x >> s_y;
	s_x -= 1, s_y -= 1;
	for (int t = 1; t <= S; t++) {
		magic();
		move_fish();
		move_shark(s_x, s_y, 0);
		//cout << "상어이동 :" << s_dir.size() << '\n';
		remove_fish(t);
		remove_smell(t);
		complete();
	}
	int ans = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			ans += fish[i][j].size();
		}
	}
	cout << ans << '\n';
	return 0;
}
