#include<iostream>
#include<vector>
using namespace std;

int dy[] = { 0,-1,0,1 };
int dx[] = { 1,0,-1,0 };
int n;
int map[101][101];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	while (n--) {
		int x, y, d, g;
		cin >> x >> y >> d >> g;
		map[y][x] = 1;
		vector<int> dir;
		dir.push_back(d);
		while (g--) {
			for (int i = (int)dir.size() - 1; i >= 0; i--) {
				dir.push_back((dir[i] + 1) % 4);
			}
		}
		for (int i = 0; i < (int)dir.size(); i++) {
			y += dy[dir[i]];
			x += dx[dir[i]];
			map[y][x] = 1;
		}
	}
	int cnt = 0;
	for (int x = 0; x < 100; x++) {
		for (int y = 0; y < 100; y++) {
			if (map[x][y] == 0)continue;
			if (map[x + 1][y] == 1 && map[x][y + 1] == 1 && map[x + 1][y + 1] == 1) {
				cnt += 1;
			}
		}
	}
	cout << cnt << '\n';
	return 0;
}
