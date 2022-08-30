#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

int N;
int MAP[21][21] = { 0 };
int sy, sx, siz;

struct Node {
	int y;
	int x;
};

bool cmp(Node a, Node b) {
	if (a.y < b.y) return true;
	if (a.y > b.y) return false;
	if (a.x < b.x) return true;
	if (a.x > b.x) return false;
	return false;
}

int diry[4] = { -1,0,0,1 };
int dirx[4] = { 0,-1,1,0 };

int bfs(int y, int x) {
	queue<Node> q;
	q.push({ y,x });

	int visited[21][21] = { 0 };
	visited[y][x]= 1;

	int mindist = 2134567890;
	vector<Node> fish;

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
			q.push({ ny,nx });

			if (visited[ny][nx] > mindist) break;	// 이미 찾은 물고기보다 멀리 가면 break

			if (MAP[ny][nx] > 0 && MAP[ny][nx] < siz) {		// 먹을 수 있는 물고기 찾은 경우
				mindist = min(mindist,visited[ny][nx]);
				fish.push_back({ ny,nx });
			}
			
		}
	}
	if(fish.empty()) return -1;
	else {
		sort(fish.begin(), fish.end(), cmp);
		sy = fish[0].y;
		sx = fish[0].x;
		MAP[sy][sx] = 0;
		return mindist-1;
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
				MAP[i][j] = 0;
			}
		}
	}
	siz = 2;
	int ans = 0;
	int cnt = 0;	// 크기가 커진 후 물고기를 몇마리 먹었는지
	while (true) {
		int temp = bfs(sy, sx);
		
		if (temp == -1) break;
		cnt++;
		if (cnt == siz) {
			siz++;
			cnt = 0;
		}
		ans += temp;
	}
	cout << ans;

	return 0;
}
