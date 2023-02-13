#include <iostream>
#include <queue>
using namespace std;

int N, M;
int MAP[100][100];
int diry[4] = { 0,0,1,-1 };
int dirx[4] = { 1,-1,0,0 };

struct Node {
	int y; int x;
};

int bfs(int i, int j) {
	queue<Node> q;
	int visited[100][100]={0};
	
	q.push({ i,j });
	visited[i][j] = 1;

	while (!q.empty()) {
		Node now = q.front();
		q.pop();
		for (int d = 0; d < 4; d++) {
			int ny = now.y + diry[d];
			int nx = now.x + dirx[d];
			if (ny <= 0 || nx <= 0 || ny >= N - 1 || nx >= M - 1) {
				return 0;
			}
			if (MAP[ny][nx] != 0) continue;
			if (visited[ny][nx]) continue;
			visited[ny][nx] = 1;
			q.push({ ny,nx });
		}
	}
	return 1;
}

int main()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> MAP[i][j];
		}
	}

	int time = 0;
	int cnt_before = 0; // 이전 턴에 남아있던 치즈조각 수
	
	queue<Node> melt;

	while (1) {
		int flag = 0;
		int turn_cnt = 0;
		while (!melt.empty()) {
			Node now = melt.front();
			melt.pop();
			MAP[now.y][now.x] = 0;
		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (MAP[i][j] == 0) continue;
				
				// 치즈가 있는 경우
				flag = 1;
				turn_cnt++;
				
				// 공기랑 접해있는지 확인
				for (int d = 0; d < 4; d++) {
					int ny = i + diry[d];
					int nx = j + dirx[d];
					//if (ny <= 0 || nx <= 0 || ny >= N - 1 || nx >= M - 1) continue;
					if (MAP[ny][nx] == 0) {
						if (bfs(ny, nx)) continue;	// 치즈 내부 구멍이면 continue
						MAP[i][j] = 2;
						melt.push({ i,j });
					}
				}
			}
		}

		if (flag == 0) {
			cout << time << "\n" << cnt_before;
			break;
		};
		cnt_before = turn_cnt;
		time++;
	}

	return 0;
}
