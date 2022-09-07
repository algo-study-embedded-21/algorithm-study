#include<iostream>
#include<queue>
#include<vector>
using namespace std;

int r, c, m, ans;
struct Edge {
	int x, y, s, d, z;
};

int dx[] = { -1,1,0,0 };
int dy[] = { 0,0,1,-1 };

bool operator<(Edge a, Edge b) {
	if (a.z < b.z)return false;
	if (a.z > b.z)return true;
	return false;
}

vector<Edge> shark[100][100];
priority_queue<Edge> n_shark;

void input() {
	cin >> r >> c >> m;
	while (m--) {
		int x, y, s, d, z;
		cin >> x >> y >> s >> d >> z;
		x--; y--; d--;
		shark[x][y].push_back({ x, y,s,d,z });
	}
}

int turn(int dir) {
	if (dir == 0)return 1;
	else if (dir == 1)return 0;
	else if (dir == 2)return 3;
	else return 2;
}

void kill_shark(int x) {
	for (int i = 0; i < r; i++) {
		if (shark[i][x].size() != 0) {
			ans += shark[i][x][0].z;
			shark[i][x].clear();
			break;
		}
	}
}

void move_shark() {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (shark[i][j].size() == 0)continue;
			for (auto p : shark[i][j]) {
				n_shark.push(p);
			}
			shark[i][j].clear();
		}
	}
	while (!n_shark.empty()) {
		Edge now = n_shark.top(); n_shark.pop();
		int nx = now.x + dx[now.d] * now.s;
		int ny = now.y + dy[now.d] * now.s;
		if (nx < 0) {
			nx *= -1;
			now.d = 1;
		}
		if (nx >= r) {
			int val = nx / (r - 1), mod = nx % (r - 1);
			if (val % 2 == 1) {
				nx = r - 1 - mod;
				now.d = 0;
			}
			else {
				nx = mod;
			}
		}
		if (ny < 0) {
			ny *= -1;
			now.d = 2;
		}
		if (ny >= c) {
			int val = ny / (c - 1), mod = ny % (c - 1);
			if (val % 2 == 1) {
				ny = c - 1 - mod;
				now.d = 3;
			}
			else {
				ny = mod;
			}
		}

		if (shark[nx][ny].size() != 0) {
			shark[nx][ny].clear();
		}
		shark[nx][ny].push_back({ nx,ny, now.s,now.d,now.z });
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	input();

	//낚시왕 이동
	for (int t = 0; t < c; t++) {
		//상어잡이
		kill_shark(t);
		/*cout << '\n';
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				if (shark[i][j].size() == 0) {
					cout << 0;
				}
				else {
					cout << shark[i][j][0].z;
				}
			}
			cout << '\n';
		}*/
		//상어이동
		move_shark();
		/*cout << '\n';
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				if (shark[i][j].size() == 0) {
					cout << 0;
				}
				else {
					cout << shark[i][j][0].z;
				}
			}
			cout << '\n';
		}*/
	}
	cout << ans;
}
