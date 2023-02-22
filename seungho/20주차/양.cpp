#include <iostream>
#include <queue>
using namespace std;

int R, C;
char MAP[250][250];
int visited[250][250] = { 0 };
int sheep = 0;
int wolf = 0;

struct Node {
	int y; int x;
};

int diry[4] = { 1,-1,0,0 };
int dirx[4] = { 0, 0, 1, -1 };

void bfs(int i, int j) {
	int s = 0;
	int w = 0;
	if (MAP[i][j] == 'o') s++;
	if (MAP[i][j] == 'v') w++;
	visited[i][j] = 1;
	queue<Node> q;
	q.push({ i, j });

	bool escape = false;

	while (!q.empty()) {
		Node now = q.front();
		q.pop();
		for (int d = 0; d < 4; d++) {
			int ny = now.y + diry[d];
			int nx = now.x + dirx[d];
			
			if (ny < 0 || nx < 0 || ny >= R || nx >= C) {
				escape = true;
				continue;
			}
			if (visited[ny][nx]) continue;
			if (MAP[ny][nx] == '#') continue;
			q.push({ ny,nx });
			visited[ny][nx] = 1;
			if (MAP[ny][nx] == 'o') s++;
			if (MAP[ny][nx] == 'v') w++;
		}
	}
	if (escape) return;
	if (s > w) wolf -= w;
	else sheep -= s;
}


int main()
{
	cin >> R >> C;

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 'o') sheep++;
			if (MAP[i][j] == 'v') wolf++;
		}
	}
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (visited[i][j] > 0) continue;
			if (MAP[i][j] == '.' || MAP[i][j] == '#') continue;
			bfs(i, j);
			int a=1;
		}
	}
	cout << sheep << " " << wolf;

	return 0;
}
