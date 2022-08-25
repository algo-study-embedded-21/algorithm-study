#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

int N, M;
int MAP[500][500];
int diry[4] = { 0,1,0,-1 };
int dirx[4] = { 1,0,-1,0 };
int visited[500][500] = { 0 };
int cnt = 0;
int maxcnt = 0;

struct Node {
	int y;
	int x;
};
vector<Node> path;

void dfs(int level, int y, int x) {
	if (level == 4) {
		maxcnt = max(maxcnt, cnt);
		for (int i = 0; i < 4; i++) {
			//cout << path[i].y << "," << path[i].x << " ";
		}
		//cout << "\n";
		return;
	}

	for (int i = 0; i < path.size(); i++) {
		Node now = path[i];
		for (int j = 0; j < 2; j++) {
			int ny = now.y + diry[j];
			int nx = now.x + dirx[j];
			if (ny < 0 || nx < 0 || ny >= N || nx >= M) continue;
			if (visited[ny][nx] > 0) continue;
			visited[ny][nx] = 1;
			cnt += MAP[ny][nx];
			path.push_back({ ny,nx });
			dfs(level + 1, ny, nx);
			visited[ny][nx] = 0;
			cnt -= MAP[ny][nx];
			path.pop_back();
		}
	}
}

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> MAP[i][j];
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			path.clear();
			memset(visited, 0, sizeof(visited));
			cnt = 0;
			path.push_back({ i, j });
			visited[i][j] = 1;
			cnt += MAP[i][j];
			dfs(1, i, j);
		}
	}
	cout << maxcnt;


	return 0;
}
