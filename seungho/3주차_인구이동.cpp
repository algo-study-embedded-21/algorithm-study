#include <iostream>
#include <queue>
#include <string.h>
using namespace std;

struct node {
	int y;
	int x;
};

int N, L, R;
int MAP[50][50];
int visited[50][50];

int dy[] = { 0,0,1,-1 };
int dx[] = { 1, -1, 0, 0 };

int flag;
int cnt=0;

void bfs(int y, int x) {
	queue<node> q;
	queue<node> uq;
	q.push({ y,x });
	uq.push({ y,x });
	visited[y][x] = 1;
	int population = MAP[y][x];			// 해당 연합 인구수 초기화

	// 연합 찾기
	while (!q.empty()) {
		node now = q.front();
		q.pop();
		
		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];
			if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
			if (visited[ny][nx] == 1) continue;
			int dif = abs(MAP[ny][nx] - MAP[now.y][now.x]);
			if (dif >= L && dif <= R) {
				population += MAP[ny][nx];
				q.push({ ny,nx });
				uq.push({ ny,nx });
				visited[ny][nx] = 1;
			}
		}
	}
	// 인구 이동
	int country = uq.size();
	if (country > 1) {
		flag = 0;
		while (!uq.empty()) {
			MAP[uq.front().y][uq.front().x] = population / country;
			uq.pop();
		}
		
	}
	
}


int main() {
	cin >> N >> L >> R;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
		}
	}
	while (true) {
		flag = 1;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (visited[i][j] == 1) continue;
				bfs(i, j);
			}
		}
		memset(visited, 0, sizeof(visited));
		if (flag == 1) break;
		cnt++;
	}
	
	cout<<cnt;

	return 0;
}
