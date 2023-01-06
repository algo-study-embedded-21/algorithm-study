#include <iostream>
#include <queue>
using namespace std;

int N, M, K;
int MAP[20][20];
int diry[4] = { 0,1,0,-1 };
int dirx[4] = { 1,0,-1,0 };

struct Node { int y; int x; };

int dfs(int y, int x, int n) {
	int cnt = 1;
	int visited[20][20]= {0};
	
	queue<Node> q;
	q.push({ y,x });

	visited[y][x] = 1;

	while (!q.empty()) {
		Node now = q.front();
		q.pop();
		for (int d = 0; d < 4; d++) {
			int ny = now.y + diry[d];
			int nx = now.x + dirx[d];
			if (ny < 0 || nx < 0 || ny >= N || nx >= M) continue;
			if (visited[ny][nx] == 1) continue;
			if (MAP[ny][nx] != n) continue;
			visited[ny][nx] = 1;
			q.push({ny,nx});
			cnt++;
		}
	}
	return cnt;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> N >> M >> K;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> MAP[i][j];
		}
	}

	// 초기 위치, 방향
	int sy = 0;
	int sx = 0;
	int d = 0;

	// 주사위	   하,전,상,후,좌,우
	int dice[6] = { 6, 5, 1, 2, 4, 3 };

	// 점수
	int score = 0;

	for (int k = 0; k < K; k++) {
		int ny = sy + diry[d];
		int nx = sx + dirx[d];
		if (ny < 0 || nx < 0 || ny >= N || nx >= M) {
			d += 2;
			d %= 4;
			ny = sy + diry[d];
			nx = sx + dirx[d];
		}
		// 1. 이동방향으로 한 칸 굴러간다.
		sy = ny;
		sx = nx;
		int t = dice[0];
		switch (d) {
			case 0:
				dice[0] = dice[5];
				dice[5] = dice[2];
				dice[2] = dice[4];
				dice[4] = t;
				break;
			case 1:
				dice[0] = dice[1];
				dice[1] = dice[2];
				dice[2] = dice[3];
				dice[3] = t;
				break;
			case 2:
				dice[0] = dice[4];
				dice[4] = dice[2];
				dice[2] = dice[5];
				dice[5] = t;
				break;
			case 3:
				dice[0] = dice[3];
				dice[3] = dice[2];
				dice[2] = dice[1];
				dice[1] = t;
				break;
		}

		// 2. 도착한 칸에 대한 점수를 획득한다.
		score += MAP[sy][sx] * dfs(sy, sx, MAP[sy][sx]);

		// 3. 주사위 아랫면과 주사위가 있는 칸 숫자 비교해서 이동 방향 결정
		if (dice[0] > MAP[sy][sx]) d++;
		else if (dice[0] < MAP[sy][sx]) d += 3;

		d %= 4;
	}

	cout << score;

	return 0;
}
