#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, M;
int MAP[50][50];
int MAP2[50][50];
int ans = 2134567890;

struct Node {
	int y;
	int x;
};

vector<Node> v;
vector<Node> active;

int diry[4] = { 0,0,1,-1 };
int dirx[4] = { 1,-1,0,0 };

void dfs(int level, int k) {
	if (level == M) {
		int cnt0 = 0;
		// 맵 복사
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				MAP2[i][j] = MAP[i][j];
				if (MAP[i][j] == 0) cnt0++;
			}
		}
		int maxtime = -1;
		// 플러드필
		// 큐에 먼저 바이러스 시작점 넣기
		queue<Node> q;
		for (int i = 0; i < active.size(); i++) {
			q.push({ active[i].y, active[i].x });
		}

		// 플러드필
		while (!q.empty()) {
			Node now = q.front();
			q.pop();
			if (MAP[now.y][now.x] != -2) {
				maxtime = max(MAP2[now.y][now.x], maxtime);
			}
			for (int i = 0; i < 4; i++) {
				int ny = now.y + diry[i];
				int nx = now.x + dirx[i];
				if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
				if (MAP2[ny][nx] == 0 || MAP2[ny][nx] == -2) {
					if (MAP2[ny][nx] == 0) cnt0--;
					MAP2[ny][nx] = MAP2[now.y][now.x] + 1;
					q.push({ ny,nx });
				}
			}
		}
		if (cnt0 > 0) return;
		if (maxtime == -1) maxtime = 1;
		// 최소 정답시간 갱신
		ans = min(ans, maxtime);
		return;
	}

	// 활성화 바이러스 고르기
	for (int i = k; i < v.size(); i++) {
		if (MAP[v[i].y][v[i].x] == 1) continue;
		MAP[v[i].y][v[i].x] = 1;
		active.push_back(v[i]);
		dfs(level + 1, i + 1);
		MAP[v[i].y][v[i].x] = -2;
		active.pop_back();
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int a;
			cin >> a;

			// 빈 칸, 비활성 바이러스 -> 0
			// 벽 -> -1
			// 활성 바이러스 -> 1~

			if (a == 2) {
				v.push_back({ i,j });
				MAP[i][j] = -2;
			}
			else if (a == 1) MAP[i][j] = -1;
			else MAP[i][j] = 0;
		}
	}

	// 1. 활성화할 바이러스 선택
	// 2. 활성화 후 플러드필

	dfs(0, 0);
	if (ans == 2134567890) ans = 0;
	cout << ans - 1;

	return 0;
}
