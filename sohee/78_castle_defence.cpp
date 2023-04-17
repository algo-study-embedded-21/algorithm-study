#include <iostream>
#include <vector>
#include <queue>
#include <set>
#define ARCHER 3
using namespace std;

int n, m, d, ans;
int map[15][15];
int dx[] = { 0, -1, 0 };
int dy[] = { -1, 0, 1 };
vector<pair<int, int>> dist[3];
vector<int> archer_pos;

struct Distance {
	int x, y;
	int dist;
};

void init() {
	cin >> n >> m >> d;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}
}

void get_attack_distance() {
	for (int i = 0; i < ARCHER; i++) {
		int r = n;
		int c = archer_pos[i];
		dist[i].clear();

		queue<Distance> q;
		q.push({ r, c, 0 });

		int visited[15][15] = { 0 };

		while (!q.empty()) {
			Distance now = q.front();
			q.pop();
			if (now.dist == d) break;

			for (int j = 0; j < 3; j++) {
				int nx = now.x + dx[j];
				int ny = now.y + dy[j];

				if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
				if (visited[nx][ny]) continue;
				dist[i].push_back({ nx - r, ny });
				visited[nx][ny] = 1;
				q.push({ nx, ny, now.dist + 1 });
			}
		}
	}
}

void copy_map(int cmap[][15]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cmap[i][j] = map[i][j];
		}
	}
}

void simulation() {
	// 공격 가능 범위 구하기
	get_attack_distance();

	int cmap[15][15] = { 0 };
	int now_ans = 0;
	copy_map(cmap);

	// n번의 턴 시뮬레이션
	for (int i = n; i > 0; i--) {
		// 3명의 궁수가 죽일 적 고르기
		set<pair<int, int>> enemy;
		for (int j = 0; j < ARCHER; j++) {
			for (pair<int, int> di : dist[j]) {
				int r = i + di.first;
				if (r < 0 || di.second < 0 || di.second >= m) continue;
				if (!cmap[r][di.second]) continue;
				enemy.insert({r, di.second});
				break;
			}
		}
		// 죽인 적의 수 세기
		now_ans += enemy.size();

		// map에서 적 지우기
		for (pair<int, int> en : enemy) {
			cmap[en.first][en.second] = 0;
		}
	}

	// ans 비교하기
	ans = max(ans, now_ans);
}

void dfs(int level, int start) {
	if (level == ARCHER) {
		// simulation
		simulation();

		return;
	}

	for (int i = start; i < m; i++) {
		archer_pos.push_back(i);
		dfs(level + 1, i + 1);
		archer_pos.pop_back();
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	// init
	init();

	// 궁수 배치
	dfs(0, 0);

	cout << ans;

	return 0;
}
