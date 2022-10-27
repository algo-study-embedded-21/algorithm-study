#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

struct node {
	int x;
	int y;
};
int MAP[10][10];
int N, M;
int cnt;
vector<node> v;
int visited[10][10];
int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };
int maxval = -2134567890;

int area() {
	cnt = 0;

	for(int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			if (!visited[i][j] && !MAP[i][j]) cnt++;
		}

	return cnt;
}


void flood(node vi) {
	queue<node> q;

	q.push(vi);
	visited[vi.x][vi.y] = 1;

	while (!q.empty()) {
		node now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = now.x + dx[i];
			int ny = now.y + dy[i];

			if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
			if (MAP[nx][ny] == 1 || MAP[nx][ny] == 2)continue;
			if (visited[nx][ny])continue;

			visited[nx][ny] = 1;
			q.push({ nx,ny });
		}
	}
}


void dfs(int virus) {
	if (virus == 3) {
		memset(visited, 0, sizeof(visited));
		for(node i : v) flood(i);
		maxval = max(maxval, area());
		return;
	}

	for(int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			if (!MAP[i][j]) {
				MAP[i][j] = 1;
				dfs(virus + 1);
				MAP[i][j] = 0;
			}
		}
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();

	cin >> N >> M;

	for(int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			cin >> MAP[i][j];

			if (MAP[i][j] == 2) v.push_back({ i,j });
		}

	dfs(0);

	cout << maxval << '\n';

	int de = -1;
}
