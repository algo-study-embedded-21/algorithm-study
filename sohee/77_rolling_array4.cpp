#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m, k;
int arr[50][50];
struct cmd {
	int x, y, s;
};
vector<cmd> cmds;
int used[6];
int ans = 2134567890;

// x방향 순서 틀려서 메모리 오류 났었음
int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };

void arr_to_origin(int origin[][50]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			origin[i][j] = arr[i][j];
		}
	}
}

void origin_to_arr(int origin[][50]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			arr[i][j] = origin[i][j];
		}
	}
}

void calc_ans() {
	for (int i = 0; i < n; i++) {
		int val = 0;
		for (int j = 0; j < m; j++) {
			val += arr[i][j];
		}
		ans = min(ans, val);
	}
}

void rolling(int x, int y, int s) {
	for (int range = 1; range <= s; range++) {
		// 순서대로 배열값 저장하기
		// 다음 칸이 범위 내라면 현재 위치의 값을 저장 (회전할 경우에도 중복 없이 저장 가능)
		queue<int> q;
		int r = x - range;
		int c = y - range;
		int row_lower = x - range;
		int row_upper = x + range;
		int col_lower = y - range;
		int col_upper = y + range;
		for (int i = 0; i < 4; i++) {
			while (true) {
				int nr = r + dx[i];
				int nc = c + dy[i];
				if (nr < row_lower || nr > row_upper || nc < col_lower || nc > col_upper) break;
				q.push(arr[r][c]);
				r = nr;
				c = nc;
			}
		}

		// 하나씩 다음칸에 저장하기
		r = x - range;
		c = y - range + 1;
		for (int i = 0; i < 4; i++) {
			while (true) {
				int nr = r + dx[i];
				int nc = c + dy[i];
				if (nr < row_lower || nr > row_upper || nc < col_lower || nc > col_upper) break;
				arr[r][c] = q.front();
				q.pop();
				r = nr;
				c = nc;
			}
		}
		arr[x - range][y - range] = q.front();
		q.pop();
	}
}

void dfs(int level) {
	if (level == k) {
		calc_ans();
		return;
	}

	int origins[50][50] = { 0 };
	// copy(&arr[0][0], &arr[0][0] + n * m, &origins[0][0]);
	arr_to_origin(origins);

	for (int i = 0; i < k; i++) {
		if (used[i])continue;
		rolling(cmds[i].x, cmds[i].y, cmds[i].s);
		used[i] = 1;
		dfs(level + 1);
		// copy(&origins[0][0], &origins[0][0] + n * m, &arr[0][0]);
		origin_to_arr(origins);
		used[i] = 0;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	// init
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> arr[i][j];
		}
	}
	for (int i = 0; i < k; i++) {
		int x, y, s;
		cin >> x >> y >> s;
		cmds.push_back({ x - 1, y - 1, s });
	}

	// 연산 순서 구하기(dfs)
	dfs(0);

	cout << ans;

	return 0;
}
