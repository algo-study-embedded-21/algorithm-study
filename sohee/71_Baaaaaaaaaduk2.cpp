#include <iostream>
#include <vector>
using namespace std;

int n, m, l;
int map[20][20];
int visited[20][20];
int ans;
int now_ans;
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
vector<pair<int, int>> vec;

void init_visited() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			visited[i][j] = 0;
		}
	}
}

int count_answer(int x, int y) {
	visited[x][y] = 1;
	if (map[x][y] == 0) return 1;
	if (map[x][y] == 1) return 0;
	now_ans++;
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
		if (visited[nx][ny]) continue;
		if (map[nx][ny] != 0) continue;
		int next = count_answer(nx, ny);
		if (next) {
			now_ans--;
			return 1;
		}
	}
	return 0;
}

void find_answer(int level, int start) {
	if (level == 2) {
		// 개수 초기화
		now_ans = 0;
		init_visited();
		// 모두 visited일 때까지 반복
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (map[i][j] != 2) continue;
				if (visited[i][j]) continue;
				count_answer(i, j);
			}
		}

		ans = max(ans, now_ans);

		return;
	}

	for (int i = start; i++; i < l) {
		map[vec[i].first][vec[i].second] = 1;
		find_answer(level + 1, i);
		map[vec[i].first][vec[i].second] = 0;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
			if (map[i][j] == 0) vec.push_back({i, j});

		}
	}

	l = vec.size();

	find_answer(0, 0);

	cout << ans;

	return 0;
}