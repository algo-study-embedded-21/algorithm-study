#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int n, m;
vector<pair<int, int>> virus;
vector<pair<int, int>> v;
int map[50][50];
int ans = -1;
int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };

struct node {
	int x, y;
	int t;
};

// 조건 확인
int check(int n_map[50][50]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (n_map[i][j] == 0) return 0;
		}
	}
	return 1;
}

// 시간 확인하기
void getTime() {
	int time = 0;
	int n_map[50][50] = {0};
	memcpy(n_map, map, sizeof(map));
	queue<node> q;
	
	// 활성화 시킨 바이러스 queue에 넣기
	for (auto l : v) {
		q.push({ l.first, l.second, 1 });
		n_map[l.first][l.second] = -1;
	}

	while (!q.empty()) {
		node now = q.front();
		q.pop();

		// 매 번 체크하던 걸 시간 바뀔 때에만 체크하는 걸로 바꾸고 통과 
		if (now.t != time) {
			if (check(n_map)) {
				if (ans == -1) ans = time;
				else ans = min(ans, time);
				break;
			}
			time = now.t;
		}

		for (int i = 0; i < 4; i++) {
			int nx = now.x + dx[i];
			int ny = now.y + dy[i];

			if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
			if (n_map[nx][ny] != 0 && n_map[nx][ny] != 2) continue;
			n_map[nx][ny] = -1;
			q.push({ nx, ny, now.t + 1 });
		}
	}
}

// dfs 바이러스 놓을 자리 구하기
void dfs(int level, int start) {
	if (level == m) {
		getTime();
		return;
	}

	int len = virus.size();
	for (int i = start; i < len; i++) {
		v.push_back(virus[i]);
		dfs(level + 1, i + 1);
		v.pop_back();
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
			if (map[i][j] == 2) virus.push_back({ i, j });
		}
	}

	dfs(0, 0);

	cout << ans;

	return 0;
}