#include <iostream>
#include <set>
#include <vector>
#include <queue>
using namespace std;

int n, r, c;
char map[50][50];
int high[50][50];
int visited[50][50];
set<int> s;
vector<int> v;
vector<pair<int, int>> houses;
int dx[] = { 1, 0, -1, 0, 1, 1, -1, -1 };
int dy[] = { 0, 1, 0, -1, 1, -1, 1, -1 };

void init_visited() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			visited[i][j] = 0;
		}
	}
}

bool is_all_pass() {
	for (pair<int, int> house : houses) {
		if (!visited[house.first][house.second]) return false;
	}
	return true;
}

int bfs(int bottom, int up) {
	init_visited();

	queue<pair<int, int>> q;

	// 시작 지점의 높이도 꼭 체크하기!
	if (high[r][c] >= bottom && high[r][c] <= up) {
		q.push({ r, c });
		visited[r][c] = 1;
	}

	while (!q.empty()) {
		pair<int, int> now = q.front();
		q.pop();

		for (int i = 0; i < 8; i++) {
			int nx = now.first + dx[i];
			int ny = now.second + dy[i];

			if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
			if (visited[nx][ny]) continue;
			if (high[nx][ny] < bottom || high[nx][ny] > up) continue;
			visited[nx][ny] = 1;
			q.push({ nx, ny });
		}
	}

	return is_all_pass();
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'P') {
				r = i; c = j;
			}
			if (map[i][j] == 'K') houses.push_back({ i, j });
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> high[i][j];
			s.insert(high[i][j]);
		}
	}

	for (set<int>::iterator iter = s.begin(); iter != s.end(); iter++) v.push_back(*iter);
	int left = 0, right = 0;
	int ans = 2134567890;
	int len = v.size();

	while (left <= right) {
		if (left >= len || right >= len) break;
		if (bfs(v[left], v[right])) {
			ans = min(ans, v[right] - v[left]);
			left++;
		}
		else right++;
	}

	cout << ans;

	return 0;
}
