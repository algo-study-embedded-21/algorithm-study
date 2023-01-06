#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M;
int ON[101][101];			// 불이 켜져있으면 1
int USED_SWITCH[101][101];	// 스위치를 사용한 방이면 1
int cnt = 1;				// 불이 켜진 방 개수

struct axis { int y; int x; };

vector<axis> SWITCH[101][101];

int finish;

int diry[4] = { 0,0,1,-1 };
int dirx[4] = { 1,-1,0,0 };

void bfs() {
	int visited[101][101]={0};
	queue<axis> q;
	q.push({ 1,1 });
	visited[1][1] = 1;

	while (!q.empty()) {
		axis now = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int ny = now.y + diry[i];
			int nx = now.x + dirx[i];
			if (ny<1 || nx<1 || ny>N || nx>N) continue;
			if (visited[ny][nx]) continue;
			if (!ON[ny][nx]) continue;		// 불이 꺼진 방이면 continue
			visited[ny][nx] = 1;
			q.push({ ny,nx });

			if (USED_SWITCH[ny][nx]) continue;	// 이미 스위치를 사용한 방이면 continue
			USED_SWITCH[ny][nx] = 1;
			finish = 0;
			for (int s = 0; s < SWITCH[ny][nx].size(); s++) {
				axis room = SWITCH[ny][nx][s];
				if (!ON[room.y][room.x]) cnt++;	// 이미 불이 켜진 방이 아니었으면 cnt++
				ON[room.y][room.x] = 1;
			}
		}
	}
}

int main()
{
	cin >> N >> M;

	for (int i = 0; i < M; i++) {
		int x, y, a, b;
		cin >> x >> y >> a >> b;
		SWITCH[x][y].push_back({ a,b });
	}

	// (1,1) 방 스위치 ON
	ON[1][1] = 1;
	for (int i = 0; i < SWITCH[1][1].size(); i++) {
		axis room = SWITCH[1][1][i];
		if (!ON[room.y][room.x]) cnt++;	// 이미 불이 켜진 방이 아니었으면 cnt++
		ON[room.y][room.x] = 1;
	}

	while (1) {
		finish = 1;
		bfs();
		if (finish) break;
	}

	cout << cnt;

	return 0;
}
