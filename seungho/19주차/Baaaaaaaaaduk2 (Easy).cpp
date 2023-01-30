#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int N, M;
int MAP[20][20];

int maxScore = -1;

struct Node {
	int y; int x;
};

int diry[4] = { 0,0,1,-1 };
int dirx[4] = { 1,-1,0,0 };

int checkMAP[20][20];

int bfs(int i, int j) {
	queue<Node> q;
	int visited[20][20]={0};
	q.push({ i,j });
	visited[i][j] = 1;
	checkMAP[i][j] = 1;
	int cnt = 1;
	while (!q.empty()) {
		Node now = q.front();
		q.pop();
		for (int d = 0; d < 4; d++) {
			int ny = now.y + diry[d];
			int nx = now.x + dirx[d];
			if (ny < 0 || nx < 0 || ny >= N || nx >= M) continue;
			if (visited[ny][nx]) continue;
			if (MAP[ny][nx] == 1) continue;
			if (MAP[ny][nx] == 0) return 0;
			visited[ny][nx] = 1;
			checkMAP[ny][nx] = 1;
			cnt++;
			q.push({ ny,nx });
		}
	}
	return cnt;
}

int check() {
	memset(checkMAP, 0, sizeof(checkMAP));
	int score = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (checkMAP[i][j]) continue;
			if (MAP[i][j] == 2) score += bfs(i,j);
		}
	}
	return score;
}

void dfs(int level, int y, int x) {
	if (level == 2) {
		maxScore = max(maxScore,check());
		return;
	}
	for(int i = y; i < N; i++){
		if (x == M - 1) {
			x = -1; continue;
		}
		for (int j = x+1; j < M; j++) {
			if (!MAP[i][j]) {
				MAP[i][j] = 1;
				dfs(level + 1, i, j);
				MAP[i][j] = 0;
			}
		}
	}
}

int main()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> MAP[i][j];
		}
	}

	// 1. dfs로 돌 2개를 둔다.
	// 2. bfs로 상대 돌 그룹이 죽는지 확인

	dfs(0,0,0);
	cout << maxScore;

	return 0;
}