#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct node {
	int y;
	int x;
	int d;
};
int N, M;
int MAP[51][51] = { 0, };
int cd[51][51]={0};

int diry[4] = { 0,0,1,-1 };
int dirx[4] = { 1,-1,0,0 };

void bfs(int y, int x) {
	queue<node> q;
	q.push({ y,x,0 });
	int visited[51][51] = { 0 };

	while (!q.empty()) {
		node now = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int ny = now.y + diry[i];
			int nx = now.x + dirx[i];
			if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
			if (visited[ny][nx] != 0) continue;
			visited[ny][nx] = visited[now.y][now.x] + 1;
			q.push({ ny,nx,0 });
			if (MAP[ny][nx] == 2) {
				cd[ny][nx] += visited[ny][nx];
			}
		}
	}
	
}
int cntcd = 0;
void bfs1(int y, int x) {
	int visited[51][51] = { 0, };
	queue<node> q;
	q.push({ y, x, 0 });
	while (!q.empty()) {
		node now = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int ny = now.y + diry[i];
			int nx = now.x + dirx[i];
			if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
			if (visited[ny][nx] != 0) continue;
			visited[ny][nx] = visited[now.y][now.x] + 1;
			q.push({ ny,nx,visited[ny][nx] });
			if (MAP[ny][nx] == 2) {
				cntcd += visited[ny][nx];
				return;
			}
		}
	}
}


bool cmp(node a, node b) {
	if (a.d < b.d)
		return true;
	if (a.d > b.d)
		return false;
	return false;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();
	
	cin >> N >> M;
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			cin >> MAP[j][i];
		}
	}

	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			if (MAP[j][i] == 1) {
				bfs(j, i);
			}
		}
	}
	vector<node>v;
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			if(MAP[j][i]==2)
				v.push_back({ j,i,cd[j][i] });
		}
	}
	sort(v.begin(), v.end(), cmp);
	for (int i = M; i < v.size(); i++) {
		MAP[v[i].y][v[i].x] = 0;
	}
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			if (MAP[j][i] == 1) {
				bfs1(j, i);
			}
		}
	}
	cout << cntcd;
	return 0;
}
