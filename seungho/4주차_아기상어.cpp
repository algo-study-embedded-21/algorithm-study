#include <iostream>
#include <queue>
using namespace std;

int N;
int MAP[21][21]={0};
int sy, sx, siz;

struct Node {
	int y;
	int x;
};

int diry[4] = { -1,0,0,1 };
int dirx[4] = { 0,-1,1,0 };

void bfs(int y, int x) {
	queue<Node> q;
	q.push({ y,x });

	int visited[21][21] = { 0 };
	queue<Node> fish;
	int mindist=0;

	while (!q.empty()) {
		Node now = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int ny = now.y + diry[i];
			int nx = now.x + dirx[i];
			if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
			if (visited[ny][nx] > 0) continue;
			if (MAP[ny][nx] > siz) continue;
			visited[ny][nx] = visited[now.y][now.x] + 1;
			if (visited[ny][nx] > mindist) break;
			if (MAP[ny][nx] < siz) {
				fish.push({ ny,nx });
				mindist = visited[ny][nx];
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 9) {
				sy = i;
				sx = j;
			}
		}
	}
	siz = 2;
	while (true) {
		bfs(sy, sx);
	}


	return 0;
}
