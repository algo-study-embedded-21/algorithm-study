#include<iostream>
#include<queue>
#include<tuple>
#define xx first
#define yy second
using namespace std;

int n, m, ans1, ans2, ans3, pp = 1;
int map[51][51][4], visited[51][51], map2[51][51], map3[51][51];
vector<int> room_size;

int dx[] = { 0,-1,0,1 };
int dy[] = { -1,0,1,0 };

void make_wall(int i,int j,int x) {
	int num = x;
	int cnt = 0;
	while (1) {
		map[i][j][cnt] = (num % 2);
		num /= 2;
		if (num == 0)break;
		cnt += 1;
	}
	
}

int make_room(int i, int j) {
	queue<pair<int, int>> q;
	int cnt = 1;
	q.push({ i,j });
	while (!q.empty()) {
		int x, y;
		tie(x, y) = q.front(); q.pop();
		map2[x][y] = pp;
		for (int k = 0; k < 4; k++) {
			int nx = x + dx[k];
			int ny = y + dy[k];
			if (nx < 0 || nx > n || ny < 0 || ny > m)continue;
			if (map[x][y][k] == 1)continue;
			if (visited[nx][ny])continue;
			visited[nx][ny] = 1;
			q.push({ nx,ny });
			cnt += 1;
		}
	}
	pp++;
	room_size.push_back(cnt);
	return cnt;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> m >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int x;
			cin >> x;
			make_wall(i, j, x);
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (!visited[i][j]) {
				visited[i][j] = 1;
				int tmp = make_room(i, j);
				if (tmp > ans2) {
					ans2 = tmp;
				}
				ans1 += 1;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			map3[i][j] = room_size[map2[i][j] - 1];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int k = 0; k < 4; k++) {
				int nx = i + dx[k];
				int ny = j + dy[k];
				if (nx<0 || nx>n || ny<0 || ny>m)continue;
				if (ans3 < map3[i][j] + map3[nx][ny] && map2[i][j]!=map2[nx][ny]) {
					ans3 = map3[i][j] + map3[nx][ny];
				}
			}
		}
	}
	cout << ans1 << '\n';
	cout << ans2 << '\n';
	cout << ans3;
}
