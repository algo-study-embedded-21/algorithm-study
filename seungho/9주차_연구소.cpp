#include <iostream>
#include <queue>
#include <string.h>
using namespace std;

int N, M;
int MAP[10][10];
int MAP2[10][10];
int ind[10][10];
int DAT[100];
int visited[10][10];

struct Node {
	int y; int x;
};

int diry[4] = { 0,0,1,-1 };
int dirx[4] = { 1,-1,0,0, };

void floodfill(int y, int x) {
	queue <Node> q;
	q.push({ y,x });

	while (!q.empty()) {
		Node now = q.front();
		q.pop();
		for (int d = 0; d < 4; d++) {
			int ny = now.y + diry[d];
			int nx = now.x + dirx[d];
			if (ny < 0 || nx < 0 || ny >= N || nx >= M) continue;
			if (MAP2[ny][nx] == 1) continue;
			if (visited[ny][nx] == 1) continue;
			visited[ny][nx] = 1;
			MAP2[ny][nx] = 2;
			q.push({ ny,nx });
		}
	}
}

int wall(int i, int j, int k) {
	// visited 초기화
	memset(visited, 0, sizeof(visited));

	// MAP2 초기화 + 벽 3개 설치
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			// MAP 복사
			MAP2[y][x] = MAP[y][x];
			// 고른 인덱스와 일치하는 칸이면 벽 세우기
			if (ind[y][x] == i || ind[y][x] == j || ind[y][x] == k) {
				MAP2[y][x] = 1;
			}
		}
	}

	// floodfill
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			// 바이러스가 있는 칸이면 플러드필
			if (MAP[y][x] == 2) {
				if (visited[y][x] == 1) continue;
				floodfill(y, x);
			}
		}
	}
	int cnt = 0;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			if (MAP2[y][x] == 0) cnt++;
		}
	}
	return cnt;
}
int main()
{
	cin >> N >> M;
	int id = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> MAP[i][j];
			ind[i][j] = id;
			DAT[id] = MAP[i][j];
			id++;
		}
	}
	
	
	
	int maxcnt = -1;
	
	for (int i = 0; i < id-2; i++) {
		// 빈 칸이 아니면 continue
		if (DAT[i] != 0) continue;
		for (int j = i+1; j < id-1; j++) {
			if (DAT[j] != 0) continue;
			for (int k = j+1; k < id; k++) {
				if (DAT[k] != 0) continue;
				maxcnt = max(maxcnt, wall(i, j, k));
			}
		}
	}

	cout << maxcnt;

	return 0;
}
