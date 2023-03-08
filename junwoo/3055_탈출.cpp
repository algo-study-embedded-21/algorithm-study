#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct node {
	int x;
	int y;
};

int R, C;
node beaver, hedge;
vector<node> water;
char MAP[51][51];
int dx[] = { 0,1,0,-1 };
int dy[] = { 1,0,-1,0 };
int visited[51][51];
int Wvisited[51][51];

void input() {
	cin >> R >> C;

	for (int i = 0; i < R; i++) {
		cin >> MAP[i];
		for (int j = 0; j < C; j++) {
			if (MAP[i][j] == 'D') beaver = { i,j };
			if (MAP[i][j] == 'S') hedge = { i,j };
			if (MAP[i][j] == '*') water.push_back({ i,j });
		}
	}
}

void flood(node a) {
	queue<node> q;

	q.push(a);
	Wvisited[a.x][a.y] = 1;

	while (!q.empty()) {
		node now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = now.x + dx[i];
			int ny = now.y + dy[i];

			if (nx < 0 || ny < 0 || nx >= R || ny >= C) continue;
			if (Wvisited[nx][ny]) continue;
			if (MAP[nx][ny] == 'X' || MAP[nx][ny] == 'D') continue;

			Wvisited[nx][ny] = Wvisited[now.x][now.y] + 1;
			q.push({ nx,ny });
		}
	}
}

void escape() {
	queue<node> q;

	q.push(hedge);
	visited[hedge.x][hedge.y] = 1;

	while (!q.empty()) {
		node now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = now.x + dx[i];
			int ny = now.y + dy[i];

			if (nx < 0 || ny < 0 || nx >= R || ny >= C) continue;
			if (Wvisited[nx][ny] > 0 && Wvisited[nx][ny] <= visited[now.x][now.y] + 1) continue;
			if (visited[nx][ny]) continue;
			if (MAP[nx][ny] == 'X' || MAP[nx][ny] == '*') continue;

			visited[nx][ny] = visited[now.x][now.y] + 1;
			q.push({ nx,ny });
		}
	}
}

void output() {
	if (!visited[beaver.x][beaver.y]) cout << "KAKTUS";
	else cout << visited[beaver.x][beaver.y] - 1;
}

int main() {

	input();
	for (node i : water) {
		flood(i);
	}
	escape();
	output();

	return 0;
}
