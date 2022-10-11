//1:32
#include<iostream>
#include<vector>
using namespace std;

struct Sand {
	int x, y, w;
};

int n, ans;
int map[500][500];
int t_x, t_y;

int dx[] = { 0,1,0,-1 };
int dy[] = { -1,0,1,0 };

void move_sand(int x, int y, int dir) {
	if (map[x][y] == 0)return;
	int a = map[x][y];
	vector<Sand> sand;
	sand.push_back({ -2,0,2 });
	sand.push_back({ -1,-1,10 });
	sand.push_back({ -1,0,7 });
	sand.push_back({ -1,1,1 });
	sand.push_back({ 0,-2,5 });
	sand.push_back({ 1,-1,10 });
	sand.push_back({ 1,0,7 });
	sand.push_back({ 1,1,1 });
	sand.push_back({ 2,0,2 });
	if (dir == 1) {
		vector<Sand> tmp;
		for (auto p : sand) {
			int nx = -p.y;
			int ny = p.x;
			tmp.push_back({ nx,ny,p.w });
		}
		sand = tmp;
	}
	else if (dir == 3) {
		vector<Sand>tmp;
		for (auto p : sand) {
			int nx = p.y;
			int ny = -p.x;
			tmp.push_back({ nx,ny,p.w });
		}
		sand = tmp;
	}
	else if (dir == 2) {
		vector<Sand>tmp;
		for (auto p : sand) {
			int nx = p.x;
			int ny = -p.y;
			tmp.push_back({ nx,ny,p.w });
		}
		sand = tmp;
	}
	int left_sand = map[x][y];
	for (auto p : sand) {
		int nx = x + p.x;
		int ny = y + p.y;
		int s = map[x][y] * p.w / 100;
		if (s == 0)continue;
		//범위밖으로 나갔을 때
		if (nx < 0 || nx >= n || ny < 0 || ny >= n) {
			ans += s;
			left_sand -= s;
		}
		//범위안이라면
		else {
			map[nx][ny] += s;
			left_sand -= s;
		}
	}
	//남은 모래 알파
	if (x + dx[dir] < 0 || x + dx[dir] >= n || y + dy[dir] < 0 || y + dy[dir] >= n) {
		ans += left_sand;
	}
	else {
		map[x + dx[dir]][y + dy[dir]] += left_sand;
	}
	map[x][y] = 0;
}

void input() {
	cin >> n;
	t_x = (n - 1) / 2, t_y = (n - 1) / 2;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	input();
	int cnt = 1;
	int dir = 0;
	bool ok = false;
	for (int i = 0; i < n; i++) {
		//4방향 돌기
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < cnt; k++) {
				t_x += dx[dir];
				t_y += dy[dir];
				move_sand(t_x, t_y, dir);
				if (t_x == 0 && t_y == 0) {
					ok = true;
					break;
				}
			}
			dir = (dir + 1) % 4; //cnt만큼 이동 후 turn
			if (ok)break;
		}
		if (ok)break;
		cnt += 1; //두번 턴할 때마다 이동량 한 칸 증가
	}
	cout << ans;
}
