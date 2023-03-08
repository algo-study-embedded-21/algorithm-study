#include <iostream>
#include <queue>
using namespace std;

char MAP[50][50];
int R, C;
int visited[50][50];
int sy, sx;	// 출발점 S

struct Node {
	int y; int x;
};

int diry[4] = { 0,0,1,-1 };
int dirx[4] = { 1,-1,0,0 };

queue<Node> water;	// 이번 턴에 물이 이동할 시작 칸

void flow() {
	queue<Node> next;
	int visit[50][50] = { 0 };		// 이번 물 이동 때 물이 채워진 칸
	while (!water.empty()) {
		Node now = water.front();
		water.pop();
		for (int d = 0; d < 4; d++) {
			int ny = now.y + diry[d];
			int nx = now.x + dirx[d];
			if (ny < 0 || nx < 0 || ny >= R || nx >= C) continue;
			if (MAP[ny][nx] != '.') continue;
			if (visit[ny][nx] > 0) continue;
			MAP[ny][nx] = '*';
			visit[ny][nx] = 1;
			next.push({ ny,nx });
		}
	}

	// 새로 물이 채워진 칸 water에 담기
	while (!next.empty()) {
		Node now = next.front();
		next.pop();
		water.push(now);
	}
}

void bfs(int r, int c) {
	queue<Node> q;
	q.push({ r,c });

	int turn = 1;
	while (!q.empty()) {
		Node now = q.front();
		q.pop();

		// 이번 턴에 bfs 다 돌아봤으면 물 이동
		if (visited[now.y][now.x] == turn) {
			flow();
			turn++;
		}

		for (int d = 0; d < 4; d++) {
			int ny = now.y + diry[d];
			int nx = now.x + dirx[d];
			if (ny < 0 || nx < 0 || ny >= R || nx >= C) continue;
			if (MAP[ny][nx] == 'D') {
				cout << visited[now.y][now.x] + 1;
				return;
			}
			if (MAP[ny][nx] != '.') continue;	// 빈 칸이 아니면 continue
			if (visited[ny][nx] > 0) continue;
			if (ny == sy && nx == sx) continue;
			bool near_water = false;
			for (int dd = 0; dd < 4; dd++) {
				int nny = ny + diry[dd];
				int nnx = nx + dirx[dd];
				if (nny < 0 || nnx < 0 || nny >= R || nnx >= C) continue;
				if (MAP[nny][nnx] == '*') {
					near_water = true;
					break;
				}
			}
			if (near_water) continue;
			q.push({ ny,nx });
			visited[ny][nx] = visited[now.y][now.x] + 1;
		}
	}
	cout << "KAKTUS";
	return;
}

int main()
{
	cin >> R >> C;

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 'S') {
				sy = i;
				sx = j;
				MAP[i][j] = '.';
			}
			else if (MAP[i][j] == '*') water.push({ i,j });
		}
	}

	bfs(sy, sx);

	return 0;
}
