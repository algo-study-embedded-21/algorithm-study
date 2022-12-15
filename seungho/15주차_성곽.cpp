#include <iostream>
#include <queue>
using namespace std;

int N, M;

int diry[4] = { 0,-1,0,1 };
int dirx[4] = { -1,0,1,0 };

int MAP[50][50][4];

struct axis {
	int y; int x;
};

int grouped[50][50];

int parent[2500];

int Find(int node) {
	if (node == parent[node]) {
		return node;
	}
	return parent[node] = Find(parent[node]);
}

int groupsize[2500];
int max_groupsize = 0;
int group_cnt = 0;
void Union(int a, int b) {
	int pa = Find(a);
	int pb = Find(b);

	if (pa == pb) return;
	parent[pb] = pa;
	groupsize[pa] += groupsize[pb];
	groupsize[pb] = 0;
	max_groupsize = max(max_groupsize, groupsize[pa]);
}

void bfs(int y, int x) {
	queue<axis> q;
	int visited[50][50];
	q.push({ y,x });
	visited[y][x] = 1;
	while (!q.empty()) {
		axis now = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			if (MAP[now.y][now.x][i]) continue;
			int ny = now.y + diry[i];
			int nx = now.x + dirx[i];
			if (ny < 0 || nx < 0 || ny >= M || nx >= N) continue;
			if (visited[ny][nx]) continue;
			visited[ny][nx] = 1;
			grouped[ny][nx] = 1;
			Union(now.y * N + now.x, ny * N + nx);
			q.push({ ny,nx });
		}
	}
}

int main()
{
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			int w;
			cin >> w;
			for (int k = 0; k < 4; k++) {
				int num = 1;
				num << k;
				MAP[i][j][k] = (num & w == num);
			}
		}
	}

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			int num = i * N + j;
			parent[num] = num;
			groupsize[num] = 1;
		}
	}

	int asdf = 1;

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if (grouped[i][j]) continue;
			grouped[i][j] = 1;
			group_cnt++;
			bfs(i, j);
		}
	}

	// 벽 없애보기
	int max_roomsize = 0;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < 4; k++) {
				int ny = i + diry[k];
				int nx = j + dirx[k];
				if (ny < 0 || nx < 0 || ny >= M || nx >= N) continue;
				max_roomsize = max(max_roomsize, groupsize[parent[i * N + j]] + groupsize[parent[ny * N + nx]]);
			}
		}
	}

	cout << group_cnt << "\n" << max_groupsize << "\n" << max_roomsize;

	return 0;
}
