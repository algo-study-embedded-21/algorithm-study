#include <iostream>
#include <vector>
using namespace std;

int answer = -1;
// 최대 10개의 세로 선, 30개의 가로 선
vector<vector<int>> v(11, vector<int>(31, 0));
int n, m, h;

int check() {
	for (int i = 1; i <= n; i++) {
		int ladder = i;
		int idx = 1;
		while (idx <= h) {
			if (v[ladder][idx] != 0) ladder = v[ladder][idx];
			idx++;
		}
		// 최종적으로 도착지점이 시작 번호와 같은지 확인
		if (i != ladder) return 0;
	}
	return 1;
}

void dfs(int level, int start_x, int start_y) {
	if (level > 3) return;

	if (check()) {
		if (answer == -1) answer = level;
		else answer = min(answer, level);
		// 깊이가 더 깊은 곳은 확인할 필요 없음
		return;
	}

	for (int i = start_x; i < n; i++) {
		int j = 1;
		if (i == start_x) j = start_y;
		for (j; j <= h; j++) {
			// 현재 세로선이나 연결할 세로선에 이미 연결된 가로 선이 있다면 pass
			if (v[i][j] != 0 || v[i+1][j] != 0) continue;
			v[i][j] = i + 1;
			v[i + 1][j] = i;

			int next_y = j == h ? 1 : j + 1;
			int next_x = next_y == 1 ? i + 1 : i;

			dfs(level + 1, next_x, next_y);

			v[i][j] = 0;
			v[i + 1][j] = 0;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();
	
	cin >> n >> m >> h;
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		v[b][a] = b + 1;
		v[b + 1][a] = b;
	}

	dfs(0, 1, 1);

	cout << answer;

	return 0;
}