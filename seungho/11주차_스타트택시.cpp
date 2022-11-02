#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int N, M, fuel;
int MAP[21][21];

int ty, tx;		// 택시 좌표
int py, px; // 최단거리 승객 좌표

int diry[4] = { 0,0,1,-1 };
int dirx[4] = { 1,-1,0,0 };

struct Node {
	int y; int x;
};

vector<Node> v;

bool cmp(Node a, Node b) {
	if (a.y < b.y) return true;
	else if (a.y > b.y) return false;
	else if (a.x < b.x) return true;
	else if (a.x > b.x) return false;
	return false;
}

int bfs1(int y, int x) {
	// 택시와 승객 위치가 같은 경우
	if (MAP[y][x] > 1) {
		py = y;
		px = x;
		return 0;
	}
	int visited[21][21] = { 0 };

	vector<Node> pass;

	queue<Node> q;
	q.push({ y, x });

	int mindist = 2134567890;	// 최단거리

	while (!q.empty()) {
		Node now = q.front();
		q.pop();
		if (visited[now.y][now.x] > mindist) break;
		for (int d = 0; d < 4; d++) {
			int ny = now.y + diry[d];
			int nx = now.x + dirx[d];
			if (ny <= 0 || nx <= 0 || ny > N || nx > N) continue;
			if (ny == y && nx == x) continue;
			if (MAP[ny][nx] == 1) continue;
			if (visited[ny][nx] > 0) continue;
			visited[ny][nx] = visited[now.y][now.x] + 1;
			q.push({ ny,nx });
			if (MAP[ny][nx] > 1) {
				// 최단거리 갱신
				if (visited[ny][nx] <= mindist) {
					mindist = visited[ny][nx];
					pass.push_back({ ny,nx });
				}
			}
		}
	}
	if (mindist == 2134567890) return -1;

	sort(pass.begin(), pass.end(), cmp);

	py = pass[0].y;
	px = pass[0].x;

	return mindist;
}

int bfs2(int y, int x) {
	int visited[21][21] = { 0 };

	queue<Node> q;
	q.push({ y, x });

	while (!q.empty()) {
		Node now = q.front();
		q.pop();
		for (int d = 0; d < 4; d++) {
			int ny = now.y + diry[d];
			int nx = now.x + dirx[d];
			if (ny <= 0 || nx <= 0 || ny > N || nx > N) continue;
			if (ny == y && nx == x) continue;
			if (MAP[ny][nx] == 1) continue;
			if (visited[ny][nx] > 0) continue;
			visited[ny][nx] = visited[now.y][now.x] + 1;
			q.push({ ny,nx });
			if (ny == v[MAP[y][x] - 2].y && nx == v[MAP[y][x] - 2].x) return visited[ny][nx];
		}
	}
	return -1;
}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> N >> M >> fuel;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> MAP[i][j];
		}
	}

	cin >> ty >> tx;

	for (int m = 0; m < M; m++) {
		int sy, sx, ey, ex;
		cin >> sy >> sx >> ey >> ex;
		// 손님 번호 2번 ~ M+1번
		MAP[sy][sx] = m + 2;
		v.push_back({ ey,ex });
	}

	for (int m = 0; m < M; m++) {
		int dist1 = bfs1(ty, tx);	// 최단거리, 승객 좌표 찾기

		// 태울 수 있는 승객 없으면 -1 리턴
		if (dist1 == -1) {
			fuel = -1;
			break;
		}
		fuel -= dist1;

		if (fuel < 0) break;

		int dist2 = bfs2(py, px);	// 목적지까지 이동

		// 목적지까지 갈 수 없으면 -1 리턴
		if (dist2 == -1) {
			fuel = -1;
			break;
		}
		fuel -= dist2;
		if (fuel < 0) break;
		fuel += 2 * dist2;
		ty = v[MAP[py][px] - 2].y;	// 택시 위치 갱신
		tx = v[MAP[py][px] - 2].x;
		MAP[py][px] = 0;
	}

	if (fuel < 0) cout << -1;
	else cout << fuel;

	return 0;
}
