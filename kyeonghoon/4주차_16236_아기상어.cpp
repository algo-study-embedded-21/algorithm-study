#include<iostream>
#include<queue>
#include<algorithm>
#include<tuple>
using namespace std;

int s_x, s_y, s_size, s_eat, n;
int map[20][20];

struct Fish {
	int x, y, size;
};

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
			if (map[i][j] == 9) {
				map[i][j] = 0;
				s_x = i; s_y = j; s_size = 2;
			}
		}
	}
	int ans = 0;
	while (true) {
		queue<pair<int, int>> q;
		q.push({ s_x,s_y });
		int visited[20][20] = { 0 };
		visited[s_x][s_y] = 1;
		bool ok = false;
		int time = 0;
		int xx = 20, yy = 20;
		while (!q.empty()) {
			int x, y;
			tie(x, y) = q.front(); q.pop();
			if (ok && visited[x][y] > time)break;
			if (map[x][y] != 0 && map[x][y] < s_size) {
				ok = true;
				if (x < xx) {
					xx = x;
					yy = y;
				}
				else if (x == xx) {
					if (y < yy) {
						yy = y;
					}
				}
				time = visited[x][y];
			}
			for (int k = 0; k < 4; k++) {
				int nx = x + dx[k];
				int ny = y + dy[k];
				if (nx < 0 || nx >= n || ny < 0 || ny >= n)continue;
				if (map[nx][ny] > s_size)continue;
				if (visited[nx][ny] > 0)continue;
				visited[nx][ny] = visited[x][y] + 1;
				q.push({ nx,ny });
			}
		}
		if (!ok)break;
		ans += (visited[xx][yy] - 1);
		map[xx][yy] = 0;
		s_x = xx; s_y = yy;
		s_eat += 1;
		if (s_size == s_eat) {
			s_size++;
			s_eat = 0;
		}
		
	}
	cout << ans;
}
