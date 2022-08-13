#include<iostream>
#include<queue>
using namespace std;
int n, k, l, ans,s_x,s_y,s_dir;
int map[100][100];
vector<pair<int, char>> dir;
queue<pair<int, int>> s;
#define X first
#define Y second

int dx[] = { 0,1,0,-1 };
int dy[] = { 1,0,-1,0 };

int main() {
	cin >> n >> k;
	while (k--) {
		int x, y;
		cin >> x >> y;
		map[x - 1][y - 1] = 1;
	}
	cin >> l;
	while(l--) {
		int x; char c;
		cin >> x >> c;
		dir.push_back({ x,c });
	}
	s.push({ 0,0 });
	map[0][0] = 2;
	while (true) {
		ans++;
		int nx = s_x + dx[s_dir];
		int ny = s_y + dy[s_dir];
		if (nx<0 || nx>=n || ny < 0 || ny >= n)break;
		if (map[nx][ny] == 2)break;
		s.push({ nx,ny });
		if (map[nx][ny] == 1) {
			map[nx][ny] = 2;
		}
		else {
			map[s.front().X][s.front().Y] = 0;
			map[nx][ny] = 2;
			s.pop();
		}
		for (auto p : dir) {
			if (p.X == ans) {
				if (p.Y == 'D') {
					s_dir = (s_dir + 1) % 4;
				}
				else {
					s_dir = (s_dir + 3) % 4;
				}
			}
		}
		s_x = nx, s_y = ny;
	}
	cout << ans;
}
