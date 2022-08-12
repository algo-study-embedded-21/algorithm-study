#include<iostream>
#include<queue>
using namespace std;
#define X first
#define Y second
int n, k, l;
int s_x, s_y, s_dir;
int map[100][100];
int dx[] = { 0,1,0,-1 };
int dy[] = { 1,0,-1,0 };

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	cin >> k;
	queue<pair<int, int>> s;
	vector<pair<int, char>> dir;
	for (int i = 0; i < k; i++) {
		int x, y;
		cin >> x >> y;
		x--; y--;
		map[x][y] = 1;
	}
	cin >> l;
	for (int i = 0; i < l; i++) {
		int num; char p;
		cin >> num >> p;
		dir.push_back({ num, p });
	}
	s.push({ 0, 0 });
	map[0][0] = 2;
	s_dir = 0;
	s_x = 0;
	s_y = 0;
	int time = 0;
	while (true) {
		s_x += dx[s_dir];
		s_y += dy[s_dir];
		if (s_x < 0 || s_x >= n || s_y < 0 || s_y >= n)break;
		if (map[s_x][s_y] == 2)break;
		s.push({ s_x, s_y });
		if (map[s_x][s_y] == 1) {
			map[s_x][s_y] = 2;
		}
		else {
			map[s.front().X][s.front().Y] = 0;
			s.pop();
		}
		map[s_x][s_y] = 2;
		time++;
		for (auto x : dir) {
			if (x.first == time) {
				if (x.second == 'D') {
					s_dir = (s_dir + 1) % 4;
				}
				else {
					s_dir = (s_dir + 3) % 4;
				}
			}
		}
	}
	cout << time + 1 << '\n';
	return 0;
}
