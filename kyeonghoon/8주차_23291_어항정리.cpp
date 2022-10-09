//2:27
#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

int map[100][100];
int n, k, ans;

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

void move_fish() {
	int tmp[100][100] = { 0 };
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			if (map[x][y] == 0)continue;
			for (int k = 0; k < 4; k++) {
				int nx = x + dx[k];
				int ny = y + dy[k];
				if (nx < 0 || nx >= n || ny < 0 || ny >= n)continue;
				if (map[nx][ny] == 0)continue;
				int d = abs(map[x][y] - map[nx][ny]) / 5;
				if (d > 0) {
					if (map[x][y] > map[nx][ny]) {
						tmp[x][y] -= d;
					}
					else {
						tmp[x][y] += d;
					}
				}
			}
		}
	}
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			map[x][y] += tmp[x][y];
		}
	}
	vector<int> v;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (map[j][i] == 0)continue;
			v.push_back(map[j][i]);
		}
	}
	memset(map, 0, sizeof(map));
	int cnt = 0;
	for (auto p : v) {
		map[0][cnt++] = p;
	}
}

void move_map1() {
	int lx = 1, ly = 1, sy = 0;
	while (sy + ly + lx <= n) {//lx+ly<=n/2 (x)
		for (int y = 0; y < ly; y++) {
			for (int x = 0; x < lx; x++) {
				map[y + 1][x + sy + ly] = map[x][sy + ly - y - 1];
				map[x][sy + ly - y - 1] = 0;
			}
		}
		sy += ly;
		if (lx == ly)lx++;
		else ly++;
	}
}

void move_map2() {
	int lx = 1, ly = n / 2, sy = 0;
	for (int k = 0; k < 2; k++) {
		for (int x = 0; x < lx; x++) {
			for (int y = 0; y < ly; y++) {
				map[x + lx][y + sy + ly] = map[lx - x - 1][sy + ly - y - 1];
				map[lx - x - 1][sy + ly - y - 1] = 0;
			}
		}
		sy += ly;
		ly /= 2;
		lx *= 2;
	}
}

void add_fish() {
	int min_fish = 1e4;
	for (int i = 0; i < n; i++) {
		min_fish = min(min_fish, map[0][i]);
	}
	for (int i = 0; i < n; i++) {
		if (map[0][i] == min_fish)map[0][i] += 1;
	}
}

bool check() {
	int min_fish = 1e4;
	int max_fish = 0;
	for (int i = 0; i < n; i++) {
		min_fish = min(min_fish, map[0][i]);
		max_fish = max(max_fish, map[0][i]);
	}
	if (max_fish - min_fish <= k)return true;
	return false;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		cin >> map[0][i];
	}
	while (1) {
		if (check())break;
		add_fish();
		move_map1();
		move_fish();
		move_map2();
		move_fish();
		ans += 1;
	}
	cout << ans << '\n';
	return 0;
}
