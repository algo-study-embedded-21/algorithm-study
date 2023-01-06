#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct node {
	int y;
	int x;
};
int N, M;
int MAP[51][51] = { 0, };
int MAP2[51][51] = { 0, };

vector<node>v;

int diry[4] = { 0,0,1,-1 };
int dirx[4] = { 1,-1,0,0 };


int bfs1(int y, int x) {
	int visited1[51][51] = { 0, };
	queue<node> q;
	q.push({ y, x });
	while (!q.empty()) {
		node now = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int ny = now.y + diry[i];
			int nx = now.x + dirx[i];
			if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
			if (visited1[ny][nx] != 0) continue;
			visited1[ny][nx] = visited1[now.y][now.x] + 1;
			q.push({ ny,nx });
			if (MAP2[ny][nx] == 2) {
				return visited1[ny][nx];
			}
		}
	}
}
int path[14] = { 0 };
int visited[14][14] = { 0, };
vector<node> v1;

int mincd = 2134567890;
void func(int level) {
	path[0] = -1;
	
	if (level == v.size() - M+1) {
		int chickend = 0;
		for (int i = 0; i < v1.size(); i++) {
			chickend += bfs1(v1[i].y,v1[i].x);
		}
		if (chickend < mincd) {
			mincd = chickend;
		}
		return;
	}
	
	for (int i = path[level-1]+1; i < v.size(); i++) {
		node now = v[i];
		if (visited[now.y][now.x] != 0) continue;
		visited[now.y][now.x] = 1;
		path[level] = i;
		MAP2[now.y][now.x] = 0;
		func(level + 1);
		visited[now.y][now.x] = 0;
		path[level] = 0;
		MAP2[now.y][now.x] = 2;

	}
}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();
	
	cin >> N >> M;
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			int p;
			cin >> p;
			MAP[j][i] = p;
			MAP2[j][i] = p;
			if(p==2)
				v.push_back({ j,i });
			if(p==1)
				v1.push_back({ j,i });
		}
	}

	func(1);

	cout << mincd;
	return 0;
}
