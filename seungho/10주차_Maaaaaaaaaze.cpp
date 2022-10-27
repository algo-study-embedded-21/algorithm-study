#include <iostream>
#include <queue>
using namespace std;

int MAP[5][5][5];
int MAP3[5][5][5];
int dirz[6] = { -1,0,0,0,0,1 };
int diry[6] = { 0,0,1,0,-1,0 };
int dirx[6] = { 0,1,0,-1,0,0 };

struct Node {
	int z; int y; int x;
};

void turn(int r, int level) {
	int MAP2[5][5] = { 0 };
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			MAP2[i][j] = MAP[level][i][j];
		}
	}
	if (r == 0) {
		return;
	}
	else if (r == 1) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				MAP[level][j][4 - i] = MAP2[i][j];
			}
		}
	}
	else if (r == 2) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				MAP[level][4 - i][4 - j] = MAP2[i][j];
			}
		}
	}
	else if (r == 3) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				MAP[level][4 - j][i] = MAP2[i][j];
			}
		}
	}
}

int bfs() {
	queue<Node> q;
	q.push({ 0,0,0 });

	int visited[5][5][5] = { 0 };

	while (!q.empty()) {
		Node now = q.front();
		q.pop();
		for (int d = 0; d < 6; d++) {
			int nz = now.z + dirz[d];
			int ny = now.y + diry[d];
			int nx = now.x + dirx[d];
			if (nz < 0 || ny < 0 || nx < 0 || nz>4 || ny>4 || nx>4) continue;
			if (nz == 0 && ny == 0 && nx == 0) continue;
			if (visited[nz][ny][nx] > 0) continue;
			if (MAP[nz][ny][nx] == 0) continue;
			visited[nz][ny][nx] = visited[now.z][now.y][now.x] + 1;
			q.push({ nz,ny,nx });
			if (nz == 4 && ny == 4 && nx == 4)	return visited[nz][ny][nx];
		}
	}
	return -1;
}

int ans = 2134567890;

void dfs(int level) {
	if (level > 4) {
		// 출발 또는 도착 칸 막혀있으면 return
		if (MAP[0][0][0] * MAP[4][4][4] == 0) return;
		int route = bfs();
		if (route > 0) {
			ans = min(ans, route);
		}
		return;
	}

	// 맵 복사
	int MAP2[5][5] = { 0 };
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			MAP2[i][j] = MAP[level][i][j];
		}
	}

	for (int r = 0; r < 4; r++) {
		turn(r, level);

		dfs(level + 1);
		// 맵 복원
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				MAP[level][i][j] = MAP2[i][j];
			}
		}
	}
}

int DAT[5] = { 0 };

void leveldfs(int level) {
	if (level > 4) {
		dfs(0);
		return;
	}

	for (int i = 0; i < 5; i++) {
		if (DAT[i] == 1) continue;
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				MAP[level][j][k] = MAP3[i][j][k];
			}
		}
		DAT[i] = 1;
		leveldfs(level + 1);
		DAT[i] = 0;
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				cin >> MAP[i][j][k];
				MAP3[i][j][k] = MAP[i][j][k];
			}
		}
	}
	leveldfs(0);
	if (ans == 2134567890) ans = -1;
	cout << ans;

	return 0;
}
