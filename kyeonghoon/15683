#include<iostream>
#include<vector>
#include<tuple>
using namespace std;

int n, m, ret = 64;
int map[8][8];

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

int cctv_dir[] = { 4,2,4,4,1 };
vector<tuple<int,int,int>> cctv;

void copy_map(int a[][8], int b[][8]) {
	for (int i = 0; i < n; i ++ ) {
		for (int j = 0; j < n; j++) {
			b[i][j] = a[i][j];
		}
	}
}

void check(int x, int y,int dir) {
	dir = dir % 4;
	while (true) {
		x += dx[dir];
		y += dy[dir];
		if (x<0 || x>=n || y<0 || y>=m)break;
		if (map[x][y] == 6)break;
		map[x][y] = -1;
	}
}

void dfs(int index) {
	if (index == cctv.size()) {
		int sum = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (map[i][j] == 0) {
					sum += 1;
				}
			}
		}
		ret = min(sum, ret);
		return;
	}
	int x, y, type;
	tie(x, y, type) = cctv[index];
	int tmp[8][8] = { 0, };

	for (int dir = 0; dir < cctv_dir[type]; dir++) {
		copy_map(map, tmp);
		if (type == 0) {
			check( x, y, dir);
		}
		else if (type == 1) {
			check( x, y, dir);
			check( x, y, dir+1);

		}//오 왼 위 아래
		else if (type == 2) {
			check( x, y, dir);
			check(x, y, dir+2);

		}
		else if (type == 3) {
			check( x, y, dir);
			check(x, y, dir+1);
			check( x, y, dir+2);

		}
		else if (type == 4) {
			check( x, y, dir);
			check( x, y, dir+1);
			check( x, y, dir+2);
			check( x, y, dir+3);
		}
		dfs(index + 1);
		copy_map(tmp, map);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
			if (map[i][j] >= 1 && map[i][j] <= 5) {
				cctv.push_back({ i,j,map[i][j] - 1 });
			}
		}
	}
	dfs(0);
	cout << ret << '\n';
	return 0;

}
