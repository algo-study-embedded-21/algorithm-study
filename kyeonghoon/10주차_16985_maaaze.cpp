#include<iostream>
#include<queue>
#include<cstring>
using namespace std;

int dx[] = { 1,-1,0,0,0,0 };
int dy[] = { 0,0,1,-1,0,0 };
int dz[] = { 0,0,0,0,1,-1 };

struct Edge {
	int x, y, z;
};

int map[5][5][5];
int dice[5][5][5];
int visited[5][5][5];
int used_map[5];
int ans = 1e9;

int bfs() {
	if (dice[0][0][0] != 1 || dice[4][4][4] != 1) {
		return 1e9;
	}
	queue<Edge> q;
	q.push({ 0,0,0 });
	memset(visited, -1, sizeof(visited));
	visited[0][0][0] = 0;
	while (!q.empty()) {
		Edge now = q.front(); q.pop();
		if (now.x == 4 && now.y == 4 && now.z == 4) {
			return visited[now.x][now.y][now.z];
		}
		for (int k = 0; k < 6; k++) {
			int nx = now.x + dx[k];
			int ny = now.y + dy[k];
			int nz = now.z + dz[k];
			if (nx < 0 || nx >= 5 || ny < 0 || ny >= 5 || nz < 0 || nz >= 5)continue;
			if (visited[nx][ny][nz] != -1)continue;
			if (dice[nx][ny][nz] != 1)continue;
			visited[nx][ny][nz] = visited[now.x][now.y][now.z] + 1;
			q.push({ nx,ny,nz });
		}
	}
	return 1e9;
}

void turn_dice(int lev, int num) {
	int tmp[5][5] = { 0 };
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			dice[i][j][lev] = map[4 - j][i][num];
		}
	}
	//4바퀴를 다 도는동안 다른 곳에서 건드리지 않음
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			map[i][j][num] = dice[i][j][lev];
		}
	}
}

void dfs(int lev) {
	if (lev == 5) {
		int tmp = bfs();
		ans = min(ans, tmp);
		return;
	}
	for (int num = 0; num < 5; num++) { //몇번째 맵을 사용할 것인가?
		if (used_map[num])continue;
		used_map[num] = 1;
		for (int dir = 0; dir < 4; dir++) {
			turn_dice(lev, num);
			dfs(lev + 1);
		}
		used_map[num] = 0;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	for (int z = 0; z < 5; z++) {
		for (int x = 0; x < 5; x++) {
			for (int y = 0; y < 5; y++) {
				cin >> map[x][y][z];
			}
		}
	}
	dfs(0);
	if (ans == 1e9) {
		cout << -1;
		return 0;
	}
	cout << ans;
}

